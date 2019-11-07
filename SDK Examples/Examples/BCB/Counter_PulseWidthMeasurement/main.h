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

#include "config.h"

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TTimer *Timer1;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *hiPeriodEditor;
        TEdit *loPeriodEditor;
        TLabel *Label3;
        TLabel *Label4;
        TListBox *cntrValueList;
        TButton *btnStart;
        TButton *btnStop;
        TButton *btnConfig;
        void __fastcall btnConfigClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall btnStartClick(TObject *Sender);
        void __fastcall btnStopClick(TObject *Sender);
private:	// User declarations
        ConfigureParameter configure;
        bool ECisRunning;
        bool isPwMeterReset;
        PwMeterCtrl* pwMeterCtrl;
        
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
