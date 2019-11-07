// ConfigForm.cpp : implementation file
//

#include "stdafx.h"
#include "SynchronousOneWaveformAO.h"
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

// CConfigForm dialog
IMPLEMENT_DYNAMIC(CConfigurationDlg, CDialog)

DevConfParam CConfigurationDlg::GetParameter()
{
   DevConfParam param;
   param.deviceNumber = (int)m_comboBox_Device.GetItemData(m_comboBox_Device.GetCurSel());
   param.channelCount = m_comboBox_ChannelCount.GetCurSel() + 1;
   param.channelStart = m_comboBox_ChannelStart.GetCurSel();
   param.vrgType = (int)m_comboBox_ValueRange.GetItemData(m_comboBox_ValueRange.GetCurSel());
   param.clockRatePerChan = m_clockRatePerChan;
   param.pointCountPerWave = (int)m_pointsCount;
	TCHAR_TO_WCHAR(m_profilePath, param.profilePath);
   return param;
}

CConfigurationDlg::CConfigurationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigurationDlg::IDD, pParent)
{
   // Initialize data member of configForm class.
   m_pointsCount = 400;
   m_clockRatePerChan = 1000.0;
}

CConfigurationDlg::~CConfigurationDlg()
{
}

BOOL CConfigurationDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   BufferedAoCtrl * bufferedAoCtrl = BufferedAoCtrl::Create();
   Array<DeviceTreeNode>* sptedDevices = bufferedAoCtrl->getSupportedDevices();

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
   bufferedAoCtrl->Dispose();
   m_comboBox_Device.SetCurSel(0);
   OnCbnSelchangeComboDevice();
   return TRUE;
}
void CConfigurationDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_Device, m_comboBox_Device);
   DDX_Control(pDX, IDC_channelStart, m_comboBox_ChannelStart);
   DDX_Control(pDX, IDC_channelCount, m_comboBox_ChannelCount);
   DDX_Control(pDX, IDC_valueRange, m_comboBox_ValueRange);
   DDX_Text(pDX, IDC_PointsPerWave, m_pointsCount);
   DDX_Text(pDX, IDC_ConvertClockRatePerChannel, m_clockRatePerChan);
}


BEGIN_MESSAGE_MAP(CConfigurationDlg, CDialog)
   //{{AFX_MSG_MAP(CConfigurationDlg)
   ON_CBN_SELCHANGE(IDC_Device, OnCbnSelchangeComboDevice)
   ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_CLOSE()
   ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
   //}}AFX_MSG_MAP
   
	ON_BN_CLICKED(IDBROWSE, OnBnClickedBrowse)
END_MESSAGE_MAP()

// CConfigForm message handlers
void CConfigurationDlg::OnCbnSelchangeComboDevice()
{
   // TODO: Add your control notification handler code here
   ErrorCode		errorCode;
   BufferedAoCtrl* bufferedAoCtrl = BufferedAoCtrl::Create();

   // Clear the context of combo box for parameters
   m_comboBox_ChannelCount.ResetContent();
   m_comboBox_ChannelStart.ResetContent();
   m_comboBox_ValueRange.ResetContent();

   // Get current selected device from device combo box
   CString des;
   m_comboBox_Device.GetLBText(m_comboBox_Device.GetCurSel(),des);

   wchar_t w_des[MAX_DEVICE_DESC_LEN];
   DeviceInformation devInfo( TCHAR_TO_WCHAR((LPCTSTR)des,  w_des) );
   errorCode = bufferedAoCtrl->setSelectedDevice(devInfo);
   GetDlgItem(IDOK)->EnableWindow(TRUE);
   if (errorCode != 0){
      CString str;
      str.Format(_T("Error: the error code is 0x%x, The %s is busy or not exit in computer now.\n\
  Select other device please!"),errorCode,des);
      AfxMessageBox(str);
      GetDlgItem(IDOK)->EnableWindow(FALSE);
      return;}
   // Set channel start combo box
   int channelCountMax = bufferedAoCtrl->getFeatures()->getChannelCountMax();
   int32 i = 0;
   for (i = 0; i < channelCountMax; i++)
   {
      CString str ;
      str.Format(_T("%d"),i);
      m_comboBox_ChannelStart.AddString(str);
   }

   // Set channel count combo box
   int channelCount = (channelCountMax < 2)? channelCountMax:2;
   for (i = 1; i < channelCount + 1; i++)
   {
      CString str ;
      str.Format(_T("%d"),i);
      m_comboBox_ChannelCount.AddString(str);
   }

   // Set value range combo box
   Array<ValueRange>* ValueRanges = bufferedAoCtrl->getFeatures()->getValueRanges();
   WCHAR	vrgDescription[128];
   MathInterval	ranges;
   for (i = 0; i < ValueRanges->getCount() ; i++)
   {
      if (ValueRanges->getItem(i) < UserCustomizedVrgStart)
      { 
         errorCode = AdxGetValueRangeInformation((ValueRanges->getItem(i)), 
                        sizeof(vrgDescription), vrgDescription, &ranges, NULL);
         CheckError(errorCode);
         CString str = vrgDescription;
         m_comboBox_ValueRange.AddString(str);
         m_comboBox_ValueRange.SetItemData(i,(int)ValueRanges->getItem(i));
      }
   }

   // Set default parameters 
   m_comboBox_ChannelStart.SetCurSel(0);
   m_comboBox_ChannelCount.SetCurSel(1);
   m_comboBox_ValueRange.SetCurSel(0);
   m_pointsCount = 512;
   m_clockRatePerChan = 1000.0;
   UpdateData(TRUE);
   bufferedAoCtrl->Dispose();
}

void CConfigurationDlg::OnBnClickedOk() 
{
	BufferedAoCtrl* bufferedAoCtrl = BufferedAoCtrl::Create();

	if (!UpdateData(TRUE))
   {
      return;
   }

   if (m_clockRatePerChan <= 0 || m_pointsCount <= 0)
   {
      AfxMessageBox(_T("Points for each waveform and convert clock rate should be greater than 0."));
      return;
   }

   // TODO: Add extra validation here
   this->GetParent()->ShowWindow(SW_SHOW);
   this->GetParent()->EnableWindow(TRUE);
   this->ShowWindow(SW_HIDE);

   // Send message to configure the device selected.
   ::SendMessage(this->GetParent()->m_hWnd,WM_CUSTOME_CFG_CHGED,0,0);
   EndDialog(IDOK);
	bufferedAoCtrl->Dispose();
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
//////////////////////////////////////////////////////////////////////////
//This function is used to handle the errorCode information
void CConfigurationDlg::CheckError(ErrorCode errorCode)
{
   if (errorCode != Success)
   {
      CString str;
      str.Format(_T("Some errors happened, the error code is:0x%x"), errorCode);
      AfxMessageBox(str);
   }
}

void CConfigurationDlg::OnBnClickedCancel()
{
   // TODO: Add your control notification handler code here
   CString windowText;
   this->GetParent()->GetWindowText(windowText);
   if (!windowText.Compare(_T("SynchronousOneWaveformAO")))
   {
      ::SendMessage(this->GetParent()->m_hWnd,WM_CUSTOME_CFG_CHGED,1,0);
   }
	this->ShowWindow(SW_HIDE);
   OnCancel();
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
