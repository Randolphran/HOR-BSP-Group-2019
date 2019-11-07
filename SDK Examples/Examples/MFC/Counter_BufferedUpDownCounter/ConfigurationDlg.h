#pragma once
#include "afxwin.h"
#include "../../../Inc/bdaqctrl.h"

using namespace Automation::BDaq;
#define WM_CUSTOME_CFG_CHGED   (WM_USER + 0x1001) 
#define WM_UPDATEVALUE         (WM_USER + 0x1002)
#define WM_STOPEVENT           (WM_USER + 0x1003)
// CConfigForm dialog

typedef struct tagDevConfParam
{
   int                deviceNumber;
   WCHAR              profilePath[256];
   // General Settings
   int8*              channelEnable;
   int32              sectionLength;
   int                sectionCount;
   SignalDrop         clkSrc;
   SignalCountingType cntType;

   //Trigger Settings
   SignalDrop         trgSrc;
   ActiveSignal       trgEdge;
   TriggerAction      trgAct;
   double             trgLevel;
   bool               configureMode;
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

public:
   CComboBox m_cbx_device;
   CString   m_profilePath;
   int32     m_sectionLength;
   int       m_sectionCount;
   CComboBox m_cbx_clkSrc;
   CComboBox m_cbx_countingType;

   CComboBox m_cbx_trgSrc;
   CComboBox m_cbx_trgAct;
   CComboBox m_cbx_trgEdge;
   double    m_trgLevel;
   int8*     m_channelEnable;
   bool      m_configureMode;
   int32     m_channelCountMax;
   void CheckError(ErrorCode errorCode);
   DECLARE_MESSAGE_MAP()
   afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedBrowse();
   afx_msg void OnCbnSelchangeCbxTrgsrc();
   afx_msg void OnBnClickedChk(UINT nID);
   afx_msg void OnBnClickedRadio();
   void ComponentEnabled(bool flag);
   void InitialChkBox();
};
