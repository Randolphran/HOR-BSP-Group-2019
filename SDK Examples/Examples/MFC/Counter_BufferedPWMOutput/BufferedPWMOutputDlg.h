// PwModulatorDlg.h : header file
//
#pragma once
#include "ConfigurationDlg.h"
#include "afxwin.h"
#include "PictureEx.h"

// CPWMOutputDlg dialog
class CBufferedPWMOutputDlg : public CDialog
{
// Construction
public:
	CBufferedPWMOutputDlg(CWnd* pParent = NULL);	// standard constructor
   ~CBufferedPWMOutputDlg();
   // this function is used to deal with Interrupt Event. 
   static void  BDAQCALL OnBfdCounterEvent(void * sender, BfdCntrEventArgs * args, void * userParam); 
// Dialog Data
	enum { IDD = IDD_PWMODULATOR_DIALOG };
// Implementation
protected:
	HICON m_hIcon;
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
   // Generated message map functions
   //{{AFX_MSG(CPWMOutputDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
   afx_msg HCURSOR OnQueryDragIcon();   
   afx_msg void OnBnClickedButtonConfig();
   afx_msg void OnStart();
   afx_msg void OnStop();
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg LRESULT  OnConfDevice(WPARAM w,LPARAM l);
   afx_msg LRESULT OnUpdateValue(WPARAM wParam, LPARAM lParam); 

   //}}AFX_MSG
   
private:
   CBrush		               m_bkBk;
   DevConfParam               m_confParam; // the device's configure information from config form.
   BufferedPwModulatorCtrl*   bfdPwModulatorCtrl;
   CConfigurationDlg	         m_confDlg;

   double         m_data1_HiPeriod;
   double         m_data1_LoPeriod;
   double         m_data2_HiPeriod;
   double         m_data2_LoPeriod;
   CPictureEx     m_executionStatus;
   
   int8*          m_channelEnable;
   int32          m_intervalCount;
   int32          m_samples;
   PulseWidth*    m_pulseWidth;

   TriggerAction m_trgAction;
   SignalDrop    m_trgSource;
   ActiveSignal  m_trgEdge;
   double        m_trgLevel;
   
   int32         m_channelCountMax;
   void ConfigurateDevice();
   void ConfiguratePanel();
   void CheckError(ErrorCode errorCode);
   ErrorCode SetPeriod(int cntr, double & hiPeriod, double & loPeriod);
	DECLARE_MESSAGE_MAP()

};
