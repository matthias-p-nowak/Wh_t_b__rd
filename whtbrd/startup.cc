#include <startup.hh>

char **cmdLine=NULL;
struct WHTBRG_settings whtbrg_settings;

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
    auto _dbg=qDebug();
    QDebugStateSaver _dss(_dbg);
    struct timeval *t=&usage.ru_utime;
    double spent=t->tv_sec+ 1.0*t->tv_usec/1000000;
    printf("%s:%d:time spent %f, sofar %f\n",file,line,spent-sofar,spent);
    _dbg.nospace()<<file<<":"<<line<<":time spent "<< spent-sofar<<", sofar "<<spent;
    sofar=spent;
  }
}

#define TIMING print_timing(__FILE__,__LINE__);





int main(int argc, char *argv[]) {
  TIMING
  QApplication whtbrd_App(argc, argv);
  new Whtbrd_Splash();
  TIMING
  qDebug()<<"hello in splash?";
  whtbrd_App.processEvents();
  char *argv2[argc+1];
  for(int i=0; i<argc; ++i)
    argv2[i]=argv[i];
  argv2[argc]=NULL;
  cmdLine=argv2;
  TIMING
  int opt;
  QStringList reqPluginDirs;
  QStringList reqPlugins;
  while ((opt = getopt(argc, argv, "L:p:v")) != -1) {
    switch (opt) {
    case 'L':
    {
      QString newDir(optarg);
      reqPluginDirs.append(newDir);
      break;
    }
    case 'p':
    {
      QString plugin(optarg);
      reqPlugins.append(plugin);
      break;
    }
    case 'v':
      ++whtbrg_settings.verbose;
      break;
    default:
      print_usage();
    }
  } // getopts
  TIMING
  QSettings setting("Wh_t_b__rd","whtbrd");
  //QString msg="getting "+setting.value("hello").toString();
  //showMessage(msg);
  //setting.setValue("hello","World");
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
  for(int i=0; i<10; ++i) {
    QThread::sleep(1);
    whtbrd_App.processEvents();
  }
  qDebug()<< "next";
  QThread::sleep(3);
}
