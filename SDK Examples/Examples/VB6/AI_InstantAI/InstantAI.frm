VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Object = "{1752FF26-D6C9-4BC8-BFE9-7D0CA26DED89}#1.0#0"; "BDaqOcx.dll"
Begin VB.Form InstantAI 
   BackColor       =   &H8000000D&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "InstantAI"
   ClientHeight    =   8145
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   11700
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   543
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   780
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.ImageList ImageList1 
      Left            =   0
      Top             =   2160
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   25
      ImageHeight     =   25
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   1
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "InstantAI.frx":0000
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.PictureBox Picture1 
      BackColor       =   &H80000008&
      Height          =   5295
      Left            =   840
      ScaleHeight     =   349
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   669
      TabIndex        =   20
      Top             =   600
      Width           =   10095
      Begin VB.Label Label4 
         Caption         =   "Label4"
         Height          =   15
         Left            =   0
         TabIndex        =   21
         Top             =   5280
         Width           =   135
      End
   End
   Begin VB.PictureBox PictureBar 
      AutoRedraw      =   -1  'True
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   1560
      ScaleHeight     =   975
      ScaleWidth      =   9135
      TabIndex        =   19
      Top             =   3360
      Visible         =   0   'False
      Width           =   9135
   End
   Begin MSComctlLib.ListView ListView 
      Height          =   855
      Left            =   600
      TabIndex        =   11
      Top             =   6240
      Width           =   8655
      _ExtentX        =   15266
      _ExtentY        =   1508
      View            =   3
      LabelWrap       =   -1  'True
      HideSelection   =   0   'False
      HideColumnHeaders=   -1  'True
      FlatScrollBar   =   -1  'True
      GridLines       =   -1  'True
      PictureAlignment=   5
      _Version        =   393217
      SmallIcons      =   "ImageList1"
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      NumItems        =   0
   End
   Begin VB.Timer timer_getData 
      Enabled         =   0   'False
      Interval        =   200
      Left            =   0
      Top             =   4680
   End
   Begin MSComctlLib.Slider Slider 
      Height          =   375
      Left            =   9360
      TabIndex        =   10
      Top             =   6720
      Width           =   1575
      _ExtentX        =   2778
      _ExtentY        =   661
      _Version        =   393216
      SmallChange     =   10
      Min             =   10
      Max             =   1000
      SelStart        =   200
      TickStyle       =   3
      TickFrequency   =   100
      Value           =   200
   End
   Begin VB.TextBox textBox1 
      BackColor       =   &H8000000F&
      Height          =   315
      Left            =   10080
      Locked          =   -1  'True
      TabIndex        =   8
      Text            =   "     200"
      Top             =   6360
      Width           =   615
   End
   Begin VB.ComboBox comboBox_chanCount 
      Height          =   315
      Left            =   4320
      Style           =   2  'Dropdown List
      TabIndex        =   6
      Top             =   7320
      Width           =   1215
   End
   Begin VB.ComboBox comboBox_chanStart 
      Height          =   315
      Left            =   1680
      Style           =   2  'Dropdown List
      TabIndex        =   4
      Top             =   7320
      Width           =   1215
   End
   Begin VB.CommandButton button_stop 
      Caption         =   "Stop"
      Enabled         =   0   'False
      Height          =   375
      Left            =   9480
      TabIndex        =   2
      Top             =   7320
      Width           =   975
   End
   Begin VB.CommandButton button_pause 
      Caption         =   "Pause"
      Enabled         =   0   'False
      Height          =   375
      Left            =   8280
      TabIndex        =   1
      Top             =   7320
      Width           =   975
   End
   Begin VB.CommandButton button_start 
      Caption         =   "Start"
      Height          =   375
      Left            =   7080
      TabIndex        =   0
      Top             =   7320
      Width           =   975
   End
   Begin BDaqOcxLibCtl.InstantAiCtrl InstantAiCtrl1 
      Left            =   120
      OleObjectBlob   =   "InstantAI.frx":02F3
      Top             =   3600
   End
   Begin VB.Label label_XCoordinateMax 
      Alignment       =   1  'Right Justify
      Caption         =   "10 Sec"
      Height          =   255
      Left            =   10080
      TabIndex        =   18
      Top             =   5880
      Width           =   855
   End
   Begin VB.Label label_XCoordinateMin 
      Caption         =   "0 Sec"
      Height          =   255
      Left            =   840
      TabIndex        =   17
      Top             =   5880
      Width           =   735
   End
   Begin VB.Label label_YCoordinateMin 
      Alignment       =   2  'Center
      Caption         =   "-5V"
      Height          =   255
      Left            =   480
      TabIndex        =   16
      Top             =   5640
      Width           =   375
   End
   Begin VB.Label label_YCoordinateMiddle 
      Alignment       =   2  'Center
      Caption         =   "0V"
      Height          =   255
      Left            =   600
      TabIndex        =   15
      Top             =   3120
      Width           =   255
   End
   Begin VB.Label label_YCoordinateMax 
      Alignment       =   2  'Center
      Caption         =   "5V"
      Height          =   255
      Left            =   480
      TabIndex        =   14
      Top             =   600
      Width           =   375
   End
   Begin VB.Label Label3 
      Caption         =   "8"
      Height          =   255
      Left            =   360
      TabIndex        =   13
      Top             =   6840
      Width           =   135
   End
   Begin VB.Label Label2 
      Caption         =   "0"
      Height          =   255
      Left            =   360
      TabIndex        =   12
      Top             =   6240
      Width           =   135
   End
   Begin VB.Label Label1 
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
      Left            =   10800
      TabIndex        =   9
      Top             =   6360
      Width           =   375
   End
   Begin VB.Label sample_interval 
      Caption         =   "Sample interval:"
      Height          =   495
      Left            =   9360
      TabIndex        =   7
      Top             =   6240
      Width           =   615
   End
   Begin VB.Label label_Count 
      Caption         =   "ChanCount:"
      Height          =   375
      Left            =   3360
      TabIndex        =   5
      Top             =   7320
      Width           =   975
   End
   Begin VB.Label label_chanStart 
      Caption         =   "ChanStart:"
      Height          =   375
      Left            =   840
      TabIndex        =   3
      Top             =   7320
      Width           =   735
   End
   Begin VB.Image Image 
      Height          =   8160
      Left            =   0
      Picture         =   "InstantAI.frx":0429
      Stretch         =   -1  'True
      Top             =   0
      Width           =   11700
   End
End
Attribute VB_Name = "InstantAI"
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

Private Const CHANNEL_COUNT_MAX As Integer = 16
Private dataScaled(CHANNEL_COUNT_MAX - 1) As Double
Private chanCountSet As Integer
Private chanCountMax As Integer
Private firstItem As ListItem
Private secondItem As ListItem

Enum TimeUnit
    Microsecond
    Millisecond
    Second
End Enum  'TimeUnit

Private Sub GetXCordRangeLabels(ranges() As String, ByVal rangeMax As Double, ByVal rangeMin As Double, ByVal unit As TimeUnit)
    Dim tUnit As Variant
    tUnit = Array("us", "ms", "Sec")
    
    Dim i As Integer
    i = CInt(unit)
    While i < CInt(TimeUnit.Second) And Not rangeMax < 1000
          rangeMax = rangeMax / 1000
          rangeMin = rangeMin / 1000
          i = i + 1
    Wend
    
    ranges(0) = Str(rangeMax) + " " + tUnit(i)
    ranges(1) = Str(rangeMin) + " " + tUnit(i)
    
End Sub 'GetXCordRangeLabels

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
    SetXTimeDiv 1000
    
    Dim X_rangeLabels(1) As String
    GetXCordRangeLabels X_rangeLabels, 10, 0, TimeUnit.Second
    label_XCoordinateMax.Caption = X_rangeLabels(0)
    label_XCoordinateMin.Caption = X_rangeLabels(1)
    
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
    'initial the listview
    'add the columnHeaders for every column
    ListView.ListItems.Clear
    
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
    PictureBar.Height = ImageList1.ImageHeight * 2 * 1.01
    
    PictureBar.ScaleMode = vbUser
    PictureBar.ScaleHeight = 2
    PictureBar.ScaleWidth = 8
    
    'set the PictureBar's image as the ListView's background
    ListView.Picture = PictureBar.Image
    
    'initial the subItems of firstItem
    Dim j As Integer
    For j = 0 To 7
        If j < chanCountSet Then
            firstItem.SubItems(j + 1) = Format(dataScaled(j), "##0.0000")
            PictureBar.Line (j, 0)-(j + 1, 1), GetLineColor(j), BF
        Else
            firstItem.SubItems(j + 1) = " "
            PictureBar.Line (j, 0)-(j + 1, 1), vbWhite, BF
        End If
    Next j
    
    'initial the subItems of secondItem
    For j = 8 To 15
        If j < chanCountSet Then
           secondItem.SubItems(j - 7) = Format(dataScaled(j), "##0.0000")
           PictureBar.Line (j - 8, 1)-(j - 7, 2), GetLineColor(j), BF
        Else
           secondItem.SubItems(j - 7) = " "
           PictureBar.Line (j - 8, 1)-(j - 7, 2), vbWhite, BF
        End If
    Next j
            
End Sub

Private Sub RefreshListView()
    Dim i As Integer
    For i = 0 To chanCountSet - 1
        If i < 8 Then
            firstItem.SubItems(i + 1) = Format(dataScaled(i), "##0.0000")
        Else
            secondItem.SubItems((i + 1) Mod 8) = Format(dataScaled(i), "##0.0000")
        End If
    Next i
            
End Sub

Private Sub HandleError(ByVal err As BDaqOcxLibCtl.ErrorCode)
    Dim utility As BDaqUtility
    Dim errorMessage As String
    Dim res As ErrorCode
        
    Set utility = New BDaqUtility
        
    res = utility.EnumToString("ErrorCode", err, errorMessage)
    
    If err <> ErrorCode.Success Then
       MsgBox "Sorry ! Some errors happened, the error code is: " & errorMessage, , "InstantAI"
    End If
End Sub

Private Sub button_pause_Click()
    timer_getData.Enabled = False
    button_pause.Enabled = False
    button_start.Enabled = True
End Sub

Private Sub button_start_Click()
    timer_getData.Enabled = True
    button_start.Enabled = False
    button_pause.Enabled = True
    button_stop.Enabled = True
End Sub

Private Sub button_stop_Click()
    timer_getData.Enabled = False
    button_start.Enabled = True
    button_pause.Enabled = False
    button_stop.Enabled = False
    ClearGraph
End Sub

Private Sub comboBox_chanCount_Click()
    ClearGraph
    chanCountSet = comboBox_chanCount.ListIndex + 1
    InitListView
End Sub

Private Sub Form_Load()
    'The default device of project is demo device, users can choose other devices according to their needs.
    If Not InstantAiCtrl1.Initialized Then
        MsgBox "Please select a device with DAQNavi wizard!", , "InstantAI"
        End
    End If
    
    'set title of the form.
    Dim devNum As Long
    Dim devDesc As String
    Dim devMode As AccessMode
    Dim modIndex As Long
    InstantAiCtrl1.getSelectedDevice devNum, devDesc, devMode, modIndex
    InstantAI.Caption = "Instant AI(" + devDesc + ")"
    
    chanCountMax = InstantAiCtrl1.Features.ChannelCountMax
    
    button_start.Enabled = True
    button_pause.Enabled = False
    button_stop.Enabled = False
    
    'initialize a graph with a picture box control to draw Ai data.(Initialize the Graph of MFC DLL.)
    InitializeGraph Picture1.Width, Picture1.Height, Picture1.hdc
    
    'initialize a timer which drive the data acquisition.
    timer_getData.Interval = Slider.value
    
    textBox1.Text = Slider.value
    
    'Add combo Box  to select start channel and channel count
    Dim chanCount As Integer
    If InstantAiCtrl1.ChannelCount <= CHANNEL_COUNT_MAX Then
       chanCount = InstantAiCtrl1.ChannelCount
    Else
       chanCount = CHANNEL_COUNT_MAX
    End If
    
    Dim i As Integer
    For i = 0 To chanCount - 1
        comboBox_chanStart.AddItem i
        comboBox_chanCount.AddItem i + 1
    Next i
    
    comboBox_chanStart.ListIndex = 0
    comboBox_chanCount.ListIndex = 2
    
    ConfigureGraph
    InitListView
    
End Sub

Private Sub Picture1_Paint()
    'Draw the Grid of the PictureBox when the PictureBox be loaded
    ChartGraph dataScaled(0), chanCountSet, 0, 1# * Slider.value / 1000
End Sub

Private Sub Slider_Scroll()
    ClearGraph
    timer_getData.Interval = Slider.value
    textBox1.Text = Slider.value
End Sub

Private Sub timer_getData_Timer()
    Dim err As BDaqOcxLibCtl.ErrorCode
    err = InstantAiCtrl1.ReadChannels(comboBox_chanStart.ListIndex, chanCountSet, Null, dataScaled)
    
    If err <> Success Then
        Call HandleError(err)
        timer_getData.Enabled = False
    End If
    
    'draw the data to the PictureBox
     ChartGraph dataScaled(0), chanCountSet, 1, 1# * Slider.value / 1000
     
    RefreshListView
              
End Sub
