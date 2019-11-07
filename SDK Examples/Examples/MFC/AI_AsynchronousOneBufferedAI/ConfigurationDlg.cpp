// Configuration.cpp : implementation file
//

#include "stdafx.h"
#include "AsynchronousOneBufferedAI.h"
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
// CConfiguration dialog

IMPLEMENT_DYNAMIC(CConfigurationDlg, CDialog)

DevConfParam CConfigurationDlg::GetParameter()
{
   DevConfParam param;
   param.deviceNumber = (int)m_comboBox_Device.GetItemData(m_comboBox_Device.GetCurSel());
   param.channelCount = m_comboBox_ChannelCount.GetCurSel() + 1;
   param.channelStart = m_comboBox_ChannelStart.GetCurSel();
   param.vrgType = (int)m_comboBox_ValueRange.GetItemData(m_comboBox_ValueRange.GetCurSel());
	TCHAR_TO_WCHAR(m_profilePath, param.profilePath);
	param.sectionLength = m_sectionLength;
   param.clockRatePerChan = m_clockRatePerChan;
   return param;
}

CConfigurationDlg::CConfigurationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigurationDlg::IDD, pParent)
{
	m_sectionLength = 1024;
	m_clockRatePerChan = 1000;
}

CConfigurationDlg::~CConfigurationDlg()
{
}

void CConfigurationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DEVICE, m_comboBox_Device);
	DDX_Control(pDX, IDC_COMBO_CHANSTART, m_comboBox_ChannelStart);
	DDX_Control(pDX, IDC_COMBO_CHANCOUNT, m_comboBox_ChannelCount);
	DDX_Control(pDX, IDC_COMBO_VALUERANGE, m_comboBox_ValueRange);
	DDX_Text(pDX, IDC_EDIT_SECTIONLENGTH, m_sectionLength);
	DDX_Text(pDX, IDC_EDIT_CLOCKRATEPERCHAN, m_clockRatePerChan);
}

BEGIN_MESSAGE_MAP(CConfigurationDlg, CDialog)
   //{{AFX_MSG_MAP(CConfigurationDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICE, OnCbnSelchangeComboDevice)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CLOSE()
   //}}AFX_MSG_MAP
	ON_BN_CLICKED(IDBROWSE, OnBnClickedBrowse)
END_MESSAGE_MAP()

BOOL CConfigurationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

   WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl::Create();
   Array<DeviceTreeNode>* sptedDevices = wfAiCtrl ->getSupportedDevices();

   int deviceCount = sptedDevices->getCount();
   if (deviceCount == 0)
   {
      GetDlgItem(IDOK)->EnableWindow(FALSE);
      GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
      AfxMessageBox(_T("No device to support the currently demonstrated function!"));
      return FALSE;
   }else{
      for (int i = 0; i < deviceCount; ++i)
      {
         DeviceTreeNode const & node = sptedDevices->getItem(i);
         TRACE(_T("%d, %s\n"), node.DeviceNumber, node.Description);
		   TCHAR des[MAX_DEVICE_DESC_LEN];
         m_comboBox_Device.AddString(WCHAR_TO_TCHAR(node.Description,des));
         m_comboBox_Device.SetItemData(i,node.DeviceNumber);
      }
      m_comboBox_Device.SetCurSel(0);
      OnCbnSelchangeComboDevice();
   }
   sptedDevices->Dispose();
   wfAiCtrl ->Dispose();
   
	return TRUE;  // return TRUE unless you set the focus to a control
}
void CConfigurationDlg::CheckError(ErrorCode errorCode)
{
	if (errorCode != Success)
	{
		CString str;
      str.Format( _T("Some errors happened, the error code is: 0x%X !"),errorCode);
		AfxMessageBox(str);
	}

}
// CConfiguration message handlers

void CConfigurationDlg::OnCbnSelchangeComboDevice()
{  
   ErrorCode		 errorCode;
   WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl::Create();

   // Clear the context of combo box for parameters
   m_comboBox_ChannelCount.ResetContent();
   m_comboBox_ChannelStart.ResetContent();
   m_comboBox_ValueRange.ResetContent();

   // Get current selected device from device combo box
   CString des;
   m_comboBox_Device.GetLBText(m_comboBox_Device.GetCurSel(),des);
   wchar_t w_des[MAX_DEVICE_DESC_LEN];
   DeviceInformation devInfo( TCHAR_TO_WCHAR((LPCTSTR)des,  w_des) );

   errorCode = Success;
	errorCode = wfAiCtrl->setSelectedDevice(devInfo);
   GetDlgItem(IDOK)->EnableWindow(TRUE);
   if (errorCode != 0){
      CString str;
      str.Format(_T("Error: the error code is 0x%x, The %s is busy or not exit in computer now.\n\
 Select other device please!"),errorCode,des);
      AfxMessageBox(str);
      GetDlgItem(IDOK)->EnableWindow(FALSE);
      return;}
   // Set channel start combo box
   int logicChannelCount = wfAiCtrl->getChannelCount();
   int channelCountMax = wfAiCtrl->getFeatures()->getChannelCountMax();
   int32 i = 0;
   for (i = 0; i < channelCountMax; i++)
   {
      CString str ;
      str.Format(_T("%d"),i);
      m_comboBox_ChannelStart.AddString(str);
   }

   // Set channel count combo box
   int channelCount = (logicChannelCount < 16)? logicChannelCount:16;
   for (i = 1; i < channelCount + 1; i++)
   {
      CString str ;
      str.Format(_T("%d"),i);
      m_comboBox_ChannelCount.AddString(str);
   }

   // Set value range combo box
   Array<ValueRange>* ValueRanges = wfAiCtrl->getFeatures()->getValueRanges();
   WCHAR	vrgDescription[128];
   MathInterval	ranges;
   ValueUnit    u = Volt;
   for (i = 0; i < ValueRanges->getCount() ; i++)
   {
      errorCode = AdxGetValueRangeInformation((ValueRanges->getItem(i)), sizeof(vrgDescription), vrgDescription, &ranges, &u);
      CheckError(errorCode);
	  if (u == CelsiusUnit)
	  {
		  continue;
	  }
      CString str = vrgDescription;
      m_comboBox_ValueRange.AddString(str);
      m_comboBox_ValueRange.SetItemData(i,(int)ValueRanges->getItem(i));
   }

   // Set default parameters 
	m_comboBox_ChannelStart.SetCurSel(0);
	m_comboBox_ChannelCount.SetCurSel(1);
	m_comboBox_ValueRange.SetCurSel(0);
	m_sectionLength = 1024;
	m_clockRatePerChan = 1000.0;
   wfAiCtrl->Dispose();
	UpdateData(FALSE);
}

void CConfigurationDlg::OnBnClickedOk()
{
	UpdateData();
   
	if (m_comboBox_Device.GetCount() == 0)
	{
		PostQuitMessage(0);
	}

   WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl::Create();
	// Get current selected device from device combo box
	CString des;
	m_comboBox_Device.GetLBText(m_comboBox_Device.GetCurSel(),des);
	wchar_t w_des[MAX_DEVICE_DESC_LEN];
	DeviceInformation devInfo( TCHAR_TO_WCHAR((LPCTSTR)des,  w_des) );
	
	wfAiCtrl->setSelectedDevice(devInfo);
	MathInterval rateRange;
   wfAiCtrl->getFeatures()->getConvertClockRange(rateRange);

	if (m_clockRatePerChan > rateRange.Max || m_clockRatePerChan < rateRange.Min)
	{
		CString str(_T("Error: 'convert clock rate per channel' is out of range! \nConvert clock rate range is "));
		CString range;
		range.Format(_T("%f - %f"),rateRange.Min, rateRange.Max);
		CString sError( str + range );   
		AfxMessageBox(sError);
		return;
	}

	int channelCount = m_comboBox_ChannelCount.GetCurSel() + 1;
	int32 aa = wfAiCtrl->getFeatures()->getDataSize();
	int  BufferCountMax = (BufferMaxSize / wfAiCtrl->getFeatures()->getDataSize()) / channelCount;

	if (m_sectionLength < 1 || m_sectionLength > BufferCountMax)
	{
		CString str(_T("Error: 'samples per channel' is out of range! \nSamples range is "));
		CString range;
		range.Format(_T("%d - %d"), 1, BufferCountMax);
		CString sError( str + range );   
		AfxMessageBox(sError);
		return;
	}

	this->GetParent()->ShowWindow(SW_SHOW);
   this->GetParent()->EnableWindow(TRUE);
   this->ShowWindow(SW_HIDE);
	UpdateData(TRUE);

   // Send message to configure the device selected.
   ::SendMessage(this->GetParent()->m_hWnd,WM_CUSTOME_CFG_CHGED,0,0);
	OnOK();
	wfAiCtrl->Dispose();
}

void CConfigurationDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
   CString windowText;
   this->GetParent()->GetWindowText(windowText);
   if (!windowText.Compare(_T("Asynchronous One Buffered AI")))
   {
      ::SendMessage(this->GetParent()->m_hWnd,WM_CUSTOME_CFG_CHGED,1,0);
   }
	this->ShowWindow(SW_HIDE);
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
