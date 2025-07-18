//////////////////////////////////////////////////////////////////////////////////////////
// stdafx.h : include file for standard system include files,
// or project specific include files, which are used frequently
// but are otherwise changed relatively infrequently.
//////////////////////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////////////////////
// Minimum supported platform...

#define   WINVER        0x0501      // (Windows XP or greater)
#define  _WIN32_WINNT   0x0501      // (Windows XP or greater)
#define  _WIN32_IE      0x0700      // (Internet Explorer 7.0)

//////////////////////////////////////////////////////////////////////////////////////////
// System headers...

#define ISOLATION_AWARE_ENABLED     1
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>                // (std COM/ShlExt)
extern CComModule _Module;          // (std COM/ShlExt)
#include <atlcom.h>                 // (std COM/ShlExt)
#include <comdef.h>                 // (std COM/ShlExt)
#include <shlobj.h>                 // (std COM/ShlExt)

#include <atlstr.h>                 // need CString, CStringA, CStringW, etc
#include <atlcoll.h>                // need CAtlMap, CAtlList, CAtlArray, etc
#include <Winver.h>                 // need GetFileVersionInfo, etc

//////////////////////////////////////////////////////////////////////////////////////////
// Global project headers...

#include "product.h"                // (product descriptions)
#include "version.h"                // (product versions including GUID/UUID)

//////////////////////////////////////////////////////////////////////////////////////////
// The following allows us to embed const string data into our product
// object code without the compiler/linker optimizing the string out...

#define $MODULEID static LPCTSTR $MODULEID = $ModuleId( _T("$Id: ") _T(__FILE__) _T(", ") \
    _T(__TIMESTAMP__) _T(", ") _T(COPYRIGHT) _T(", ") _T(COMPANY) _T("\n") )

__inline LPCTSTR $ModuleId( LPCTSTR psz$ModuleId ) { return psz$ModuleId; }

//////////////////////////////////////////////////////////////////////////////////////////
// Debugging...

#ifdef _DEBUG
  #define  TRACE            ATLTRACE
  #define  ASSERT           ATLASSERT
  #define  VERIFY( e )      ASSERT( e )
#else
  #define  TRACE            __noop
  #define  ASSERT           __noop
  #define  VERIFY( e )      (void)(e)
#endif

//////////////////////////////////////////////////////////////////////////////////////////
