// InstantAoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StaticAO.h"
#include "StaticAODlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CStaticAODlg dialog
extern TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out);

CStaticAODlg::CStaticAODlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStaticAODlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   // Initialize data member of configForm class.
   memset(&m_confParam, 0, sizeof(m_confParam)); 
   memset(m_waveSelectButton, 0, sizeof(CButton*) * 6);

   m_wavePointsIndexA = 0;
   m_wavePointsIndexB = 0;
   m_dataScaled = NULL; 
   m_isCheckedA = FALSE;
   m_isCheckedB = FALSE;
   m_waveformGenerator = NULL;
   m_instantAoCtrl = NULL;
}

CStaticAODlg::~CStaticAODlg()
{
   // release memory resource.
   if (m_dataScaled != NULL)
   {
      delete m_dataScaled;
   }
   if (m_waveformGenerator != NULL)
   {
      delete m_waveformGenerator;
   }
   m_instantAoCtrl->Dispose();
}

void CStaticAODlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_SLIDER1, m_trackTimerInterval);
   DDX_Text(pDX, IDC_HighLevelA, m_highLevelA);
   DDX_Text(pDX, IDC_LowLevelA, m_lowLevelA);
   DDX_Text(pDX, IDC_HighLevelB, m_highLevelB);
   DDX_Text(pDX, IDC_LowLevelB, m_lowLevelB);
   DDX_Text(pDX, IDC_ValueA, m_valueA);
   DDX_Text(pDX, IDC_ValueB, m_valueB);
}

BEGIN_MESSAGE_MAP(CStaticAODlg, CDialog)
   //{{AFX_MSG_MAP(CStaticAODlg)
   ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_WM_CTLCOLOR()
   ON_WM_TIMER()
   ON_CONTROL_RANGE(BN_CLICKED, IDC_SineA, IDC_TriangleB, OnCheckBoxClicked)
   ON_BN_CLICKED(IDC_ManualA, OnManualAClick)
   ON_BN_CLICKED(IDC_ManualB, OnManualBClick)
   ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnNMReleasedcaptureSlider)
   ON_BN_CLICKED(IDC_Configure, OnBnClickedButtonConfig)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CInstantAoDlg message handlers

LRESULT CStaticAODlg::OnConfDevice(WPARAM w,LPARAM l)
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
   m_waveformGenerator->SetPointPerPeriod(m_confParam.pointCountPerWave);
   SetTimer(0, m_trackTimerInterval.GetPos(), NULL);
   TRACE(("OnConfDevice\n"));
   return 0;
}

BOOL CStaticAODlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
   //////////////////////////////////////////////////////////////////////////
   // the following is used to change the background picture of the InstantAo dialog
   CBitmap			bmp;
   bmp.LoadBitmap(IDB_Background);                 //IDB_Background is the ID of the background picture
   m_bkBk.CreatePatternBrush(&bmp);
   bmp.DeleteObject();

   m_confDlg.Create(IDD_CONFIGURATION,this);
   m_confDlg.ShowWindow(SW_SHOW);
   this->ShowWindow(SW_HIDE);
   this->EnableWindow(FALSE);
   
   // create WaveformGenerator object.
   m_waveformGenerator = new WaveformGenerator(m_confParam.pointCountPerWave);
   // allocate memory for AO data buffer. 
   m_dataScaled = new double[2];
   if (m_waveformGenerator == NULL || m_waveformGenerator == NULL)
   {
      AfxMessageBox(_T("Allocate memory failed"));
      PostQuitMessage(0);
      return TRUE;
   }

   m_trackTimerInterval.SetRange(1, 1000, TRUE);
   m_trackTimerInterval.SetPos(50);

   // use six CButton pointers to waveSelectButton to initialize m_waveSelectButton array.
   int i = 0;
   int j = 0;
   for (i = 0; i < WAVE_BTN_COUNT; i++)
   {
      m_waveSelectButton[i] = (CButton*)GetDlgItem(IDC_SineA + i);
   }
   
   for (i = 0; i < CHANNEL_COUNT; i++)
   {
      for (j = 0; j < WAVE_STYLE_COUNT; j++)
      {
         m_waveformStyleBmp[i][j] = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_Sine + i * WAVE_STYLE_COUNT + j));
      }  
   }
   
   // Load picture for two manual buttons. 
   HBITMAP hBmp; 
   hBmp=::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_Manual));
   ((CButton*)GetDlgItem(IDC_ManualA))->SetBitmap(hBmp); 
   ((CButton*)GetDlgItem(IDC_ManualB))->SetBitmap(hBmp);
   
   // load picture for WAVE_BTN_COUNT buttons, including SineA,
   // SquareA, TriangleA, SineB, SquareB, TriangleB.
   for (i = 0; i < WAVE_BTN_COUNT; i++)
   {
      m_waveSelectButton[i]->SetBitmap(m_waveformStyleBmp[0][i % WAVE_STYLE_COUNT]); 
   }

   // initialize high level, low level, value text box.
   m_highLevelA = 5;
   m_lowLevelA = -5;
   m_valueA  = 2.5;
   m_highLevelB = 5;
   m_lowLevelB = -5;
   m_valueB  = 2.5;
   UpdateData(FALSE);

   // the default state of m_isCheckA and m_isCheckB is not checked.
   m_isCheckedA = FALSE;
   m_isCheckedB = FALSE;

   m_instantAoCtrl = InstantAoCtrl::Create();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

//////////////////////////////////////////////////////////////////////////
//This function is used to config device with config parameter.
void CStaticAODlg::ConfigurateDevice()
{
   ErrorCode	errorCode;
   DeviceInformation devInfo(m_confParam.deviceNumber);
   errorCode = m_instantAoCtrl->setSelectedDevice(devInfo);
   CheckError(errorCode);
	errorCode = m_instantAoCtrl->LoadProfile(m_confParam.profilePath);
	CheckError(errorCode);

   m_instantAoCtrl->getSelectedDevice(devInfo);
   CString str ;
   TCHAR des[MAX_DEVICE_DESC_LEN];
   str.Format(_T("Static AO - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
   SetWindowText(str);
   
   //get channel max number. set value range for every channel.
   int channelCountMax = m_instantAoCtrl->getFeatures()->getChannelCountMax();
   for (int i = 0; i < channelCountMax; i++)
   {
      m_instantAoCtrl->getChannels()->getItem(i).setValueRange((ValueRange)(m_confParam.vrgType));
   }
}

//////////////////////////////////////////////////////////////////////////
//According to config info, configure running dialog.
void CStaticAODlg::ConfiguratePanel()
{  
   // According to m_configInfo.channelCount, config running dialog.
   int i = 0; 
   BOOL bEnable = m_confParam.channelCount > 1 ? TRUE:FALSE;

   if (bEnable == FALSE)
   {
      for (i = WAVE_STYLE_COUNT; i < WAVE_BTN_COUNT; i++)
      {
         m_waveSelectButton[i]->SetBitmap(NULL);
      }
      ((CButton*)GetDlgItem(IDC_ManualB))->SetBitmap(NULL);
   }
   else
   {
      for (i = WAVE_STYLE_COUNT; i < WAVE_BTN_COUNT; i++)
      {
         if (m_waveSelectButton[i]->GetBitmap() == NULL)
         {
            m_waveSelectButton[i]->SetBitmap(m_waveformStyleBmp[m_waveSelectButton[i]->GetCheck()][i % WAVE_STYLE_COUNT]);
         }
      }
      if ( ((CButton*)GetDlgItem(IDC_ManualB))->GetBitmap() == NULL )
      {
         ((CButton*)GetDlgItem(IDC_ManualB))->SetBitmap(::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_Manual)));
      }
   }
   
   for (i = WAVE_STYLE_COUNT; i < WAVE_BTN_COUNT; i++)
   {
      m_waveSelectButton[i]->EnableWindow(bEnable);
   }
   GetDlgItem(IDC_ManualB)->EnableWindow(bEnable);
   GetDlgItem(IDC_HighLevelB)->EnableWindow(bEnable);
   GetDlgItem(IDC_LowLevelB)->EnableWindow(bEnable);
   GetDlgItem(IDC_ValueB)->EnableWindow(bEnable);
   

   // According to m_configInfo.channelCount to configure two labels, including ChannelNoA, ChannelNoB.
   CString strChannelA = _T("");
   strChannelA.Format(_T("%d"), m_confParam.channelStart);
   GetDlgItem(IDC_ChannelNoA)->SetWindowText(strChannelA);
   int channelCountMax = m_instantAoCtrl->getFeatures()->getChannelCountMax();
   CString strChannelB = _T("");
   if (m_confParam.channelCount > 1)
   {
      strChannelB.Format(_T("%d"), (m_confParam.channelStart + 1) % channelCountMax);
   }
   GetDlgItem(IDC_ChannelNoB)->SetWindowText(strChannelB);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStaticAODlg::OnPaint()
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
HCURSOR CStaticAODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CStaticAODlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

//////////////////////////////////////////////////////////////////////////
//This function is used to handle the errorCode information
void CStaticAODlg::CheckError(ErrorCode errorCode)
{
   if (BioFailed(errorCode))
   {
      KillTimer(0);
      CString str;
      str.Format(_T("Some errors happened, the error code is: 0x%X !\n"),errorCode);
      AfxMessageBox(str);
      this->EnableWindow(FALSE);
      this->m_confDlg.ShowWindow(SW_SHOW);
   }
}

//////////////////////////////////////////////////////////////////////////
//This function is ON_TIMER Message's message handling function.
void CStaticAODlg::OnTimer(UINT_PTR nIDEvent)
{
   // TODO: Add your message handler code here and/or call default
   ErrorCode ret;
   
   if (m_isCheckedA)
   {
      m_dataScaled[0] = m_waveformGenerator->GetOnePoint(m_formStyleA, m_wavePointsIndexA++, m_highLevelA, m_lowLevelA);
		m_wavePointsIndexA = (m_wavePointsIndexA >= m_confParam.pointCountPerWave)? 0 : m_wavePointsIndexA;
   }
   if (m_isCheckedB)
   {
      m_dataScaled[1] = m_waveformGenerator->GetOnePoint(m_formStyleB, m_wavePointsIndexB++, m_highLevelB, m_lowLevelB);
		m_wavePointsIndexB = (m_wavePointsIndexB >= m_confParam.pointCountPerWave) ? 0 : m_wavePointsIndexB;
   }

   ret = m_instantAoCtrl->Write(m_confParam.channelStart, m_confParam.channelCount, m_dataScaled);
   if (ret != Success)
   {
      KillTimer(0);
      CheckError(ret);
   }
   CDialog::OnTimer(nIDEvent);
}

void CStaticAODlg::OnCheckBoxClicked(UINT nID)
{
   CButton *btn = (CButton*)GetDlgItem(nID);
   int index = nID - IDC_SineA;
   CString str;

   ASSERT( index >= 0 && index < WAVE_BTN_COUNT );
   
   UpdateData(TRUE);

   switch (btn->GetCheck()) 
   {  
      case BST_CHECKED:  // If btn is checked.
      {
         if (index < WAVE_STYLE_COUNT)  //Group A buttons
         {
            for (int i = 0; i < WAVE_STYLE_COUNT; i++)  
            {
               m_waveSelectButton[i]->SetCheck(BST_UNCHECKED);
               m_waveSelectButton[i]->SetBitmap(m_waveformStyleBmp[0][i % WAVE_STYLE_COUNT]);
            }
            
            m_wavePointsIndexA = 0;
            m_isCheckedA = TRUE;
            m_formStyleA = (WaveformStyle)(index % WAVE_STYLE_COUNT);
         }
         else                            // Group B buttons
         {
            for (int i = WAVE_STYLE_COUNT; i < WAVE_BTN_COUNT; i++)  
            {
               m_waveSelectButton[i]->SetCheck(BST_UNCHECKED);
               m_waveSelectButton[i]->SetBitmap(m_waveformStyleBmp[0][i % WAVE_STYLE_COUNT]);
            }
            
            m_wavePointsIndexB = 0;
            m_isCheckedB = TRUE;
            m_formStyleB = (WaveformStyle)(index % WAVE_STYLE_COUNT);
         }
         
         m_waveSelectButton[index]->SetCheck(BST_CHECKED); 
         m_waveSelectButton[index]->SetBitmap(m_waveformStyleBmp[1][index % WAVE_STYLE_COUNT]);
         break;
      }
      case BST_UNCHECKED: // If btn isn't checked.
      {
         m_waveSelectButton[index]->SetBitmap(m_waveformStyleBmp[0][index % WAVE_STYLE_COUNT]);
         if (index < 3)
         {
            m_isCheckedA = FALSE;
         }
         else
         {
            m_isCheckedB = FALSE;
         }
         break;
      }
      default:
      {
         break;
      }      
   }
}
void CStaticAODlg::OnManualAClick()
{
   // TODO: Add your control notification handler code here
   UpdateData(TRUE);

   for (int i = 0; i < WAVE_STYLE_COUNT; i++)
   {
      m_waveSelectButton[i]->SetCheck(BST_UNCHECKED);
      m_waveSelectButton[i]->SetBitmap(m_waveformStyleBmp[0][i % WAVE_STYLE_COUNT]);
   }
   
   m_isCheckedA = FALSE;
   m_dataScaled[0] = m_valueA;
}

void CStaticAODlg::OnManualBClick()
{
   // TODO: Add your control notification handler code here
   UpdateData(TRUE);

   for (int i = WAVE_STYLE_COUNT; i < WAVE_BTN_COUNT; i++)
   {
      m_waveSelectButton[i]->SetCheck(BST_UNCHECKED);
      m_waveSelectButton[i]->SetBitmap(m_waveformStyleBmp[0][i % WAVE_STYLE_COUNT]);
   }
   m_isCheckedB = FALSE;
   m_dataScaled[1] = m_valueB;
}

void CStaticAODlg::OnNMReleasedcaptureSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
   // TODO: Add your control notification handler code here
   int currentPos = 0;
   currentPos = m_trackTimerInterval.GetPos();
   KillTimer(0);
   SetTimer(0, currentPos, NULL);

   CString str;
   str.Format(_T("%d ms"), currentPos);
   GetDlgItem(IDC_interval)->SetWindowText(str);
   *pResult = 0;
}

void CStaticAODlg::OnBnClickedButtonConfig()
{
   // TODO: Add your control notification handler code here
   KillTimer(0);
   this->EnableWindow(FALSE);
   m_confDlg.ShowWindow(SW_SHOW);
}
