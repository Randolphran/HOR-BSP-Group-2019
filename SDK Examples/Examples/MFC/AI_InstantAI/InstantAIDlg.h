// InstantAiDlg.h : header file
//

#pragma once

#include "ConfigurationDlg.h"
#include "../SimpleGraph.h"

// CInstantAIDlg dialog
class CInstantAIDlg : public CDialog
{
// Construction
public:
	CInstantAIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_INSTANTAI_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	HICON m_hIcon;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
   afx_msg LRESULT  OnConfDevice(WPARAM w,LPARAM l);// user-defined ,for getting the configuration information.
   afx_msg void OnTimer(UINT_PTR nIDEvent);
   afx_msg void OnNMCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult);
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg void OnNMReleasedcaptureSliderTimerinterval(NMHDR *pNMHDR, LRESULT *pResult);
   afx_msg void OnBnClickedButtonStart();
   afx_msg void OnBnClickedButtonPause();
   afx_msg void OnBnClickedButtonStop();
   afx_msg void OnBnClickedButtonConfig();
   afx_msg void OnClose();
   DECLARE_MESSAGE_MAP()
	
private:// user define
   CBrush			m_bkBk;

	SimpleGraph         m_simpleGraph;
   CConfigurationDlg   m_confDlg;
   InstantAiCtrl *     m_instantAiCtrl;
   DevConfParam        m_confParam;

   void ConfigurateDevice();
   void ConfigurateGraph();
   void InitListView();
   void RefreshListView(DOUBLE data[]);
   void CheckError(ErrorCode error);
	
};
