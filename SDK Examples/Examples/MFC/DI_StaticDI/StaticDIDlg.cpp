// DI_InstantDlg.cpp : implementation file
//
#include "stdafx.h"
#include "StaticDI.h"
#include "StaticDIDlg.h"

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

// CInstantDIDlg dialog

CStaticDIDlg::CStaticDIDlg(CWnd* pParent /*=NULL*/)
: CDialog(CStaticDIDlg::IDD, pParent)
, m_portNum0(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   m_portData =  NULL;
	m_portCount = 0;
   m_portNum0 = 0;
   memset(&m_confParam, 0, sizeof(m_confParam));
}

CStaticDIDlg::~CStaticDIDlg()
{
	if ( m_portData != NULL )
	{
		delete[]m_portData;
		m_portData = NULL;
	}
}
void CStaticDIDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_SCROLLBAR, m_scrollBar);
}

BEGIN_MESSAGE_MAP(CStaticDIDlg, CDialog)
//{{AFX_MSG_MAP(CStaticDIDlg)
ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_CONFIG, OnBnClickedConfig)
ON_WM_TIMER()
ON_WM_VSCROLL()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CStaticDIDlg message handlers

LRESULT CStaticDIDlg::OnConfDevice(WPARAM w,LPARAM l)
{
   int cancle = (int)w;
   if (cancle)
   {
      PostQuitMessage(0);
      return 0;
   }
   m_confParam = m_confDlg.GetParameter();
   ConfigureDevice();
   ConfiguratePanel();
   TRACE(("OnConfDevice\n"));
   return 0;
}


BOOL CStaticDIDlg::OnInitDialog()
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
   m_confDlg.Create(IDD_CONFIGURATION,this);
   m_confDlg.ShowWindow(SW_SHOW);
   this->ShowWindow(SW_HIDE);
   this->EnableWindow(FALSE);

   m_instantDiCtrl = InstantDiCtrl::Create();
	int ports[8][12] = {{IDC_PORTNUM0,IDC_PORTVAL0,IDC_GROUPBOX00,IDC_GROUPBOX01,IDC_PICT00,IDC_PCIT01,IDC_PCIT02,IDC_PCIT03,IDC_PCIT04,IDC_PCIT05,IDC_PCIT06,IDC_PCIT07},       
	{IDC_PORTNUM1,IDC_PORTVAL1,IDC_GROUPBOX10,IDC_GROUPBOX11,IDC_PCIT10,IDC_PCIT11,IDC_PCIT12,IDC_PCIT13,IDC_PCIT14,IDC_PCIT15,IDC_PCIT16,IDC_PCIT17},
	{IDC_PORTNUM2,IDC_PORTVAL2,IDC_GROUPBOX20,IDC_GROUPBOX21,IDC_PCIT20,IDC_PCIT21,IDC_PCIT22,IDC_PCIT23,IDC_PCIT24,IDC_PCIT25,IDC_PCIT26,IDC_PCIT27},
	{IDC_PORTNUM3,IDC_PORTVAL3,IDC_GROUPBOX30,IDC_GROUPBOX31,IDC_PCIT30,IDC_PCIT31,IDC_PCIT32,IDC_PCIT33,IDC_PCIT34,IDC_PCIT35,IDC_PCIT36,IDC_PCIT37},
	{IDC_PORTNUM4,IDC_PORTVAL4,IDC_GROUPBOX40,IDC_GROUPBOX41,IDC_PCIT40,IDC_PCIT41,IDC_PCIT42,IDC_PCIT43,IDC_PCIT44,IDC_PCIT45,IDC_PCIT46,IDC_PCIT47},
	{IDC_PORTNUM5,IDC_PORTVAL5,IDC_GROUPBOX50,IDC_GROUPBOX51,IDC_PCIT50,IDC_PCIT51,IDC_PCIT52,IDC_PCIT53,IDC_PCIT54,IDC_PCIT55,IDC_PCIT56,IDC_PCIT57},
	{IDC_PORTNUM6,IDC_PORTVAL6,IDC_GROUPBOX60,IDC_GROUPBOX61,IDC_PCIT60,IDC_PCIT61,IDC_PCIT62,IDC_PCIT63,IDC_PCIT64,IDC_PCIT65,IDC_PCIT66,IDC_PCIT67},
	{IDC_PORTNUM7,IDC_PORTVAL7,IDC_GROUPBOX70,IDC_GROUPBOX71,IDC_PCIT70,IDC_PCIT71,IDC_PCIT72,IDC_PCIT73,IDC_PCIT74,IDC_PCIT75,IDC_PCIT76,IDC_PCIT77}};
	
	for ( int i = 0; i < 8; i++ )
	{
		for ( int j = 0; j < 12; j++ )
		{
			m_ports[i][j] = ports[i][j]; 
		}
	}
   m_imageList[0] = IDB_LEDLOW;
	m_imageList[1] = IDB_LEDHIGH;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStaticDIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CStaticDIDlg::OnPaint()
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
		//add the background picture
		CPaintDC   dc(this);   
		CRect   rect;   
		GetClientRect(&rect);   
		CDC   dcMem;   
		dcMem.CreateCompatibleDC(&dc);   
		CBitmap   bmpBackground;   
		bmpBackground.LoadBitmap(IDB_BACK);     
		BITMAP   bitmap;   
		bmpBackground.GetBitmap(&bitmap);   
		CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
		dc.StretchBlt(-38, -30, bitmap.bmWidth, bitmap.bmHeight, &dcMem, 
			0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);  
		// draw rect
		CBrush brush;   
		brush.CreateSolidBrush(RGB(236,233,216));       
		CBrush* pOldBrush = dc.SelectObject(&brush); 
		dc.Rectangle(14,58,393,361);   
		dc.SelectObject(pOldBrush); 
		brush.DeleteObject(); 
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStaticDIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//This function is used to handle the errorCode information
void CStaticDIDlg::CheckError(ErrorCode errorCode)
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

void CStaticDIDlg::ConfiguratePanel()
{
   
   //Initialize the scroll bar 
   m_portCount = m_instantDiCtrl->getFeatures()->getPortCount();
   if ( m_portCount < 9 )
   {
		m_scrollBar.ShowWindow(SW_HIDE);
   }
	else
	{
		if ( m_portCount >= 9 )
		{  
			m_scrollBar.ShowWindow(SW_SHOW);  		 
			int scrollMax = 303 + 38*( m_portCount - 8 );  //38 is one port height
			m_scrollBar.SetScrollRange(0, scrollMax);
			m_scrollBar.SetScrollPos(0);
			SCROLLINFO   info;
			info.fMask = SIF_PAGE;
			info.nPage = 303;
			m_scrollBar.SetScrollInfo(&info,true); 
		}
   }
   InitPorts();
   SetTimer(0,100,NULL);
}

void CStaticDIDlg::ConfigureDevice()
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
   str.Format(_T("Static DI - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
   SetWindowText(str);
}

void CStaticDIDlg::OnBnClickedConfig()
{
	KillTimer(0);
   this->EnableWindow(FALSE);
   m_confDlg.ShowWindow(SW_SHOW);
}

void CStaticDIDlg::InitPorts()
{
   SetAllPorts(false);  //false:hide; true:show
   m_portData = new byte[m_portCount];
   ErrorCode errorCode = m_instantDiCtrl->Read(0, m_portCount, m_portData);
   CheckError(errorCode);
   m_portNum0 = 0;
   int portCount = 0;
   if ( m_portCount < 9 )
   {
      portCount = m_portCount;
   }
   else
   {
		if ( m_portCount >=9 )
		{
			portCount = 8;
		}
   }
   for (int i=0; i<portCount; i++)
   {
		for ( int j = 0; j < 12; j++ )
      {
			CString portNum;
			portNum.Format(_T("%d"),i);  
			GetDlgItem(m_ports[i][0])->SetWindowText(portNum);
			CString portVal;
			portVal.Format(_T("%X"),m_portData[i]);  
			GetDlgItem(m_ports[i][1])->SetWindowText(portVal);
			int bitValue;
         if ( j > 3)
			{ 
				bitValue = (m_portData[i] >>(j-4)) & 0x1;
				CBitmap   bmp;   
				bmp.LoadBitmap(m_imageList[bitValue]); 
				CStatic *pStatic = (CStatic *)GetDlgItem(m_ports[i][j]);
				pStatic->SetBitmap((HBITMAP)bmp); 
				bmp.Detach();  
				CRect rc;
				GetDlgItem(m_ports[i][j])->GetClientRect(&rc);
				InvalidateRect(&rc,false);
         }
      }
		ShowPort(m_ports[i]);
   }	    
}

void CStaticDIDlg::ShowPort(int *pPort)
{
   for ( int i = 0; i < 12; i++ )
   {
		GetDlgItem(*(pPort++))->ShowWindow(SW_SHOW);
   }
}
void CStaticDIDlg::SetAllPorts( bool state)
{
   for ( int i = 0; i < 8; i++ )
   {
		for ( int j = 0; j < 12; j++ )
		{
			GetDlgItem(m_ports[i][j])->ShowWindow(state);
		}
   }
}

void CStaticDIDlg::OnTimer(UINT_PTR nIDEvent)
{
   byte* portData = new byte[m_portCount];
   for ( int k = 0; k < m_portCount; k++ )
   {
		portData[k] = m_portData[k];
   }
   ErrorCode errorCode = m_instantDiCtrl->Read(0, m_portCount, m_portData);

	CheckError(errorCode);

   CString portVal; 
	
   int newBitValue = 0;
   int oldBitValue = 0;
   int portCount = 0;
   if ( m_portCount < 9 )
   {
		portCount = m_portCount;
   }
   else
   {
		if ( m_portCount >9 )
		{
			portCount = 8;
		}
   }
   for ( int i = 0; i < portCount; i++ )
   {
		for ( int j = 0; j < 12; j++ )
		{		 
			if ( j > 3)
			{  
				oldBitValue = (portData[i+m_portNum0] >>(j-4)) & 0x1;
				newBitValue = (m_portData[i+m_portNum0] >>(j-4)) & 0x1;
				if ( newBitValue != oldBitValue )
				{
					CBitmap  bmp;   
					bmp.LoadBitmap(m_imageList[newBitValue]); 
					((CStatic*)GetDlgItem(m_ports[i][j]))->SetBitmap((HBITMAP)bmp);
					bmp.Detach();
					CRect rc;
					GetDlgItem(m_ports[i][j])->GetClientRect(&rc);
					InvalidateRect(&rc,false);
               //refresh the port value
					portVal.Format(_T("%X"),m_portData[i+m_portNum0]);  
					GetDlgItem(m_ports[i][1])->SetWindowText(portVal);
				}
			}
		}
   }
	if ( portData != NULL)
	{
		delete []portData;
		portData = NULL;
	}
   CDialog::OnTimer(nIDEvent);
}

void CStaticDIDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
   SCROLLINFO   info;
   m_scrollBar.GetScrollInfo(&info);
   int iNewPos;
   int length = info.nMax - 303;
   switch(nSBCode)
   {
		if ( &m_scrollBar == pScrollBar )
		{
      	case SB_THUMBTRACK:
				m_scrollBar.SetScrollPos(nPos);
				iNewPos = m_scrollBar.GetScrollPos();
				refreshLed(iNewPos);
			case SB_LINEDOWN:
				iNewPos = m_scrollBar.GetScrollPos();
				iNewPos = iNewPos + 1;
			 	if ( iNewPos >info.nMax )
				{
					iNewPos = info.nMax;
				}
				m_scrollBar.SetScrollPos(iNewPos);
            refreshLed(iNewPos);
				break;
			case SB_LINEUP:
				iNewPos = m_scrollBar.GetScrollPos();
				iNewPos = iNewPos - 1;
				if ( iNewPos < 0 )
				{
					iNewPos = 0;
				}
				m_scrollBar.SetScrollPos(iNewPos);
				refreshLed(iNewPos);
				break;
			case SB_PAGEDOWN:
				iNewPos = m_scrollBar.GetScrollPos();
				iNewPos = iNewPos + 1;
				if ( iNewPos >info.nMax )
				{
					iNewPos = info.nMax;
				} 
				m_scrollBar.SetScrollPos(iNewPos);
				refreshLed(iNewPos);
				break;
			case SB_PAGEUP:
				iNewPos = m_scrollBar.GetScrollPos();
				iNewPos = iNewPos - 1;
				if ( iNewPos < 0 )
				{
					iNewPos = 0;
				}
				m_scrollBar.SetScrollPos(iNewPos);
				refreshLed(iNewPos);
				break;
		}
	}
   CDialog::OnVScroll(nSBCode,nPos,pScrollBar);
}

void CStaticDIDlg::refreshLed(int iNewPos)
{
   int minPos = 0;
   int maxPos = 0;
   for ( int k = 0; k < (m_portCount-8+1); k++ )
   {	
		if ( 0 == k )
		{
			minPos = 0;
			maxPos = 19;
		}
		if ( (m_portCount-8+1) == k )
		{
			minPos = 38*k-19;
			maxPos = 38*k;
		}
		minPos = 38*k-19;
		maxPos = 38*k+19;
		if ( minPos< iNewPos && iNewPos < maxPos )
		{			
			if ( k != m_portNum0 )
			{	
				m_portNum0 = k;
				for ( int i = 0; i < 8 ; i++ )
				{	
					int portNumber = i+k;		   
					CString portNum;
					portNum.Format(_T("%d"), portNumber);  
					GetDlgItem(m_ports[i][0])->SetWindowText(portNum);
					CString portVal;
					portVal.Format(_T("%X"),m_portData[portNumber]);  
					GetDlgItem(m_ports[i][1])->SetWindowText(portVal);
					
					for (int j=0; j < 12; j++)
					{
						int bitValue;
						if ( j > 3)
						{ 
							bitValue = (m_portData[portNumber] >>(j-4)) & 0x1;
							CBitmap   bmp;   
							bmp.LoadBitmap(m_imageList[bitValue]); 
							CStatic *pStatic = (CStatic *)GetDlgItem(m_ports[i][j]);
							pStatic->SetBitmap((HBITMAP)bmp); 
							bmp.Detach();
							CRect rc;
							GetDlgItem(m_ports[i][j])->GetClientRect(&rc);
							InvalidateRect(&rc,false);
						}
					}
				}
			}
		}
   }
}
