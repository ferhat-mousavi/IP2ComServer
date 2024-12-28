// Configurations.cpp : implementation file
//

#include "stdafx.h"
#include "IP2ComServer.h"
#include "Configurations.h"
#include ".\configurations.h"


// CConfigurations dialog

IMPLEMENT_DYNAMIC(CConfigurations, CDialog)
CConfigurations::CConfigurations(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigurations::IDD, pParent)
//	, m_IP_port(_T("1599"))
//, m_COM_Port(0)
//, m_cbx_BaudRate(9600)
//, m_cbx_DataBits(0)
, m_Cbx_StopBit(0)
, m_cbx_Parity(0)
, m_bLog(FALSE)
{
	m_IP_port=10020;
	m_COM_Port=6;
	m_cbx_BaudRate=0;
	m_cbx_DataBits=DATABIT_8;

}

CConfigurations::~CConfigurations()
{
}

void CConfigurations::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_IP_port);
	//	DDV_MaxChars(pDX, m_IP_port, 1000000);
	DDX_CBIndex(pDX, IDC_COMBO1, m_COM_Port);
	DDX_CBIndex(pDX, IDC_COMBO2, m_cbx_BaudRate);
	DDX_CBIndex(pDX, IDC_COMBO3, m_cbx_DataBits);
	DDX_CBIndex(pDX, IDC_COMBO5, m_Cbx_StopBit);
	DDX_CBIndex(pDX, IDC_COMBO4, m_cbx_Parity);
	DDX_Check(pDX, IDC_CHECK1, m_bLog);
}


BEGIN_MESSAGE_MAP(CConfigurations, CDialog)
	ON_COMMAND(ID_FILE_OPTIONS, OnFileOptions)
	ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
END_MESSAGE_MAP()


// CConfigurations message handlers

void CConfigurations::OnFileOptions()
{
	// TODO: Add your command handler code here
}

BOOL CConfigurations::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigurations::OnBnClickedCheck1()
{
	m_bLog=!m_bLog;

}
