#include "Set4LibInterfaces.hh"

Set4LibInterfaces::Set4LibInterfaces(){

}

Set4LibInterfaces::~Set4LibInterfaces(){

}

bool Set4LibInterfaces::AddLibInterface(std::string LibName, std::shared_ptr<LibInterface> LibInterface){


    if(!this->_LibInterfaces.insert({LibName, LibInterface}).second){
        std::cerr << "Isnieje: " << LibName << std::endl;
        return false;
    }
    return true;


}

std::shared_ptr<LibInterface> Set4LibInterfaces::GetLibInterface(std::string LibName){

    return this->_LibInterfaces.at(LibName);
}


std::vector<std::string> Set4LibInterfaces::GetLibNames(){
    
        std::vector<std::string> LibNames;

        for(auto it = this->_LibInterfaces.begin(); it != this->_LibInterfaces.end(); ++it){
            LibNames.push_back(it->first);
        }
        return LibNames;
}
