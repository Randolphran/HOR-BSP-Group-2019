// ContinueCompareDlg.h : header file
//

#pragma once
#include "ConfigurationDlg.h"
#include "afxwin.h"

// CContinueCompareDlg dialog
class CContinueCompareDlg : public CDialog
{
// Construction
public:
	CContinueCompareDlg(CWnd* pParent = NULL);
  // standard constructor
   ~CContinueCompareDlg();

   static void BDAQCALL OnUdCounterEvent(void * sender, UdCntrEventArgs * args, void * userParam);
// Dialog Data
	enum { IDD = IDD_ContinueCompare_DIALOG };
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
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg void OnTimer(UINT_PTR nIDEvent);
   afx_msg LRESULT OnUpdateContComp(WPARAM wParam, LPARAM lParam); 
   DECLARE_MESSAGE_MAP()
private:
   DevConfParam       m_confParam; // the device's configure information from config form.
   UdCounterCtrl*     m_udCounterCtrl;
   CConfigurationDlg	 m_confDlg;

   CBrush	m_bkBk;
   CString   m_counterValue;
   BOOL isFirst;
   ULONG m_matchCount;
   ULONG m_endCount;
   void ConfigurateDevice();
   void CheckError(ErrorCode errorCode);
   void EnableCompareTable(BOOL enabled);

public:
   ULONG m_tab1CompData0;
   ULONG m_tab1CompData1;
   ULONG m_tab1CompData2;
   ULONG m_tab2CompData0;
   ULONG m_tab2CompData1;
   ULONG m_tab2CompData2;

   ULONG m_intrvl1FirVal;
   LONG m_intrvl1Cremt;
   ULONG m_intrl1Count;
   ULONG m_intrvl2FirVal;
   LONG m_intrvl2Cremt;
   ULONG m_intrl2Count;

   int  m_tabIndex;
   TabSel m_contCompTabSel;
   void CreateDisperseTable(int tabIndex,int CompTab[]);
   void CreateLineTable(int tabIndex,LineTabParam & param);
};
