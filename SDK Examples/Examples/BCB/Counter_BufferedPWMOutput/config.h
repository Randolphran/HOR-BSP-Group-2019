//---------------------------------------------------------------------------

#ifndef configH
#define configH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "../.././Inc/bdaqctrl.h"
#include <CheckLst.hpp>

#include <iostream>
#include <conio.h>
using namespace Automation::BDaq;
//---------------------------------------------------------------------------
struct ConfigureParameter
{
	wchar_t*        deviceName;
        wchar_t*        profilePath;
        int32           intervalCount;
        SignalDrop      clkSource;
        // trigger parameters
        double          trgLevel;
        SignalDrop      trgSource;
        ActiveSignal    trgEdge;
        TriggerAction   trgAction;

        int           deviceNumber;
        int8*         channelEnable;
        bool          configureMode;
};

class TConfigForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TComboBox *cmbDevice;
        TButton *btnOk;
        TButton *btnCancel;
        TLabel *Label3;
        TEdit *txtProfilePath;
        TButton *btnBrowse;
        TGroupBox *GroupBox2;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TComboBox *cbxTrgSource;
        TComboBox *cbxTrgAction;
        TComboBox *cbxTrgEdge;
        TLabel *Label11;
        TEdit *txtTrgLevel;
        TLabel *Label12;
        TRadioButton *radProfile;
        TRadioButton *radManual;
        TGroupBox *GroupBox3;
        TGroupBox *GroupBox4;
        TGroupBox *GroupBox1;
        TLabel *Label6;
        TLabel *Label7;
        TComboBox *cbxSampleClkSrc;
        TEdit *txtIntervalCount;
        TCheckListBox *chkListBox;
        TLabel *Label2;
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall cmbDeviceChange(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall btnOkClick(TObject *Sender);
        void __fastcall btnBrowseClick(TObject *Sender);
        void __fastcall cbxTrgSourceChange(TObject *Sender);
        void __fastcall radioBtnClick(TObject *Sender);
        void __fastcall checkBoxClick(TObject *Sender);
private:	// User declarations
        ConfigureParameter configure;
        
public:		// User declarations
        __fastcall TConfigForm(TComponent* Owner);
        __fastcall ~TConfigForm();
        bool isFirstLoad;
        bool isBtnOkClicked;
        void Initialization();
        void CheckError(ErrorCode errorCode);
        void ComponentEnabled(bool flag);
        ConfigureParameter GetConfigureParameter(){return configure;}
        int32 channelCountMax;
        BufferedPwModulatorCtrl* m_bfdPwModulatorCtrl;
        void InitialChkBox();
        void RefreshConfigureParameter();
};
//---------------------------------------------------------------------------
extern PACKAGE TConfigForm *ConfigForm;
//---------------------------------------------------------------------------
#endif
