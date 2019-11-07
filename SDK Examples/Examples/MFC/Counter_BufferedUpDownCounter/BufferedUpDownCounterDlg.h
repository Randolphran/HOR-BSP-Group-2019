// UpDownCounterDlg.h : header file
//

#pragma once
#include "ConfigurationDlg.h"
#include "afxwin.h"

// CUpDownCounterDlg dialog
class CBufferedUpDownCounterDlg : public CDialog
{
// Construction
public:
	CBufferedUpDownCounterDlg(CWnd* pParent = NULL);	// standard constructor
   ~CBufferedUpDownCounterDlg();

// this function is used to deal with Interrupt Event. 
   static void BDAQCALL OnBfdUdCounterEvent(void * sender, BfdCntrEventArgs * args, void * userParam);
   static void BDAQCALL OnBfdUdCounterStoppedEvent(void * sender, BfdCntrEventArgs * args, void * userParam);

// Dialog Data
	enum { IDD = IDD_UPDOWNCOUNTER_DIALOG };
// Implementation
protected:
	HICON m_hIcon;
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
   // Generated message map functions
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
   
private:
   DevConfParam               m_confParam; // the device's configure information from config form.
   BufferedUdCounterCtrl*     m_bfdUdCounterCtrl;
   CConfigurationDlg	         m_confDlg;

   CBrush	 m_bkBk;
   CListBox  m_counterValueList;
   int32*    m_dataBuf;
   int32**   chs_dataBuf;

   int       m_eventChannel;
   int       m_displayChannel;

   int8*         m_channelEnable;
   int32         m_sectionLength;
   int           m_sectionCount;
   int32         m_samples;
   SignalDrop    m_sampleClkSrc;
   CountingType  m_countingType;
   int32         m_channelCountMax;


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
   void CheckError(ErrorCode errorCode);
   void OnCbnSelchangeEventChannel();

   void ChannelStatusChange(int channel, CString str);
   void DisplayChannelStatus(int channel);
   void DisplayChannelValue(int channel);
   void CopyChannelData(int channel);
   DECLARE_MESSAGE_MAP()
};
