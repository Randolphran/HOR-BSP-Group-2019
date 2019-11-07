// OneShotSyncbufferedAiDlg.h : header file
//
#pragma once
#include "ConfigurationDlg.h"
#include "../SimpleGraph.h"
// CSynchonousOneBufferedAIDlg dialog
class CSynchonousOneBufferedAIDlg : public CDialog
{
// Construction
public:
	CSynchonousOneBufferedAIDlg(CWnd* pParent = NULL);	// standard constructor
   virtual ~CSynchonousOneBufferedAIDlg();
// Dialog Data
	enum { IDD = IDD_ONESHOTSYNCBUFFEREDAI_DIALOG };

// Implementation
protected:
	HICON m_hIcon;
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg void OnBnClickedButtonConfig();
   afx_msg void OnBnClickedButtonGetdata();
   afx_msg void OnNMCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult);
   afx_msg void OnNMReleasedcaptureSliderTimeshift(NMHDR *pNMHDR, LRESULT *pResult);
   afx_msg void OnNMReleasedcaptureSliderTimediv(NMHDR *pNMHDR, LRESULT *pResult);
   afx_msg LRESULT OnConfDevice(WPARAM wParam, LPARAM lParam);// user-defined ,for getting the configuration information.
   afx_msg void OnClose();

private:// user define
   CConfigurationDlg   m_confDlg;
   DevConfParam        m_confParam;
   WaveformAiCtrl *    m_wfAiCtrl;
   SimpleGraph         m_simpleGraph;
   DOUBLE*			     m_data;
   CBrush		        m_bkBk;
	int                 m_shiftEdit;
	int                 m_divEdit;
	TimeUnit            m_timeUnit;

   void ConfigurateDevice();
   void ConfigurateGraph();
   void InitListView();
   void CheckError(ErrorCode error);

	DECLARE_MESSAGE_MAP()
};
