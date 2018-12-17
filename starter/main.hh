#ifndef INCLUDED201812176
#define INCLUDED201812176

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <setjmp.h>
#include <unistd.h>
#include <dlfcn.h>
#include <string>
#include <memory>

// #include "whrtbrd.hh"

extern "C" {
 
class Whtbrd_global {
public:
  int verbose=0;
  void doHello();
};


extern Whtbrd_global _whtbrd_global;
}
#endif
