//////////////////////////////////////////////////////////////////////////////////////////
// VersInfoExShlExt.h  --  Declaration of the CVersInfoShlExt class
//////////////////////////////////////////////////////////////////////////////////////////
//
//   Copyright (C) Software Development Laboratories, aka "Fish" (David B. Trout)
//
//   Licensed under terms of the ZLIB/LIBPNG Open Source Software License
//   http://www.opensource.org/licenses/zlib-license.php
//
//   THIS SOFTWARE IS PROVIDED 'AS-IS', WITHOUT ANY EXPRESS OR IMPLIED WARRANTY.
//   IN NO EVENT WILL THE AUTHOR(S) BE HELD LIABLE FOR ANY DAMAGES ARISING FROM
//   THE USE OF THIS SOFTWARE.
//
//   Permission is granted to anyone to use this software for any purpose, including
//   commercial applications, and to alter it and redistribute it freely, subject to
//   the following restrictions:
//
//    1. The origin of this software must not be misrepresented; you must not claim
//       that you wrote the original software. If you use this software in a product,
//       an acknowledgment in the product documentation would be appreciated but is
//       not required.
//
//    2. Altered source versions must be plainly marked as such, and must not be
//       misrepresented as being the original software.
//
//    3. Neither this notice nor the above Copyright information may be removed
//       or altered from any source distribution.
//
//////////////////////////////////////////////////////////////////////////////////////////
//
//  Change History:
//
//  10/13/10    1.0.0   Fish    Created.
//
//////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "resource.h"           // (need 'MYUUIDS_RGS' resource id)
#include "CVersInfo.h"          // (our CVersInfo class contains most of our smarts)

//////////////////////////////////////////////////////////////////////////////////////////
// CVersInfoShlExt  --  Our primary Shell Extension DLL module implementation class

class ATL_NO_VTABLE CVersInfoShlExt

    : public CComObjectRootEx < CComSingleThreadModel >
    , public CComCoClass      < CVersInfoShlExt, &CLSID_VersInfoShlExt >
    , public IShellExtInit
    , public IShellPropSheetExt
{
public:

    CVersInfoShlExt()  { m_pVI = NULL; }

    BEGIN_COM_MAP( CVersInfoShlExt )

        COM_INTERFACE_ENTRY( IShellExtInit )
        COM_INTERFACE_ENTRY( IShellPropSheetExt )

    END_COM_MAP()

    STDMETHODIMP  Initialize  ( LPCITEMIDLIST, LPDATAOBJECT, HKEY );
    STDMETHODIMP  AddPages    ( LPFNADDPROPSHEETPAGE, LPARAM );
    STDMETHODIMP  ReplacePage ( UINT, LPFNADDPROPSHEETPAGE, LPARAM ) { return E_NOTIMPL; }

    DECLARE_REGISTRY_RESOURCEID( MYUUIDS_RGS )

protected:

    CVersionInfo*  m_pVI;       // ptr to parsed version information
};

//////////////////////////////////////////////////////////////////////////////////////////
