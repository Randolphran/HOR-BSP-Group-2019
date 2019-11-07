#pragma once
#include "../SimpleGraph.h"
#include "../../../Inc/bdaqctrl.h"
using namespace Automation::BDaq;

#define BufferMaxSize          60 * 1000 * 1000
#define WM_CUSTOME_CFG_CHGED   (WM_USER + 0x1001) 

// CConfiguration dialog
typedef struct DiveceConfigueInfomation 
{
	int			deviceNumber;					 
	int			channelCount;				
	int			channelStart;			
	int			vrgType;
	WCHAR 		profilePath[256];
	int32       sectionLength;
	double      clockRatePerChan;
	int			moduleIndex;
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
	
	afx_msg void OnCbnSelchangeComboDevice();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEditDatacountperchan();
	afx_msg void OnEnChangeEditClockrateperchan();
	afx_msg void OnCbnSelchangeComboChancount();
	afx_msg void OnClose();
   virtual BOOL OnInitDialog();

public:
   CComboBox m_comboBox_Device;
   CComboBox m_comboBox_ChannelStart;
   CComboBox m_comboBox_ChannelCount;
   CComboBox m_comboBox_ValueRange;

   double  m_clockRatePerChan;
	int32   m_sectionLength;
   double  m_totalTime;
	CString m_profilePath;
   void CheckError(ErrorCode errorCode);
   DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedBrowse();
};
