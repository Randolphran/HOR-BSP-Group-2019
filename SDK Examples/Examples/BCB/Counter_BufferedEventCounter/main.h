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

#define MAX_ROW_COUNT       10
#define Profile_Confiugre   1
#define Manual_Configure    0

#include "config.h"

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TImage *bkgrndImage;
        TGroupBox *GroupBox1;
        TEdit *txtChannelStatus;
        TListBox *cntrValueList;
        TButton *btnStart;
        TButton *btnStop;
        TButton *btnConfig;
        TLabel *Label1;
        TLabel *Label2;
        TComboBox *cbxDisplayChannel;
        TLabel *Label3;

        void __fastcall btnStopClick(TObject *Sender);
        void __fastcall btnStartClick(TObject *Sender);
        void __fastcall btnConfigClick(TObject *Sender);
        void __fastcall cbxDisplayChannelChange(TObject *Sender);
        
private:	// User declarations
        ConfigureParameter configure;
        bool ECisRunning;
        bool haveData;
        
        int32* dataBuf;
        int32** chs_dataBuf;
        int32  samplesCount;
        int32  sectionLength;
        int32  sectionCount;
        int8*  channelEnable;
        int32  channelCountMax;
        AnsiString* chs_Status;
        int32  eventChannel;  // event occured channel
        int32  displayChannel; // which channel' value want to display.
        
        BufferedEventCounterCtrl* bfdEventCounterCtrl;
        
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        __fastcall ~TMainForm();
        void Initialization();
        void ConfigureDevice();
        void SetConfigureParameter(ConfigureParameter value){configure = value;}
        void CheckError(ErrorCode errorCode);
        static void BDAQCALL OnDataReadyEvent(void *sender, BfdCntrEventArgs * args, void * userParam);
        static void BDAQCALL OnStoppedEvent(void *sender, BfdCntrEventArgs * args, void * userParam);
        void ChannelStatusChange(int32 channel, AnsiString str);
        void DisplayChannelStatus(int32 channel);
        void DisplayChannelValue(int32 channel);
        void CopyChannelData(int32 channel);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
