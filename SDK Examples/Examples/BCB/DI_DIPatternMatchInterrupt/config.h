//---------------------------------------------------------------------------

#ifndef configH
#define configH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Graphics.hpp>

#include "../../../Inc/bdaqctrl.h"

using namespace Automation::BDaq;
//---------------------------------------------------------------------------
struct ConfigureParameter
{
	wchar_t *deviceName;
        int selectedPort;
        byte enabledChannels;
	byte pmValue;
        wchar_t* profilePath;
};

class TConfigForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TComboBox *cmbDevice;
        TButton *btnOk;
        TButton *btnCancel;
        TLabel *Label2;
        TComboBox *cmbDIport;
        TLabel *Label3;
        TLabel *Label4;
        TGroupBox *GroupBox2;
        TImage *Image04;
        TImage *Image05;
        TImage *Image06;
        TImage *Image07;
        TEdit *enableChan;
        TImageList *ImageList1;
        TGroupBox *GroupBox1;
        TImage *Image00;
        TImage *Image01;
        TImage *Image02;
        TImage *Image03;
        TGroupBox *GroupBo4;
        TImage *Image14;
        TImage *Image15;
        TImage *Image16;
        TImage *Image17;
        TGroupBox *GroupBox3;
        TImage *Image13;
        TImage *Image10;
        TImage *Image11;
        TImage *Image12;
        TEdit *edtpmValue;
        TLabel *Label5;
        TEdit *txtProfilePath;
        TButton *butBrowse;
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall btnOkClick(TObject *Sender);
        void __fastcall cmbDeviceChange(TObject *Sender);
        void __fastcall Image0Click(TObject *Sender);
        void __fastcall Image1Click(TObject *Sender);
        void __fastcall cmbDIportChange(TObject *Sender);
        void __fastcall butBrowseClick(TObject *Sender);
private:	// User declarations
        ConfigureParameter configure;
        TImage* images[2][8];
        byte enableChannels;
        byte pmValue;
        int *deviceIndex;
        
public:		// User declarations
        __fastcall TConfigForm(TComponent* Owner);
        bool isFirstLoad;
        bool isBtnOkClicked;
        void Initialization();
        void InitializePortState();
        void CheckError(ErrorCode errorCode);
        ConfigureParameter GetConfigureParameter(){return configure;}
};
//---------------------------------------------------------------------------
extern PACKAGE TConfigForm *ConfigForm;
//---------------------------------------------------------------------------
#endif
