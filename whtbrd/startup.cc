#include <startup.hh>

// char **cmdLine=NULL;
// struct WHTBRG_settings whtbrg_settings;

using namespace std;

void print_usage() {
  /// @brief usages of the program
  printf("Wh.t.b..rd - the simple program to present simple explanations\n"
         "use: whtbrd [-v] [-c configuration] [-L <plugin path>] [-p <plugin>] [<presentation>]\n"
         "	-v                increase verbosity\n"
         "	-L <plugin path>  add the <plugin path> to the list of directories for plugins\n"
         "	-p <plugin>       add the <plugin> to the list of plugins to load\n"

         "\n");
  exit(EXIT_SUCCESS);
}

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





int main(int argc, char *argv[]) {
  TIMING
  QApplication whtbrd_App(argc, argv);
  TIMING
  Whtbrd_Splash::init();
  TIMING
  {
    int opt;
    QStringList reqPluginDirs;
    QStringList reqPlugins;
    while ((opt = getopt(argc, argv, "L:p:v")) != -1) {
      switch (opt) {
      case 'L':
      {
        QString newDir(optarg);
        QFileInfo fi(newDir);
        fi.makeAbsolute();
        reqPluginDirs.append(fi.filePath());
        break;
      }
      case 'p':
      {
        QString plugin(optarg);
        reqPlugins.append(plugin);
        break;
      }
      case 'v': {
        int v=qDebug().verbosity()+1;
        qDebug().setVerbosity(v);
        break;
      }
      default:
        print_usage();
      }
    } // getopts
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
        IWhtbrdPlugin *wp=qobject_cast<IWhtbrdPlugin *>(plugin);
        if(wp) {
          qDebug() << "interface" << wp->name() << "loaded";
          wp->startup();
          TIMING
        }
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
    TIMING
  }

  qDebug()<< "starting to run application";
  whtbrd_App.setQuitOnLastWindowClosed(true);
  whtbrd_App.exec();
  fromHere("about to exit main");
  TIMING
}
