// MainDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SynchronousOneWaveformAO.h"
#include "SynchronousOneWaveformAODlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSynchronousOneWaveformAODlg dialog
extern TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out);

CSynchronousOneWaveformAODlg::CSynchronousOneWaveformAODlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSynchronousOneWaveformAODlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   memset(m_uiStateAllChannels, 0, sizeof(m_uiStateAllChannels));
   m_bufferedAoCtrl = NULL;
}

CSynchronousOneWaveformAODlg::~CSynchronousOneWaveformAODlg()
{
   m_bufferedAoCtrl->Dispose();
}
void CSynchronousOneWaveformAODlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_HighLevelA, m_waveformParam[0].HighLevel);
   DDX_Text(pDX, IDC_LowLevelA, m_waveformParam[0].LowLevel);
   DDX_Text(pDX, IDC_HighLevelB, m_waveformParam[1].HighLevel);
   DDX_Text(pDX, IDC_LowLevelB, m_waveformParam[1].LowLevel);
   DDX_Radio(pDX, IDC_SineA, m_uiStateAllChannels[0].btnSelected);
   DDX_Radio(pDX, IDC_SineB, m_uiStateAllChannels[1].btnSelected);
}

BEGIN_MESSAGE_MAP(CSynchronousOneWaveformAODlg, CDialog)
   //{{AFX_MSG_MAP(CSynchronousOneWaveformAODlg)
   ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
   ON_WM_PAINT()
   ON_WM_QUERYDRAGICON()
   ON_CONTROL_RANGE(BN_CLICKED, IDC_SineA, IDC_TriangleB, OnCheckBoxClicked)
   ON_BN_CLICKED(IDC_Configure, OnBnClickedButtonConfig)
   ON_BN_CLICKED(IDC_Start, OnStart)
	ON_WM_CLOSE()
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CSynchronousOneWaveformAODlg message handlers
LRESULT CSynchronousOneWaveformAODlg::OnConfDevice(WPARAM w,LPARAM l)
{
   int cancle = (int)w;
   if (cancle)
   {
      PostQuitMessage(0);
      return 0;
   }
   m_confParam = m_confDlg.GetParameter();
   ConfigurateDevice();
   ConfiguratePanel();
   TRACE(("OnConfDevice\n"));
   return 0;
}

BOOL CSynchronousOneWaveformAODlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

   // TODO: Add extra initialization here
   m_bufferedAoCtrl = BufferedAoCtrl::Create();
   InitUIState();
   m_confDlg.Create(IDD_CONFIGURATION,this);
   m_confDlg.ShowWindow(SW_SHOW);
   this->ShowWindow(SW_HIDE);
   this->EnableWindow(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

//////////////////////////////////////////////////////////////////////////
///config device with config info.
ErrorCode CSynchronousOneWaveformAODlg::ConfigurateDevice()
{
   ErrorCode	errorCode;
   DeviceInformation devInfo(m_confParam.deviceNumber);
   errorCode = m_bufferedAoCtrl->setSelectedDevice(devInfo);
   CheckError(errorCode);
	errorCode = m_bufferedAoCtrl->LoadProfile(m_confParam.profilePath);
	CheckError(errorCode);

   m_bufferedAoCtrl->getSelectedDevice(devInfo);
   CString str ;
   TCHAR des[MAX_DEVICE_DESC_LEN];
   str.Format(_T("Synchronous One Waveform AO - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
   SetWindowText(str);

   // Set necessary parameters for buffered AI operation, 
   // Note: this step is optional if you had done these settings via "Device Configuration" dialog.
	ScanChannel* scanChannel = m_bufferedAoCtrl->getScanChannel();
   errorCode = scanChannel->setChannelStart(m_confParam.channelStart);
   CheckError(errorCode);
   errorCode = scanChannel->setChannelCount(m_confParam.channelCount);
   CheckError(errorCode);
   errorCode = scanChannel->setSamples(m_confParam.pointCountPerWave);
   CheckError(errorCode);
   errorCode = m_bufferedAoCtrl->getConvertClock()->setRate(m_confParam.clockRatePerChan);
   CheckError(errorCode);
   int count = m_bufferedAoCtrl->getFeatures()->getChannelCountMax();
   for (int i = m_confParam.channelStart; i < m_confParam.channelStart + m_confParam.channelCount; ++i)
   {
      errorCode = m_bufferedAoCtrl->getChannels()->getItem(i%count).setValueRange((ValueRange)(m_confParam.vrgType));
      CheckError(errorCode);
   }
   return errorCode;
}

void CSynchronousOneWaveformAODlg::SetUIStateOfChannelState(PUIStateOfChannel uiStateOfChannel, BOOL state)
{
   for (int i = 0; i < WAVE_STYLE_COUNT; i++)
   {
      if (state == FALSE)
      {
         uiStateOfChannel->btnWaveStyle[i]->SetBitmap(NULL);
      }
      else
      {
         if (uiStateOfChannel->btnWaveStyle[i]->GetBitmap() == NULL)
         {
            uiStateOfChannel->btnWaveStyle[i]->SetBitmap(
               m_waveformStyleBmp[i % WAVE_STYLE_COUNT][uiStateOfChannel->btnWaveStyle[i]->GetCheck()]);
         }
      }
      uiStateOfChannel->btnWaveStyle[i]->EnableWindow(state);
   }

   uiStateOfChannel->editHighLevel->EnableWindow(state);
   uiStateOfChannel->editLowLevel->EnableWindow(state);
}


void CSynchronousOneWaveformAODlg::InitUIState()
{
   int i = 0;
   int j = 0;

   for (i = 0; i < WAVE_STYLE_COUNT; i++)
   {
      for (j = 0; j < 2; j++)
      {
         m_waveformStyleBmp[i][j] = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_Sine + j * WAVE_STYLE_COUNT + i));
      }  
   }

   // initialize UI group UIGroupPerChannel for two channel.
   for (i = 0; i < CHANNEL_COUNT; i++)
   {
      for (j = 0; j < WAVE_STYLE_COUNT; j++)
      {
         m_uiStateAllChannels[i].btnWaveStyle[j] = (CButton*)GetDlgItem(IDC_SineA + i * WAVE_STYLE_COUNT + j);
      }
      m_uiStateAllChannels[i].editHighLevel = (CEdit*)GetDlgItem(IDC_HighLevelA + i);
      m_uiStateAllChannels[i].editLowLevel =  (CEdit*)GetDlgItem(IDC_LowLevelA + i);
      // For each channel, the default output WaveType is sine. 
      m_uiStateAllChannels[i].btnSelected = 0;
   }


   // Initialize high level, low level, value text box.
   for (i = 0; i < CHANNEL_COUNT; i++)
   {
      m_waveformParam[i].Style = sine;
      m_waveformParam[i].HighLevel = 5;
      m_waveformParam[i].LowLevel = -5;
   }  
   UpdateData(FALSE);

   for (i = 0; i< CHANNEL_COUNT; i++)
   {
      OnCheckBoxClicked(IDC_SineA + i * WAVE_STYLE_COUNT);
   }
}

//////////////////////////////////////////////////////////////////////////
///According to config info, configure running dialog.
void CSynchronousOneWaveformAODlg::ConfiguratePanel()
{
   // According to config info, config running dialog.
   BOOL bEnable = m_confParam.channelCount > 1 ? TRUE:FALSE;
   SetUIStateOfChannelState(&m_uiStateAllChannels[1], bEnable);

   // According to m_configInfo.channelCount to configure two labels, including ChannelNoA, ChannelNoB.
   CString strChannelA = _T("");
   strChannelA.Format(_T("%d"), m_confParam.channelStart);
   GetDlgItem(IDC_ChannelNoA)->SetWindowText(strChannelA);

   CString strChannelB = _T("");
   int channelCountMax = m_bufferedAoCtrl->getFeatures()->getChannelCountMax();
   if (m_confParam.channelCount > 1)
   {
      strChannelB.Format(_T("%d"), (m_confParam.channelStart + 1) % channelCountMax);
   }
   GetDlgItem(IDC_ChannelNoB)->SetWindowText(strChannelB);
}
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CSynchronousOneWaveformAODlg::OnPaint()
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
HCURSOR CSynchronousOneWaveformAODlg::OnQueryDragIcon()
{
   return static_cast<HCURSOR>(m_hIcon);
}

void CSynchronousOneWaveformAODlg::OnCheckBoxClicked(UINT nID)
{
   int index = nID - IDC_SineA;
   int state = -1;
   ASSERT(index >= 0 && index < WAVE_BTN_COUNT);
   
   UpdateData(TRUE);

   for (int i = 0; i< CHANNEL_COUNT; i++)
   {
      for (int j = 0; j < WAVE_STYLE_COUNT; j++)  
      {
         state = m_uiStateAllChannels[i].btnWaveStyle[j]->GetCheck();

         if (m_uiStateAllChannels[i].btnWaveStyle[j]->IsWindowEnabled())
         {
            m_uiStateAllChannels[i].btnWaveStyle[j]->SetBitmap(m_waveformStyleBmp[j % WAVE_STYLE_COUNT][state]);
         } 
      }
   }
}
void CSynchronousOneWaveformAODlg::OnBnClickedButtonConfig()
{
   // TODO: Add your control notification handler code here
   this->EnableWindow(FALSE);
   m_confDlg.ShowWindow(SW_SHOW);
}


void CSynchronousOneWaveformAODlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
}

void CSynchronousOneWaveformAODlg::OnStart()
{
   // TODO: Add your control notification handler code here
   if (!UpdateData(TRUE))
   {
      //TRACE(traceAppMsg, 0, "UpdateData failed.\n");
      // the UpdateData routine will set focus to correct item
      return;
   }
   
   WaveformGenerator waveformGenerator(m_confParam.pointCountPerWave);
   m_waveformParam[0].Style = (WaveformStyle)m_uiStateAllChannels[0].btnSelected;
   m_waveformParam[1].Style = (WaveformStyle)m_uiStateAllChannels[1].btnSelected;

   double  *waveformData = new double[CHANNEL_COUNT * m_confParam.pointCountPerWave];
   if (waveformData == NULL)
   {
      AfxMessageBox(_T("Allocate memory failed"));
      return ;
   }

   if (m_confParam.channelCount <= 1)
   {
      waveformGenerator.GetOnePeriod(waveformData, m_waveformParam[0]);
   }
   else 
   {
      waveformGenerator.GetMultipleWaveform(waveformData, m_confParam.channelCount, m_waveformParam);
   }

   m_bufferedAoCtrl->SetData(m_confParam.channelCount*m_confParam.pointCountPerWave,waveformData);

   // Allocate memory for ao data buffer.
   if (waveformData != NULL)
   {
      delete waveformData;
   }
   m_bufferedAoCtrl->Prepare();
   ErrorCode errorCode = m_bufferedAoCtrl->RunOnce();
   CheckError(errorCode);
}

//////////////////////////////////////////////////////////////////////////
//This function is used to handle the errorCode information
void CSynchronousOneWaveformAODlg::CheckError(ErrorCode errorCode)
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

