// Programmed by Ferhat Mousavi
// First Released: 12/07/2005
// Last Released: 11/07/2006
 

#include "StdAfx.h"
#include ".\comport.h"

CComPort::CComPort(void)
{
   m_hConn = NULL;
   m_hMPP = NULL;

   m_pConn = NULL;
   m_pMPP = NULL;
}

CComPort::~CComPort(void)
{
   if(m_pConn && m_pConn->bConnected)
   {
      TRACE(_T("Warning: terminating COMM connection in GCommMonitor::~GCommMonitor()\n"));
      Disconnect();
   }

   if(m_hConn)
   {
      ::GlobalUnlock(m_hConn);
      ::GlobalFree(m_hConn);
   }

   if(m_hMPP)
   {
      ::GlobalUnlock(m_hMPP);
      ::GlobalFree(m_hMPP);
   }
}


BOOL CComPort::IsConnected() const
{
   return (m_pConn && m_pConn->bConnected);
}



BOOL CComPort::Connect(LPTTYSTRUCT lpTTY)
{
   if(m_pConn && m_pConn->bConnected)
      return TRUE;

   // only allocate this guy once
   if(!m_hConn)
   {
      m_hConn = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(CONNECTION));
      m_pConn = (LPCONNECTION)::GlobalLock(m_hConn);
      ZeroMemory(m_pConn, sizeof(CONNECTION));
   }

   // create I/O event used for overlapped reads/writes
   //if((m_pConn->osRead.hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL)) == NULL)
     // return FALSE;

   //if((m_pConn->osWrite.hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL)) == NULL)
     // return FALSE;
   
   // open communcations file
   CString strPort;
   //if(lpTTY->byCommPort > 3)
   //{
   //   strPort = "\\\\.\\TELNET";
	  //AfxMessageBox(" ??? ");
   //}
   //else
   //{
      strPort.Format(_T("COM%d"), lpTTY->byCommPort + 1);
   //}

   m_pConn->hCommDev = ::CreateFile(strPort, GENERIC_READ|GENERIC_WRITE, 0,
                                  NULL, OPEN_EXISTING, 
                                  0, //FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, 
                                  NULL);

   if(m_pConn->hCommDev == INVALID_HANDLE_VALUE)
      return FALSE;
   
   BOOL bPurge = FALSE;
   // get any early notifications
   if(::SetCommMask(m_pConn->hCommDev, EV_RXCHAR))
   {
      // setup device buffers
      if(::SetupComm(m_pConn->hCommDev, 4096, 4096))
      {
         // purge any information in the buffer
         if(::PurgeComm(m_pConn->hCommDev, //PURGE_TXABORT|PURGE_RXABORT|
                                           PURGE_TXCLEAR|PURGE_RXCLEAR))
         {
            bPurge = TRUE;
         }
      }
   }
   
   if(!bPurge)
   {
      ::CloseHandle(m_pConn->hCommDev);
      return FALSE;
   }

   // set up for overlapped I/O
   COMMTIMEOUTS CommTimeOuts;

   //   BEST SETTINGS
   //CommTimeOuts.ReadIntervalTimeout = 1;			//0xFFFFFFFF;
   //CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
   //CommTimeOuts.ReadTotalTimeoutConstant = 5;
   //CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
   //CommTimeOuts.WriteTotalTimeoutConstant = 0;	

   
   CommTimeOuts.ReadIntervalTimeout = 5;			
   CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
   CommTimeOuts.ReadTotalTimeoutConstant = 5;
   CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
   CommTimeOuts.WriteTotalTimeoutConstant = 0;	
   
  

   if(!::SetCommTimeouts(m_pConn->hCommDev, &CommTimeOuts))
   {
      ::CloseHandle(m_pConn->hCommDev);
      return FALSE;
   }

   // set up the connect
   DCB dcb;
   ZERO_MEMORY(dcb);
   dcb.DCBlength = sizeof(DCB);

   if(!::GetCommState(m_pConn->hCommDev, &dcb))
   {
      ::CloseHandle(m_pConn->hCommDev);
      return FALSE;
   }
   
   dcb.BaudRate = lpTTY->dwBaudRate;
   dcb.ByteSize = lpTTY->byByteSize;
   dcb.Parity = lpTTY->byParity;
   dcb.StopBits = lpTTY->byStopBits;
  
/*
   // setup hardware flow control
   BOOL bSet = (BYTE)((lpTTY->byFlowCtrl & FC_DTRDSR) != 0);
   dcb.fOutxDsrFlow = bSet;
   if(bSet)
      dcb.fDtrControl = DTR_CONTROL_HANDSHAKE;
   else
      dcb.fDtrControl = DTR_CONTROL_ENABLE;

   bSet = (BYTE)((lpTTY->byFlowCtrl & FC_RTSCTS) != 0);
	dcb.fOutxCtsFlow = bSet;
   if(bSet)
      dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
   else
      dcb.fRtsControl = RTS_CONTROL_ENABLE;

   // setup software flow control
   bSet = (BYTE)((lpTTY->byFlowCtrl & FC_XONXOFF) != 0);

   dcb.fInX = dcb.fOutX = bSet;
   dcb.XonChar = ASCII_XON;
   dcb.XoffChar = ASCII_XOFF;
   dcb.XonLim = 100;
   dcb.XoffLim = 100;
*/
   // other various settings
   dcb.fBinary = TRUE;
   dcb.fParity = FALSE;
   dcb.fOutxCtsFlow = FALSE;
   dcb.fOutX = FALSE;
   dcb.fInX = FALSE;
   dcb.fErrorChar = FALSE;
   dcb.fNull = FALSE;
   


   if(!::SetCommState(m_pConn->hCommDev, &dcb))
   {
      ::CloseHandle(m_pConn->hCommDev);
      return FALSE;
   }

   m_pConn->bConnected = TRUE;

   return m_pConn->bConnected;
}



BOOL CComPort::Disconnect()
{
   if(!m_pConn)
      return TRUE;

   // set connected flag to false
   m_pConn->bConnected = FALSE;
   
   // disable event notification and wait for thread to halt
   //SetCommMask(m_pConn->hCommDev, 0);

   // block until thread has been halted
   //while(m_pConn->dwThreadID != 0)
   //{
   //   Sleep(10);
   //}

   // drop DTR 
   //EscapeCommFunction(m_pConn->hCommDev, CLRDTR);

   // purge any outstanding reads/writes and close device handle
   PurgeComm(m_pConn->hCommDev, //PURGE_TXABORT|PURGE_RXABORT|
                                PURGE_TXCLEAR|PURGE_RXCLEAR);

   ::CloseHandle(m_pConn->hCommDev);
   //::CloseHandle(m_pConn->osRead.hEvent);
   //::CloseHandle(m_pConn->osWrite.hEvent);

   return TRUE;
}





BOOL CComPort::Monitor(LPMONITORPROC lpMonitorProc, LPARAM lParam)
{
   BOOL bMonitor = FALSE;

   // create monitoring thread
   if(m_pConn->bConnected)
   {
      if(lpMonitorProc)
      {
         if(!m_hMPP)
         {
            m_hMPP = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(MONITORPROCPARAMS));
            m_pMPP = (LPMONITORPROCPARAMS)::GlobalLock(m_hMPP);
         }

         m_pMPP->lpConn = m_pConn;
         m_pMPP->lpCallback = lpMonitorProc;
         m_pMPP->lpCallbackParam = lParam;

         // create a secondary thread to watch for an event
         DWORD dwThreadID;
         if(::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CommMonitorProc,
                           (LPVOID)m_pMPP, 0, &dwThreadID))
         {
            m_pConn->dwThreadID = dwThreadID;

            ::EscapeCommFunction(m_pConn->hCommDev, SETDTR);
            bMonitor = TRUE;
         }
      }
      else
      {
         ASSERT(FALSE);  // not currently implemented
      }
   }

   return bMonitor;
}



DWORD CALLBACK CComPort::CommMonitorProc(LPVOID lpThreadParameter)
{
   HGLOBAL hParams = (HGLOBAL)lpThreadParameter;
   LPMONITORPROCPARAMS pParams = (LPMONITORPROCPARAMS)::GlobalLock(hParams);
   if(!pParams)
      return 0;
   
   HGLOBAL hBuf = ::GlobalAlloc(GMEM_MOVEABLE, MAX_RXBLOCK + 1);
   if(!hBuf)
   {
      ::GlobalUnlock(hParams);
      return 0;
   }

   LPBYTE lpBuffer = (LPBYTE)::GlobalLock(hBuf);
   if(!lpBuffer)
   {
      ::GlobalUnlock(hParams);
      ::GlobalFree(hBuf);
      return 0;
   }

   // create I/O event used for overlapped read
   //OVERLAPPED os;
   //::ZeroMemory(&os, sizeof(os));

   //os.hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);

   //if(os.hEvent == NULL || !SetCommMask(pParams->lpConn->hCommDev, EV_RXCHAR))
   //{
//      ReportLastError();
   //  return 0;
   //}

   while(pParams->lpConn->bConnected)
   {
      //DWORD dwEvtMask = 0;
      int nLength = 0;

      //OVERLAPPED ol;
      //::ZeroMemory(&ol, sizeof(ol));
      //ol.hEvent = os.hEvent;

      //WaitCommEvent(pParams->lpConn->hCommDev, &dwEvtMask, NULL);

      //if((dwEvtMask & EV_RXCHAR) == EV_RXCHAR)
      //{
         do
         {
            if((nLength = CommReadBlock(pParams->lpConn, lpBuffer, MAX_RXBLOCK)) != 0)
            {
               if(pParams->lpCallback)
                  pParams->lpCallback(hBuf, nLength, pParams->lpCallbackParam);
            }

         } while(nLength > 0);
      //}
   }

   ::GlobalUnlock(hBuf);
   ::GlobalFree(hBuf);

   // get rid of event handles
   //::CloseHandle(os.hEvent);

   // clear information in structure (indicates the thread has terminated)
   pParams->lpConn->dwThreadID = NULL;

   ::GlobalUnlock(hParams);
   return 1;
}





BOOL CALLBACK CComPort::CommReadBlock(LPCONNECTION lpConn, LPBYTE lpszBlock, int nLen)
{
   // only try to read number of bytes in queue
   DWORD dwErrorFlags;
   COMSTAT ComStat;

   ::ClearCommError(lpConn->hCommDev, &dwErrorFlags, &ComStat);
   DWORD dwLength = (DWORD)nLen;//min((DWORD)nLen, ComStat.cbInQue);

   if(dwLength > 0)
   {
      BOOL bReadStat = ReadFile(lpConn->hCommDev, lpszBlock, dwLength,
                                &dwLength, NULL);//&lpConn->osRead);

	  LPCTSTR tmp;
	  lpszBlock[dwLength] = 0;
	  tmp = (LPCTSTR)lpszBlock;
	  //tmp[dwLength] = 0;
	  CString tm;
	  tm.Format("len=%d, %s",dwLength,tmp);
	  //AfxMessageBox(tm);

      if(!bReadStat)
      {
         if(GetLastError() == ERROR_IO_PENDING)
         {
            OutputDebugString("\n\rIO Pending");
            // we have to wait for read to complete.  This function will timeout
            // according to the CommTimeOuts.ReadTotalTimeoutConstant variable
            // Every time it times out, check for port errors
            /*while(!GetOverlappedResult(lpConn->hCommDev, &lpConn->osRead,
                                       &dwLength, TRUE))
            {
               DWORD dwError = GetLastError();
               if(dwError == ERROR_IO_INCOMPLETE)
               {
                  // normal result if not finished
                  continue;
               }
               else
               {
                  // CAN DISPLAY ERROR MESSAGE HERE
                  // an error occured, try to recover
                  ::ClearCommError(lpConn->hCommDev, &dwErrorFlags, &ComStat);
                  if(dwErrorFlags > 0)
                  {
                     // CAN DISPLAY ERROR MESSAGE HERE
                  }

                  break;
               }
            }*/
            
         }
         else
         {
            // some other error occured
            dwLength = 0;
            ClearCommError(lpConn->hCommDev, &dwErrorFlags, &ComStat);
            if(dwErrorFlags > 0)
            {
               // CAN DISPLAY ERROR MESSAGE HERE
            }
         }
      }
   }

   return dwLength;
}



BOOL CComPort::CommWriteBlock(LPBYTE lpszBlock, int nLen)
{
   // only try to read number of bytes in queue
   DWORD dwErrorFlags;
   COMSTAT ComStat;
   ::ClearCommError(m_pConn->hCommDev, &dwErrorFlags, &ComStat);
   DWORD dwLength = (DWORD)nLen;//min((DWORD)nLen, ComStat.cbInQue);
   if(dwLength > 0)
   {
      BOOL bReadStat = WriteFile(m_pConn->hCommDev, lpszBlock, dwLength,
                                &dwLength, NULL);//&lpConn->osRead);

   }
   return dwLength;
}

