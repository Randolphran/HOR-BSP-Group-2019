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
        TLabel *Label3;
        TLabel *Label4;
        TListView *chanDataList;
        TEdit *timerIntvlEditor;
        TTrackBar *timerTrackBar;
        TButton *BtnStart;
        TButton *BtnPause;
        TButton *BtnStop;
        TButton *BtnConfig;
        TTimer *Timer1;
        void __fastcall chanDataListCustomDrawSubItem(
          TCustomListView *Sender, TListItem *Item, int SubItem,
          TCustomDrawState State, bool &DefaultDraw);
        void __fastcall timerTrackBarChange(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall BtnStartClick(TObject *Sender);
        void __fastcall BtnPauseClick(TObject *Sender);
        void __fastcall BtnStopClick(TObject *Sender);
        void __fastcall BtnConfigClick(TObject *Sender);
private:	// User declarations
        ConfigureParameter configure;
        InstantAiCtrl * instantAiCtrl;

        TSimpleGraph* m_graph;
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        void Initialization();
        void ConfigureDevice();
        void InitializeGraph();
        void InitListView();
        void SetConfigureParameter(ConfigureParameter value){configure = value;}
        void CheckError(ErrorCode errorCode);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
