unit DaqUtils;

interface

uses
  Windows, Graphics, Classes, StdCtrls, ExtCtrls, Controls, SysUtils, StrUtils, Math, JPEG, SyncObjs;

const
    STATE_DISABLE_IMG_IDX: Integer = 2;
    STATE_HI_IMG_IDX     : Integer = 1;
    STATE_LO_IMG_IDX     : Integer = 0;
    EVENT_MAX_ALLOWED    : Integer = MAXIMUM_WAIT_OBJECTS - 1;
type
   TWaveStyle = (Sine, Triangle, Square);

   TWaveParam = record
      Style     : TWaveStyle;
      HiLevel   : Double;
      LoLevel   : Double;
      PtsPerPeriod: Integer;
   end;

   TWaveGenerator  = class
   public
      class function  GetOnePoint(const wave: TWaveParam; ptIndex: Integer): Double;
      class procedure GetWaveform(waveCount: Integer; const wave: array of TWaveParam; dataCount: Integer; var data: array of Double);
   end;

   TPortPanel = class(TPanel)
   private
      m_stateChanged : TNotifyEvent;
      m_portLabel    : TLabel;
      m_hexEditor    : TEdit;
      m_highGrpBox   : TGroupBox;
      m_lowGrpBox    : TGroupBox;
      m_stateBoxes   : array[0..7] of TImage;
      m_stateImages  : array[0..2] of TGraphic;
      m_mask         : Byte;

      function  getEditable: Boolean;
      procedure setEditable(value: Boolean);
      function  getMask: Byte;
      procedure setMask(value: Byte);
      function  getPortNum: Integer;
      function  getState: Byte;
      procedure setState(value: Byte);

      procedure HexEditor_Exit(sender: TObject);
      procedure HexEditor_KeyDown(sender: TObject; var key: Word; shift: TShiftState);
      procedure StateBox_Clicked(sender: TObject);
   public
      constructor Create(AOwner : TComponent); override;
      procedure Initialize(port: Integer; const images: array of TGraphic);
      function  ShowPortLabel(show : Boolean):Boolean;
      function  ShowHexEditor(show : Boolean):Boolean;

      property Editable: Boolean      read getEditable    write setEditable;
      property Mask    : Byte         read getMask        write setMask;
      property Port    : Integer      read getPortNum;
      property State   : Byte         read getState       write setState;
      property OnChange: TNotifyEvent read m_stateChanged write m_stateChanged;
   end;

   TEventCheckNotify = procedure(id : Integer; obj : THandle) of object;
   TEventCheckThread = class(TThread)
   private
      m_ids     : array[0..MAXIMUM_WAIT_OBJECTS - 1 - 1] of Integer;
      m_handles : array[0..MAXIMUM_WAIT_OBJECTS - 1 - 1] of THandle;
      m_notifies: array[0..MAXIMUM_WAIT_OBJECTS - 1 - 1] of TEventCheckNotify;
      m_synced  : array[0..MAXIMUM_WAIT_OBJECTS - 1 - 1] of Boolean;
      m_count   : Integer;

      m_syncObj : THandle;
      m_lock    : TCriticalSection;

      syncId  : Integer;
      syncObj : THandle;
      syncProc: TEventCheckNotify;
      procedure SyncNotify;
   protected
      procedure Execute; override;
   public
      constructor Create(createSuspended : boolean); overload;
      destructor  Destroy; override;
      procedure   Add(id : Integer; handle : THandle; notify: TEventCheckNotify; synced : Boolean);
      procedure   Remove(handle : THandle);
      procedure   Clear;
      procedure   Stop;

      property Count : Integer read m_count;
   end;

   TOverOneScreenMode = ( BeginScreen, EndScreen );
   TSimpleGraph = class
   private
      m_hostCtrl     : TPaintBox;

      m_YCordMax     : Double;
      m_YCordMin     : Double;

      m_xIncByTime    : Double;
      m_plotData      : array of Double;
      m_dataPoint     : array of array of TPoint;

      m_XCordDivRate  : Double;
      m_XCordTimeDiv  : Double;
      m_XCordTimeOffset: Double;

      m_plotCount     : Integer;
      m_shiftCount    : Integer;
      m_dataCachedPerPlot: Integer;
      m_mapIndexPerPlot  : Integer;
      m_pointPerScreen   : Integer;
      m_overOneScreenMode: TOverOneScreenMode;

      procedure HostCtrlPaint(sender: TObject);
      procedure SaveData(const data: array of Double; dataPerPlot: Integer);

      procedure Redraw;
      procedure CalcDrawParams(xIncBySec : Double);
      procedure MapDataPoints;
      procedure DrawOnePlot(canvas :TCanvas; const data : array of TPoint; count: Integer);
   public
      constructor Create(hostCtrl: TPaintBox);
      destructor  Destroy; override;

      procedure Clear;
      procedure Chart(const data: array of Double; plotCount, dataPerPlot: Integer; xIncBySec: Double);
      procedure ScaleXCord(DivValue: Integer);
      procedure Shift(shiftTime: Integer);
      procedure PaintTo(canvas : TCanvas);
      function  GetPlotColor(plot: Integer): TColor;

      property XCordTimeDiv: Double  read m_XCordTimeDiv   write m_XCordTimeDiv;
      property XCordOffset:  Double  read m_XCordTimeOffset write m_XCordTimeOffset;
      property YCordMax:     Double  read m_YCordMax       write m_YCordMax;
      property YCordMin:     Double  read m_YCordMin       write m_YCordMin;
      property OverOneScreenMode: TOverOneScreenMode read m_overOneScreenMode   write m_overOneScreenMode;
   end;

   function LoadJPEGFromResource(resHandle : THandle; name : string):TJPEGImage;

implementation

{ helper method to load JPEG from resource }
function LoadJPEGFromResource(resHandle : THandle; name : string):TJPEGImage;
var
   resStream : TResourceStream;
   jpegImage : TJPEGImage;
begin
   resStream := TResourceStream.Create(resHandle, name, RT_RCDATA );

   jpegImage := TJPEGImage.Create;
   jpegImage.LoadFromStream(resStream);

   resStream.Free;
   Result := jpegImage;
end;

{ TWaveGenerator}
class procedure TWaveGenerator.GetWaveform(
   waveCount: Integer; const wave: array of TWaveParam;
   dataCount: Integer; var data: array of Double);
var
   i, j : Integer;
begin
   if (waveCount > Length(wave)) or (dataCount > Length(data)) then
      raise Exception.Create('Invalid parameter of the waveform');

   for i := 0 to (dataCount div waveCount - 1) do
      for j := 0 to waveCount - 1 do
         data[i * waveCount + j] := GetOnePoint(wave[j], i);
end;

class function TWaveGenerator.GetOnePoint(const wave: TWaveParam; ptIndex: Integer): Double;
var
   amplitude, dcOffset, xPts: double;
begin
   if ptIndex < 0 then raise Exception.Create('Point Index invalid');
   ptIndex := ptIndex mod wave.PtsPerPeriod;

   amplitude := (wave.HiLevel - wave.LoLevel) / 2;
   dcOffset  := (wave.HiLevel + wave.LoLevel) / 2;
   case wave.Style of
   Sine:
      begin
         Result := amplitude * Sin(ptIndex * 2.0 * PI / wave.PtsPerPeriod) + dcOffset;
      end;
   Triangle:
      begin
         xPts := wave.PtsPerPeriod div 4;
         if ptIndex < xPts           then Result := ptIndex / xPts
         else if ptIndex >= 3 * xPts then Result := ptIndex / xPts - 4
         else                             Result := 2 - ptIndex / xPts;

         Result := amplitude * Result + dcOffset;
      end;
   Square:
      begin
         xPts := wave.PtsPerPeriod div 2;
         if ptIndex < xPts then  Result := amplitude
         else                    Result := -amplitude;

         Result := Result +  dcOffset;
      end;
   else
      raise Exception.Create('Invalid wave style of the waveform');
   end;
end;


{TPortPanel}
function TPortPanel.getEditable : Boolean;
begin
   Result := not m_hexEditor.ReadOnly;
end;

procedure TPortPanel.setEditable(value : Boolean);
begin
   m_hexEditor.ReadOnly := not value;
   if m_hexEditor.ReadOnly then m_hexEditor.Color := self.Color
   else m_hexEditor.Color := clWhite;
end;

function TPortPanel.getMask : Byte;
begin
   Result := m_mask;
end;

procedure TPortPanel.setMask(value: Byte);
var
   i     : Integer;
   state : Byte;
begin
   if m_mask = value then exit;

   m_mask := value;
   state  := self.State;
   for i := 0 to 7 do
      if (value and (1 shl i)) = 0  then
      begin
         m_stateBoxes[i].Tag   := STATE_DISABLE_IMG_IDX;
         m_stateBoxes[i].Picture.Graphic := m_stateImages[STATE_DISABLE_IMG_IDX];
      end
      else
      begin
         m_stateBoxes[i].Tag   := (state shr i) and $1;
         m_stateBoxes[i].Picture.Graphic := m_stateImages[m_stateBoxes[i].Tag];
      end;
end;

function TPortPanel.getPortNum : Integer;
begin
   Result := StrToInt(m_portLabel.Caption);
end;

function TPortPanel.getState : Byte;
begin
   try
      Result := Byte(StrToInt('$' + m_hexEditor.Text));
   except
      on EConvertError do Result := 0;
   end;
end;

procedure TPortPanel.setState(value: Byte);
var
   i : Integer;
begin
   for i := 0 to 7 do
     if (m_stateBoxes[i].Tag <> STATE_DISABLE_IMG_IDX) then
     begin
         m_stateBoxes[i].Tag := (value shr i) and 1;
         m_stateBoxes[i].Picture.Graphic := m_stateImages[(value shr i) and 1];
     end;

   m_hexEditor.Text := Format('%.2X', [value and m_mask]);
end;

procedure TPortPanel.HexEditor_KeyDown(sender: TObject; var key: Word; shift: TShiftState);
begin
   if key = VK_RETURN then
      HexEditor_Exit(sender);
end;

procedure TPortPanel.HexEditor_Exit(sender: TObject);
var
   i, value : Integer;
begin
   if (not m_hexEditor.ReadOnly) then
   try
      self.State := Byte(StrToInt('$' + m_hexEditor.Text) and m_mask);
      if Assigned(m_stateChanged) then  m_stateChanged(self);
   except
      on EConvertError do
      begin
         value := 0;
         for i := 0 to 7 do value := value or ((m_stateBoxes[i].Tag and 1) shl i);
         m_hexEditor.Text := Format('%.2X', [value and m_mask]);
      end
   end
end;

procedure TPortPanel.StateBox_Clicked(sender: TObject);
var
   box : TImage;
   ch  : Integer;
   val : Integer;
begin
   box := TImage(sender);
   if (not m_hexEditor.ReadOnly) and (box.Tag <> STATE_DISABLE_IMG_IDX) then
   begin
      box.Tag   := (not box.Tag) and 1;
      box.Picture.Graphic := m_stateImages[box.Tag];

      ch  := StrToInt(MidStr(box.Name, 4, 1));
      val := self.State and (not (1 shl ch));
      val := val or (box.Tag shl ch);
      m_hexEditor.Text := Format('%.2X', [val]);

      if Assigned(m_stateChanged) then  m_stateChanged(self);
   end
end;

constructor TPortPanel.Create(AOwner : TComponent);
var
   i : Integer;
   x : Integer;
begin
   Inherited Create(AOwner);
   self.BevelOuter := bvNone;

   m_mask      := $ff;

   m_portLabel := TLabel.Create(self);
   m_portLabel.SetBounds(0, 8, 20, 24);

   m_highGrpBox := TGroupBox.Create(self);
   m_highGrpBox.SetBounds(25, 0, 122, 36);
   x := 2;
   for i := 7 downto 4 do
   begin
      m_stateBoxes[i] := TImage.Create(m_highGrpBox);
      m_stateBoxes[i].Name := 'box'+ IntToStr(i);
      m_stateBoxes[i].SetBounds(x, 4, 28, 28);
      m_stateBoxes[i].OnClick := StateBox_Clicked;
      m_highGrpBox.InsertControl(m_stateBoxes[i]);
      x := x + 30;
   end;

   m_lowGrpBox := TGroupBox.Create(self);
   m_lowGrpBox.SetBounds(150, 0, 122, 36);
   x := 2;
   for i := 3 downto 0 do
   begin
      m_stateBoxes[i] := TImage.Create(m_lowGrpBox);
      m_stateBoxes[i].Name := 'box'+ IntToStr(i);
      m_stateBoxes[i].SetBounds(x, 4, 28, 28);
      m_stateBoxes[i].OnClick := StateBox_Clicked;
      m_lowGrpBox.InsertControl(m_stateBoxes[i]);
      x := x + 30;
   end;

   m_hexEditor := TEdit.Create(self);
   m_hexEditor.SetBounds(280, 6, 20, 24);
   m_hexEditor.MaxLength := 2;
   m_hexEditor.OnExit    := HexEditor_Exit;
   m_hexEditor.OnKeyDown := HexEditor_KeyDown;

   self.InsertControl(m_portLabel);
   self.InsertControl(m_highGrpBox);
   self.InsertControl(m_lowGrpBox);
   self.InsertControl(m_hexEditor);
end;

function TPortPanel.ShowPortLabel(show : Boolean):Boolean;
begin
   Result := m_portLabel.Visible;
   m_portLabel.Visible := show;
end;

function TPortPanel.ShowHexEditor(show : Boolean):Boolean;
begin
   Result := m_HexEditor.Visible;
   m_HexEditor.Visible := show;
end;

procedure TPortPanel.Initialize(port: Integer; const images: array of TGraphic);
begin
   m_stateImages[0] := images[0];
   m_stateImages[1] := images[1];
   if Length(images) >= 3 then m_stateImages[2] := images[2];

   m_portLabel.Caption := IntToStr(port);

   self.State := $0;
end;

{TEventCheckThread}
constructor TEventCheckThread.Create(createSuspended : boolean);
begin
    Inherited Create(createSuspended);
    m_syncObj := CreateEvent(nil, false, false, nil);
    m_lock    := TCriticalSection.Create;
end;

destructor  TEventCheckThread.Destroy;
begin
   if not Terminated then Stop;
   Inherited Destroy;
end;

procedure TEventCheckThread.Add(id : Integer; handle : THandle; notify: TEventCheckNotify; synced : Boolean);
var
   allowed : Boolean;
begin
   m_lock.Enter;
   allowed := m_count < EVENT_MAX_ALLOWED;
   if allowed then
   begin
      m_ids[m_count]      := id;
      m_handles[m_count]  := handle;
      m_notifies[m_count] := notify;
      m_synced[m_count]   := synced;

      Inc(m_count);
   end;
   m_lock.Leave;

   if allowed then SetEvent(m_syncObj)
   else raise Exception.Create('The event count reaches the upper limit of a thread!');
end;

procedure TEventCheckThread.Remove(handle : THandle);
var
   i   : Integer;
   fOk : Boolean;
begin
   fOk := false;
   m_lock.Enter;
   for i := 0 to m_Count - 1 do
      if m_handles[i] = handle then break;

   if i < m_count then
   begin
      if i <> m_count - 1 then
      begin
         Move(m_ids[i+1], m_ids[i], (m_count - (i+1)) * SizeOf(Integer));
         Move(m_handles[i+1], m_handles[i], (m_count - (i+1)) * SizeOf(THandle));
         Move(m_notifies[i+1], m_notifies[i], (m_count - (i+1)) * SizeOf(TEventCheckNotify));
         Move(m_synced[i+1], m_synced[i], (m_count - (i+1)) * SizeOf(Boolean));
      end;

      Dec(m_count);
      fOk := true;
   end;

   m_lock.Leave;
   if fOk then SetEvent(m_syncObj);
end;

procedure TEventCheckThread.Clear;
begin
   m_lock.Enter;
   m_count := 0;
   m_lock.Leave;
   SetEvent(m_syncObj);
end;

procedure TEventCheckThread.Stop;
begin
   Terminate;
   SetEvent(m_syncObj);
end;

procedure TEventCheckThread.SyncNotify;
begin
   syncProc(syncId, syncObj);
end;

procedure TEventCheckThread.Execute;
var
   handles : array of THandle;
   ids     : array of Integer;
   notifies: array of TEventCheckNotify;
   synced  : array of Boolean;
   count   : Cardinal;
   waitRet : Cardinal;
   evtIndex: Cardinal;
begin
   SetLength(ids,     MAXIMUM_WAIT_OBJECTS);
   SetLength(handles, MAXIMUM_WAIT_OBJECTS);
   SetLength(notifies,MAXIMUM_WAIT_OBJECTS);
   SetLength(synced,  MAXIMUM_WAIT_OBJECTS);

   count      := 1;
   handles[0] := m_syncObj;
   SetEvent(m_syncObj);

   repeat
      waitRet := WaitForMultipleObjects(count, @handles[0], false, INFINITE);
      if waitRet = WAIT_OBJECT_0 then
      begin
         if Terminated then break;
         m_lock.Enter;
         count := m_count + 1;
         if m_count <> 0 then
         begin
            Move(m_ids[0],     ids[1],      m_count * SizeOf(Integer));
            Move(m_handles[0], handles[1],  m_count * SizeOf(THandle));
            Move(m_notifies[0],notifies[1], m_count * SizeOf(TEventCheckNotify));
            Move(m_synced[0],  synced[1],   m_count * SizeOf(Boolean));
         end;
         m_lock.Leave;
      end
      else if waitRet < WAIT_OBJECT_0 + count then
      begin
         evtIndex := waitRet - WAIT_OBJECT_0;
         if not synced[evtIndex] then notifies[evtIndex](ids[evtIndex],handles[evtIndex])
         else
         begin
            syncId   := ids[evtIndex];
            syncObj  := handles[evtIndex];
            syncProc := notifies[evtIndex];
            Synchronize(SyncNotify);
         end
      end;
   until Terminated;
end;


{TSimpleGraph}
constructor TSimpleGraph.Create(hostCtrl: TPaintBox);
begin
   m_hostCtrl := hostCtrl;
   m_overOneScreenMode := BeginScreen;
   m_XCordTimeDiv      := 1000;
   m_hostCtrl.OnPaint  := HostCtrlPaint;
end;

destructor TSimpleGraph.Destroy;
begin

end;

procedure TSimpleGraph.Clear;
begin
   m_dataCachedPerPlot := 0;
   m_shiftCount := 0;
   m_hostCtrl.Invalidate;
end;

procedure TSimpleGraph.Shift(shiftTime: Integer);
begin
  m_XCordTimeOffset := shiftTime;
  Redraw;
end;

procedure TSimpleGraph.ScaleXCord(DivValue: Integer);
begin
   if DivValue = 0 then exit;
   
   m_mapIndexPerPlot := 0;
   m_XCordTimeDiv := DivValue;
   Redraw;
end;

procedure TSimpleGraph.Redraw;
begin
   CalcDrawParams(m_xIncByTime);
   MapDataPoints;
   m_hostCtrl.Invalidate;
end;

procedure TSimpleGraph.CalcDrawParams(xIncBySec : Double);
var
   xcordDivBase : Double;
begin
   m_shiftCount := Trunc(m_XCordTimeOffset / (xIncBySec * 1000));
   xcordDivBase := m_hostCtrl.Width * xIncBySec * 1000 / 10;
   if CompareValue(xIncBySec * 10 * 1000, 1.0) <= 0 then
   begin
      m_shiftCount := m_shiftCount Div 1000;
      xcordDivBase := xcordDivBase * 1000;
   end;
   m_XCordDivRate  := xcordDivBase / m_XCordTimeDiv;
   m_pointPerScreen:= Round(m_hostCtrl.Width * m_XCordTimeDiv / xcordDivBase + 0.4 ) + 1;
end;

procedure TSimpleGraph.MapDataPoints;
var
   yscale : Double;
   count, i, j, seg : Integer;
begin
   yscale  := (m_hostCtrl.Height - 1) / (m_YCordMax - m_YCordMin);

   if m_dataCachedPerPlot - m_shiftCount > m_pointPerScreen then
         count := m_pointPerScreen
   else  count := m_dataCachedPerPlot - m_shiftCount;

   for i := 0 to count - 1 do begin
      seg := (m_mapIndexPerPlot + m_shiftCount + i) * m_plotCount;
      for j := 0 to m_plotCount - 1 do
      begin
         m_dataPoint[j][i].Y := Trunc((m_YCordMax - m_plotData[seg +j]) * yscale);
         m_dataPoint[j][i].X := Round(i * m_XCordDivRate);
      end;
   end; 
end;

procedure TSimpleGraph.HostCtrlPaint(sender: TObject);
begin
   PaintTo(m_hostCtrl.Canvas);
end;

procedure TSimpleGraph.PaintTo(canvas : TCanvas);
var
   ptS, ptE: TPoint;
   step    : Double;
   i, count: Integer;
begin
   canvas.Brush.Color := clBlack;
   canvas.FillRect(m_hostCtrl.ClientRect);
   canvas.Pen.Color := $006400;

   // horizon line
   step :=  (m_hostCtrl.Height - 1.0) / 10;
   for i := 1 to 10 - 1 do
   begin
      ptS.X := 0;
      ptS.Y := Round(i * step);
      ptE.X := m_hostCtrl.Width - 1;
      ptE.Y := ptS.Y;
      canvas.Polyline([ptS, ptE]);
   end;

   // vertical line
   step :=  (m_hostCtrl.Width - 1.0) / 10;
   for i := 1 to 10 - 1 do
   begin
      ptS.X := Round(i * step);
      ptS.Y := 0;
      ptE.X := ptS.X;
      ptE.Y := m_hostCtrl.Height - 1;
      canvas.Polyline([ptS, ptE]);
   end;

   // plots' line
   if m_dataCachedPerPlot > 0 then
   begin
      count := Min(m_dataCachedPerPlot - m_shiftCount, m_pointPerScreen); 
      if count > 0 then
         for i := 0 to m_plotCount - 1 do
         begin
            canvas.Pen.Color := GetPlotColor(i);
            DrawOnePlot(canvas, m_dataPoint[i], count);
         end;
   end;
end;

procedure TSimpleGraph.DrawOnePlot(canvas: TCanvas; const data : array of TPoint; count: Integer);
begin
   if count > 1 then canvas.Polyline(Slice(data, count))
   else              canvas.Polyline([data[0], data[0]]);
end;


procedure TSimpleGraph.Chart(const data: array of Double; plotCount, dataPerPlot: Integer; xIncBySec: Double);
begin
   m_xIncByTime  := xIncBySec;
   if (m_plotData = nil) or (plotCount <> m_plotCount) then
   begin
      m_plotCount := plotCount;
      m_dataCachedPerPlot := 0;
      SetLength(m_plotData,  plotCount * (m_hostCtrl.Width * 4 + 1));
      SetLength(m_dataPoint, plotCount, m_hostCtrl.Width * 4 + 1);
   end;
   
   CalcDrawParams(xIncBySec);
   SaveData(data, dataPerPlot);
   MapDataPoints;
   m_hostCtrl.Invalidate;
end;

procedure TSimpleGraph.SaveData(const data: array of Double; dataPerPlot: Integer);
var
   ovflCount : Integer;
begin
   if dataPerPlot * m_plotCount > Length(m_plotData) then 
      SetLength(m_plotData, (dataPerPlot + 1) * m_plotCount);
   
   if (dataPerPlot >= m_pointPerScreen) then
   begin
      if m_overOneScreenMode = EndScreen then m_mapIndexPerPlot := dataPerPlot - m_pointPerScreen - 1;     
      
      Move(data[0], m_plotData[0], m_plotCount * dataPerPlot * Sizeof(Double));
      m_dataCachedPerPlot := dataPerPlot;
   end else begin
      if m_dataCachedPerPlot + dataPerPlot <= m_pointPerScreen then
      begin
        Move(data, m_plotData[m_dataCachedPerPlot * m_plotCount], m_plotCount * dataPerPlot * Sizeof(Double));
        Inc(m_dataCachedPerPlot, dataPerPlot);
      end else begin
         ovflCount := m_plotCount * (m_dataCachedPerPlot + dataPerPlot - m_pointPerScreen);
         Move(m_plotData[ovflCount], m_plotData[0], (m_plotCount * m_dataCachedPerPlot - ovflCount) * Sizeof(Double));
         Move(data, m_plotData[m_plotCount * m_dataCachedPerPlot - ovflCount], m_plotCount * dataPerPlot * Sizeof(Double));
         m_dataCachedPerPlot := m_pointPerScreen;
         m_mapIndexPerPlot   := 0;
      end
   end
end;



function TSimpleGraph.GetPlotColor(plot: Integer): TColor;
const
   clrs: array[0..15] of TColor = (
      $008CFF, $D30094, $2FFFAD, $7280FA,
      $EBCE87, $B48246, $8FBC8F, $90EE90,
      $ADDEFF, $0045FF, $9314FF, $D355BA,
      $D3D3D3, $8515C7, $E1E4FF, $E6E0B0
    );
begin
    if (plot < 0) or (plot > 15) then Result := clBlack
    else Result := clrs[plot];
end;


end.
