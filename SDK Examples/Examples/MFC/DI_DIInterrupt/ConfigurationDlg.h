// ConfigureForm.cpp : 
//
#pragma once
#include "afxwin.h"
#include "../../../Inc/bdaqctrl.h"
using namespace Automation::BDaq;
#define WM_CUSTOME_CFG_CHGED   (WM_USER + 0x1001) 
#define WM_UPDATELIST           (WM_USER + 0x1002)

typedef struct tagDevConfParam
{
	int    deviceNumber;
   int    diEnableChannel[16];
	int    enabledCount;
	WCHAR  profilePath[256];
}DevConfParam, *pDevConfParam;

// CConfigureForm dialog
class CConfigurationDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigurationDlg)
		
public:
	CConfigurationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConfigurationDlg();	
   DevConfParam GetParameter();
	ErrorCode SetINTStatus(InstantDiCtrl * instantDiCtrl);
	void CheckError(ErrorCode errorCode);
	void CallConfigTool(TCHAR* deviceNumber);

	// Dialog Data
	enum { IDD = IDD_CONFIGURATION};
	CComboBox m_comboBox_Device;	
	CComboBox m_comboBox_Port; 
	CScrollBar m_scrollBar;
	int m_deviceCount;
	int m_picBoxStatus[32];   
	int m_enabledCount;
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	HICON m_hIcon;	
	int m_portNum0;
	// Generated message map functions
	//{{AFX_MSG(CConfigureForm)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnOk();
	afx_msg void OnCbnSelchangeComboDevice();
	afx_msg void OnClick(UINT nID);
   afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
   afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBrowse();
	//}}AFX_MSG
   DECLARE_MESSAGE_MAP()

private:
	int m_portNumList[256];
	int m_enabledChannel[16];
   int m_portsID[4][11];
	int m_imageList[3];  
	byte *m_diIntChannl; 
	int m_portCount;
	int m_diINTPortCount;
	CString m_profilePath;
   void SetAllPorts(bool state);
	void showPicture(int nID, int imageNum);
   void ShowPort(int *pPort);
   void InitScrollBar(int portCount);
	void refreshButton(int iNewPos);
	void configEnableButton();	
};

