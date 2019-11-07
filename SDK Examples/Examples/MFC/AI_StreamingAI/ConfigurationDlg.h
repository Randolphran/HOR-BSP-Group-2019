#pragma once
#include "../SimpleGraph.h"
#include "../../../Inc/bdaqctrl.h"
using namespace Automation::BDaq;

#define WM_CUSTOME_CFG_CHGED   (WM_USER + 0x1001)

typedef struct DiveceConfigueInfomation 
{
	int			deviceNumber;					 
	int			channelCount;				
	int			channelStart;			
	int			vrgType;
	double      clockRatePerChan;
	int32			sectionLength;
	WCHAR       profilePath[256];
}DevConfParam;
// CConfiguration dialog

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
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboDevice();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
	afx_msg void OnEnChangeEditClockrateperchan();
	afx_msg void OnBnClickedBrowse();

public:
   CComboBox m_comboBox_Device;
   CComboBox m_comboBox_ChannelStart;
   CComboBox m_comboBox_ChannelCount;
   CComboBox m_comboBox_ValueRange;

   double m_clockRatePerChan;
	int32 m_sectionLength;
	CString m_profilePath;
   // show the error code if Some errors happened
   void CheckError(ErrorCode errorCode);
   DECLARE_MESSAGE_MAP()
};
