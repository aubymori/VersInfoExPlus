//////////////////////////////////////////////////////////////////////////////////////////
//  CVersInfo.cpp  --  Implementation of the CVersionInfo class
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

#include "stdafx.h"
#include "CVersInfo.h"

#pragma comment( lib, "Version.lib" )       // (need GetFileVersionInfoSize, etc)

$MODULEID;      // (embed module-id timestamp and copyright string into object code)

//////////////////////////////////////////////////////////////////////////////////////////
// (default constructor)

CStringTable::CStringTable( LPCWSTR pszLangW /* =NULL */ )
    : m_wLangId(0)
    , m_wCodePage(0)
{
    if (!pszLangW) return;
    m_strLangW = pszLangW;
    LPWSTR pszEndLangW = NULL; // (work)
    DWORD dwLang = wcstoul( m_strLangW, &pszEndLangW, 16 );
    m_wLangId = dwLang >> 16;
    m_wCodePage = dwLang & 0xFFFF;
}

//////////////////////////////////////////////////////////////////////////////////////////
// (copy operator)

CStringTable& CStringTable::operator = ( const CStringTable& st )
{
    m_strLangW   = st.m_strLangW;
    m_wLangId    = st.m_wLangId;
    m_wCodePage  = st.m_wCodePage;
  //m_StringsMap = st.m_StringsMap;
    CopySimpleMap< CStringW, CStringW >( m_StringsMap, st.m_StringsMap );

    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// (copy operator)

CVersionInfo& CVersionInfo::operator = ( const CVersionInfo& vi )
{
    m_strModnameW     = vi.m_strModnameW;
    m_strFileVersionW = vi.m_strFileVersionW;
    m_FFInfo          = vi.m_FFInfo;
  //m_StringTableMap  = vi.m_StringTableMap;
    CopySimpleMap< CStringW, CStringTable >( m_StringTableMap, vi.m_StringTableMap );

    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////
// (alternate constructor)

CVersionInfo::CVersionInfo( const BYTE* pVersionInfo )
{
    memset( &m_FFInfo, 0, sizeof( m_FFInfo ));      // (init class data)
    if (!pVersionInfo) { ASSERT(0); return; }       // (missing VS_VERSIONINFO data)
    Init( pVersionInfo );                           // (init remainder of class data)
}

//////////////////////////////////////////////////////////////////////////////////////////
// (default constructor)

CVersionInfo::CVersionInfo( LPCTSTR pszModname /* =NULL */ )
{
    memset( &m_FFInfo, 0, sizeof( m_FFInfo ));      // (init class data)
    if (!pszModname) return;                        // (no module given)
    m_strModnameW = pszModname;                     // (init class data)

    // Get pointer to module's VS_VERSIONINFO data...

    DWORD  dwHandle  = NULL;
    DWORD  dwSize    = GetFileVersionInfoSize( pszModname, &dwHandle );

    if (!dwSize) return;                            // (there is no version info)
    BYTE* pVersionInfo = (BYTE*) malloc( dwSize );  // (allocate temporary buffer)
    if (!pVersionInfo) return;                      // (out of memory)
    if (!GetFileVersionInfo( pszModname, dwHandle, dwSize, pVersionInfo ))
        return;                                     // (GetFileVersionInfo failed)
    ASSERT( pVersionInfo );                         // (verify GetFileVersionInfo)

    // Now use it to initialize the rest of our class...

    Init( pVersionInfo );                           // (init remainder of class data)
    free((void*)pVersionInfo);                      // (discard temporary buffer)
}

//////////////////////////////////////////////////////////////////////////////////////////
// VERSIONINFO block header layout...

// Each block always has a key, but may or may not have a value member, which
// itself could be one or more child sub-block(s), etc. All blocks start on a
// 32-bit DWORD alignment boundary, as does their value data and children sub-
// blocks as well (which may be present in addition to the value data). Neither
// the block length nor the value length fields include whatever padding there
// may be between the end of the block and the start of the next block, or the
// end of the key and the start of the value data. It is highly encouraged to
// use the associated helper functions for navigating through the data instead
// of trying to do it yourself.

#pragma warning(push)           // (save warning setting)
#pragma warning(disable:4200)   // (disable "zero-sized array in struct/union")

struct BLOCK                    // (always aligned on 32-bit (DWORD) boundary)
{
    WORD    wLength;            // Length of this block    (doesn't include padding)
    WORD    wValueLength;       // Value length            (if any)
    WORD    wType;              // Value type              (0 = binary, 1 = text)
    WCHAR   szKeyW[];           // Value name (block key)  (always NULL terminated)
  //WORD    padding1[];         // Padding, if any         (ALIGNMENT)
  //xxxxx   Value[];            // Value data, if any      (*ALIGNED*)
  //WORD    padding2[];         // Padding, if any         (ALIGNMENT)
  //xxxxx   Child[];            // Child block(s), if any  (*ALIGNED*)
};

#pragma warning(pop)            // (restore warning setting)
typedef struct BLOCK  BLOCK;    // (same name for convenience)

//////////////////////////////////////////////////////////////////////////////////////////
// Helper functions for navigating VERSIONINFO data...

inline BLOCK*  RoundUp32  ( BLOCK* p, size_t n )    { return (BLOCK*) (((ptrdiff_t) p + n + 3) & ~3); }
inline BLOCK*  AlignBlock ( BLOCK* pBlk, BLOCK* p ) { return RoundUp32( pBlk, ((BYTE*)p - (BYTE*)pBlk) ); }
inline BLOCK*  BlockValue ( BLOCK* pBlk )           { return AlignBlock( pBlk, (BLOCK*) ((BYTE*)pBlk + sizeof(BLOCK) + (( wcslen( pBlk->szKeyW ) + 1) * sizeof(WCHAR))) ); }
inline BLOCK*  EndBlock   ( BLOCK* pBlk )           { return (BLOCK*) ((BYTE*) pBlk + pBlk->wLength); } // (NOTE: must NOT be rounded)
inline BLOCK*  ChildBlock ( BLOCK* pBlk )           { return AlignBlock( pBlk, (BLOCK*) ((BYTE*) BlockValue( pBlk ) + pBlk->wValueLength) ); }
inline BLOCK*  NextBlock  ( BLOCK* pBlk )           { return AlignBlock( pBlk, EndBlock( pBlk )); }

//////////////////////////////////////////////////////////////////////////////////////////
// (constructor helper -- does all of our class initialization grunt work)

void CVersionInfo::Init( const BYTE* pVI )
{
    memset( &m_FFInfo, 0, sizeof( m_FFInfo ));  // (since we're a ctor helper)

    // Point to the VS_VERSIONINFO block passed to us (key = "VS_VERSION_INFO")

    BLOCK* pVersionInfo = (BLOCK*) pVI;
    ASSERT( CStringW(_T("VS_VERSION_INFO")).CompareNoCase( pVersionInfo->szKeyW ) == 0 );

    // The root VS_VERSIONINFO block's value data is a VS_FIXEDFILEINFO structure

    if (pVersionInfo->wValueLength)
    {
        TRACE(_T("*** CVersionInfo::Init(): VS_FIXEDFILEINFO found\n"));
        memcpy( &m_FFInfo, BlockValue( pVersionInfo ), min( sizeof( m_FFInfo ),
            pVersionInfo->wValueLength ) );
        m_strFileVersionW.Format( L"%u.%u.%u.%u"
            ,m_FFInfo.dwFileVersionMS >> 16
            ,m_FFInfo.dwFileVersionMS & 0xFFFF
            ,m_FFInfo.dwFileVersionLS >> 16
            ,m_FFInfo.dwFileVersionLS & 0xFFFF
        );
    }

    // Process all of the root block's child blocks...

    BLOCK* pBlock       = ChildBlock( pVersionInfo );
    BLOCK* pEndVersInfo = EndBlock( pVersionInfo );

    for (; pBlock < pEndVersInfo; pBlock = NextBlock( pBlock ))
    {
        if (_wcsicmp( pBlock->szKeyW, L"VarFileInfo" ) == 0)
        {
            TRACE(_T("*** CVersionInfo::Init(): SKIPPING \"VarFileInfo\" block\n"));
        }
        else if (_wcsicmp( pBlock->szKeyW, L"StringFileInfo" ) == 0)
        {
            TRACE(_T("*** CVersionInfo::Init(): Found \"StringFileInfo\" block\n"));

            // Process all StringTables...

            BLOCK* pStrTab    = (BLOCK*) ChildBlock( pBlock );
            BLOCK* pEndStrTab = EndBlock( pBlock );

            for (; pStrTab < pEndStrTab; pStrTab = NextBlock( pStrTab ))
            {
                TRACE(_T("*** CVersionInfo::Init(): Processing StringTable \"%ws\"...\n"),
                    pStrTab->szKeyW );

                CStringTable st( pStrTab->szKeyW );  // ("LLLLCCCC")

                // Process all StringTable Strings...

                BLOCK* pString     = (BLOCK*) ChildBlock( pStrTab );
                BLOCK* pEndStrings = EndBlock( pStrTab );

                for (; pString < pEndStrings; pString = NextBlock( pString ))
                {
                    CStringW strNameW  = pString->szKeyW;
                    CStringW strValueW = (LPCWSTR) BlockValue( pString );

                    TRACE(_T("*** CVersionInfo::Init(): string \"%ws\" = \"%ws\"\n"),
                        strNameW, strValueW );

                    VERIFY( st.m_StringsMap.Add( strNameW, strValueW ));
                }

                VERIFY( m_StringTableMap.Add( st.m_strLangW, st ));
            }
        }
        else
        {
            TRACE(_T("*** CVersionInfo::Init(): Skipping unrecognized block \"%ws\"\n"),
                pBlock->szKeyW );
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// (Debugging -- OutputDebugString all members...)

#ifdef _DEBUG
void Dump( const CStringTable& st )
{
    TRACE(_T("m_strLangW = \"%ws\"\n"), st.m_strLangW );
    TRACE(_T("m_wLangId = 0x%04.4X\n"), st.m_wLangId );
    TRACE(_T("m_wCodePage = 0x%04.4X\n"), st.m_wCodePage );
    TRACE(_T("m_StringsMap = {\n"));

    for (int i=0; i < st.m_StringsMap.GetSize(); i++)
        TRACE(_T("\"%ws\" = \"%ws\"\n"),
            st.m_StringsMap.GetKeyAt(i),
            st.m_StringsMap.GetValueAt(i) );

    TRACE(_T("}\n"));
}
#endif // _DEBUG

//////////////////////////////////////////////////////////////////////////////////////////
// (Debugging -- OutputDebugString all members...)

#ifdef _DEBUG
void Dump( const CVersionInfo& vi )
{
    TRACE(_T("m_strModnameW = \"%ws\"\n"), vi.m_strModnameW );
    TRACE(_T("m_strFileVersionW = \"%ws\"\n"), vi.m_strFileVersionW );
    TRACE(_T("m_FFInfo = {\n"));
    {
        DWORD* pdw = (DWORD*) &vi.m_FFInfo;
        for (size_t i = 0; i < sizeof( vi.m_FFInfo ); i += 4, pdw++)
            TRACE(_T("%08.8X\n"), *pdw );
    }
    TRACE(_T("}\n"));
    TRACE(_T("m_StringTableMap = {\n"));

    for (int i=0; i < vi.m_StringTableMap.GetSize(); i++)
    {
        TRACE(_T("\"%ws\" = {\n"), vi.m_StringTableMap.GetKeyAt(i) );
        Dump( vi.m_StringTableMap.GetValueAt(i) );
        TRACE(_T("}\n"));
    }

    TRACE(_T("}\n"));
}
#endif // _DEBUG

//////////////////////////////////////////////////////////////////////////////////////////
