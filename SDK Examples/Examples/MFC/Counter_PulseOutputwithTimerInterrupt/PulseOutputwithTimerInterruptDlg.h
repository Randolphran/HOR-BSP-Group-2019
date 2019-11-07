// TimerPulseDlg.h : header file
//

#pragma once
#include "ConfigurationDlg.h"
#include "afxwin.h"
#include "PictureEx.h"

// CPulseOutputwithTimerInterruptDlg dialog
class CPulseOutputwithTimerInterruptDlg : public CDialog
{
// Construction
public:
	CPulseOutputwithTimerInterruptDlg(CWnd* pParent = NULL);	// standard constructor
   ~CPulseOutputwithTimerInterruptDlg();

   static void BDAQCALL OnCounterEvent(void * sender, CntrEventArgs * args, void * userParam);
    
// Dialog Data
	enum { IDD = IDD_TIMERPULSE_DIALOG };
   
// Implementation
protected:
	HICON m_hIcon;
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
   // Generated message map functions
   //{{AFX_MSG(CPulseOutputwithTimerInterruptDlg)
   LRESULT OnConfDevice(WPARAM w,LPARAM l);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
   afx_msg HCURSOR OnQueryDragIcon();   
   afx_msg void OnBnClickedButtonConfig();
   afx_msg void OnStart();
   afx_msg void OnStop();
	afx_msg void OnClose();
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg LRESULT OnUpdateEventCount(WPARAM wParam, LPARAM lParam);
   //}}AFX_MSG

private:
   CBrush		         m_bkBk;
   DevConfParam         m_confParam; // the device's configure information from config form.
   TimerPulseCtrl*      m_timerPulseCtrl;
   CConfigurationDlg	   m_confDlg;

   double m_desiredFrequency;
   double m_generatedFrequency;
	int    m_eventCount;
   CPictureEx m_executionStatus;
   void ConfigurateDevice();
   void ConfiguratePanel();
   void CheckError(ErrorCode errorCode);
	DECLARE_MESSAGE_MAP()

};
