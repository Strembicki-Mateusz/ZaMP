#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include <map>
#include <memory>
#include <vector>
#include <utility>

#include "LibInterface.hh"

class Set4LibInterfaces{
    private:
        std::map<std::string, std::shared_ptr<LibInterface>> _LibInterfaces;

    public:
        Set4LibInterfaces();
        bool AddLibInterface(std::string LibName, std::shared_ptr<LibInterface> LibInterface);
        std::shared_ptr<LibInterface> GetLibInterface(std::string LibName);
        std::vector<std::string> GetLibNames();

        ~Set4LibInterfaces();
};

#endif