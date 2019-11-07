// DiInterruptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DIInterrupt.h"
#include "DIInterruptDlg.h"
//#include <string>
//#include <stdio.h> 
using namespace std;

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

// CDIInterruptDlg dialog
CDIInterruptDlg::CDIInterruptDlg(CWnd* pParent /*=NULL*/)
: CDialog(CDIInterruptDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(&m_confParam, 0, sizeof(m_confParam));
}

CDIInterruptDlg::~CDIInterruptDlg()
{
	m_gifPic.UnLoad();
   m_instantDiCtrl->Dispose();
}

void CDIInterruptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_GIFPIC, m_gifPic);
}

BEGIN_MESSAGE_MAP(CDIInterruptDlg, CDialog)
//{{AFX_MSG_MAP(CDIInterruptDlg)
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

// CDIInterruptDlg message handlers
LRESULT CDIInterruptDlg::OnConfDevice(WPARAM w,LPARAM l)
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

BOOL CDIInterruptDlg::OnInitDialog()
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
   m_instantDiCtrl->addInterruptHandler(OnDiSnapEvent, this);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDIInterruptDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDIInterruptDlg::OnPaint()
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
		//CDialog::OnPaint();
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
		dc.StretchBlt(-68, -35, bitmap.bmWidth, bitmap.bmHeight, &dcMem, 
			0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);  
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDIInterruptDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
//This function is used to handle the errorCode information
void CDIInterruptDlg::CheckError(ErrorCode errorCode)
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

void CDIInterruptDlg::OnBnClickedConfig()
{
   this->EnableWindow(FALSE);
   m_confDlg.ShowWindow(SW_SHOW);
}

void CDIInterruptDlg::OnClickedStart()
{
   m_list.DeleteAllItems();
   this->m_eventCount = 0;
   GetDlgItem(IDC_START)->EnableWindow(FALSE);
   GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
   GetDlgItem(IDC_CONFIG)->EnableWindow(FALSE);
   m_gifPic.Draw();
   m_instantDiCtrl->SnapStart();
}

void CDIInterruptDlg::OnClickedStop()
{
	m_gifPic.Stop();
   ErrorCode errorCode = m_instantDiCtrl->SnapStop();
   CheckError(errorCode);
	
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_CONFIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
}

LRESULT CDIInterruptDlg::OnUpdateList(WPARAM wParam, LPARAM lParam)
{
   DiSnapEventArgs * args = (DiSnapEventArgs *)lParam;
   this->m_eventCount = (int)wParam;
   int itemCount = this->m_eventCount;
   if (itemCount > 10)
   {
      m_list.DeleteItem(0);
      itemCount = 10;
   }

	//row 1
	CString changedNo;
	changedNo.Format(_T("%d"),args->SrcNum);
	m_list.InsertItem(itemCount-1, ((CString)"           "+changedNo));
	
	//row 2   
   int portCount = args->Length;
	CString valueString;
	for (int i = 0; i < portCount; i++)
	{
		CString portData;
		portData.Format(_T("%X"),args->PortData[i]);
		valueString = valueString + portData;
		if ( i < portCount -1)
		{
			valueString = valueString + (CString)", ";
		}             
	}    
	m_list.SetItemText(itemCount-1, 1, valueString );
	return 0;
}

void CDIInterruptDlg::ConfigureDevice()
{
   ErrorCode	errorCode;
   DeviceInformation devInfo(m_confParam.deviceNumber);
   errorCode = m_instantDiCtrl->setSelectedDevice(devInfo);
   CheckError(errorCode);
	errorCode = m_instantDiCtrl->LoadProfile(m_confParam.profilePath);
	CheckError(errorCode);

   m_instantDiCtrl->getSelectedDevice(devInfo);
   CString str ;
   TCHAR des[MAX_DEVICE_DESC_LEN];
   str.Format(_T("DI Interrupt - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
   SetWindowText(str);

   Array<DiintChannel>* interruptChans = m_instantDiCtrl->getDiintChannels();
   int intPortCount = interruptChans->getCount();
   for ( int i = 0; i < m_confParam.enabledCount; ++i)
   {
      for (int j = 0; j < intPortCount; ++j)
      {
         if (m_confParam.diEnableChannel[i] == interruptChans->getItem(j).getChannel())
         {
            errorCode = interruptChans->getItem(j).setEnabled(true);
            CheckError(errorCode);
            TRACE("enable: %d, %d\n", i, j);
            break;
         }
      }
   }
}

void CDIInterruptDlg::ConfigurePanel()
{
   //initialize the list for data
   int portCount = m_instantDiCtrl->getPortCount();
   m_list.DeleteAllItems();
   m_list.DeleteColumn(0);
   m_list.DeleteColumn(0);
   int with = (portCount <= 10)?207:207+(portCount-10)*20;
   m_list.SetColumnWidth(1,with);

   //initialize the list for data
   m_list.InsertColumn(0, _T("INT Channel"), LVCFMT_CENTER, 92);
   CString columnText;
   columnText.Format(_T("DI ports value (Port 0~%d)"),(portCount-1));
   m_list.InsertColumn(1, columnText, LVCFMT_LEFT,with );

   GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
}

void CDIInterruptDlg::OnDiSnapEvent(void * sender, DiSnapEventArgs * args, void * userParam)
{
   CDIInterruptDlg * uParam = (CDIInterruptDlg *)userParam;
   HWND hWnd = uParam->m_hWnd;
   uParam->m_eventCount++;
   ::SendMessage(hWnd,WM_UPDATELIST,uParam->m_eventCount,(LPARAM)args);
}