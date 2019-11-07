// OneShotAsyncbufferedAiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AsynOneBufferedAI_TDtp.h"
#include "AsynOneBufferedAI_TDtpDlg.h"

using namespace Automation::BDaq;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define  SectionCount 1

extern TCHAR const * WCHAR_TO_TCHAR(WCHAR const * in, TCHAR * out);
// CAsynchronousOneBufferedAIDlg dialog

CAsynchronousOneBufferedAIDlg::CAsynchronousOneBufferedAIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAsynchronousOneBufferedAIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_data = NULL;
    m_confParam.deviceNumber = -1;
  // m_onAIStop.owner = this;
  // m_bufAiCtrl = NULL;
}

int CAsynchronousOneBufferedAIDlg::GetArrowXCordRelativeWidth(int dataReadyCountPerChan, int delayCountPerChan, int pixelCount) 
{
	int relativePixelWidth = 0;
   double rate = m_wfAiCtrl->getConversion()->getClockRate();

	CSliderCtrl* pshiftSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIMESHIFT);
	double shift = pshiftSlider->GetPos();
	CSliderCtrl* pdivSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIMEDIV);
	double divide = pdivSlider->GetPos();

	if (rate > 1000*10)
	{
		rate /= 1000;
	}
	int screenCount = (int)(divide * 10 * rate / 1000);
	int shiftCount = (int)(shift * rate / 1000);
   int showCount = dataReadyCountPerChan - delayCountPerChan - shiftCount ;
	if (showCount >= 0 && showCount <= screenCount) 
	{
		relativePixelWidth = pixelCount * showCount  / screenCount;
		TRACE("relativePixelWidth is %d\n",relativePixelWidth);
	}else{
		relativePixelWidth = -1;
	}
	return relativePixelWidth;
}
void CAsynchronousOneBufferedAIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_GRAPH, m_simpleGraph);
	DDX_Text(pDX, IDC_EDIT_TIMESHIFT, m_shiftEdit);
	DDX_Text(pDX, IDC_EDIT_TIMEDIV, m_divEdit);
}

BEGIN_MESSAGE_MAP(CAsynchronousOneBufferedAIDlg, CDialog)
    //{{AFX_MSG_MAP(CAsyncOneBufferedAiDlg)
   ON_MESSAGE(WM_CUSTOME_CFG_CHGED,OnConfDevice)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST, OnNMCustomDrawList)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TIMESHIFT, OnNMReleasedCaptureSliderTimeShift)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TIMEDIV, OnNMReleasedcaptureSliderTimediv)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG, OnBnClickedButtonConfig)
	ON_BN_CLICKED(IDC_BUTTON_GETDATA, OnBnClickedButtonGetdata)
	ON_WM_CLOSE()
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CAsynchronousOneBufferedAIDlg message handlers

LRESULT  CAsynchronousOneBufferedAIDlg::OnConfDevice(WPARAM w,LPARAM l)
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

LRESULT CAsynchronousOneBufferedAIDlg::OnAiStop(WPARAM wParam, LPARAM lParam)
{
   GetDlgItem(IDC_BUTTON_GETDATA)->EnableWindow(TRUE);
   GetDlgItem(IDC_BUTTON_CONFIG)->EnableWindow(TRUE);
   return 1;
}

void CAsynchronousOneBufferedAIDlg::SetTriggerPointFlagLoacation(int delayCountPerChan)
{
	if (m_wfAiCtrl->getTrigger() != NULL)
	{
		CWnd * arrowPicBox = (GetDlgItem(IDC_STATIC_TRIGGER));
		CWnd * triggerLable = (GetDlgItem(IDC_STATIC_TRIGGERPOINT));
		CWnd *  graph = GetDlgItem(IDC_STATIC_GRAPH);
		RECT rectGraph;
		graph->GetWindowRect(&rectGraph);
		int graphWidth = rectGraph.right - rectGraph.left;

		// relative length value according to main window
      int DataReadyCountPerChan = (int)(m_ReadyDataCountAllChan)/(m_wfAiCtrl->getConversion()->getChannelCount());
      double  rate = m_wfAiCtrl->getConversion()->getClockRate();
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

		CString str;
		str.Format(_T("%.3f "),triggerTime);
		str  = str + unit + " Triggered.";

		triggerLable->SetWindowText(str);

		int delayCount = m_wfAiCtrl->getTrigger()->getDelayCount();
		int relativeWidth = GetArrowXCordRelativeWidth(DataReadyCountPerChan, delayCountPerChan, graphWidth);
		if (relativeWidth < 0)
		{
			arrowPicBox->ShowWindow(SW_HIDE);
			triggerLable->ShowWindow(SW_HIDE);
		}else{
			arrowPicBox->ShowWindow(SW_SHOW);
			triggerLable->ShowWindow(SW_SHOW);

			RECT graphWindow;
			graph->GetWindowRect(&graphWindow);
			this->ScreenToClient(&graphWindow);
			RECT rectArrowClient;
			arrowPicBox->GetClientRect(&rectArrowClient);
			// relative length value according to main window
			arrowPicBox->SetWindowPos(NULL,graphWindow.left+ relativeWidth,graphWindow.bottom,
											  0,0,SWP_NOZORDER|SWP_NOSIZE);
			triggerLable->SetWindowPos(NULL,graphWindow.left + relativeWidth + rectArrowClient.right,graphWindow.bottom,
				0,0,SWP_NOZORDER|SWP_NOSIZE);
			this->Invalidate(FALSE);
		}
	}
}

void CAsynchronousOneBufferedAIDlg::OnStoppedEvent(void * sender, BfdAiEventArgs * args, void * userParam)
{
   WaveformAiCtrl * wfAiCtrl = (WaveformAiCtrl *)sender;
   CAsynchronousOneBufferedAIDlg * uParam = (CAsynchronousOneBufferedAIDlg *)userParam;
	int32 getDataCount = ((uParam->m_confParam.channelCount*uParam->m_confParam.sectionLength*SectionCount) < args->Count)?(uParam->m_confParam.channelCount*uParam->m_confParam.sectionLength*SectionCount) : args->Count;
   ErrorCode ret = wfAiCtrl->GetData(getDataCount, uParam->m_data, 0, NULL, NULL, NULL, NULL);
   if ((ret >= ErrorHandleNotValid) && (ret != Success))
   {
       CString str;
       str.Format(_T("Some errors happened, the error code is: 0x%X !\n"),ret);
       AfxMessageBox(str);
   }
   
   uParam->ConfigurateGraph(getDataCount / uParam->m_confParam.channelCount);
   uParam->m_ReadyDataCountAllChan = getDataCount;
   uParam->m_simpleGraph.Clear();
   uParam->m_simpleGraph.Chart(
   	 uParam->m_data, //the data of channels.
   	 uParam->m_confParam.channelCount, //channelcount, how many channel do you want to paint?
   	 getDataCount / uParam->m_confParam.channelCount,//the data count for prechannel.
     1.0/wfAiCtrl->getConversion()->getClockRate());//time interval of the sample points.

   Trigger * trigger = NULL;
   if (uParam->m_confParam.triggerIndex == 0)
   {
      trigger = wfAiCtrl->getTrigger();
   }else if(uParam->m_confParam.triggerIndex == 1){
      trigger = wfAiCtrl->getTrigger1();
   }

   if (trigger != NULL)
   {
      if (trigger->getSource() != SignalNone)
      {
         // relative length value according to main window
         int delayCountPerChan = trigger->getDelayCount();
         uParam->SetTriggerPointFlagLoacation(delayCountPerChan);
      }
   }

   uParam->GetDlgItem(IDC_BUTTON_GETDATA)->EnableWindow(TRUE);
   uParam->GetDlgItem(IDC_BUTTON_CONFIG)->EnableWindow(TRUE);
   //TRACE("data handler\n");
}


BOOL CAsynchronousOneBufferedAIDlg::OnInitDialog()
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
   m_wfAiCtrl->addStoppedHandler(OnStoppedEvent, this);

	CWnd * arrowPicBox = (GetDlgItem(IDC_STATIC_TRIGGER));
	RECT rectArrowWindow;
	arrowPicBox->GetWindowRect(&rectArrowWindow);
	this->ScreenToClient(&rectArrowWindow);

	(GetDlgItem(IDC_STATIC_TRIGGER))->ShowWindow(SW_HIDE);
	(GetDlgItem(IDC_STATIC_TRIGGERPOINT))->ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAsynchronousOneBufferedAIDlg::OnPaint()
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
HCURSOR CAsynchronousOneBufferedAIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAsynchronousOneBufferedAIDlg::OnNMCustomDrawList(NMHDR *pNMHDR, LRESULT *pResult)
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
			   lplvcd->clrTextBk = RGB(255,255, 255);
			   *pResult = CDRF_NEWFONT;
		   }
		   break;
	   default:
		   *pResult = CDRF_DODEFAULT;
		   break;
	}
	//*pResult = 0;
}

void CAsynchronousOneBufferedAIDlg::OnNMReleasedCaptureSliderTimeShift(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	CSliderCtrl* pshiftSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIMESHIFT);
	int shiftTime = pshiftSlider->GetPos();
	m_shiftEdit = shiftTime;

   Trigger * trigger = NULL;
   if (m_confParam.triggerIndex == 0)
   {
      trigger = m_wfAiCtrl->getTrigger();
   }else if(m_confParam.triggerIndex == 1){
      trigger = m_wfAiCtrl->getTrigger1();
   }
	if (trigger != NULL)
	{
		if (trigger->getSource() != SignalNone)
		{
			int delayCount = trigger->getDelayCount();
			SetTriggerPointFlagLoacation(delayCount);
		}
	}
	CString ranges[2];
	m_simpleGraph.GetXCordRangeLabels(ranges,m_simpleGraph.m_XCordTimeDiv*10 + shiftTime,shiftTime,m_timeUnit);
	((CStatic*)GetDlgItem(IDC_STATIC_ENDTIME))->SetWindowText(ranges[0]);
	((CStatic*)GetDlgItem(IDC_STATIC_STARTTIME))->SetWindowText(ranges[1]);
   UpdateData(FALSE);
	m_simpleGraph.Shift(shiftTime);
	*pResult = 0;
}

void CAsynchronousOneBufferedAIDlg::OnNMReleasedcaptureSliderTimediv(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CSliderCtrl* pdivSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIMEDIV);
	int divTime = pdivSlider->GetPos();
	m_divEdit = divTime;
	m_simpleGraph.Div(divTime);

	CSliderCtrl* pshiftSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_TIMESHIFT);
	int shiftTime = pshiftSlider->GetPos();
	m_shiftEdit = shiftTime;

   Trigger * trigger = NULL;
   if (m_confParam.triggerIndex == 0)
   {
      trigger = m_wfAiCtrl->getTrigger();
   }else if(m_confParam.triggerIndex == 1){
      trigger = m_wfAiCtrl->getTrigger1();
   }

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
	m_simpleGraph.GetXCordRangeLabels(ranges,m_simpleGraph.m_XCordTimeDiv*10 + shiftTime,shiftTime,m_timeUnit);
	((CStatic*)GetDlgItem(IDC_STATIC_ENDTIME))->SetWindowText(ranges[0]);
	((CStatic*)GetDlgItem(IDC_STATIC_STARTTIME))->SetWindowText(ranges[1]);

	*pResult = 0;
}

void CAsynchronousOneBufferedAIDlg::OnBnClickedButtonConfig()
{
	// TODO: Add your control notification handler code here
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

void CAsynchronousOneBufferedAIDlg::OnBnClickedButtonGetdata()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_GETDATA)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONFIG)->EnableWindow(FALSE);

   ErrorCode errorCode = m_wfAiCtrl->Start();
	CheckError(errorCode);

	GetDlgItem(IDC_SLIDER_TIMESHIFT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SLIDER_TIMEDIV)->EnableWindow(TRUE);
}

void CAsynchronousOneBufferedAIDlg::CheckError(ErrorCode error)
{
	if (BioFailed(error))
	{
      CString str;
      str.Format(_T("Some errors happened, the error code is: 0x%X !\n"),error);
      AfxMessageBox(str);
     OnBnClickedButtonConfig();
	}
}
void CAsynchronousOneBufferedAIDlg::ConfigurateDevice()
{
   ErrorCode	errorCode;
   if ( m_data != NULL)
   {
      delete [] m_data;
      m_data = NULL;
   }
	// in asynchronous buffered AI mode user data buffer is equal to raw data buffer.
	long userDataBufferLength = m_confParam.channelCount* m_confParam.sectionLength*SectionCount;
   m_data = new DOUBLE[userDataBufferLength];
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
   str.Format(_T("Asynchronous One Buffered AI with Trigger Delay to Stop - Run( %s )"),WCHAR_TO_TCHAR((LPCWSTR)devInfo.Description,des));
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
	
   int count = m_wfAiCtrl->getFeatures()->getChannelCountMax();
	Array<AiChannel> * channels = m_wfAiCtrl->getChannels();
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
   if (m_confParam.triggerIndex == 0)
   {
      Trigger * trigger = m_wfAiCtrl->getTrigger();
      // close the trigger1,in order to avoid affect trigger0
      if(m_wfAiCtrl->getFeatures()->getTriggerCount() > 1)
      {
         m_wfAiCtrl->getTrigger1()->setSource(SignalNone);
      }
      (GetDlgItem(IDC_STATIC_TRIGGER))->ShowWindow(SW_SHOW);
      (GetDlgItem(IDC_STATIC_TRIGGERPOINT))->ShowWindow(SW_SHOW);

      if (trigger != NULL)
      {
         trigger->setSource((SignalDrop)(m_confParam.triggerSource));
         if (trigger->getSource() != SignalNone)
         {
            trigger->setAction((TriggerAction)m_confParam.triggerAction);
            trigger->setEdge((ActiveSignal )(m_confParam.triggerEdge));
            trigger->setLevel(m_confParam.triggerLevel);
            trigger->setDelayCount((int)m_confParam.delayCount);
         }else{
            (GetDlgItem(IDC_STATIC_TRIGGER))->ShowWindow(SW_HIDE);
            (GetDlgItem(IDC_STATIC_TRIGGERPOINT))->ShowWindow(SW_HIDE);
         }
      }else{
         (GetDlgItem(IDC_STATIC_TRIGGER))->ShowWindow(SW_HIDE);
         (GetDlgItem(IDC_STATIC_TRIGGERPOINT))->ShowWindow(SW_HIDE);

      }
   }else if (m_confParam.triggerIndex == 1){

      // trigger1 parameters setting
      if (m_wfAiCtrl->getFeatures()->getTriggerCount() > 1)
      {
         Trigger * trigger1 = m_wfAiCtrl->getTrigger1();
         if (m_wfAiCtrl->getFeatures()->getTriggerCount() > 0)
         {
            m_wfAiCtrl->getTrigger()->setSource(SignalNone);
         }

         (GetDlgItem(IDC_STATIC_TRIGGER))->ShowWindow(SW_SHOW);
         (GetDlgItem(IDC_STATIC_TRIGGERPOINT))->ShowWindow(SW_SHOW);
         if (trigger1 != NULL)
         {
            trigger1->setSource((SignalDrop)(m_confParam.triggerSource));
            if (trigger1->getSource() != SignalNone)
            {
               trigger1->setAction((TriggerAction)m_confParam.triggerAction);
               trigger1->setEdge((ActiveSignal )(m_confParam.triggerEdge));
               trigger1->setLevel(m_confParam.triggerLevel);
               trigger1->setDelayCount((int)m_confParam.delayCount);
            }else{
               (GetDlgItem(IDC_STATIC_TRIGGER))->ShowWindow(SW_HIDE);
               (GetDlgItem(IDC_STATIC_TRIGGERPOINT))->ShowWindow(SW_HIDE);
            }
         }else{
            (GetDlgItem(IDC_STATIC_TRIGGER))->ShowWindow(SW_HIDE);
            (GetDlgItem(IDC_STATIC_TRIGGERPOINT))->ShowWindow(SW_HIDE);
         }
      }
   }

   // prepare the buffered AI. 
   errorCode = m_wfAiCtrl->Prepare();
   CheckError(errorCode);

}
void CAsynchronousOneBufferedAIDlg::ConfigurateGraph()
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
	if ((ValueRange)this->m_confParam.vrgType < Jtype_0To760C)
	{
		CheckError(AdxGetValueRangeInformation((ValueRange)this->m_confParam.vrgType, 0, NULL, &rangeY, &unit));
		if (Milliampere == unit  || Millivolt == unit )
		{
			rangeY.Max /= 1000;
			rangeY.Min /= 1000;
		}
	}
	else
	{
		unit = CelsiusUnit;
		switch ((ValueRange)this->m_confParam.vrgType)
		{
		case Jtype_0To760C:
			rangeY.Max = 760;
			rangeY.Min = 0;
			break;
		case Ktype_0To1370C:
			rangeY.Max = 1370;
			rangeY.Min = 0;
			break;
		case Ttype_Neg100To400C:
			rangeY.Max = 400;
			rangeY.Min = -100;
			break;
		case Etype_0To1000C:
			rangeY.Max = 1000;
			rangeY.Min = 0;
			break;
		case Rtype_500To1750C:
		case Stype_500To1750C:
			rangeY.Max = 1750;
			rangeY.Min = 500;
			break;
		case Btype_500To1800C:
			rangeY.Max = 1800;
			rangeY.Min = 500;
			break;
		default:
			rangeY.Max = 100;
			rangeY.Min = 0;
			break;
		}
	}
	CString Y_rangeLabels[3];
	m_simpleGraph.GetYCordRangeLabels(Y_rangeLabels,rangeY.Max,rangeY.Min,unit);
	((CStatic*)GetDlgItem(IDC_STATIC_YRANGEMAX))->SetWindowText(Y_rangeLabels[0]);
	((CStatic*)GetDlgItem(IDC_STATIC_YRANGEMID))->SetWindowText(Y_rangeLabels[2]);
	((CStatic*)GetDlgItem(IDC_STATIC_YRANGEMIN))->SetWindowText(Y_rangeLabels[1]);
	m_simpleGraph.m_YCordRangeMax = rangeY.Max;
	m_simpleGraph.m_YCordRangeMin = rangeY.Min;

	m_simpleGraph.Clear();
	GetDlgItem(IDC_SLIDER_TIMESHIFT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SLIDER_TIMEDIV)->EnableWindow(FALSE);
}

void CAsynchronousOneBufferedAIDlg::ConfigurateGraph( int samplesCountPerChan )
{
    CRect rc;
    CWnd *pWnd = GetDlgItem(IDC_STATIC_GRAPH);
    pWnd->GetClientRect(&rc);
    double conversionRate = m_wfAiCtrl->getConversion()->getClockRate();
    //1 pixel to 1 data point. How much time plotting rc.Width / 10(panelLineCount) data points requires in ms. 
    double timeInterval = 100.0 * rc.Width() / conversionRate;
    double shiftMax = 1000.0 * samplesCountPerChan / conversionRate;
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
	GetDlgItem(IDC_SLIDER_TIMESHIFT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SLIDER_TIMEDIV)->EnableWindow(TRUE);
}


void CAsynchronousOneBufferedAIDlg::InitListView()
{
	CListCtrl*	pcolorList = (CListCtrl*)this->GetDlgItem(IDC_LIST);	
	while (pcolorList->DeleteColumn(0));
	pcolorList->DeleteAllItems();
	pcolorList->SetExtendedStyle(LVS_EX_GRIDLINES );
	//pcolorList->SetExtendedStyle(pcolorList->GetExtendedStyle() | LVS_EX_DOUBLEBUFFER);

	CImageList imagelist;
	imagelist.Create(IDB_BITMAP_LIST, 1, 20, RGB(255, 255, 0));
	pcolorList->SetImageList(&imagelist, LVSIL_SMALL);
	//pcolorList->SetBkColor(RGB(236, 224, 220));

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
HBRUSH CAsynchronousOneBufferedAIDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

void CAsynchronousOneBufferedAIDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if ( m_data != NULL )
	{
		delete [] m_data;
		m_data = NULL;
	}
   m_wfAiCtrl->Dispose();
	CDialog::OnClose();
}
