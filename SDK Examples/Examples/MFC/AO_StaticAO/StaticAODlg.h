// InstantAoDlg.h : header file
//
#pragma once
#include "ConfigurationDlg.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "../WaveformGenerator.h"

#define CHANNEL_COUNT      2
#define WAVE_STYLE_COUNT   3
#define WAVE_BTN_COUNT     CHANNEL_COUNT * WAVE_STYLE_COUNT

// CStaticAODlg dialog
class CStaticAODlg : public CDialog
{
// Construction
public:
   CStaticAODlg(CWnd* pParent = NULL);	// standard constructor
   virtual ~CStaticAODlg();
// Dialog Data
	enum { IDD = IDD_INSTANTAO_DIALOG };
   
// Implementation
protected:
	HICON m_hIcon;
   
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
   //{{AFX_MSG(CStaticAODlg)
   virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg LRESULT  OnConfDevice(WPARAM w,LPARAM l);// user-defined ,for getting the configuration information.
   afx_msg void OnTimer(UINT_PTR nIDEvent);
   afx_msg void OnCheckBoxClicked(UINT nID);   
   afx_msg void OnManualAClick();
   afx_msg void OnManualBClick();
   afx_msg void OnBnClickedButtonConfig();
   afx_msg void OnNMReleasedcaptureSlider(NMHDR *pNMHDR, LRESULT *pResult);
   //}}AFX_MSG

private:
   // the device's configure information from config form.
   CBrush		       m_bkBk;
   InstantAoCtrl *    m_instantAoCtrl;
   DevConfParam       m_confParam;  
   CConfigurationDlg	 m_confDlg;

   CButton           *m_waveSelectButton[WAVE_BTN_COUNT];
   HBITMAP            m_waveformStyleBmp[CHANNEL_COUNT][WAVE_STYLE_COUNT];
   double            *m_dataScaled; 
   WaveformGenerator *m_waveformGenerator;
   
   // whether the waveform style button is checked.
   BOOL               m_isCheckedA;
   BOOL               m_isCheckedB;
   
   // WaveformGenerator's GetOnePoint function's parameters.
   WaveformStyle      m_formStyleA;
   WaveformStyle      m_formStyleB;
   double             m_highLevelA;
   double             m_lowLevelA;
   double             m_highLevelB;
   double             m_lowLevelB;
   double             m_valueA;
   double             m_valueB;
   int                m_wavePointsIndexA;
   int                m_wavePointsIndexB;

   CSliderCtrl m_trackTimerInterval;

   void ConfigurateDevice();
   void ConfiguratePanel();
   void CheckError(ErrorCode errorCode);
   DECLARE_MESSAGE_MAP()   
};
