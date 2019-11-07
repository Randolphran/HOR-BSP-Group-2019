//---------------------------------------------------------------------------

#ifndef configH
#define configH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "../.././Inc/bdaqctrl.h"

using namespace Automation::BDaq;
//---------------------------------------------------------------------------
struct ConfigureParameter
{
	wchar_t* deviceName;
	int channel;
        wchar_t* profilePath;
};

class TConfigForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TComboBox *cmbDevice;
        TComboBox *cmbCounterChannel;
        TButton *btnOk;
        TButton *btnCancel;
        TLabel *Label3;
        TEdit *txtProfilePath;
        TButton *btnBrowse;
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall cmbDeviceChange(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall btnOkClick(TObject *Sender);
        void __fastcall btnBrowseClick(TObject *Sender);
private:	// User declarations
        ConfigureParameter configure;
        
public:		// User declarations
        __fastcall TConfigForm(TComponent* Owner);
        bool isFirstLoad;
        bool isBtnOkClicked;
        void Initialization();
        void CheckError(ErrorCode errorCode);
        ConfigureParameter GetConfigureParameter(){return configure;}
};
//---------------------------------------------------------------------------
extern PACKAGE TConfigForm *ConfigForm;
//---------------------------------------------------------------------------
#endif
