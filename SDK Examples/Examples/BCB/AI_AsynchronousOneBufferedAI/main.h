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
class StoppedHandler;

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
        TLabel *shiftTimeLabel;
        TLabel *Label3;
        TLabel *divTimeLabel;
        TListView *chanDataList;
        TEdit *shiftTimeEditor;
        TTrackBar *shiftTrackBar;
        TEdit *divTimeEditor;
        TTrackBar *divTrackBar;
        TButton *BtnStart;
        TButton *BtnConfig;
        void __fastcall chanDataListCustomDrawSubItem(
          TCustomListView *Sender, TListItem *Item, int SubItem,
          TCustomDrawState State, bool &DefaultDraw);
        void __fastcall BtnStartClick(TObject *Sender);
        void __fastcall shiftTrackBarChange(TObject *Sender);
        void __fastcall divTrackBarChange(TObject *Sender);
        void __fastcall BtnConfigClick(TObject *Sender);
private:	// User declarations
        ConfigureParameter configure;
        WaveformAiCtrl * wfAiCtrl;
        TSimpleGraph* m_graph;
        double* dataScaled;
        int dataCount;
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        void Initialization();
        void ConfigureDevice();
        void InitializeGraph();
        void InitListView();
        void SetConfigureParameter(ConfigureParameter value){configure = value;}
        void CheckError(ErrorCode errorCode);
        static BDAQCALL void OnStoppedEvent(void *sender, BfdAiEventArgs * args, void * userParam);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
