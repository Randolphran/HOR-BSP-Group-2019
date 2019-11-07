// DI Status ChangeDlg.h : header file
//

#pragma once
#include "ConfigurationDlg.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "PictureEx.h"

class CDIStatusChangeInterruptDlg : public CDialog
{
   // Construction
public:
   CDIStatusChangeInterruptDlg(CWnd* pParent = NULL);	
   ~CDIStatusChangeInterruptDlg();
   // Dialog Data
   enum { IDD = IDD_DISTATUSCHANGE_DIALOG };
   // This function is used to deal with 'StatusChange' Event.
   static void  BDAQCALL OnDiSnapEvent(void * sender, DiSnapEventArgs * args, void * userParam);
   // Implementation
protected:
   HICON m_hIcon;
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	// Generated message map functions
	//{{AFX_MSG(CDIStatusChangeInterruptDlg)
   LRESULT OnConfDevice(WPARAM w,LPARAM l);
   virtual BOOL OnInitDialog();
   afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
   afx_msg void OnPaint();
   afx_msg HCURSOR OnQueryDragIcon();
   afx_msg LRESULT OnUpdateList(WPARAM wParam, LPARAM lParam);   
	afx_msg void OnBnClickedConfig();
   afx_msg void OnClickedStart();
   afx_msg void OnClickedStop();
	//}}AFX_MSG
private:
   InstantDiCtrl *      m_instantDiCtrl;
   DevConfParam         m_confParam; // the device's configure information from config form.
   CConfigurationDlg	   m_confDlg;
   int m_eventCount;

   CPictureEx m_gifPic;
   CListCtrl  m_list;

private:
   void ConfigureDevice();
   void ConfigurePanel();
   void CheckError(ErrorCode errorCode);
   DECLARE_MESSAGE_MAP()

};

