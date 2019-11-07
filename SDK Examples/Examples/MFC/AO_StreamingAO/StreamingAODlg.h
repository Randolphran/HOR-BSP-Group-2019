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
#define CONVERT_CLK_RATE( pointCountPerWave, waveformOutFreq) (pointCountPerWave * waveformOutFreq)

typedef struct tagUIStateOfChannel
{
   CButton *btnWaveStyle[WAVE_STYLE_COUNT];
   CEdit   *editHighLevel;
   CEdit   *editLowLevel;
   int      btnSelected;
}UIStateOfChannel, *PUIStateOfChannel;

typedef enum tagbfdAoEvnetType {
   AoStopped = 0,
   DataTransmitted,
   Underrun,
   TransStopped,
} BfdAoEvnetType;

// CStreamingAODlg dialog
class CStreamingAODlg : public CDialog
{
public:
   BfdAoEvnetType bfdAoEvnetType ;
   // Construction
public:
   CStreamingAODlg(CWnd* pParent = NULL);	// standard constructor
   virtual ~CStreamingAODlg();
   // Dialog Data
   enum { IDD = IDD_AO_CYCLICWAVEFORMOUT_DIALOG };

   // Implementation
protected:
   HICON m_hIcon;
   virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
   // Generated message map functions
   //{{AFX_MSG(CStreamingAODlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnPaint();
   afx_msg LRESULT OnConfDevice(WPARAM wParam,LPARAM lParam);// user-defined ,for getting the configuration information.
   afx_msg HCURSOR OnQueryDragIcon();
   afx_msg void OnCheckBoxClicked(UINT nID);   
   afx_msg void OnBnClickedButtonConfig();
   afx_msg void OnStart();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
private:
   CConfigurationDlg    m_confDlg;
   BufferedAoCtrl *     m_bufferedAoCtrl;
   DevConfParam         m_confParam;

   UIStateOfChannel     m_uiStateAllChannels[CHANNEL_COUNT];
   HBITMAP              m_waveformStyleBmp[WAVE_STYLE_COUNT][2];
   WaveformParameter    m_waveformParam[CHANNEL_COUNT];
   
   void ConfigurateDevice(); // config device with configInfo.
   void ConfiguratePanel(); // config UI with configInfo.
   void StartBufferedAo();
   void SetUIStateOfChannelState(PUIStateOfChannel uiStateOfChannel, BOOL state);
   void InitUIState();
   void CheckError(ErrorCode errorCode); 

public:
   static void BDAQCALL OnStoppedEvent(void * sender, BfdAoEventArgs *args, void * userParam);
   static void BDAQCALL OnDataTransmittedEvent(void * sender, BfdAoEventArgs *args, void * userParam);
   static void BDAQCALL OnTransitStoppedEvent(void * sender, BfdAoEventArgs *args, void * userParam);
};
