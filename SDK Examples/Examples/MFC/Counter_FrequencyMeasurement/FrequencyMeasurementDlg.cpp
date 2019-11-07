// FrequencyMeasurementDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FrequencyMeasurement.h"
#include "FrequencyMeasurementDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCFrequencyMeasurementDlg dialog
extern TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out);

CCFrequencyMeasurementDlg::CCFrequencyMeasurementDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCFrequencyMeasurementDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   m_freqMeterCtrl = NULL;
   m_index  = 1;
   memset(&m_confParam, 0, sizeof(m_confParam));
}

CCFrequencyMeasurementDlg::~CCFrequencyMeasurementDlg()
{
}

LRESULT CCFrequencyMeasurementDlg::OnConfDevice(WPARAM w,LPARAM l)
{
   int cancle = (int)w;
   if (cancle)
   {
      PostQuitMessage(0);
      return 0;
   }
   m_confParam = m_confDlg.GetParameter();
   ConfigurateDevice();
   // Init rangeYType list to larger and smaller the rangeY type
   InitRangeYTypeList();
   ConfiguratePanel();
   TRACE(("OnConfDevice\n"));
   return 0;
}

void CCFrequencyMeasurementDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_GraphPicture, m_simpleGraph);
   DDX_Control(pDX, IDC_DATA_SPEED, m_trackTimerInterval);
}

BEGIN_MESSAGE_MAP(CCFrequencyMeasurementDlg, CDialog)
   //{{AFX_MSG(CCFrequencyMeasurementDlg)
   ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_WM_CTLCOLOR()
   ON_WM_TIMER()
   ON_BN_CLICKED(IDC_Start, CCFrequencyMeasurementDlg::OnStart)
   ON_BN_CLICKED(IDC_Pause, CCFrequencyMeasurementDlg::OnPause)
   ON_BN_CLICKED(IDC_Stop, CCFrequencyMeasurementDlg::OnStop)
   ON_BN_CLICKED(IDC_Configure, CCFrequencyMeasurementDlg::OnBnClickedButtonConfig)
   ON_STN_CLICKED(IDC_larger, CCFrequencyMeasurementDlg::OnLarger)
   ON_STN_CLICKED(IDC_smaller, CCFrequencyMeasurementDlg::OnSmaller)
   ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_DATA_SPEED, CCFrequencyMeasurementDlg::OnNMReleasedcaptureDataSpeed)
   //}}AFX_MSG
END_MESSAGE_MAP()


// CCFrequencyMeasurementDlg message handlers

BOOL CCFrequencyMeasurementDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
   // the following is used to change the background picture of the Frequency Measure dialog
   CBitmap			bmp;
   bmp.LoadBitmap(IDB_Background);            //IDB_Background is the ID of the background picture
   m_bkBk.CreatePatternBrush(&bmp);
   bmp.DeleteObject();

   m_confDlg.Create(IDD_CONFIGURATION,this);
   m_confDlg.ShowWindow(SW_SHOW);
   this->ShowWindow(SW_HIDE);
   this->EnableWindow(FALSE);
   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
   GetDlgItem(IDC_Pause)->EnableWindow(FALSE);

   m_freqMeterCtrl = FreqMeterCtrl::Create();  
   
   CRect rc;
   CWnd *pWnd = GetDlgItem(IDC_GraphPicture);
   pWnd->GetClientRect(&rc);
   m_simpleGraph.InitGraph();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCFrequencyMeasurementDlg::OnPaint()
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
HCURSOR CCFrequencyMeasurementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CCFrequencyMeasurementDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
//Init rangeYType list to larger and smaller the rangeY type
void CCFrequencyMeasurementDlg::InitRangeYTypeList()
{
   RangeYType rangeYType;

   for ( int i = 10000000; i >= 1; i /= 10 ) //10 MHz
   {
      if (i >= 1000000)
      {
         rangeYType.rangeY.Max = i / 1000000;//MHz
         rangeYType.rangeY.Min = 0;
         rangeYType.unit = MHz;
         m_rangeYTypeList.push_back(rangeYType);
         continue;
      }
      if (i >= 1000)
      {
         rangeYType.rangeY.Max = i / 1000;//KHz
         rangeYType.rangeY.Min = 0;
         rangeYType.unit = KHz;
         m_rangeYTypeList.push_back(rangeYType);
         continue;
      }

      // Hz
      rangeYType.rangeY.Max = i;
      rangeYType.rangeY.Min = 0;
      rangeYType.unit = Hz;
      m_rangeYTypeList.push_back(rangeYType);
   }
}

void CCFrequencyMeasurementDlg::ConfiguratePanel()
{
   // set run dialog's window text.
   m_trackTimerInterval.SetRange(10, 1000);
   m_trackTimerInterval.SetPos(50);
	CString X_rangeLabels[2];
	m_simpleGraph.GetXCordRangeLabels(X_rangeLabels,10,0,Second);
	((CStatic*)GetDlgItem(IDC_XCoordinateMax))->SetWindowText(X_rangeLabels[0]);
	((CStatic*)GetDlgItem(IDC_XCoordinateMin))->SetWindowText(X_rangeLabels[1]);
   
	m_simpleGraph.m_XCordTimeDiv = 1000;
   // set coordinate Y value
	SetYCord(m_index);

   GetDlgItem(IDC_Start)->EnableWindow(TRUE);
   GetDlgItem(IDC_Pause)->EnableWindow(FALSE);
   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
   GetDlgItem(IDC_Configure)->EnableWindow(TRUE);
}

//////////////////////////////////////////////////////////////////////////
//This function is used to handle the errorCode information
void CCFrequencyMeasurementDlg::CheckError(ErrorCode errorCode)
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

void CCFrequencyMeasurementDlg::OnTimer(UINT_PTR nIDEvent)
{
   // TODO: Add your message handler code here and/or call default
   double value = 0.0;
   m_freqMeterCtrl->Read(1, &value);
   m_simpleGraph.Chart(&value, 1, 1, 1.0*m_timerInterval/1000);
   SetDlgItemInt(IDC_EDIT_FREQUENCY,(UINT)value,FALSE);
   CDialog::OnTimer(nIDEvent);
}

void CCFrequencyMeasurementDlg::OnStart()
{
   // TODO: Add your control notification handler code here
   ErrorCode errorCode = m_freqMeterCtrl->setEnabled(true);

   m_timerInterval = m_trackTimerInterval.GetPos();
   SetTimer(0, m_timerInterval, NULL);

   GetDlgItem(IDC_Start)->EnableWindow(FALSE);
   GetDlgItem(IDC_Pause)->EnableWindow(TRUE);
   GetDlgItem(IDC_Stop)->EnableWindow(TRUE);
   GetDlgItem(IDC_Configure)->EnableWindow(FALSE);
}

void CCFrequencyMeasurementDlg::OnPause()
{
   // TODO: Add your control notification handler code here
   KillTimer(0);
   GetDlgItem(IDC_Pause)->EnableWindow(FALSE);
   GetDlgItem(IDC_Start)->EnableWindow(TRUE);
   GetDlgItem(IDC_Stop)->EnableWindow(TRUE);
}

void CCFrequencyMeasurementDlg::OnStop()
{
   // TODO: Add your control notification handler code here
   ErrorCode errorCode = m_freqMeterCtrl->setEnabled(false);
   CheckError(errorCode);
   
   GetDlgItem(IDC_Configure)->EnableWindow(TRUE);
   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
   GetDlgItem(IDC_Pause)->EnableWindow(FALSE);
   GetDlgItem(IDC_Start)->EnableWindow(TRUE);
   KillTimer(0);
   m_simpleGraph.Clear();
}

void CCFrequencyMeasurementDlg::OnBnClickedButtonConfig()
{
   // TODO: Add your control notification handler code here
   KillTimer(0);
   this->EnableWindow(FALSE);
   m_confDlg.ShowWindow(SW_SHOW);
}

void CCFrequencyMeasurementDlg::OnLarger()
{
   // TODO: Add your control notification handler code here
   if (m_index <= 0)
   {
      return;
   }
   m_index--;
   SetYCord(m_index);
}

void CCFrequencyMeasurementDlg::OnSmaller()
{
   // TODO: Add your control notification handler code here
   if (m_index >= 7)
   {
      return;
   }
   m_index++;
	SetYCord(m_index);
}

void CCFrequencyMeasurementDlg::SetYCord(int index)
{
	int rate = 1;
	RangeYType rangeYType = m_rangeYTypeList[index];
	if (rangeYType.unit == KHz)
	{
		rate = 1000;
	}
	else if (rangeYType.unit == MHz)
	{
		rate = 1000 * 1000;
	}
	CString Y_rangeLabels[3];
	m_simpleGraph.GetYCordRangeLabels(Y_rangeLabels,rangeYType.rangeY.Max,rangeYType.rangeY.Min,rangeYType.unit);
	((CStatic*)GetDlgItem(IDC_YCoordinateMax))->SetWindowText(Y_rangeLabels[0]);
	((CStatic*)GetDlgItem(IDC_YCoordinateMiddle))->SetWindowText(Y_rangeLabels[2]);
	((CStatic*)GetDlgItem(IDC_YCoordinateMin))->SetWindowText(Y_rangeLabels[1]);
	m_simpleGraph.m_YCordRangeMax = rangeYType.rangeY.Max*rate;
	m_simpleGraph.m_YCordRangeMin = rangeYType.rangeY.Min*rate;
	m_simpleGraph.Clear();
}

void CCFrequencyMeasurementDlg::OnNMReleasedcaptureDataSpeed(NMHDR *pNMHDR, LRESULT *pResult)
{
   // TODO: Add your control notification handler code here
   CString str;
   m_timerInterval = m_trackTimerInterval.GetPos();
   SetTimer(0, m_timerInterval, NULL);
   m_simpleGraph.Clear();
   str.Format(_T("%d ms"), m_timerInterval);
   GetDlgItem(IDC_Interval)->SetWindowText(str);
   *pResult = 0;
}

void CCFrequencyMeasurementDlg::ConfigurateDevice()
{
   ErrorCode	errorCode;
   DeviceInformation devInfo(m_confParam.deviceNumber);
   errorCode = m_freqMeterCtrl->setSelectedDevice(devInfo);
   CheckError(errorCode);
	errorCode = m_freqMeterCtrl->LoadProfile(m_confParam.profilePath);
	CheckError(errorCode);

   m_freqMeterCtrl->getSelectedDevice(devInfo);
   CString str ;
   TCHAR des[MAX_DEVICE_DESC_LEN];
   str.Format(_T("Frequency Measurement - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
   SetWindowText(str);
   errorCode = m_freqMeterCtrl->setChannelCount(1);
   CheckError(errorCode);
   errorCode = m_freqMeterCtrl->setChannelStart(m_confParam.channel);
   CheckError(errorCode);
}
