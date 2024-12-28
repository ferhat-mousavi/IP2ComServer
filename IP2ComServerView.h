// IP2ComServerView.h : interface of the CIP2ComServerView class
//


#pragma once


class CIP2ComServerView : public CListView
{
protected: // create from serialization only
	CIP2ComServerView();
	DECLARE_DYNCREATE(CIP2ComServerView)

// Attributes
public:
	CIP2ComServerDoc* GetDocument() const;
	void Update();
	void InsertComMsg( CString str );
	void InsertInternalMsg( CString str );
	void InsertIPMsg( CString str );
	void DeleteAll();

	CStringArray m_msgpool;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CIP2ComServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in IP2ComServerView.cpp
inline CIP2ComServerDoc* CIP2ComServerView::GetDocument() const
   { return reinterpret_cast<CIP2ComServerDoc*>(m_pDocument); }
#endif

