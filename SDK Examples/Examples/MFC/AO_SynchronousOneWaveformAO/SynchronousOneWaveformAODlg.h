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

// CSynchronousOneWaveformAODlg dialog
class CSynchronousOneWaveformAODlg : public CDialog
{
// Construction
public:
	CSynchronousOneWaveformAODlg(CWnd* pParent = NULL);	// standard constructor
   virtual ~CSynchronousOneWaveformAODlg();
   void ConfiguratePanel(); // config UI with configInfo.
   
private:
   void CheckError(ErrorCode errorCode); 
   ErrorCode ConfigurateDevice(); // config device with configInfo.
   void SetUIStateOfChannelState(PUIStateOfChannel uiStateOfChannel, BOOL state);
   void InitUIState();

   // Dialog Data
	enum { IDD = IDD_AO_SYNCHRONOUSONEWAVEFORMOUT_DIALOG };

// Implementation
protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
   
   // Generated message map functions
   //{{AFX_MSG(CSynchronousOneWaveformAODlg)
   afx_msg LRESULT OnConfDevice(WPARAM wParam,LPARAM lParam);// user-defined ,for getting the configuration information.
   virtual BOOL OnInitDialog();
   afx_msg void OnPaint();
   afx_msg HCURSOR OnQueryDragIcon();
   afx_msg void OnCheckBoxClicked(UINT nID);   
   afx_msg void OnBnClickedButtonConfig();
   afx_msg void OnStart();
	afx_msg void OnClose();
   //}}AFX_MSG
   
private:
   CConfigurationDlg    m_confDlg;
   BufferedAoCtrl *     m_bufferedAoCtrl;
   DevConfParam         m_confParam;

   UIStateOfChannel   m_uiStateAllChannels[CHANNEL_COUNT];
   HBITMAP            m_waveformStyleBmp[WAVE_STYLE_COUNT][2];
   WaveformParameter  m_waveformParam[CHANNEL_COUNT];

	DECLARE_MESSAGE_MAP()
};
