#ifndef ETL_HPP
#define ETL_HPP

#include <stdexcept>
#include <iostream>
#include <cmath>

/*
*  Copyright (c) 2026 CortexR7
*
*  This header defines the ETL (Engine Template Library)
*  This header can be included and will reimplemnent some usefull container from the STL
*  for better control.
*
*/

#include "impl/DEBUG_LOG.hpp"

namespace ETL
{
    #include "impl/DynamicArray.hpp"
    #include "impl/StaticArray.hpp"
};

#endif