#ifndef  TOOLBOX_HH
#define  TOOLBOX_HH


#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <cstdio>
#include <sstream>
#include <vector>
#include <memory>
#include <map>

#include "LibInterface.hh"

#define LINE_SIZE 1000
#define LIMIT 10000

using namespace std;

class toolbox{
public:
    map<string,shared_ptr<LibInterface>> libs;
    void printPluginInfo( AbstractInterp4Command* pCmd );
    void addLib( string name );
    void addLibs( vector<string> names );
};

#endif