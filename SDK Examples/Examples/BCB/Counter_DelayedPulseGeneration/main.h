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
        TGroupBox *GroupBox1;
        TButton *btnConfig;
        TButton *btnStart;
        TButton *btnStop;
        TImage *ExecutionStatus;
        TLabel *Label1;
        TLabel *label_shotCount;
        TEdit *clockCountEditor;
        TEdit *shotCountEditor;
        void __fastcall btnConfigClick(TObject *Sender);
        void __fastcall btnStopClick(TObject *Sender);
        void __fastcall btnStartClick(TObject *Sender);
private:	// User declarations
        TGIFImage *gif;
        ConfigureParameter configure;
        OneShotCtrl * oneShotCtrl;
        int DelayedPulseCount;
        int countOfValue;
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
