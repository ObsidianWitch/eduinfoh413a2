#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>

#ifdef DEBUG
    extern std::ostream& logOut;
#else
    extern std::ostream logOut;
#endif // DEBUG

#endif // LOG_HPP
