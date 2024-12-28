// MainFrm.h : interface of the CMainFrame class
//


#pragma once

#include "VS2Server.h"
#include "SerialPort.h"
#include "ComPort.h"

class CMainFrame : public CFrameWnd , CVS2Server
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:
	LRESULT OnComRcv( WPARAM wParam, LPARAM wPortNr );

	bool WriteLogFile(CString logMessage);
// Attributes
public:
	CComPort m_com;

	DWORD m_SP;
	DWORD m_Client;

	CString m_IPMess;	
	CString m_ComMess;

	int m_Port;
	int m_COM;
	bool m_IsConnected;
	bool m_IsLog;

// Operations
public:
	DWORD m_listener;

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	void OnProcessIncoming(DWORD dwSP,DWORD dwClient, UCHAR* buf, int len);
	void OnAccept(DWORD dwSP,DWORD dwClient);
	void OnDisconnect(DWORD dwSP,DWORD dwClient);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()

protected:
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnUpdateStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStop(CCmdUI *pCmdUI);

public:
	afx_msg void OnFileOptions();
	afx_msg void OnTimer(UINT nIDEvent);
};


