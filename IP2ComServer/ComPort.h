#pragma once


#if _MSC_VER > 1000
#endif // _MSC_VER > 1000


#define IDM_COM_RCV WM_USER + 1000


#define COMPORT_01	0
#define COMPORT_02	1
#define COMPORT_03	2
#define COMPORT_04	3
#define COMPORT_05	4
#define COMPORT_06	5
#define COMPORT_07	6


#define ZERO_MEMORY(s)  ::ZeroMemory(&s, sizeof(s))

#define MAX_RXBLOCK   2024

// flow control
#define FC_DTRDSR  0x01
#define FC_RTSCTS  0x02
#define FC_XONXOFF 0x04

#define ASCII_XON  0x11
#define ASCII_XOFF 0x13


typedef struct _TTYSTRUCT
{
   BYTE byCommPort;  // zero based port - 3 or higher implies TELNET
   BYTE byXonXoff;
   BYTE byByteSize; 
   BYTE byFlowCtrl;
   BYTE byParity; 
   BYTE byStopBits;
   DWORD dwBaudRate;

} TTYSTRUCT, *LPTTYSTRUCT;



typedef struct _CONNECTION 
{
   HANDLE hCommDev;
   BOOL bConnected;
   OVERLAPPED osWrite;
   OVERLAPPED osRead;
   DWORD dwThreadID;

} CONNECTION, *LPCONNECTION;

// Define in monitoring ComPort module
static int CALLBACK MonitorCallback(HGLOBAL hBuf, int nLen, LPARAM lParam);


typedef int CALLBACK MONITORPROC(HGLOBAL, int, LPARAM);
typedef MONITORPROC *LPMONITORPROC;


typedef struct _MONITORPROCPARMS
{
   LPCONNECTION lpConn;
   LPMONITORPROC lpCallback;
   LPARAM lpCallbackParam;

} MONITORPROCPARAMS, *LPMONITORPROCPARAMS;


class CComPort
{
public:
	CComPort(void);
    // connect to a comm port
    BOOL Connect(LPTTYSTRUCT lpTTY);
    // disconnect 
    BOOL Disconnect();

    // monitor (read) data at open connection
    BOOL Monitor(LPMONITORPROC lpMonitorProc, LPARAM lParam=NULL);
    BOOL IsConnected() const;
	BOOL CommWriteBlock(LPBYTE lpszBlock, int nLen);

protected:
    // thread entry point
    static DWORD CALLBACK CommMonitorProc(LPVOID lpThreadParameter);
    // helper function to monitor comm port
    static BOOL CALLBACK CommReadBlock(LPCONNECTION lpConn, LPBYTE lpszBlock, int nLen);

    // information about the current connection and
    // monitoring thread
    LPCONNECTION m_pConn;
    HGLOBAL m_hConn;
    LPMONITORPROCPARAMS m_pMPP;
    HGLOBAL m_hMPP;

public:
	~CComPort(void);
};

