// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DaqUtils.pas' rev: 6.00

#ifndef DaqUtilsHPP
#define DaqUtilsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <SyncObjs.hpp>	// Pascal unit
#include <jpeg.hpp>	// Pascal unit
#include <Math.hpp>	// Pascal unit
#include <StrUtils.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Daqutils
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TWaveStyle { Sine, Triangle, Square };
#pragma option pop

struct TWaveParam
{
	TWaveStyle Style;
	double HiLevel;
	double LoLevel;
	int PtsPerPeriod;
} ;

class DELPHICLASS TWaveGenerator;
class PASCALIMPLEMENTATION TWaveGenerator : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	/*         class method */ static double __fastcall GetOnePoint(TMetaClass* vmt, const TWaveParam &wave, int ptIndex);
	/*         class method */ static void __fastcall GetWaveform(TMetaClass* vmt, int waveCount, const TWaveParam * wave, const int wave_Size, int dataCount, double * data, const int data_Size);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TWaveGenerator(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TWaveGenerator(void) { }
	#pragma option pop
	
};


class DELPHICLASS TPortPanel;
class PASCALIMPLEMENTATION TPortPanel : public Extctrls::TPanel 
{
	typedef Extctrls::TPanel inherited;
	
private:
	Classes::TNotifyEvent m_stateChanged;
	Stdctrls::TLabel* m_portLabel;
	Stdctrls::TEdit* m_hexEditor;
	Stdctrls::TGroupBox* m_highGrpBox;
	Stdctrls::TGroupBox* m_lowGrpBox;
	Extctrls::TImage* m_stateBoxes[8];
	Graphics::TGraphic* m_stateImages[3];
	Byte m_mask;
	bool __fastcall getEditable(void);
	void __fastcall setEditable(bool value);
	Byte __fastcall getMask(void);
	void __fastcall setMask(Byte value);
	int __fastcall getPortNum(void);
	Byte __fastcall getState(void);
	void __fastcall setState(Byte value);
	void __fastcall HexEditor_Exit(System::TObject* sender);
	void __fastcall HexEditor_KeyDown(System::TObject* sender, Word &key, Classes::TShiftState shift);
	void __fastcall StateBox_Clicked(System::TObject* sender);
	
public:
	__fastcall virtual TPortPanel(Classes::TComponent* AOwner);
	void __fastcall Initialize(int port, const Graphics::TGraphic* * images, const int images_Size);
	bool __fastcall ShowPortLabel(bool show);
	bool __fastcall ShowHexEditor(bool show);
	__property bool Editable = {read=getEditable, write=setEditable, nodefault};
	__property Byte Mask = {read=getMask, write=setMask, nodefault};
	__property int Port = {read=getPortNum, nodefault};
	__property Byte State = {read=getState, write=setState, nodefault};
	__property Classes::TNotifyEvent OnChange = {read=m_stateChanged, write=m_stateChanged};
public:
	#pragma option push -w-inl
	/* TCustomControl.Destroy */ inline __fastcall virtual ~TPortPanel(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TPortPanel(HWND ParentWindow) : Extctrls::TPanel(ParentWindow) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TEventCheckNotify)(int id, unsigned obj);

class DELPHICLASS TEventCheckThread;
class PASCALIMPLEMENTATION TEventCheckThread : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
private:
	int m_ids[63];
	unsigned m_handles[63];
	TEventCheckNotify m_notifies[63];
	bool m_synced[63];
	int m_count;
	unsigned m_syncObj;
	Syncobjs::TCriticalSection* m_lock;
	int syncId;
	unsigned syncObj;
	TEventCheckNotify syncProc;
	void __fastcall SyncNotify(void);
	
protected:
	virtual void __fastcall Execute(void);
	
public:
	__fastcall TEventCheckThread(bool createSuspended)/* overload */;
	__fastcall virtual ~TEventCheckThread(void);
	void __fastcall Add(int id, unsigned handle, TEventCheckNotify notify, bool synced);
	void __fastcall Remove(unsigned handle);
	void __fastcall Clear(void);
	void __fastcall Stop(void);
	__property int Count = {read=m_count, nodefault};
};


#pragma option push -b-
enum TOverOneScreenMode { BeginScreen, EndScreen };
#pragma option pop

typedef DynamicArray<double >  DaqUtils__5;

typedef DynamicArray<Types::TPoint >  DaqUtils__6;

typedef DynamicArray<DynamicArray<Types::TPoint > >  DaqUtils__7;

class DELPHICLASS TSimpleGraph;
class PASCALIMPLEMENTATION TSimpleGraph : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	Extctrls::TPaintBox* m_hostCtrl;
	double m_YCordMax;
	double m_YCordMin;
	double m_xIncByTime;
	DynamicArray<double >  m_plotData;
	DynamicArray<DynamicArray<Types::TPoint > >  m_dataPoint;
	double m_XCordDivRate;
	double m_XCordTimeDiv;
	double m_XCordTimeOffset;
	int m_plotCount;
	int m_shiftCount;
	int m_dataCachedPerPlot;
	int m_mapIndexPerPlot;
	int m_pointPerScreen;
	TOverOneScreenMode m_overOneScreenMode;
	int m_xPosition;
	bool m_recordEndFlag;
	bool m_drawRecordEnd;
	int m_recordEndPointx;
	void __fastcall HostCtrlPaint(System::TObject* sender);
	void __fastcall SaveData(const double * data, const int data_Size, int dataPerPlot);
	void __fastcall Redraw(void);
	void __fastcall CalcDrawParams(double xIncBySec);
	void __fastcall MapDataPoints(void);
	void __fastcall DrawOnePlot(Graphics::TCanvas* canvas, const Types::TPoint * data, const int data_Size, int count);
	
public:
	__fastcall TSimpleGraph(Extctrls::TPaintBox* hostCtrl);
	__fastcall virtual ~TSimpleGraph(void);
	void __fastcall Clear(void);
	void __fastcall Chart(const double * data, const int data_Size, int plotCount, int dataPerPlot, double xIncBySec, bool flag)/* overload */;
	void __fastcall Chart(const double * data, const int data_Size, int plotCount, int dataPerPlot, double xIncBySec)/* overload */;
	void __fastcall ScaleXCord(int DivValue);
	void __fastcall Shift(int shiftTime);
	void __fastcall PaintTo(Graphics::TCanvas* canvas);
	Graphics::TColor __fastcall GetPlotColor(int plot);
	__property double XCordTimeDiv = {read=m_XCordTimeDiv, write=m_XCordTimeDiv};
	__property double XCordOffset = {read=m_XCordTimeOffset, write=m_XCordTimeOffset};
	__property double YCordMax = {read=m_YCordMax, write=m_YCordMax};
	__property double YCordMin = {read=m_YCordMin, write=m_YCordMin};
	__property TOverOneScreenMode OverOneScreenMode = {read=m_overOneScreenMode, write=m_overOneScreenMode, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE int STATE_DISABLE_IMG_IDX;
extern PACKAGE int STATE_HI_IMG_IDX;
extern PACKAGE int STATE_LO_IMG_IDX;
extern PACKAGE int EVENT_MAX_ALLOWED;
extern PACKAGE Jpeg::TJPEGImage* __fastcall LoadJPEGFromResource(unsigned resHandle, AnsiString name);

}	/* namespace Daqutils */
using namespace Daqutils;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DaqUtils
