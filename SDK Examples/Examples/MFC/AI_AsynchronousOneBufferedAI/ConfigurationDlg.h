#pragma once
#include "../SimpleGraph.h"
#include "../../../Inc/bdaqctrl.h"
using namespace Automation::BDaq;

#define BufferMaxSize           60 * 1000 * 1000

#define WM_CUSTOME_CFG_CHGED   (WM_USER + 0x1001)
// CConfiguration dialog
typedef struct tagDevConfParam 
{
	int			deviceNumber;					 
	int			channelCount;				
	int			channelStart;			
	int			vrgType;
	double      clockRatePerChan;
	int32       sectionLength;
	WCHAR       profilePath[256];
}DevConfParam;

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
    //{{AFX_MSG(CConfigurationDlg)
   virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboDevice();
	afx_msg void OnEnChangeEditDatacount();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

public:
   CComboBox m_comboBox_Device;
   CComboBox m_comboBox_ChannelStart;
   CComboBox m_comboBox_ChannelCount;
   CComboBox m_comboBox_ValueRange;

	double  m_clockRatePerChan;
	CString m_profilePath;
	int32   m_sectionLength;

   void CheckError(ErrorCode errorCode);
	afx_msg void OnBnClickedBrowse();
};
