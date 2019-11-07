// PwMeterDlg.h : header file
//

#pragma once
#include "ConfigurationDlg.h"
#include "afxwin.h"

// CPulseWidthMeasurementDlg dialog
class CPulseWidthMeasurementDlg : public CDialog
{
// Construction
public:
	CPulseWidthMeasurementDlg(CWnd* pParent = NULL);	// standard constructor
   ~CPulseWidthMeasurementDlg();

// Dialog Data
	enum { IDD = IDD_PWMETER_DIALOG };

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
   afx_msg void OnTimer(UINT_PTR nIDEvent);
   afx_msg LRESULT  OnConfDevice(WPARAM w,LPARAM l);
   //}}AFX_MSG
private:
   DevConfParam         m_confParam; // the device's configure information from config form.
   PwMeterCtrl *        m_PwMeterCtrl;
   CConfigurationDlg	   m_confDlg;

   CBrush	m_bkBk;
   CListBox m_counterValueList;
   CString  m_hiPeriod;
   CString  m_loPeriod;
   void ConfigurateDevice();
   void ConfiguratePanel();
   void CheckError(ErrorCode errorCode);
   
	DECLARE_MESSAGE_MAP()
};
