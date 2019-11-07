// EventCountingDlg.h : header file
//

#pragma once
#include "ConfigurationDlg.h"
#include "afxwin.h"

// CEventCounterDlg dialog
class CEventCounterDlg : public CDialog
{
// Construction
public:
	CEventCounterDlg(CWnd* pParent = NULL);	// standard constructor
   ~CEventCounterDlg();

// Dialog Data
	enum { IDD = IDD_EVENTCOUNTING_DIALOG };
// Implementation
protected:
	HICON m_hIcon;
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
   // Generated message map functions
   //{{AFX_MSG(CEventCounterDlg)
	virtual BOOL OnInitDialog();
   afx_msg LRESULT  OnConfDevice(WPARAM w,LPARAM l);// user-defined ,for getting the configuration information.
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
   afx_msg void OnBnClickedButtonConfig();
   afx_msg void OnStop(); 
   afx_msg void OnStart();
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg void OnTimer(UINT_PTR nIDEvent);
   //}}AFX_MSG
private:
   DevConfParam       m_confParam; // the device's configure information from config form.
   EventCounterCtrl*  m_eventCounterCtrl;
   CConfigurationDlg	 m_confDlg;

   CBrush	m_bkBk;
   CListBox m_counterValueList;
   CString  m_counterValue;

   void ConfigurateDevice();
   void ConfiguratePanel();
   void CheckError(ErrorCode errorCode);
	DECLARE_MESSAGE_MAP()
};
