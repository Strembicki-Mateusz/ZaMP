#include "AbstractInterp4Command.hh"
#include <cassert>
#include <dlfcn.h>
#include <iostream>

using namespace std;

class LibInterface {
  void *pLibHnd_Move = nullptr;
  AbstractInterp4Command *(*pCreateCmd_Move)(void) = nullptr;

  void *pLibHnd_Set = nullptr;
  AbstractInterp4Command *(*pCreateCmd_Set)(void) = nullptr;

  void *pLibHnd_Pause = nullptr;
  AbstractInterp4Command *(*pCreateCmd_Pause)(void) = nullptr;

  void *pLibHnd_Rotate = nullptr;
  AbstractInterp4Command *(*pCreateCmd_Rotate)(void) = nullptr;

public:
  int open_library(const char *path) {
    pLibHnd_Move = dlopen(path, RTLD_LAZY);
    pLibHnd_Pause = dlopen(path, RTLD_LAZY);
    pLibHnd_Set = dlopen(path, RTLD_LAZY);
    pLibHnd_Rotate = dlopen(path, RTLD_LAZY);
    if (!pLibHnd_Move) 
    {
      cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
      return 1;
    }

    if (!pLibHnd_Set) 
    {
      cerr << "!!! Brak biblioteki: Interp4Set.so" << endl;
      return 1;
    }

    if (!pLibHnd_Pause) 
    {
      cerr << "!!! Brak biblioteki: Interp4Pause.so" << endl;
      return 1;
    }

    if (!pLibHnd_Rotate) 
    {
      cerr << "!!! Brak biblioteki: Interp4Rotate.so" << endl;
      return 1;
    }
    return 0;
  }

  
  int init() {
    void *pFun;

    pFun = dlsym(pLibHnd_Move, "CreateCmd");
    if (!pFun) {
      cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
      return 1;
    }
    pCreateCmd_Move = reinterpret_cast<AbstractInterp4Command *(*)(void)>(pFun);

    pFun = dlsym(pLibHnd_Set, "CreateCmd");
    if (!pFun) {
      cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
      return 1;
    }
    pCreateCmd_Set = reinterpret_cast<AbstractInterp4Command *(*)(void)>(pFun);

    pFun = dlsym(pLibHnd_Pause, "CreateCmd");
    if (!pFun) {
      cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
      return 1;
    }
    pCreateCmd_Pause = reinterpret_cast<AbstractInterp4Command *(*)(void)>(pFun);

    pFun = dlsym(pLibHnd_Rotate, "CreateCmd");
    if (!pFun) {
      cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
      return 1;
    }
    pCreateCmd_Rotate = reinterpret_cast<AbstractInterp4Command *(*)(void)>(pFun);
    return 0;
  }

  AbstractInterp4Command *create_cmd_intrep(){
    assert(pCreateCmd_Move);
    return pCreateCmd_Move();
  }
  ~LibInterface() { dlclose(pLibHnd_Move); dlclose(pLibHnd_Set); dlclose(pLibHnd_Pause); dlclose(pLibHnd_Rotate); }
};

int main() {
  LibInterface lib_interface;
  lib_interface.open_library("libInterp4Rotate.so");
  lib_interface.init();

  AbstractInterp4Command *pCmd = lib_interface.create_cmd_intrep();
  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  delete pCmd;
}
