#ifndef INCLUDED201812172
#define INCLUDED201812172

#define fromHere(msg) printf("%s:%d: %s\n",__FILE__,__LINE__,msg)



struct WHTBRG_settings{
  int verbose=0;
};

// int WHTBRD_init(struct WHTBRG_settings *settings);
typedef int (*WHTBRD_init_fct)(struct WHTBRG_settings *settings);
// void WHTBRD_startup();
typedef int (*WHTBRD_startup_fct)();

extern struct WHTBRG_settings whtbrg_settings;
#endif