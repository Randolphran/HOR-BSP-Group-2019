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
	int			cycles;
	CString	   deviceDescription;
	WCHAR       profilePath[256];

	// for trigger
	int delayCount;
	double triggerLevel;
	SignalDrop triggerSource;
	ActiveSignal triggerEdge;
	TriggerAction triggerAction;
   // for trigger1
   int delayCount1;
   double trigger1Level;
   SignalDrop trigger1Source;
   ActiveSignal trigger1Edge;
   TriggerAction trigger1Action;
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
	// for trigger
	afx_msg void OnEnChangeEditTriggerDelayCount();
	afx_msg void OnEnChangeEditTriggerLevel();

public:
   CComboBox m_comboBox_Device;
   CComboBox m_comboBox_ChannelStart;
   CComboBox m_comboBox_ChannelCount;
   CComboBox m_comboBox_ValueRange;

   double m_clockRatePerChan;
	int32 m_sectionLength;
	int m_sectionCount;
	int m_cycles;
	CString m_profilePath;
   // show the error code if Some errors happened
   void CheckError(ErrorCode errorCode);
   DECLARE_MESSAGE_MAP()

	// parameters for trigger
	CComboBox m_comboBox_source;
	CComboBox m_comboBox_edge;
	int m_triggerDelayCount;
	double m_triggerLevel;

   // parameters for trigger1
   CComboBox m_comboBox_source1;
   CComboBox m_comboBox_edge1;
   int m_trigger1DelayCount;
   double m_trigger1Level;

	afx_msg void OnCbnSelchangeComboSource();
	afx_msg void OnEnChangeEditSectionlength();
	afx_msg void OnEnChangeEditSectioncount();
	afx_msg void OnEnChangeEditCycles();
	afx_msg void OnBnClickedBrowse();
};
