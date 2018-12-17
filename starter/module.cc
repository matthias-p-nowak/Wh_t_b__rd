#include <main.hh>

class TestLib {
public:
  TestLib() {
    printf("TestLib constructed\n");
  }
  ~TestLib(){
    printf("TestLib destroyed\n");
  }
};

class TestLib instance;

extern "C" {
  void init(Whtbrd_global *glob) {
    printf("hello world from module\n");
    fprintf(stderr,"verbosity: %d\n",glob->verbose);
   int x=_whtbrd_global.verbose;
    glob->doHello();
  }
}
