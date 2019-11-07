// InstantDIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DIStatusChangeInterrupt.h"
#include "DIStatusChangeInterruptDlg.h"
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


// CDIStatusChangeInterruptDlg dialog


CDIStatusChangeInterruptDlg::CDIStatusChangeInterruptDlg(CWnd* pParent /*=NULL*/)
: CDialog(CDIStatusChangeInterruptDlg::IDD, pParent)
{
   m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   memset(&m_confParam, 0, sizeof(m_confParam));
}

CDIStatusChangeInterruptDlg::~CDIStatusChangeInterruptDlg()
{
   m_gifPic.UnLoad();
   m_instantDiCtrl->Dispose();
}


void CDIStatusChangeInterruptDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_LIST, m_list);
   DDX_Control(pDX, IDC_GIF, m_gifPic);
}

BEGIN_MESSAGE_MAP(CDIStatusChangeInterruptDlg, CDialog)
//{{AFX_MSG_MAP(CDIStatusChangeInterruptDlg)
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


// CDIStatusChangeInterruptDlg message handlers
LRESULT CDIStatusChangeInterruptDlg::OnConfDevice(WPARAM w,LPARAM l)
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


BOOL CDIStatusChangeInterruptDlg::OnInitDialog()
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
   m_instantDiCtrl->addChangeOfStateHandler(OnDiSnapEvent, this);
   return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDIStatusChangeInterruptDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDIStatusChangeInterruptDlg::OnPaint()
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
		bmpBackground.LoadBitmap(IDB_BACKGROUND);   
		BITMAP   bitmap;   
		bmpBackground.GetBitmap(&bitmap);   
		CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
		dc.StretchBlt(-68, -43, bitmap.bmWidth, bitmap.bmHeight, &dcMem, 
			0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);  
   }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDIStatusChangeInterruptDlg::OnQueryDragIcon()
{
   return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
//This function is used to handle the errorCode information
void CDIStatusChangeInterruptDlg::CheckError(ErrorCode errorCode)
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

void CDIStatusChangeInterruptDlg::ConfigurePanel()
{
   //initialize the list for data
   int portCount = m_instantDiCtrl->getPortCount();
   m_list.DeleteAllItems();
   m_list.DeleteColumn(0);
   m_list.DeleteColumn(0);

   //initialize the list for data
   m_list.InsertColumn(0, _T("Changed No#"), LVCFMT_CENTER, 92);
   CString ColumnText;
   ColumnText.Format(_T("DI ports value (Port 0~%d)"),(portCount-1));
   int with = (portCount <= 10)?207:207+(portCount-10)*20;
   m_list.InsertColumn(1, ColumnText, LVCFMT_LEFT,with );

   GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
}
//

//This function is used to config device with config parameter.
void CDIStatusChangeInterruptDlg::ConfigureDevice()
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
   str.Format(_T("DI Status Change Interrupt - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
   SetWindowText(str);

   Array<DiCosintPort>* diCosintPorts = m_instantDiCtrl->getDiCosintPorts();
   int cosintPorts = diCosintPorts->getCount();
   for (int i = 0; i < cosintPorts; ++i)
   {
      if (diCosintPorts->getItem(i).getPort() == m_confParam.selectedPort)
      {
         m_instantDiCtrl->getDiCosintPorts()->getItem(i).setMask(m_confParam.enabledChannels);
      }
   }
}

void CDIStatusChangeInterruptDlg::OnBnClickedConfig()
{
   this->EnableWindow(FALSE);
   m_confDlg.ShowWindow(SW_SHOW);
}

void CDIStatusChangeInterruptDlg::OnClickedStart()
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

void CDIStatusChangeInterruptDlg::OnClickedStop()
{
   m_gifPic.Stop();
   GetDlgItem(IDC_START)->EnableWindow(TRUE);
   GetDlgItem(IDC_CONFIG)->EnableWindow(TRUE);
   GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
   ErrorCode errorCode = m_instantDiCtrl->SnapStop();
   CheckError(errorCode);
}

LRESULT CDIStatusChangeInterruptDlg::OnUpdateList(WPARAM wParam, LPARAM lParam)
{
   this->m_eventCount = (int)wParam;
   DiSnapEventArgs * args = (DiSnapEventArgs *)lParam;
   int itemCount = m_eventCount;
   if (itemCount > 10)
   {
		m_list.DeleteItem(0);
		itemCount = 10;
   }
   //Column 1
   CString changedNo;
   changedNo.Format(_T("%d"),m_eventCount);
   m_list.InsertItem((itemCount - 1), ((CString)"           "+changedNo));
	
   //Column 2   
   CString valueString;
   int portCount = this->m_instantDiCtrl->getPortCount();
   for (int i = 0; i < args->Length; i++)
   {
      //args->Length;
		CString portData;
		portData.Format(_T("%X"),args->PortData[i]);
		valueString = valueString + portData;
		if ( i < portCount -1)
		{
			valueString = valueString + (CString)", ";
		}             
   }    
   m_list.SetItemText((itemCount - 1), 1, valueString );
   return 0;
}

void CDIStatusChangeInterruptDlg::OnDiSnapEvent(void * sender, DiSnapEventArgs * args, void * userParam)
{
   CDIStatusChangeInterruptDlg * uParam = (CDIStatusChangeInterruptDlg *)userParam;
   HWND hWnd = uParam->m_hWnd;
   uParam->m_eventCount++;
   ::SendMessage(hWnd, WM_UPDATELIST, uParam->m_eventCount, (LPARAM)args);
}