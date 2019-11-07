// Instant DoDlg.h : header file
//

#pragma once
#include "ConfigurationDlg.h"
#include "afxwin.h"

// CStaticDODlg dialog
class CStaticDODlg : public CDialog
{
	// Construction
public:
	CStaticDODlg(CWnd* pParent = NULL);	// standard constructor
	~CStaticDODlg();

	// Dialog Data
	enum { IDD = IDD_INSTANTDO_DIALOG };
	
	// Implementation
protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	// Generated message map functions
	//{{AFX_MSG(CStaticDODlg)
   LRESULT OnConfDevice(WPARAM w,LPARAM l);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnClick(UINT nID);
	afx_msg void OnBnClickedConfig();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
private:
	InstantDoCtrl *      m_instantDoCtrl;
	DevConfParam         m_confParam; // the device's configure information from config form.
	CConfigurationDlg	   m_confDlg;

	int m_portNum0;
	int m_ports[8][12];
	int m_imageList[3]; 
   int m_picBoxStatus[64]; 
	CScrollBar m_scrollBar;	
	void ConfigureDevice();
   void ConfigurePanel();
   void CheckError(ErrorCode errorCode);
	void SetAllPorts(bool state);
	void InitPorts();
	void refreshButton(int iNewPos);
	void showPicture(int nID, int imageNum); 
	byte drawButton(int i, int j, ErrorCode ret, int  portNumber,byte * portValue);	
	DECLARE_MESSAGE_MAP()
};

