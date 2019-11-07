// PwMeterDlg.h : header file
//

#pragma once
#include "ConfigurationDlg.h"
#include "afxwin.h"

// CPulseWidthMeasurementDlg dialog
class CBufferedPulseWidthMeasurementDlg : public CDialog
{
// Construction
public:
	CBufferedPulseWidthMeasurementDlg(CWnd* pParent = NULL);	// standard constructor
   ~CBufferedPulseWidthMeasurementDlg();

// this function is used to deal with Interrupt Event. 
   static void BDAQCALL OnBfdPwMeterEvent(void * sender, BfdCntrEventArgs * args, void * userParam);
   static void BDAQCALL OnBfdPwMeterStoppedEvent(void * sender, BfdCntrEventArgs * args, void * userParam);

// Dialog Data
	enum { IDD = IDD_BFDPWMEASUREMENT_DIALOG };

// Implementation
protected:
	HICON m_hIcon;
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
   // Generated message map functions
   //{{AFX_MSG(CPulseWidthMeasurementDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
   afx_msg void OnBnClickedButtonConfig();
   afx_msg void OnStop(); 
   afx_msg void OnStart();
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg LRESULT OnConfDevice(WPARAM w,LPARAM l);
   afx_msg LRESULT OnUpdateValue(WPARAM wParam, LPARAM lParam); 
   afx_msg LRESULT OnStoppedEvent(WPARAM wParam, LPARAM lParam); 
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
private:
   DevConfParam         m_confParam; // the device's configure information from config form.
   BufferedPwMeterCtrl* m_bfdPwMeterCtrl;
   CConfigurationDlg	   m_confDlg;

   CBrush	   m_bkBk;
   CListBox    m_counterValueList;

   CString     m_hiPeriod;
   CString     m_loPeriod;
   PulseWidth* m_dataBuf;

   PulseWidth** chs_dataBuf;

   int         m_eventChannel;
   int         m_displayChannel;

   int8*       m_channelEnable;
   int32       m_sectionLength;
   int         m_sectionCount;
   int32       m_samples;
   SignalDrop  m_sampleClkSrc;
   int32       m_channelCountMax;

   TriggerAction m_trgAction;
   SignalDrop    m_trgSource;
   ActiveSignal  m_trgEdge;
   double        m_trgLevel;

   CComboBox   m_cbx_eventChannel;
   CString     m_channelStatus;

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
};
