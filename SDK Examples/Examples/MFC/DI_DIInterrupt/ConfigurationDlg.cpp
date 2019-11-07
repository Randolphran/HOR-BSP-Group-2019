// ConfigureForm.cpp : 
//

#include "stdafx.h"
#include "DIInterrupt.h"
#include "ConfigurationDlg.h"
#ifndef UNICODE
TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out)
{
   WideCharToMultiByte (CP_OEMCP,NULL,in,-1,out,MAX_DEVICE_DESC_LEN,NULL,FALSE);
   return out;
}
#else
TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out)
{
	wcscpy_s(out, wcslen(in) + 1, in);
	return out;
}
#endif

#ifndef UNICODE
WCHAR const * TCHAR_TO_WCHAR(TCHAR const * in,  WCHAR* out)
{
   MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)in, -1, out, MAX_DEVICE_DESC_LEN);
   return out;
}
#else
WCHAR const * TCHAR_TO_WCHAR(TCHAR const * in,  WCHAR* out)
{
	wcscpy_s(out, wcslen(in) + 1, in);
	return out;
}
#endif
// CConfigureForm dialog
IMPLEMENT_DYNAMIC(CConfigurationDlg, CDialog)

CConfigurationDlg::CConfigurationDlg(CWnd* pParent /*=NULL*/)
: CDialog(CConfigurationDlg::IDD, pParent)
, m_portNum0(0)
{
   m_diIntChannl = NULL;
	m_deviceCount = 0;
	m_enabledCount = 0;
	m_diINTPortCount = 0;
   m_portNum0 = -1;

	for (int i = 0; i < 256; i++)
	{
		if( i < 32 )
		{
			m_picBoxStatus[i] = -1;
		}
		if (i < 16 )
		{
         m_enabledChannel[i] = -1;
		}
      m_portNumList[i] = -1;
	}   
}

CConfigurationDlg::~CConfigurationDlg()
{
	if ( m_diIntChannl != NULL )
	{
		delete[]m_diIntChannl;
      m_diIntChannl = NULL;
	}
}

DevConfParam CConfigurationDlg::GetParameter()
{
   DevConfParam param;
   param.deviceNumber = (int)m_comboBox_Device.GetItemData(m_comboBox_Device.GetCurSel());
   param.enabledCount = m_enabledCount;
   for ( int i = 0; i < 16; i++ )
   {
      param.diEnableChannel[i] = m_enabledChannel[i];
   }
	TCHAR_TO_WCHAR(m_profilePath, param.profilePath);
   return param;
}

void CConfigurationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DEVICE, m_comboBox_Device);
	DDX_Control(pDX, IDC_SCROLLBAR, m_scrollBar);
}


BEGIN_MESSAGE_MAP(CConfigurationDlg, CDialog)
//{{AFX_MSG_MAP(CConfigureForm)
ON_BN_CLICKED(IDOK, OnOk)
ON_WM_PAINT()
ON_WM_VSCROLL()
ON_CBN_SELCHANGE(IDC_DEVICE, OnCbnSelchangeComboDevice)
ON_CONTROL_RANGE(STN_CLICKED,IDC_PICBOX1,IDC_PICBOX32, OnClick)
ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
ON_WM_CLOSE()
//}}AFX_MSG_MAP

ON_BN_CLICKED(IDC_BROWSE, OnBnClickedBrowse)
END_MESSAGE_MAP()

void CConfigurationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialog::OnPaint();
		CPaintDC   dc(this);   
		CBrush brush;   
		brush.CreateSolidBrush(RGB(236,233,216));       
		CBrush* pOldBrush = dc.SelectObject(&brush); 
		dc.Rectangle(20,96,311,214);   
		dc.SelectObject(pOldBrush); 
		brush.DeleteObject(); 
	}
}

BOOL CConfigurationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_enabledCount = 0;
   m_diINTPortCount = 0;
	m_imageList[0] = IDB_BUTTONUP;
	m_imageList[1] = IDB_BUTTONDOWN;
	m_imageList[2] = IDB_BUTTONDISABLE;
	for (int K = 0; K < 256; K++)
	{
      m_portNumList[K] = -1;
	}
	int portsID[4][11]={{IDC_PORTNUM0,IDC_GROUPBOX1,IDC_GROUPBOX2,IDC_PICBOX1,IDC_PICBOX2,IDC_PICBOX3,IDC_PICBOX4,IDC_PICBOX5,IDC_PICBOX6,IDC_PICBOX7,IDC_PICBOX8},
	{IDC_PORTNUM1,IDC_GROUPBOX3,IDC_GROUPBOX4,IDC_PICBOX9,IDC_PICBOX10,IDC_PICBOX11,IDC_PICBOX12,IDC_PICBOX13,IDC_PICBOX14,IDC_PICBOX15,IDC_PICBOX16},
	{IDC_PORTNUM2,IDC_GROUPBOX5,IDC_GROUPBOX6,IDC_PICBOX17,IDC_PICBOX18,IDC_PICBOX19,IDC_PICBOX20,IDC_PICBOX21,IDC_PICBOX22,IDC_PICBOX23,IDC_PICBOX24},
	{IDC_PORTNUM3,IDC_GROUPBOX7,IDC_GROUPBOX8,IDC_PICBOX25,IDC_PICBOX26,IDC_PICBOX27,IDC_PICBOX28,IDC_PICBOX29,IDC_PICBOX30,IDC_PICBOX31,IDC_PICBOX32}};

	for ( int i = 0; i < 4; i++ )
	{
		for ( int j = 0; j < 11; j++ )
		{
			m_portsID[i][j] = portsID[i][j]; 
		}
	}
	//hide the all ports
   SetAllPorts(false); 

	// create available device list.
   InstantDiCtrl * instantDiCtrl = InstantDiCtrl::Create();
   Array<DeviceTreeNode>* sptedDevices = instantDiCtrl->getSupportedDevices();

   if (sptedDevices->getCount() == 0)
   {
      GetDlgItem(IDOK)->EnableWindow(FALSE);
      GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
      AfxMessageBox(_T("No device to support the currently demonstrated function!"));
      return FALSE;
   }else{
      int deviceCount = 0;
      for (int i = 0; i < sptedDevices->getCount(); ++i)
      {
        
         DeviceTreeNode const & node = sptedDevices->getItem(i);
         TRACE("%d, %s\n", node.DeviceNumber, node.Description);

         DeviceInformation devInfo(node.DeviceNumber,ModeRead);
         instantDiCtrl->setSelectedDevice(devInfo);
         Array<DiintChannel>* INTChannels = instantDiCtrl->getDiintChannels();
         if (INTChannels == NULL)
         {
            continue;
         }
         TCHAR des[MAX_DEVICE_DESC_LEN];
         m_comboBox_Device.AddString(WCHAR_TO_TCHAR(node.Description,des));
         m_comboBox_Device.SetItemData(deviceCount++,node.DeviceNumber);
      }
      sptedDevices->Dispose();
   }
   instantDiCtrl->Dispose();
   m_comboBox_Device.SetCurSel(0);
   OnCbnSelchangeComboDevice();
	return TRUE;
}

// CConfigureForm 
void CConfigurationDlg::OnCbnSelchangeComboDevice()
{
	// TODO: Add your control notification handler code here
   InstantDiCtrl * instantDiCtrl = InstantDiCtrl::Create();
   CString des;
   m_comboBox_Device.GetLBText(m_comboBox_Device.GetCurSel(),des);

   wchar_t w_des[MAX_DEVICE_DESC_LEN];
   DeviceInformation devInfo( TCHAR_TO_WCHAR((LPCTSTR)des,  w_des) );
   ErrorCode errorCode = instantDiCtrl->setSelectedDevice(devInfo);
   GetDlgItem(IDOK)->EnableWindow(TRUE);
   if (errorCode != 0){
      CString str;
      str.Format(_T("Error: the error code is 0x%x, The %s is busy or not exit in computer now.\n\
  Select other device please!"),errorCode,des);
      AfxMessageBox(str);
      GetDlgItem(IDOK)->EnableWindow(FALSE);
      return;}
   SetINTStatus(instantDiCtrl);
	
   instantDiCtrl->Dispose();
}
void CConfigurationDlg::InitScrollBar( int portCount )
{
	//Initialize the scroll bar 
	if ( portCount < 5 )
	{
		m_scrollBar.ShowWindow(SW_HIDE);
	}
	else
	{
		if ( portCount > 5 || 5 == portCount  )
		{  
			m_scrollBar.ShowWindow(SW_SHOW);  		 
			int scrollMax = 120 + 28*( portCount - 4 );  //28 is one port height
			m_scrollBar.SetScrollRange(0, scrollMax);
			m_scrollBar.SetScrollPos(0);
			SCROLLINFO   info;
			info.fMask = SIF_PAGE;
			info.nPage = 120;
			m_scrollBar.SetScrollInfo(&info,true); 
		}
	}
}

ErrorCode CConfigurationDlg::SetINTStatus(InstantDiCtrl * instantDiCtrl)
{
	ErrorCode errorCode = Success;
   m_enabledCount = 0;
   m_portNum0 = -1;  
	m_diINTPortCount = 0;
	int i = 0;
	for ( int k = 0; k < 256; k++ )
	{
		m_portNumList[k] = -1;
		if( k < 32 )
		{
			m_picBoxStatus[k] = -1;
		}
		if (k < 16 )
		{
			m_enabledChannel[k] = -1;
		}
	}
	
   SetAllPorts(false); 
   int portsCount = instantDiCtrl->getPortCount();
   Array<DiintChannel>* interruptChans = instantDiCtrl->getDiintChannels();
	if ( m_diIntChannl != NULL )
	{
		delete[]m_diIntChannl;
		m_diIntChannl = NULL;
	}
	
   int INTChanCount = interruptChans->getCount();
   m_diIntChannl = new byte[portsCount*8];
   memset(m_diIntChannl,0,portsCount*8);

   for ( i = 0; i < INTChanCount; ++i)
   {
      m_diIntChannl[interruptChans->getItem(i).getChannel()] = 1;
   }
	
	bool isINTPort = false;
	for( i = 0; i < portsCount; i++ )
	{
		isINTPort = false;
		for( int j=0; j<8; j++)
		{
			if( 1 == m_diIntChannl[i*8+j] )
			{
				isINTPort = true;
				break;
			}
		}
		if( true == isINTPort)
		{
			m_portNumList[m_diINTPortCount] = i;
         m_diINTPortCount++;
		}
	}
	
   InitScrollBar( m_diINTPortCount );
   int portCount = 0;
	if ( m_diINTPortCount < 5 )
	{
		portCount = m_diINTPortCount;
	}
	else
	{
		if ( m_diINTPortCount >5 || 5 == m_diINTPortCount )
		{
			portCount = 4;
		}
	}
	
	// initialize the button
	for( i = 0; i < portCount; i++ )
	{
      ShowPort(m_portsID[i]);
		int INTPortNum = m_portNumList[i];
		
		CString portNum;
		portNum.Format(_T("%d"),INTPortNum);  
		GetDlgItem(IDC_PORTNUM0+i)->SetWindowText(_T("Port")+portNum+_T(":"));
		CRect rc;
		GetDlgItem(IDC_PORTNUM0+i)->GetClientRect(&rc);
		
		for(int j=0; j<8; j++)
		{
			if( 0 == m_diIntChannl [8*INTPortNum+j])
			{
				showPicture(IDC_PICBOX1+8*i+j,2);
            m_picBoxStatus[8*i+j] = 2;
			}
			else
			{
				if ( 1 == m_diIntChannl[8*INTPortNum+j] )
				{
					showPicture(IDC_PICBOX1+8*i+j,0);
					m_picBoxStatus[8*i+j] = 0;
				}
			}
		}
	}
   m_portNum0 = m_portNumList[0];
   configEnableButton();
	return errorCode;

	interruptChans->Dispose();
}

void  CConfigurationDlg::configEnableButton()
{
	int i = 0;
	for ( i = 0; i < 16; i++ )
	{
		m_enabledChannel[i] = m_enabledChannel[i];
		if ( m_enabledChannel[i] != -1 )
		{
			m_enabledCount++;
		}
	}

	for ( i = 0; i < 4 ; i++ )
	{	
		int INTPortNum = m_portNumList[i];		   
		// initialize the INT channel
		for(int j=0; j<8; j++)
		{
			for ( int q = 0; q < 16; q++ )
			{
				if ( (8*INTPortNum+j) == m_enabledChannel[q] )
				{
					showPicture(IDC_PICBOX1+8*i+j,1);
					m_picBoxStatus[8*i+j] = 1;
				}
			}
		}
	} 
}

void CConfigurationDlg::showPicture( int nID, int imageNum )
{
	CBitmap   bmp;   
	bmp.LoadBitmap(m_imageList[imageNum]); 
	((CStatic *)GetDlgItem(nID))->SetBitmap((HBITMAP)bmp); 
	bmp.Detach();
	CRect rc;
	GetDlgItem(nID)->GetClientRect(&rc);
	InvalidateRect(&rc,false);
}

//This function is used to handle the errorCode information
void CConfigurationDlg::CheckError(ErrorCode errorCode)
{
   if (errorCode !=  Success)
   {
      CString str;
      str.Format(_T("Some errors happened, the error code is:0x%x"), errorCode);
      AfxMessageBox(str);
   }
}

void CConfigurationDlg::OnOk()
{
	InstantDiCtrl* instantDiCtrl = InstantDiCtrl::Create();
	if ( 0 == m_enabledCount )
   {
      MessageBox(_T("Please enable at least one channel!"));
      return;
   }
   this->GetParent()->ShowWindow(SW_SHOW);
   this->GetParent()->EnableWindow(TRUE);
   this->ShowWindow(SW_HIDE);
/*
	Array<DeviceTreeNode>* sptedDevices = instantDiCtrl->getSupportedDevices();
	DeviceTreeNode const & node = sptedDevices->getItem(m_comboBox_Device.GetCurSel());
	DeviceInformation devInfo(node.DeviceNumber);
	ErrorCode errorCode = instantDiCtrl->setSelectedDevice(devInfo);

	int32 devNumber = instantDiCtrl->getDevice()->getDeviceNumber();
	int32 pdtId = instantDiCtrl->getDevice()->getProductId();

	TCHAR devNumberBuf[8] = {0};
	wsprintf(devNumberBuf, L"%x", devNumber);

	CallConfigTool(devNumberBuf);
	
	// Load the profile which has been changed by client.  
	TCHAR fileSavingPath[64] = {0};
	wsprintf(fileSavingPath, L"../../profile/0x%x-%x.xml", pdtId, devNumber);
	errorCode = instantDiCtrl->LoadProfile(fileSavingPath);
	
	// Load the default profile.
	if (errorCode == ErrorConfigDataLost)
	{
		MessageBox(L"Can not find the customization profile. Now load the default profile!");
		TCHAR fileDefaultPath[64] = {0};
		wsprintf(fileDefaultPath, L"../../../Navigator/profile/0x%x.xml", pdtId);
		errorCode = instantDiCtrl->LoadProfile(fileDefaultPath);
		CheckError(errorCode);
	}
	*/
   // Send message to configure the device selected.
   ::SendMessage(this->GetParent()->m_hWnd,WM_CUSTOME_CFG_CHGED,0,0);
	CDialog::OnOK();
	/*sptedDevices->Dispose();*/
	instantDiCtrl->Dispose();
}


void CConfigurationDlg::OnClick(UINT nID)
{
	int clickCh = nID - IDC_PICBOX1;
	int Index = 0;
	for ( int i = 0; i < m_diINTPortCount; ++i )
	{
		if ( m_portNum0 == m_portNumList[i] )
		{
			Index = i;
			break;
		}
	}
	
	int clickPort = m_portNumList[Index + clickCh/8];
	int enableCh = 8*clickPort+clickCh%8;
	
	if ( 0 == m_picBoxStatus[clickCh] )
	{
		if ( m_enabledCount < 16 )
		{	
			m_enabledCount++;	
			showPicture(nID,1);  	
			m_picBoxStatus[clickCh] = 1;
			for ( int i = 0; i < 16; i++ )
			{
				if ( m_enabledChannel[i] == -1 )
				{
					m_enabledChannel[i] = enableCh;
					break;
				}
			}
		}
		else
		{
			MessageBox(_T("Demo only supports 16 channels enabled at the same time !"));
		}
	}
	else
	{
		if ( 1 == m_picBoxStatus[clickCh] )
		{
         m_enabledCount--;
			showPicture(nID,0);
			m_picBoxStatus[clickCh] = 0;
			for ( int i = 0; i < 16; i++ )
			{
				if ( m_enabledChannel[i] == enableCh )
				{
					m_enabledChannel[i] = -1;
					break;
				}
			}
			
			int channel[16];
			int enableCount = 0;
			for ( int j = 0; j < 16; j++ )
			{
				channel[j] = -1;
				if ( m_enabledChannel[j] != -1 )
				{
					channel[enableCount] = m_enabledChannel[j];
					enableCount++;
				}
			}
			for ( int k = 0; k < 16; k++ )
			{
				m_enabledChannel[k] = channel[k];
			}
		}
	}
}


void CConfigurationDlg::SetAllPorts( bool state)
{
	for ( int i= 0; i < 4; i++)
	{
		for (int j = 0; j < 11; j++)
		{
         GetDlgItem(m_portsID[i][j])->ShowWindow(state);
		}
	}
}

void CConfigurationDlg::ShowPort(int *pPort)
{
   for ( int i = 0; i < 11; i++ )
   {
		GetDlgItem(*(pPort++))->ShowWindow(SW_SHOW);
   }
}

void CConfigurationDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SCROLLINFO   info;
	m_scrollBar.GetScrollInfo(&info);
	int iNewPos;
	int length = info.nMax - 120;
	switch(nSBCode)
	{
		if ( &m_scrollBar == pScrollBar )
		{
			case SB_THUMBTRACK:
				m_scrollBar.SetScrollPos(nPos);
				iNewPos = m_scrollBar.GetScrollPos();
				refreshButton(iNewPos);
			case SB_LINEDOWN:
				iNewPos = m_scrollBar.GetScrollPos();
				iNewPos = iNewPos + 1;
				if ( iNewPos >info.nMax )
				{
					iNewPos = info.nMax;
				}
				m_scrollBar.SetScrollPos(iNewPos);
				refreshButton(iNewPos);
				break;
			case SB_LINEUP:
				iNewPos = m_scrollBar.GetScrollPos();
				iNewPos = iNewPos - 1;
				if ( iNewPos < 0 )
				{
					iNewPos = 0;
				}
				m_scrollBar.SetScrollPos(iNewPos);
				refreshButton(iNewPos);
				break;
			case SB_PAGEDOWN:
				iNewPos = m_scrollBar.GetScrollPos();
				iNewPos = iNewPos + 1;
				if ( iNewPos >info.nMax )
				{
					iNewPos = info.nMax;
				}
				m_scrollBar.SetScrollPos(iNewPos);
				refreshButton(iNewPos);
				break;
			case SB_PAGEUP:
				iNewPos = m_scrollBar.GetScrollPos();
				iNewPos = iNewPos - 1;
				if ( iNewPos < 0 )
				{
					iNewPos = 0;
				}
				m_scrollBar.SetScrollPos(iNewPos);
				refreshButton(iNewPos);
				break;
		}
	}
	CDialog::OnVScroll(nSBCode,nPos,pScrollBar);
}

void CConfigurationDlg::refreshButton(int iNewPos)
{
	int minPos = 0;
	int maxPos = 0;
	for ( int k = 0; k < (m_diINTPortCount-4+1); k++ )
	{	
		if ( 0 == k )
		{
			minPos = 0;
			maxPos = 14;
		}
		if ( (m_diINTPortCount-4+1) == k )
		{
			minPos = 28*k-14;
			maxPos = 28*k;
		}
		minPos = 28*k-14;
		maxPos = 28*k+14;
		if ( minPos< iNewPos && iNewPos < maxPos )
		{			
			if ( m_portNumList[k] != m_portNum0 )
			{	
				m_portNum0 = m_portNumList[k];
				for ( int i = 0; i < 4 ; i++ )
				{	
					int INTPortNum = m_portNumList[i+k];		   
					CString portNum;
					portNum.Format(_T("%d"), INTPortNum);
					GetDlgItem(IDC_PORTNUM0+i)->SetWindowText(_T("  "));
					GetDlgItem(IDC_PORTNUM0+i)->SetWindowText(_T("Port")+portNum+_T(":"));
					
					CRect rc;
					GetDlgItem(IDC_PORTNUM0+i)->GetClientRect(&rc);
               GetDlgItem(IDC_PORTNUM0+i)->RedrawWindow(&rc);
					
               // initialize the INT channel
					for(int j=0; j<8; j++)
					{
						if( 0 == m_diIntChannl [8*INTPortNum+j])
						{
							showPicture(IDC_PICBOX1+8*i+j,2);
							m_picBoxStatus[8*i+j] = 2;
						}
						else
						{
							if ( 1 == m_diIntChannl[8*INTPortNum+j] )
							{
								showPicture(IDC_PICBOX1+8*i+j,0);
								m_picBoxStatus[8*i+j] = 0;
							}
						}
                  //show the enabled the INT channel
						for ( int q = 0; q < 16; q++ )
						{
							if ( (8*INTPortNum+j) == m_enabledChannel[q] )
							{
                        showPicture(IDC_PICBOX1+8*i+j,1);
                        m_picBoxStatus[8*i+j] = 1;
							}
						}
					}      					
				}
			}
		}
	}
}


void CConfigurationDlg::OnBnClickedCancel()
{
   // TODO: Add your control notification handler code here
   CString windowText;
   this->GetParent()->GetWindowText(windowText);
   if (!windowText.Compare(_T("DI Interrupt")))
   {
      ::SendMessage(this->GetParent()->m_hWnd,WM_CUSTOME_CFG_CHGED,1,0);
      this->CloseWindow();
   } 
   OnCancel();
}

void CConfigurationDlg::OnClose()
{
   // TODO: Add your message handler code here and/or call default
   if ( m_comboBox_Device.GetCount() <= 0)
   {
      PostQuitMessage(0);
   }
   CDialog::OnClose();
}

void CConfigurationDlg::OnBnClickedBrowse()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, _T("xml"), _T(""), OFN_OVERWRITEPROMPT, _T("Licence File(*.xml)|*.xml|"));
	dlg.m_ofn.lpstrInitialDir = _T("../../profile/"); 
	if(dlg.DoModal() == IDOK)
	{
		m_profilePath = dlg.GetPathName();
		GetDlgItem(IDC_EDIT_PROFILE)->SetWindowText(m_profilePath);
	} 
}
