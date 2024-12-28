// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "IP2ComServer.h"


#include "IP2ComServerDoc.h"
#include "IP2ComServerView.h"
#include "Configurations.h"


#include "MainFrm.h"
#include ".\mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()


	ON_COMMAND(ID_TOOLBAR_START, OnStart)
	ON_COMMAND(ID_TOOLBAR_STOP, OnStop)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_START, OnUpdateStart)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_STOP, OnUpdateStop)

	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
	// User Defined messages
	ON_MESSAGE(IDM_COM_RCV, OnComRcv)
	//ON_MESSAGE(WM_COMM_RXFLAG_DETECTED, OnComRcv)
	ON_COMMAND(ID_FILE_OPTIONS, OnFileOptions)
	ON_WM_TIMER()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	EnableActiveAccessibility();
	// TODO: add member initialization code here
	m_listener = 0;
	
}

CMainFrame::~CMainFrame()
{

}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	m_Port=10020;
	m_COM=COMPORT_07;
	m_IsConnected=FALSE;

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style &= ~FWS_ADDTOTITLE ; // get rid of 'Untitled' in main window caption.

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG




//void CVirtualHSMDlg::OnAccept(DWORD dwSP,DWORD dwClient)
//{
//	char addr[64];
//	int port;
//	//__super::
//		GetPeerName(dwSP, dwClient, addr, &port);
//	CString s;
//	s.Format("new connection from %s:%d", addr, port);
////	AfxMessageBox(s);
//	//__super::
//	SetHeaders(dwSP, dwClient, FALSE, FALSE);
//}



void CMainFrame::OnAccept(DWORD dwSP,DWORD dwClient)
{
	char addr[64];
	int port;
	//__super::
	((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("OnAccept");
	GetPeerName(dwSP, dwClient, addr, &port);
	__super::SetHeaders(dwSP, dwClient, false, false);
	CString s;
	m_IsConnected=TRUE;
	s.Format("CLIENT CONNECTED %s:%d", addr, port);
	m_SP=dwSP;
	m_Client=dwClient;
	((CIP2ComServerView*)GetActiveView())->InsertInternalMsg(s);


}

void CMainFrame::OnDisconnect(DWORD dwSP,DWORD dwClient)
{
	((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("CLIENT DISCONNECTED!!!");
	m_IsConnected=FALSE;
	((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("OnDisconnect!!!");
}


// IP Incomming
void CMainFrame::OnProcessIncoming(DWORD dwSP,DWORD dwClient, UCHAR* buf, int len)
{

	static char Temp[5];
	//if(m_IsConnected){
	//	return;
	//}
	if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("OnProcessIncoming");
	if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg((CString)buf);
	char PosTemp[512];
	memcpy(PosTemp,buf+2,len-3);
	PosTemp[len-3]=0;

	
	
	
	m_com.CommWriteBlock((LPBYTE)buf+2,len-3);	
	Temp[0]=ACK;
	__super::Send(m_SP, m_Client, (LPBYTE)Temp, 1);		
	
	
	if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg((CString)PosTemp);
	if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("POSA GIDEN DATA");


	m_SP=dwSP;
	m_Client=dwClient;
}


void CMainFrame::OnStart()
{
	int _nDataValues[] = {5,6,7,8};

	m_listener = __super::CreateListener(m_Port); // PORT NUMBER

	if (m_listener <=0 ) {
		AfxMessageBox("can not create listener");
		return;
	}
	((CIP2ComServerView*)GetActiveView())->DeleteAll();

	if(m_com.IsConnected)
	{
	   UpdateData();

       // initialize tty info
       TTYSTRUCT tty;
       ZERO_MEMORY(tty);

       tty.byCommPort = (BYTE)m_COM;
       tty.byXonXoff = FALSE;
       tty.byByteSize = (BYTE)_nDataValues[3]; 
       tty.byFlowCtrl = 0;
       tty.byParity = 0; 
       tty.byStopBits = 0;
       tty.dwBaudRate = (DWORD)CBR_115200;	//CBR_110, CBR_300, CBR_600, CBR_1200, CBR_2400,					
											//CBR_4800, CBR_9600, CBR_14400, CBR_19200,
											//CBR_38400, CBR_56000, CBR_57600, CBR_115200,
											//CBR_128000, CBR_256000
	
		if(m_com.Connect(&tty))
		{
//          ShowControls(SW_HIDE, &m_rectDisplayStart);
 
          // we're about to start up a thread...if we don't force all control
          // repaints before then, the display will repaint sluggishly
			MSG msg;
			 while(PeekMessage(&msg, NULL, WM_PAINT, WM_PAINT, PM_NOREMOVE))
			{
             ::TranslateMessage(&msg);
             ::DispatchMessage(&msg);
			}

          // begin monitoring
			if(!m_com.Monitor(&MonitorCallback, (LPARAM)m_hWnd))
			{
			  OnStop();
			}
			
		((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("SERVER STARTED SUCCESSFULLY");
		}
		else
		{
			AfxMessageBox("Can not open com port");
			OnStop();
		}
	}else{
		OnStop();
	}
	AfxGetMainWnd()->SetTimer(1,500, NULL);
}

void CMainFrame::OnStop()
{
	if (m_listener > 0) __super::DeleteListener(m_listener); 
	m_listener = 0;
	m_com.Disconnect();
	if(m_IsConnected){
		((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("CLIENT DISCONNECTED!!!");
		m_IsConnected=FALSE;
	}
	((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("SERVER STOPPED!!!");

	AfxGetMainWnd()->KillTimer(1);
}

void CMainFrame::OnUpdateStart(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_listener <= 0);
}

void CMainFrame::OnUpdateStop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_listener > 0);
}

// COM Incomming
int CALLBACK MonitorCallback(HGLOBAL hBuf, int nLen, LPARAM lParam)
{
   HWND hDlg = (HWND)lParam;
   ::SendMessage(hDlg, IDM_COM_RCV, nLen, (LPARAM)hBuf);

   return 1;
}


LRESULT CMainFrame::OnComRcv( WPARAM wLen, LPARAM hBuf) //WPARAM wParam, LPARAM wPortNr )
{
 static char	Temp[1024],POSPacket[1024];
 static int		POSPacketLen = 0, RcvLen = 0, SendToHost = 0; 	
 static int		i;

m_IsLog = 1;

	LPBYTE lpBuf = (LPBYTE)::GlobalLock((HGLOBAL)hBuf);

	SendToHost = 0;
	if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("COMPORT");
	if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg((CString)(LPBYTE)hBuf);
	if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("COMPORT");
	if ( (int)wLen < 10 )		/* to fast compare */
	{
		if( ( lpBuf[0] == ACK ) ) 
		{
			if ( (int)wLen == 1 )
			{
				Temp[0]=EOT;
				m_com.CommWriteBlock((LPBYTE)Temp,1);	
				if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("ACK RECEIVED from POS - EOT Send to POS");
				
				memset(POSPacket,0,25);
				POSPacketLen=0;
				::GlobalUnlock((HGLOBAL)hBuf);
				return 1;
			}
		}
		else if(!memcmp(lpBuf,"CONNECT",7))
		{
			if ( m_IsConnected )
			{
				memset(POSPacket,0,25);
				POSPacketLen=0;
				Temp[0] = ENQ;
				m_com.CommWriteBlock((LPBYTE)Temp,1);
			    if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("CONNECT received from POS - ENQ Send to POS");
			}
			::GlobalUnlock((HGLOBAL)hBuf);
			return 1;
		}
	}
	
	switch ( lpBuf[0] )
	{
		case STX :
		case ACK :
		case NAK :
		case DLE :
			POSPacketLen = 0;
			POSPacket[0] = 0x23;	//#
			POSPacket[1] = 'a';
			memcpy( POSPacket+2, lpBuf, (size_t)wLen );
			POSPacketLen = (int)wLen + 2;
			break;
		default  :
			
			if (POSPacketLen)
			{
				if ( (POSPacketLen + (int)wLen) > 1000 )
				{
					if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("POS DATA BUFFER OVERFLOW");
				}
				else
				{
					memcpy( POSPacket + POSPacketLen, lpBuf, (size_t)wLen);
					POSPacketLen = POSPacketLen + (int)wLen;
				}
			}
			else
			{
				for (i=0;i<(int)wLen;i++)
				{
					switch ( lpBuf[i] )
					{
						case STX :
						case ACK :
						case NAK :
						case DLE :
							POSPacketLen = 0;
							POSPacket[0] = 0x23;	//#
							POSPacket[1] = 'a';
							memcpy( POSPacket+2, &lpBuf[i], (size_t)(wLen-i) );
							POSPacketLen = (int)wLen + 2 - i;
							break;
						default  :
							// ignore the 
							break;
					}
				}	
				if( POSPacketLen == 0 )
				{				
					if(m_IsLog)
					{
						((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("Unexpected Data Received from POS");
					}
				}
			}
			break;
	}
	
	switch ( POSPacket[2] )
	{
		case STX :
			
			if ( POSPacketLen > (23 + 2) )	// 23 FIXLEN for header in to the POS buffer
			{
				RcvLen=0;
				memcpy( Temp, POSPacket + (23 + 2 - 4), 2 );
				Temp[2] = 0;
				sscanf( Temp,"%02X",&RcvLen);

				if ( POSPacketLen >= ( RcvLen + (23 + 2) + 2))
				{
					SendToHost = 1;

					Temp[0] = ACK;
					memcpy( Temp + 1, POSPacket + 4, 2 );
					Temp[3] = '0';
					m_com.CommWriteBlock( (LPBYTE)Temp, 4 );
		
				}
				else
				{
					if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("POS packet fragmented in the Data");
				}
			}
			else
			{
				if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("POS packet fragmented before header");
			}
			break;
		case ACK :
			if ( POSPacketLen >= 6 )
			{
				SendToHost = 1;
				
				if ( POSPacketLen >= 7 )
				{
					if ( POSPacket[6] == ACK )
					{
						Temp[0]=EOT;
						m_com.CommWriteBlock((LPBYTE)Temp,1);
						if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("ACK RECEIVED from POS - EOT Send to POS");
						if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg((CString)POSPacket);
						if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("ACK RECEIVED from POS - EOT Send to POS");
					}
				}

				POSPacketLen = 6;
			}
			break;
		case NAK :
			if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("NAK RECEIVED from POS");
			memset(POSPacket,0,25);
			POSPacketLen=0;
			break;
		case DLE :
			if ( POSPacketLen >= 4 )
			{
				if ( POSPacket[3] == EOT )
				{
					SendToHost = 1;
				}
				else
				{
					if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("ERROR! EOT not Received after DLE");
				}
				POSPacketLen = 4;
			}
			break;
		default  :
			if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("INVALID POS DATA!! ERROR");
			POSPacketLen = 0;
			break;
	}
	
	::GlobalUnlock((HGLOBAL)hBuf);
	
	if ( SendToHost )
	{
		switch ( POSPacket[2] )
		{
			case STX : 
				//if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("STX Data Packet Received From POS");
				break;
			case ACK :
				//if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("ACK Packet Received From POS");
				break;
			case DLE :
				//if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("DLE + EOT Received From POS");
				break;
			default  :	
				//if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("DEFAULT:ERROR in the POS Packet buffer");
				 SendToHost = 0;
				 memset(POSPacket,0,25);
        		 POSPacketLen=0;
				break;
		}
		
		if ( SendToHost && m_IsConnected )
		{	
			__super::Send(m_SP, m_Client, (LPBYTE)POSPacket, POSPacketLen);
			if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("Transferred to HOST");
			if(m_IsLog)((CIP2ComServerView*)GetActiveView())->InsertInternalMsg((CString)POSPacket);
		}
	}

	if(SendToHost && (!m_IsConnected))
	{
		((CIP2ComServerView*)GetActiveView())->InsertInternalMsg("HOST Connection is Dropped, Data not transfered to HOST !");
	}

	if(SendToHost){
		memset(POSPacket,0,25);
		POSPacketLen=0;
	}

	return TRUE;
}



bool CMainFrame::WriteLogFile(CString logMessage)
{
	// Virtual Function
	CString logStr;

	CTime t = CTime::GetCurrentTime();
	
	CString currDateTime = t.Format( "%A, %B %d, %Y, %H:%M:%S" );
	// s == "Tuesday, March 19, 1991"


	CStdioFile logfile("log.log", CFile::modeCreate | CFile::modeNoTruncate | 
		CFile::modeReadWrite | CFile::typeText );
	if(!logfile)
	{
	  CWnd a; 
	  a.MessageBox("Can not open log.log");
	  return false;
	}
	logfile.SeekToEnd(); 

	logStr.Format("[[%s]]",currDateTime.GetBuffer());
	logfile.Write(logStr.GetBuffer(), logStr.GetLength());


//	logStr.Format("[[%s]]%c%c",logMessage.GetBuffer(),0x0D,0x0A);
	logStr.Format( "[[%s]]%c", logMessage.GetBuffer() ,0x0A );
	logfile.Write(logStr.GetBuffer(), logStr.GetLength());
	logfile.Close();
	return true;
}


void CMainFrame::OnFileOptions()
{
	CConfigurations cfg;

	if (cfg.DoModal()==IDOK) {
		m_Port=cfg.m_IP_port;
		m_COM=cfg.m_COM_Port;
		m_IsLog=cfg.m_bLog;
		

	}
}

void CMainFrame::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	__super::OnTimer(nIDEvent);
}