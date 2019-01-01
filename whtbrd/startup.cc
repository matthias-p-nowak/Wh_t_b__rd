#include <startup.hh>

using namespace std;


void print_timing(const char *file, int line) {
  static double sofar=0;
  struct rusage usage;
  if(getrusage(RUSAGE_SELF, &usage)) {
    perror("rusage");
  }
  else {
    struct timeval *t=&usage.ru_utime;
    double spent=t->tv_sec+ 1.0*t->tv_usec/1000000;
    printf("%s:%d:time spent %f, sofar %f\n",file,line,spent-sofar,spent);
    sofar=spent;
  }
}

#define TIMING print_timing(__FILE__,__LINE__);





#define STR(x) #x

int main(int argc, char *argv[]) {
  TIMING
  QApplication whtbrd_App(argc, argv);
  whtbrd_App.setOrganizationName("Wh_t_b__rd");
  whtbrd_App.setApplicationName("whtbrd");
  whtbrd_App.setApplicationVersion(STR(WHTBRD_VERSION));
  TIMING
  QLinkedList<QObject*> pluginList;
  {
    QCommandLineParser parser;
    parser.setApplicationDescription("Wh.t.b..rd presenting program");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("presentation","the presentation to show");
    QCommandLineOption pluginOption(QStringList() << "p" << "plugin","add a <plugin> to it","plugin");
    parser.addOption(pluginOption);

    QCommandLineOption dirOption(QStringList()<<"L"<<"directory","add a <directory> to the plugin search path","directory");
    parser.addOption(dirOption);
    TIMING
    if(!parser.parse(whtbrd_App.arguments())){
    QMessageBox msgBox;
      msgBox.setText("Wrong arguments");
      msgBox.setInformativeText(parser.errorText()+"\n\n"+parser.helpText());
    msgBox.exec();
    // std::cerr <<parser.errorText().toStdString()<<std::endl<<std::endl;
    // std::cerr <<parser.helpText().toStdString()<<std::endl;
    }
    parser.process(whtbrd_App);
    Whtbrd_Splash::init();
    TIMING
    QStringList reqPluginDirs=parser.values(dirOption);
    QStringList reqPlugins=parser.values(pluginOption);

    TIMING
    QSettings setting("Wh_t_b__rd","whtbrd");
    QVariant var;
    const char _plugins[]="plugins";
    var=setting.value(_plugins);
    if(!var.isNull()) {
      reqPlugins += var.toStringList();
    }
    if(reqPlugins.empty())
      setting.remove(_plugins);
    else {
      reqPlugins.removeDuplicates();
      setting.setValue(_plugins,reqPlugins);
    }
    const char _pluginDirs[]="pluginDirs";
    var=setting.value(_pluginDirs);
    if(!var.isNull()) {
      reqPluginDirs+=var.toStringList();
    }
    if(reqPluginDirs.empty())
      setting.remove(_pluginDirs);
    else {

      reqPluginDirs.removeDuplicates();
      setting.setValue(_pluginDirs,reqPluginDirs);
    }
    setting.sync();
    TIMING
    if(!reqPluginDirs.empty()) {
      auto paths=whtbrd_App.libraryPaths();
      for(QString path: reqPluginDirs) {
        if(!paths.contains(path)) {
          qDebug()<<"adding path "<<path;
          whtbrd_App.addLibraryPath(path);
        }
      }
    }
    qDebug()<<"loading plugins";
    QQueue<QString> pluginQueue;
    reqPlugins.swap(pluginQueue);
    int failed=0;
    while(failed++<pluginQueue.size()) {
      QString pluginName=pluginQueue.dequeue();
      qDebug()<<"loading:"<<pluginName;
      QPluginLoader loader(pluginName);
      if(!loader.load()) {
        qDebug() << pluginName <<":"<< loader.errorString();
        pluginQueue.enqueue(pluginName);
      } else {
        failed=0;
        reqPlugins += pluginName;
        qDebug()<<"success";
        QObject *plugin=loader.instance();
        if(plugin)
          pluginList.append(plugin);
      }
    }
    if(!reqPlugins.empty()) {
      setting.setValue(_plugins,reqPlugins);
    }
    if(!pluginQueue.empty()) {
      for(QString n: pluginQueue) {
        qDebug()<< "plugin" << n<< "not loaded";
      }
    }
    qDebug()<<"all loaded";
    TIMING
    for(QObject *plugin: pluginList) {
      IWhtbrdPlugin *wp=qobject_cast<IWhtbrdPlugin *>(plugin);
      if(wp) {
        wp->startup(pluginList);
        qDebug() << "interface"<< wp->objectName() << "loaded";
        TIMING
      }
    }
    TIMING
  }

  qDebug()<< "starting to run application";
  whtbrd_App.setQuitOnLastWindowClosed(true);
  whtbrd_App.exec();
  fromHere("about to exit main");
  TIMING
}
