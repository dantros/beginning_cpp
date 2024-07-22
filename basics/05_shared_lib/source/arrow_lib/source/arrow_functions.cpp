#include <iostream>
#include "arrow_functions.h"

std::ostream& operator<<(std::ostream& os, const Arrow& arrow)
{
    return os<< "[" << arrow.source() << " -> " << arrow.target() << " ]";
}