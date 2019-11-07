VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Object = "{1752FF26-D6C9-4BC8-BFE9-7D0CA26DED89}#1.0#0"; "BDaqOcx.dll"
Begin VB.Form StreamingAI_TDtr 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Streaming AI with Trigger Delay to Start"
   ClientHeight    =   7665
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   11520
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   511
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   768
   StartUpPosition =   3  'Windows Default
   Begin VB.PictureBox Picture1 
      BackColor       =   &H80000008&
      Height          =   5100
      Left            =   960
      ScaleHeight     =   5040
      ScaleWidth      =   9840
      TabIndex        =   13
      Top             =   600
      Width           =   9900
      Begin VB.Label Label1 
         Caption         =   "Label1"
         Height          =   15
         Left            =   0
         TabIndex        =   15
         Top             =   5040
         Width           =   135
      End
      Begin VB.Label Label2 
         Caption         =   "Label2"
         Height          =   15
         Left            =   0
         TabIndex        =   14
         Top             =   5040
         Width           =   135
      End
   End
   Begin VB.PictureBox PictureBar 
      AutoRedraw      =   -1  'True
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      Height          =   735
      Left            =   2280
      ScaleHeight     =   735
      ScaleWidth      =   5295
      TabIndex        =   12
      Top             =   2760
      Visible         =   0   'False
      Width           =   5295
   End
   Begin MSComctlLib.ImageList ImageList1 
      Left            =   1680
      Top             =   1560
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   21
      ImageHeight     =   21
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   1
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "StreamingAI_TDtr.frx":0000
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.ListView ListView 
      Height          =   675
      Left            =   2280
      TabIndex        =   11
      Top             =   5880
      Width           =   5280
      _ExtentX        =   9313
      _ExtentY        =   1191
      View            =   3
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      HideColumnHeaders=   -1  'True
      FlatScrollBar   =   -1  'True
      GridLines       =   -1  'True
      _Version        =   393217
      SmallIcons      =   "ImageList1"
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin MSComctlLib.Slider trackBar_div 
      Height          =   375
      Left            =   8280
      TabIndex        =   10
      Top             =   6120
      Width           =   2415
      _ExtentX        =   4260
      _ExtentY        =   661
      _Version        =   393216
      Min             =   10
      Max             =   1000
      SelStart        =   100
      TickStyle       =   3
      TickFrequency   =   100
      Value           =   100
   End
   Begin VB.CommandButton button_stop 
      Caption         =   "Stop"
      Height          =   375
      Left            =   9720
      TabIndex        =   9
      Top             =   6960
      Width           =   1095
   End
   Begin VB.CommandButton button_pause 
      Caption         =   "Pause"
      Height          =   375
      Left            =   8400
      TabIndex        =   8
      Top             =   6960
      Width           =   1095
   End
   Begin VB.CommandButton button_start 
      Caption         =   "Start"
      Height          =   375
      Left            =   7080
      TabIndex        =   7
      Top             =   6960
      Width           =   1095
   End
   Begin BDaqOcxLibCtl.BufferedAiCtrl BufferedAiCtrl1 
      Left            =   840
      OleObjectBlob   =   "StreamingAI_TDtr.frx":02F3
      Top             =   6600
   End
   Begin VB.Label Label4 
      Caption         =   "Div:"
      Height          =   375
      Left            =   7920
      TabIndex        =   6
      Top             =   6120
      Width           =   375
   End
   Begin VB.Label Label3 
      Caption         =   "Color of channels:"
      Height          =   375
      Left            =   960
      TabIndex        =   5
      Top             =   6120
      Width           =   1455
   End
   Begin VB.Label label_XCoordinateMax 
      Alignment       =   1  'Right Justify
      Caption         =   "12 Sec"
      Height          =   255
      Left            =   9840
      TabIndex        =   4
      Top             =   5760
      Width           =   975
   End
   Begin VB.Label label_XCoordinateMin 
      Caption         =   "0 Sec"
      Height          =   255
      Left            =   960
      TabIndex        =   3
      Top             =   5760
      Width           =   735
   End
   Begin VB.Label label_YCoordinateMin 
      Alignment       =   2  'Center
      Caption         =   "-5V"
      Height          =   255
      Left            =   600
      TabIndex        =   2
      Top             =   5400
      Width           =   375
   End
   Begin VB.Label label_YCoordinateMiddle 
      Alignment       =   2  'Center
      Caption         =   "0V"
      Height          =   375
      Left            =   600
      TabIndex        =   1
      Top             =   2880
      Width           =   375
   End
   Begin VB.Label label_YCoordinateMax 
      Alignment       =   2  'Center
      Caption         =   "5V"
      Height          =   375
      Left            =   600
      TabIndex        =   0
      Top             =   600
      Width           =   375
   End
   Begin VB.Image Image1 
      Height          =   7680
      Left            =   0
      Picture         =   "StreamingAI_TDtr.frx":045C
      Stretch         =   -1  'True
      Top             =   0
      Width           =   11460
   End
End
Attribute VB_Name = "StreamingAI_TDtr"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

'declare the plot Sub/Function implemented by MFC DLL.
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

Private firstItem As ListItem
Private secondItem As ListItem
Private dataScaled() As Double
Private isFirstOverRun As Boolean

Enum timeUnit
    Microsecond
    Millisecond
    Second
End Enum  'TimeUnit

Private divideValue As Double
Private tUnit As timeUnit

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

Private Sub SetXCordRangeLabels()
    Dim X_rangeLabels(1) As String
    GetXCordRangeLabels X_rangeLabels, CLng(trackBar_div.value) * 10, 0, tUnit
    label_XCoordinateMax.Caption = X_rangeLabels(0)
    label_XCoordinateMin.Caption = X_rangeLabels(1)
End Sub  'SetXCordRangeLabels

Private Sub GetYCordRangeLabels(ranges() As String, ByVal rangeMax As Double, ByVal rangeMin As Double, ByVal unit As ValueUnit)
    Dim sUnit As Variant
    sUnit = Array("kV", "V", "mV", "uV", "KA", "A", "mA", "uA", "C", "")
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

Private Sub HandleError(ByVal err As BDaqOcxLibCtl.ErrorCode)
    Dim utility As BDaqUtility
    Dim errorMessage As String
    Dim res As ErrorCode
        
    Set utility = New BDaqUtility
        
    res = utility.EnumToString("ErrorCode", err, errorMessage)
    
    If err <> BDaqOcxLibCtl.ErrorCode.Success Then
       MsgBox "Sorry ! There are some errors happened, the error code is: " & errorMessage, , "StreamingAI_TDtr"
    End If
End Sub

Private Sub BufferedAiCtrl1_CacheOverflow(ByVal Offset As Long, ByVal Count As Long)
    MsgBox "BufferedAiCacheOverflow"
End Sub

Private Sub BufferedAiCtrl1_DataReady(ByVal Offset As Long, ByVal Count As Long)
    Dim err As ErrorCode
    err = ErrorCode.Success
    
    'The BufferedAiCtrl has been disposed.
    If BufferedAiCtrl1.State = Idle Then
        End
    End If
    
    Dim chCount As Integer
    chCount = BufferedAiCtrl1.ScanChannel.ChannelCount
    
    'get data
    err = BufferedAiCtrl1.GetData(Count, dataScaled)
    If err <> ErrorCode.Success Then
        HandleError err
        End
    End If
    
    'draw the data to the PictureBox
    ChartGraph dataScaled(0), BufferedAiCtrl1.ScanChannel.ChannelCount, Count / BufferedAiCtrl1.ScanChannel.ChannelCount, 1# / BufferedAiCtrl1.ConvertClock.Rate
    
End Sub

Private Sub BufferedAiCtrl1_Overrun(ByVal Offset As Long, ByVal Count As Long)
    If isFirstOverRun Then
        MsgBox "BufferedAiOverrun"
        isFirstOverRun = False
    End If
End Sub

Private Sub ConfigureGraph()
    
     'ms
    If BufferedAiCtrl1.ConvertClock.Rate > 10 * 1000 Then
        divideValue = (1000# * 100 * Picture1.Width / BufferedAiCtrl1.ConvertClock.Rate)
        trackBar_div.value = CInt(Fix(divideValue))
        tUnit = timeUnit.Microsecond
    Else
        'set the time unit
        tUnit = timeUnit.Millisecond
        divideValue = (1# * 100 * Picture1.Width / BufferedAiCtrl1.ConvertClock.Rate)
        trackBar_div.value = CInt(Fix(divideValue))
    End If
    
    'set coordinate value.
    trackBar_div.Max = 32767  'the max. value of Integer in vb.
    trackBar_div.Min = 0
    
    trackBar_div.Max = 4 * trackBar_div.value
    trackBar_div.Min = CInt(1# * trackBar_div.value / 10)
    If trackBar_div.Min = 0 Then
        trackBar_div.Min = 1
    End If
    
    SetXTimeDiv divideValue
    SetXTimeOffset 0
    SetXCordRangeLabels
    
    Dim unit As ValueUnit
    unit = -1  'Don't show unit in the label.
    Dim Y_CordLables(3) As String
    GetYCordRangeLabels Y_CordLables, 10, -10, unit
    label_YCoordinateMax.Caption = Y_CordLables(0)
    label_YCoordinateMin.Caption = Y_CordLables(1)
    label_YCoordinateMiddle.Caption = Y_CordLables(2)
    
    SetYRangeMax 10   'the value range of channels is -10~+10V here
    SetYRangeMin -10
    
    ClearGraph
    
End Sub

Private Sub InitListView()
    'listview control ,one grid indicates a channel which specials with color.
    
    ListView.ListItems.Clear
    
    'add the columnHeaders for every column
    Dim i As Integer
    ListView.ColumnHeaders.Add , , , 0
    For i = 0 To 7
        ListView.ColumnHeaders.Add , , , ListView.Width / 8
    Next i
    
    Set firstItem = ListView.ListItems.Add(, , "")
    Set secondItem = ListView.ListItems.Add(, , "")
    
    'use imgList to modify the height of listView grids.
    ListView.SmallIcons = ImageList1
    
    'set the PictureBarWidth and PictureBarHeight to show the background
    PictureBar.Width = ListView.Width
    PictureBar.Height = ImageList1.ImageHeight * 2
    
    PictureBar.ScaleMode = vbUser
    PictureBar.ScaleHeight = 2
    PictureBar.ScaleWidth = 8
    
    'set the PictureBar's image as the ListView's background
    ListView.Picture = PictureBar.Image
    
    'set the color of channels
    Dim j As Integer
    For j = 0 To 7
        If j < BufferedAiCtrl1.ScanChannel.ChannelCount Then
            PictureBar.Line (j, 0)-(j + 1, 1), GetLineColor(j), BF
        Else
            PictureBar.Line (j, 0)-(j + 1, 1), vbWhite, BF
        End If
    Next j
    
    For j = 8 To 15
        If j < BufferedAiCtrl1.ScanChannel.ChannelCount Then
           PictureBar.Line (j - 8, 1)-(j - 7, 2), GetLineColor(j), BF
        Else
           PictureBar.Line (j - 8, 1)-(j - 7, 2), vbWhite, BF
        End If
    Next j
    
    
End Sub

Private Sub button_pause_Click()
    Dim err As ErrorCode
    err = ErrorCode.Success
    err = BufferedAiCtrl1.Stop
    
    If err <> ErrorCode.Success Then
        HandleError err
        End
    End If
    
    button_start.Enabled = True
    button_pause.Enabled = False
End Sub

Private Sub button_start_Click()
    Dim err As ErrorCode
    err = ErrorCode.Success
    Dim delayCountPerChanMax As Long
    delayCountPerChanMax = 0
    
    If BufferedAiCtrl1.Features.TriggerSupported Then
        Dim range As MathInterval
        range = BufferedAiCtrl1.Features.TriggerDelayRange
        
        If BufferedAiCtrl1.Trigger.Source <> SignalDrop.SignalNone Then
            If BufferedAiCtrl1.Features.SamplingMethod = SamplingMethod.EqualTimeSwitch Then
                delayCountPerChanMax = CLng(range.Max / BufferedAiCtrl1.ScanChannel.ChannelCount)
            Else
                delayCountPerChanMax = CLng(range.Max)
            End If
            
            If BufferedAiCtrl1.Trigger.DelayCount > delayCountPerChanMax Or BufferedAiCtrl1.Trigger.DelayCount < range.Min Then
                Dim errMessage As String
                errMessage = "      parameter error: " & vbCr & vbLf & "               DelayCount is within " & Str(range.Min) & "-" & Str(delayCountPerChanMax) & "."
                MsgBox errMessage
                Exit Sub
            End If
        End If
    End If
                
    ConfigureGraph
    
    err = BufferedAiCtrl1.Start
    If err <> ErrorCode.Success Then
        HandleError err
        End
    End If
    
    button_start.Enabled = False
    button_pause.Enabled = True
    button_stop.Enabled = True
End Sub

Private Sub button_stop_Click()
    Dim err As ErrorCode
    err = ErrorCode.Success
    err = BufferedAiCtrl1.Stop
    
    If err <> ErrorCode.Success Then
        HandleError err
        End
    End If
    
    button_start.Enabled = True
    button_pause.Enabled = False
    button_stop.Enabled = False
    
    ClearGraph
End Sub

Private Sub Form_Load()
    'The default device of project is demo device, users can choose other devices according to their needs.
    If Not BufferedAiCtrl1.Initialized Then
        MsgBox "Please select a device in control property!", , "StreamingAI_TDtr"
        End
    End If
    
    'set title of the form
    Dim devNum As Long
    Dim devDesc As String
    Dim devMode As AccessMode
    Dim modIndex As Long
    BufferedAiCtrl1.getSelectedDevice devNum, devDesc, devMode, modIndex
    StreamingAI_TDtr.Caption = "Streaming AI with Trigger Delay to Start(" + devDesc + ")"
    
    'initialize the isFirstOverRun
    isFirstOverRun = True
    
    button_start.Enabled = True
    button_pause.Enabled = False
    button_stop.Enabled = False
     
    BufferedAiCtrl1.Streaming = True 'specify the running mode: streaming-buffered
    
    Dim err As ErrorCode
    err = ErrorCode.Success
    err = BufferedAiCtrl1.Prepare
    If err <> ErrorCode.Success Then
        HandleError err
        End
    End If
    
    'redefine the array of dataScaled
    ReDim dataScaled(BufferedAiCtrl1.BufferCapacity - 1)
    
    'initialize a graph with a picture box control to draw Ai data.(Initialize the Graph of MFC DLL.)
    InitializeGraph Picture1.Width, Picture1.Height, Picture1.hdc
    
       If BufferedAiCtrl1.Features.TriggerSupported Then
        BufferedAiCtrl1.Trigger.Action = DelayToStart
    End If
    
    If BufferedAiCtrl1.Features.Trigger1Supported Then
        BufferedAiCtrl1.Trigger1.Action = DelayToStart
    End If
    
    ConfigureGraph
    InitListView
End Sub

Private Sub Picture1_Paint()

 'Draw the Grid of the PictureBox when the PictureBox be loaded
  ChartGraph dataScaled(0), BufferedAiCtrl1.ScanChannel.ChannelCount, 0, 1# / BufferedAiCtrl1.ConvertClock.Rate
End Sub

Private Sub trackBar_div_Scroll()

    DivGraph trackBar_div.value
    SetXCordRangeLabels
End Sub
