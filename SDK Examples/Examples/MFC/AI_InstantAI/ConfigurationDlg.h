#pragma once
#include "../SimpleGraph.h"
#include "../../../Inc/bdaqctrl.h"
using namespace Automation::BDaq;

#define WM_CUSTOME_CFG_CHGED   (WM_USER + 0x1001) 

// CConfigDlg 
typedef struct tagConfigParam{
	int			deviceNumber;					 
	int			channelCount;				
	int			channelStart;			
	int			vrgType;
	WCHAR 		profilePath[256];
}DevConfParam;

// CConfiguration dialog

class CConfigurationDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigurationDlg)
public:
	CConfigurationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConfigurationDlg();
// Dialog Data
	enum { IDD = IDD_CONFIGURATION };
   DevConfParam GetParameter();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //{{AFX_MSG(CConfigurationDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnCbnSelchangeComboDevice();
   afx_msg void OnBnClickedOk();
   afx_msg void OnBnClickedCancel();
   afx_msg void OnClose();
	afx_msg void OnBnClickedBrowse();

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
public:
   CComboBox m_comboBox_Device;
   CComboBox m_comboBox_ChannelStart;
   CComboBox m_comboBox_ChannelCount;
   CComboBox m_comboBox_ValueRange;
	CString   m_profilePath;
   void CheckError(ErrorCode errorCode);
};
