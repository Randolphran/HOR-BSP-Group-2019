// EventCountingDlg.h : header file
//

#pragma once
#include "ConfigurationDlg.h"
#include "afxwin.h"

// CBufferedEventCounterDlg dialog
class CBufferedEventCounterDlg : public CDialog
{
// Construction
public:
	CBufferedEventCounterDlg(CWnd* pParent = NULL);	// standard constructor
   ~CBufferedEventCounterDlg();
   // this function is used to deal with Interrupt Event. 
   static void  BDAQCALL OnBfdEventCounterEvent(void * sender, BfdCntrEventArgs * args, void * userParam);
   static void  BDAQCALL OnBfdEventCounterStoppedEvent(void * sender, BfdCntrEventArgs * args, void * userParam);
// Dialog Data
	enum { IDD = IDD_BFDEVENTCOUNTER_DIALOG };
// Implementation
protected:
	HICON m_hIcon;
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
   // Generated message map functions
   //{{AFX_MSG(CBufferedEventCounterDlg)
	virtual BOOL OnInitDialog();
   afx_msg LRESULT  OnConfDevice(WPARAM w,LPARAM l);// user-defined ,for getting the configuration information.
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
   afx_msg void OnBnClickedButtonConfig();
   afx_msg void OnStop(); 
   afx_msg void OnStart();
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg LRESULT OnUpdateValue(WPARAM wParam, LPARAM lParam); 
   afx_msg LRESULT OnStoppedEvent(WPARAM wParam, LPARAM lParam); 
   //}}AFX_MSG
private:
   DevConfParam       m_confParam; // the device's configure information from config form.
   BufferedEventCounterCtrl* m_bfdEventCounterCtrl;
   CConfigurationDlg	 m_confDlg;

   CBrush	  m_bkBk;
   CListBox   m_counterValueList;

   int32*     m_dataBuf;
   int32**    chs_dataBuf;

   int        m_eventChannel;
   int        m_displayChannel;
   int32      m_channelCountMax;
   
   int8*      m_channelEnable;
   int32      m_sectionLength;
   int        m_sectionCount;
   int32      m_samples;
   SignalDrop m_sampleClkSrc;
   
   TriggerAction m_trgAction;
   SignalDrop    m_trgSource;
   ActiveSignal  m_trgEdge;
   double        m_trgLevel;

   CComboBox m_cbx_eventChannel;
   CString   m_channelStatus;
   
   CString*  chs_Status;

   bool m_isRunning;
   bool m_haveData;

   void ConfigurateDevice();
   void ConfiguratePanel();
   void CheckError(ErrorCode errorCode);
   void OnCbnSelchangeEventChannel();

   void ChannelStatusChange(int channel, CString str);
   void DisplayChannelStatus(int channel);
   void DisplayChannelValue(int channel);
   void CopyChannelData(int channel);
	DECLARE_MESSAGE_MAP()
};
