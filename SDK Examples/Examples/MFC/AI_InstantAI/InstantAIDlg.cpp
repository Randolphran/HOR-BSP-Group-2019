// InstantAiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InstantAi.h"
#include "InstantAiDlg.h"
#include "ConfigurationDlg.h"
using namespace Automation::BDaq;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CInstantAIDlg dialog
#define LV_COL_COUNT       8           // !!!Notice : the count must be 2 ^x !!!
#define ROW_OF_CH(ch)      ((ch) & (~(LV_COL_COUNT - 1)))
#define COL_OF_CH(ch)      ((ch) & (LV_COL_COUNT - 1))

extern TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out);

CInstantAIDlg::CInstantAIDlg(CWnd* pParent /*=NULL*/)
: CDialog(CInstantAIDlg::IDD, pParent)
{
   m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   m_instantAiCtrl = InstantAiCtrl::Create();
}

void CInstantAIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_GRAPH, m_simpleGraph);
}

BEGIN_MESSAGE_MAP(CInstantAIDlg, CDialog)
   //{{AFX_MSG_MAP(CInstantAIDlg)
   ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
	ON_WM_TIMER()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST, OnNMCustomdrawList)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TIMERINTERVAL, OnNMReleasedcaptureSliderTimerinterval)
	ON_BN_CLICKED(IDC_BUTTON_START, OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_CONDIG, OnBnClickedButtonConfig)
	ON_WM_CLOSE()
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CInstantAIDlg message handlers
LRESULT  CInstantAIDlg::OnConfDevice(WPARAM w,LPARAM l)
{
   int cancle = (int)w;
   if (cancle)
   {
      PostQuitMessage(0);
      return 0;
   }
   m_confParam = m_confDlg.GetParameter();
   ConfigurateDevice();
   ConfigurateGraph();
   InitListView();
   return 0;
}

BOOL CInstantAIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CBitmap			bmp;
	bmp.LoadBitmap(IDB_BACKGROUND);                 //IDB_BCAKGROUND is the ID of the background picture
	m_bkBk.CreatePatternBrush(&bmp);
	bmp.DeleteObject();

	CSliderCtrl* pslider = (CSliderCtrl*)this->GetDlgItem(IDC_SLIDER_TIMERINTERVAL);
	pslider->SetRange(10, 1000);        //Notice !!! this range(10,1000) is defined in the UI definition of AI  
	pslider->SetTicFreq(100);
	pslider->SetPos(200);
	SetDlgItemText(IDC_EDIT_INTERVAL,_T("200"));
   
	m_confDlg.Create(IDD_CONFIGURATION,this);
   m_confDlg.ShowWindow(SW_SHOW);
   this->ShowWindow(SW_HIDE);
	this->EnableWindow(FALSE);

	CRect rc;
	CWnd *pWnd = GetDlgItem(IDC_STATIC_GRAPH);
	pWnd->GetClientRect(&rc);
	m_simpleGraph.InitGraph();
	return FALSE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInstantAIDlg::OnPaint()
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
HCURSOR CInstantAIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CInstantAIDlg::ConfigurateDevice()
{
	ErrorCode	errorCode;
   DeviceInformation devInfo(m_confParam.deviceNumber);
   errorCode = m_instantAiCtrl->setSelectedDevice(devInfo);
   CheckError(errorCode);
	errorCode = m_instantAiCtrl->LoadProfile(m_confParam.profilePath);
	CheckError(errorCode);

   m_instantAiCtrl->getSelectedDevice(devInfo);
   TCHAR des[MAX_DEVICE_DESC_LEN];
   CString str ;
   str.Format(_T("Instant AI - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
	SetWindowText(str);
   
	//get channel max number. set value range for every channel.
	int count = m_instantAiCtrl->getFeatures()->getChannelCountMax();
   Array<AiChannel> * channels = m_instantAiCtrl->getChannels();
   int channel = m_confParam.channelStart;
   for (int i = 0; i < m_confParam.channelCount; ++i)
   {
      if (channel >= count){
         channel = 0;}
      if (channels->getItem(channel).getSignalType() == Differential)
      {
         if (channel%2 == 1){
            channel -= 1;}
         errorCode = channels->getItem(channel%count).setValueRange((ValueRange)(m_confParam.vrgType));
         CheckError(errorCode);
         channel += 1;
      }
      errorCode = channels->getItem(channel%count).setValueRange((ValueRange)(m_confParam.vrgType));
      CheckError(errorCode);

      channel += 1;
   }
}

void CInstantAIDlg::ConfigurateGraph()
{
	TimeUnit timeunit = Second;
	CString X_rangeLabels[2];
	m_simpleGraph.GetXCordRangeLabels(X_rangeLabels,10,0,timeunit);
	((CStatic*)GetDlgItem(IDC_STATIC_ENDTIME))->SetWindowText(X_rangeLabels[0]);
	((CStatic*)GetDlgItem(IDC_STATIC_STARTTIME))->SetWindowText(X_rangeLabels[1]);

   m_simpleGraph.m_XCordTimeDiv = 1000;
	ValueUnit unit;
	MathInterval rangeY ;
	CheckError(AdxGetValueRangeInformation((ValueRange)m_confParam.vrgType, 0, NULL, &rangeY, &unit));
	if (Milliampere == unit  || Millivolt == unit )
	{
		rangeY.Max /= 1000;
		rangeY.Min /= 1000;
	}

	CString Y_rangeLabels[3];
	m_simpleGraph.GetYCordRangeLabels(Y_rangeLabels,rangeY.Max,rangeY.Min,unit);
	((CStatic*)GetDlgItem(IDC_STATIC_YRANGEMAX))->SetWindowText(Y_rangeLabels[0]);
	((CStatic*)GetDlgItem(IDC_STATIC_YRANGEMID))->SetWindowText(Y_rangeLabels[2]);
	((CStatic*)GetDlgItem(IDC_STATIC_YRANGEMIN))->SetWindowText(Y_rangeLabels[1]);
	m_simpleGraph.m_YCordRangeMax = rangeY.Max;
	m_simpleGraph.m_YCordRangeMin = rangeY.Min;

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_SLIDER_TIMERINTERVAL)->EnableWindow(TRUE);
}

void CInstantAIDlg::InitListView()
{
	CListCtrl*	pcolorList = (CListCtrl*)this->GetDlgItem(IDC_LIST);	
	while (pcolorList->DeleteColumn(0));
	pcolorList->DeleteAllItems();
	pcolorList->SetExtendedStyle(LVS_EX_GRIDLINES);
	pcolorList->SetExtendedStyle(pcolorList->GetExtendedStyle());

	CImageList imagelist;
	imagelist.Create(IDB_BITMAP_LIST, 1, 20, RGB(255, 255, 0));
	pcolorList->SetImageList(&imagelist, LVSIL_SMALL);

	int row = 2;				
	int column = 8;        ////Notice, we use '8' for the number of items in a color list row
   int i = 0;
	for (i = 0; i < column; i++)
	{
		pcolorList->InsertColumn(i, _T(""), LVCFMT_LEFT, 62);
	}
   int j = 0;
	for(i= 0; i < row; i++)
	{
		pcolorList->InsertItem(i, _T(""));
		for (j = 0; j < column; j++)
		{
			pcolorList->SetItemText(i, j, _T(""));
		}
		pcolorList->SetItemData(i,i);
	}

	CString  str = _T("0.0000");
	for (int ch = 0; ch < m_confParam.channelCount; ch++)
	{
		pcolorList->SetItemText(ROW_OF_CH(ch) / LV_COL_COUNT, COL_OF_CH(ch), str);
	}
}


void CInstantAIDlg::CheckError(ErrorCode error)
{
	if (BioFailed(error))
	{
		KillTimer(0);
      CString str;
      str.Format(_T("Some errors happened, the error code is: 0x%X !\n"),error);
		AfxMessageBox(str);
      OnBnClickedButtonConfig();
	}
}

void CInstantAIDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	ErrorCode	errorCode = Success;
   DOUBLE data[128];
   errorCode = m_instantAiCtrl->ReadAny(m_confParam.channelStart, m_confParam.channelCount, NULL, data);
	CheckError(errorCode);
   if (errorCode != Success)
   {
      return;
   }
   CSliderCtrl* pslider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIMERINTERVAL);
   int dataCyclic = pslider->GetPos();
	m_simpleGraph.Chart(data, m_confParam.channelCount, 1,1.0*dataCyclic/1000);
	RefreshListView(data);
	CDialog::OnTimer(nIDEvent);
}

void CInstantAIDlg::RefreshListView(DOUBLE data[])
{
	CListCtrl	*pcolorList = (CListCtrl*)GetDlgItem(IDC_LIST);
	CString str ;
	for (int ch = 0; ch < m_confParam.channelCount; ch++)
	{
      str.Format(_T("%.6g"),data[ch]);
		pcolorList->SetItemText(ROW_OF_CH(ch) / LV_COL_COUNT, COL_OF_CH(ch), str);
	}
}

void CInstantAIDlg::OnNMCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	LPNMLVCUSTOMDRAW	lplvcd	= (LPNMLVCUSTOMDRAW)pNMHDR;
	int					row		   = 0 ;
	switch(lplvcd->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT :
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		break;
	case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
      // set color for list view.
		row = (int)(lplvcd->nmcd.lItemlParam);
		if (8 * row + lplvcd->iSubItem < m_confParam.channelCount)
		{
			lplvcd->clrTextBk  = m_simpleGraph.LinesColor[row * 8 + lplvcd->iSubItem];
			*pResult = CDRF_NEWFONT;
		}
		else
		{
			lplvcd->clrTextBk = RGB(255, 255, 255);
			*pResult = CDRF_NEWFONT;
		}
		break;
	default:
		*pResult = CDRF_DODEFAULT;
		break;
	}
	//*pResult = 0;
}

HBRUSH CInstantAIDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	if (pWnd == this)
	{
		return (HBRUSH)m_bkBk;
	}
    
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CInstantAIDlg::OnNMReleasedcaptureSliderTimerinterval(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CSliderCtrl* pslider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIMERINTERVAL);
	KillTimer(0);
	int dataCyclic = pslider->GetPos();// / 10 * 10;
	m_simpleGraph.Clear();
	if(!(((CButton*)GetDlgItem(IDC_BUTTON_START))->IsWindowEnabled()))
	{
		SetTimer(0, dataCyclic, NULL);
	}
	CString str ;
   str.Format(_T("%d"),dataCyclic);
	SetDlgItemText(IDC_EDIT_INTERVAL, str);
   m_simpleGraph.Clear();
}

void CInstantAIDlg::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here
	CSliderCtrl* pslider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIMERINTERVAL);
	int dataCyclic = pslider->GetPos();
   CString str ;
   str.Format(_T("%d"),dataCyclic);
	SetDlgItemText(IDC_EDIT_INTERVAL, str);

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CONFIG)->EnableWindow(FALSE);
	GetDlgItem(IDC_SLIDER_TIMERINTERVAL)->EnableWindow(TRUE);

	SetTimer(0, dataCyclic, NULL);
}

void CInstantAIDlg::OnBnClickedButtonPause()
{
	// TODO: Add your control notification handler code here
	KillTimer(0);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
}

void CInstantAIDlg::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	KillTimer(0);
	m_simpleGraph.Clear();
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONFIG)->EnableWindow(TRUE);
}

void CInstantAIDlg::OnBnClickedButtonConfig()
{
	// TODO: Add your control notification handler code here
   this->EnableWindow(FALSE);
   //this->ShowWindow(SW_HIDE);
	KillTimer(0);
	m_simpleGraph.Clear();
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
	//GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);

	m_confDlg.ShowWindow(SW_SHOW);
}
void CInstantAIDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	m_instantAiCtrl->Dispose();
	CDialog::OnClose();
}
