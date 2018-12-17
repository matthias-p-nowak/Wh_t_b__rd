#include <plug1.hh>



extern "C" {
  int WHTBRD_init(struct WHTBRG_settings *settings);
}

int WHTBRD_init(struct WHTBRG_settings *_settings){
  fromHere("init called");
}
