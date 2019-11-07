// UpDownCounterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UpDownCounter.h"
#include "UpDownCounterDlg.h"

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


// CUpDownCounterDlg dialog
LRESULT CUpDownCounterDlg::OnConfDevice(WPARAM w,LPARAM l)
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
	ConfiguratePanel();
	m_counterValue.Format(_T("0"));  
	m_counterValueList.ResetContent();
	TRACE(("OnConfDevice\n"));
	return 0;
}

CUpDownCounterDlg::CUpDownCounterDlg(CWnd* pParent /*=NULL*/)
: CDialog(CUpDownCounterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(&m_confParam, 0, sizeof(m_confParam));
	m_udCounterCtrl = NULL;
}

CUpDownCounterDlg::~CUpDownCounterDlg()
{
	m_udCounterCtrl->Dispose();
}

void CUpDownCounterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_RESET_VALUE, m_comboBox_resetValue);
	DDX_Control(pDX, IDC_CounterValueList, m_counterValueList);
	DDX_Control(pDX,IDC_EDIT_RESET_TIMES,m_resetTimes);
	DDX_Text(pDX, IDC_CounterValue, m_counterValue);
	DDX_Control(pDX, IDC_EDIT_RESET_VALUE, m_resetValue);
}

BEGIN_MESSAGE_MAP(CUpDownCounterDlg, CDialog)
	//{{AFX_MSG_MAP(CUpDownCounterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Start, OnStart)
	ON_BN_CLICKED(IDC_Stop, OnStop)
	ON_BN_CLICKED(IDC_BUTTON_VALUE_RESET, OnValueReset)
	ON_BN_CLICKED(IDC_Configure, OnBnClickedButtonConfig)
	ON_CBN_SELCHANGE(IDC_COMBO_RESET_VALUE, OnCbnSelchangeComboResetValue)
	ON_BN_CLICKED(IDC_RADIO_DISABLE, OnResetIndexChged)
	ON_BN_CLICKED(IDC_RADIO_FINITE, OnResetIndexChged)
	ON_BN_CLICKED(IDC_RADIO_INFINITE, OnResetIndexChged)
	ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CUpDownCounterDlg message handlers

BOOL CUpDownCounterDlg::OnInitDialog()
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
	// the following is used to change the background picture of the UpDown Counter dialog
	CBitmap			bmp;
	bmp.LoadBitmap(IDB_Background);                 //IDB_Background is the ID of the background picture
	m_bkBk.CreatePatternBrush(&bmp);
	bmp.DeleteObject();

	m_confDlg.Create(IDD_CONFIGURATION,this);
	m_confDlg.ShowWindow(SW_SHOW);
	this->ShowWindow(SW_HIDE);
	this->EnableWindow(FALSE);
	m_udCounterCtrl = UdCounterCtrl::Create();
	GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_VALUE_RESET)->EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUpDownCounterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUpDownCounterDlg::OnPaint()
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
HCURSOR CUpDownCounterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
//This function is used to handle the errorCode information
void CUpDownCounterDlg::CheckError(ErrorCode errorCode)
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

void CUpDownCounterDlg::OnStart()
{
	CString start;
	GetDlgItem(IDC_Start)->GetWindowText(start);
	// TODO: Add your control notification handler code here
	ErrorCode errorCode;
	if (0 == start.Compare(_T("Start")))
	{
		m_counterValueList.ResetContent();
		// Set reset times for counter value
		int resetTimes = 0;
		if(IsDlgButtonChecked(IDC_RADIO_FINITE)){
			CString strTimes;
			GetDlgItemText(IDC_EDIT_RESET_TIMES,strTimes);
			resetTimes = _ttoi(strTimes);// reset counter value finite times 

		}else if(IsDlgButtonChecked(IDC_RADIO_INFINITE)){
			resetTimes = -1;// -1 means that reset counter value infinite times
		}else if(IsDlgButtonChecked(IDC_RADIO_DISABLE)){
			resetTimes = 0;// 0 means that can not reset counter value
		}
		m_udCounterCtrl->setResetTimesByIndex(resetTimes);

		//set reset value
		CString strResetValue;
		int index = m_comboBox_resetValue.GetCurSel();
		int rValue = m_comboBox_resetValue.GetItemData(index);
		if (rValue == -1){
			GetDlgItemText(IDC_EDIT_RESET_VALUE,strResetValue);
			rValue = _ttoi(strResetValue);
		}
		ULONG ulValue = (ULONG)rValue;
		for (int i = m_udCounterCtrl->getChannelStart(); i < m_udCounterCtrl->getChannelStart() + m_udCounterCtrl->getChannelCount(); i++ )
		{
			errorCode = m_udCounterCtrl->getChannels()->getItem(i).setInitialValue(ulValue);
			CheckError(errorCode);
		}

		//Start UpDown Counter function.
		errorCode = m_udCounterCtrl->setEnabled(true);
		CheckError(errorCode);
		SetTimer(0, 40, NULL);
		GetDlgItem(IDC_Stop)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_VALUE_RESET)->EnableWindow(TRUE);
		GetDlgItem(IDC_Configure)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_RESET_VALUE)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_DISABLE)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_INFINITE)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_FINITE)->EnableWindow(FALSE);

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

void CUpDownCounterDlg::OnStop()
{
	// TODO: Add your control notification handler code here
	// Stop the user Timer
	KillTimer(0);

	GetDlgItem(IDC_Start)->SetWindowText(_T("Start"));
	GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_VALUE_RESET)->EnableWindow(FALSE);
	GetDlgItem(IDC_Configure)->EnableWindow(TRUE);

	GetDlgItem(IDC_COMBO_RESET_VALUE)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_DISABLE)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_INFINITE)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_FINITE)->EnableWindow(TRUE);

	ErrorCode errorCode = m_udCounterCtrl->setEnabled(FALSE);
	CheckError(errorCode);
}

void CUpDownCounterDlg::OnBnClickedButtonConfig()
{
	// TODO: Add your control notification handler code here
	KillTimer(0);
	this->EnableWindow(FALSE);
	m_confDlg.ShowWindow(SW_SHOW);
}

HBRUSH CUpDownCounterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CUpDownCounterDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	ErrorCode errorCode;
	errorCode = m_udCounterCtrl->setEnabled(TRUE);
	CheckError(errorCode);
	int value = 0;
	m_udCounterCtrl->Read(1, &value);

	m_counterValue.Format(_T("%u"),value);  
	GetDlgItem(IDC_CounterValue)->SetWindowText(m_counterValue);
	CDialog::OnTimer(nIDEvent);
}

void CUpDownCounterDlg::ConfigurateDevice()
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
	str.Format(_T("UpDown Counter - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
	SetWindowText(str);

	// set counter channel
	errorCode = m_udCounterCtrl->setChannelCount(1);
	CheckError(errorCode);
	errorCode = m_udCounterCtrl->setChannelStart(m_confParam.channel);
	CheckError(errorCode);
	// set counting type
	for (int i = m_udCounterCtrl->getChannelStart(); i < m_udCounterCtrl->getChannelStart() + m_udCounterCtrl->getChannelCount(); i++ )
	{
		errorCode = m_udCounterCtrl->getChannels()->getItem(i).setCountingType(m_confParam.cntType);
		CheckError(errorCode);
	}
}

void CUpDownCounterDlg::ConfiguratePanel()
{
	m_comboBox_resetValue.ResetContent();
	// for reset value
	Array<int32> * resetValues = m_udCounterCtrl->getFeatures()->getUdInitialValues();

	int valueCount = resetValues->getCount();
	CString strVal;
	CString header = _T("0x");
	int i = 0;
	for (; i < valueCount; ++i)
	{
		if (resetValues->getItem(i) != -1)
		{
			strVal.Format(_T("%x"), resetValues->getItem(i));
			header += strVal;
			m_comboBox_resetValue.AddString(header);
			m_comboBox_resetValue.SetItemData(i,resetValues->getItem(i));
		}else{
			strVal.Format(_T("%d"), -1);
			m_comboBox_resetValue.AddString(strVal);
			m_comboBox_resetValue.SetItemData(i,-1);
		}
		if (i == 0){
			m_comboBox_resetValue.SetCurSel(0);
		}
	}


	//for using edit text as reset value  
	m_resetValue.SetWindowText(_T("0"));

	//radio button for reset value.
	CButton *rDisable = (CButton*)GetDlgItem(IDC_RADIO_FINITE);
	rDisable->SetCheck(0);
	rDisable = (CButton*)GetDlgItem(IDC_RADIO_INFINITE);
	rDisable->SetCheck(0);
	rDisable = (CButton*)GetDlgItem(IDC_RADIO_DISABLE);
	rDisable->SetCheck(0);

	rDisable = (CButton*)GetDlgItem(IDC_RADIO_DISABLE);
	rDisable->SetCheck(1);

	//reset times
	m_resetTimes.SetWindowText(_T("0"));
	GetDlgItem(IDC_EDIT_RESET_TIMES)->EnableWindow(FALSE);
}

void CUpDownCounterDlg::OnCbnSelchangeComboResetValue()
{
	int sel = m_comboBox_resetValue.GetCurSel();
	int resetValue = (int)m_comboBox_resetValue.GetItemData(sel);
	if (resetValue == -1){
		GetDlgItem(IDC_EDIT_RESET_VALUE)->EnableWindow(TRUE);
	}else{
		GetDlgItem(IDC_EDIT_RESET_VALUE)->EnableWindow(FALSE);
	}
}

void CUpDownCounterDlg::OnResetIndexChged()
{
	CButton * rDisable = (CButton *)GetDlgItem(IDC_RADIO_DISABLE);
	if(IsDlgButtonChecked(IDC_RADIO_DISABLE)){
		GetDlgItem(IDC_EDIT_RESET_TIMES)->EnableWindow(FALSE);
		// for reseting counter value in finite times
	}else if(IsDlgButtonChecked(IDC_RADIO_FINITE)){
		GetDlgItem(IDC_EDIT_RESET_TIMES)->EnableWindow(TRUE);
		m_resetTimes.SetWindowText(_T("1"));
		m_udCounterCtrl->setResetTimesByIndex(1);
	}else if(IsDlgButtonChecked(IDC_RADIO_INFINITE)){
		GetDlgItem(IDC_EDIT_RESET_TIMES)->EnableWindow(FALSE);
	}
}

void CUpDownCounterDlg::OnValueReset()
{
	m_udCounterCtrl->ValueReset();
}