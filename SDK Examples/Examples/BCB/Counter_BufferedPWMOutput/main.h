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
#include <Math.hpp>

#include "../GifImage.hpp"
#include "config.h"

#define MAX_ROW_COUNT       10
#define Profile_Confiugre   1
#define Manual_Configure    0

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *data1_hiPeriod;
        TEdit *data1_loPeriod;
        TLabel *Label4;
        TLabel *Label5;
        TGroupBox *GroupBox1;
        TImage *ExecutionStatus;
        TButton *btnConfig;
        TButton *btnStart;
        TButton *btnStop;
        TGroupBox *GroupBox2;
        TGroupBox *GroupBox3;
        TLabel *Label1;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TEdit *data2_hiPeriod;
        TEdit *data2_loPeriod;
        TLabel *Label6;
        void __fastcall btnConfigClick(TObject *Sender);
        void __fastcall btnStartClick(TObject *Sender);
        void __fastcall btnStopClick(TObject *Sender);
private:	// User declarations
        TGIFImage *gif;
        ConfigureParameter configure;
        BufferedPwModulatorCtrl* bfdPwModulatorCtrl;
        int32  samplesCount;
        PulseWidth* pulseWidth;
        int8* channelEnable;
        int32 channelCountMax;
        
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        __fastcall ~TMainForm();
        void Initialization();
        void ConfigureDevice();
        void SetConfigureParameter(ConfigureParameter value){configure = value;}
        void CheckError(ErrorCode errorCode);
        static void  BDAQCALL OnDataTransmittedEvent(void * sender, BfdCntrEventArgs * args, void * userParam); 
};

//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
