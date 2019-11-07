// ConfigForm.cpp : implementation file
//

#include "stdafx.h"
#include "BufferedPulseWidthMeasurement.h"
#include "ConfigurationDlg.h"
#include <tchar.h>

#define MAX_COUNTER_COUNT   8
#define Profile_Confiugre   1
#define Manual_Configure    0

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
   m_sectionLength = 1024;
   m_sectionCount = 0;
   m_trgLevel = 3.0;
   m_configureMode = 0; //Profile configure == 1; ManualConfigure == 0;
}

CConfigurationDlg::~CConfigurationDlg()
{
}

DevConfParam CConfigurationDlg::GetParameter()
{
   DevConfParam param;
   param.deviceNumber   = (int)m_cbx_device.GetItemData(m_cbx_device.GetCurSel());
   param.sectionLength  = m_sectionLength;
   param.sectionCount   = m_sectionCount;
   param.clkSource      = (SignalDrop)m_cbx_clkSrc.GetItemData(m_cbx_clkSrc.GetCurSel());
	TCHAR_TO_WCHAR(m_profilePath, param.profilePath);

   param.trgAction = (TriggerAction)(m_cbx_trgAct.GetCurSel() + 1);
   param.trgEdge   = (ActiveSignal)m_cbx_trgEdge.GetItemData(m_cbx_trgEdge.GetCurSel());
   param.trgSource = (SignalDrop)m_cbx_trgSrc.GetItemData(m_cbx_trgSrc.GetCurSel());
   param.trgLevel  = m_trgLevel;
   UpdateData();

   param.configureMode = m_configureMode;
   param.channelEnable = new int8[m_channelCountMax];
   memcpy(param.channelEnable, m_channelEnable, sizeof(int8) * m_channelCountMax);

   return param;
}

void CConfigurationDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_Device, m_cbx_device);
   DDX_Control(pDX, IDC_CBX_ClkSrc, m_cbx_clkSrc);
   DDX_Text(pDX, IDC_EDIT_SectionCount, m_sectionCount);

   //for trigger
   DDX_Control(pDX, IDC_CBX_TrgSrc, m_cbx_trgSrc);
   DDX_Control(pDX, IDC_CBX_TrgAct, m_cbx_trgAct);
   DDX_Control(pDX, IDC_CBX_TrgEdge, m_cbx_trgEdge);
   DDX_Text(pDX, IDC_EDIT_TrgLevel, m_trgLevel);
   DDX_Text(pDX, IDC_EDIT_SectionLength, m_sectionLength);
}

BEGIN_MESSAGE_MAP(CConfigurationDlg, CDialog)
   //{{AFX_MSG_MAP(CConfigForm)
   ON_BN_CLICKED(IDOK, OnBnClickedOk)
   ON_CBN_SELCHANGE(IDC_Device, OnCbnSelchangeComboDevice)
   ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
   ON_WM_CLOSE()
   //}}AFX_MSG_MAP
   
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnBnClickedButtonBrowse)
   ON_CBN_SELCHANGE(IDC_CBX_TrgSrc, OnCbnSelchangeCbxTrgsrc)

   // for Channel Enabled
   ON_CONTROL_RANGE(BN_CLICKED, IDC_CHK0, IDC_CHK7, OnBnClickedChk)
   ON_BN_CLICKED(IDC_RADIOProfile, OnBnClickedRadio)
   ON_BN_CLICKED(IDC_RADIOManual, OnBnClickedRadio)
END_MESSAGE_MAP()

BOOL CConfigurationDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   // create available device list.
   BufferedPwMeterCtrl* bfdPwMeterCtrl = BufferedPwMeterCtrl::Create();
   Array<DeviceTreeNode>* sptedDevices = bfdPwMeterCtrl->getSupportedDevices();

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
         m_cbx_device.AddString(WCHAR_TO_TCHAR(node.Description,des));
         m_cbx_device.SetItemData(i,node.DeviceNumber);
      }
      sptedDevices->Dispose();
   }
   bfdPwMeterCtrl->Dispose();
   m_cbx_device.SetCurSel(0);
   OnCbnSelchangeComboDevice();
   return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//This function is used to handle the errorCode information
void CConfigurationDlg::CheckError(ErrorCode errorCode)
{
   if (BioFailed(errorCode))
   {
      CString str;
      str.Format(_T("Some errors happened, the error code is:0x%x"), errorCode);
      AfxMessageBox(str);
   }
}

void CConfigurationDlg::OnCbnSelchangeComboDevice()
{
   // TODO: Add your control notification handler code here
   BufferedPwMeterCtrl* bfdPwMeterCtrl = BufferedPwMeterCtrl::Create();

   // Get current selected device from device combo box
   CString des;
   m_cbx_device.GetLBText(m_cbx_device.GetCurSel(),des);
   wchar_t w_des[MAX_DEVICE_DESC_LEN];
   DeviceInformation devInfo( TCHAR_TO_WCHAR((LPCTSTR)des,  w_des) );
   ErrorCode errorCode = bfdPwMeterCtrl->setSelectedDevice(devInfo);
   GetDlgItem(IDOK)->EnableWindow(TRUE);
   if (errorCode != 0){
      CString str;
      str.Format(_T("Error: the error code is 0x%x, The %s is busy or not exit in computer now.\n\
 Select other device please!"),errorCode,des);
      AfxMessageBox(str);
      GetDlgItem(IDOK)->EnableWindow(FALSE);
      return;}

   //initial channel enable
   m_channelCountMax = bfdPwMeterCtrl->getFeatures()->getChannelCountMax();
   m_channelEnable = new int8[m_channelCountMax];
   memset(m_channelEnable, 0, sizeof(int8) * m_channelCountMax);
   
   //Default using Manual Configure
   ((CButton*)GetDlgItem(IDC_RADIOManual))->SetCheck(TRUE);
   OnBnClickedRadio();
   InitialChkBox();

   m_sectionCount = 0;
   m_sectionLength = 1024;

   //Set sample clock source combo box
   if (m_cbx_clkSrc.GetCount() > 0){
      m_cbx_clkSrc.ResetContent();
   }
   CString str;
   CounterClockSourceIndexer* indexer = bfdPwMeterCtrl->getFeatures()->getPiSampleClockSources();
   for (int i = 0; i < indexer->getItem(0)->getCount(); i++)
   {
      SignalDrop  clkSrc = indexer->getItem(0)->getItem(i);
      wchar_t enumStr[MAX_SIG_DROP_DESC_LEN];
      errorCode = AdxEnumToString(L"SignalDrop", clkSrc, MAX_SIG_DROP_DESC_LEN, enumStr);
      CheckError(errorCode);
      str = enumStr;
      m_cbx_clkSrc.AddString(str);
      TRACE("\nsource[%d], value[%d]\n", i, (int)clkSrc);
      m_cbx_clkSrc.SetItemData(i, (int)clkSrc);
   }
   m_cbx_clkSrc.SetCurSel(0);

   //Set trigger function layout
   Array<SignalDrop>* trgSrc = bfdPwMeterCtrl->getFeatures()->getTriggerSources();
   for (int i = 0; i < trgSrc->getCount(); i++)
   {
      wchar_t enumStr[MAX_SIG_DROP_DESC_LEN];
      errorCode = AdxEnumToString(L"SignalDrop", trgSrc->getItem(i), MAX_SIG_DROP_DESC_LEN, enumStr);
      CheckError(errorCode);
      str = enumStr;
      m_cbx_trgSrc.AddString(str);
      TRACE("\nsource[%d], value[%d]\n", i, (int)trgSrc->getItem(i));
      m_cbx_trgSrc.SetItemData(i, (int)trgSrc->getItem(i));
   }
   m_cbx_trgSrc.SetCurSel(0);

   Array<TriggerAction>*trgAct = bfdPwMeterCtrl->getFeatures()->getTriggerActions();
   for (int i = 0; i < trgAct->getCount(); i++)
   {
      wchar_t enumStr[MAX_SIG_DROP_DESC_LEN];
      errorCode = AdxEnumToString(L"TriggerAction", trgAct->getItem(i), MAX_SIG_DROP_DESC_LEN, enumStr);
      CheckError(errorCode);
      str = enumStr;
      m_cbx_trgAct.AddString(str);
      TRACE("\nsource[%d], value[%d]\n", i, (int)trgAct->getItem(i));
      m_cbx_trgAct.SetItemData(i, (int)trgAct->getItem(i));
   }
   m_cbx_trgAct.SetCurSel(0);

   m_cbx_trgEdge.AddString(_T("RisingEdge"));
   m_cbx_trgEdge.SetItemData(0,(int)RisingEdge);
   m_cbx_trgEdge.AddString(_T("FallingEdge"));
   m_cbx_trgEdge.SetItemData(1,(int)FallingEdge);
   m_cbx_trgEdge.SetCurSel(0);

   bfdPwMeterCtrl->Dispose();
   OnCbnSelchangeCbxTrgsrc();
   UpdateData(FALSE);
}

void CConfigurationDlg::OnBnClickedOk() 
{
   UpdateData(TRUE);
   if (m_trgLevel > 10 || m_trgLevel < -10)
   {
      AfxMessageBox(_T(" 'trigger level' is out of range \"-10v ~ 10v \""));
      return;
   }

   CString str;
   GetDlgItem(IDC_EDIT_PROFILE)->GetWindowText(str);
   if(m_configureMode == Profile_Confiugre){
      if (str.IsEmpty()){
         AfxMessageBox(_T("Sorry, profile path is null, please select the device's profile"));
      } else{
         // TODO: Add extra validation here
         this->GetParent()->ShowWindow(SW_SHOW);
         this->GetParent()->EnableWindow(TRUE);
         this->ShowWindow(SW_HIDE);

         // Send message to configure the device selected.
         ::SendMessage(this->GetParent()->m_hWnd,WM_CUSTOME_CFG_CHGED,0,0);
         CDialog::OnOK();
      }
   }else{
      int sum = 0;
      for (int i = 0; i < m_channelCountMax; ++i){
         sum |= m_channelEnable[i];
      }

      if(sum){
         // TODO: Add extra validation here
         this->GetParent()->ShowWindow(SW_SHOW);
         this->GetParent()->EnableWindow(TRUE);
         this->ShowWindow(SW_HIDE);

         // Send message to configure the device selected.
         ::SendMessage(this->GetParent()->m_hWnd,WM_CUSTOME_CFG_CHGED,0,0);
         CDialog::OnOK();
      }else{
         AfxMessageBox(_T("Please enable at least one channel!")); 
      }
   }
}

void CConfigurationDlg::OnBnClickedCancel()
{
   // TODO: Add your control notification handler code here
   CString windowText;
   this->GetParent()->GetWindowText(windowText);
   if (!windowText.Compare(_T("Counter_BufferedPulseWidthMeasurement")))
   {
      ::SendMessage(this->GetParent()->m_hWnd,WM_CUSTOME_CFG_CHGED,1,0);
      this->CloseWindow();
   } 
   OnCancel();
}

void CConfigurationDlg::OnClose()
{
   // TODO: Add your message handler code here and/or call default
   if ( m_cbx_device.GetCount() <= 0)
   {
      PostQuitMessage(0);
   }
   CDialog::OnClose();
}

void CConfigurationDlg::OnBnClickedButtonBrowse()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, _T("xml"), _T(""), OFN_OVERWRITEPROMPT, _T("Licence File(*.xml)|*.xml||"));
   dlg.m_ofn.lpstrInitialDir = _T("c:\\");  
	if(dlg.DoModal() == IDOK)
	{
		m_profilePath = dlg.GetPathName();
		GetDlgItem(IDC_EDIT_PROFILE)->SetWindowText(m_profilePath);
	} 
}

void CConfigurationDlg::OnCbnSelchangeCbxTrgsrc()
{
   // TODO: Add your control notification handler code here
   BufferedPwMeterCtrl* bfdPwMeterCtrl = BufferedPwMeterCtrl::Create();
   // Get current selected device from device combo box
   CString des;
   m_cbx_device.GetLBText(m_cbx_device.GetCurSel(),des);
   wchar_t w_des[MAX_DEVICE_DESC_LEN];
   DeviceInformation devInfo( TCHAR_TO_WCHAR((LPCTSTR)des,  w_des) );
   bfdPwMeterCtrl->setSelectedDevice(devInfo);

   if (bfdPwMeterCtrl->getTrigger()){
      SignalDrop trgSrc = (SignalDrop)m_cbx_trgSrc.GetItemData(m_cbx_trgSrc.GetCurSel());

      switch (trgSrc)
      {
      case SignalNone:
         ((CWnd*)GetDlgItem(IDC_CBX_TrgAct))->EnableWindow(FALSE);
         ((CWnd*)GetDlgItem(IDC_CBX_TrgEdge))->EnableWindow(FALSE);
         ((CWnd*)GetDlgItem(IDC_EDIT_TrgLevel))->EnableWindow(FALSE);
         break;
      case SigDiPatternMatch:
      case SigDiStatusChange:
         ((CWnd*)GetDlgItem(IDC_CBX_TrgAct))->EnableWindow(TRUE);
         ((CWnd*)GetDlgItem(IDC_CBX_TrgEdge))->EnableWindow(FALSE);
         ((CWnd*)GetDlgItem(IDC_EDIT_TrgLevel))->EnableWindow(FALSE);
         break;
      default:
         ((CWnd*)GetDlgItem(IDC_CBX_TrgAct))->EnableWindow(TRUE);
         ((CWnd*)GetDlgItem(IDC_CBX_TrgEdge))->EnableWindow(TRUE);
         ((CWnd*)GetDlgItem(IDC_EDIT_TrgLevel))->EnableWindow(TRUE);
         break;
      }
   }
   bfdPwMeterCtrl->Dispose();
}

void CConfigurationDlg::OnBnClickedRadio()
{
   // TODO: Add your control notification handler code here
   if (((CButton*)GetDlgItem(IDC_RADIOProfile))->GetCheck()){
      m_configureMode = Profile_Confiugre;
   } 
   if (((CButton*)GetDlgItem(IDC_RADIOManual))->GetCheck()){
      m_configureMode = Manual_Configure;
   }
   ComponentEnabled(m_configureMode);
}

void CConfigurationDlg::OnBnClickedChk(UINT nID)
{
   TRACE("nID[%d]\n", nID);
   // TODO: Add your control notification handler code here
   int32 index = nID - IDC_CHK0;  
   if(((CButton*)GetDlgItem(nID))->GetCheck()){
      m_channelEnable[index] = 1;
   }else{
      m_channelEnable[index] = 0;
   }
   TRACE("m_channelEnable[%d]== %d\n", index, m_channelEnable[index]);
}

void CConfigurationDlg::ComponentEnabled(bool flag)
{
   if (flag){
      ((CWnd*)GetDlgItem(IDC_EDIT_PROFILE))->EnableWindow(TRUE);
      ((CWnd*)GetDlgItem(IDC_BUTTON_BROWSE))->EnableWindow(TRUE);

      for(int32 i = 0; i < m_channelCountMax; i++){
         ((CWnd*)GetDlgItem(IDC_CHK0 + i))->EnableWindow(FALSE);
      }
      ((CWnd*)GetDlgItem(IDC_EDIT_SectionLength))->EnableWindow(FALSE);
      ((CWnd*)GetDlgItem(IDC_EDIT_SectionCount))->EnableWindow(FALSE);
      ((CWnd*)GetDlgItem(IDC_CBX_ClkSrc))->EnableWindow(FALSE);

      ((CWnd*)GetDlgItem(IDC_CBX_TrgSrc))->EnableWindow(FALSE);
      OnCbnSelchangeCbxTrgsrc();
   } else{
      ((CWnd*)GetDlgItem(IDC_EDIT_PROFILE))->EnableWindow(FALSE);
      ((CWnd*)GetDlgItem(IDC_BUTTON_BROWSE))->EnableWindow(FALSE);

      for(int32 i = 0; i < m_channelCountMax; i++){
         ((CWnd*)GetDlgItem(IDC_CHK0 + i))->EnableWindow(TRUE);
      }

      ((CWnd*)GetDlgItem(IDC_EDIT_SectionLength))->EnableWindow(TRUE);
      ((CWnd*)GetDlgItem(IDC_EDIT_SectionCount))->EnableWindow(TRUE);
      ((CWnd*)GetDlgItem(IDC_CBX_ClkSrc))->EnableWindow(TRUE);

      ((CWnd*)GetDlgItem(IDC_CBX_TrgSrc))->EnableWindow(TRUE);
      OnCbnSelchangeCbxTrgsrc();
   }
}


void CConfigurationDlg::InitialChkBox()
{
   for(int32 i = 0; i < MAX_COUNTER_COUNT; i++){
      GetDlgItem(IDC_CHK0 + i)->ShowWindow(SW_HIDE);
   }

   for(int32 i = 0; i < m_channelCountMax; i++){
      GetDlgItem(IDC_CHK0 + i)->ShowWindow(SW_SHOW);
      if(m_channelEnable[i]){
         ((CButton*)GetDlgItem(IDC_CHK0 + i))->SetCheck(BST_CHECKED);   
      }else{
         ((CButton*)GetDlgItem(IDC_CHK0 + i))->SetCheck(BST_UNCHECKED);   
      }
   }
}