//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <ComCtrls.hpp>

#include "config.h"
#include "../DaqUtils.hpp"

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TPaintBox *DataView;
        TLabel *yTLabel;
        TLabel *yBLabel;
        TLabel *yMLabel;
        TImage *Enlarge;
        TImage *Shorten;
        TLabel *xLLabel;
        TLabel *xRLabel;
        TLabel *Label1;
        TTrackBar *timerTrackBar;
        TLabel *timerValueLabel;
        TButton *btnStart;
        TButton *btnPause;
        TButton *btnStop;
        TButton *btnConfig;
        TTimer *Timer1;
        TEdit *editValue;
        void __fastcall timerTrackBarChange(TObject *Sender);
        void __fastcall EnlargeClick(TObject *Sender);
        void __fastcall ShortenClick(TObject *Sender);
        void __fastcall btnStartClick(TObject *Sender);
        void __fastcall btnPauseClick(TObject *Sender);
        void __fastcall btnStopClick(TObject *Sender);
        void __fastcall btnConfigClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
        ConfigureParameter configure;
        FreqMeterCtrl* freqMeterCtrl;
        TSimpleGraph* graph;
        double m_yaxisMax;
        bool isCounterReseted;
        double frequency[1];
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        void Initialization();
        void ConfigureDevice();
        void SetConfigureParameter(ConfigureParameter value){configure = value;}
        void CheckError(ErrorCode errorCode);
        void InitializeGraph();
        void InitializeYAxis();
        AnsiString FormatFreqString(double freqHz);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
