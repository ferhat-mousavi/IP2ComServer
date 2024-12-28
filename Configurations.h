#pragma once

#define DATABIT_8	3
#define DATABIT_7	2
#define DATABIT_6	1
#define DATABIT_5	0

// CConfigurations dialog

class CConfigurations : public CDialog
{
	DECLARE_DYNAMIC(CConfigurations)

public:
	CConfigurations(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConfigurations();

// Dialog Data
	enum { IDD = IDD_CONFIGURATIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOptions();
	unsigned long m_IP_port;
	int m_COM_Port;
	virtual BOOL OnInitDialog();
	int m_cbx_BaudRate;
	int m_cbx_DataBits;
	int m_Cbx_StopBit;
	int m_cbx_Parity;
	BOOL m_bLog;
	afx_msg void OnBnClickedCheck1();
	//afx_msg void OnBnClickedOk();
};

