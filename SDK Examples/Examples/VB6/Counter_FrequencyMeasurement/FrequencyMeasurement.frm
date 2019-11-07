VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{1752FF26-D6C9-4BC8-BFE9-7D0CA26DED89}#1.0#0"; "BDaqOcx.dll"
Begin VB.Form FrequencyMeasurement 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Frequency Measurement"
   ClientHeight    =   7140
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   10140
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   476
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   676
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   50
      Left            =   9120
      Top             =   5640
   End
   Begin MSComctlLib.Slider trackBar 
      Height          =   375
      Left            =   3600
      TabIndex        =   7
      Top             =   6600
      Width           =   2055
      _ExtentX        =   3625
      _ExtentY        =   661
      _Version        =   393216
      Min             =   10
      Max             =   1000
      SelStart        =   50
      TickStyle       =   3
      Value           =   50
   End
   Begin VB.CommandButton Stop_button 
      Caption         =   "Stop"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Left            =   8880
      TabIndex        =   3
      Top             =   3000
      Width           =   1095
   End
   Begin VB.CommandButton Pause_button 
      Caption         =   "Pause"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Left            =   8880
      TabIndex        =   2
      Top             =   2280
      Width           =   1095
   End
   Begin VB.CommandButton Start_button 
      Caption         =   "Start"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Left            =   8880
      TabIndex        =   1
      Top             =   1200
      Width           =   1095
   End
   Begin VB.PictureBox GraphPicture 
      BackColor       =   &H80000008&
      Height          =   5895
      Left            =   960
      ScaleHeight     =   5835
      ScaleWidth      =   7755
      TabIndex        =   0
      Top             =   360
      Width           =   7815
   End
   Begin BDaqOcxLibCtl.FreqMeterCtrl FreqMeterCtrl1 
      Left            =   9120
      OleObjectBlob   =   "FrequencyMeasurement.frx":0000
      Top             =   6360
   End
   Begin BDaqOcxLibCtl.FreqMeterCtrl FreqMeterCtrl2 
      Left            =   9480
      OleObjectBlob   =   "FrequencyMeasurement.frx":006E
      Top             =   6360
   End
   Begin VB.Image smaller 
      Height          =   330
      Left            =   360
      Picture         =   "FrequencyMeasurement.frx":00DC
      Top             =   4800
      Width           =   300
   End
   Begin VB.Image larger 
      Height          =   315
      Left            =   360
      Picture         =   "FrequencyMeasurement.frx":0557
      Top             =   4320
      Width           =   345
   End
   Begin VB.Label label_YCoordinateMin 
      Alignment       =   2  'Center
      Caption         =   "0Hz"
      Height          =   255
      Left            =   120
      TabIndex        =   13
      Top             =   6000
      Width           =   855
   End
   Begin VB.Label label_YCoordinateMiddle 
      Alignment       =   2  'Center
      Caption         =   "50KHz"
      Height          =   255
      Left            =   120
      TabIndex        =   12
      Top             =   3120
      Width           =   855
   End
   Begin VB.Label label_YCoordinateMax 
      Alignment       =   2  'Center
      Caption         =   "100KHz"
      Height          =   255
      Left            =   120
      TabIndex        =   11
      Top             =   360
      Width           =   855
   End
   Begin VB.Label fm2_Label 
      BackColor       =   &H00C000C0&
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Left            =   8880
      TabIndex        =   10
      Top             =   4800
      Width           =   1095
   End
   Begin VB.Label fm1_Label 
      BackColor       =   &H000080FF&
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   8880
      TabIndex        =   9
      Top             =   4320
      Width           =   1095
   End
   Begin VB.Label TimeInterval 
      Caption         =   "50 ms"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   5760
      TabIndex        =   8
      Top             =   6720
      Width           =   855
   End
   Begin VB.Label Label1 
      Caption         =   "Sample interval:"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   2160
      TabIndex        =   6
      Top             =   6600
      Width           =   1455
   End
   Begin VB.Label label_XCoordinateMax 
      Alignment       =   1  'Right Justify
      Caption         =   "10 sec"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   7560
      TabIndex        =   5
      Top             =   6360
      Width           =   1215
   End
   Begin VB.Label label_XCoordinateMin 
      Caption         =   "0 sec"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   960
      TabIndex        =   4
      Top             =   6360
      Width           =   735
   End
   Begin VB.Image Image1 
      Height          =   750
      Left            =   7800
      Picture         =   "FrequencyMeasurement.frx":09DF
      Top             =   -120
      Width           =   2400
   End
End
Attribute VB_Name = "FrequencyMeasurement"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'declare the plot Sub/Function implemented by MFC DLL
Private Declare Sub InitializeGraph Lib "SimpleGraphDLL.dll" (ByVal right As Long, ByVal bottom As Long, ByVal hdc As Long)
Private Declare Sub ChartGraph Lib "SimpleGraphDLL.dll" (ByRef plotData As Double, ByVal plotCount As Long, ByVal dataCountPerPlot As Long, ByVal xIncBySec As Double)
Private Declare Sub ClearGraph Lib "SimpleGraphDLL.dll" ()
Private Declare Sub ShiftGraph Lib "SimpleGraphDLL.dll" (ByVal shiftTime As Long)
Private Declare Sub DivGraph Lib "SimpleGraphDLL.dll" (ByVal divTime As Long)
Private Declare Sub SetXTimeOffset Lib "SimpleGraphDLL.dll" (ByVal xTimeValue As Double)
Private Declare Sub SetXTimeDiv Lib "SimpleGraphDLL.dll" (ByVal xTimeValue As Double)
Private Declare Sub SetYRangeMax Lib "SimpleGraphDLL.dll" (ByVal value As Double)
Private Declare Sub SetYRangeMin Lib "SimpleGraphDLL.dll" (ByVal value As Double)
Private Declare Function GetLineColor Lib "SimpleGraphDLL.dll" (ByVal index As Long) As Long
Private Declare Function GetXTimeDiv Lib "SimpleGraphDLL.dll" () As Double

Enum timeUnit
    Microsecond
    Millisecond
    Second
End Enum  'TimeUnit

Enum FrequencyUnit
    Hz
    KHz
    MHz
End Enum 'FrequencyUnit

Private Type RangeYType
    rangeY As MathInterval
    unit As FrequencyUnit
End Type 'RangeYType

Private Const channelCount As Integer = 8
Private frequency(channelCount - 1) As Double    'selected counter channel' frequency.
Private index As Integer
Private isCounterReseted As Boolean
Private rangeYTypeList(7) As RangeYType

Private Sub GetXCordRangeLabels(ranges() As String, ByVal rangeMax As Double, ByVal rangeMin As Double, ByVal unit As timeUnit)
    Dim tUnit As Variant
    tUnit = Array("us", "ms", "Sec")
    
    Dim i As Integer
    i = CInt(unit)
    While i < CInt(timeUnit.Second) And Not rangeMax < 1000
          rangeMax = rangeMax / 1000
          rangeMin = rangeMin / 1000
          i = i + 1
    Wend
    
    ranges(0) = Str(rangeMax) + " " + tUnit(i)
    ranges(1) = Str(rangeMin) + " " + tUnit(i)
End Sub 'GetXCordRangeLabels

Private Sub GetYCordRangeLabels(ranges() As String, ByVal rangeMax As Double, ByVal rangeMin As Double, ByVal unit As FrequencyUnit)
    Dim sUnit As Variant
    sUnit = Array("Hz", "k", "M", "")
    Dim index As Integer
    index = CInt(unit)
    
    If index = -1 Then  'No unit
        index = UBound(sUnit)
    End If
    
    ranges(0) = Str(rangeMax) + sUnit(index)
    ranges(1) = Str(rangeMin) + sUnit(index)
    
    If rangeMax = -rangeMin Then
        ranges(2) = " 0"
    Else
        ranges(2) = ""
    End If
End Sub  'GetYCordRangeLabels

Private Sub InitRangeYTypeList()
    Dim RangeYTp As RangeYType
    Dim i As Long
    i = 10000000
    Dim j As Integer
    j = 0
    While i >= 1
        '10 MHz
        If i >= 1000000 Then
            RangeYTp.rangeY.Max = i / 1000000  'MHz
            RangeYTp.rangeY.Min = 0
            RangeYTp.unit = MHz
            rangeYTypeList(j) = RangeYTp
            j = j + 1
        ElseIf i >= 1000 Then
            RangeYTp.rangeY.Max = i / 1000  'KHz
            RangeYTp.rangeY.Min = 0
            RangeYTp.unit = KHz
            rangeYTypeList(j) = RangeYTp
            j = j + 1
        Else
            RangeYTp.rangeY.Max = i   'Hz
            RangeYTp.rangeY.Min = 0
            RangeYTp.unit = Hz
            rangeYTypeList(j) = RangeYTp
            j = j + 1
        End If
            
        i = i / 10
    Wend
End Sub

Private Sub SetYCord(ByVal index As Integer)
    Dim RangeYTp As RangeYType
    RangeYTp = rangeYTypeList(index)
    
    Dim Y_CordLables(2) As String
    GetYCordRangeLabels Y_CordLables, RangeYTp.rangeY.Max, RangeYTp.rangeY.Min, RangeYTp.unit
    label_YCoordinateMax.Caption = Y_CordLables(0)
    label_YCoordinateMin.Caption = Y_CordLables(1)
    label_YCoordinateMiddle.Caption = Y_CordLables(2)
    
    Dim rate As Long
    rate = 1
    If RangeYTp.unit = KHz Then
        rate = 1000
    Else
        If RangeYTp.unit = MHz Then
            rate = 1000000
        End If
    End If
    
    SetYRangeMax RangeYTp.rangeY.Max * rate
    SetYRangeMin RangeYTp.rangeY.Min * rate
End Sub

Private Sub SetFormTitle()
    Dim devNum1 As Long
    Dim devNum2 As Long
    Dim devDesc1 As String
    Dim devDesc2 As String
    Dim devMode As AccessMode
    Dim modIndex As Long
    FreqMeterCtrl1.getSelectedDevice devNum1, devDesc1, devMode, modIndex
    FreqMeterCtrl2.getSelectedDevice devNum2, devDesc2, devMode, modIndex
    
    If devDesc1 <> "" And devDesc2 = "" Then
        FrequencyMeasurement.Caption = "Frequency Measurement(" + devDesc1 + ")"
    Else
        If devDesc1 = "" And devDesc2 <> "" Then
            FrequencyMeasurement.Caption = "Frequency Measurement(" + devDesc2 + ")"
        Else
            If devNum1 = devNum2 Then
                FrequencyMeasurement.Caption = "Frequency Measurement(" + devDesc1 + ")"
            Else
                FrequencyMeasurement.Caption = "Frequency Measurement(" + devDesc1 + "," + devDesc2 + ")"
            End If
        End If
    End If
End Sub

'refresh the text of listViewItem with frequency value.
Private Sub RefreshListView()
    'control label ,one item indicates a channel which specials with color and value.
    fm1_Label.Caption = Format(frequency(7), "##0.0")
    fm2_Label.Caption = Format(frequency(3), "##0.0")
End Sub

Private Sub Form_Load()
    'The default device of project is demo device, users can choose other devices according to their needs.
    If Not FreqMeterCtrl1.Initialized And Not FreqMeterCtrl2.Initialized Then
        MsgBox "Please select a device with DAQNavi wizard!"
        End
    End If
    
    'set the title of form
    SetFormTitle
    
    'initialize the value of label
    fm1_Label.Caption = "0.0"
    fm2_Label.Caption = "0.0"
    
    'initialize a graph with a picture box control to draw frequency data.(Initialize the Graph of MFC DLL.)
    InitializeGraph GraphPicture.Width, GraphPicture.Height, GraphPicture.hdc
    
    Timer1.Interval = 50
    TimeInterval.Caption = Str(trackBar.value) + "ms"
    
    'set coordinate value.
    SetXTimeDiv 1000
    
    Dim X_rangeLabels(1) As String
    GetXCordRangeLabels X_rangeLabels, 10, 0, Second
    label_XCoordinateMax.Caption = X_rangeLabels(0)
    label_XCoordinateMin.Caption = X_rangeLabels(1)
    
    isCounterReseted = True
    index = 1
    
    'initialize the range of Y coordinate
    InitRangeYTypeList
    
    SetYCord (index)
    ClearGraph
    Start_button.Enabled = True
    Pause_button.Enabled = False
    Stop_button.Enabled = False
End Sub

Private Sub GraphPicture_Paint()
    'Draw the Grid of the PictureBox when the PictureBox be loaded
    ChartGraph frequency(0), 1, 0, 1# * Timer1.Interval / 1000
End Sub

Private Sub larger_Click()
    If index <= 0 Then
        Exit Sub
    End If
    
    index = index - 1
    SetYCord (index)
    ClearGraph
End Sub

Private Sub Pause_button_Click()
    Timer1.Enabled = False
    Pause_button.Enabled = False
    Start_button.Enabled = True
    Stop_button.Enabled = True
    isCounterReseted = False
End Sub

Private Sub smaller_Click()
    If index >= 7 Then
        Exit Sub
    End If
    
    index = index + 1
    SetYCord (index)
    ClearGraph
End Sub

Private Sub Start_button_Click()
    If isCounterReseted = True Then
        If FreqMeterCtrl1.Initialized And FreqMeterCtrl1.Channel <> -1 Then
            FreqMeterCtrl1.Enabled = True
        End If
        
        If FreqMeterCtrl2.Initialized And FreqMeterCtrl2.Channel <> -1 Then
            FreqMeterCtrl2.Enabled = True
        End If
        
        Stop_button.Enabled = True
    End If
    
    Timer1.Enabled = True
    Start_button.Enabled = False
    Pause_button.Enabled = True
End Sub

Private Sub Stop_button_Click()
    If FreqMeterCtrl1.Enabled = True Then
        FreqMeterCtrl1.Enabled = False
    End If
    
    If FreqMeterCtrl2.Enabled = True Then
        FreqMeterCtrl2.Enabled = False
    End If
    
    Timer1.Enabled = False
    Stop_button.Enabled = False
    Pause_button.Enabled = False
    Start_button.Enabled = True
    isCounterReseted = True
    ClearGraph
        
End Sub

Private Sub Timer1_Timer()
    If FreqMeterCtrl1.Initialized And FreqMeterCtrl1.Channel <> -1 Then
        frequency(7) = FreqMeterCtrl1.value
    Else
        frequency(7) = 0#
    End If
    
    If FreqMeterCtrl2.Initialized And FreqMeterCtrl2.Channel <> -1 Then
        frequency(3) = FreqMeterCtrl2.value
    Else
        frequency(3) = 0#
    End If
    
    RefreshListView
    ChartGraph frequency(0), channelCount, 1, 1# * Timer1.Interval / 1000
End Sub

Private Sub trackBar_Scroll()
    Timer1.Interval = trackBar.value
    TimeInterval.Caption = Str(trackBar.value) + "ms"
    ClearGraph
End Sub
