// Configuration.cpp : implementation file
//

#include "stdafx.h"
#include "AsynOneBufferedAI_TDtp.h"
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

	// for trigger
   param.triggerIndex = (int)m_comboBox_trigger_index.GetItemData(m_comboBox_trigger_index.GetCurSel());
	param.triggerAction = DelayToStop;
	param.delayCount = m_triggerDelayCount;
	param.triggerLevel = m_triggerLevel;
	param.triggerSource = (SignalDrop)m_comboBox_source.GetItemData(m_comboBox_source.GetCurSel());
	param.triggerEdge = (ActiveSignal)m_comboBox_edge.GetItemData(m_comboBox_edge.GetCurSel());

   return param;
}

CConfigurationDlg::CConfigurationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigurationDlg::IDD, pParent)
{
	m_sectionLength = 1024;
	m_clockRatePerChan = 1000;

	// for trigger
	m_triggerDelayCount = 600;
	m_triggerLevel = 2.0;
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

	// for trigger parameters 
   DDX_Control(pDX, IDC_COMBO_TRIGGER_INDEX,m_comboBox_trigger_index);
	DDX_Control(pDX, IDC_COMBO_SOURCE,m_comboBox_source);
	DDX_Control(pDX, IDC_COMBO_EDGE,m_comboBox_edge);
	DDX_Text(pDX, IDC_EDIT_LEVEL, m_triggerLevel);
	DDX_Text(pDX, IDC_EDIT_DELAYCOUNT, m_triggerDelayCount);
  
}

BEGIN_MESSAGE_MAP(CConfigurationDlg, CDialog)
   //{{AFX_MSG_MAP(CConfigurationDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICE, OnCbnSelchangeComboDevice)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_CLOSE()

	// for trigger
   ON_CBN_SELCHANGE(IDC_COMBO_TRIGGER_INDEX, OnCbnSelchangeComboTriggerIndex)
	ON_EN_CHANGE(IDC_EDIT_DELAYCOUNT, OnEnChangeEditTriggerDelayCount)
	ON_EN_CHANGE(IDC_EDIT_LEVEL, OnEnChangeEditTriggerLevel)
   ON_CBN_SELCHANGE(IDC_COMBO_SOURCE, OnCbnSelchangeComboSource)

   //}}AFX_MSG_MAP
	
	ON_BN_CLICKED(IDBROWSE, OnBnClickedBrowse)
END_MESSAGE_MAP()

BOOL CConfigurationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

   WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl::Create();
   Array<DeviceTreeNode>* sptedDevices = wfAiCtrl ->getSupportedDevices();
	DeviceInformation selected;

   if (sptedDevices->getCount() == 0)
   {
      GetDlgItem(IDOK)->EnableWindow(FALSE);
      GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
      AfxMessageBox(_T("No device to support the currently demonstrated function!"));
      return FALSE;
   }else{
		int index = 0;
		for (int i = 0; i < sptedDevices->getCount(); ++i)
		{
			DeviceTreeNode const & node = sptedDevices->getItem(i);
			TRACE("%d, %s\n", node.DeviceNumber, node.Description);
			selected.DeviceNumber = node.DeviceNumber;
			wfAiCtrl->setSelectedDevice(selected);
         TCHAR des[MAX_DEVICE_DESC_LEN];
			m_comboBox_Device.AddString(WCHAR_TO_TCHAR(node.Description,des));
			m_comboBox_Device.SetItemData(index++,node.DeviceNumber);
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
   m_comboBox_trigger_index.ResetContent();

   // Get current selected device from device combo box
   CString des;
   m_comboBox_Device.GetLBText(m_comboBox_Device.GetCurSel(),des);

   wchar_t w_des[MAX_DEVICE_DESC_LEN];
   DeviceInformation devInfo(TCHAR_TO_WCHAR((LPCTSTR)des,w_des));
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
   int32 i = 0;
   int chanCountMax = wfAiCtrl->getFeatures()->getChannelCountMax();
   for (i = 0; i < chanCountMax; i++)
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
      errorCode = AdxGetValueRangeInformation((ValueRanges->getItem(i)), 128/*sizeof(vrgDescription)*/, vrgDescription, &ranges, &u);
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
	// trigger function layout 
	WCHAR	signalDes[128];
	SignalPosition sigPos;

   if (wfAiCtrl->getFeatures()->getTriggerCount() > 0)
   {
      m_comboBox_trigger_index.AddString(_T("Trigger0"));
      m_comboBox_trigger_index.SetItemData(0,0);
      if (wfAiCtrl->getFeatures()->getTrigger1Supported())
      {
         m_comboBox_trigger_index.AddString(_T("Trigger1"));
         m_comboBox_trigger_index.SetItemData(1,1);
      }

      Array<SignalDrop>*  sources = wfAiCtrl->getFeatures()->getTriggerSources();

      CString str;
      ((CWnd*)GetDlgItem(IDC_COMBO_SOURCE))->EnableWindow(TRUE);
      ((CWnd*)GetDlgItem(IDC_COMBO_EDGE))->EnableWindow(TRUE);
      ((CWnd*)GetDlgItem(IDC_EDIT_DELAYCOUNT))->EnableWindow(TRUE);
      ((CWnd*)GetDlgItem(IDC_EDIT_LEVEL))->EnableWindow(TRUE);
      ((CWnd*)GetDlgItem(IDC_EDIT_DELAYCOUNT))->EnableWindow(TRUE);

      if (m_comboBox_source.GetCount() > 0)
      {
         m_comboBox_source.ResetContent();
      }
      for (int i = 0; i < sources->getCount();++i)
      {
         errorCode = AdxGetSignalConnectionInformation(sources->getItem(i),128/*sizeof(signalDes)*/ ,signalDes, &sigPos);
         CheckError(errorCode);
         str = signalDes;
         m_comboBox_source.AddString(str);
         TRACE("\nsource %d value:%d",i,(int)sources->getItem(i));
         m_comboBox_source.SetItemData(i,(int)sources->getItem(i));
      }
      m_comboBox_source.SetCurSel(0);

      if (m_comboBox_edge.GetCount() > 0)
      {
         m_comboBox_edge.ResetContent();
      }
      m_comboBox_edge.AddString(_T("Rising Edge"));
      m_comboBox_edge.SetItemData(0,(int)RisingEdge);
      m_comboBox_edge.AddString(_T("Falling Edge"));
      m_comboBox_edge.SetItemData(1,(int)FallingEdge);
      m_comboBox_edge.SetCurSel(0);

      m_comboBox_trigger_index.SetCurSel(0);

   }else{
         GetDlgItem(IDC_COMBO_SOURCE)->EnableWindow(FALSE);
         GetDlgItem(IDC_COMBO_EDGE)->EnableWindow(FALSE);
         GetDlgItem(IDC_EDIT_LEVEL)->EnableWindow(FALSE);
         GetDlgItem(IDC_EDIT_DELAYCOUNT)->EnableWindow(FALSE);
   }
	
	wfAiCtrl->Dispose();
	OnCbnSelchangeComboSource();
	UpdateData(FALSE);
}

void CConfigurationDlg::OnCbnSelchangeComboTriggerIndex()
{
   ErrorCode		 errorCode;
   WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl::Create();
   // Get current selected device from device combo box
   CString des;
   m_comboBox_Device.GetLBText(m_comboBox_Device.GetCurSel(),des);

   wchar_t w_des[MAX_DEVICE_DESC_LEN];
   DeviceInformation devInfo(TCHAR_TO_WCHAR((LPCTSTR)des,w_des));
   errorCode = wfAiCtrl->setSelectedDevice(devInfo);
   GetDlgItem(IDOK)->EnableWindow(TRUE);
   if (errorCode != 0){
      CString str;
      str.Format(_T("Error: the error code is 0x%x, The %s is busy or not exit in computer now.\n\
                    Select other device please!"),errorCode,des);
      AfxMessageBox(str);
      GetDlgItem(IDOK)->EnableWindow(FALSE);
      return;}

   WCHAR	signalDes[128];
   SignalPosition sigPos;
   if (m_comboBox_trigger_index.GetCurSel() == 0)
   {
      Array<SignalDrop>*  sources = wfAiCtrl->getFeatures()->getTriggerSources();

      // for trigger source
      CString str;
      if (m_comboBox_source.GetCount() > 0)
      {
         m_comboBox_source.ResetContent();
      }
      for (int i = 0; i < sources->getCount();++i)
      {
         errorCode = AdxGetSignalConnectionInformation(sources->getItem(i),128/*sizeof(signalDes)*/ ,signalDes, &sigPos);
         CheckError(errorCode);
         str = signalDes;
         m_comboBox_source.AddString(str);
         TRACE("\nsource %d value:%d",i,(int)sources->getItem(i));
         m_comboBox_source.SetItemData(i,(int)sources->getItem(i));
      }
      SignalDrop src = wfAiCtrl->getTrigger()->getSource();
      for (int j = 0; j < sources->getCount(); ++j)
      {
         if (src == sources->getItem(j))
         {
            m_comboBox_source.SetCurSel(j);
         }
      }

      // for trigger edge
      if (m_comboBox_edge.GetCount() > 0)
      {
         m_comboBox_edge.ResetContent();
      }
      m_comboBox_edge.AddString(_T("Rising Edge"));
      m_comboBox_edge.SetItemData(0,(int)RisingEdge);
      m_comboBox_edge.AddString(_T("Falling Edge"));
      m_comboBox_edge.SetItemData(1,(int)FallingEdge);
      ActiveSignal edge = wfAiCtrl->getTrigger()->getEdge();
      if (edge == RisingEdge)
      {
         m_comboBox_edge.SetCurSel(0);
      }else if (edge == FallingEdge){
         m_comboBox_edge.SetCurSel(1);
      }

      // for trigger level
      m_triggerLevel = wfAiCtrl->getTrigger()->getLevel();
      // for trigger delay count
      m_triggerDelayCount = wfAiCtrl->getTrigger()->getDelayCount();

   }else if (m_comboBox_trigger_index.GetCurSel() == 1)
   {
      Array<SignalDrop>*  sources1 = wfAiCtrl->getFeatures()->getTrigger1Sources();

      // for trigger source
      CString str;
      if (m_comboBox_source.GetCount() > 0)
      {
         m_comboBox_source.ResetContent();
      }
      for (int i = 0; i < sources1->getCount();++i)
      {
         errorCode = AdxGetSignalConnectionInformation(sources1->getItem(i),128/*sizeof(signalDes)*/ ,signalDes, &sigPos);
         CheckError(errorCode);
         str = signalDes;
         m_comboBox_source.AddString(str);
         TRACE("\nsource %d value:%d",i,(int)sources1->getItem(i));
         m_comboBox_source.SetItemData(i,(int)sources1->getItem(i));
      }
      SignalDrop src = wfAiCtrl->getTrigger1()->getSource();
      for (int j = 0; j < sources1->getCount(); ++j)
      {
         if (src == sources1->getItem(j))
         {
            m_comboBox_source.SetCurSel(j);
         }
      }

      // for trigger edge
      if (m_comboBox_edge.GetCount() > 0)
      {
         m_comboBox_edge.ResetContent();
      }
      m_comboBox_edge.AddString(_T("Rising Edge"));
      m_comboBox_edge.SetItemData(0,(int)RisingEdge);
      m_comboBox_edge.AddString(_T("Falling Edge"));
      m_comboBox_edge.SetItemData(1,(int)FallingEdge);
      ActiveSignal edge = wfAiCtrl->getTrigger1()->getEdge();
      if (edge == RisingEdge)
      {
         m_comboBox_edge.SetCurSel(0);
      }else if (edge == FallingEdge){
         m_comboBox_edge.SetCurSel(1);
      }

      // for trigger level
      m_triggerLevel = wfAiCtrl->getTrigger1()->getLevel();
      // for trigger delay count
      m_triggerDelayCount = wfAiCtrl->getTrigger1()->getDelayCount();
   }

   wfAiCtrl->Dispose();

   OnCbnSelchangeComboSource();
  
}
void CConfigurationDlg::OnEnChangeEditTriggerDelayCount()
{
	UpdateData();
}
void CConfigurationDlg::OnEnChangeEditTriggerLevel()
{
	UpdateData();
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
	DeviceInformation devInfo(TCHAR_TO_WCHAR((LPCTSTR)des,  w_des));
	
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
	
   if ((wfAiCtrl->getFeatures()->getTriggerCount() > 0) && (m_comboBox_trigger_index.GetCurSel() == 0))
	{
		if (m_comboBox_source.GetItemData(m_comboBox_source.GetCurSel()) != SignalNone )
		{
			int chanCount = m_comboBox_ChannelCount.GetCurSel() + 1;
			MathInterval delayCountRange;
         wfAiCtrl->getFeatures()->getTriggerDelayRange(delayCountRange);
			SamplingMethod method = wfAiCtrl->getFeatures()->getSamplingMethod();
			if (method == EqualTimeSwitch)
			{
				delayCountRange.Max /= chanCount;
			}

			if (m_triggerDelayCount > delayCountRange.Max || m_triggerDelayCount < delayCountRange.Min )
			{
				CString str(L"Error: 'trigger delayCount' is out of range! \nDelay count range is ");
				CString range;
				range.Format(_T("(%d - %f)"),(int)delayCountRange.Min ,delayCountRange.Max);
				CString sError( str + range );   
				AfxMessageBox(sError);
				return;
			}else if (m_triggerDelayCount > m_sectionLength )
			{
				CString error = _T("Error : 'trigger delayCount' must be smaller than 'samples'!");
				AfxMessageBox(error);
				return;
			}

			if (m_triggerLevel > 10 || m_triggerLevel < -10)
			{
				AfxMessageBox(_T(" 'trigger level' is out of range \"-10v ~ 10v \""));
				return;
			}
		}
	}

   if ((wfAiCtrl->getFeatures()->getTriggerCount() > 1) && (m_comboBox_trigger_index.GetCurSel() == 1))
   {
      if (m_comboBox_source.GetItemData(m_comboBox_source.GetCurSel()) != SignalNone )
      {
         int chanCount = m_comboBox_ChannelCount.GetCurSel() + 1;
         MathInterval delayCountRange1;
         wfAiCtrl->getFeatures()->getTrigger1DelayRange(delayCountRange1);
         SamplingMethod method = wfAiCtrl->getFeatures()->getSamplingMethod();
         if (method == EqualTimeSwitch)
         {
            delayCountRange1.Max /= chanCount;
         }

         if (m_triggerDelayCount > delayCountRange1.Max || m_triggerDelayCount < delayCountRange1.Min )
         {
            CString str(L"Error: 'trigger delayCount' is out of range! \nDelay count range is ");
            CString range;
            range.Format(_T("(%d - %f)"),(int)delayCountRange1.Min, delayCountRange1.Max);
            CString sError( str + range );   
            AfxMessageBox(sError);
            return;
         }else if (m_triggerDelayCount > m_sectionLength )
         {
            CString error = _T("Error : 'trigger delayCount' must be smaller than 'samples'!");
            AfxMessageBox(error);
            return;
         }

         if (m_triggerLevel > 10 || m_triggerLevel < -10)
         {
            AfxMessageBox(_T(" 'trigger level' is out of range \"-10v ~ 10v \""));
            return;
         }
      }
   }
   
	int channelCount = m_comboBox_ChannelCount.GetCurSel() + 1;
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
   if (!windowText.Compare(_T("Asynchronous One Buffered AI with Trigger Delay to Stop")))
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

void CConfigurationDlg::OnCbnSelchangeComboSource()
{
	// TODO: Add your control notification handler code here
   WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl::Create();
	// Get current selected device from device combo box
	CString des;
	m_comboBox_Device.GetLBText(m_comboBox_Device.GetCurSel(),des);
   wchar_t w_des[MAX_DEVICE_DESC_LEN];
	DeviceInformation devInfo(TCHAR_TO_WCHAR((LPCTSTR)des,  w_des));
	wfAiCtrl->setSelectedDevice(devInfo);
   if (wfAiCtrl->getFeatures()->getTriggerSupported())
   {
      SignalDrop  source = (SignalDrop)m_comboBox_source.GetItemData(m_comboBox_source.GetCurSel());
      switch (source)
      {
      case SignalNone:
         ((CWnd*)GetDlgItem(IDC_COMBO_EDGE))->EnableWindow(FALSE);
         ((CWnd*)GetDlgItem(IDC_EDIT_DELAYCOUNT))->EnableWindow(FALSE);
         ((CWnd*)GetDlgItem(IDC_EDIT_LEVEL))->EnableWindow(FALSE);
         ((CWnd*)GetDlgItem(IDC_EDIT_DELAYCOUNT))->EnableWindow(FALSE);
         break;
      case SigExtDigClock:
      case SigExtDigTrigger0:
      case SigExtDigTrigger1:
      case SigExtDigTrigger2:
      case SigExtDigTrigger3:
         ((CWnd*)GetDlgItem(IDC_COMBO_EDGE))->EnableWindow(TRUE);
         ((CWnd*)GetDlgItem(IDC_EDIT_DELAYCOUNT))->EnableWindow(TRUE);
         ((CWnd*)GetDlgItem(IDC_EDIT_LEVEL))->EnableWindow(FALSE);
         ((CWnd*)GetDlgItem(IDC_EDIT_DELAYCOUNT))->EnableWindow(TRUE);
         break;
      default:
         ((CWnd*)GetDlgItem(IDC_COMBO_EDGE))->EnableWindow(TRUE);
         ((CWnd*)GetDlgItem(IDC_EDIT_DELAYCOUNT))->EnableWindow(TRUE);
         ((CWnd*)GetDlgItem(IDC_EDIT_LEVEL))->EnableWindow(TRUE);
         ((CWnd*)GetDlgItem(IDC_EDIT_DELAYCOUNT))->EnableWindow(TRUE);
      }
   }
	wfAiCtrl->Dispose();
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
