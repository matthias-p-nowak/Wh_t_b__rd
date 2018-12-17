#include <startup.hh>
using namespace std;

struct WHTBRG_settings whtbrg_settings;


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

int main(int argc, char *argv[]) {
  void(*startupFunction)();
  startupFunction=NULL;
  {
    fromHere("getting options and settings");
    // a new scope for the variables used for starting up
    unordered_set<string> plugDirs;
    unordered_set<string> plugins;
    int opt;
    string startFile;
    char *env_HOME=getenv("HOME");
    if(env_HOME)
      startFile=env_HOME;
    else
      startFile="";
    startFile += "/.config";
    if(mkdir(startFile.c_str(),0755)) {
      if(errno!=EEXIST) {
        perror("could not create ~/.config directory");
        exit(EXIT_FAILURE);
      }
    }
    startFile += "/whtbrd";
    if(mkdir(startFile.c_str(),0755)) {
      if(errno!=EEXIST) {
        perror("could not create config file directory");
        exit(EXIT_FAILURE);
      }
    }
    startFile += "/start";
    while ((opt = getopt(argc, argv, "c:L:p:v")) != -1) {
      switch (opt) {
      case 'c':
        startFile=optarg;
        break;
      case 'L':
      {
        string newDir(optarg);
        plugDirs.insert(newDir);
        break;
      }
      case 'p':
      {
        string plugin(optarg);
        plugins.insert(plugin);
        break;
      }
      case 'v':
        ++whtbrg_settings.verbose;
        break;
      default:
        print_usage();
      }
    } // getopts
    unordered_set<string> readPlugDirs;
    unordered_set<string> readPlugins;
    ifstream readSettings(startFile);
    if(readSettings.is_open())
      while(!readSettings.eof()) {
        string line;
        getline(readSettings,line);
        string key=line.substr(0,2);
        if(key=="L+") {
          string dir=line.substr(2);
          readPlugDirs.insert(dir);
          plugDirs.erase(dir);
        } else if(key=="p+") {
          string plug=line.substr(2);
          readPlugins.insert(plug);
          plugins.erase(plug);
        }
      }
    readSettings.close();
    if(!plugDirs.empty() || !plugins.empty()) {
      ofstream wrStartFile(startFile,ofstream::app);
      for(string pd : plugDirs)
        wrStartFile << "L+" << pd << endl;
      for(string pl : plugins)
        wrStartFile << "p+" << pl << endl;
    }
    plugDirs.insert(readPlugDirs.begin(),readPlugDirs.end());
    plugins.insert(readPlugins.begin(),readPlugins.end());
    const char envLdName[]="LD_LIBRARY_PATH";
    char *env_LD_paths=getenv(envLdName);
    // char *env_LD_paths=getenv("MANPATH");
    printf("got %s as LD_LIBRARY_PATH\n",env_LD_paths);
    if(env_LD_paths) {
      char *entry;
      while((entry=strtok(env_LD_paths,":"))) {
        env_LD_paths=NULL;
        plugDirs.erase(entry);
      }
    }
    if(!plugDirs.empty()) {
      // restart required
      string new_ld_path;
      for(string pd : plugDirs)
        new_ld_path += ":"+pd;
      new_ld_path.erase(0,1);
      if(env_LD_paths)
        new_ld_path+= ":"+string(env_LD_paths);
      setenv(envLdName,new_ld_path.c_str(),1);
      if(setenv("WHTBRD_RESTARTED","already",0)) {
        fprintf(stderr,"restart didn't fixed LD_LIBRARY_PATH -> %s",env_LD_paths);
        exit(EXIT_FAILURE);
      }
      char *argv2[argc+1];
      for(int i=0; i<argc; ++i)
        argv2[i]=argv[i];
      argv2[argc]=NULL;
      execvp(argv[0],argv2);
      fprintf(stderr,"missed execvp 2018-12-07/1\n");
      exit(EXIT_FAILURE);
    } else {
      // no further plugins directories to add
    }
    for(string p: plugins){
      dlerror();
      if(whtbrg_settings.verbose>1)
        printf("loading %s\n",p.c_str());
      void *pluginLib=dlopen(p.c_str(), RTLD_LAZY);
      if(pluginLib==NULL){
        dlerror();
        string p2="lib"+p+".so";
        pluginLib=dlopen(p2.c_str(), RTLD_LAZY);        
      }
      if(pluginLib==NULL){
        fprintf(stderr,"couldn't open pluginLib %s due to %s\n",p.c_str(),dlerror());
        continue;
      }
      WHTBRD_init_fct init;
      init=(WHTBRD_init_fct)dlsym(pluginLib,"WHTBRD_init");
      if(init)
        init(&whtbrg_settings);
      if(!startupFunction){
        startupFunction=(void (*)()) dlsym(pluginLib,"WHTBRD_startup");
      }
    }
  }
  fromHere("settings read");
  //
  if(startupFunction){
    if(whtbrg_settings.verbose>1)
      printf("calling the found WHTBRD_startup function\n");
    startupFunction();
  }
  fromHere("all done");
  return 0;
}
