VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Object = "{1752FF26-D6C9-4BC8-BFE9-7D0CA26DED89}#1.0#0"; "BDaqOcx.dll"
Begin VB.Form AsynchronousOneBufferedAI 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Asynchronous One Buffered AI"
   ClientHeight    =   8025
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   11400
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   535
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   760
   StartUpPosition =   3  'Windows Default
   Begin VB.PictureBox Picture1 
      BackColor       =   &H80000008&
      Height          =   5100
      Left            =   840
      ScaleHeight     =   5040
      ScaleWidth      =   9840
      TabIndex        =   17
      Top             =   600
      Width           =   9900
   End
   Begin VB.PictureBox PictureBar 
      AutoRedraw      =   -1  'True
      BackColor       =   &H80000008&
      BorderStyle     =   0  'None
      Height          =   675
      Left            =   1920
      ScaleHeight     =   675
      ScaleMode       =   0  'User
      ScaleWidth      =   7935
      TabIndex        =   16
      Top             =   3000
      Visible         =   0   'False
      Width           =   7935
   End
   Begin MSComctlLib.ImageList ImageList1 
      Left            =   2160
      Top             =   1680
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
            Picture         =   "AsynchronousOneBufferedAI.frx":0000
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.CommandButton button_getData 
      Caption         =   "Get Data"
      Height          =   375
      Left            =   8400
      TabIndex        =   15
      Top             =   7440
      Width           =   1215
   End
   Begin MSComctlLib.Slider trackBar_div 
      Height          =   375
      Left            =   8280
      TabIndex        =   14
      Top             =   6840
      Width           =   2535
      _ExtentX        =   4471
      _ExtentY        =   661
      _Version        =   393216
      Min             =   10
      Max             =   1000
      SelStart        =   100
      TickFrequency   =   100
      Value           =   100
   End
   Begin VB.TextBox textBox_div 
      Alignment       =   1  'Right Justify
      Height          =   315
      Left            =   6600
      Locked          =   -1  'True
      TabIndex        =   12
      Top             =   6840
      Width           =   1215
   End
   Begin MSComctlLib.Slider trackBar_shift 
      Height          =   375
      Left            =   3120
      TabIndex        =   10
      Top             =   6840
      Width           =   2775
      _ExtentX        =   4895
      _ExtentY        =   661
      _Version        =   393216
      Max             =   1000
      TickFrequency   =   100
   End
   Begin VB.TextBox textBox_shift 
      Alignment       =   1  'Right Justify
      Height          =   315
      Left            =   1440
      Locked          =   -1  'True
      TabIndex        =   8
      Text            =   "10"
      Top             =   6840
      Width           =   1215
   End
   Begin MSComctlLib.ListView ListView 
      Height          =   675
      Left            =   2160
      TabIndex        =   6
      Top             =   6000
      Width           =   7935
      _ExtentX        =   13996
      _ExtentY        =   1191
      View            =   3
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      HideColumnHeaders=   -1  'True
      FlatScrollBar   =   -1  'True
      GridLines       =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      Appearance      =   1
      NumItems        =   0
   End
   Begin BDaqOcxLibCtl.BufferedAiCtrl BufferedAiCtrl1 
      Left            =   360
      OleObjectBlob   =   "AsynchronousOneBufferedAI.frx":02F3
      Top             =   6480
   End
   Begin VB.Label label_divide 
      Alignment       =   2  'Center
      Caption         =   "ms"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   7800
      TabIndex        =   13
      Top             =   6840
      Width           =   375
   End
   Begin VB.Label Label4 
      Caption         =   "Div:"
      Height          =   375
      Left            =   6120
      TabIndex        =   11
      Top             =   6840
      Width           =   375
   End
   Begin VB.Label label_shift 
      Alignment       =   2  'Center
      Caption         =   "ms"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2640
      TabIndex        =   9
      Top             =   6840
      Width           =   375
   End
   Begin VB.Label Label2 
      Caption         =   "Shift:"
      Height          =   255
      Left            =   960
      TabIndex        =   7
      Top             =   6840
      Width           =   495
   End
   Begin VB.Label Label1 
      Caption         =   "Color of channels:"
      Height          =   255
      Left            =   840
      TabIndex        =   5
      Top             =   6240
      Width           =   1335
   End
   Begin VB.Label label_XCoordinateMax 
      Alignment       =   1  'Right Justify
      Caption         =   "12 Sec"
      Height          =   255
      Left            =   9600
      TabIndex        =   4
      Top             =   5760
      Width           =   1095
   End
   Begin VB.Label label_XCoordinateMin 
      Caption         =   "0 Sec"
      Height          =   255
      Left            =   840
      TabIndex        =   3
      Top             =   5760
      Width           =   1095
   End
   Begin VB.Label label_YCoordinateMin 
      Alignment       =   2  'Center
      Caption         =   "-5V"
      Height          =   375
      Left            =   480
      TabIndex        =   2
      Top             =   5400
      Width           =   375
   End
   Begin VB.Label label_YCoordinateMiddle 
      Alignment       =   2  'Center
      Caption         =   "0V"
      Height          =   375
      Left            =   480
      TabIndex        =   1
      Top             =   3000
      Width           =   375
   End
   Begin VB.Label label_YCoordinateMax 
      Alignment       =   2  'Center
      Caption         =   "5V"
      Height          =   375
      Left            =   480
      TabIndex        =   0
      Top             =   600
      Width           =   375
   End
   Begin VB.Image Image1 
      Height          =   8040
      Left            =   0
      Picture         =   "AsynchronousOneBufferedAI.frx":045C
      Stretch         =   -1  'True
      Top             =   0
      Width           =   11340
   End
End
Attribute VB_Name = "AsynchronousOneBufferedAI"
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

Enum timeUnit
    Microsecond
    Millisecond
    Second
End Enum  'TimeUnit

Private tUnit As timeUnit

Private Sub HandleError(ByVal err As BDaqOcxLibCtl.ErrorCode)
    Dim utility As BDaqUtility
    Dim errorMessage As String
    Dim res As ErrorCode
        
    Set utility = New BDaqUtility
        
    res = utility.EnumToString("ErrorCode", err, errorMessage)
    
    If err <> BDaqOcxLibCtl.ErrorCode.Success Then
       MsgBox "Sorry ! There are some errors happened, the error code is: " & errorMessage, , "AsynchronousOneBufferedAI"
    End If
End Sub

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

Private Sub SetXCord()
    SetXTimeDiv trackBar_div.value
    SetXTimeOffset trackBar_shift.value
    Dim rangeMax As Double
    rangeMax = GetXTimeDiv * 10 + trackBar_shift.value
    Dim X_rangeLabels(2) As String
    GetXCordRangeLabels X_rangeLabels, rangeMax, trackBar_shift.value, tUnit
    label_XCoordinateMax.Caption = X_rangeLabels(0)
    label_XCoordinateMin.Caption = X_rangeLabels(1)
End Sub  'SetXCord

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

Private Sub ConfigureGraph()
    If BufferedAiCtrl1.ConvertClock.Rate > 10000 Then
        trackBar_div.value = CInt(Fix(((100# * 1000 * Picture1.Width) / BufferedAiCtrl1.ConvertClock.Rate)))
        tUnit = Microsecond
        trackBar_shift.Max = (Fix(1000 * 1000# * BufferedAiCtrl1.ScanChannel.Samples / BufferedAiCtrl1.ConvertClock.Rate)) 'us
        trackBar_shift.Min = 0
        label_divide.Caption = "us"
        label_shift.Caption = "us"
    Else
        trackBar_shift.Max = CInt(Fix(1000# * BufferedAiCtrl1.ScanChannel.Samples / BufferedAiCtrl1.ConvertClock.Rate))  'ms
        trackBar_shift.Min = 0
        trackBar_shift.value = 0
        textBox_shift.Text = trackBar_shift.value
        tUnit = Millisecond
    
        '1 pixel to 1 data point. How much time plotting pictureBox.Size.Width / 10(panelLineCount) data points requires in ms.
        trackBar_div.value = CInt(Fix(((100# * Picture1.Width) / BufferedAiCtrl1.ConvertClock.Rate)))
    End If
    
    trackBar_div.Max = 32767  'the max. value of Integer in vb.
    trackBar_div.Min = 0
    
    textBox_div.Text = trackBar_div.value
    trackBar_div.Max = 4 * trackBar_div.value  '1 pixel to 4 data points
    trackBar_div.Min = CInt(1# * trackBar_div.value / 10)   ' 10 pixel to 1 data points
    If trackBar_div.Min = 0 Then
        trackBar_div.Min = 1
    End If
    
    SetXCord
    
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
    PictureBar.Height = ImageList1.ImageHeight * 2 * 1.08
    
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

Private Sub BufferedAiCtrl1_Stopped(ByVal Offset As Long, ByVal Count As Long)
    Dim err As ErrorCode
    err = Success
    
    'The BufferedAiCtrl has been disposed.
    If BufferedAiCtrl1.State = Idle Then
        End
    End If
    
    'get data
    err = BufferedAiCtrl1.GetData(Count, dataScaled)
    If err <> Success Then
        button_getData.Enabled = True
        HandleError err
        End
    End If
    
     'draw the data to the PictureBox
    ChartGraph dataScaled(0), BufferedAiCtrl1.ScanChannel.ChannelCount, BufferedAiCtrl1.ScanChannel.Samples, 1# / BufferedAiCtrl1.ConvertClock.Rate
    
    button_getData.Enabled = True
End Sub

Private Sub button_getData_Click()
    Dim err As ErrorCode
    err = Success
    
    ConfigureGraph
    
    err = BufferedAiCtrl1.Start
    
    If err <> Success Then
        HandleError err
        End
    End If
    
    trackBar_shift.Enabled = True
    trackBar_div.Enabled = True
    button_getData.Enabled = False
    
End Sub

Private Sub Form_Load()
    'The default device of project is demo device, users can choose other devices according to their needs.
    If Not BufferedAiCtrl1.Initialized Then
        MsgBox "Please select a device with DAQNavi wizard!", , "AsynchronousOneBufferedAI"
        End
    End If
    
    'set title of the form
    Dim devNum As Long
    Dim devDesc As String
    Dim devMode As AccessMode
    Dim modIndex As Long
    BufferedAiCtrl1.getSelectedDevice devNum, devDesc, devMode, modIndex
    AsynchronousOneBufferedAI.Caption = "Asynchronous One Buffered AI(" + devDesc + ")"
    
    BufferedAiCtrl1.Streaming = False 'specify the running mode: One-buffered
    
    'initialize a graph with a picture box control to draw Ai data.(Initialize the Graph of MFC DLL.)
    InitializeGraph Picture1.Width, Picture1.Height, Picture1.hdc
    
    Dim err As ErrorCode
    err = ErrorCode.Success
    err = BufferedAiCtrl1.Prepare
    If err <> ErrorCode.Success Then
        HandleError err
        End
    End If
    
    'redefine the array of dataScaled
    ReDim dataScaled(BufferedAiCtrl1.BufferCapacity - 1)
    
    trackBar_shift.Enabled = False
    trackBar_div.Enabled = False
    
    ConfigureGraph
    InitListView
End Sub

Private Sub Picture1_Paint()
    'Draw the Grid of the PictureBox when the PictureBox be loaded
    ChartGraph dataScaled(0), BufferedAiCtrl1.ScanChannel.ChannelCount, 0, 1# / BufferedAiCtrl1.ConvertClock.Rate
End Sub

Private Sub trackBar_div_Scroll()
    SetXCord
    textBox_div.Text = trackBar_div.value
    DivGraph trackBar_div.value
End Sub

Private Sub trackBar_shift_Scroll()
    SetXCord
    textBox_shift.Text = trackBar_shift.value
    ShiftGraph trackBar_shift.value
End Sub
