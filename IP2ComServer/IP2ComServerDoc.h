// IP2ComServerDoc.h : interface of the CIP2ComServerDoc class
//


#pragma once

//#include "VS2Server.h"


class CIP2ComServerDoc : public CDocument// , CVS2Server
{
protected: // create from serialization only
	CIP2ComServerDoc();
	DECLARE_DYNCREATE(CIP2ComServerDoc)

// Attributes
public:
	//DWORD m_listener;
	//CStringArray m_msgpool;

// Operations
public:
	
// Overrides
public:
//	void OnProcessIncoming(DWORD dwSP,DWORD dwClient, UCHAR* buf, int len);
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CIP2ComServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//afx_msg void OnStart();
	//afx_msg void OnStop();
	//afx_msg void OnUpdateStart(CCmdUI *pCmdUI);
	//afx_msg void OnUpdateStop(CCmdUI *pCmdUI);


// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


