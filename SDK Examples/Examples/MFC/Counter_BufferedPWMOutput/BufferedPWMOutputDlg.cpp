// PwModulatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include <malloc.h>
#include "BufferedPWMOutput.h"
#include "BufferedPWMOutputDlg.h"

#define MAX_ROW_COUNT       10
#define Profile_Confiugre   1
#define Manual_Configure    0

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPWMOutputDlg dialog
extern TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out);
CBufferedPWMOutputDlg::CBufferedPWMOutputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBufferedPWMOutputDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

   // Initialize data member of configForm class.
   bfdPwModulatorCtrl = NULL;
   m_channelEnable = NULL;
   m_pulseWidth = NULL;
   m_samples = 0;
}

void CBufferedPWMOutputDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_data1_HiPeriod, m_data1_HiPeriod);
   DDX_Text(pDX, IDC_data1_LoPeriod, m_data1_LoPeriod);
   DDX_Text(pDX, IDC_data2_HiPeriod, m_data2_HiPeriod);
   DDX_Text(pDX, IDC_data2_LoPeriod, m_data2_LoPeriod);
   DDX_Control(pDX, IDC_ExecutionStatus, m_executionStatus);
}

BEGIN_MESSAGE_MAP(CBufferedPWMOutputDlg, CDialog)
   //{{AFX_MSG_MAP(CPWMOutputDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_Configure, OnBnClickedButtonConfig)
   ON_BN_CLICKED(IDC_Start, OnStart)
   ON_BN_CLICKED(IDC_Stop, OnStop)
   ON_WM_CTLCOLOR()
   ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
   ON_MESSAGE(WM_UPDATEVALUE, OnUpdateValue)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CPWMOutputDlg message handlers
LRESULT CBufferedPWMOutputDlg::OnConfDevice(WPARAM w,LPARAM l)
{
   int cancle = (int)w;
   if (cancle)
   {
      PostQuitMessage(0);
      return 0;
   }
   m_confParam = m_confDlg.GetParameter();
   ConfigurateDevice();
   TRACE(("OnConfDevice\n"));
   return 0;
}

BOOL CBufferedPWMOutputDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
   //////////////////////////////////////////////////////////////////////////
   // the following is used to change the background picture of the PWMOutput dialog
   CBitmap			bmp;
   bmp.LoadBitmap(IDB_Background);                 //IDB_Background is the ID of the background picture
   m_bkBk.CreatePatternBrush(&bmp);
   bmp.DeleteObject();
   
   if (m_executionStatus.Load(MAKEINTRESOURCE(IDR_ExecutionStatus),_T("gaf")))
   {
      m_executionStatus.Draw();
      Sleep(1000);
      m_executionStatus.Stop();
   }
      
   m_confDlg.Create(IDD_CONFIGURATION,this);
   m_confDlg.ShowWindow(SW_SHOW);
   this->ShowWindow(SW_HIDE);
   this->EnableWindow(FALSE);

   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
   m_data1_HiPeriod = 0.08;
   m_data1_LoPeriod = 0.02;
   m_data2_HiPeriod = 0.05;
   m_data2_LoPeriod = 0.05;

   bfdPwModulatorCtrl = BufferedPwModulatorCtrl::Create();
   bfdPwModulatorCtrl->addDataTransmittedHandler(OnBfdCounterEvent, this);
   UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBufferedPWMOutputDlg::OnPaint()
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
HCURSOR CBufferedPWMOutputDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBufferedPWMOutputDlg::OnBnClickedButtonConfig()
{
   // TODO: Add your control notification handler code here

   int32 intervalCount = bfdPwModulatorCtrl->getIntervalCount();
   m_confDlg.m_intervelCount = intervalCount;

   SignalDrop clkSrc = bfdPwModulatorCtrl->getSampleClkSrc();
   CounterClockSourceIndexer* indexer = bfdPwModulatorCtrl->getFeatures()->getPoSampleClockSources();
   for(int i = 0; i < indexer->getItem(0)->getCount(); i++){
      if(clkSrc == indexer->getItem(0)->getItem(i)){
         m_confDlg.m_cbx_clkSrc.SetCurSel(i);
         break;
      }
   }

   SignalDrop trgSrc = bfdPwModulatorCtrl->getTrigger()->getSource();
   Array<SignalDrop>*  sources = bfdPwModulatorCtrl->getFeatures()->getTriggerSources();
   for(int i = 0; i < sources->getCount(); i++){
      if(trgSrc == sources->getItem(i)){
         m_confDlg.m_cbx_trgSrc.SetCurSel(i);
         break;
      }
   }

   TriggerAction trgAction = bfdPwModulatorCtrl->getTrigger()->getAction();
   Array<TriggerAction>* action = bfdPwModulatorCtrl->getFeatures()->getTriggerActions();
   for(int i = 0; i < action->getCount(); i++){
      if(trgAction == action->getItem(i)){
         m_confDlg.m_cbx_trgAct.SetCurSel(i);
         break;
      }
   }

   ActiveSignal trgEdge = bfdPwModulatorCtrl->getTrigger()->getEdge();
   int index = -1;
   trgEdge == RisingEdge ? (index = 0) : (index = 0);
   m_confDlg.m_cbx_trgEdge.SetCurSel(index);

   double trgLevel = bfdPwModulatorCtrl->getTrigger()->getLevel();
   m_confDlg.m_trgLevel = trgLevel;

   bfdPwModulatorCtrl->getChannelMap(m_channelCountMax, m_channelEnable);
   memcpy(m_confDlg.m_channelEnable, m_channelEnable, sizeof(int8) * m_channelCountMax);
   m_confDlg.InitialChkBox();

   m_confDlg.UpdateData(FALSE);
   this->EnableWindow(FALSE);
   m_confDlg.ShowWindow(SW_SHOW);
}

//////////////////////////////////////////////////////////////////////////
//This function is used to handle the errorCode information
void CBufferedPWMOutputDlg::CheckError(ErrorCode errorCode)
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

void CBufferedPWMOutputDlg::OnStart()
{
   ErrorCode errorCode;
   m_pulseWidth = new PulseWidth[m_samples];
   memset(m_pulseWidth, 0, sizeof(PulseWidth)*m_samples);
   if (!UpdateData(TRUE))
   {
      TRACE("UpdateData failed during dialog termination.\n");
      // the UpdateData routine will set focus to correct item
      return;
   }

   errorCode = bfdPwModulatorCtrl->Prepare();
   CheckError(errorCode);

   for (int32 i = 0; i < m_samples; i++)
   {
      if((i & 0x1) == 0){
         m_pulseWidth[i].HiPeriod = m_data1_HiPeriod;
         m_pulseWidth[i].LoPeriod = m_data1_LoPeriod;
      }else{
         m_pulseWidth[i].HiPeriod = m_data2_HiPeriod;
         m_pulseWidth[i].LoPeriod = m_data2_LoPeriod;
      }
      //UpdateData(FALSE);
   }

   for (int i = 0; i < m_channelCountMax; i++)
   {
      if (m_channelEnable[i]){
         errorCode = bfdPwModulatorCtrl->SetData(i, m_samples, m_pulseWidth);
         CheckError(errorCode);
      }
   }
   errorCode = bfdPwModulatorCtrl->setEnabled(true);
   CheckError(errorCode);

   //UpdateData(FALSE);   

   GetDlgItem(IDC_Start)->EnableWindow(FALSE);
   GetDlgItem(IDC_Stop)->EnableWindow(TRUE);
   GetDlgItem(IDC_Configure)->EnableWindow(FALSE);
   GetDlgItem(IDC_data1_HiPeriod)->EnableWindow(FALSE);
   GetDlgItem(IDC_data1_LoPeriod)->EnableWindow(FALSE);
   GetDlgItem(IDC_data2_HiPeriod)->EnableWindow(FALSE);
   GetDlgItem(IDC_data2_LoPeriod)->EnableWindow(FALSE);
   m_executionStatus.Draw();
}

void CBufferedPWMOutputDlg::OnStop()
{
   // TODO: Add your control notification handler code here
   ErrorCode errorCode;
   //KillTimer(0);
   errorCode = bfdPwModulatorCtrl->setEnabled(false);
   CheckError(errorCode);
   
   GetDlgItem(IDC_Start)->EnableWindow(TRUE);
   GetDlgItem(IDC_Configure)->EnableWindow(TRUE);
   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
   GetDlgItem(IDC_data1_HiPeriod)->EnableWindow(TRUE);
   GetDlgItem(IDC_data1_LoPeriod)->EnableWindow(TRUE);
   GetDlgItem(IDC_data2_HiPeriod)->EnableWindow(TRUE);
   GetDlgItem(IDC_data2_LoPeriod)->EnableWindow(TRUE);

   m_executionStatus.Stop();
}

HBRUSH CBufferedPWMOutputDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

CBufferedPWMOutputDlg::~CBufferedPWMOutputDlg()
{
   bfdPwModulatorCtrl->Dispose();
   m_executionStatus.UnLoad();
   if (m_pulseWidth != NULL){
      delete [] m_pulseWidth;
      m_pulseWidth = NULL;
   }
}

LRESULT CBufferedPWMOutputDlg::OnUpdateValue(WPARAM wParam, LPARAM lParam)
{
   BfdCntrEventArgs* data = (BfdCntrEventArgs*)lParam;
   return 0;
}

void CBufferedPWMOutputDlg::ConfigurateDevice()
{
   ErrorCode	errorCode;
   DeviceInformation devInfo(m_confParam.deviceNumber);
   errorCode = bfdPwModulatorCtrl->setSelectedDevice(devInfo);
   CheckError(errorCode);
   bfdPwModulatorCtrl->getSelectedDevice(devInfo);
   CString str ;
   TCHAR des[MAX_DEVICE_DESC_LEN];
   str.Format(_T("Buffered Counter PWM Output - Run( %s )"), WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description, des));
   SetWindowText(str);
   m_channelCountMax = bfdPwModulatorCtrl->getFeatures()->getChannelCountMax();
   m_channelEnable = new int8[m_channelCountMax];
   memset(m_channelEnable, 0, sizeof(int8)*m_channelCountMax);

   if(m_confParam.configureMode == Profile_Confiugre){
      errorCode = bfdPwModulatorCtrl->LoadProfile(m_confParam.profilePath);
      CheckError(errorCode);
      bfdPwModulatorCtrl->getChannelMap(m_channelCountMax, m_channelEnable);
      m_samples       = bfdPwModulatorCtrl->getSamples();
   }else{
      memcpy(m_channelEnable, m_confParam.channelEnable, sizeof(int8) * m_channelCountMax);

      errorCode = bfdPwModulatorCtrl->setChannelMap(m_channelCountMax, m_confParam.channelEnable);
      CheckError(errorCode);
      errorCode = bfdPwModulatorCtrl->setIntervalCount(m_confParam.intervelCount);
      CheckError(errorCode);

      m_samples = m_confParam.intervelCount * 2;
      errorCode = bfdPwModulatorCtrl->setSamples(m_samples);
      CheckError(errorCode);
      errorCode = bfdPwModulatorCtrl->setStreaming(TRUE);
      CheckError(errorCode);
      errorCode = bfdPwModulatorCtrl->setSampleClkSrc(m_confParam.clkSource);
      CheckError(errorCode);
      // for setting trigger
      Trigger* trig = bfdPwModulatorCtrl->getTrigger();
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
}

void CBufferedPWMOutputDlg::OnBfdCounterEvent(void * sender, BfdCntrEventArgs * args, void * userParam)
{
   CBufferedPWMOutputDlg* uParam = (CBufferedPWMOutputDlg*)userParam;
   HWND hWnd = uParam->m_hWnd;
   ::SendMessage(hWnd, WM_UPDATEVALUE, NULL, (LPARAM)args);
}