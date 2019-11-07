// SnapCounterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SnapCounter.h"
#include "SnapCounterDlg.h"

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


// CSnapCounterDlg dialog
LRESULT CSnapCounterDlg::OnConfDevice(WPARAM w,LPARAM l)
{
   int cancle = (int)w;
   if (cancle)
   {
      PostQuitMessage(0);
      return 0;
   }
   m_confParam = m_confDlg.GetParameter();
   ConfigurateDevice();
   ConfiguratePanel();
   m_counterValue.Format(_T("0"));  
   m_counterValueList.ResetContent();
   TRACE(("OnConfDevice\n"));
   return 0;
}

CSnapCounterDlg::CSnapCounterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSnapCounterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   memset(&m_confParam, 0, sizeof(m_confParam));
   m_udCounterCtrl = NULL;
}

CSnapCounterDlg::~CSnapCounterDlg()
{
   m_udCounterCtrl->Dispose();
}

void CSnapCounterDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Control(pDX, IDC_CounterValueList, m_counterValueList);
   DDX_Control(pDX, IDC_LIST_SANP_SOURCE, m_snapSourceList);
   DDX_Text(pDX, IDC_CounterValue, m_counterValue);
   DDX_Text(pDX, IDC_EDIT_SNAP_COUNT, m_snapCount);
   //DDX_Text(pDX,IDC_EDIT_TIME_INTERVAL,m_timeInterval);
}

BEGIN_MESSAGE_MAP(CSnapCounterDlg, CDialog)
   //{{AFX_MSG_MAP(CSnapCounterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_Start, OnStart)
   ON_BN_CLICKED(IDC_Stop, OnStop)
   ON_BN_CLICKED(IDC_Configure, OnBnClickedButtonConfig)
   ON_LBN_SELCHANGE(IDC_LIST_SANP_SOURCE,OnSnapSrcSelChanged)
   ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
   ON_WM_CTLCOLOR()
   ON_WM_TIMER()
   ON_MESSAGE(WM_UPDATSNAPCOUNT, OnUpdateSnapCount)

   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CSnapCounterDlg message handlers

BOOL CSnapCounterDlg::OnInitDialog()
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

   // initialize the time interval 
   GetDlgItem(IDC_EDIT_TIME_INTERVAL)->SetWindowText(_T("5"));
   m_isTimerUsing = FALSE;
   UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSnapCounterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSnapCounterDlg::OnPaint()
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
HCURSOR CSnapCounterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
//This function is used to handle the errorCode information
void CSnapCounterDlg::CheckError(ErrorCode errorCode)
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

void CSnapCounterDlg::OnStart()
{
   //CString start;
   //GetDlgItem(IDC_Start)->GetWindowText(start);
   // TODO: Add your control notification handler code here
   UpdateData(TRUE);
   ErrorCode errorCode;
   m_counterValueList.ResetContent();
   m_snapCount.Format(_T("%d"),0);
   m_eventCount = 0;
   UpdateData(FALSE);
   aryListBoxSrcSel.RemoveAll();
   m_isTimerUsing = FALSE;

   int item = 0;
   int timerChan = -1;
   int cnt = m_snapSourceList.GetSelCount();
   CArray<int,int> aryListBoxSel;
   aryListBoxSel.SetSize(cnt);
   m_snapSourceList.GetSelItems(cnt,aryListBoxSel.GetData());
   //*************************************************************************************************
   // only one timer is used here; if more than one timer is selected, the last selected timer is used.
   //*************************************************************************************************
   int snapSrcCount = aryListBoxSel.GetSize();
   for (int i = 0; i < snapSrcCount;++i)
   {
      item = (int)m_snapSourceList.GetItemData(aryListBoxSel.GetAt(i));
      CheckTimerUsingParam((EventId)item,timerChan,m_isTimerUsing);
      m_udCounterCtrl->SnapStart((EventId)item);
      aryListBoxSrcSel.Add((int)item);
   }

   if (m_isTimerUsing)
   {
      ErrorCode	errorCode;
      m_timerPulseCtrl = TimerPulseCtrl::Create();
      DeviceInformation devInfo(m_confParam.deviceNumber);
      errorCode = m_timerPulseCtrl->setSelectedDevice(devInfo);
      CheckError(errorCode);
      CString interVal;
      GetDlgItem(IDC_EDIT_TIME_INTERVAL)->GetWindowText(interVal);
      double frequency = _tcstod(interVal, 0);
		m_timerPulseCtrl->setChannelCount(1);
		m_timerPulseCtrl->setChannelStart(timerChan);
      for (int i = m_timerPulseCtrl->getChannelStart(); i < m_timerPulseCtrl->getChannelStart() + m_timerPulseCtrl->getChannelCount(); i++)
      {
         int err = m_timerPulseCtrl->getChannels()->getItem(i).setFrequency(frequency);
      }
      m_timerPulseCtrl->setEnabled(TRUE);
   }

   //Set snap source
  //m_udCounterCtrl->setnapsource(cnt,arySrcSel.getData());


   //Start Snap Counter function.
   errorCode = m_udCounterCtrl->setEnabled(true);
   CheckError(errorCode);
   SetTimer(0, 40, NULL);
   GetDlgItem(IDC_Stop)->EnableWindow(TRUE);
   GetDlgItem(IDC_Configure)->EnableWindow(FALSE);
   GetDlgItem(IDC_Start)->EnableWindow(FALSE);
   GetDlgItem(IDC_LIST_SANP_SOURCE)->EnableWindow(FALSE);

   UpdateData(TRUE);
}

void CSnapCounterDlg::OnStop()
{
   // TODO: Add your control notification handler code here
   // Stop the user Timer
   KillTimer(0);

   //GetDlgItem(IDC_Start)->SetWindowText(_T("Start"));
   GetDlgItem(IDC_Stop)->EnableWindow(FALSE);
   GetDlgItem(IDC_Start)->EnableWindow(TRUE);
   GetDlgItem(IDC_Configure)->EnableWindow(TRUE);
   GetDlgItem(IDC_LIST_SANP_SOURCE)->EnableWindow(TRUE);

   // stop timer pulse
   if (m_isTimerUsing)
   {
      m_timerPulseCtrl->setEnabled(FALSE);
      m_timerPulseCtrl->Dispose();
   }
   // stop snap function
   int cnt = (int)aryListBoxSrcSel.GetSize();
   for (int i = 0; i < cnt; ++i)
   {
      m_udCounterCtrl->SnapStop((EventId)aryListBoxSrcSel.GetAt(i));
   }

   
   //stop updown counter
   ErrorCode errorCode = m_udCounterCtrl->setEnabled(FALSE);
   CheckError(errorCode);
}

void CSnapCounterDlg::OnBnClickedButtonConfig()
{
   // TODO: Add your control notification handler code here
   KillTimer(0);
   this->EnableWindow(FALSE);
   m_confDlg.ShowWindow(SW_SHOW);
}

HBRUSH CSnapCounterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CSnapCounterDlg::OnTimer(UINT_PTR nIDEvent)
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

void CSnapCounterDlg::ConfigurateDevice()
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
   str.Format(_T("Snap Counter - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
   SetWindowText(str);

	// set counter channel
   errorCode = m_udCounterCtrl->setChannelCount(1);
   CheckError(errorCode);
   errorCode = m_udCounterCtrl->setChannelStart(m_confParam.channel);
   CheckError(errorCode);
   // set counting type
   errorCode = m_udCounterCtrl->setCountingType(m_confParam.cntType);

   for (int32 i = m_udCounterCtrl->getChannelStart(); i < m_udCounterCtrl->getChannelStart() + m_udCounterCtrl->getChannelCount(); i ++)
   {
      errorCode = m_udCounterCtrl->getChannels()->getItem(i).setCountingType(m_confParam.cntType);
      CheckError(errorCode);
   }
}
void CSnapCounterDlg::ConfiguratePanel()
{
   // for reset value
   Array<EventId>* snapSrcs = m_udCounterCtrl->getFeatures()->getUdSnapEventSources();
   int srcCount = snapSrcs->getCount();
   CString strSrc;
   m_snapSourceList.ResetContent();
   for (int i = 0; i < srcCount; ++i)
   {
      EventIDtoString(snapSrcs->getItem(i),strSrc);
	  m_snapSourceList.InsertString(i,strSrc);
      m_snapSourceList.SetItemData(i,snapSrcs->getItem(i));
   }
   
}

LRESULT CSnapCounterDlg::OnUpdateSnapCount(WPARAM wParam, LPARAM lParam)
{
   UdCntrEventArgs * args = (UdCntrEventArgs *)lParam;
   int snapCount = (int)wParam;
   m_snapCount.Format(_T("%d"),snapCount); 
   UpdateData(FALSE);
   //refresh the snap value list
   CString snapValue;
   CString srcID;
   CString source;
   CString str;
   EventIDtoString(args->Id,srcID);
   snapValue +=_T("CntrValue: ");
   for (int i = 0; i < args->Length; ++i)
   {
	  str.Format(_T("%x"), args->Data[i]);
	  snapValue += str;
	  snapValue += _T(" ");
   }
   m_counterValueList.AddString(snapValue);

   source +=_T("SrcID:");
   source += srcID;
   m_counterValueList.AddString(source);
   if (m_counterValueList.GetCount() > 40)
   {
      m_counterValueList.DeleteString(0);
   }

   return TRUE;
}

void CSnapCounterDlg::EventIDtoString(EventId id,CString &str)
{
   switch (id)
   {
   case EvtUdIndex0:
      str = L"Index0";
      break;
   case EvtUdIndex1:
      str = L"Index1";
      break;
   case EvtUdIndex2:
      str = L"Index2";
      break;
   case EvtUdIndex3:
      str = L"Index3";
      break;
   case EvtUdIndex4:
      str = L"Index4";
      break;
   case EvtUdIndex5:
      str = L"Index5";
      break;
   case EvtUdIndex6:
      str = L"Index6";
      break;
   case EvtUdIndex7:
      str = L"Index7";
      break;
   case EvtCntTimer0:
      str = L"Timer0";
      break;
   case EvtCntTimer1:
      str = L"Timer1";
      break;
   case EvtCntTimer2:
      str = L"Timer2";
      break;
   case EvtCntTimer3:
      str = L"Timer3";
      break;
   case EvtCntTimer4:
      str = L"Timer4";
      break;
   case EvtCntTimer5:
      str = L"Timer5";
      break;
   case EvtCntTimer6:
      str = L"Timer6";
      break;
   case EvtCntTimer7:
      str = L"Timer7";
      break;
   case EvtDiintChannel000:
      str = L"DiintChannel0";
      break;
   case EvtDiintChannel001:
      str = L"DiintChannel1";
      break;
   case EvtDiintChannel002:
      str = L"DiintChannel2";
      break;
   case EvtDiintChannel003:
      str = L"DiintChannel3";
      break;
   case EvtDiintChannel004:
      str = L"DiintChannel4";
      break;
   case EvtDiintChannel005:
      str = L"DiintChannel5";
      break;
   case EvtDiintChannel006:
      str = L"DiintChannel6";
      break;
   case EvtDiintChannel007:
      str = L"DiintChannel7";
      break;
   case EvtDiCosintPort000:
      str = L"DiConsintChannel0";
      break;
   case EvtDiCosintPort001:
      str = L"DiConsintChannel1";
      break;
   case EvtDiCosintPort002:
      str = L"DiConsintChannel2";
      break;
   case EvtDiCosintPort003:
      str = L"DiConsintChannel3";
      break;
   case EvtDiPmintPort000:
      str = L"DiPmintChannel0";
      break;
   case EvtDiPmintPort001:
      str = L"DiPmintChannel1";
      break;
   case EvtDiPmintPort002:
      str = L"DiPmintChannel2";
      break;
   case EvtDiPmintPort003:
      str = L"DiPmintChannel3";
      break;
   default:
      str = L"";
   }
}
void CSnapCounterDlg::OnSnapSrcSelChanged()
{
   int item = 0;
   int cnt = m_snapSourceList.GetSelCount();
   CArray<int,int> aryListBoxSel;
   aryListBoxSel.SetSize(cnt);
   m_snapSourceList.GetSelItems(cnt,aryListBoxSel.GetData());
   int i = 0;
   int timerChan = -1;
   BOOL isTimerUsing = FALSE;
   for (; i < aryListBoxSel.GetSize();++i)
   {
      item = (int)m_snapSourceList.GetItemData(aryListBoxSel.GetAt(i));
      CheckTimerUsingParam((EventId)item,timerChan,isTimerUsing);
      if (isTimerUsing)
      {
         GetDlgItem(IDC_EDIT_TIME_INTERVAL)->EnableWindow(TRUE);
         break;
      }
   }
   if (i == cnt)
   {
      GetDlgItem(IDC_EDIT_TIME_INTERVAL)->EnableWindow(FALSE);
   }
}

void CSnapCounterDlg::CheckTimerUsingParam(EventId id,int & timerChan,BOOL & isTimerUsing)
{
   if (id >= EvtCntTimer0 && id <=  EvtCntTimer7)
   {
      timerChan = id - EvtCntTimer0;
   }
  
   if (timerChan != -1)
   {
      isTimerUsing = TRUE;
   }
}
void CSnapCounterDlg::OnUdCounterEvent(void * sender, UdCntrEventArgs * args, void * userParam)
{
   CSnapCounterDlg* uParam = (CSnapCounterDlg*)userParam;
   ::SendMessage(uParam->m_hWnd, WM_UPDATSNAPCOUNT, uParam->m_eventCount++, (LPARAM)args);
}