// ConfigForm.cpp : implementation file
//

#include "stdafx.h"
#include "FrequencyMeasurement.h"
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
// CConfigurationDlg dialog

IMPLEMENT_DYNAMIC(CConfigurationDlg, CDialog)

CConfigurationDlg::CConfigurationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigurationDlg::IDD, pParent)
{
   // Initialize data member of configForm class.
}

CConfigurationDlg::~CConfigurationDlg()
{}

DevConfParam CConfigurationDlg::GetParameter()
{
   DevConfParam param;
   param.deviceNumber = (int)m_comboBox_Device.GetItemData(m_comboBox_Device.GetCurSel());
   param.channel = (int)m_comboBox_counterChan.GetItemData(m_comboBox_counterChan.GetCurSel());
	TCHAR_TO_WCHAR(m_profilePath, param.profilePath);

   return param;
}

BOOL CConfigurationDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   // create available device list.
   FreqMeterCtrl* freqMeterCtrl = FreqMeterCtrl::Create();
   Array<DeviceTreeNode>* sptedDevices = freqMeterCtrl->getSupportedDevices();

   if (sptedDevices->getCount() == 0)
   {
      GetDlgItem(IDOK)->EnableWindow(FALSE);
      GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
      AfxMessageBox(_T("No device to support the currently demonstrated function!"));
      return FALSE;
   }else{
      for (int i = 0; i < sptedDevices->getCount(); ++i)
      {
         DeviceTreeNode const & node = sptedDevices->getItem(i);
         TRACE("%d, %s\n", node.DeviceNumber, node.Description);
         TCHAR des[MAX_DEVICE_DESC_LEN];
         m_comboBox_Device.AddString(WCHAR_TO_TCHAR(node.Description,des));
         m_comboBox_Device.SetItemData(i,node.DeviceNumber);
      }
      sptedDevices->Dispose();
   }
   freqMeterCtrl->Dispose();
   m_comboBox_Device.SetCurSel(0);
   OnCbnSelchangeComboDevice();
   return TRUE;
}

void CConfigurationDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_Device, m_comboBox_Device);
   DDX_Control(pDX, IDC_COMBO_CHANNEL,m_comboBox_counterChan);
}

BEGIN_MESSAGE_MAP(CConfigurationDlg, CDialog)
   //{{AFX_MSG_MAP(CConfigurationDlg)
   ON_BN_CLICKED(IDOK, OnBnClickedOk)
   ON_CBN_SELCHANGE(IDC_Device, OnCbnSelchangeComboDevice)
   ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
   ON_WM_CLOSE()
   //}}AFX_MSG_MAP
    
	ON_BN_CLICKED(IDBROWSE, OnBnClickedBrowse)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
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
// CConfigurationDlg message handlers
void CConfigurationDlg::OnCbnSelchangeComboDevice()
{
   // TODO: Add your control notification handler code here
   FreqMeterCtrl* freqMeterCtrl = FreqMeterCtrl::Create();
   // Get current selected device from device combo box
   CString des;
   m_comboBox_Device.GetLBText(m_comboBox_Device.GetCurSel(),des);
   wchar_t w_des[MAX_DEVICE_DESC_LEN];
   DeviceInformation devInfo(TCHAR_TO_WCHAR((LPCTSTR)des,  w_des));
   ErrorCode errorCode = freqMeterCtrl->setSelectedDevice(devInfo);
   GetDlgItem(IDOK)->EnableWindow(TRUE);
   if (errorCode != 0){
      CString str;
      str.Format(_T("Error: the error code is 0x%x, The %s is busy or not exit in computer now.\n\
 Select other device please!"),errorCode,des);
      AfxMessageBox(str);
      GetDlgItem(IDOK)->EnableWindow(FALSE);
      return;}
   // Set channel start combo box
   int channelCountMax = freqMeterCtrl->getFeatures()->getChannelCountMax();
   Array<CounterCapability> * counterCap ;
   int itemCount;
   int counterChanIndex = 0;
	m_comboBox_counterChan.ResetContent();
   for (int i = 0; i < channelCountMax; i++)
   {
      itemCount = freqMeterCtrl->getFeatures()->getCapabilities()->getItem(i)->getCount();
      counterCap = freqMeterCtrl->getFeatures()->getCapabilities()->getItem(i);
      for (int j = 0; j < itemCount; ++j )
      {
         if ( InstantFreqMeter == counterCap->getItem(j))
         {
            CString str ;
            str.Format(_T("%d"),i);
            m_comboBox_counterChan.AddString(str);
            m_comboBox_counterChan.SetItemData(counterChanIndex++,i);
         }
      }
   }

  freqMeterCtrl->Dispose();
  m_comboBox_counterChan.SetCurSel(0);
}

void CConfigurationDlg::OnBnClickedOk() 
{
   // TODO: Add extra validation here
   if (m_comboBox_counterChan.GetCount() == 0)
   {
      AfxMessageBox(_T("No item is selected!\n Please select at least one counter channel"));
      return;
   }
   this->GetParent()->ShowWindow(SW_SHOW);
   this->GetParent()->EnableWindow(TRUE);
   this->ShowWindow(SW_HIDE);

   // Send message to configure the device selected.
   ::SendMessage(this->GetParent()->m_hWnd,WM_CUSTOME_CFG_CHGED,0,0);
   CDialog::OnOK();
}


void CConfigurationDlg::OnBnClickedCancel()
{
   // TODO: Add your control notification handler code here
   CString windowText;
   this->GetParent()->GetWindowText(windowText);
   if (!windowText.Compare(_T("Counter_FrequencyMeasurement")))
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
