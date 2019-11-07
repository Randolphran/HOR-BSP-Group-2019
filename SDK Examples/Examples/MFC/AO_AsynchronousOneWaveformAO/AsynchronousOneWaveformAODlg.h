// MainDialog.h : header file
//
#pragma once
#include "ConfigurationDlg.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "../WaveformGenerator.h"

#define CHANNEL_COUNT      2
#define WAVE_STYLE_COUNT   3
#define WAVE_BTN_COUNT     CHANNEL_COUNT * WAVE_STYLE_COUNT

typedef struct tagUIStateOfChannel
{
   CButton *btnWaveStyle[WAVE_STYLE_COUNT];
   CEdit   *editHighLevel;
   CEdit   *editLowLevel;
   int      btnSelected;
}UIStateOfChannel, *PUIStateOfChannel;

// MainDialog dialog
class CAsynchronousOneWaveformAODlg : public CDialog
{
   // Construction
public:
   CAsynchronousOneWaveformAODlg(CWnd* pParent = NULL);	// standard constructor
   virtual ~CAsynchronousOneWaveformAODlg();
   // Dialog Data
   enum { IDD = IDD_ASYNCHRONOUSBUFFEREDAO_DIALOG};

   // Implementation
protected:
   HICON m_hIcon;
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
   // Generated message map functions
   //{{AFX_MSG(CAsynchronousOneWaveformAODlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnPaint();
   afx_msg HCURSOR OnQueryDragIcon();
   afx_msg void OnCheckBoxClicked(UINT nID);   
   afx_msg void OnBnClickedButtonConfig();
   afx_msg LRESULT OnConfDevice(WPARAM wParam,LPARAM lParam);// user-defined ,for getting the configuration information.
   afx_msg void OnStart();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
private:
   CConfigurationDlg    m_confDlg;
   BufferedAoCtrl *     m_bufferedAoCtrl;
   DevConfParam         m_confParam;

   UIStateOfChannel   m_uiStateAllChannels[CHANNEL_COUNT];
   HBITMAP            m_waveformStyleBmp[WAVE_STYLE_COUNT][2];
   WaveformParameter  m_waveformParam[CHANNEL_COUNT];
   
   void ConfigurateDevice(); // config device with configInfo.
   void SetUIStateOfChannelState(PUIStateOfChannel uiStateOfChannel, BOOL state);
   void ConfiguratePanel(); // config UI with configInfo.
   void InitUIState();
   void CheckError(ErrorCode errorCode); 
public:
   static void BDAQCALL OnStoppedEvent(void * sender, BfdAoEventArgs * args, void * userParam);
};
