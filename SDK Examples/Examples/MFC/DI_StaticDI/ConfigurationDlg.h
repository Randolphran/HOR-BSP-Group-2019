// ConfigureForm.h : header file
//
#pragma once
#include "afxwin.h"
#include "../../../Inc/bdaqctrl.h"
using namespace Automation::BDaq;
#define WM_CUSTOME_CFG_CHGED   (WM_USER + 0x1001) 
// CConfigureForm dialog

typedef struct tagDevConfParam
{
	int      deviceNumber;
	WCHAR    profilePath[256];
}DevConfParam, *pDevConfParam;

class CConfigurationDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigurationDlg)
		
public:
	CConfigurationDlg(CWnd* pParent = NULL);   	// standard constructor
	virtual ~CConfigurationDlg();
   DevConfParam GetParameter();

	enum { IDD = IDD_CONFIGURATION };
   
protected:
	// Generated message map functions
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//{{AFX_MSG(CConfigureForm)
	virtual BOOL OnInitDialog();	
   afx_msg void OnBnClickedCancel();
	afx_msg void OnOk();
	afx_msg HCURSOR OnQueryDragIcon();
   afx_msg void OnClose();
	afx_msg void OnBnClickedBrowse();
	//}}AFX_MSG
	
private:
   CComboBox m_comboBox_Device;
	CString m_profilePath;
	DECLARE_MESSAGE_MAP()  
};

