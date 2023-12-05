#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <vector>
#include <sstream>
#include "LibInterface.hh"
#include "AbstractInterp4Command.hh"
#include "Set4LibInterfaces.hh"

using namespace std;

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

bool ExecActions(istream& rIStrm, Set4LibInterfaces &rLibs) //AbstractInterp4Command& pCmd)
{
  string CmdKey;
  LibInterface lib;
  while(rIStrm.good())
  {
    rIStrm >> CmdKey;
    if (!rLibs.GetLibInterface(CmdKey))
    {
      cout << "Nie udało się pobrać biblioteki" << endl;
    }
    if(!lib.CreateCmd()->ReadParams(rIStrm))
      return false;

    lib.CreateCmd()->PrintSyntax();
    //pCmd1->ReadParams(rIStrm);
    cout << endl;
    cout << endl;
    lib.CreateCmd()->PrintCmd();
    cout << endl;
    return true;

  }
  return 0;
}

int main(){

  std::vector<const char*> lib_names = {
    "../libs/libInterp4Move.so",
    "../libs/libInterp4Set.so",
    "../libs/libInterp4Pause.so",
    "../libs/libInterp4Rotate.so"
  };

  std::vector<const char*> cmd_names = {
    "Move",
    "Set",
    "Pause",
    "Rotate"
  };

  istringstream IStrm4Cmds;

  std::vector<LibInterface> libinterfaces(lib_names.size());

  for (int i = 0; i < lib_names.size(); i++){
    if (!libinterfaces[i].Init(lib_names[i])) return 1;
  }


Set4LibInterfaces set_4_libs;

for(int i = 0; i < lib_names.size(); i++){
  set_4_libs.AddLibInterface(cmd_names[i], std::make_shared<LibInterface>(libinterfaces[i]));
}



ExecPreprocesor("../opis_dzialan.cmd", IStrm4Cmds); 

ExecActions(IStrm4Cmds,set_4_libs);
}


