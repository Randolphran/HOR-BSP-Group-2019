// PwMeterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PulseWidthMeasurement.h"
#include "PulseWidthMeasurementDlg.h"

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


// CPulseWidthMeasurementDlg dialog

CPulseWidthMeasurementDlg::CPulseWidthMeasurementDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPulseWidthMeasurementDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

   // Initialize data member of configForm class.
   m_PwMeterCtrl = NULL;
}

void CPulseWidthMeasurementDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_CounterValueList, m_counterValueList);
   DDX_Text(pDX, IDC_HiPeriod, m_hiPeriod);
   DDX_Text(pDX, IDC_LoPeriod, m_loPeriod);
}

BEGIN_MESSAGE_MAP(CPulseWidthMeasurementDlg, CDialog)
   //{{AFX_MSG_MAP(CPulseWidthMeasurementDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_Start, OnStart)
   ON_BN_CLICKED(IDC_Stop, OnStop)
   ON_BN_CLICKED(IDC_Configure, OnBnClickedButtonConfig)
   ON_WM_CTLCOLOR()
   ON_WM_TIMER()
   ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CPulseWidthMeasurementDlg message handlers
LRESULT CPulseWidthMeasurementDlg::OnConfDevice(WPARAM w,LPARAM l)
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
   m_hiPeriod.Format(_T(" "));  
   m_loPeriod.Format(_T(" ")); 
   UpdateData(FALSE);
   //GetDlgItem(IDC_shotCount)->SetWindowText(_T("0"));
   TRACE(("OnConfDevice\n"));
   return 0;
}

BOOL CPulseWidthMeasurementDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
   m_PwMeterCtrl = PwMeterCtrl::Create();
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
   // the following is used to change the background picture of the PulseWidthMeasurement dialog
   CBitmap			bmp;
   bmp.LoadBitmap(IDB_Background);                 //IDB_Background is the ID of the background picture
   m_bkBk.CreatePatternBrush(&bmp);
   bmp.DeleteObject();
   
   m_confDlg.Create(IDD_CONFIGURATION,this);
   m_confDlg.ShowWindow(SW_SHOW);
   this->ShowWindow(SW_HIDE);
   this->EnableWindow(FALSE);

   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);

   m_PwMeterCtrl = PwMeterCtrl::Create();
   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
   
   // Initialize m_device, m_cntr, control.
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPulseWidthMeasurementDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPulseWidthMeasurementDlg::OnPaint()
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
HCURSOR CPulseWidthMeasurementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
//This function is used to handle the errorCode information
void CPulseWidthMeasurementDlg::CheckError(ErrorCode errorCode)
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

void CPulseWidthMeasurementDlg::OnStart()
{
   // TODO: Add your control notification handler code here
   CString start;
   GetDlgItem(IDC_Start)->GetWindowText(start);
   // TODO: Add your control notification handler code here
   ErrorCode errorCode;
   if (0 == start.Compare(_T("Start")))
   {
      m_counterValueList.ResetContent();
      //Start Event Counting function.
      errorCode = m_PwMeterCtrl->setEnabled(true);
      CheckError(errorCode);
      SetTimer(0, 40, NULL);
      GetDlgItem(IDC_Stop)->EnableWindow(TRUE);
      GetDlgItem(IDC_Configure)->EnableWindow(FALSE);
      GetDlgItem(IDC_Start)->SetWindowText(_T("Latch"));
   }
   else
   {
      UpdateData(TRUE);
      m_counterValueList.AddString("High:"+m_hiPeriod+ " Low:"+m_loPeriod);
      if (m_counterValueList.GetCount() > 6)
      {
         m_counterValueList.DeleteString(0);
      }
   } 
}

void CPulseWidthMeasurementDlg::OnStop()
{
   // TODO: Add your control notification handler code here
   // Stop the user Timer
   KillTimer(0);

   GetDlgItem(IDC_Start)->SetWindowText(_T("Start"));
   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
   GetDlgItem(IDC_Configure)->EnableWindow(TRUE);
   
   ErrorCode errorCode = m_PwMeterCtrl->setEnabled(FALSE);
   CheckError(errorCode);   
}

void CPulseWidthMeasurementDlg::OnBnClickedButtonConfig()
{
   // TODO: Add your control notification handler code here
   this->EnableWindow(FALSE);
   m_confDlg.ShowWindow(SW_SHOW);
}

HBRUSH CPulseWidthMeasurementDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CPulseWidthMeasurementDlg::OnTimer(UINT_PTR nIDEvent)
{
   // TODO: Add your message handler code here and/or call default
   PulseWidth pwValue;
   m_PwMeterCtrl->Read(1, &pwValue);
   m_hiPeriod.Format(_T("%f"),pwValue.HiPeriod);  
   m_loPeriod.Format(_T("%f"),pwValue.LoPeriod); 
   UpdateData(FALSE);
   CDialog::OnTimer(nIDEvent);
}

CPulseWidthMeasurementDlg::~CPulseWidthMeasurementDlg()
{
   m_PwMeterCtrl->Dispose();
}

void CPulseWidthMeasurementDlg::ConfigurateDevice()
{
   ErrorCode	errorCode;
   DeviceInformation devInfo(m_confParam.deviceNumber);
   errorCode = m_PwMeterCtrl->setSelectedDevice(devInfo);
   CheckError(errorCode);
	errorCode = m_PwMeterCtrl->LoadProfile(m_confParam.profilePath);
	CheckError(errorCode);

   m_PwMeterCtrl->getSelectedDevice(devInfo);
   CString str ;
   TCHAR des[MAX_DEVICE_DESC_LEN];
   str.Format(_T("Pulse Width Measurement - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
   SetWindowText(str);
   
   errorCode = m_PwMeterCtrl->setChannelCount(1);
   CheckError(errorCode);
   errorCode = m_PwMeterCtrl->setChannelStart(m_confParam.channel);
   CheckError(errorCode);

}