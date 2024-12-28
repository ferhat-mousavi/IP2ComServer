// IP2ComServer.h : main header file for the IP2ComServer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CIP2ComServerApp:
// See IP2ComServer.cpp for the implementation of this class
//

class CIP2ComServerApp : public CWinApp
{
public:
	CIP2ComServerApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CIP2ComServerApp theApp;