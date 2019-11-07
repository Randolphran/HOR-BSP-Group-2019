//---------------------------------------------------------------------------

#ifndef configH
#define configH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "../../../Inc/bdaqctrl.h"

using namespace Automation::BDaq;
//---------------------------------------------------------------------------
struct ConfigureParameter
{
	wchar_t* deviceName;
        int channelStart;
        int channelCount;
	ValueRange valueRange;
        int sectionLength;
        double clockRate;
        wchar_t* profilePath;

        // for trigger
        TriggerAction triggerAction;
        SignalDrop triggerSource;
        ActiveSignal triggerEdge;
	int delayCount;
	double triggerLevel;
};

class TConfigForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TComboBox *cmbDevice;
        TButton *btnOk;
        TButton *btnCancel;
        TGroupBox *GroupBox1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TComboBox *cmbChannelStart;
        TComboBox *cmbChannelCount;
        TComboBox *cmbValueRange;
        TLabel *Label7;
        TEdit *txtClockRate;
        TLabel *Label8;
        TEdit *txtSectionLength;
        TLabel *Label5;
        TGroupBox *GroupBox2;
        TLabel *Label6;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TComboBox *cmbTriggerSource;
        TComboBox *cmbTriggerEdge;
        TEdit *txtTriggerLevel;
        TEdit *txtDelayCount;
        TLabel *Label13;
        TEdit *txtProfilePath;
        TButton *btnBrowse;
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall btnOkClick(TObject *Sender);
        void __fastcall cmbDeviceChange(TObject *Sender);
        void __fastcall cmbTriggerSourceChange(TObject *Sender);
        void __fastcall btnBrowseClick(TObject *Sender);
private:	// User declarations
        ConfigureParameter configure;

        bool isTriggerSupported;
public:		// User declarations
        __fastcall TConfigForm(TComponent* Owner);
        bool isFirstLoad;
        bool isBtnOkClicked;
        void Initialization();
        void CheckError(ErrorCode errorCode);
        ConfigureParameter GetConfigureParameter(){return configure;}
        void RefreshConfigureParameter();
};
//---------------------------------------------------------------------------
extern PACKAGE TConfigForm *ConfigForm;
//---------------------------------------------------------------------------
#endif
