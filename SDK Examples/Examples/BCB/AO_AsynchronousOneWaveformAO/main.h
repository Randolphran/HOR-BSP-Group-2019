//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <ImgList.hpp>
#include <Graphics.hpp>

#include "config.h"
#include "../DaqUtils.hpp"

//---------------------------------------------------------------------------
class BufferedAoStoppedHandler;

class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TImage *bkgrndImage;
        TLabel *chLabelA;
        TLabel *chLabelB;
        TSpeedButton *BtnSineA;
        TSpeedButton *BtnTriangleA;
        TSpeedButton *BtnSquareA;
        TSpeedButton *BtnSineB;
        TSpeedButton *BtnTriangleB;
        TSpeedButton *BtnSquareB;
        TEdit *txtboxHiLevelA;
        TEdit *txtboxLoLevelA;
        TEdit *txtboxHiLevelB;
        TEdit *txtboxLoLevelB;
        TButton *BtnStart;
        TImageList *ImageList1;
        TButton *btnConfig;
        void __fastcall btnConfigClick(TObject *Sender);
        void __fastcall BtnStartClick(TObject *Sender);
        void __fastcall WaveButtonClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
        ConfigureParameter configure;
        BufferedAoCtrl * bfdAoCtrl;

        double* dataScaled;
        TWaveParam m_waveParam[2];
        TSpeedButton* m_waveButton[6];
        bool m_waveSeled[2];
        Graphics::TBitmap* bitmap;
        bool formCloseFlag;
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        void Initialization();
        void ConfigureDevice();
        void SetConfigureParameter(ConfigureParameter value){configure = value;}
        void CheckError(ErrorCode errorCode);
        void ConfigurePanel();
        void InitialButtons();
        static void BDAQCALL OnStoppedEvent(void *sender, BfdAoEventArgs * args, void * userParam);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
