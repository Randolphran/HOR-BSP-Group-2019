// MainDialog.cpp : implementation file
//

#include "stdafx.h"
#include "StreamingAO.h"
#include "StreamingAODlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CStreamingAODlg dialog
extern TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out);

CStreamingAODlg::CStreamingAODlg(CWnd* pParent /*=NULL*/)
: CDialog(CStreamingAODlg::IDD, pParent)
{
   m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   memset(m_uiStateAllChannels, 0, sizeof(m_uiStateAllChannels));
}

CStreamingAODlg::~CStreamingAODlg()
{
   m_bufferedAoCtrl->Dispose();
}
void CStreamingAODlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_HighLevelA, m_waveformParam[0].HighLevel);
   DDX_Text(pDX, IDC_LowLevelA, m_waveformParam[0].LowLevel);
   DDX_Text(pDX, IDC_HighLevelB, m_waveformParam[1].HighLevel);
   DDX_Text(pDX, IDC_LowLevelB, m_waveformParam[1].LowLevel);
   DDX_Radio(pDX, IDC_SineA, m_uiStateAllChannels[0].btnSelected);
   DDX_Radio(pDX, IDC_SineB, m_uiStateAllChannels[1].btnSelected);
}

BEGIN_MESSAGE_MAP(CStreamingAODlg, CDialog)
   //{{AFX_MSG_MAP(CStreamingAODlg)
   ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
   ON_WM_PAINT()
   ON_WM_QUERYDRAGICON()
   ON_CONTROL_RANGE(BN_CLICKED, IDC_SineA, IDC_TriangleB, OnCheckBoxClicked)
   ON_BN_CLICKED(IDC_Configure, OnBnClickedButtonConfig)
   ON_BN_CLICKED(IDC_Start, OnStart)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CStreamingAODlg message handlers

LRESULT CStreamingAODlg::OnConfDevice(WPARAM w,LPARAM l)
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

void CStreamingAODlg::OnStoppedEvent(void * sender, BfdAoEventArgs * args, void * userParam)
{
   CStreamingAODlg *uParam = (CStreamingAODlg *)userParam;
   uParam->bfdAoEvnetType = AoStopped;
}

void CStreamingAODlg::OnDataTransmittedEvent(void * sender, BfdAoEventArgs * args, void * userParam)
{
   CStreamingAODlg *uParam = (CStreamingAODlg *)userParam;
   uParam->bfdAoEvnetType = DataTransmitted;
}

void CStreamingAODlg::OnTransitStoppedEvent(void * sender, BfdAoEventArgs * args, void * userParam)
{
   CStreamingAODlg *uParam = (CStreamingAODlg *)userParam;
   uParam->bfdAoEvnetType = TransStopped;
}

BOOL CStreamingAODlg::OnInitDialog()
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

   m_bufferedAoCtrl->addStoppedHandler(OnStoppedEvent, this);
   m_bufferedAoCtrl->addTransitStoppedHandler(OnTransitStoppedEvent, this);
   m_bufferedAoCtrl->addDataTransmittedHandler(OnDataTransmittedEvent, this);
   return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStreamingAODlg::ConfigurateDevice()
{
   ErrorCode	errorCode;
   DeviceInformation devInfo(m_confParam.deviceNumber);
   errorCode = m_bufferedAoCtrl->setSelectedDevice(devInfo);
   CheckError(errorCode);
	errorCode = m_bufferedAoCtrl->LoadProfile(m_confParam.profilePath);
	CheckError(errorCode);

   m_bufferedAoCtrl->getSelectedDevice(devInfo);
   TCHAR des[MAX_DEVICE_DESC_LEN];
   CString str ;
   str.Format(_T("Streaming AO - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
   SetWindowText(str);
   errorCode = m_bufferedAoCtrl->setStreaming(true);
	CheckError(errorCode);
   // Set necessary parameters for buffered AI operation, 
	ScanChannel* scanChannel = m_bufferedAoCtrl->getScanChannel();
	int intervalCount = (m_confParam.pointCountPerWave +1) / 2;//ensure that the buffer be divided two parts
   errorCode = scanChannel->setChannelStart(m_confParam.channelStart);
   CheckError(errorCode);
   errorCode = scanChannel->setChannelCount(m_confParam.channelCount);
   CheckError(errorCode);
	errorCode = scanChannel->setIntervalCount(intervalCount); 
	CheckError(errorCode);
   errorCode = scanChannel->setSamples(m_confParam.pointCountPerWave);
   CheckError(errorCode);
   double convertClockRatePerChannel = CONVERT_CLK_RATE(m_confParam.pointCountPerWave, m_confParam.waveformOutFreq);
   errorCode = m_bufferedAoCtrl->getConvertClock()->setRate(convertClockRatePerChannel);
   CheckError(errorCode);
   int count = m_bufferedAoCtrl->getFeatures()->getChannelCountMax();
	AoChannelCollection* channels = m_bufferedAoCtrl->getChannels();
   for (int i = m_confParam.channelStart; i < m_confParam.channelStart + m_confParam.channelCount; ++i)
   {
      errorCode = channels->getItem(i%count).setValueRange((ValueRange)(m_confParam.vrgType));
      CheckError(errorCode);
   }
   
   m_bufferedAoCtrl->Prepare();
}

void CStreamingAODlg::SetUIStateOfChannelState(PUIStateOfChannel uiStateOfChannel, BOOL state)
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

void CStreamingAODlg::InitUIState()
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
void CStreamingAODlg::ConfiguratePanel()
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
void CStreamingAODlg::OnPaint()
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
HCURSOR CStreamingAODlg::OnQueryDragIcon()
{
   return static_cast<HCURSOR>(m_hIcon);
}

void CStreamingAODlg::OnCheckBoxClicked(UINT nID)
{
   int state = -1;

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
void CStreamingAODlg::OnBnClickedButtonConfig()
{
   // TODO: Add your control notification handler code here
   this->EnableWindow(FALSE);
   m_confDlg.ShowWindow(SW_SHOW);
}

void CStreamingAODlg::StartBufferedAo()
{
   ErrorCode   errorCode = Success;
   double      *waveformData = NULL;
   WaveformGenerator waveformGenerator(m_confParam.pointCountPerWave);
  // waveformGenerator.SetPointPerPeriod(m_confParam.pointCountPerWave);
   m_waveformParam[0].Style = (WaveformStyle)m_uiStateAllChannels[0].btnSelected;
   m_waveformParam[1].Style = (WaveformStyle)m_uiStateAllChannels[1].btnSelected;

	// in order to output 'waveformOutFreq' times waveform in a second each channel, the example set 'userBufferLength' following. 
	int userBufferLength = (CHANNEL_COUNT * m_confParam.pointCountPerWave*((int)m_confParam.waveformOutFreq + 1));
   waveformData = new double[userBufferLength];
   if (waveformData == NULL)
   {
      AfxMessageBox(_T("Allocate memory failed"));
      return;
   }

   if (m_confParam.channelCount <= 1)
   {
      waveformGenerator.GetOnePeriod(waveformData, m_waveformParam[0]);
   }
   else 
   {
      waveformGenerator.GetMultipleWaveform(waveformData, m_confParam.channelCount, m_waveformParam);
   }

	if ((int)m_confParam.waveformOutFreq > 1)
	{
		for (int i=0; i < (int)m_confParam.waveformOutFreq; ++i)
		{
			memcpy((byte*)waveformData + i*CHANNEL_COUNT * m_confParam.pointCountPerWave*sizeof(double),
				(byte*)waveformData,CHANNEL_COUNT * m_confParam.pointCountPerWave*sizeof(double));
		}
	}
   
   errorCode = m_bufferedAoCtrl->SetData(userBufferLength,waveformData);
   CheckError(errorCode);
   // Allocate memory for ao data buffer.
   if (waveformData != NULL)
   {
      delete waveformData;
   }

   for (int i = 0; i < CHANNEL_COUNT; i++)
   {
      SetUIStateOfChannelState(&m_uiStateAllChannels[i], FALSE);
   }
   
   GetDlgItem(IDC_Start)->SetWindowText(_T("Stop"));
   GetDlgItem(IDC_Configure)->EnableWindow(FALSE);
   
   m_bufferedAoCtrl->Start();
}

void CStreamingAODlg::OnStart()
{
   // TODO: Add your control notification handler code here
   if (!UpdateData(TRUE))
   {
      // the UpdateData routine will set focus to correct item
      return;
   }
   
   if ( ((CButton*)GetDlgItem(IDC_Start))->GetCheck() == BST_CHECKED )
   {
      StartBufferedAo();
   } 
   else
   {
      m_bufferedAoCtrl->Stop(0);
      for (int i = 0; i < m_confParam.channelCount; i++)
      {
         SetUIStateOfChannelState(&m_uiStateAllChannels[i], TRUE);
      }
      GetDlgItem(IDC_Start)->SetWindowText(_T("Start"));
      GetDlgItem(IDC_Configure)->EnableWindow(TRUE);
   }
}

//This function is used to handle the errorCode information
void CStreamingAODlg::CheckError(ErrorCode errorCode)
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