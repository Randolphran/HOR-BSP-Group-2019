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
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *hiPeriodEditor;
        TEdit *loPeriodEditor;
        TLabel *Label4;
        TLabel *Label5;
        TGroupBox *GroupBox1;
        TImage *ExecutionStatus;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TEdit *actualHiPeriod;
        TEdit *actualLoPeriod;
        TLabel *Label9;
        TLabel *Label10;
        TButton *btnConfig;
        TButton *btnStart;
        TButton *btnStop;
        void __fastcall btnConfigClick(TObject *Sender);
        void __fastcall btnStartClick(TObject *Sender);
        void __fastcall btnStopClick(TObject *Sender);
private:	// User declarations
        TGIFImage *gif;
        ConfigureParameter configure;
        PwModulatorCtrl* pwModulatorCtrl;
        
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        void Initialization();
        void ConfigureDevice();
        void SetConfigureParameter(ConfigureParameter value){configure = value;}
        void CheckError(ErrorCode errorCode);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
