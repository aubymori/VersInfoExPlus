///////////////////////////////////////////////////////////////////////////////////////
// Version.h  --  defines the build version '#define' strings for the product
///////////////////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////
#include "AutoBuildCount.h"     //  (where BUILDCOUNT_STR and BUILDCOUNT_NUM are defined)
//////////////////////////////////

#define  VERMAJOR_NUM    1          // MAJOR Release (program radically changed)
#define  VERMAJOR_STR   "1"

#define  VERINTER_NUM    1          // Minor Enhancements (new/modified feature, etc)
#define  VERINTER_STR   "1"

#define  VERMINOR_NUM    0          // Bug Fix
#define  VERMINOR_STR   "0"

///////////////////////////////////////////////////////////////////////////////////////
// Construct VERSION string consisting of above MAJOR/INTER/MINOR strings + BUILDCOUNT
///////////////////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
  #ifdef _DEBUG
    #define VERSION_STR_T  _T(VERMAJOR_STR) _T(".") _T(VERINTER_STR) _T(".") _T(VERMINOR_STR) _T(".") _T(BUILDCOUNT_STR) _T("-UD")
    #define VERSION_STR       VERMAJOR_STR     "."     VERINTER_STR     "."     VERMINOR_STR     "."     BUILDCOUNT_STR     "-UD"
  #else
    #define VERSION_STR_T  _T(VERMAJOR_STR) _T(".") _T(VERINTER_STR) _T(".") _T(VERMINOR_STR) _T(".") _T(BUILDCOUNT_STR) _T("-U")
    #define VERSION_STR       VERMAJOR_STR     "."     VERINTER_STR     "."     VERMINOR_STR     "."     BUILDCOUNT_STR     "-U"
  #endif
#else
  #ifdef _DEBUG
    #define VERSION_STR_T  _T(VERMAJOR_STR) _T(".") _T(VERINTER_STR) _T(".") _T(VERMINOR_STR) _T(".") _T(BUILDCOUNT_STR) _T("-D")
    #define VERSION_STR       VERMAJOR_STR     "."     VERINTER_STR     "."     VERMINOR_STR     "."     BUILDCOUNT_STR     "-D"
  #else
    #define VERSION_STR_T  _T(VERMAJOR_STR) _T(".") _T(VERINTER_STR) _T(".") _T(VERMINOR_STR) _T(".") _T(BUILDCOUNT_STR)
    #define VERSION_STR       VERMAJOR_STR     "."     VERINTER_STR     "."     VERMINOR_STR     "."     BUILDCOUNT_STR
  #endif
#endif

///////////////////////////////////////////////////////////////////////////////////////

#include "myuuids.h"                    // (custom pre-build event rule)

#define MAKE_QUOTED( xxx )              #xxx
#define REGFMT_CLSID( clsid )           _T("{") _T(MAKE_QUOTED( clsid )) _T("}")
#define VERSINFOEX_CLASS_UUID_REGFMT    REGFMT_CLSID( VERSINFOEX_CLASS_UUID )

///////////////////////////////////////////////////////////////////////////////////////
