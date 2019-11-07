//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>

#include "../DaqUtils.hpp"
#include "config.h"

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TImage *bkgrndImage;
        TButton *btnConfig;
        TLabel *Label1;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TScrollBox *ScrollBox1;
        void __fastcall btnConfigClick(TObject *Sender);
private:	// User declarations
         ConfigureParameter configure;
         InstantDoCtrl * instantDoCtrl;

         int portCount;
         TPortPanel** m_portPanel;
         int portPanelLength;
         const TGraphic* m_stateImage[3];
         
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        void Initialization();
        void ConfigureDevice();
        void InitializePortPanel();
        void SetConfigureParameter(ConfigureParameter value){configure = value;}
        void CheckError(ErrorCode errorCode);
        void __fastcall PortChanged(TObject *Sender);

};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
