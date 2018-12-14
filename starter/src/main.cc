/**
 * @author Matthias P. Nowak
 * @date 2018-12-13
 */
#include <main.hh>

Whtbrd_global _whtbrd_global;

// ***********************************************
/*
 * we catch an exit call and return to our main function
 */
jmp_buf _longjmpBuffer;

void my_atexit(int status, void *arg) {
  if(status==0)
    return;
  static int count=0;
  fprintf(stderr,"atexit function status %d\n",status);
  if(++count<2)
    longjmp(_longjmpBuffer,status);
}

// ***********************************************


void bigStuff() {
  // TODO read a config file, probably from config (getenv) or argument
  // rename files if there are newer once
  // TODO load libraries via dlopen
  // start the splash screen
  dlerror();
  // void *lib=dlopen("/home/me/projects/whtbrd/build/starter/libtestLib.so", RTLD_LAZY);
  void *lib=dlopen("libtestLib.so", RTLD_NOW|RTLD_GLOBAL);
  if(lib==NULL){
    fprintf(stderr,"it failed: %s\n",dlerror());
    return;
  }
  void (*init)(Whtbrd_global *glob); // a pointer to a function
  dlerror();
  init=(void (*)(Whtbrd_global *glob))dlsym(lib,"init");
  if(init==NULL){
    fprintf(stderr,"no init found: %s\n",dlerror());
    return;
  }
  init(&_whtbrd_global);
}

void print_usage(char *progname) {
  /**
   * @brief prints out the usage for the program
   */
  printf("Wh.t.b..rd program for simple explanations\n\n"
  "%s [-v] [<presentation>]\n"
  "	-v    increase verbosity\n"
  "	      \n"
  ,progname);
  exit(EXIT_SUCCESS);
}


// ***********************************************
// entry point and also handling a premature exit
int main(int argc, char *argv[]) {
  {
    int opt;
    while ((opt = getopt(argc, argv, "v")) != -1) {
      switch (opt) {
      case 'v':
        ++_whtbrd_global.verbose;
        break;
      default:
        print_usage(argv[0]);
      }
    }
  }
  if(_whtbrd_global.verbose>0)
    printf("hello world\n");
  int exitReason;
  if(0==(exitReason=setjmp(_longjmpBuffer))) {
    if(on_exit(my_atexit,NULL)) {
      perror("on_exit");
    };
    // doing the big stuff
    if(_whtbrd_global.verbose>5)
      printf("doing big stuff\n");
    bigStuff();
  }
  else {
    if(_whtbrd_global.verbose>0)
      fprintf(stderr,"someone called exit(%d) , exiting gracefully\n",exitReason);
  }
  if(_whtbrd_global.verbose>0)
    printf("all done\n");
  return 0;
}


