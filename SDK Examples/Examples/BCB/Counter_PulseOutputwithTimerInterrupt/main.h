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

#include "../GifImage.hpp"
#include "config.h"

//---------------------------------------------------------------------------

class CntrEventHandler;

class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *userFreqEditor;
        TGroupBox *GroupBox1;
        TImage *ExecutionStatus;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TEdit *devFreqEditor;
        TEdit *evtCountEditor;
        TButton *btnConfig;
        TButton *btnStart;
        TButton *btnStop;
        void __fastcall btnConfigClick(TObject *Sender);
        void __fastcall btnStartClick(TObject *Sender);
        void __fastcall btnStopClick(TObject *Sender);
private:	// User declarations
        TGIFImage *gif;
        ConfigureParameter configure;
        TimerPulseCtrl* timerPulseCtrl;
        int eventCount;

public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        void Initialization();
        void ConfigureDevice();
        void SetConfigureParameter(ConfigureParameter value){configure = value;}
        void CheckError(ErrorCode errorCode);
        static void BDAQCALL OnCounterEvent(void *sender, CntrEventArgs *args, void * userParam);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
