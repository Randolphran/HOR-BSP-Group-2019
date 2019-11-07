// OneShotSyncbufferedAiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SynchronousOneBufferedAI.h"
#include "SynchronousOneBufferedAIDlg.h"
#include "ConfigurationDlg.h"

using namespace Automation::BDaq;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define  SectionCount 1
#define  GetDataLength   m_confParam.channelCount*m_confParam.sectionLength*SectionCount

// CSynchonousOneBufferedAIDlg dialog
extern TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out);
LRESULT  CSynchonousOneBufferedAIDlg::OnConfDevice(WPARAM w,LPARAM l)
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

CSynchonousOneBufferedAIDlg::CSynchonousOneBufferedAIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSynchonousOneBufferedAIDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_data = NULL;
    m_confParam.deviceNumber = -1;
    m_wfAiCtrl = NULL;
}

CSynchonousOneBufferedAIDlg::~CSynchonousOneBufferedAIDlg()
{
   m_wfAiCtrl->Dispose();
}
void CSynchonousOneBufferedAIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_GRAPH, m_simpleGraph);
	DDX_Text(pDX, IDC_EDIT_TIMESHIFT, m_shiftEdit);
	DDX_Text(pDX, IDC_EDIT_TIMEDIV, m_divEdit);
}

BEGIN_MESSAGE_MAP(CSynchonousOneBufferedAIDlg, CDialog)
    //{{AFX_MSG_MAP(CSynchonousOneBufferedAIDlg)
   ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_CONDIG, OnBnClickedButtonConfig)
	ON_BN_CLICKED(IDC_BUTTON_GETDATA, OnBnClickedButtonGetdata)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST, OnNMCustomdrawList)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TIMESHIFT, OnNMReleasedcaptureSliderTimeshift)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TIMEDIV, OnNMReleasedcaptureSliderTimediv)
   //}}AFX_MSG_MAP
   ON_WM_CLOSE()
END_MESSAGE_MAP()

// CSyncOneBufferedAiDlg message handlers

BOOL CSynchonousOneBufferedAIDlg::OnInitDialog()
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

   m_confDlg.Create(IDD_CONFIGURATION,this);
   m_confDlg.ShowWindow(SW_SHOW);
   this->ShowWindow(SW_HIDE);
   this->EnableWindow(FALSE);

	CRect rc;
	CWnd *pWnd = GetDlgItem(IDC_STATIC_GRAPH);
	pWnd->GetClientRect(&rc);
	m_simpleGraph.InitGraph();

   // Set the notification event Handler by which we can known the state of operation effectively.
   m_wfAiCtrl = WaveformAiCtrl::Create();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSynchonousOneBufferedAIDlg::OnPaint()
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
HCURSOR CSynchonousOneBufferedAIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSynchonousOneBufferedAIDlg::CheckError(ErrorCode error)
{
	if (BioFailed(error))
	{
      CString str;
      str.Format(_T("Some errors happened, the error code is: 0x%X !\n"),error);
      AfxMessageBox(str);
      OnBnClickedButtonConfig();
	}
}
void CSynchonousOneBufferedAIDlg::ConfigurateDevice()
{
   ErrorCode	errorCode;
   if ( m_data != NULL)
   {
      delete [] m_data;
      m_data = NULL;
   }
   m_data = new DOUBLE[GetDataLength];
   if (m_data == NULL)
   {
      AfxMessageBox(_T("Sorry! Error in allocating memory...."));
      this->CloseWindow();
      exit(0);
   }

   // Select a device with AccessWrite/AccessWriteWithReset mode with device number or device description.
   DeviceInformation devInfo(m_confParam.deviceNumber);
   errorCode = m_wfAiCtrl->setSelectedDevice(devInfo);
   CheckError(errorCode);
	errorCode = m_wfAiCtrl->LoadProfile(m_confParam.profilePath);
	CheckError(errorCode);

   m_wfAiCtrl->getSelectedDevice(devInfo);

   TCHAR des[MAX_DEVICE_DESC_LEN];
   CString str ;
   str.Format(_T("Synchronous One Buffered AI - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
   SetWindowText(str);
   
   // Set necessary parameters for buffered AI operation, 
   Conversion * conversion = m_wfAiCtrl->getConversion();
   errorCode = conversion->setChannelStart(m_confParam.channelStart);
   CheckError(errorCode);
   errorCode = conversion->setChannelCount(m_confParam.channelCount);
	CheckError(errorCode);
	errorCode = conversion->setClockRate(m_confParam.clockRatePerChan);
	CheckError(errorCode); 
	Record * record = m_wfAiCtrl->getRecord();
   errorCode = record->setSectionLength(m_confParam.sectionLength);
   CheckError(errorCode);
   errorCode = record->setSectionCount(SectionCount);//The nonzero value means 'One Buffered' mode.
   CheckError(errorCode);
   
	// Get Accurate clock Rate for configuring graph
	/*m_confParam.clockRatePerChan = m_wfAiCtrl->getConversion()->getClockRate();*/
	int count = m_wfAiCtrl->getFeatures()->getChannelCountMax();
	Array<AiChannel>* channels = m_wfAiCtrl->getChannels();
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

   // prepare the buffered AI. 
    errorCode = m_wfAiCtrl->Prepare();
    CheckError(errorCode);
}
void CSynchonousOneBufferedAIDlg::ConfigurateGraph()
{
    CRect rc;
    CWnd *pWnd = GetDlgItem(IDC_STATIC_GRAPH);
    pWnd->GetClientRect(&rc);
    double conversionRate = m_wfAiCtrl->getConversion()->getClockRate();
    //1 pixel to 1 data point. How much time plotting rc.Width / 10(panelLineCount) data points requires in ms. 
    double timeInterval = 100.0 * rc.Width() / conversionRate;
    double shiftMax = 1000.0 * this->m_confParam.sectionLength / conversionRate;
    int timeUnit = (int)Millisecond;
    while (conversionRate >= 10 * 1000)
    {
        timeInterval *= 1000;
        conversionRate /= 1000;
        shiftMax *= 1000;
        --timeUnit;
    }

    m_timeUnit = (TimeUnit)timeUnit;

    CSliderCtrl* pshiftSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIMESHIFT);
    pshiftSlider->SetRangeMax(shiftMax);
    pshiftSlider->SetRangeMin(0);
    pshiftSlider->SetPos(0);
    int shiftTime = pshiftSlider->GetPos();
    m_shiftEdit = shiftTime;

    CSliderCtrl* pdivSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIMEDIV);
    int divValue = (int)timeInterval;
    m_divEdit = divValue;
    pdivSlider->SetRangeMax(4 * divValue);
    int divMin = divValue / 10;
    if ( divMin == 0 )
    {
        divMin = 1;
    }
    pdivSlider->SetRangeMin(divMin);
    pdivSlider->SetPos(divValue);

    TCHAR const * tUnit[] = {_T("ns"), _T("us"), _T("ms"), _T("Sec")};
    SetDlgItemText(IDC_STATIC_SHIFTUNIT, tUnit[timeUnit]);
    SetDlgItemText(IDC_STATIC_DIVUNIT, tUnit[timeUnit]);

    UpdateData(FALSE);
	//set parameters for plot.	
	m_simpleGraph.m_XCordTimeOffset = shiftTime;
   m_simpleGraph.Div(divValue);

	CString X_rangeLabels[2];
	m_simpleGraph.GetXCordRangeLabels(X_rangeLabels,m_simpleGraph.m_XCordTimeDiv*10 + shiftTime,shiftTime,m_timeUnit);
	((CStatic*)GetDlgItem(IDC_STATIC_ENDTIME))->SetWindowText(X_rangeLabels[0]);
	((CStatic*)GetDlgItem(IDC_STATIC_STARTTIME))->SetWindowText(X_rangeLabels[1]);

	ValueUnit unit;
	MathInterval rangeY ;
	CheckError(AdxGetValueRangeInformation((ValueRange)this->m_confParam.vrgType, 0, NULL, &rangeY, &unit));
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

   m_simpleGraph.Clear();
}

void CSynchonousOneBufferedAIDlg::InitListView()
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
		pcolorList->InsertColumn(i, _T(" "), LVCFMT_LEFT, 62);
	}
	for(i= 0; i < row; i++)
	{
		pcolorList->InsertItem(i, _T(" "));
		for (int j = 0; j < column; j++)
		{
			pcolorList->SetItemText(i, j, _T(" "));
		}
		pcolorList->SetItemData(i,i);
	}
}
void CSynchonousOneBufferedAIDlg::OnBnClickedButtonConfig()
{
	m_simpleGraph.Clear();
	m_confDlg.UpdateData(FALSE);
	int channelStart = m_wfAiCtrl->getConversion()->getChannelStart();
	m_confDlg.m_comboBox_ChannelStart.SetCurSel(channelStart);
	int channelCount = m_wfAiCtrl->getConversion()->getChannelCount();
	m_confDlg.m_comboBox_ChannelCount.SetCurSel(channelCount -1);
	DOUBLE clockRate = m_wfAiCtrl->getConversion()->getClockRate();
	m_confDlg.m_clockRatePerChan = clockRate;
	int32 sectionLength = m_wfAiCtrl->getRecord()->getSectionLength();
	m_confDlg.m_sectionLength = sectionLength;
	m_confDlg.UpdateData(FALSE);
    this->EnableWindow(FALSE);
    m_confDlg.ShowWindow(SW_SHOW);
}

void CSynchonousOneBufferedAIDlg::OnBnClickedButtonGetdata()
{
	// TODO: Add your control notification handler code here
   GetDlgItem(IDC_BUTTON_GETDATA)->EnableWindow(FALSE);
   GetDlgItem(IDC_BUTTON_CONFIG)->EnableWindow(FALSE);

   ErrorCode errorCode = m_wfAiCtrl->Start();
   CheckError(errorCode);

   m_wfAiCtrl->GetData(GetDataLength, m_data, -1, NULL, NULL, NULL, NULL);
   m_simpleGraph.Clear();
   m_simpleGraph.Chart(
   	  m_data,//the data of channels.
   	  m_confParam.channelCount,//channelcount, how many channel do you want to paint?
      m_confParam.sectionLength,//the data count for prechannel.
      1.0/m_wfAiCtrl->getConversion()->getClockRate());//time interval of the sample points.
   GetDlgItem(IDC_BUTTON_GETDATA)->EnableWindow(TRUE);
   GetDlgItem(IDC_BUTTON_CONFIG)->EnableWindow(TRUE);
}

void CSynchonousOneBufferedAIDlg::OnNMCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult)
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
}

void CSynchonousOneBufferedAIDlg::OnNMReleasedcaptureSliderTimeshift(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CSliderCtrl* pshiftSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIMESHIFT);
	int shiftTime = pshiftSlider->GetPos();
	m_shiftEdit = shiftTime;
   m_simpleGraph.Shift(shiftTime);

	CString ranges[2];
	m_simpleGraph.GetXCordRangeLabels(ranges,m_simpleGraph.m_XCordTimeDiv*10 + shiftTime,shiftTime,m_timeUnit);
	((CStatic*)GetDlgItem(IDC_STATIC_ENDTIME))->SetWindowText(ranges[0]);
	((CStatic*)GetDlgItem(IDC_STATIC_STARTTIME))->SetWindowText(ranges[1]);
	UpdateData(FALSE);
	*pResult = 0;
}

void CSynchonousOneBufferedAIDlg::OnNMReleasedcaptureSliderTimediv(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CSliderCtrl* pdivSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIMEDIV);
	int divTime = pdivSlider->GetPos();
	m_divEdit = divTime;
	m_simpleGraph.Div(divTime);
	
	CSliderCtrl* pshiftSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIMESHIFT);
	int shiftTime = pshiftSlider->GetPos();
	m_shiftEdit = shiftTime;

	UpdateData(FALSE);

	CString ranges[2];
	m_simpleGraph.GetXCordRangeLabels(ranges,m_simpleGraph.m_XCordTimeDiv*10 + shiftTime,shiftTime,m_timeUnit);
	((CStatic*)GetDlgItem(IDC_STATIC_ENDTIME))->SetWindowText(ranges[0]);
	((CStatic*)GetDlgItem(IDC_STATIC_STARTTIME))->SetWindowText(ranges[1]);
	*pResult = 0;
}

HBRUSH CSynchonousOneBufferedAIDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CSynchonousOneBufferedAIDlg::OnClose()
{
   // TODO: Add your message handler code here and/or call default
   if ( m_data != NULL)
   {
      delete [] m_data;
      m_data = NULL;
   }
   CDialog::OnClose();
}


