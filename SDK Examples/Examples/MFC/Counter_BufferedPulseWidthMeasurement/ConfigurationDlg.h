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
   int            deviceNumber;
	WCHAR          profilePath[256];
   // General Settings
   int8*          channelEnable;
   int32          sectionLength;
   int            sectionCount;
   SignalDrop     clkSource;
   //for trigger parameters
   double         trgLevel;
   SignalDrop     trgSource;
   ActiveSignal   trgEdge;
   TriggerAction  trgAction;
   bool           configureMode;
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
   afx_msg void OnBnClickedCancel();
   afx_msg void OnClose();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   void CheckError(ErrorCode errorCode);

   public:
   CComboBox m_cbx_device;
   CString   m_profilePath;
   CComboBox m_cbx_clkSrc;
   int       m_sectionCount;
   int       m_sectionLength;
   CComboBox m_cbx_trgSrc;
   CComboBox m_cbx_trgAct;
   CComboBox m_cbx_trgEdge;
   double    m_trgLevel;
   int8*     m_channelEnable;
   bool      m_configureMode;
	int32     m_channelCountMax;
public:
	afx_msg void OnBnClickedButtonBrowse();
   afx_msg void OnCbnSelchangeCbxTrgsrc();
   afx_msg void OnBnClickedChk(UINT nID);
   afx_msg void OnBnClickedRadio();
   void ComponentEnabled(bool flag);
   void InitialChkBox();
};
