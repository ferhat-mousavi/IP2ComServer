// IP2ComServerView.cpp : implementation of the CIP2ComServerView class
//

#include "stdafx.h"
#include "IP2ComServer.h"

#include "IP2ComServerDoc.h"
#include "IP2ComServerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIP2ComServerView

IMPLEMENT_DYNCREATE(CIP2ComServerView, CListView)

BEGIN_MESSAGE_MAP(CIP2ComServerView, CListView)
END_MESSAGE_MAP()

// CIP2ComServerView construction/destruction

CIP2ComServerView::CIP2ComServerView()
{
	EnableActiveAccessibility();
	// TODO: add construction code here

}

CIP2ComServerView::~CIP2ComServerView()
{
}

BOOL CIP2ComServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style |= LVS_REPORT;
	

	return CListView::PreCreateWindow(cs);
}

void CIP2ComServerView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CListCtrl& rList = GetListCtrl();

	rList.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES  );
    rList.InsertColumn(0, "Date / Time", LVCFMT_LEFT, 200);
    rList.InsertColumn(1, "Message", LVCFMT_LEFT, 800);
}


// CIP2ComServerView diagnostics

#ifdef _DEBUG
void CIP2ComServerView::AssertValid() const
{
	CListView::AssertValid();
}

void CIP2ComServerView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CIP2ComServerDoc* CIP2ComServerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIP2ComServerDoc)));
	return (CIP2ComServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CIP2ComServerView message handlers


void CIP2ComServerView::Update()
{
	//CpossrvDoc* pDoc = GetDocument();

	//if (pDoc->m_msgpool.GetCount() < 2) return;
	//CString in = pDoc->m_msgpool.GetAt(0);
	//pDoc->m_msgpool.RemoveAt(0);
	//CString out = pDoc->m_msgpool.GetAt(0);
	//pDoc->m_msgpool.RemoveAt(0);
	//AddTx(in,out);
}


void CIP2ComServerView::InsertComMsg( CString str )
{
	CListCtrl& rList = GetListCtrl();

	CTime t = CTime::GetCurrentTime();

	CString currDateTime = t.Format( "%A, %B %d, %Y, %H:%M:%S" );


	rList.InsertItem(0, currDateTime);
	
	

	rList.SetItemText(0, 1, "FROM COM.: "+str);

}

void CIP2ComServerView::InsertInternalMsg( CString str )
{
	CListCtrl& rList = GetListCtrl();
	CTime t = CTime::GetCurrentTime();
	CString currDateTime = t.Format( "%A, %B %d, %Y, %H:%M:%S" );

	rList.InsertItem(0, currDateTime);

	rList.SetItemText(0, 1, "INTERNAL.: "+str);

}


void CIP2ComServerView::InsertIPMsg( CString str )
{
	CListCtrl& rList = GetListCtrl();
	CTime t = CTime::GetCurrentTime();
	CString currDateTime = t.Format( "%A, %B %d, %Y, %H:%M:%S" );

	rList.InsertItem(0,currDateTime);

	rList.SetItemText(0, 1,  "FROM IP..: "+str);

}