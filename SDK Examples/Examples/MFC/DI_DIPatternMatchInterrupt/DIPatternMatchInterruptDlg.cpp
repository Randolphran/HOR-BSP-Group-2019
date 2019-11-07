// DI Pattern MatchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DIPatternMatchInterrupt.h"
#include "DIPatternMatchInterruptDlg.h"
#include <string>
#include <stdio.h> 
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About
extern TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out);

//int eventCount = 0;
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
{}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// CDIPatternMatchInterruptDlg dialog

CDIPatternMatchInterruptDlg::CDIPatternMatchInterruptDlg(CWnd* pParent /*=NULL*/)
: CDialog(CDIPatternMatchInterruptDlg::IDD, pParent)
{
   m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   memset(&m_confParam, 0, sizeof(m_confParam));
}

CDIPatternMatchInterruptDlg::~CDIPatternMatchInterruptDlg()
{
   m_gifPic.UnLoad();
   m_instantDiCtrl->Dispose();
}


void CDIPatternMatchInterruptDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST, m_list);
   DDX_Control(pDX, IDC_GIFPIC, m_gifPic);
}

BEGIN_MESSAGE_MAP(CDIPatternMatchInterruptDlg, CDialog)
//{{AFX_MSG_MAP(CDIPatternMatchInterruptDlg)
ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_CONFIG, OnBnClickedConfig)
ON_BN_CLICKED(IDC_START, OnClickedStart)
ON_BN_CLICKED(IDC_STOP, OnClickedStop)
ON_MESSAGE(WM_UPDATELIST, OnUpdateList)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CInstantDIDlg message handlers
LRESULT CDIPatternMatchInterruptDlg::OnConfDevice(WPARAM w,LPARAM l)
{
   int cancle = (int)w;
   if (cancle)
   {
      PostQuitMessage(0);
      return 0;
   }
   m_confParam = m_confDlg.GetParameter();
   ConfigureDevice();
   ConfigurePanel();
   this->m_eventCount = 0;
   TRACE(("OnConfDevice\n"));
   return 0;
}

BOOL CDIPatternMatchInterruptDlg::OnInitDialog()
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
	
   //Initialize the gif picture
   if (m_gifPic.Load(MAKEINTRESOURCE(IDR_GIFPIC),_T("gaf")))
   {
		m_gifPic.Draw();
		Sleep(1000);
		m_gifPic.Stop();
   }
	
   // TODO: Add extra initialization here
   m_confDlg.Create(IDD_CONFIGURATION,this);
   m_confDlg.ShowWindow(SW_SHOW);
   this->ShowWindow(SW_HIDE);
   this->EnableWindow(FALSE);

   m_instantDiCtrl = InstantDiCtrl::Create();
   m_instantDiCtrl->addPatternMatchHandler(OnDiSnapEvent, this);
   return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDIPatternMatchInterruptDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDIPatternMatchInterruptDlg::OnPaint()
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
		CPaintDC   dc(this);   
		CRect   rect;   
		GetClientRect(&rect);   
		CDC   dcMem;   
		dcMem.CreateCompatibleDC(&dc);   
		CBitmap   bmpBackground;   
		bmpBackground.LoadBitmap(IDB_BACKRUN);   
		BITMAP   bitmap;   
		bmpBackground.GetBitmap(&bitmap);   
		CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
		dc.StretchBlt(-3, -3, bitmap.bmWidth, bitmap.bmHeight, &dcMem, 
			0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);  
   }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDIPatternMatchInterruptDlg::OnQueryDragIcon()
{
   return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
//This function is used to handle the errorCode information
void CDIPatternMatchInterruptDlg::CheckError(ErrorCode errorCode)
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

void CDIPatternMatchInterruptDlg::ConfigurePanel()
{
   //initialize the list for data
   int portCount = m_instantDiCtrl->getPortCount();
   m_list.DeleteAllItems();
   m_list.DeleteColumn(0);
   m_list.DeleteColumn(0);
   int width = (portCount <= 10)?207:207+(portCount-10)*20;
   m_list.SetColumnWidth(1,width);

   //initialize the list for data
   m_list.InsertColumn(0, _T("Matched No#"), LVCFMT_CENTER, 92);
   CString ColumnText;
   ColumnText.Format(_T("DI ports value (Port 0~%d)"),(portCount-1));
   m_list.InsertColumn(1, (ColumnText), LVCFMT_LEFT,width );

   GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
}


//This function is used to config device with config parameter.
void CDIPatternMatchInterruptDlg::ConfigureDevice()
{
   DeviceInformation devInfo(m_confParam.deviceNumber);
   ErrorCode errorCode = m_instantDiCtrl->setSelectedDevice(devInfo);
   CheckError(errorCode);
	errorCode = m_instantDiCtrl->LoadProfile(m_confParam.profilePath);
	CheckError(errorCode);

   m_instantDiCtrl->getSelectedDevice(devInfo);
   CString str ;
   TCHAR des[MAX_DEVICE_DESC_LEN];
   str.Format(_T("DI Pattern Match Interrupt - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
   SetWindowText(str);
   
   Array<DiPmintPort>* diPmintPorts = m_instantDiCtrl->getDiPmintPorts();
   int pmPorts = diPmintPorts->getCount();
   for (int i = 0; i < pmPorts; ++i)
   {
      if (diPmintPorts->getItem(i).getPort() == m_confParam.selectedPort)
      {
         m_instantDiCtrl->getDiPmintPorts()->getItem(i).setMask(m_confParam.enabledChannels);
         m_instantDiCtrl->getDiPmintPorts()->getItem(0).setPattern(m_confParam.pmValue);
      }
   }
}

void CDIPatternMatchInterruptDlg::OnBnClickedConfig()
{
   this->EnableWindow(FALSE);
   m_confDlg.ShowWindow(SW_SHOW);
}

void CDIPatternMatchInterruptDlg::OnClickedStart()
{
   m_list.DeleteAllItems();
   this->m_eventCount = 0;
   GetDlgItem(IDC_START)->EnableWindow(FALSE);
   GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
   GetDlgItem(IDC_CONFIG)->EnableWindow(FALSE);
	m_gifPic.Draw();

   ErrorCode errorCode = m_instantDiCtrl->SnapStart();
   CheckError(errorCode);
}

void CDIPatternMatchInterruptDlg::OnClickedStop()
{
   m_gifPic.Stop();
   GetDlgItem(IDC_START)->EnableWindow(TRUE);
   GetDlgItem(IDC_CONFIG)->EnableWindow(TRUE);
   GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
   ErrorCode errorCode = m_instantDiCtrl->SnapStop();
   CheckError(errorCode);
}

LRESULT CDIPatternMatchInterruptDlg::OnUpdateList(WPARAM wParam, LPARAM lParam)
{
   this->m_eventCount = (int)wParam;
   DiSnapEventArgs * args = (DiSnapEventArgs *)lParam;
   int itemCount = (int)wParam;
   if (itemCount > 10)
   {
		m_list.DeleteItem(0);
		itemCount = 10;
   }
   //row 1
   CString changedNo;
   changedNo.Format(_T("%d"), this->m_eventCount);
   m_list.InsertItem((itemCount - 1), ((CString)"           "+changedNo));
	
   //row 2   
   CString valueString;
   for (int i = 0; i < args->Length; i++)
   {
		CString portData;
		portData.Format(_T("%X"),args->PortData[i]);
		valueString = valueString + portData;
		if ( i < args->Length -1)
		{
			valueString = valueString + (CString)", ";
		}             
   }    
   m_list.SetItemText((itemCount - 1), 1, valueString );
   return 0;
}


void CDIPatternMatchInterruptDlg::OnDiSnapEvent(void * sender, DiSnapEventArgs * args, void * userParam)
{
   CDIPatternMatchInterruptDlg * uParam = (CDIPatternMatchInterruptDlg *)userParam;
   HWND hWnd = uParam->m_hWnd;
   uParam->m_eventCount++;
   ::SendMessage(hWnd,WM_UPDATELIST,uParam->m_eventCount,(LPARAM)args);
}