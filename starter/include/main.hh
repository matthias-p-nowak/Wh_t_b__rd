#ifndef WHTBRD_INCLUDE
#define WHTBRD_INCLUDE
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <setjmp.h>
#include <unistd.h>
#include <dlfcn.h>
#include <string>
#include <memory>

// #include "whrtbrd.hh"

 
class Whtbrd_global {
public:
  int verbose=0;
};

extern "C"{
extern Whtbrd_global _whtbrd_global;
}

#endif
