// StreamingAiDlg.h : header file
//

#pragma once
#include "ConfigurationDlg.h"
#include "../SimpleGraph.h"
//#define  INTERVALS 4
#define  USER_BUFFER_LENTH_MAX_PER_CHAN 8000000 //125000000 
// CStreamingAIDlg dialog
class CStreamingAIDlg : public CDialog
{
public:// Construction
   CStreamingAIDlg(CWnd* pParent = NULL);	// standard constructor
   // Dialog Data
   enum { IDD = IDD_STREAMINGAI_DIALOG };
protected:// Implementation
   HICON m_hIcon;
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
   // Generated message map functions
   virtual BOOL OnInitDialog();
   afx_msg void OnPaint();
   afx_msg HCURSOR  OnQueryDragIcon();
   afx_msg LRESULT  OnConfDevice(WPARAM wParam, LPARAM lParam);// user-defined ,for getting the configuration information.
   afx_msg void OnBnClickedButtonConfig();
   afx_msg void OnBnClickedButtonStart();
   afx_msg void OnBnClickedButtonPause();
   afx_msg void OnBnClickedButtonStop();
   afx_msg void OnClose();
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg void OnNMCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult);
   afx_msg void OnNMReleasedcaptureSliderTimediv(NMHDR *pNMHDR, LRESULT *pResult);
   DECLARE_MESSAGE_MAP()

private:
   DOUBLE*			     m_data;
   TimeUnit            m_timeUnit;
   CBrush	           m_bkBk;
	int32               m_sectionLength;
	int				     m_channelCount;

   CConfigurationDlg   m_confDlg;
   WaveformAiCtrl *    m_wfAiCtrl;
   DevConfParam        m_confParam;
   SimpleGraph         m_simpleGraph;

private:
   void ConfigurateDevice();
   void ConfigurateGraph();
   void InitListView();
   void CheckError(ErrorCode error);
public:
   static void BDAQCALL OnDataReadyEvent(void * sender, BfdAiEventArgs * args, void *userParam);
};
