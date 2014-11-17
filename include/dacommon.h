#ifndef LIBDACORE_LINKAGE_H
#define LIBDACORE_LINKAGE_H

#ifdef LIBDACORE_STDCALL
  #define LIBDACORE_CALLING __stdcall
#else
  #define LIBDACORE_CALLING __cdecl
#endif

#if !defined(LIBDACORE_STATIC) && (defined(_MSC_VER) || defined(__WATCOMC__))

  #ifdef libdacore_EXPORTS
      #define DACORE_API __declspec(dllexport)
  #else
      #define DACORE_API __declspec(dllimport)
  #endif

  #define DACORE_APIENTRY LIBDACORE_CALLING

#else

  #define DACORE_API

  #if defined(__MINGW32__)
    #define DACORE_APIENTRY LIBDACORE_CALLING
  #else
    #define DACORE_APIENTRY
  #endif

#endif

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include "ISerialize.h"

#endif