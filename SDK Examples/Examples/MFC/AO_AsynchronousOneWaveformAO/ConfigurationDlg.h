#pragma once
#include "afxwin.h"
#include "../../../Inc/bdaqctrl.h"
using namespace Automation::BDaq;
#define WM_CUSTOME_CFG_CHGED   (WM_USER + 0x1001) 
#define WM_UPDATEMSG           (WM_USER + 0x1002)
// CConfigForm dialog

typedef struct tagDevConfParam
{
   int  deviceNumber;
   long channelStart;
   long channelCount;
   long vrgType;
   int  pointCountPerWave;
   double clockRatePerChan;
	WCHAR profilePath[256];
}DevConfParam, *PDevConfParam;
#define PCDeviceSetting const PDevConfParam 

#define MODULE_INDEX        0 

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
   //{{AFX_MSG(ConfigForm)
   virtual BOOL OnInitDialog();
   virtual void OnBnClickedOk();
   afx_msg void OnCbnSelchangeComboDevice();
   afx_msg void OnEnChangeConvertclockrateperchannel();
   afx_msg void OnBnClickedCancel();
   afx_msg void OnClose();
   //}}AFX_MSG

private:
   CComboBox m_comboBox_Device;
   CComboBox m_comboBox_ChannelStart;
   CComboBox m_comboBox_ChannelCount;
   CComboBox m_comboBox_ValueRange; 
   double    m_pointsCount;
   double    m_clockRatePerChan;
	CString   m_profilePath;

   void CheckError(ErrorCode errorCode);
   DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnBnClickedBrowse();
};
