// OneShotAsyncbufferedAiDlg.h : header file
//
#pragma once
#include "ConfigurationDlg.h"
#include "../SimpleGraph.h"

class CAsynchronousOneBufferedAIDlg : public CDialog
{
public:
	CAsynchronousOneBufferedAIDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	enum { IDD = IDD_ONESHOTASYNCBUFFEREDAI_DIALOG };
  
// Implementation
protected:
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
   virtual BOOL OnInitDialog();
   afx_msg void OnNMCustomDrawList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedCaptureSliderTimeShift(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderTimediv(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonCondig();
	afx_msg void OnBnClickedButtonGetdata();
	afx_msg void OnBnClickedButtonConfig();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
   afx_msg void OnPaint();
   afx_msg HCURSOR OnQueryDragIcon();
   afx_msg LRESULT OnConfDevice(WPARAM wParam, LPARAM lParam);// user-defined ,for getting the configuration information.
   afx_msg LRESULT OnAiStop(WPARAM wParam, LPARAM lParam);

   DECLARE_MESSAGE_MAP()

private:
   HICON       m_hIcon;
   CBrush	   m_bkBk;
   DOUBLE*		m_data;
   int         m_shiftEdit;
   int         m_divEdit;
   TimeUnit    m_timeUnit;

   CConfigurationDlg   m_confDlg;
   DevConfParam        m_confParam;
   WaveformAiCtrl *    m_wfAiCtrl;
   SimpleGraph         m_simpleGraph;
public:
   void ConfigurateDevice();
   void ConfigurateGraph();
   void InitListView();
   void CheckError(ErrorCode error);
   static void BDAQCALL OnStoppedEvent(void * sender, BfdAiEventArgs * args, void * userParam);
};

