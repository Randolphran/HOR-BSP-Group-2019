// StreamingAiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StreamingAI_Retrigger.h"
#include "StreamingAI_RetriggerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CStreamingAIDlg dialog
extern TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out);
CStreamingAIDlg::CStreamingAIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStreamingAIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_data = NULL;
    m_wfAiCtrl = NULL;
}

void CStreamingAIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_GRAPH, m_simpleGraph);
}

BEGIN_MESSAGE_MAP(CStreamingAIDlg, CDialog)
   //{{AFX_MSG_MAP(CStreamingAIDlg)
   ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONFIG, OnBnClickedButtonConfig)
	ON_BN_CLICKED(IDC_BUTTON_START, OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnBnClickedButtonStop)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST, OnNMCustomdrawList)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TIMEDIV, OnNMReleasedcaptureSliderTimediv)

   //}}AFX_MSG_MAP
END_MESSAGE_MAP()
// CStreamingAIDlg message handlers

LRESULT  CStreamingAIDlg::OnConfDevice(WPARAM w,LPARAM l)
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

void CStreamingAIDlg::OnDataReadyEvent(void * sender, BfdAiEventArgs * args, void *userParam)
{
	ErrorCode ret = Success;
   CStreamingAIDlg * uParam = (CStreamingAIDlg *) userParam;
	int32 getDataCount = ((uParam->m_confParam.sectionLength * uParam->m_confParam.channelCount) < args->Count)? (uParam->m_confParam.sectionLength * uParam->m_confParam.channelCount) :args->Count;
	int32 returnedCount = 0;
	double timeStamp = 0.0;
	int32 realDataCount = 0;

	uParam->m_flag = false;
	uParam->m_readyDataCountAllChan = args->Count;
	ret = uParam->m_wfAiCtrl->GetData(getDataCount, uParam->m_data, 0, &returnedCount, &timeStamp, NULL, NULL);
    if ((ret >= ErrorHandleNotValid) && (ret != Success))
    {
        CString str;
        str.Format(_T("Some errors happened, the error code is: 0x%X !\n"),ret);
        AfxMessageBox(str);
    }

	uParam->m_flag = (ret == WarningRecordEnd ) ? TRUE : FALSE;
	realDataCount = (returnedCount < getDataCount) ? returnedCount : getDataCount;
	
	uParam->m_simpleGraph.Chart(uParam->m_data,//the data of channels. 
										 uParam->m_confParam.channelCount,//channelcount, how many channel do you want to paint?
										 realDataCount/uParam->m_confParam.channelCount,//the data count for prechannel.
										 1.0/uParam->m_wfAiCtrl->getConversion()->getClockRate(),//time interval of the sample points.
										 uParam->m_flag);//recordEndFlag
}

void CStreamingAIDlg::OnCacheOverflowEvent(void * sender, BfdAiEventArgs * args, void *userParam)
{
   //AfxMessageBox(_T("BufferedAiCacheOverflow"));
}

void CStreamingAIDlg::OnOverRunEvent(void * sender, BfdAiEventArgs * args, void *userParam)
{
   AfxMessageBox(_T("BufferedAiOverrun"));
}

void CStreamingAIDlg::OnStopEvent(void * sender, BfdAiEventArgs * args, void *userParam)
{
   //AfxMessageBox(_T("EvtBufferedAiStopped"));
	CStreamingAIDlg *uParam = (CStreamingAIDlg *) userParam;
	uParam->GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
   uParam->GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	uParam->GetDlgItem(IDC_BUTTON_CONFIG)->EnableWindow(TRUE);
	uParam->GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
	uParam->GetDlgItem(IDC_SLIDER_TIMEDIV)->EnableWindow(TRUE);	
}

void CStreamingAIDlg::OnBurnOutEvent(void * sender, BfdAiEventArgs * args, void *userParam)
{
	AfxMessageBox(_T("EvtBufferedAiBurnOut"));
}

BOOL CStreamingAIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
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

   m_wfAiCtrl = WaveformAiCtrl::Create();
   // Set the notification event Handler by which we can known the state of operation effectively.
   m_wfAiCtrl->addDataReadyHandler(OnDataReadyEvent, this);
   m_wfAiCtrl->addCacheOverflowHandler(OnCacheOverflowEvent, this);
   m_wfAiCtrl->addOverrunHandler(OnOverRunEvent, this);
   m_wfAiCtrl->addStoppedHandler(OnStopEvent, this);

	CRect rc;
	CWnd *pWnd = GetDlgItem(IDC_STATIC_GRAPH);
	pWnd->GetClientRect(&rc);
	m_simpleGraph.InitGraph();
	return FALSE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStreamingAIDlg::OnPaint()
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
HCURSOR CStreamingAIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStreamingAIDlg::CheckError(ErrorCode error)
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

void CStreamingAIDlg::ConfigurateDevice()
{
   ErrorCode	errorCode;
   // Select a device with AccessWrite/AccessWriteWithReset mode with device number or device description.
   DeviceInformation devInfo(m_confParam.deviceNumber);
   errorCode = m_wfAiCtrl->setSelectedDevice(devInfo);
   CheckError(errorCode);
	errorCode= m_wfAiCtrl->LoadProfile(m_confParam.profilePath);
	CheckError(errorCode);

   m_wfAiCtrl->getSelectedDevice(devInfo);
   CString str ;
   str.Format(_T("Streaming AI with Retrigger - Run( %s )"),m_confParam.deviceDescription);
   SetWindowText(str);
   
	//users can set the size of buffer for saving data by sectionLength and channelCount.
	m_channelCount = (int)(this->m_confParam.channelCount);
	m_sectionLength = (m_confParam.sectionLength > USER_BUFFER_LENTH_MAX_PER_CHAN) ? USER_BUFFER_LENTH_MAX_PER_CHAN : m_confParam.sectionLength;
	if ( m_data != NULL)
	{
		delete [] m_data;
		m_data = NULL;
	}

	int32 bufferDataLength = m_confParam.sectionLength * m_confParam.channelCount;
	m_data = new DOUBLE[bufferDataLength];// re-allocate array if channel count has changed.
	if (m_data == NULL)
	{
		AfxMessageBox(_T("Sorry! Error in allocating memory...."));
		this->CloseWindow();
		return;
	}

   // Set necessary parameters for Buffered AI operation, 
   Conversion * conversion = m_wfAiCtrl->getConversion();
   errorCode = conversion->setChannelStart(m_confParam.channelStart);
   CheckError(errorCode);
   errorCode =conversion->setChannelCount(m_confParam.channelCount);
   CheckError(errorCode);
	errorCode =conversion->setClockRate(m_confParam.clockRatePerChan);
   CheckError(errorCode);
	Record * record = m_wfAiCtrl->getRecord();
   errorCode = record->setSectionCount(0);//0 means streaming mode.
   CheckError(errorCode);
   errorCode = record->setSectionLength(m_sectionLength);
   CheckError(errorCode);
	errorCode = record->setCycles(m_confParam.cycles);
	CheckError(errorCode);

	// Get Accurate clock Rate for configuring graph
   m_confParam.clockRatePerChan = m_wfAiCtrl->getConversion()->getClockRate();

	// Initialize 
   int count = m_wfAiCtrl->getFeatures()->getChannelCountMax();
	Array<AiChannel> *channels =  m_wfAiCtrl->getChannels();
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

	// trigger parameters setting
   if(m_wfAiCtrl->getFeatures()->getTriggerCount() > 0)
   {
      Trigger * trigger = m_wfAiCtrl->getTrigger();
      trigger->setAction((TriggerAction)m_confParam.triggerAction);
      trigger->setSource((SignalDrop)(m_confParam.triggerSource));
      trigger->setEdge((ActiveSignal )(m_confParam.triggerEdge));
      trigger->setLevel(m_confParam.triggerLevel);
      trigger->setDelayCount(m_confParam.delayCount);
   }
   // trigger1 parameters setting
     if(m_wfAiCtrl->getFeatures()->getTriggerCount() > 1)
   {
      Trigger * trigger1 = m_wfAiCtrl->getTrigger1();
      trigger1->setAction((TriggerAction)m_confParam.trigger1Action);
      trigger1->setSource((SignalDrop)(m_confParam.trigger1Source));
      trigger1->setEdge((ActiveSignal )(m_confParam.trigger1Edge));
      trigger1->setLevel(m_confParam.trigger1Level);
      trigger1->setDelayCount(m_confParam.delayCount1);
   }

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONFIG)->EnableWindow(TRUE);
}

void CStreamingAIDlg::ConfigurateGraph()
{
    CRect rc;
    CWnd *pWnd = GetDlgItem(IDC_STATIC_GRAPH);
    pWnd->GetClientRect(&rc);
    double convertRate = m_wfAiCtrl->getConversion()->getClockRate();
    int timeUnit = (int)Millisecond;

    double timeInterval = 100.0 * rc.Width() / convertRate;
    while (convertRate >= 10 * 1000)
    {
        timeInterval *= 1000;
        convertRate /= 1000;
        --timeUnit;
    }
    m_timeUnit = (TimeUnit)timeUnit;

    CSliderCtrl* pdivSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIMEDIV);
    int divValue = (int)timeInterval;
    pdivSlider->SetRangeMax(4 * divValue);
    int divMin = divValue / 10;
    if ( divMin == 0 )
    {
        divMin = 1;
    }
    pdivSlider->SetRangeMin(divMin);
    pdivSlider->SetPos(divValue);
    UpdateData(FALSE);

    //set parameters for plot.	
    m_simpleGraph.m_XCordTimeOffset = 0;
    m_simpleGraph.Div(divValue);

	CString X_rangeLabels[2];
	DOUBLE shiftTime = this->m_simpleGraph.m_XCordTimeOffset;
	m_simpleGraph.GetXCordRangeLabels(X_rangeLabels,m_simpleGraph.m_XCordTimeDiv*10 + shiftTime,shiftTime,m_timeUnit);
	((CStatic*)GetDlgItem(IDC_STATIC_ENDTIME))->SetWindowText(X_rangeLabels[0]);
	((CStatic*)GetDlgItem(IDC_STATIC_STARTTIME))->SetWindowText(X_rangeLabels[1]);

	ValueUnit	  unit;
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

}

void CStreamingAIDlg::InitListView()
{
	CListCtrl*	pcolorList = (CListCtrl*)this->GetDlgItem(IDC_LIST);	
	while (pcolorList->DeleteColumn(0));
	pcolorList->DeleteAllItems();
	pcolorList->SetExtendedStyle(LVS_EX_GRIDLINES);
	pcolorList->SetExtendedStyle(pcolorList->GetExtendedStyle());

	CImageList imagelist;
	imagelist.Create(IDB_BITMAP_LIST, 1, 12, RGB(255, 255, 0));
	pcolorList->SetImageList(&imagelist, LVSIL_SMALL);

	int row = 2;				
	int column = 8;        ////Notice, we use '8' for the number of items in a color list row
   int i = 0;
	for (i = 0; i < column; i++)
	{
		pcolorList->InsertColumn(i, _T(" "), LVCFMT_LEFT, 50);
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
void CStreamingAIDlg::OnBnClickedButtonConfig()
{
	// TODO: Add your control notification handler code here
   m_wfAiCtrl->Stop();
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

void CStreamingAIDlg::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONFIG)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(TRUE);

   // prepare the Waveform AI. 
   ErrorCode errorCode = m_wfAiCtrl->Prepare();
   CheckError(errorCode);
   errorCode = m_wfAiCtrl->Start();
   CheckError(errorCode);
}
void CStreamingAIDlg::OnBnClickedButtonPause()
{
	// TODO: Add your control notification handler code here
    ErrorCode err = Success;
    err = m_wfAiCtrl->Stop();    
    if (err != Success)
    {
        CheckError(err);
        return;
    }

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
   GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CONFIG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
	//GetDlgItem(IDC_SLIDER_TIMEDIV)->EnableWindow(FALSE);
}

void CStreamingAIDlg::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
    ErrorCode err = Success;
    err = m_wfAiCtrl->Stop();    
    if (err != Success)
    {
        CheckError(err);
        return;
    }

	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CONFIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(FALSE);
   GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_SLIDER_TIMEDIV)->EnableWindow(TRUE);
	this->m_simpleGraph.Clear();
}

void CStreamingAIDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
   m_wfAiCtrl->Dispose();
	if ( m_data != NULL )
	{
		delete [] m_data;
		m_data = NULL;
	}
	CDialog::OnClose();
}

HBRUSH CStreamingAIDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CStreamingAIDlg::OnNMCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
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
	//*pResult = 0;
}

void CStreamingAIDlg::OnNMReleasedcaptureSliderTimediv(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CSliderCtrl* pdivSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIMEDIV);
	m_simpleGraph.Div(pdivSlider->GetPos());
   TRACE("slider:%d",pdivSlider->GetPos());
	//m_simpleGraph.Clear();

	Trigger * trigger = m_wfAiCtrl->getTrigger1();
	if (trigger != NULL)
	{
		if (trigger->getSource() != SignalNone)
		{
			int delayCount = trigger->getDelayCount();
			SetTriggerPointFlagLoacation(delayCount);
		}
	}
	UpdateData(FALSE);

	CString ranges[2];
	m_simpleGraph.GetXCordRangeLabels(ranges,m_simpleGraph.m_XCordTimeDiv*10 ,0, m_timeUnit);
	((CStatic*)GetDlgItem(IDC_STATIC_ENDTIME))->SetWindowText(ranges[0]);
	((CStatic*)GetDlgItem(IDC_STATIC_STARTTIME))->SetWindowText(ranges[1]);
}

int CStreamingAIDlg::GetArrowXCordRelativeWidth(int dataReadyCountPerChan, int delayCountPerChan, int pixelCount)
{
	int relativePixelWidth = 0;
	double rate = m_wfAiCtrl->getConversion()->getClockRate();
	CSliderCtrl* pdivSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIMEDIV);
	double divide = pdivSlider->GetPos();

	if (rate > 1000*10)
	{
		rate /= 1000;
	}
	int screenCount = (int)(divide * 10 * rate / 1000);
	int showCount = dataReadyCountPerChan - delayCountPerChan;
	if (showCount >= 0 && showCount <= screenCount)// 
	{
		relativePixelWidth = pixelCount * showCount / screenCount;
		TRACE("relativePixelWidth is %d\n",relativePixelWidth);
	}else{
		relativePixelWidth = -1;
	}
	return relativePixelWidth;
}

void CStreamingAIDlg::SetTriggerPointFlagLoacation(int delayCountPerChan)
{
	if (m_wfAiCtrl->getTrigger1() != NULL)
	{
		CWnd *  graph = GetDlgItem(IDC_STATIC_GRAPH);
		RECT rectGraph;
		graph->GetWindowRect(&rectGraph);
		int graphWidth = rectGraph.right - rectGraph.left;

		// relative length value according to main window
		int DataReadyCountPerChan = (int)(m_readyDataCountAllChan)/(m_wfAiCtrl->getConversion()->getChannelCount());
		double rate = m_wfAiCtrl->getConversion()->getClockRate();

		CString unit = " ms";
		double triggerTime = 0;
		double timeFactor = 1000;
		if (rate > 1000 * 1000)
		{
			unit = " us";
			timeFactor = 1000 * 1000;
		}

		triggerTime = timeFactor * (DataReadyCountPerChan - delayCountPerChan) / rate;
		if (triggerTime > 1000 && unit == "us")
		{
			triggerTime /= 1000;
			unit = " ms";
		}
		if (triggerTime < 1 && unit == "ms")
		{
			triggerTime *= 1000;
			unit = " us";
		}
	}
}
