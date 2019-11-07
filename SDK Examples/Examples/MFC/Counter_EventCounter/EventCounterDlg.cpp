// EventCountingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EventCounter.h"
#include "EventCounterDlg.h"

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


// CEventCounterDlg dialog
LRESULT CEventCounterDlg::OnConfDevice(WPARAM w,LPARAM l)
{
   int cancle = (int)w;
   if (cancle)
   {
      PostQuitMessage(0);
      return 0;
   }
   m_confParam = m_confDlg.GetParameter();
   ConfigurateDevice();
   m_counterValue.Format(_T("0"));  
   m_counterValueList.ResetContent();
   TRACE(("OnConfDevice\n"));
   return 0;
}

CEventCounterDlg::CEventCounterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEventCounterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   memset(&m_confParam, 0, sizeof(m_confParam));
   m_eventCounterCtrl = NULL;
}

CEventCounterDlg::~CEventCounterDlg()
{
   m_eventCounterCtrl->Dispose();
}

void CEventCounterDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_CounterValueList, m_counterValueList);
   DDX_Text(pDX, IDC_CounterValue, m_counterValue);
}

BEGIN_MESSAGE_MAP(CEventCounterDlg, CDialog)
   //{{AFX_MSG_MAP(CEventCounterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_Start, OnStart)
   ON_BN_CLICKED(IDC_Stop, OnStop)
   ON_BN_CLICKED(IDC_Configure, OnBnClickedButtonConfig)
   ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
   ON_WM_CTLCOLOR()
   ON_WM_TIMER()
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CEventCounterDlg message handlers

BOOL CEventCounterDlg::OnInitDialog()
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
   // the following is used to change the background picture of the Event Counting dialog
   CBitmap			bmp;
   bmp.LoadBitmap(IDB_Background);                 //IDB_Background is the ID of the background picture
   m_bkBk.CreatePatternBrush(&bmp);
   bmp.DeleteObject();
   
   m_confDlg.Create(IDD_CONFIGURATION,this);
   m_confDlg.ShowWindow(SW_SHOW);
   this->ShowWindow(SW_HIDE);
   this->EnableWindow(FALSE);
   m_eventCounterCtrl = EventCounterCtrl::Create();
   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
   
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEventCounterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEventCounterDlg::OnPaint()
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
HCURSOR CEventCounterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
//This function is used to handle the errorCode information
void CEventCounterDlg::CheckError(ErrorCode errorCode)
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

void CEventCounterDlg::OnStart()
{
   CString start;
   GetDlgItem(IDC_Start)->GetWindowText(start);
   // TODO: Add your control notification handler code here
   ErrorCode errorCode;
   if (0 == start.Compare(_T("Start")))
   {
      m_counterValueList.ResetContent();
      //Start Event Counting function.
      errorCode = m_eventCounterCtrl->setEnabled(true);
      CheckError(errorCode);
      SetTimer(0, 40, NULL);
      GetDlgItem(IDC_Stop)->EnableWindow(TRUE);
      GetDlgItem(IDC_Configure)->EnableWindow(FALSE);
      GetDlgItem(IDC_Start)->SetWindowText(_T("Latch"));
   }
   else
   {
      UpdateData(TRUE);
      m_counterValueList.AddString(m_counterValue);
      if (m_counterValueList.GetCount() > 8)
      {
         m_counterValueList.DeleteString(0);
      }
   } 
}

void CEventCounterDlg::OnStop()
{
   // TODO: Add your control notification handler code here
   // Stop the user Timer
   KillTimer(0);

   GetDlgItem(IDC_Start)->SetWindowText(_T("Start"));
   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
   GetDlgItem(IDC_Configure)->EnableWindow(TRUE);
   
   ErrorCode errorCode = m_eventCounterCtrl->setEnabled(FALSE);
   CheckError(errorCode);
}

void CEventCounterDlg::OnBnClickedButtonConfig()
{
   // TODO: Add your control notification handler code here
   KillTimer(0);
   this->EnableWindow(FALSE);
   m_confDlg.ShowWindow(SW_SHOW);
}

HBRUSH CEventCounterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CEventCounterDlg::OnTimer(UINT_PTR nIDEvent)
{
   // TODO: Add your message handler code here and/or call default
   ErrorCode errorCode;
   errorCode = m_eventCounterCtrl->setEnabled(TRUE);
   CheckError(errorCode);
   int32 value = 0;
   m_eventCounterCtrl->Read(1, &value);
   m_counterValue.Format(_T("%d"),value);  
   UpdateData(FALSE);
   CDialog::OnTimer(nIDEvent);
}


void CEventCounterDlg::ConfigurateDevice()
{
   ErrorCode	errorCode;
   DeviceInformation devInfo(m_confParam.deviceNumber);
   errorCode = m_eventCounterCtrl->setSelectedDevice(devInfo);
   CheckError(errorCode);
	errorCode = m_eventCounterCtrl->LoadProfile(m_confParam.profilePath);
	CheckError(errorCode);

   m_eventCounterCtrl->getSelectedDevice(devInfo);
   CString str ;
   TCHAR des[MAX_DEVICE_DESC_LEN];
   str.Format(_T("Event Counter - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
   SetWindowText(str);
   errorCode = m_eventCounterCtrl->setChannelCount(1);
	CheckError(errorCode);
   errorCode = m_eventCounterCtrl->setChannelStart(m_confParam.channel);
   CheckError(errorCode);
}
