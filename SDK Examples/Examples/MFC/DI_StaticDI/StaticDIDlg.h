// DI_InstantDlg.h : header file
//

#pragma once
#include "ConfigurationDlg.h"
#include "afxwin.h"

// CStaticDIDlg dialog
class CStaticDIDlg : public CDialog
{
	// Construction
public:
	CStaticDIDlg(CWnd* pParent = NULL);	// standard constructor
	~CStaticDIDlg();

	enum { IDD = IDD_INSTANTDI_DIALOG };
	
	// Implementation
protected:
   HICON m_hIcon;  
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	 
	// Generated message map functions
	//{{AFX_MSG(CStaticDIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();   
	afx_msg void OnBnClickedConfig();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   LRESULT OnConfDevice(WPARAM w,LPARAM l);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
   InstantDiCtrl *      m_instantDiCtrl;
   DevConfParam         m_confParam; // the device's configure information from config form.
   CConfigurationDlg	   m_confDlg;

   int m_portNum0;
	byte* m_portData;
	int m_portCount;
	int m_ports[8][12];
	int m_imageList[2];   
   CScrollBar m_scrollBar;

	void SetAllPorts(bool state);
	void ShowPort(int *pPort);
	void InitPorts();
	void refreshLed(int iNewPos);
   void ConfigureDevice();
   void ConfiguratePanel();
   void CheckError(ErrorCode errorCode);
};


