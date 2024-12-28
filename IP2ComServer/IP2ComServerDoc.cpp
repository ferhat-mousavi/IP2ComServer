// IP2ComServerDoc.cpp : implementation of the CIP2ComServerDoc class
//

#include "stdafx.h"
#include "IP2ComServer.h"

#include "IP2ComServerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CIP2ComServerDoc

IMPLEMENT_DYNCREATE(CIP2ComServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CIP2ComServerDoc, CDocument)
	//ON_COMMAND(ID_TOOLBAR_START, OnStart)
	//ON_COMMAND(ID_TOOLBAR_STOP, OnStop)
	//ON_UPDATE_COMMAND_UI(ID_TOOLBAR_START, OnUpdateStart)
	//ON_UPDATE_COMMAND_UI(ID_TOOLBAR_STOP, OnUpdateStop)


	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CIP2ComServerDoc, CDocument)
END_DISPATCH_MAP()

// Note: we add support for IID_IIP2ComServer to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {07EC726C-7926-49C3-9D19-96280C1C69BD}
static const IID IID_IIP2ComServer =
{ 0x7EC726C, 0x7926, 0x49C3, { 0x9D, 0x19, 0x96, 0x28, 0xC, 0x1C, 0x69, 0xBD } };

BEGIN_INTERFACE_MAP(CIP2ComServerDoc, CDocument)
	INTERFACE_PART(CIP2ComServerDoc, IID_IIP2ComServer, Dispatch)
END_INTERFACE_MAP()


// CIP2ComServerDoc construction/destruction

CIP2ComServerDoc::CIP2ComServerDoc()
{
	// TODO: add one-time construction code here

	//m_listener = 0;
	//
	EnableAutomation();
	AfxOleLockApp();
}

CIP2ComServerDoc::~CIP2ComServerDoc()
{
	AfxOleUnlockApp();
}

BOOL CIP2ComServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CIP2ComServerDoc serialization

void CIP2ComServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CIP2ComServerDoc diagnostics

#ifdef _DEBUG
void CIP2ComServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIP2ComServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CIP2ComServerDoc commands

//
//void CIP2ComServerDoc::OnProcessIncoming(DWORD dwSP,DWORD dwClient, UCHAR* buf, int len)
//{
//}




//void CIP2ComServerDoc::OnStart()
//{
//
//	m_listener = __super::CreateListener(1599); // PORT NUMBER
//	if (m_listener <=0 ) {
//		AfxMessageBox("can not create listener");
//		return;
//	}
//
//	m_com.InitPort( m_ComThread );
//	if( !m_com.StartMonitoring() )
//	{
//		AfxMessageBox("can not open port");
//		OnStop();
//		return;
//	}
//
//	AfxGetMainWnd()->SetTimer(1, 500, NULL);
//}
//
//void CIP2ComServerDoc::OnStop()
//{
//	if (m_listener > 0) __super::DeleteListener(m_listener); 
//	m_listener = 0;
//	AfxGetMainWnd()->KillTimer(1);
//}
//
//void CIP2ComServerDoc::OnUpdateStart(CCmdUI *pCmdUI)
//{
//	pCmdUI->Enable(m_listener <= 0);
//}
//
//void CIP2ComServerDoc::OnUpdateStop(CCmdUI *pCmdUI)
//{
//	pCmdUI->Enable(m_listener > 0);
//}
//
//


