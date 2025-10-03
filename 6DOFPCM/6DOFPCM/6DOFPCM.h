
// 6DOFPCM.h : main header file for the 6DOFPCM application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// C6DOFPCMApp:
// See 6DOFPCM.cpp for the implementation of this class
//

class C6DOFPCMApp : public CWinAppEx
{
public:
	C6DOFPCMApp();
	ULONG_PTR m_gdiplusToken;

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern C6DOFPCMApp theApp;
