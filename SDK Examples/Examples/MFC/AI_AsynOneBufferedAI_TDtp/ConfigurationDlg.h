#pragma once
#include "../SimpleGraph.h"
#include "../../../Inc/bdaqctrl.h"
using namespace Automation::BDaq;


#define WM_CUSTOME_CFG_CHGED   (WM_USER + 0x1001) 

#define BufferMaxSize           60 * 1000 * 1000

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

	// for trigger
   int triggerIndex;
	double delayCount;
	double triggerLevel;
	SignalDrop triggerSource;
	ActiveSignal triggerEdge;
	TriggerAction triggerAction;
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
	// for trigger
   afx_msg void OnCbnSelchangeComboTriggerIndex();
	afx_msg void OnEnChangeEditTriggerDelayCount();
	afx_msg void OnEnChangeEditTriggerLevel();
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

	// parameters for trigger
   CComboBox m_comboBox_trigger_index;
	CComboBox m_comboBox_source;
	CComboBox m_comboBox_edge;

	double m_triggerDelayCount;
	double m_triggerLevel;

   void CheckError(ErrorCode errorCode);
	afx_msg void OnCbnSelchangeComboSource();
	afx_msg void OnBnClickedBrowse();
};
