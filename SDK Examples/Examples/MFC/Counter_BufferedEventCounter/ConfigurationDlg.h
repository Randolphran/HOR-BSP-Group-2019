#pragma once
#include "afxwin.h"
#include "../../../Inc/BDaqCtrl.h"
using namespace Automation::BDaq;
#define WM_CUSTOME_CFG_CHGED   (WM_USER + 0x1001)
#define WM_UPDATEVALUE         (WM_USER + 0x1002)
#define WM_STOPEVENT           (WM_USER + 0x1003)
// CConfigForm dialog

typedef struct tagDevConfParam
{
   int           deviceNumber;
	WCHAR         profilePath[256];
   int8*         channelEnable;
   int32         sectionLength;
   int           sectionCount;
   SignalDrop    clkSource;

   //for trigger parameters
   double        trgLevel;
   SignalDrop    trgSource;
   ActiveSignal  trgEdge;
   TriggerAction trgAction;
   bool          configureMode;
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
   //device general settings
   CComboBox m_cbx_device;
   CComboBox m_cbx_clkSrc;
   
   //trigger settings
   CComboBox m_cbx_trgSrc;
   CComboBox m_cbx_trgEdge;
   CComboBox m_cbx_trgAct;

	CString   m_profilePath;
   double    m_trgLevel;
   int32     m_sectionLength;
   int       m_sectionCount;
   int8*     m_channelEnable;
   bool      m_configureMode;
   int32     m_channelCountMax;
   void CheckError(ErrorCode errorCode);
   DECLARE_MESSAGE_MAP()
   afx_msg void OnBnClickedCancel();
public:
	afx_msg void OnBnClickedBrowse();
   afx_msg void OnCbnSelchangeTrgsrc();
   afx_msg void OnBnClickedChk(UINT nID);
   afx_msg void OnBnClickedRadio();
   void ComponentEnabled(bool flag);
   void InitialChkBox();
};
