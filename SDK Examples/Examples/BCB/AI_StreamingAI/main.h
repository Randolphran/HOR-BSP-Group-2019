//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>

#include "config.h"
#include "../DaqUtils.hpp"

//---------------------------------------------------------------------------
class DataReadyHandler;
class OverrunHandler;
class CacheOverflowHandler;

class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TImage *bkgrndImage;
        TPaintBox *DataView;
        TLabel *yTLabel;
        TLabel *yMLabel;
        TLabel *yBLabel;
        TLabel *xLLabel;
        TLabel *xRLabel;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *divTimeLabel;
        TListView *chanDataList;
        TTrackBar *divTrackBar;
        TButton *BtnStart;
        TButton *BtnPause;
        TButton *BtnStop;
        TButton *BtnConfig;
        void __fastcall chanDataListCustomDrawSubItem(
          TCustomListView *Sender, TListItem *Item, int SubItem,
          TCustomDrawState State, bool &DefaultDraw);
        void __fastcall divTrackBarChange(TObject *Sender);
        void __fastcall BtnStartClick(TObject *Sender);
        void __fastcall BtnPauseClick(TObject *Sender);
        void __fastcall BtnStopClick(TObject *Sender);
        void __fastcall BtnConfigClick(TObject *Sender);
private:	// User declarations
        ConfigureParameter configure;
        WaveformAiCtrl * wfAiCtrl;
        int dataCount;
        TSimpleGraph* m_graph;
        double* dataScaled;
        bool isFirstOverRun;
        
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        void Initialization();
        void ConfigureDevice();
        void InitializeGraph();
        void InitListView();
        void SetConfigureParameter(ConfigureParameter value){configure = value;}
        void CheckError(ErrorCode errorCode);

        static void BDAQCALL OnDataReadyEvent(void *sender, BfdAiEventArgs * args, void * userParam);
        static void BDAQCALL OnOverrunEvent(void *sender, BfdAiEventArgs * args, void * userParam);
        static void BDAQCALL OnCacheOverflowEvent(void *sender, BfdAiEventArgs * args, void * userParam);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
