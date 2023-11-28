#include "AbstractInterp4Command.hh"
#include <cassert>
#include <dlfcn.h>
#include <iostream>
#include <sstream>


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
      cerr << "!!! Brak biblioteki!" << endl;
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

  AbstractInterp4Command *create_cmd_intrep_Move(){
    assert(pCreateCmd_Move);
    return pCreateCmd_Move();
  }
  AbstractInterp4Command *create_cmd_intrep_Set(){
    assert(pCreateCmd_Set);
    return pCreateCmd_Set();
  }
  AbstractInterp4Command *create_cmd_intrep_Rotate(){
    assert(pCreateCmd_Rotate);
    return pCreateCmd_Rotate();
  }
  AbstractInterp4Command *create_cmd_intrep_Pause(){
    assert(pCreateCmd_Pause);
    return pCreateCmd_Pause();
  }
  ~LibInterface() { dlclose(pLibHnd_Move); dlclose(pLibHnd_Set); dlclose(pLibHnd_Pause); dlclose(pLibHnd_Rotate); }
};



#define LINE_SIZE 500

bool ExecPreprocesor( const char* NazwaPliku, istringstream& IStrm4Cmds )
{
  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;

  Cmd4Preproc += NazwaPliku;
  FILE* pProc = popen(Cmd4Preproc.c_str(),"r");
  if (!pProc) return false;
  while (fgets(Line,LINE_SIZE,pProc)) {
    OTmpStrm << Line;
  }
  IStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc) == 0;
}

bool ExecActions(istream& rIStrm, LibInterface& lib_interface1, LibInterface& lib_interface2, LibInterface& lib_interface3, LibInterface& lib_interface4) //AbstractInterp4Command& pCmd)
{
  string CmdKey;
  
  AbstractInterp4Command *pCmd1 = lib_interface1.create_cmd_intrep_Move();
  AbstractInterp4Command *pCmd2 = lib_interface2.create_cmd_intrep_Rotate();
  AbstractInterp4Command *pCmd3 = lib_interface3.create_cmd_intrep_Set();
  AbstractInterp4Command *pCmd4 = lib_interface4.create_cmd_intrep_Pause();

  while(rIStrm.good())
  {
  rIStrm >> CmdKey;
  if(CmdKey == "Move")
  {
    if(!pCmd1->ReadParams(rIStrm))
      return false;

    pCmd1->PrintSyntax();
    //pCmd1->ReadParams(rIStrm);
    cout << endl;
    cout << endl;
    pCmd1->PrintCmd();
    cout << endl;

  }
  else if(CmdKey == "Pause")
  {
    if(!pCmd4->ReadParams(rIStrm))
      return false;

    pCmd4->PrintSyntax();
    //pCmd2->ReadParams(rIStrm);
    cout << endl;
    cout << endl;
    pCmd4->PrintCmd();
    cout << endl;

  }
  else if(CmdKey == "Set")
  {
    if(!pCmd3->ReadParams(rIStrm))
      return false;
    
    pCmd3->PrintSyntax();
    //pCmd3->ReadParams(rIStrm);
    cout << endl;
    cout << endl;
    pCmd3->PrintCmd();
    cout << endl;

  }
  else if(CmdKey == "Rotate")
  {
    if(!pCmd2->ReadParams(rIStrm))
      return false;

    pCmd2->PrintSyntax();
    //pCmd4->ReadParams(rIStrm);
    cout << endl;
    cout << endl;
    pCmd2->PrintCmd();
    cout << endl;

  }
  else {cout << "brak takiego polecenia" << endl;}
  }
  return true;
}



int main(int argc, char** argv) 
{

  istringstream IStrm4Cmds;

  if(!ExecPreprocesor("./opis_dzialan.cmd" ,IStrm4Cmds ))
  {
    cout << "Nie można wykonać" << endl;
    return 2;
  }

  LibInterface lib_interface1;
  LibInterface lib_interface2;
  LibInterface lib_interface3;
  LibInterface lib_interface4;
  lib_interface1.open_library("libs/libInterp4Move.so");
  lib_interface2.open_library("libs/libInterp4Rotate.so");
  lib_interface3.open_library("libs/libInterp4Set.so");
  lib_interface4.open_library("libs/libInterp4Pause.so");
  lib_interface1.init();
  lib_interface2.init();
  lib_interface3.init();
  lib_interface4.init();
  
  
  ExecActions(IStrm4Cmds, lib_interface1, lib_interface2, lib_interface3, lib_interface4);
  //cout << IStrm4Cmds.str() << endl;
  
  
  
  
  
  
  
  
  
  
  
  
  
  
}
