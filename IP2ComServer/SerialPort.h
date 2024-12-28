#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__

#define WM_COMM_BREAK_DETECTED		WM_USER+1	// A break was detected on input.
#define WM_COMM_CTS_DETECTED		WM_USER+2	// The CTS (clear-to-send) signal changed state. 
#define WM_COMM_DSR_DETECTED		WM_USER+3	// The DSR (data-set-ready) signal changed state. 
#define WM_COMM_ERR_DETECTED		WM_USER+4	// A line-status error occurred. Line-status errors are CE_FRAME, CE_OVERRUN, and CE_RXPARITY. 
#define WM_COMM_RING_DETECTED		WM_USER+5	// A ring indicator was detected. 
#define WM_COMM_RLSD_DETECTED		WM_USER+6	// The RLSD (receive-line-signal-detect) signal changed state. 
#define WM_COMM_RXCHAR				WM_USER+7	// A character was received and placed in the input buffer. 
#define WM_COMM_RXFLAG_DETECTED		WM_USER+8	// The event character was received and placed in the input buffer.  
#define WM_COMM_TXEMPTY_DETECTED	WM_USER+9	// The last character in the output buffer was sent.  

#define STX 2
#define ETX 3
#define EOT 4
#define ENQ 5
#define ACK 6
#define DLE 16
#define SLE DLE
#define NAK 21

class CSerialPort
{														 
public:
	// contruction and destruction
	CSerialPort();
	virtual		~CSerialPort();

	// port initialisation											
	BOOL		InitPort(DWORD OwnerThread,
						UINT portnr = 1,
						UINT baud = 19200,
						char parity = 'N',
						UINT databits = 8,
						UINT stopsbits = 1,
						DWORD dwCommEvents = EV_RXCHAR | EV_CTS,
						UINT nBufferSize = 512);

	// start/stop comm watching
	BOOL		StartMonitoring();
	BOOL		RestartMonitoring();
	BOOL		StopMonitoring();

	DWORD		GetWriteBufferSize();
	DWORD		GetCommEvents();
	DCB			GetDCB();

	void		WriteToPort(char* string,UINT len=0);
	virtual void OnReceiveChar(BYTE) {};

public:
	BOOL				m_bSuspended;
	BOOL				m_bThreadAlive;
	HANDLE				m_hComm;
	OVERLAPPED			m_ov;
	void ProcessErrorMessage(char* ErrorText);
	BOOL PostThreadMessage(UINT Msg, WPARAM wParam);

	// Event array. 
	// One element is used for each event. There are two event handles for each port.
	// A Write event and a receive character event which is located in the overlapped structure (m_ov.hEvent).
	// There is a general shutdown when the port is closed. 
	HANDLE				m_hEventArray[3];

	// thread
	HANDLE			m_ThreadHandle;
	DWORD				m_ThreadID;
	// misc
	UINT				m_nPortNr;
	UCHAR*				m_szWriteBuffer;
	UINT				m_wrLen;

	HANDLE				m_hWriteEvent;
	// synchronisation objects
//	CRITICAL_SECTION	m_csCommunicationSync;
	HANDLE			m_hMutex;
	// owner thread ID
	DWORD				m_OwnerThread; // m_pOwner;
protected:
//	static UINT	CommThread(LPVOID pParam);


	// handles
	HANDLE				m_hShutdownEvent;

	// structures
	COMMTIMEOUTS		m_CommTimeouts;
	DCB					m_dcb;


	// misc
	DWORD				m_dwCommEvents;
	DWORD				m_nWriteBufferSize;
};

#endif __SERIALPORT_H__



