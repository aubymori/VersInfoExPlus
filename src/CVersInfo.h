//////////////////////////////////////////////////////////////////////////////////////////
//  CVersInfo.h  --  Declaration of the CVersionInfo class
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

//////////////////////////////////////////////////////////////////////////////////////////
// (a "helper" class used by main CVersionInfo class)

class CStringTable
{
public:

    CStringTable( LPCWSTR pszLangW = NULL );                    // (default ctor)
    CStringTable( const CStringTable* pST ) { *this = *pST; }   // (copy ctor)
    CStringTable( const CStringTable&  st ) { *this =   st; }   // (copy ctor)
    CStringTable& operator = ( const CStringTable&      st );   // (copy operator)

public:

    typedef   CSimpleMap< CStringW, CStringW >      CStringsMap;

    CStringW            m_strLangW;                 // Language string ("LLLLCCCC")
    WORD                m_wLangId;                  // LangId
    WORD                m_wCodePage;                // Code page
    CStringsMap         m_StringsMap;               // Strings map (key=name)
};

//////////////////////////////////////////////////////////////////////////////////////////
// The main/root/primary "Version Information" class...

class CVersionInfo
{
public:

    CVersionInfo( LPCTSTR pszModname = NULL );                  // (default ctor)
    CVersionInfo( const BYTE* pVersionInfo );                   // (alternate ctor)
    CVersionInfo( const CVersionInfo* pVI ) { *this = *pVI; }   // (copy ctor)
    CVersionInfo( const CVersionInfo&  vi ) { *this =   vi; }   // (copy ctor)
    CVersionInfo& operator = ( const CVersionInfo&      vi );   // (copy operator)

public:

    typedef  CSimpleMap< CStringW, CStringTable >   CStringTableMap;

    CStringW            m_strModnameW;              // Module name
    CStringW            m_strFileVersionW;          // (from m_FFInfo)
    VS_FIXEDFILEINFO    m_FFInfo;                   // FixedFileInfo
    CStringTableMap     m_StringTableMap;           // StringTable map (key=language)

private:

    void Init( const BYTE* pVersionInfo );          // (constructor helper)
};

//////////////////////////////////////////////////////////////////////////////////////////
// (copy constructor/copy operator helper -- why doesn't ATL support copying maps?!)

template < typename KEY, typename VAL >
void CopySimpleMap( CSimpleMap< KEY, VAL >& dst, const CSimpleMap< KEY, VAL >& src )
{
    dst.RemoveAll();
    for (int i=0; i < src.GetSize(); i++)
        VERIFY( dst.Add( src.GetKeyAt(i), src.GetValueAt(i) ));
}

//////////////////////////////////////////////////////////////////////////////////////////
// (debugging)

#ifdef _DEBUG
extern void Dump( const CStringTable& st );     // (OutputDebugString all members)
extern void Dump( const CVersionInfo& vi );     // (OutputDebugString all members)
#endif // _DEBUG

//////////////////////////////////////////////////////////////////////////////////////////
