// Instant DoDlg.cpp : implementation file
//
#include "stdafx.h"
#include "StaticDO.h"
#include "StaticDODlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CAboutDlg dialog used for APP About
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


// CStaticDODlg dialog
CStaticDODlg::CStaticDODlg(CWnd* pParent /*=NULL*/)
: CDialog(CStaticDODlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   m_instantDoCtrl = NULL;
	m_portNum0 = 0;
   m_confParam.deviceNumber = -1;
	for ( int i = 0; i < 64; i++ )
	{
		m_picBoxStatus[i] = -1;
	}
}

CStaticDODlg::~CStaticDODlg()
{
}

void CStaticDODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR, m_scrollBar);
}

BEGIN_MESSAGE_MAP(CStaticDODlg, CDialog)
//{{AFX_MSG_MAP(CStaticDODlg)
ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_CONTROL_RANGE(STN_CLICKED,IDC_PICT00,IDC_PCIT77, OnClick)
ON_BN_CLICKED(IDC_CONFIG, OnBnClickedConfig)
ON_WM_VSCROLL()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CStaticDODlg message handlers
LRESULT CStaticDODlg::OnConfDevice(WPARAM w,LPARAM l)
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
   TRACE(("OnConfDevice\n"));
   return 0;
}

BOOL CStaticDODlg::OnInitDialog()
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

   m_instantDoCtrl = InstantDoCtrl::Create();

	// Initialize m_device, m_cntr, control.
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
	m_imageList[0] = IDB_BUTTONUP;
	m_imageList[1] = IDB_BUTTONDOWN;
	m_imageList[2] = IDB_BUTTONDISABLE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStaticDODlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void CStaticDODlg::OnPaint()
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
		dc.StretchBlt(-40, -18, bitmap.bmWidth, bitmap.bmHeight, &dcMem, 
			0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);  
		// draw the rect
		CBrush brush;   
		brush.CreateSolidBrush(RGB(236,233,216));       
		CBrush* pOldBrush = dc.SelectObject(&brush); 
		dc.Rectangle(14,70,393,373);   
		dc.SelectObject(pOldBrush); 
		brush.DeleteObject(); 
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStaticDODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//This function is used to handle the errorCode information
void CStaticDODlg::CheckError(ErrorCode errorCode)
{
   if(BioFailed(errorCode))
   {
      CString str;
      str.Format(_T("Some errors happened, the error code is: 0x%X !\n"),errorCode);
      AfxMessageBox(str);
      this->EnableWindow(FALSE);
      this->m_confDlg.ShowWindow(SW_SHOW);
   }
}
void CStaticDODlg::ConfigurePanel()
{
   int portCountMax = m_instantDoCtrl->getFeatures()->getPortCount();
   if ( portCountMax < 9 )
   {
      m_scrollBar.ShowWindow(SW_HIDE);
   }
   else
   {
      if ( portCountMax >= 9 )
      {  
         m_scrollBar.ShowWindow(SW_SHOW);  		 
         int scrollMax = 303 + 38*( portCountMax - 8 );  //38 is one port height
         m_scrollBar.SetScrollRange(0, scrollMax);
         m_scrollBar.SetScrollPos(0);
         SCROLLINFO   info;
         info.fMask = SIF_PAGE; 
         info.nPage = 303;
         m_scrollBar.SetScrollInfo(&info,true); 
      }
   }
   InitPorts();
}
void CStaticDODlg::ConfigureDevice()
{
   ErrorCode	errorCode;
   DeviceInformation devInfo(m_confParam.deviceNumber);
   errorCode = m_instantDoCtrl->setSelectedDevice(devInfo);
   CheckError(errorCode);
	errorCode = m_instantDoCtrl->LoadProfile(m_confParam.profilePath);
	CheckError(errorCode);

   m_instantDoCtrl->getSelectedDevice(devInfo);
   CString str ;
   TCHAR des[MAX_DEVICE_DESC_LEN];
   str.Format(_T("Static DO - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
   SetWindowText(str);
}


void CStaticDODlg::OnBnClickedConfig()
{
   this->EnableWindow(FALSE);
   m_confDlg.ShowWindow(SW_SHOW);
}

void CStaticDODlg::InitPorts()
{
	SetAllPorts(false);  //false:hide; true:show
	for ( int k = 0; k < 64; k++ )
	{
		m_picBoxStatus[k] = -1;
	}
	m_portNum0 = 0;
   int portCountMax = m_instantDoCtrl->getFeatures()->getPortCount();
	byte * portsValue = new byte[portCountMax];
	ErrorCode errorCode = m_instantDoCtrl->Read(0, portCountMax, portsValue);

    CheckError(errorCode);

	int portCount = 0;
	if ( portCountMax < 9 )
	{
		portCount = portCountMax;
	}
	else
	{
		if ( portCountMax >=9 )
		{
			portCount = 8;
		}
	}
	
	CBitmap   bmp; 
	byte portData; 
	for (int i=0; i < portCount; i++ )
	{
		portData = 0;
		for ( int j = 0; j < 12; j++ )
		{
			// set the port number
			CString portNum;
			portNum.Format(_T("%d"),i);  
			GetDlgItem(m_ports[i][0])->SetWindowText(portNum);

			// set the portValue
			CString portVal;
			portVal.Format(_T("%X"),portsValue[i]);  
			GetDlgItem(m_ports[i][1])->SetWindowText(portVal);
			portData = drawButton(i, j, errorCode, i,portsValue);
		}

		/*if ( Success == errorCode )
		{		
			CString portVal;
			portVal.Format(_T("%X"),portData);  
			GetDlgItem(m_ports[i][1])->SetWindowText(portVal);
		}*/

      int *pPort = m_ports[i];
      for ( int i = 0; i < 12; i++ )
      {
         GetDlgItem(*(pPort++))->ShowWindow(SW_SHOW);
      }
	}	    
}

void CStaticDODlg::SetAllPorts( bool state)
{
	for ( int i = 0; i < 8; i++ )
	{
		for ( int j = 0; j < 12; j++ )
		{
			GetDlgItem(m_ports[i][j])->ShowWindow(state);
		}
	}
}

void CStaticDODlg::showPicture( int nID, int imageNum )
{
	CBitmap   bmp;   
	bmp.LoadBitmap(m_imageList[imageNum]); 
	((CStatic *)GetDlgItem(nID))->SetBitmap((HBITMAP)bmp); 
	bmp.Detach();
	CRect rc;
	GetDlgItem(nID)->GetClientRect(&rc);
	InvalidateRect(&rc,false);
}

void CStaticDODlg::OnClick(UINT nID)
{
	int clickCh = nID - IDC_PICT00;
	int clickPort = clickCh/8 ;

   m_picBoxStatus[clickCh] = (0 == m_picBoxStatus[clickCh])?1:0;
   showPicture(nID,(0 == m_picBoxStatus[clickCh])?0:1);
	byte portData = 0;
	for ( int i = 0; i < 8; i++)
	{   
		if ( 1 == m_picBoxStatus[8*clickPort+i])
		{
         portData = (byte)(portData | (1 << i));
		}
	}
	
	CString portVal;
	portVal.Format(_T("%X"),portData);  
	GetDlgItem(m_ports[clickPort][1])->SetWindowText(portVal);
	ErrorCode errorCode = m_instantDoCtrl->Write(clickPort+m_portNum0, 1, &portData);
	CheckError(errorCode);
}

void CStaticDODlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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
		refreshButton(iNewPos);
	case SB_LINEDOWN:
		iNewPos = m_scrollBar.GetScrollPos();
		iNewPos = iNewPos + 1;
		if ( iNewPos >info.nMax )
		{
			iNewPos = info.nMax;
		}
		m_scrollBar.SetScrollPos(iNewPos);
		refreshButton(iNewPos);
		break;
	case SB_LINEUP:
		iNewPos = m_scrollBar.GetScrollPos();
		iNewPos = iNewPos - 1;
		if ( iNewPos < 0 )
		{
			iNewPos = 0;
		}
		m_scrollBar.SetScrollPos(iNewPos);
		refreshButton(iNewPos);
		break;
	case SB_PAGEDOWN:
		iNewPos = m_scrollBar.GetScrollPos();
		iNewPos = iNewPos + 1;
		if ( iNewPos >info.nMax )
		{
			iNewPos = info.nMax;
		}
		m_scrollBar.SetScrollPos(iNewPos);
		refreshButton(iNewPos);
		break;
	case SB_PAGEUP:
		iNewPos = m_scrollBar.GetScrollPos();
		iNewPos = iNewPos - 1;
		if ( iNewPos < 0 )
		{
			iNewPos = 0;
		}
		m_scrollBar.SetScrollPos(iNewPos);
		refreshButton(iNewPos);
		break;
		}
	}
	CDialog::OnVScroll(nSBCode,nPos,pScrollBar);
}

void CStaticDODlg::refreshButton(int iNewPos)
{
   int portCount = m_instantDoCtrl->getFeatures()->getPortCount();
   byte * portValue = new byte[portCount];
	ErrorCode errorCode = m_instantDoCtrl->Read(0, portCount, portValue);
	CheckError(errorCode);

	int minPos = 0;
	int maxPos = 0;
	for ( int k = 0; k < (portCount-8+1); k++ )
	{	
		if ( 0 == k )
		{
			minPos = 0;
			maxPos = 19;
		}
		if ( (portCount-8+1) == k )
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
					portVal.Format(_T("%X"),portValue[portNumber]);  
					GetDlgItem(m_ports[i][1])->SetWindowText(portVal);
					
               byte portData = 0;
					for (int j=0; j < 12; j++)
					{
                  portData = drawButton( i, j, errorCode, portNumber,portValue);
					}
					if ( Success == errorCode )
					{		
						CString portVal;
						portVal.Format(_T("%X"),portData);  
						GetDlgItem(m_ports[i][1])->SetWindowText(portVal);
					}
				}
			}
		}
	}
   delete [] portValue;
}

byte CStaticDODlg::drawButton(int i, int j, ErrorCode ret, int  portNumber,byte * portValue)
{	
	int dicBitValue;
	int dataBitValue;
	byte portData = 0;
	if ( j > 3)
	{ 
      Array<uint8>* doDataMask = m_instantDoCtrl->getFeatures()->getDoDataMask();
      uint8 dataMask = doDataMask->getItem(portNumber);

		dicBitValue = (dataMask >>(j-4)) & 0x1;
		dataBitValue = (portValue[portNumber] >>(j-4)) & 0x1;
		
		if ( Success == ret )
		{
			if ( 0 == dicBitValue )
			{
				showPicture(m_ports[i][j],2);
				GetDlgItem(m_ports[i][j])->EnableWindow(FALSE);
				m_picBoxStatus[i*8+j-4] = 2;
			}
			else
			{	
				if ( 0 == dataBitValue )
				{
					GetDlgItem(m_ports[i][j])->EnableWindow(TRUE);
					showPicture(m_ports[i][j],0);
					m_picBoxStatus[i*8+j-4] = 0;
				}
				else
				{
					if ( 1 == dataBitValue )
					{
						GetDlgItem(m_ports[i][j])->EnableWindow(TRUE);
						showPicture(m_ports[i][j],1);
						m_picBoxStatus[i*8+j-4] = 1;
					}
				}
				if ( 1 == dicBitValue && 1 == dataBitValue )
				{
					portData = (byte)(portData | (1 << (j-4)));
				}
			}
		}
		else
		{
			if ( 0 == dataBitValue )
			{
				GetDlgItem(m_ports[i][j])->EnableWindow(true);
				showPicture(m_ports[i][j],0);
				m_picBoxStatus[i*8+j-4] = 0;
			}
			else
			{
				if ( 1 == dataBitValue )
				{
					GetDlgItem(m_ports[i][j])->EnableWindow(true);
					showPicture(m_ports[i][j],1);
					m_picBoxStatus[i*8+j-4] = 1;
				}
			}
		}
	}
	return portData;
}
