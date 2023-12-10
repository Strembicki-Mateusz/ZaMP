#include "LibInterface.hh"
#include <iostream>

using namespace std;

LibInterface::LibInterface( const char* libName ){
	LibHandler = dlopen(libName,RTLD_LAZY);

	if (!LibHandler) {
		cerr << "!!! Brak biblioteki: " << libName << endl;
	}

	void* pFun;
	pFun = dlsym(LibHandler,"CreateCmd");
	
	if (!pFun) {
		cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
	}
	
	pCreateCmd = *reinterpret_cast<AbstractInterp4Command* (**)(void)>(&pFun);
}