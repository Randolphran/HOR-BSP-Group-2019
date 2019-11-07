#pragma once
#include "afxwin.h"
#include "../../../Inc/BDaqCtrl.h"
using namespace Automation::BDaq;
#define WM_CUSTOME_CFG_CHGED   (WM_USER + 0x1001) 
#define WM_UPDATSNAPCOUNT           (WM_USER + 0x1002)
// CConfigForm dialog

typedef struct tagDevConfParam
{
   int deviceNumber;
   long channel;
   SignalCountingType cntType;
	WCHAR profilePath[256];
}DevConfParam, *PDevConfParam;

class CConfigurationDlg : public CDialog
{
   DECLARE_DYNAMIC(CConfigurationDlg)

public:
   CConfigurationDlg(CWnd* pParent = NULL);   // standard constructor
   ~CConfigurationDlg();

   DevConfParam GetParameter();
   // Dialog Data
   enum { IDD = IDD_CONFIGURATION };

protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //{{AFX_MSG(CConfigForm)
   afx_msg void OnCbnSelchangeComboDevice();
   virtual BOOL OnInitDialog();
   virtual void OnBnClickedOk();
   afx_msg void OnClose();
   //}}AFX_MSG

private:
   CComboBox m_comboBox_Device;
   CComboBox m_comboBox_counterChan;
   CComboBox m_comboBox_countingType;
	CString   m_profilePath;
   void CheckError(ErrorCode errorCode);
   DECLARE_MESSAGE_MAP()
   afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedBrowse();
};
