#include <base.hh>

extern "C" {
  int WHTBRD_init(struct WHTBRG_settings *settings);
  void WHTBRD_startup();
}

int WHTBRD_init(struct WHTBRG_settings *_settings){
  fromHere("hello");
}

void WHTBRD_startup(){
  fromHere("startup called");
}
