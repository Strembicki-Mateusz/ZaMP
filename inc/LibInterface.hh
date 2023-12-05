#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH

#include <dlfcn.h>
#include <cassert>

#include "AbstractInterp4Command.hh"


class LibInterface {

  public:
  void *_pLibHnd = nullptr;
  AbstractInterp4Command *(*_pCreateCmd )(void) = nullptr;
  bool Init(const char *sFileName);
  AbstractInterp4Command *CreateCmd();

 ~LibInterface();

};

#endif