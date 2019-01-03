#include <startup.hh>

/**
 * Wh.t.b..rd is a modularized program. The main function reads settings,
 * loads modules and then runs the message queue.
 * In addition a splash screen is displayed for debug messages
 */

using namespace std;

/**
 * a general purpose function that can be used for primitive profiling
 */
void print_timing(const char *file, int line) {
  static double spent=0; // remember from last call
  struct rusage usage;
  if(getrusage(RUSAGE_SELF, &usage)) {
    perror("rusage");
  }
  else {
    // for simple access
    struct timeval *t=&usage.ru_utime;
    double recent=-spent; // second half of recent=spent(last time) - spent(newest)
    spent=t->tv_sec+ t->tv_usec/1000000.0;
    recent+=spent; // first half of difference
    printf("%s:%d:time recent %f, spent %f\n",file,line,recent,spent);
  }
}

#define TIMING print_timing(__FILE__,__LINE__);

/**
 * The version is defined on the command line for CC compiler, might be
 * translated as a number, but we need a string argument. This macro stringify
 * does the job with "#x"
 */
#define STR(x) #x

/**
 * Main program
 */
int main(int argc, char *argv[]) {
  TIMING // measuring all dynamic linking including initializations
  // Splash already demands a QApplication and we need Qt's plugin loading
  // mechanism, hence going below QApplication doesn't make much sense.
  QApplication whtbrd_App(argc, argv);
  whtbrd_App.setOrganizationName("Wh_t_b__rd");
  whtbrd_App.setApplicationName("whtbrd");
  whtbrd_App.setApplicationVersion(STR(WHTBRD_VERSION));
  TIMING // for measuring QApplications initialization time
  Whtbrd_Splash::init(); // showing splash screen
  // the linked list is compiled and need to live until the end
  QLinkedList<QObject*> pluginList;
  {
    // a block for variables that should no longer exist when the
    // message pump starts
    QCommandLineParser parser;
    parser.setApplicationDescription("Wh.t.b..rd presenting program");
    parser.addHelpOption(); // aka -h
    parser.addVersionOption(); // aka -v
    parser.addPositionalArgument("presentation","the presentation to show");
    // -p
    QCommandLineOption pluginOption(QStringList() << "p" << "plugin","add a <plugin> to it","plugin");
    parser.addOption(pluginOption);
    // -L
    QCommandLineOption dirOption(QStringList()<<"L"<<"directory","add a <directory> to the plugin search path","directory");
    parser.addOption(dirOption);
    //
    // 2 stage processing - first one for showing in QMessageBox (Windows)
    if(!parser.parse(whtbrd_App.arguments())) {
      // some error
      QMessageBox msgBox;
      msgBox.setText("Wrong arguments");
      msgBox.setInformativeText(parser.errorText()+"\n\n"+parser.helpText());
      msgBox.exec();
    }
    // this call does the right thing for "-h" and "-v"
    parser.process(whtbrd_App); // includes an exit in case of errors
    // 
    TIMING
    QStringList reqPluginDirs=parser.values(dirOption);
    QStringList reqPlugins=parser.values(pluginOption);
    QSettings setting;
    QVariant val; 
    // which plugins to load
    const char _plugins[]="plugins";
    val=setting.value(_plugins);
    if(!val.isNull()) {
      reqPlugins += val.toStringList();
    }
    // storing updated plugin list
    if(reqPlugins.empty())
      setting.remove(_plugins);
    else {
      reqPlugins.removeDuplicates();
      setting.setValue(_plugins,reqPlugins);
    }
    // which directories are relevant
    const char _pluginDirs[]="pluginDirs";
    val=setting.value(_pluginDirs);
    if(!val.isNull()) {
      reqPluginDirs+=val.toStringList();
    }
    // storing updated list
    if(reqPluginDirs.empty())
      setting.remove(_pluginDirs);
    else {

      reqPluginDirs.removeDuplicates();
      setting.setValue(_pluginDirs,reqPluginDirs);
    }
    setting.sync(); // we are not yet in the event loop, hence saving manually
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
    // now loading all plugins or at least try
    qDebug()<<"loading plugins";
    // Plugins might be dependend on other plugins and will fail when tried 
    // too early. The are appended to the queue for another trial.
    QQueue<QString> pluginQueue;
    // queue gets the plugins to try, reqPlugins has the successful ones
    reqPlugins.swap(pluginQueue);
    int failed=0; // the counter for consecutive failures
    // failed == pluginQueue.size() is true when all elements have been tried
    while(failed++<pluginQueue.size()) {
      // get one name
      QString pluginName=pluginQueue.dequeue();
      qDebug()<<"loading:"<<pluginName;
      QPluginLoader loader(pluginName);
      if(!loader.load()) {
        // not this time
        qDebug() << pluginName <<":"<< loader.errorString();
        pluginQueue.enqueue(pluginName); // for another trial
      } else {
        // good
        failed=0; // reseting stop condition
        reqPlugins += pluginName; // good one at this time
        qDebug()<<"success";
        QObject *plugin=loader.instance();
        if(plugin)
          pluginList.append(plugin);
      }
    }
    if(!reqPlugins.empty()) {
      // update the list with the good ones
      setting.setValue(_plugins,reqPlugins);
    }
    qDebug()<<"plugins loaded, starting them";
    TIMING
    for(QObject *plugin: pluginList) {
      // try to get an Wh.t.b..rd plugin from the list
      IWhtbrdPlugin *wp=qobject_cast<IWhtbrdPlugin *>(plugin);
      if(wp) {
        wp->startup();
        qDebug() << "interface"<< wp->objectName() << "loaded";
      }
    }
    TIMING
  }
  qDebug()<< "starting to run application";
  whtbrd_App.exec();
  // last window got closed
  fromHere("about to exit main");
  TIMING
}
