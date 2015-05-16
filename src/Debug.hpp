#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>

#ifdef DEBUG
    extern std::ostream& debug;
#else
    extern std::ostream debug;
#endif // DEBUG

#endif // DEBUG_HPP
