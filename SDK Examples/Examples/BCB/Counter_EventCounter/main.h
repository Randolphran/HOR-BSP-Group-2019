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
        TImage *bkgrndImage;
        TTimer *Timer1;
        TGroupBox *GroupBox1;
        TEdit *curValueEditor;
        TListBox *cntrValueList;
        TButton *btnStart;
        TButton *btnStop;
        TButton *btnConfig;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall btnStopClick(TObject *Sender);
        void __fastcall btnStartClick(TObject *Sender);
        void __fastcall btnConfigClick(TObject *Sender);
        
private:	// User declarations
        ConfigureParameter configure;
        bool ECisRunning;
        bool isEventCountingReset;
        EventCounterCtrl* eventCounterCtrl;
        
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
