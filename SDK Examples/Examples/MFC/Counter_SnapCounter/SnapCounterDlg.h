// SnapCounterDlg.h : header file
//

#pragma once
#include "ConfigurationDlg.h"
#include "afxwin.h"

// CSnapCounterDlg dialog
class CSnapCounterDlg : public CDialog
{ 
   // Construction
public:
   CSnapCounterDlg(CWnd* pParent = NULL);	// standard constructor
   ~CSnapCounterDlg();

   static void BDAQCALL OnUdCounterEvent(void * sender, UdCntrEventArgs * args, void * userParam);

   // Dialog Data
   enum { IDD = IDD_SNAPCOUNTER_DIALOG };
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
   afx_msg void OnSnapSrcSelChanged();
   afx_msg void OnStop(); 
   afx_msg void OnStart();
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg void OnTimer(UINT_PTR nIDEvent);
   afx_msg void OnResetIndexChged();
   afx_msg LRESULT OnUpdateSnapCount(WPARAM wParam, LPARAM lParam); 
   DECLARE_MESSAGE_MAP()
private:
   DevConfParam       m_confParam; // the device's configure information from config form.
   UdCounterCtrl*     m_udCounterCtrl;
   TimerPulseCtrl *   m_timerPulseCtrl;
   BOOL               m_isTimerUsing;
   CConfigurationDlg	 m_confDlg;

   CBrush	 m_bkBk;
   CListBox  m_counterValueList;
   CListBox  m_snapSourceList;
   CString   m_counterValue;
   CString   m_snapCount;
   //double    m_timeInterval;
	int       m_eventCount;   
   CArray<int,int> aryListBoxSrcSel;

   void ConfigurateDevice();
   void ConfiguratePanel();
   void CheckError(ErrorCode errorCode);
   void EventIDtoString(EventId id,CString &str);
   void CheckTimerUsingParam(EventId id,int & timerChan,BOOL & isTimerUsing);
};
