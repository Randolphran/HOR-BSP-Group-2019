// TimerPulseDlg.cpp : implementation file
//

#include "stdafx.h"
#include <malloc.h>
#include "PulseOutputwithTimerInterrupt.h"
#include "PulseOutputwithTimerInterruptDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPulseOutputwithTimerInterruptDlg dialog
extern TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out);

LRESULT CPulseOutputwithTimerInterruptDlg::OnConfDevice(WPARAM w,LPARAM l)
{
   int cancle = (int)w;
   if (cancle)
   {
      PostQuitMessage(0);
      return 0;
   }
   m_confParam = m_confDlg.GetParameter();
   ConfigurateDevice();

   GetDlgItem(IDC_eventCount)->SetWindowText(_T("0"));
   TRACE(("OnConfDevice\n"));
   return 0;
}

CPulseOutputwithTimerInterruptDlg::CPulseOutputwithTimerInterruptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPulseOutputwithTimerInterruptDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   memset(&m_confParam, 0, sizeof(m_confParam));
   m_timerPulseCtrl = NULL;
}

void CPulseOutputwithTimerInterruptDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_desiredFrequency, m_desiredFrequency);
   DDX_Text(pDX, IDC_generatedFrequency, m_generatedFrequency);
   DDX_Control(pDX, IDC_ExecutionStatus, m_executionStatus);
}

BEGIN_MESSAGE_MAP(CPulseOutputwithTimerInterruptDlg, CDialog)
   //{{AFX_MSG_MAP(CPulseOutputwithTimerInterruptDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_Configure, OnBnClickedButtonConfig)
   ON_BN_CLICKED(IDC_Start, OnStart)
   ON_BN_CLICKED(IDC_Stop, OnStop)
   ON_WM_CTLCOLOR()
   ON_MESSAGE(WM_UPDATEMSG, OnUpdateEventCount)
   ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CPulseOutputwithTimerInterruptDlg message handlers
BOOL CPulseOutputwithTimerInterruptDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
   //////////////////////////////////////////////////////////////////////////
   // the following is used to change the background picture of the Timer Pulse dialog
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
   m_desiredFrequency = 50;
   m_generatedFrequency = 0;
	m_eventCount = 0;
   m_timerPulseCtrl = TimerPulseCtrl::Create();

	//Caution: When TimerTick interrupt is too frequent, the operating system may hang.
	//The following is the suggestion:
	//1.If you use the pulse output function only, you don't need to deal with TimerTick event.
	//2.If you want to use timer interrupt function, uncomment the following codes.
   
   //m_timerPulseCtrl->addTimerTickHandler(OnCounterEvent, this->m_hWnd);

   UpdateData(FALSE);

   // Initialize m_device, m_cntr, control.
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPulseOutputwithTimerInterruptDlg::OnPaint()
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
HCURSOR CPulseOutputwithTimerInterruptDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CPulseOutputwithTimerInterruptDlg::ConfigurateDevice()
{
   ErrorCode	errorCode;
   DeviceInformation devInfo(m_confParam.deviceNumber);
   devInfo.ModuleIndex = m_confParam.moduleIndex;
   errorCode = m_timerPulseCtrl->setSelectedDevice(devInfo);
   CheckError(errorCode);
	errorCode = m_timerPulseCtrl->LoadProfile(m_confParam.profilePath);
	CheckError(errorCode);
	
   m_timerPulseCtrl->getSelectedDevice(devInfo);
   CString str ;
   TCHAR des[MAX_DEVICE_DESC_LEN];
   str.Format(_T("Pulse Output with Timer Interrupt - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
   SetWindowText(str);
   errorCode = m_timerPulseCtrl->setChannelCount(1);
   CheckError(errorCode);
   errorCode = m_timerPulseCtrl->setChannelStart(m_confParam.channel);
   CheckError(errorCode);
}
//////////////////////////////////////////////////////////////////////////
//This function is used to handle the errorCode information
void CPulseOutputwithTimerInterruptDlg::CheckError(ErrorCode errorCode)
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

void CPulseOutputwithTimerInterruptDlg::OnBnClickedButtonConfig()
{
   // TODO: Add your control notification handler code here
   this->EnableWindow(FALSE);
   m_confDlg.ShowWindow(SW_SHOW);
}

void CPulseOutputwithTimerInterruptDlg::OnStart()
{
   ErrorCode errorCode;
   double frequency = 0;
   
   if (!UpdateData(TRUE))
   {
      TRACE("UpdateData failed during dialog termination.\n");
      // the UpdateData routine will set focus to correct item
      return;
   }

   frequency = m_desiredFrequency;
   int channelStart = m_timerPulseCtrl->getChannelStart();
   int channelCount = m_timerPulseCtrl->getChannelCount();
   for(int i = channelStart; i < channelCount + channelStart; i++ )
   {
      errorCode = m_timerPulseCtrl->getChannels()->getItem(i).setFrequency(frequency);
      CheckError(errorCode);
   }

   for(int j = channelStart; j < channelCount + channelStart; j++ )
   {
      frequency = m_timerPulseCtrl->getChannels()->getItem(j).getFrequency();
   }
   errorCode = m_timerPulseCtrl->setEnabled(true);
   CheckError(errorCode);
   UpdateData(TRUE);
   m_generatedFrequency = frequency;

	m_eventCount = 0;
   UpdateData(FALSE);

   GetDlgItem(IDC_Start)->EnableWindow(FALSE);
   GetDlgItem(IDC_Stop)->EnableWindow(TRUE);
   GetDlgItem(IDC_Configure)->EnableWindow(FALSE);
   GetDlgItem(IDC_desiredFrequency)->EnableWindow(FALSE);

   m_executionStatus.Draw();
}

void CPulseOutputwithTimerInterruptDlg::OnStop()
{
   // TODO: Add your control notification handler code here
   ErrorCode errorCode = m_timerPulseCtrl->setEnabled(false);
   CheckError(errorCode);

   GetDlgItem(IDC_Start)->EnableWindow(TRUE);
   GetDlgItem(IDC_Configure)->EnableWindow(TRUE);
   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
   GetDlgItem(IDC_desiredFrequency)->EnableWindow(TRUE);

   m_executionStatus.Stop();
}

void CPulseOutputwithTimerInterruptDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
}
HBRUSH CPulseOutputwithTimerInterruptDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

CPulseOutputwithTimerInterruptDlg::~CPulseOutputwithTimerInterruptDlg()
{
   m_executionStatus.UnLoad();
   m_timerPulseCtrl->Dispose();
}

LRESULT CPulseOutputwithTimerInterruptDlg::OnUpdateEventCount(WPARAM wParam, LPARAM lParam)
{
   CString str;
   str.Format(_T("%d"), (int)wParam);
   GetDlgItem(IDC_eventCount)->SetWindowText(str);
   UpdateData(TRUE);
   return 0;
}

void CPulseOutputwithTimerInterruptDlg::OnCounterEvent(void * sender, CntrEventArgs * args, void * userParam)
{
  CPulseOutputwithTimerInterruptDlg* uParam = (CPulseOutputwithTimerInterruptDlg*)userParam;
  ::SendMessage(uParam->m_hWnd, WM_UPDATEMSG, uParam->m_eventCount++, 0);
}