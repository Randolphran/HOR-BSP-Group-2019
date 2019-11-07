// UpDownCounterDlg.h : header file
//

#pragma once
#include "ConfigurationDlg.h"
#include "afxwin.h"

// CUpDownCounterDlg dialog
class CUpDownCounterDlg : public CDialog
{
// Construction
public:
	CUpDownCounterDlg(CWnd* pParent = NULL);	// standard constructor
   ~CUpDownCounterDlg();

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
   afx_msg void OnValueReset();
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg void OnTimer(UINT_PTR nIDEvent);
   afx_msg void OnCbnSelchangeComboResetValue();
   afx_msg void OnResetIndexChged();
   DECLARE_MESSAGE_MAP()
private:
   DevConfParam       m_confParam; // the device's configure information from config form.
   UdCounterCtrl*     m_udCounterCtrl;
   CConfigurationDlg	 m_confDlg;

   CBrush	m_bkBk;
   CListBox m_counterValueList;
   CString   m_counterValue;
   CComboBox m_comboBox_resetValue;
   CEdit     m_resetValue;
   CEdit    m_resetTimes;

   void ConfigurateDevice();
   void ConfiguratePanel();
   void CheckError(ErrorCode errorCode);
};
