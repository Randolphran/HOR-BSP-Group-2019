
// ConfigureForm.h : header file
//
#pragma once
#include "afxwin.h"
#include "../../../Inc/bdaqctrl.h"
using namespace Automation::BDaq;
#define WM_CUSTOME_CFG_CHGED   (WM_USER + 0x1001) 
#define WM_UPDATELIST          (WM_USER + 0x1002)
// CConfigureForm dialog

typedef struct tagDevConfParam
{
   int  deviceNumber;
   int  selectedPort;
   byte enabledChannels;
	WCHAR profilePath[256];
}DevConfParam, *pDevConfParam;

class CConfigurationDlg : public CDialog
{
   DECLARE_DYNAMIC(CConfigurationDlg)
		
public:
   CConfigurationDlg(CWnd* pParent = NULL);  
   virtual ~CConfigurationDlg();

   DevConfParam GetParameter();
//dialog data	
   enum { IDD = IDD_CONFIGURATION };

protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	// Generated message map functions
	//{{AFX_MSG(CConfigureForm)
   virtual BOOL OnInitDialog();
   afx_msg void OnOk();
   afx_msg void OnCbnSelchangeComboDevice();
   afx_msg void OnSelchangePort();
   afx_msg void OnClick();
   afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBrowse();
	//}}AFX_MSG

private:
   void CheckError(ErrorCode errorCode);
	void CallConfigTool(TCHAR* deviceNumber);

private:
   int m_imageList[2];  
   int m_portStatus[8];
   byte m_enableData;
	CString m_profilePath;
   CComboBox m_comboBox_Device;	
   CComboBox m_comboBox_Port;  
   DECLARE_MESSAGE_MAP()		
};