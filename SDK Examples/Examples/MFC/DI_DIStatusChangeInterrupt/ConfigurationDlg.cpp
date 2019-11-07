// ConfigureForm.cpp : implementation file
//

#include "stdafx.h"
#include "DIStatusChangeInterrupt.h"
#include "ConfigurationDlg.h"
#include <tchar.h>

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
			m_portStatus[i] = -1;
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
ON_STN_CLICKED(IDC_PIC0, OnClick)
ON_STN_CLICKED(IDC_PIC1,OnClick)
ON_STN_CLICKED(IDC_PIC2,OnClick)
ON_STN_CLICKED(IDC_PIC3,OnClick)
ON_STN_CLICKED(IDC_PIC4,OnClick)
ON_STN_CLICKED(IDC_PIC5,OnClick)
ON_STN_CLICKED(IDC_PIC6,OnClick)
ON_STN_CLICKED(IDC_PIC7,OnClick)
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
   CString portVal;
   GetDlgItem(IDC_PORTVALUE)->GetWindowText(portVal);
   long portData = _tcstol(portVal,NULL,16);
   param.enabledChannels = (byte)portData;
	
	TCHAR_TO_WCHAR(m_profilePath, param.profilePath);
   return param;
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
         Array<DiCosintPort>* diCosintPorts = instantDiCtrl->getDiCosintPorts();
         if (diCosintPorts == NULL)
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
   Array<DiCosintPort>* diCosintPorts = instantDiCtrl->getDiCosintPorts();
   int PmPortCount = diCosintPorts->getCount();
	m_comboBox_Port.ResetContent();
   int portNumber = 0;
   for (int i = 0; i < PmPortCount; ++i)
   {
      portNumber = diCosintPorts->getItem(i).getPort();
      CString portNum;
      portNum.Format(_T("%d"),portNumber);
      m_comboBox_Port.AddString(portNum);
      m_comboBox_Port.SetItemData(i,portNumber);
   }
   
   diCosintPorts->Dispose();
   instantDiCtrl->Dispose();

   m_comboBox_Port.SetCurSel(0);
   OnSelchangePort();
}

void CConfigurationDlg::OnSelchangePort()
{
   //read the CFG_DiPmintEnabledChannels to initialize the enabledChannel status
   InstantDiCtrl * instantDiCtrl = InstantDiCtrl::Create();
   CString des;
   m_comboBox_Device.GetLBText(m_comboBox_Device.GetCurSel(),des);
   wchar_t w_des[MAX_DEVICE_DESC_LEN];
   DeviceInformation devInfo( TCHAR_TO_WCHAR((LPCTSTR)des,  w_des) );
   instantDiCtrl->setSelectedDevice(devInfo);

   uint8 enabledChans = instantDiCtrl->getDiCosintPorts()->getItem(m_comboBox_Port.GetCurSel()).getMask();

   byte portData = 0;
   for ( int i = 0; i < 8; i++ )
   {
		int bitValue = enabledChans & (1 << (i));
		if ( 0 != bitValue )
		{ 
			CBitmap   bmp;   
			bmp.LoadBitmap(m_imageList[bitValue]); 
			((CStatic *)GetDlgItem(IDC_PIC0+i))->SetBitmap((HBITMAP)bmp); 
			bmp.Detach();
			CRect rc;
			GetDlgItem(IDC_PIC0+i)->GetClientRect(&rc);
			InvalidateRect(&rc,false);
			portData = (byte)(portData | (1 << (i)));
			m_portStatus[i] = 1;
		} 
      else
		{
			CBitmap   bmp;   
			bmp.LoadBitmap(m_imageList[bitValue]); 
			((CStatic *)GetDlgItem(IDC_PIC0+i))->SetBitmap((HBITMAP)bmp); 
			bmp.Detach();
			CRect rc;
			GetDlgItem(IDC_PIC0+i)->GetClientRect(&rc);
			InvalidateRect(&rc,false);
         m_portStatus[i] = 0;
		}
   }
   
   instantDiCtrl->Dispose();

   //show the value
   m_enableData = portData;
   CString portVal;
   portVal.Format(_T("%X"),portData);  
   GetDlgItem(IDC_PORTVALUE)->SetWindowText(portVal);
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
	CString portVal;
   GetDlgItem(IDC_PORTVALUE)->GetWindowText(portVal);
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
}

void CConfigurationDlg::OnClick()
{
	CPoint point; 
   GetCursorPos(&point); 
   byte portData = 0;  
	
   for (int i=0;i<8;i++)
   {   
		CRect rect;
		GetDlgItem(IDC_PIC0+i)->GetWindowRect(&rect);
		
      if(rect.PtInRect(point)) 
      { 
			if( 0 == m_portStatus[i])
			{
				CBitmap   bmp;   
				bmp.LoadBitmap(m_imageList[1]); 
				((CStatic *)GetDlgItem(IDC_PIC0+i))->SetBitmap((HBITMAP)bmp); 
				bmp.Detach();
				CRect rc;
				GetDlgItem(IDC_PIC0+i)->GetClientRect(&rc);
				InvalidateRect(&rc,false);
            m_portStatus[i] = 1;
			}
			else
			{		 
				if( 1 == m_portStatus[i])
				{
					CBitmap   bmp;   
					bmp.LoadBitmap(m_imageList[0]); 
					((CStatic *)GetDlgItem(IDC_PIC0+i))->SetBitmap((HBITMAP)bmp); 
					bmp.Detach();
					CRect rc;
					GetDlgItem(IDC_PIC0+i)->GetClientRect(&rc);
					InvalidateRect(&rc,false);
					m_portStatus[i] = 0;
				}
			}
      } 
		if (m_portStatus[i] == 1)
		{
			portData = (byte)(portData | (1 << (i)));
		}
   } 
   //show the value
   m_enableData = portData;
   CString portVal;
   portVal.Format(_T("%X"),portData);  
   GetDlgItem(IDC_PORTVALUE)->SetWindowText(portVal);
}

void CConfigurationDlg::OnBnClickedCancel()
{
   // TODO: Add your control notification handler code here
   CString windowText;
   this->GetParent()->GetWindowText(windowText);
   if (!windowText.Compare(_T("DIStatusChangeInterrupt")))
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
