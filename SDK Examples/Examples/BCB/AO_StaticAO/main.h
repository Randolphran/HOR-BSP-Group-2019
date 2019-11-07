//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <ImgList.hpp>
#include <Graphics.hpp>

#include "config.h"
#include "../DaqUtils.hpp"

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TImage *bkgrndImage;
        TSpeedButton *BtnSineA;
        TSpeedButton *BtnTriangleA;
        TSpeedButton *BtnSquareA;
        TLabel *timerFreqLabel;
        TSpeedButton *BtnSineB;
        TSpeedButton *BtnTriangleB;
        TSpeedButton *BtnSquareB;
        TLabel *chLabelA;
        TLabel *chLabelB;
        TEdit *txtboxHiLevelA;
        TEdit *txtboxLoLevelA;
        TEdit *txtboxValueA;
        TEdit *txtboxHiLevelB;
        TEdit *txtboxLoLevelB;
        TBitBtn *BtnManualA;
        TTrackBar *timerTrackBar;
        TBitBtn *BtnManualB;
        TEdit *txtboxValueB;
        TButton *btnConfigure;
        TTimer *Timer1;
        TImageList *ImageList1;
        void __fastcall btnConfigureClick(TObject *Sender);
        void __fastcall timerTrackBarChange(TObject *Sender);
        void __fastcall ManualOutClick(TObject *Sender);
        void __fastcall WaveButtonClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
        ConfigureParameter configure;
        InstantAoCtrl * instantAoCtrl;
        
        int channelStart;
        int channelCount;
        double dataScaled[2];
        TWaveParam m_waveParam[2];
        TSpeedButton* m_waveButton[6];
        int m_wavePtIdx[2];
        bool m_waveSeled[2];
        Graphics::TBitmap* bitmap;
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        void Initialization();
        void ConfigureDevice();
        void SetConfigureParameter(ConfigureParameter value){configure = value;}
        void CheckError(ErrorCode errorCode);
        void ConfigurePanel();
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
