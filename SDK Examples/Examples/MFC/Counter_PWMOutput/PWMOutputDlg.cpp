// PwModulatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include <malloc.h>
#include "PWMOutput.h"
#include "PWMOutputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPWMOutputDlg dialog
extern TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out);
CPWMOutputDlg::CPWMOutputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPWMOutputDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

   // Initialize data member of configForm class.
   m_pwModulatorCtrl = NULL;
}

void CPWMOutputDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_desiredHiPeriod, m_desiredHiPeriod);
   DDX_Text(pDX, IDC_desiredLoPeriod, m_desiredLoPeriod);
   DDX_Text(pDX, IDC_generatedHiPeriod, m_generatedHiPeriod);
   DDX_Text(pDX, IDC_generatedLoPeriod, m_generatedLoPeriod);
   DDX_Control(pDX, IDC_ExecutionStatus, m_executionStatus);
}

BEGIN_MESSAGE_MAP(CPWMOutputDlg, CDialog)
   //{{AFX_MSG_MAP(CPWMOutputDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_Configure, OnBnClickedButtonConfig)
   ON_BN_CLICKED(IDC_Start, OnStart)
   ON_BN_CLICKED(IDC_Stop, OnStop)
   ON_WM_CTLCOLOR()
   ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CPWMOutputDlg message handlers
LRESULT CPWMOutputDlg::OnConfDevice(WPARAM w,LPARAM l)
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

BOOL CPWMOutputDlg::OnInitDialog()
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
   m_desiredHiPeriod = 0.08;
   m_desiredLoPeriod = 0.02;
   m_generatedHiPeriod = 0.08;
   m_generatedLoPeriod = 0.02;

   m_pwModulatorCtrl = PwModulatorCtrl::Create();
   UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPWMOutputDlg::OnPaint()
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
HCURSOR CPWMOutputDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPWMOutputDlg::OnBnClickedButtonConfig()
{
   // TODO: Add your control notification handler code here
   this->EnableWindow(FALSE);
   m_confDlg.ShowWindow(SW_SHOW);
}

//////////////////////////////////////////////////////////////////////////
//This function is used to handle the errorCode information
void CPWMOutputDlg::CheckError(ErrorCode errorCode)
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

void CPWMOutputDlg::OnStart()
{
   ErrorCode errorCode;
   PulseWidth pulseWidth = {0.08,0.02};
   
   if (!UpdateData(TRUE))
   {
      TRACE("UpdateData failed during dialog termination.\n");
      // the UpdateData routine will set focus to correct item
      return;
   }

   pulseWidth.HiPeriod = m_desiredHiPeriod;
   pulseWidth.LoPeriod = m_desiredLoPeriod;

   for (int i = m_pwModulatorCtrl->getChannelStart(); i < m_pwModulatorCtrl->getChannelStart() + m_pwModulatorCtrl->getChannelCount(); i++)
   {
      errorCode = m_pwModulatorCtrl->getChannels()->getItem(i).setPulseWidth(pulseWidth);
      CheckError(errorCode);
   }
   
   errorCode = m_pwModulatorCtrl->setEnabled(true);
   CheckError(errorCode);

   m_generatedHiPeriod = pulseWidth.HiPeriod;
   m_generatedLoPeriod = pulseWidth.LoPeriod;
   UpdateData(FALSE);

   GetDlgItem(IDC_Start)->EnableWindow(FALSE);
   GetDlgItem(IDC_Stop)->EnableWindow(TRUE);
   GetDlgItem(IDC_Configure)->EnableWindow(FALSE);
   GetDlgItem(IDC_desiredHiPeriod)->EnableWindow(FALSE);
   GetDlgItem(IDC_desiredLoPeriod)->EnableWindow(FALSE);

   m_executionStatus.Draw();
}

void CPWMOutputDlg::OnStop()
{
   // TODO: Add your control notification handler code here
   ErrorCode errorCode;
   KillTimer(0);
   errorCode = m_pwModulatorCtrl->setEnabled(false);
   CheckError(errorCode);
   
   GetDlgItem(IDC_Start)->EnableWindow(TRUE);
   GetDlgItem(IDC_Configure)->EnableWindow(TRUE);
   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
   GetDlgItem(IDC_desiredHiPeriod)->EnableWindow(TRUE);
   GetDlgItem(IDC_desiredLoPeriod)->EnableWindow(TRUE);

   m_executionStatus.Stop();
}

HBRUSH CPWMOutputDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

CPWMOutputDlg::~CPWMOutputDlg()
{
   m_pwModulatorCtrl->Dispose();
   m_executionStatus.UnLoad();
}

void CPWMOutputDlg::ConfigurateDevice()
{
   ErrorCode	errorCode;
   DeviceInformation devInfo(m_confParam.deviceNumber);
   errorCode = m_pwModulatorCtrl->setSelectedDevice(devInfo);
   CheckError(errorCode);
	errorCode = m_pwModulatorCtrl->LoadProfile(m_confParam.profilePath);
	CheckError(errorCode);

   m_pwModulatorCtrl->getSelectedDevice(devInfo);
   CString str ;
   TCHAR des[MAX_DEVICE_DESC_LEN];
   str.Format(_T("PWM Output - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
   SetWindowText(str);
   errorCode= m_pwModulatorCtrl->setChannelCount(1);
   errorCode = m_pwModulatorCtrl->setChannelStart(m_confParam.channel);
   CheckError(errorCode);
}