// FrequencyMeasurementDlg.h : header file
//

#pragma once
#include "stdafx.h"
#include "ConfigurationDlg.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "../SimpleGraph.h"

struct RangeYType{
   MathInterval rangeY;
   FrequencyUnit unit;
};

// CCFrequencyMeasurementDlg dialog
class CCFrequencyMeasurementDlg : public CDialog
{
// Construction
public:
	CCFrequencyMeasurementDlg(CWnd* pParent = NULL);	// standard constructor
   ~CCFrequencyMeasurementDlg();
// Dialog Data
	enum { IDD = IDD_FREQUENCYMEASUREMENT_DIALOG };
// Implementation
protected:
	HICON m_hIcon;
   void SetYCord(int index);
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
   // Generated message map functions
   //{{AFX_MSG(CCFrequencyMeasurementDlg)
   afx_msg LRESULT  OnConfDevice(WPARAM w,LPARAM l);// user-defined ,for getting the configuration information.
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
   afx_msg HCURSOR OnQueryDragIcon(); 
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg void OnTimer(UINT_PTR nIDEvent);
   afx_msg void OnStart();
   afx_msg void OnPause();
   afx_msg void OnStop();
   afx_msg void OnBnClickedButtonConfig();
   afx_msg void OnLarger();
   afx_msg void OnSmaller();
   afx_msg void OnNMReleasedcaptureDataSpeed(NMHDR *pNMHDR, LRESULT *pResult);
   //}}AFX_MSG

private:
   CConfigurationDlg	    m_confDlg;
   DevConfParam          m_confParam; // the device's configure information from config form.
   FreqMeterCtrl*        m_freqMeterCtrl;

   CBrush		          m_bkBk;
   vector <RangeYType>   m_rangeYTypeList;
   MathInterval          m_rangeX;
   int                   m_index;               // the index of using RangeYType in m_rangeYTypeList vector. 
   int                   m_timerInterval;

   SimpleGraph m_simpleGraph;
   CSliderCtrl m_trackTimerInterval;

   void ConfigurateDevice();
   void ConfiguratePanel();
   void CheckError(ErrorCode errorCode);
   void InitRangeYTypeList();

   DECLARE_MESSAGE_MAP()
};
