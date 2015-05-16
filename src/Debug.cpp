#include "Debug.hpp"

#ifdef DEBUG
    std::ostream& debug = std::cout;
#else
    std::ostream debug(0);
#endif // DEBUG
