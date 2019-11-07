// OneShotDlg.cpp : implementation file
//

#include "stdafx.h"
#include <malloc.h>
#include "DelayedPulseGeneration.h"
#include "DelayedPulseGenerationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDelayedPulseGenerationDlg dialog
extern TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out);
CDelayedPulseGenerationDlg::CDelayedPulseGenerationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDelayedPulseGenerationDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   
   // Initialize data member of configForm class.
   m_oneShotCtrl = NULL;
   memset(&m_confParam, 0, sizeof(m_confParam));
}

void CDelayedPulseGenerationDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_clockCount, m_clockCount);
}

BEGIN_MESSAGE_MAP(CDelayedPulseGenerationDlg, CDialog)
   //{{AFX_MSG_MAP(CDelayedPulseGenerationDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_WM_CTLCOLOR()
   ON_BN_CLICKED(IDC_Configure, OnBnClickedButtonConfig)
   ON_BN_CLICKED(IDC_Start, OnStart)
   ON_BN_CLICKED(IDC_Stop, OnStop)
   ON_MESSAGE(WM_UPDATEMSG, OnUpdateEventCount)
   ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)

   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
// CDelayedPulseGenerationDlg dialog
LRESULT CDelayedPulseGenerationDlg::OnConfDevice(WPARAM w,LPARAM l)
{
   int cancle = (int)w;
   if (cancle)
   {
      PostQuitMessage(0);
      return 0;
   }
   m_confParam = m_confDlg.GetParameter();
   ConfigurateDevice();
   GetDlgItem(IDC_shotCount)->SetWindowText(_T("0"));
   TRACE(("OnConfDevice\n"));
   return 0;
}

BOOL CDelayedPulseGenerationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
   //////////////////////////////////////////////////////////////////////////
   // the following is used to change the background picture of the One Shot dialog
   CBitmap			bmp;
   bmp.LoadBitmap(IDB_Background);                 //IDB_Background is the ID of the background picture
   m_bkBk.CreatePatternBrush(&bmp);
   bmp.DeleteObject();
   
   m_confDlg.Create(IDD_CONFIGURATION,this);
   m_confDlg.ShowWindow(SW_SHOW);
   this->ShowWindow(SW_HIDE);
   this->EnableWindow(FALSE);

   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
   m_clockCount = 1000;
   m_oneShotCtrl = OneShotCtrl::Create();
	m_eventCount = 0;

	//Caution: When OneShot interrupt is too frequent, the operating system may hang.
	//The following is the suggestion:
	//1.If you generate delayed pulse only, you don't need to deal with OneShot event.
	//2.If you want to use OneShot interrupt function, uncomment the following codes.
	
   //m_oneShotCtrl->addOneShotHandler(OnCounterEvent, this->m_hWnd);

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDelayedPulseGenerationDlg::OnPaint()
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
HCURSOR CDelayedPulseGenerationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


HBRUSH CDelayedPulseGenerationDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
void CDelayedPulseGenerationDlg::CheckError(ErrorCode errorCode)
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

void CDelayedPulseGenerationDlg::OnBnClickedButtonConfig()
{
   // TODO: Add your control notification handler code here
   this->EnableWindow(FALSE);
   m_confDlg.ShowWindow(SW_SHOW);
}

void CDelayedPulseGenerationDlg::OnStart()
{
   ErrorCode errorCode;

   if (!UpdateData(TRUE))
   {
      //TRACE(traceAppMsg, 0, _T("UpdateData failed during dialog termination.\n"));
      // the UpdateData routine will set focus to correct item
      return;
   }

   GetDlgItem(IDC_shotCount)->SetWindowText(_T("0"));
   MathInterval valueRange;
   m_oneShotCtrl->getFeatures()->getOsDelayCountRange(valueRange);
   double rangeMax = valueRange.Max;
   double rangeMin = valueRange.Min;
	
   if (m_clockCount > rangeMax || m_clockCount < rangeMin)
	{
		CString str(L"DelayCount is out of range:");
		CString str1;
		str1.Format(_T("(%d - %d)"),rangeMin,rangeMax);
		CString error = str + str1;
		AfxMessageBox(error);
		return;
	}
   errorCode = m_oneShotCtrl->setDelayCount(m_clockCount);
   CheckError(errorCode);
   int channelStart = m_oneShotCtrl->getChannelStart();
   int channelCount = m_oneShotCtrl->getChannelCount();
   for (int32 i = channelStart; i < channelStart + channelCount; i++)
   {
      errorCode = m_oneShotCtrl->getChannels()->getItem(i).setDelayCount(m_clockCount);
      CheckError(errorCode);
   }
   errorCode = m_oneShotCtrl->setEnabled(true);
   CheckError(errorCode);
	this->m_eventCount = 0;
  
   UpdateData(TRUE);
   
   GetDlgItem(IDC_Start)->EnableWindow(FALSE);
   GetDlgItem(IDC_Stop)->EnableWindow(TRUE);
   GetDlgItem(IDC_Configure)->EnableWindow(FALSE);
   GetDlgItem(IDC_clockCount)->EnableWindow(FALSE);
}

void CDelayedPulseGenerationDlg::OnStop()
{
   // TODO: Add your control notification handler code here
   ErrorCode errorCode = m_oneShotCtrl->setEnabled(FALSE);
   CheckError(errorCode);   
   GetDlgItem(IDC_Start)->EnableWindow(TRUE);
   GetDlgItem(IDC_Configure)->EnableWindow(TRUE);
   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
   GetDlgItem(IDC_clockCount)->EnableWindow(TRUE);
}

CDelayedPulseGenerationDlg::~CDelayedPulseGenerationDlg()
{
   m_oneShotCtrl->Dispose();
}

void CDelayedPulseGenerationDlg::ConfigurateDevice()
{
   ErrorCode	errorCode;
   DeviceInformation devInfo(m_confParam.deviceNumber);
   errorCode = m_oneShotCtrl->setSelectedDevice(devInfo);
   CheckError(errorCode);
	errorCode = m_oneShotCtrl->LoadProfile(m_confParam.profilePath);
	CheckError(errorCode);

   m_oneShotCtrl->getSelectedDevice(devInfo);
   CString str ;
   TCHAR des[MAX_DEVICE_DESC_LEN];
   str.Format(_T("Delayed Pulse Generation - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
   SetWindowText(str);
   errorCode = m_oneShotCtrl->setChannelCount(1);
   CheckError(errorCode);
   errorCode = m_oneShotCtrl->setChannelStart(m_confParam.channel);
   CheckError(errorCode);
}

LRESULT CDelayedPulseGenerationDlg::OnUpdateEventCount(WPARAM wParam, LPARAM lParam)
{
   CString str;
   str.Format(_T("%d"), (int)wParam);
   GetDlgItem(IDC_shotCount)->SetWindowText(str);
   return 0;
}

void CDelayedPulseGenerationDlg::OnCounterEvent(void * sender, CntrEventArgs * args, void * userParam)
{
	CDelayedPulseGenerationDlg* uParam = (CDelayedPulseGenerationDlg*) userParam;
	::SendMessage(uParam->m_hWnd, WM_UPDATEMSG, uParam->m_eventCount++, 0);
}