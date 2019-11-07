// ConfigureForm.cpp : implementation file
//

#include "stdafx.h"
#include "DIPatternMatchInterrupt.h"
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
{
   for (int i = 0; i < 256; i++)
   {
		if( i < 8 )
		{
			m_enabledStatus[i] = -1;
			m_PmValueStatus[i] = -1;
		}
   }   
}

CConfigurationDlg::~CConfigurationDlg()
{
}

void CConfigurationDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_DEVICE, m_comboBox_Device);
   DDX_Control(pDX, IDC_PORT, m_comboBox_Port);
}


BEGIN_MESSAGE_MAP(CConfigurationDlg, CDialog)
//{{AFX_MSG_MAP(CConfigureForm)
ON_BN_CLICKED(IDOK, OnOk)
ON_CBN_SELCHANGE(IDC_DEVICE, OnCbnSelchangeComboDevice)
ON_CBN_SELCHANGE(IDC_PORT, OnSelchangePort)
ON_CONTROL_RANGE(STN_CLICKED,IDC_PIC0,IDC_PIC15,OnClick)
ON_WM_PAINT()
ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
ON_WM_CLOSE()
//}}AFX_MSG_MAP

ON_BN_CLICKED(IDBROWSE, OnBnClickedBrowse)
END_MESSAGE_MAP()

DevConfParam CConfigurationDlg::GetParameter()
{
   DevConfParam param;
   param.deviceNumber = (int)m_comboBox_Device.GetItemData(m_comboBox_Device.GetCurSel());
   param.selectedPort = (int)m_comboBox_Port.GetItemData(m_comboBox_Port.GetCurSel());
   CString enabledChan;
   GetDlgItem(IDC_PMCH)->GetWindowText(enabledChan);
   long enabledChannels = _tcstol(enabledChan,NULL,16);
   param.enabledChannels = (byte)enabledChannels;

   CString PmValue;
   GetDlgItem(IDC_PMVALUE)->GetWindowText(PmValue);
   long Value = _tcstol(PmValue,NULL,16);
   param.pmValue = (byte)Value;
	
	TCHAR_TO_WCHAR(m_profilePath, param.profilePath);
   return param;
}

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
		CRect   rect;   
		GetClientRect(&rect);   
		CDC   dcMem;   
		dcMem.CreateCompatibleDC(&dc);   
		CBitmap   bmpBackground;   
		bmpBackground.LoadBitmap(IDC_CONFIG);   
		BITMAP   bitmap;   
		bmpBackground.GetBitmap(&bitmap);   
		CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
		dc.StretchBlt(-83, -99, bitmap.bmWidth, bitmap.bmHeight, &dcMem, 
			0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);  
	}
}

BOOL CConfigurationDlg::OnInitDialog()
{
   CDialog::OnInitDialog();
   m_imageList[0] = IDB_BUTTONUP;
   m_imageList[1] = IDB_BUTTONDOWN;

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
         Array<DiPmintPort>* diPmintPort = instantDiCtrl->getDiPmintPorts();
         if (diPmintPort == NULL)
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
   return true;
}

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
   Array<DiPmintPort>* diPmintPorts = instantDiCtrl->getDiPmintPorts();
   int PmPortCount = diPmintPorts->getCount();
	m_comboBox_Port.ResetContent();
   int portNumber = 0;
   for (int i = 0; i < PmPortCount; ++i)
   {
      portNumber = diPmintPorts->getItem(i).getPort();
      CString portNum;
      portNum.Format(_T("%d"),portNumber);
      m_comboBox_Port.AddString(portNum);
      m_comboBox_Port.SetItemData(i,portNumber);
   }

   m_comboBox_Port.SetCurSel(0);
   OnSelchangePort();
   
   diPmintPorts->Dispose();
   instantDiCtrl->Dispose();
}

void CConfigurationDlg::OnSelchangePort()
{
   // TODO: 
   int selectedPort = (int)m_comboBox_Port.GetItemData(m_comboBox_Port.GetCurSel());

   InstantDiCtrl * instantDiCtrl = InstantDiCtrl::Create();
   CString des;
   m_comboBox_Device.GetLBText(m_comboBox_Device.GetCurSel(),des);
   wchar_t w_des[MAX_DEVICE_DESC_LEN];
   DeviceInformation devInfo( TCHAR_TO_WCHAR((LPCTSTR)des,  w_des) );
   instantDiCtrl->setSelectedDevice(devInfo);

   uint8 enabledChans = instantDiCtrl->getDiPmintPorts()->getItem(m_comboBox_Port.GetCurSel()).getMask();
   for ( int i = 0; i < 8; i++ )
   {
		int bitValue = enabledChans & (1 << (i));
		if ( 0 != bitValue )
		{ 
			showPicture(IDC_PIC0+i,1);
         m_enabledStatus[i] = 1;
		} 
      else
		{
			showPicture(IDC_PIC0+i,0);
         m_enabledStatus[i] = 0;
		}
   }
   //show the enabled value
   CString enableVal;
   enableVal.Format(_T("%X"),enabledChans);  
   GetDlgItem(IDC_PMCH)->SetWindowText(enableVal);
	
   //read the CFG_DiPmintValueOfPorts to initialize the PmValue status
   uint8 matchValue = instantDiCtrl->getDiPmintPorts()->getItem(m_comboBox_Port.GetCurSel()).getPattern();
   int bitValue = 0;
   for ( int j = 0; j < 8; j++ )
   {
      bitValue = matchValue & (1 << (j));
		if ( 0 != bitValue )
		{ 
			showPicture(IDC_PIC8+j,1);
         m_PmValueStatus[j] = 1;
         
		} 
		if ( 0 == bitValue )
		{
			showPicture(IDC_PIC8+j,0);
         m_PmValueStatus[j] = 0;
		}
   }

   instantDiCtrl->Dispose();

   //show the enabled value
	CString PmVal;
   PmVal.Format(_T("%X"),matchValue);  
   GetDlgItem(IDC_PMVALUE)->SetWindowText(PmVal);
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
	
	CString portVal;
   GetDlgItem(IDC_PMCH)->GetWindowText(portVal);
   long portData = _tcstol(portVal,NULL,16);
   if ( 0 == portData )
   {
      MessageBox(_T("Please enable at least one channel!"));
      return;
   }
   this->GetParent()->ShowWindow(SW_SHOW);
   this->GetParent()->EnableWindow(TRUE);
   this->ShowWindow(SW_HIDE);

   // Send message to configure the device selected.
   ::SendMessage(this->GetParent()->m_hWnd,WM_CUSTOME_CFG_CHGED,0,0);
   CDialog::OnOK();
	instantDiCtrl->Dispose();
}


void CConfigurationDlg::OnClick(UINT nID)
{
	int enableCh = 0;
	int pmValueCh = 0;
	if ( nID > IDC_PIC7)
	{
		pmValueCh = nID - IDC_PIC8;
		if( 0 == m_PmValueStatus[pmValueCh] )
		{
         showPicture(nID,1);
			m_PmValueStatus[pmValueCh] = 1;
		}
		else
		{		 
			if( 1 == m_PmValueStatus[pmValueCh] ) 
			{
				showPicture(nID,0);
				m_PmValueStatus[pmValueCh] = 0;
				
			}
		}
	}
	else
	{
		enableCh = nID - IDC_PIC0;
		if( 0 == m_enabledStatus[enableCh] )
		{
			showPicture(nID,1);
			m_enabledStatus[enableCh] = 1;
		}
		else
		{		 
			if( 1 == m_enabledStatus[enableCh] )
			{
				showPicture(nID,0);
				m_enabledStatus[enableCh] = 0;
			}
		}
	}
	
	byte enableData = 0;
	byte pmValue = 0;
	for (int i=0; i<8; i++)
	{	  
		if (m_enabledStatus[i] == 1)
		{
			enableData = (byte)(enableData | (1 << (i)));
		}
		if (m_PmValueStatus[i] == 1)
		{
			pmValue = (byte)(pmValue | (1 << (i)));
		}
	}
	
   //show the enable value
   CString enableVal;
   enableVal.Format(_T("%X"),enableData);  
   GetDlgItem(IDC_PMCH)->SetWindowText(enableVal);
	
	//show the pm value
	CString pmVal;
	pmVal.Format(_T("%X"),pmValue);  
	GetDlgItem(IDC_PMVALUE)->SetWindowText(pmVal);
}


void CConfigurationDlg::OnBnClickedCancel()
{
   // TODO: Add your control notification handler code here
   CString windowText;
   this->GetParent()->GetWindowText(windowText);
   if (!windowText.Compare(_T("DIPatternMatchInterrupt")))
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
