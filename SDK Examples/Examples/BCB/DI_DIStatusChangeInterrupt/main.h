//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>

#include "config.h"
#include "../GifImage.hpp"

//---------------------------------------------------------------------------

class StatusChangeHandler;

class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TImage *bkgrndImage;
        TImage *gifViewer;
        TListView *eventDataList;
        TButton *BtnStart;
        TButton *BtnStop;
        TButton *btnConfig;
        void __fastcall BtnStartClick(TObject *Sender);
        void __fastcall BtnStopClick(TObject *Sender);
        void __fastcall btnConfigClick(TObject *Sender);
private:	// User declarations
        ConfigureParameter configure;
        InstantDiCtrl * instantDiCtrl;
        TGIFImage *gif;
        int changedNum;
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        void Initialization();
        void ConfigureDevice(); 
        void SetConfigureParameter(ConfigureParameter value){configure = value;}
        void CheckError(ErrorCode errorCode);
        static void BDAQCALL OnDiSnapEvent(void *sender, DiSnapEventArgs * args, void * userParam);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
