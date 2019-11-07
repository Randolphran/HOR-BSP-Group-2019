// PwModulatorDlg.h : header file
//
#pragma once
#include "ConfigurationDlg.h"
#include "afxwin.h"
#include "PictureEx.h"

// CPWMOutputDlg dialog
class CPWMOutputDlg : public CDialog
{
// Construction
public:
	CPWMOutputDlg(CWnd* pParent = NULL);	// standard constructor
   ~CPWMOutputDlg();
    
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
   //}}AFX_MSG
   
private:
   CBrush		         m_bkBk;
   DevConfParam         m_confParam; // the device's configure information from config form.
   PwModulatorCtrl*     m_pwModulatorCtrl;
   CConfigurationDlg	   m_confDlg;

   double m_desiredHiPeriod;
   double m_desiredLoPeriod;
   double m_generatedHiPeriod;
   double m_generatedLoPeriod;
   CPictureEx m_executionStatus;

   void ConfigurateDevice();
   void ConfiguratePanel();
   void CheckError(ErrorCode errorCode);
   ErrorCode SetPeriod(int cntr, double & hiPeriod, double & loPeriod);
	DECLARE_MESSAGE_MAP()

};
