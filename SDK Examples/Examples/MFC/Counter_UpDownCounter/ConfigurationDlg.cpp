// ConfigForm.cpp : implementation file
//

#include "stdafx.h"
#include "UpDownCounter.h"
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
// CConfigForm dialog

IMPLEMENT_DYNAMIC(CConfigurationDlg, CDialog)

CConfigurationDlg::CConfigurationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigurationDlg::IDD, pParent)
{
   // Initialize data member of configForm class.
}

CConfigurationDlg::~CConfigurationDlg()
{
}

DevConfParam CConfigurationDlg::GetParameter()
{
   DevConfParam param;
   param.deviceNumber = (int)m_comboBox_Device.GetItemData(m_comboBox_Device.GetCurSel());
   param.channel = (int)m_comboBox_counterChan.GetItemData(m_comboBox_counterChan.GetCurSel());
   param.cntType = (CountingType)m_comboBox_countingType.GetItemData(m_comboBox_countingType.GetCurSel());
	TCHAR_TO_WCHAR(m_profilePath, param.profilePath);
   return param;
}

void CConfigurationDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_Device, m_comboBox_Device);
   DDX_Control(pDX, IDC_CounterChannel, m_comboBox_counterChan);
   DDX_Control(pDX, IDC_COMBO_COUNTING_TPYE, m_comboBox_countingType);
}

BEGIN_MESSAGE_MAP(CConfigurationDlg, CDialog)
   //{{AFX_MSG_MAP(CConfigForm)
   ON_BN_CLICKED(IDOK, OnBnClickedOk)
   ON_CBN_SELCHANGE(IDC_Device, OnCbnSelchangeComboDevice)
   ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
   ON_WM_CLOSE()
   //}}AFX_MSG_MAP
   
	ON_BN_CLICKED(IDBROWSE, OnBnClickedBrowse)
END_MESSAGE_MAP()

BOOL CConfigurationDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   // create available device list.
   UdCounterCtrl* udCounterCtrl = UdCounterCtrl::Create();
   Array<DeviceTreeNode>* sptedDevices = udCounterCtrl->getSupportedDevices();

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
   udCounterCtrl->Dispose();
   m_comboBox_Device.SetCurSel(0);
   OnCbnSelchangeComboDevice();
   return TRUE;
}

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

void CConfigurationDlg::OnCbnSelchangeComboDevice()
{
   // TODO: Add your control notification handler code here
   UdCounterCtrl* udCounterCtrl = UdCounterCtrl::Create();
   // Clear the context of combo box for parameters
   m_comboBox_counterChan.ResetContent();
   // Get current selected device from device combo box
   CString des;
   m_comboBox_Device.GetLBText(m_comboBox_Device.GetCurSel(),des);
   wchar_t w_des[MAX_DEVICE_DESC_LEN];
   DeviceInformation devInfo( TCHAR_TO_WCHAR((LPCTSTR)des,  w_des) );
   ErrorCode errorCode = udCounterCtrl->setSelectedDevice(devInfo);
   GetDlgItem(IDOK)->EnableWindow(TRUE);
   if (errorCode != 0){
      CString str;
      str.Format(_T("Error: the error code is 0x%x, The %s is busy or not exit in computer now.\n\
 Select other device please!"),errorCode,des);
      AfxMessageBox(str);
      GetDlgItem(IDOK)->EnableWindow(FALSE);
      return;}
   // Set channel start combo box
   int channelCountMax = udCounterCtrl->getFeatures()->getChannelCountMax();
   Array<CounterCapability> * counterCap ;
   int itemCount;
   int counterChanIndex = 0;
   for (int i = 0; i < channelCountMax; i++)
   {
      itemCount = udCounterCtrl->getFeatures()->getCapabilities()->getItem(i)->getCount();
      counterCap = udCounterCtrl->getFeatures()->getCapabilities()->getItem(i);
      for (int j = 0; j < itemCount; ++j )
      {
         if ( UpDownCount == counterCap->getItem(j))
         {
            CString str ;
            str.Format(_T("%d"),i);
            m_comboBox_counterChan.AddString(str);
            m_comboBox_counterChan.SetItemData(counterChanIndex++,i);
         }
      }
   }
   m_comboBox_counterChan.SetCurSel(0);

   // Set Counting type for selected device
   int cntTypeCount = udCounterCtrl->getFeatures()->getUdCountingTypes()->getCount();
   Array<CountingType> * counttingType = udCounterCtrl->getFeatures()->getUdCountingTypes();
   WCHAR strType[64] = {0};
	TCHAR tstrType[64] = {0};
   for (int k = 0; k < cntTypeCount; ++k)
   {
      AdxEnumToString(L"CountingType",counttingType->getItem(k),64,strType);
		WCHAR_TO_TCHAR(strType, tstrType);
      m_comboBox_countingType.AddString(tstrType);
      m_comboBox_countingType.SetItemData(k,counttingType->getItem(k));
   }
   m_comboBox_countingType.SetCurSel(0);
   udCounterCtrl->Dispose();
}

void CConfigurationDlg::OnBnClickedOk() 
{
	// TODO: Add extra validation here
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
   if (!windowText.Compare(_T("Counter_UpDownCounter")))
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
