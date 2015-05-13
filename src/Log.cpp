#include "Log.hpp"

#ifdef DEBUG
    std::ostream& logOut = std::cout;
#else
    std::ostream logOut(0);
#endif // DEBUG
