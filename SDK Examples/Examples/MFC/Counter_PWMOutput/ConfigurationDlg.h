#pragma once
#include "afxwin.h"
#include "../../../Inc/BDaqCtrl.h"
using namespace Automation::BDaq;
#define WM_CUSTOME_CFG_CHGED   (WM_USER + 0x1001) 
// CConfigForm dialog
typedef struct tagDevConfParam
{
   int  deviceNumber;
   long channel;
	WCHAR profilePath[256];
}DevConfParam, *PDevConfParam;

class CConfigurationDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigurationDlg)
public:
	CConfigurationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConfigurationDlg();
   
   DevConfParam GetParameter();
// Dialog Data
   enum { IDD = IDD_CONFIGURATION };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //{{AFX_MSG(CConfigForm)
   afx_msg void OnCbnSelchangeComboDevice();
   virtual BOOL OnInitDialog();
   virtual void OnBnClickedOk();
   afx_msg void OnBnClickedCancel();
   afx_msg void OnClose();
   //}}AFX_MSG
	
private:
   CComboBox m_comboBox_Device;
   CComboBox m_comboBox_counterChan;
   void CheckError(ErrorCode errorCode);
	CString m_profilePath;
   DECLARE_MESSAGE_MAP()   
public:
	afx_msg void OnBnClickedBrowse();
};
