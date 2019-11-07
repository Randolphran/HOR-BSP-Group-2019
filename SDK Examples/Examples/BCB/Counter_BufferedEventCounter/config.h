//---------------------------------------------------------------------------

#ifndef configH
#define configH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "../../../Inc/bdaqctrl.h"
#include <CheckLst.hpp>
#define Profile_Confiugre   1
#define Manual_Configure    0

using namespace Automation::BDaq;
//---------------------------------------------------------------------------
struct ConfigureParameter
{
        wchar_t*      deviceName;
        wchar_t*      profilePath;
        int           deviceNumber;
        int8*         channelEnable;
        int32         sectionLength;
        int           sectionCount;
        SignalDrop    clkSource;
        // trigger parameters
        double        trgLevel;
        SignalDrop    trgSource;
        ActiveSignal  trgEdge;
        TriggerAction trgAction;
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
        TGroupBox *GroupBox1;
        TLabel *Label6;
        TEdit *txtSectionLength;
        TLabel *Label7;
        TEdit *txtSectionCount;
        TLabel *Label8;
        TComboBox *cbxSampleClkSrc;
        TGroupBox *GroupBox2;
        TLabel *Label9;
        TComboBox *cbxTrgSource;
        TLabel *Label10;
        TComboBox *cbxTrgAction;
        TLabel *Label11;
        TComboBox *cbxTrgEdge;
        TLabel *Label12;
        TEdit *txtTrgLevel;
        TLabel *Label13;
        TRadioButton *radProfile;
        TRadioButton *radManual;
        TGroupBox *GroupBox3;
        TGroupBox *GroupBox4;
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
        void InitialChkBox();
        int32 channelCountMax;
        BufferedEventCounterCtrl* m_bfdEventCounterCtrl;
        ConfigureParameter GetConfigureParameter(){return configure;}
        void RefreshConfigureParameter();
};
//---------------------------------------------------------------------------
extern PACKAGE TConfigForm *ConfigForm;
//---------------------------------------------------------------------------
#endif
