// BufferedPwMeterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BufferedPulseWidthMeasurement.h"
#include "BufferedPulseWidthMeasurementDlg.h"

#define MAX_ROW_COUNT       10
#define Profile_Confiugre   1
#define Manual_Configure    0

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About
extern TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out);
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// CPulseWidthMeasurementDlg message handlers
LRESULT CBufferedPulseWidthMeasurementDlg::OnConfDevice(WPARAM w,LPARAM l)
{
   int cancle = (int)w;
   if (cancle)
   {
      PostQuitMessage(0);
      return 0;
   }
   m_confParam = m_confDlg.GetParameter();
   ConfigurateDevice();
   m_counterValueList.ResetContent();
   UpdateData(FALSE);
   TRACE(("OnConfDevice\n"));
   return 0;
}

// CPulseWidthMeasurementDlg dialog
CBufferedPulseWidthMeasurementDlg::CBufferedPulseWidthMeasurementDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBufferedPulseWidthMeasurementDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   
   // Initialize data member of configForm class.
   memset(&m_confParam, 0, sizeof(m_confParam));
   m_bfdPwMeterCtrl = NULL;
   m_dataBuf = NULL;
   m_channelEnable = NULL;
  
   chs_dataBuf = NULL;
   chs_Status  = NULL;

   m_haveData = false;
   m_isRunning = false;

   m_sectionLength = 0;
   m_sectionCount = 0;
   m_samples = 0;
}

CBufferedPulseWidthMeasurementDlg::~CBufferedPulseWidthMeasurementDlg()
{
   m_bfdPwMeterCtrl->Dispose();
   if ( m_dataBuf != NULL ){
      delete [] m_dataBuf;
      m_dataBuf = NULL;
   }
   if ( m_channelEnable != NULL ){
      delete [] m_channelEnable;
      m_channelEnable = NULL;
   }

   if(chs_Status != NULL){
      delete [] chs_Status;
      chs_Status = NULL;
   }

   if(chs_dataBuf != NULL){
      for(int i = 0; i < m_channelCountMax; i++){
         delete [] chs_dataBuf[i];
      }
   }
   chs_dataBuf = NULL;
}

void CBufferedPulseWidthMeasurementDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_CounterValueList, m_counterValueList);
   DDX_Text(pDX, IDC_ChannelStatus, m_channelStatus);
   DDX_Control(pDX, IDC_EventChannel, m_cbx_eventChannel);
}

BEGIN_MESSAGE_MAP(CBufferedPulseWidthMeasurementDlg, CDialog)
   //{{AFX_MSG_MAP(CPulseWidthMeasurementDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_Start, OnStart)
   ON_BN_CLICKED(IDC_Stop, OnStop)
   ON_BN_CLICKED(IDC_Configure, OnBnClickedButtonConfig)
   ON_CBN_SELCHANGE(IDC_EventChannel, OnCbnSelchangeEventChannel)
   ON_WM_CTLCOLOR()
   ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
   ON_MESSAGE(WM_UPDATEVALUE, OnUpdateValue)
   ON_MESSAGE(WM_STOPEVENT, OnStoppedEvent)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CBufferedPulseWidthMeasurementDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
   //////////////////////////////////////////////////////////////////////////
   // the following is used to change the background picture of the BufferedPulseWidthMeasurement dialog
   CBitmap			bmp;
   bmp.LoadBitmap(IDB_Background);                 //IDB_Background is the ID of the background picture
   m_bkBk.CreatePatternBrush(&bmp);
   bmp.DeleteObject();
   
   m_confDlg.Create(IDD_CONFIGURATION,this);
   m_confDlg.ShowWindow(SW_SHOW);
   this->ShowWindow(SW_HIDE);
   this->EnableWindow(FALSE);

   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);

   m_bfdPwMeterCtrl = BufferedPwMeterCtrl::Create();
   m_bfdPwMeterCtrl->addDataReadyHandler(OnBfdPwMeterEvent, this);
   m_bfdPwMeterCtrl->addStoppedHandler(OnBfdPwMeterStoppedEvent, this);
   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
   
   // Initialize m_device, m_cntr, control.
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBufferedPulseWidthMeasurementDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBufferedPulseWidthMeasurementDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBufferedPulseWidthMeasurementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
//This function is used to handle the errorCode information
void CBufferedPulseWidthMeasurementDlg::CheckError(ErrorCode errorCode)
{
   if (BioFailed(errorCode))
   {
      CString str;
      str.Format(_T("Some errors happened, the error code is: 0x%X !\n"),errorCode);
      AfxMessageBox(str);
      this->EnableWindow(FALSE);
      this->m_confDlg.ShowWindow(SW_SHOW);
   }
}

void CBufferedPulseWidthMeasurementDlg::OnStart()
{
   // Setting Status is Running.
   for (int i = 0; i < m_channelCountMax; i++){
      if (m_channelEnable[i] == 1){
         ChannelStatusChange(i, _T("Running"));
      }
   }
   DisplayChannelStatus(m_displayChannel);
   CString start;
   GetDlgItem(IDC_Start)->GetWindowText(start);
   // TODO: Add your control notification handler code here
   ErrorCode errorCode;
   m_counterValueList.ResetContent();
   //Start the function.
   errorCode = m_bfdPwMeterCtrl->Prepare();
   CheckError(errorCode);
   errorCode = m_bfdPwMeterCtrl->setEnabled(true);
   CheckError(errorCode);
   GetDlgItem(IDC_Start)->EnableWindow(FALSE);
   GetDlgItem(IDC_Stop)->EnableWindow(TRUE);
   GetDlgItem(IDC_Configure)->EnableWindow(FALSE);
   m_isRunning = true;
   m_haveData = true;
}

void CBufferedPulseWidthMeasurementDlg::OnStop()
{
   // TODO: Add your control notification handler code here
   GetDlgItem(IDC_Start)->EnableWindow(TRUE);
   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
   GetDlgItem(IDC_Configure)->EnableWindow(TRUE);
   
   ErrorCode errorCode = m_bfdPwMeterCtrl->setEnabled(FALSE);
   CheckError(errorCode); 
   for (int i = 0; i < m_channelCountMax; i++){
      if (m_channelEnable[i] == 1){
         ChannelStatusChange(i, _T("Stopped"));
      }
   }

   DisplayChannelStatus(m_displayChannel);
   m_isRunning = false;
}

void CBufferedPulseWidthMeasurementDlg::OnBnClickedButtonConfig()
{
   // TODO: Add your control notification handler code here
   m_haveData = false;

   int32 sectionLength = m_bfdPwMeterCtrl->getRecord()->getSectionLength();
   m_confDlg.m_sectionLength = sectionLength;
   int32 sectionCount = m_bfdPwMeterCtrl->getRecord()->getSectionCount();
   m_confDlg.m_sectionCount = sectionCount;

   SignalDrop clkSrc = m_bfdPwMeterCtrl->getSampleClkSrc();
   CounterClockSourceIndexer* indexer = m_bfdPwMeterCtrl->getFeatures()->getPiSampleClockSources();
   for(int i = 0; i < indexer->getItem(0)->getCount(); i++){
      if(clkSrc == indexer->getItem(0)->getItem(i)){
         m_confDlg.m_cbx_clkSrc.SetCurSel(i);
         break;
      }
   }

   SignalDrop trgSrc = m_bfdPwMeterCtrl->getTrigger()->getSource();
   Array<SignalDrop>*  sources = m_bfdPwMeterCtrl->getFeatures()->getTriggerSources();
   for(int i = 0; i < sources->getCount(); i++){
      if(trgSrc == sources->getItem(i)){
         m_confDlg.m_cbx_trgSrc.SetCurSel(i);
         break;
      }
   }

   TriggerAction trgAction = m_bfdPwMeterCtrl->getTrigger()->getAction();
   Array<TriggerAction>* action = m_bfdPwMeterCtrl->getFeatures()->getTriggerActions();
   for(int i = 0; i < action->getCount(); i++){
      if(trgAction == action->getItem(i)){
         m_confDlg.m_cbx_trgAct.SetCurSel(i);
         break;
      }
   }

   ActiveSignal trgEdge = m_bfdPwMeterCtrl->getTrigger()->getEdge();
   int index = -1;
   trgEdge == RisingEdge ? (index = 0) : (index = 0);
   m_confDlg.m_cbx_trgEdge.SetCurSel(index);

   double trgLevel = m_bfdPwMeterCtrl->getTrigger()->getLevel();
   m_confDlg.m_trgLevel = trgLevel;

   m_bfdPwMeterCtrl->getChannelMap(m_channelCountMax, m_channelEnable);
   memcpy(m_confDlg.m_channelEnable, m_channelEnable, sizeof(int8) * m_channelCountMax);
   m_confDlg.InitialChkBox();

   m_confDlg.UpdateData(FALSE);
   this->EnableWindow(FALSE);
   m_confDlg.ShowWindow(SW_SHOW);
}

HBRUSH CBufferedPulseWidthMeasurementDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
   HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

   // TODO:  Change any attributes of the DC here
   if (pWnd == this)
   {
      return m_bkBk;
   }
   // TODO:  Return a different brush if the default is not desired
   return hbr;
}

LRESULT CBufferedPulseWidthMeasurementDlg::OnUpdateValue(WPARAM wParam, LPARAM lParam)
{
   CopyChannelData(m_eventChannel);
   if (m_eventChannel == m_displayChannel){
      DisplayChannelValue(m_displayChannel);
   }
   UpdateData(FALSE);
   return 0;
}

LRESULT CBufferedPulseWidthMeasurementDlg::OnStoppedEvent(WPARAM wParam, LPARAM lParam)
{
   if (m_bfdPwMeterCtrl->getState() == Stopped){
      ErrorCode errorCode = m_bfdPwMeterCtrl->setEnabled(FALSE);
      CheckError(errorCode);
      GetDlgItem(IDC_Start)->EnableWindow(TRUE);
      GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
      GetDlgItem(IDC_Configure)->EnableWindow(TRUE);    
      m_isRunning = false;
   }
   ChannelStatusChange(m_eventChannel, _T("Stopped"));
   DisplayChannelStatus(m_displayChannel);
   UpdateData(FALSE);
   return 0;
}

void CBufferedPulseWidthMeasurementDlg::ConfigurateDevice()
{
   ErrorCode	errorCode;
   DeviceInformation devInfo(m_confParam.deviceNumber);
   errorCode = m_bfdPwMeterCtrl->setSelectedDevice(devInfo);
   CheckError(errorCode);

   m_bfdPwMeterCtrl->getSelectedDevice(devInfo);
   CString str ;
   TCHAR des[MAX_DEVICE_DESC_LEN];
   str.Format(_T("Buffered Pulse Width Measurement - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
   SetWindowText(str);
   
   m_channelCountMax = m_bfdPwMeterCtrl->getFeatures()->getChannelCountMax();
   m_channelEnable = new int8[m_channelCountMax];
   memset(m_channelEnable, 0, sizeof(int8)*m_channelCountMax);

   chs_Status = new CString[m_channelCountMax];

   if(m_confParam.configureMode == Profile_Confiugre){
      errorCode = m_bfdPwMeterCtrl->LoadProfile(m_confParam.profilePath);
      CheckError(errorCode);
      m_bfdPwMeterCtrl->getChannelMap(m_channelCountMax, m_channelEnable);
      m_sectionLength = m_bfdPwMeterCtrl->getRecord()->getSectionLength();
      m_sectionCount  = m_bfdPwMeterCtrl->getRecord()->getSectionCount();
   }else{
      memcpy(m_channelEnable, m_confParam.channelEnable, sizeof(int8) * m_channelCountMax);
      m_sectionLength = m_confParam.sectionLength;
      m_sectionCount  = m_confParam.sectionCount;

      errorCode = m_bfdPwMeterCtrl->setChannelMap(m_channelCountMax, m_channelEnable);
      CheckError(errorCode);
      errorCode = m_bfdPwMeterCtrl->setSampleClkSrc(m_confParam.clkSource);
      CheckError(errorCode);
      Record* record = m_bfdPwMeterCtrl->getRecord();
      errorCode = record->setSectionLength(m_confParam.sectionLength);
      CheckError(errorCode);
      errorCode = record->setSectionCount(m_confParam.sectionCount);
      CheckError(errorCode);

      // for setting trigger
      Trigger* trig = m_bfdPwMeterCtrl->getTrigger();
      if (trig){
         errorCode = trig->setSource(m_confParam.trgSource);
         CheckError(errorCode);       
         errorCode = trig->setAction(m_confParam.trgAction);
         CheckError(errorCode);
         errorCode = trig->setEdge(m_confParam.trgEdge);
         CheckError(errorCode);
         errorCode = trig->setLevel(m_confParam.trgLevel);
         CheckError(errorCode);
      }
   } 

   //users can set the size of buffer for saving data by sectionLength and channelCount.
   m_samples = m_sectionLength;
   if (m_sectionCount){
      m_samples = m_sectionCount * m_sectionLength;
   }

   if (m_samples <= 1){
      m_samples = 2;
   }

   m_dataBuf   = new PulseWidth[m_samples];
   memset(m_dataBuf, 0, sizeof(PulseWidth) * m_samples);
   
   chs_dataBuf = new PulseWidth* [m_channelCountMax];
   for (int i = 0; i < m_channelCountMax; i++){
      chs_dataBuf[i] = new PulseWidth [m_samples];
      memset(chs_dataBuf[i], 0, sizeof(PulseWidth) * m_samples);
   }
   
   if ((m_dataBuf == NULL) || (chs_dataBuf == NULL)){
      AfxMessageBox(_T("Sorry! Error in allocating memory...."));
      this->CloseWindow();
      return;
   }

   // Set eventChannel combo box
   m_cbx_eventChannel.ResetContent();
   for (int i = 0; i < m_channelCountMax; i++ )
   {
      if (m_channelEnable[i] & 0x1){
         CString str;
         str.Format(_T("%d"), i);
         m_cbx_eventChannel.AddString(str);
      }
   }
   m_cbx_eventChannel.SetCurSel(0);
 
   // Setting Status is Ready.
   for (int i = 0; i < m_channelCountMax; i++){
      if (m_channelEnable[i] == 1){
         ChannelStatusChange(i, _T("Ready"));
      }
   }
   CString strChannel; 
   GetDlgItem(IDC_EventChannel)->GetWindowText(strChannel);  
   m_displayChannel = _ttoi(strChannel);
   DisplayChannelStatus(m_displayChannel);
}

void CBufferedPulseWidthMeasurementDlg::OnBfdPwMeterEvent(void * sender, BfdCntrEventArgs * args, void * userParam)
{
   int32 returnCount = 0;
   ErrorCode ret = Success;
   BufferedPwMeterCtrl* bfdPwMeterCtrl = (BufferedPwMeterCtrl*)sender;
   CBufferedPulseWidthMeasurementDlg* uParam = (CBufferedPulseWidthMeasurementDlg*)userParam;
   HWND hWnd = uParam->m_hWnd;
    uParam->m_eventChannel = args->Channel;
   int32 count = min(uParam->m_samples, args->Count);
   ret = bfdPwMeterCtrl->GetData(args->Channel, count, uParam->m_dataBuf, 0, &returnCount);
   if (!ret){
      ::SendMessage(hWnd, WM_UPDATEVALUE, NULL, NULL);
   }
}

void CBufferedPulseWidthMeasurementDlg::OnBfdPwMeterStoppedEvent(void * sender, BfdCntrEventArgs * args, void * userParam)
{
   int32 returnCount = 0;
   ErrorCode ret = Success;
   BufferedPwMeterCtrl* bfdPwMeterCtrl = (BufferedPwMeterCtrl*)sender;
   CBufferedPulseWidthMeasurementDlg* uParam = (CBufferedPulseWidthMeasurementDlg*)userParam;
   HWND hWnd = uParam->m_hWnd;
   uParam->m_eventChannel = args->Channel;
   int32 count = min(uParam->m_samples, args->Count);
   if(count > 0){
      ret = bfdPwMeterCtrl->GetData(args->Channel, count, uParam->m_dataBuf, 0, &returnCount);
      if (!ret){
         ::SendMessage(hWnd, WM_UPDATEVALUE, NULL, NULL);
      }
   }

   ::SendMessage(hWnd, WM_STOPEVENT, NULL, NULL); 
}

void CBufferedPulseWidthMeasurementDlg::OnCbnSelchangeEventChannel()
{
   CString strChannel; 
   GetDlgItem(IDC_EventChannel)->GetWindowText(strChannel);  
   m_displayChannel = _ttoi(strChannel);

   DisplayChannelStatus(m_displayChannel);
   DisplayChannelValue(m_displayChannel);
}

void CBufferedPulseWidthMeasurementDlg::ChannelStatusChange(int32 channel, CString str)
{
   chs_Status[channel] = str;
}

void CBufferedPulseWidthMeasurementDlg::DisplayChannelStatus(int channel)
{
   m_channelStatus = chs_Status[channel];
   GetDlgItem(IDC_ChannelStatus)->SetWindowText(m_channelStatus); 
   UpdateData(FALSE);
}

void CBufferedPulseWidthMeasurementDlg::DisplayChannelValue(int channel)
{	
   m_counterValueList.ResetContent();
   int listCount = 0;
   if(m_sectionLength >= MAX_ROW_COUNT){
      listCount = MAX_ROW_COUNT;
   }else{
      listCount = m_sectionLength;
   }

   CString str;
   if (m_haveData | m_isRunning){
      for(int i = 0; i < listCount; i++){
         str.Format(_T("High: %0.6f s,  Low: %0.6f s"),  chs_dataBuf[channel][i].HiPeriod,  chs_dataBuf[channel][i].LoPeriod);
         m_counterValueList.AddString(str);
      }
   }  
}

void CBufferedPulseWidthMeasurementDlg::CopyChannelData(int channel)
{
   int ch = channel;
   memcpy(chs_dataBuf[ch], m_dataBuf, sizeof(PulseWidth)*m_samples);
}