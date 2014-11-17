// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

//TODO: conditional compilation for linux/windows

// this is to undo a conflict between min/max in windows and std c++
#undef max
#undef min

// STD C++ 
#include <set>
#include <map>
#include <tuple>
#include <sstream>

//BOOST
#include <boost/signals2.hpp>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/date_time/local_time/local_time.hpp>

// GNU Scientific Library
#include <gsl/gsl_fit.h>

// DACore
#include "Validate.h"
#include "Notify.h"
