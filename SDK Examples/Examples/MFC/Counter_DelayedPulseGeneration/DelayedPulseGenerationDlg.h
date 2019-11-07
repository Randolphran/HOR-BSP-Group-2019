// OneShotDlg.h : header file
//

#pragma once
#include "ConfigurationDlg.h"
#include "afxwin.h"

// CDelayedPulseGenerationDlg dialog
class CDelayedPulseGenerationDlg : public CDialog
{
// Construction
public:
	CDelayedPulseGenerationDlg(CWnd* pParent = NULL);	// standard constructor
   ~CDelayedPulseGenerationDlg();

   static void BDAQCALL OnCounterEvent(void * sender, CntrEventArgs * args, void * userParam);
   
// Dialog Data
   enum { IDD = IDD_ONESHOT_DIALOG };
// Implementation
protected:
	HICON m_hIcon;
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
   // Generated message map functions
   //{{AFX_MSG(CDelayedPulseGenerationDlg)
   afx_msg LRESULT  OnConfDevice(WPARAM w,LPARAM l);
   afx_msg LRESULT OnUpdateEventCount(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg void OnBnClickedButtonConfig();
   afx_msg void OnStart();
   afx_msg void OnStop();
   //}}AFX_MSG
private:
   CBrush		         m_bkBk;
   DevConfParam         m_confParam; // the device's configure information from config form.
   OneShotCtrl*         m_oneShotCtrl;
   CConfigurationDlg	   m_confDlg;
	int                  m_eventCount;  

   long m_clockCount;
   void ConfigurateDevice();
   void ConfiguratePanel();
   void CheckError(ErrorCode errorCode);
   DECLARE_MESSAGE_MAP()
};
