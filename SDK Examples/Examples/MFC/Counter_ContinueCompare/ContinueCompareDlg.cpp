// ContinueCompareDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ContinueCompare.h"
#include "ContinueCompareDlg.h"

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


// CContinueCompareDlg dialog
LRESULT CContinueCompareDlg::OnConfDevice(WPARAM w,LPARAM l)
{
	int cancle = (int)w;
	if (cancle)
	{
		PostQuitMessage(0);
		return 0;
	}
	int deviceNumber = m_confParam.deviceNumber;
	m_confParam = m_confDlg.GetParameter();
	ConfigurateDevice();
	m_counterValue.Format(_T("0"));  
	TRACE(("OnConfDevice\n"));
	return 0;
}

CContinueCompareDlg::CContinueCompareDlg(CWnd* pParent /*=NULL*/)
: CDialog(CContinueCompareDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(&m_confParam, 0, sizeof(m_confParam));
	m_udCounterCtrl = NULL;
	m_tabIndex = 0;

	//initialize the compare table
	m_tab1CompData0 = 100;
	m_tab1CompData1 = 340;
	m_tab1CompData2 = 720;
	m_tab2CompData0 = 1000;
	m_tab2CompData1 = 1980;
	m_tab2CompData2 = 2510;

	m_intrvl1FirVal = 150;
	m_intrvl1Cremt = 3;
	m_intrl1Count = 3;
	m_intrvl2FirVal = 210;
	m_intrvl2Cremt = 3;
	m_intrl2Count = 3;

}

CContinueCompareDlg::~CContinueCompareDlg()
{
	m_udCounterCtrl->Dispose();
}

void CContinueCompareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CounterValue, m_counterValue);
	DDX_Text(pDX,IDC_EDIT_TABLE1_DATA0,m_tab1CompData0);
	DDX_Text(pDX,IDC_EDIT_TABLE1_DATA1,m_tab1CompData1);
	DDX_Text(pDX,IDC_EDIT_TABLE1_DATA2,m_tab1CompData2);
	DDX_Text(pDX,IDC_EDIT_TABLE2_DATA0,m_tab2CompData0);
	DDX_Text(pDX,IDC_EDIT_TABLE2_DATA1,m_tab2CompData1);
	DDX_Text(pDX,IDC_EDIT_TABLE2_DATA2,m_tab2CompData2);

	DDX_Text(pDX,IDC_EDIT_INTERVAL1_FIRSTVALUE,m_intrvl1FirVal);
	DDX_Text(pDX,IDC_EDIT_INTERVAL1_INCREMENT,m_intrvl1Cremt);
	DDX_Text(pDX,IDC_EDIT_INTERVAL1_COUNT,m_intrl1Count);
	DDX_Text(pDX,IDC_EDIT_INTERVAL2_FIRSTVALUE,m_intrvl2FirVal);
	DDX_Text(pDX,IDC_EDIT_INTERVAL2_INCREMENT,m_intrvl2Cremt);
	DDX_Text(pDX,IDC_EDIT_INTERVAL2_COUNT,m_intrl2Count);

	DDX_Text(pDX,IDC_EDIT_PATTERN_MATCH_COUNT,m_matchCount);
	DDX_Text(pDX,IDC_EDIT_END_COUNT,m_endCount);
}

BEGIN_MESSAGE_MAP(CContinueCompareDlg, CDialog)
	//{{AFX_MSG_MAP(CContinueCompareDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Start, OnStart)
	ON_BN_CLICKED(IDC_Stop, OnStop)
	ON_BN_CLICKED(IDC_Configure, OnBnClickedButtonConfig)
	ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_MESSAGE(WM_UPDATE_CONTCOMP, OnUpdateContComp)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CContinueCompareDlg message handlers

BOOL CContinueCompareDlg::OnInitDialog()
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
	// the following is used to change the background picture of the Snap Counter dialog
	CBitmap			bmp;
	bmp.LoadBitmap(IDB_Background);                 //IDB_Background is the ID of the background picture
	m_bkBk.CreatePatternBrush(&bmp);
	bmp.DeleteObject();

	m_confDlg.Create(IDD_CONFIGURATION,this);
	m_confDlg.ShowWindow(SW_SHOW);
	this->ShowWindow(SW_HIDE);
	this->EnableWindow(FALSE);
	m_udCounterCtrl = UdCounterCtrl::Create();
	m_udCounterCtrl->addUdCntrEventHandler(OnUdCounterEvent, this);
	GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
	isFirst = TRUE;
	m_matchCount = 0;
	m_endCount = 0;
	UpdateData(FALSE);

	// default compare table is dispersed
	CheckDlgButton(IDC_RADIO_TABLE,1);
	m_contCompTabSel = dispersed;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CContinueCompareDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CContinueCompareDlg::OnPaint()
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
HCURSOR CContinueCompareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
//This function is used to handle the errorCode information
void CContinueCompareDlg::CheckError(ErrorCode errorCode)
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

void CContinueCompareDlg::OnStart()
{
	// TODO: Add your control notification handler code here
	ErrorCode errorCode;
	UpdateData(TRUE);
	// Set compare table
	int ComTable[3] = {0};
	LineTabParam param;
	m_contCompTabSel = IsDlgButtonChecked(IDC_RADIO_TABLE)? dispersed:lined;
	if (m_contCompTabSel == dispersed)
	{
		CreateDisperseTable(0,ComTable);
		m_udCounterCtrl->CompareSetTable(m_udCounterCtrl->getChannelStart(),3,ComTable);
	}else{
		CreateLineTable(0,param);
		m_udCounterCtrl->CompareSetInterval(m_udCounterCtrl->getChannelStart(),param.FirstValue,param.Increment,param.count);
	}

	m_tabIndex = 0;
	m_matchCount = 0;
	m_endCount = 0;

	//Start Snap Counter function.
	errorCode = m_udCounterCtrl->setEnabled(true);
	CheckError(errorCode);
	SetTimer(0, 40, NULL);
	GetDlgItem(IDC_Stop)->EnableWindow(TRUE);
	GetDlgItem(IDC_Start)->EnableWindow(FALSE);
	GetDlgItem(IDC_Configure)->EnableWindow(FALSE);
	EnableCompareTable(FALSE);
	UpdateData(FALSE);
}

void CContinueCompareDlg::OnStop()
{
	// TODO: Add your control notification handler code here
	// Stop the user Timer
	KillTimer(0);

	GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
	GetDlgItem(IDC_Start)->EnableWindow(TRUE);
	GetDlgItem(IDC_Configure)->EnableWindow(TRUE);
	EnableCompareTable(TRUE);   
	ErrorCode errorCode = m_udCounterCtrl->setEnabled(FALSE);
	CheckError(errorCode);
}

void CContinueCompareDlg::OnBnClickedButtonConfig()
{
	// TODO: Add your control notification handler code here
	KillTimer(0);
	this->EnableWindow(FALSE);
	m_confDlg.ShowWindow(SW_SHOW);
}

HBRUSH CContinueCompareDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CContinueCompareDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	ErrorCode errorCode;
	errorCode = m_udCounterCtrl->setEnabled(TRUE);
	CheckError(errorCode);
	int value = 0;
	m_udCounterCtrl->Read(1, &value);
	m_counterValue.Format(_T("0x%x"),value);
	GetDlgItem(IDC_CounterValue)->SetWindowText(m_counterValue);
	CDialog::OnTimer(nIDEvent);
}

LRESULT CContinueCompareDlg::OnUpdateContComp(WPARAM wParam, LPARAM lParam)
{
	m_matchCount = (int)wParam;
	m_endCount = (int)lParam; 
	UpdateData(FALSE);
	return TRUE;
}

void CContinueCompareDlg::ConfigurateDevice()
{
	ErrorCode	errorCode;
	DeviceInformation devInfo(m_confParam.deviceNumber);
	errorCode = m_udCounterCtrl->setSelectedDevice(devInfo);
	CheckError(errorCode);
	errorCode = m_udCounterCtrl->LoadProfile(m_confParam.profilePath);
	CheckError(errorCode);

	m_udCounterCtrl->getSelectedDevice(devInfo);
	CString str ;
	TCHAR des[MAX_DEVICE_DESC_LEN];
	str.Format(_T("Continue Compare - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
	SetWindowText(str);

	// set counter channel
	errorCode = m_udCounterCtrl->setChannelCount(1);
	CheckError(errorCode);
	errorCode = m_udCounterCtrl->setChannelStart(m_confParam.channel);
	CheckError(errorCode);
	// set counting type
	for(int i = m_udCounterCtrl->getChannelStart(); i < m_udCounterCtrl->getChannelStart() + m_udCounterCtrl->getChannelCount(); i++)
	{
		errorCode = m_udCounterCtrl->getChannels()->getItem(i).setCountingType(m_confParam.cntType);
		CheckError(errorCode);
	}
}

void CContinueCompareDlg::CreateDisperseTable(int tabIndex,int CompTab[3])
{
	ASSERT(CompTab != NULL);
	if (tabIndex == 0)
	{
		CompTab[0] = m_tab1CompData0;
		CompTab[1] = m_tab1CompData1;
		CompTab[2] = m_tab1CompData2;
	}else{
		CompTab[0] = m_tab2CompData0;
		CompTab[1] = m_tab2CompData1;
		CompTab[2] = m_tab2CompData2;
	}
}

void CContinueCompareDlg::CreateLineTable(int tabIndex,LineTabParam & param)
{
	if (tabIndex == 0){
		param.FirstValue = m_intrvl1FirVal;
		param.Increment = m_intrvl1Cremt;
		param.count = m_intrl1Count;
	}else{
		param.FirstValue = m_intrvl2FirVal;
		param.Increment = m_intrvl2Cremt;
		param.count = m_intrl2Count;
	}
}


void CContinueCompareDlg::EnableCompareTable(BOOL enabled)
{
	GetDlgItem(IDC_RADIO_TABLE)->EnableWindow(enabled);
	GetDlgItem(IDC_EDIT_TABLE1_DATA0)->EnableWindow(enabled);
	GetDlgItem(IDC_EDIT_TABLE1_DATA1)->EnableWindow(enabled);
	GetDlgItem(IDC_EDIT_TABLE1_DATA2)->EnableWindow(enabled);
	GetDlgItem(IDC_EDIT_TABLE2_DATA0)->EnableWindow(enabled);
	GetDlgItem(IDC_EDIT_TABLE2_DATA1)->EnableWindow(enabled);
	GetDlgItem(IDC_EDIT_TABLE2_DATA2)->EnableWindow(enabled);

	GetDlgItem(IDC_RADIO_INTERVAL)->EnableWindow(enabled);
	GetDlgItem(IDC_EDIT_INTERVAL1_FIRSTVALUE)->EnableWindow(enabled);
	GetDlgItem(IDC_EDIT_INTERVAL1_INCREMENT)->EnableWindow(enabled);
	GetDlgItem(IDC_EDIT_INTERVAL1_COUNT)->EnableWindow(enabled);
	GetDlgItem(IDC_EDIT_INTERVAL2_FIRSTVALUE)->EnableWindow(enabled);
	GetDlgItem(IDC_EDIT_INTERVAL2_INCREMENT)->EnableWindow(enabled);
	GetDlgItem(IDC_EDIT_INTERVAL2_COUNT)->EnableWindow(enabled);
}

void CContinueCompareDlg::OnUdCounterEvent(void * sender, UdCntrEventArgs * args, void * userParam)
{
	static bool   matched = false;
	static int    comTable[3];
	LineTabParam  lineTabParam;
	static int    evntEndID[8];
	static int    evntMatchID[8];

	CContinueCompareDlg * uParam = (CContinueCompareDlg *) userParam;

	int channelStart = 0;
	int channelCount = 0;

	UdCounterCtrl * udCounterCtrl = (UdCounterCtrl*)sender;
	channelStart = udCounterCtrl->getChannelStart();
	channelCount = udCounterCtrl->getChannelCount();

	for (int i = 0; i <channelCount; i++ )
	{
		evntEndID[i] = EvtCntCompareTableEnd0 + i + channelStart;
		evntMatchID[i] = EvtCntPatternMatch0 + i + channelStart;
	}

	if ((EvtCntCompareTableEnd0 + channelStart <= args->Id) && (args->Id <= EvtCntCompareTableEnd0 + channelStart + channelCount))
	{
		uParam->m_endCount++;
		uParam->m_tabIndex++;
		if (uParam->m_contCompTabSel == dispersed)

		{
			uParam->CreateDisperseTable(uParam->m_tabIndex % 2, comTable);
			udCounterCtrl->CompareSetTable(channelStart, 3, comTable);
		}else{
			uParam->CreateLineTable(uParam->m_tabIndex % 2, lineTabParam);
			udCounterCtrl->CompareSetInterval(channelStart,lineTabParam.FirstValue,lineTabParam.Increment,lineTabParam.count);
		}
		matched = true;
	}
	else if ((EvtCntPatternMatch0 + channelStart <= args->Id) && (args->Id <= EvtCntPatternMatch0 + channelStart + channelCount))
	{
		uParam->m_matchCount++;
		matched = true;
	}
	if (matched){
		::SendMessage(uParam->m_hWnd, WM_UPDATE_CONTCOMP, uParam->m_matchCount, uParam->m_endCount);
		matched = false;
	}
}