#pragma once
#include <string>

#ifndef debug_HPP
#define debug_HPP
namespace debug {



    void reset();
#ifndef DEBUG
#define DEBUG 0
#define DEBUG_COLLISION 1
#endif

        void writestring(std::string string);





    
}
#endif