VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{1752FF26-D6C9-4BC8-BFE9-7D0CA26DED89}#1.0#0"; "BDaqOcx.dll"
Begin VB.Form SnapCounter 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "SnapCounter"
   ClientHeight    =   4800
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   7905
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4800
   ScaleWidth      =   7905
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   50
      Left            =   1560
      Top             =   120
   End
   Begin VB.TextBox txtSnapCount 
      Height          =   380
      Left            =   1560
      Locked          =   -1  'True
      TabIndex        =   8
      Top             =   4080
      Width           =   1215
   End
   Begin VB.Frame Frame2 
      Height          =   3855
      Left            =   3360
      TabIndex        =   1
      Top             =   720
      Width           =   4335
      Begin VB.CommandButton btnStop 
         Caption         =   "Stop"
         Height          =   375
         Left            =   2880
         TabIndex        =   12
         Top             =   2160
         Width           =   1215
      End
      Begin VB.CommandButton btnStart 
         Caption         =   "Start"
         Height          =   375
         Left            =   2880
         TabIndex        =   11
         Top             =   1200
         Width           =   1215
      End
      Begin MSComctlLib.ListView CounterValueList 
         Height          =   2655
         Left            =   240
         TabIndex        =   10
         Top             =   960
         Width           =   2295
         _ExtentX        =   4048
         _ExtentY        =   4683
         View            =   3
         Arrange         =   1
         LabelWrap       =   -1  'True
         HideSelection   =   -1  'True
         HideColumnHeaders=   -1  'True
         FlatScrollBar   =   -1  'True
         _Version        =   393217
         ForeColor       =   -2147483640
         BackColor       =   -2147483643
         BorderStyle     =   1
         Appearance      =   1
         NumItems        =   0
      End
      Begin VB.TextBox txtCounterValue 
         Height          =   385
         Left            =   240
         TabIndex        =   9
         Top             =   360
         Width           =   2295
      End
   End
   Begin VB.Frame Frame1 
      Height          =   3255
      Left            =   240
      TabIndex        =   0
      Top             =   720
      Width           =   2895
      Begin VB.TextBox txtTimeInterval 
         Enabled         =   0   'False
         Height          =   380
         Left            =   1440
         TabIndex        =   5
         Top             =   2400
         Width           =   1095
      End
      Begin VB.ListBox listSnapSource 
         Height          =   1620
         ItemData        =   "SnapCounter.frx":0000
         Left            =   240
         List            =   "SnapCounter.frx":0002
         MultiSelect     =   1  'Simple
         TabIndex        =   3
         Top             =   600
         Width           =   2295
      End
      Begin VB.Label Label3 
         Caption         =   "(From 0.02Hz to 50kHz)"
         Height          =   255
         Left            =   600
         TabIndex        =   6
         Top             =   2880
         Width           =   1935
      End
      Begin VB.Label Label2 
         Caption         =   "Time interval:"
         Height          =   255
         Left            =   360
         TabIndex        =   4
         Top             =   2400
         Width           =   975
      End
      Begin VB.Label Label1 
         Caption         =   "Snap source:"
         Height          =   255
         Left            =   240
         TabIndex        =   2
         Top             =   240
         Width           =   1215
      End
   End
   Begin BDaqOcxLibCtl.UdCounterCtrl UdCounterCtrl1 
      Left            =   2400
      OleObjectBlob   =   "SnapCounter.frx":0004
      Top             =   120
   End
   Begin VB.Label Label5 
      Caption         =   "Snap Count:"
      Height          =   255
      Left            =   480
      TabIndex        =   13
      Top             =   4200
      Width           =   975
   End
   Begin BDaqOcxLibCtl.TimerPulseCtrl TimerPulseCtrl1 
      Left            =   3120
      OleObjectBlob   =   "SnapCounter.frx":008E
      Top             =   120
   End
   Begin VB.Image Image1 
      Height          =   4725
      Left            =   0
      Picture         =   "SnapCounter.frx":00F4
      Top             =   0
      Width           =   7890
   End
   Begin VB.Label Label4 
      Caption         =   "Snap count:"
      Height          =   255
      Left            =   600
      TabIndex        =   7
      Top             =   4080
      Width           =   975
   End
End
Attribute VB_Name = "SnapCounter"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private m_isTimerUsing  As Boolean
Private snapEventSources() As Long
Private selectedSources() As Long

Private snapCount As Integer

Private Sub HandleError(ByVal err As BDaqOcxLibCtl.ErrorCode)
    Dim utility As BDaqUtility
    Dim errorMessage As String
    Dim res As ErrorCode
        
    Set utility = New BDaqUtility
        
    res = utility.EnumToString("ErrorCode", err, errorMessage)
    
    If err <> BDaqOcxLibCtl.ErrorCode.Success Then
       MsgBox "Sorry ! There are some errors happened, the error code is: " & errorMessage, , "Warning Information"
    End If
End Sub

Private Sub InitListView()
    'add the columnHeaders for every column
    CounterValueList.ColumnHeaders.Add , , , 0
    CounterValueList.ColumnHeaders.Add , , , CounterValueList.Width
End Sub

Private Sub EventIDtoString(ByVal id As Long, ByRef str As String)
    Select Case id
    
    Case 406   'EvtUdIndex0
        str = "Index0"
    Case 407   'EvtUdIndex1
        str = "Index1"
    Case 408   'EvtUdIndex2
        str = "Index2"
    Case 409   'EvtUdIndex3
        str = "Index3"
    Case 410   'EvtUdIndex4
        str = "Index4"
    Case 411   'EvtUdIndex5
        str = "Index5"
    Case 412   'EvtUdIndex6
        str = "Index6"
    Case 413   'EvtUdIndex7
        str = "Index7"
        
    Case 390   'EvtCntTimer0
        str = "Timer0"
    Case 391   'EvtCntTimer1
        str = "Timer1"
    Case 392   'EvtCntTimer2
        str = "Timer2"
    Case 393   'EvtCntTimer3
        str = "Timer3"
    Case 394   'EvtCntTimer4
        str = "Timer4"
    Case 395   'EvtCntTimer5
        str = "Timer5"
    Case 396   'EvtCntTimer6
        str = "Timer6"
    Case 397   'EvtCntTimer7
        str = "Timer7"
    
    Case 12    'EvtDiintChannel000
        str = "DiintChannel0"
    Case 13    'EvtDiintChannel001
        str = "DiintChannel1"
    Case 14    'EvtDiintChannel002
        str = "DiintChannel2"
    Case 15    'EvtDiintChannel003
        str = "DiintChannel3"
    Case 16    'EvtDiintChannel004
        str = "DiintChannel4"
    Case 17    'EvtDiintChannel005
        str = "DiintChannel5"
    Case 18    'EvtDiintChannel006
        str = "DiintChannel6"
    Case 19    'EvtDiintChannel007
        str = "DiintChannel7"
    Case Else
        str = ""
    End Select
End Sub

Private Sub CheckTimerUsingParam(ByVal id As Long, ByRef timerChan As Integer, ByRef isTimerUsing As Boolean)
    If id >= 390 And id <= 397 Then
        timerChan = id - 390
    End If
    
    If timerChan <> -1 Then
        isTimerUsing = True
    End If
End Sub

Private Sub ConfiguratePanel()
    'for reset value
    Dim snapSrcs() As Long
    snapSrcs = UdCounterCtrl1.Features.snapEventSources
    snapEventSources = UdCounterCtrl1.Features.snapEventSources
    Dim srcCount As Integer
    srcCount = UBound(snapSrcs) - LBound(snapSrcs) + 1
    Dim srcSrc As String
    
    listSnapSource.Clear
    
    Dim i As Integer
    For i = 0 To srcCount - 1
        EventIDtoString snapSrcs(i), srcSrc
        listSnapSource.AddItem srcSrc
    Next
End Sub

Private Sub btnStart_Click()
    CounterValueList.ListItems.Clear
    txtCounterValue.Text = "0"
    txtSnapCount.Text = "0"
    snapCount = 0
    
    m_isTimerUsing = False
    
    Dim timerChan As Integer
    timerChan = -1
    
    Dim count As Integer
    count = listSnapSource.SelCount
    Dim i As Integer
    For i = 0 To count - 1
        CheckTimerUsingParam selectedSources(i), timerChan, m_isTimerUsing
        UdCounterCtrl1.SnapStart selectedSources(i)
    Next
    
    If m_isTimerUsing Then
        Dim frequency As Double
        frequency = CDbl(txtTimeInterval.Text)
         
        TimerPulseCtrl1.Channel = timerChan
        TimerPulseCtrl1.frequency = frequency
        TimerPulseCtrl1.Enabled = True

    End If
    
    'Start Snap Counter function.
    UdCounterCtrl1.Enabled = True
    Timer1.Enabled = True
    
    btnStart.Enabled = False
    btnStop.Enabled = True
    listSnapSource.Enabled = False
End Sub

Private Sub btnStop_Click()
    Timer1.Enabled = False
    
    btnStart.Enabled = True
    btnStop.Enabled = False
    listSnapSource.Enabled = True
    
    'stop timer pulse
    If m_isTimerUsing Then
        TimerPulseCtrl1.Enabled = False
    End If
    
    'stop snap function
    Dim count As Integer
    count = listSnapSource.SelCount
    Dim i As Integer
    For i = 0 To count - 1
        UdCounterCtrl1.SnapStop selectedSources(i)
    Next
    
    'stop updown counter
    UdCounterCtrl1.Enabled = False
End Sub

Private Sub Form_Load()
    'The default device of project is demo device, users can choose other devices according to their needs.
    If Not UdCounterCtrl1.Initialized Then
        MsgBox "Please select a device with DAQNavi wizard!", , "Warning Information"
        End
    End If
    
    'set title of the form
    Dim devNum As Long
    Dim devDesc As String
    Dim devMode As AccessMode
    Dim modIndex As Long
    UdCounterCtrl1.getSelectedDevice devNum, devDesc, devMode, modIndex
    SnapCounter.Caption = "Snap Counter(" + devDesc + ")"
    
    'initial the form
    txtTimeInterval.Text = "5"
    m_isTimerUsing = False
    snapCount = 0
    CounterValueList.ListItems.Clear
    
    ConfiguratePanel
    InitListView
    
    btnStart.Enabled = True
    btnStop.Enabled = False
    
    
End Sub

Private Sub listSnapSource_Click()
    Dim i As Integer
    Dim j As Integer
    j = 0
    
    Dim timerChan As Integer
    timerChan = -1
    Dim isTimerUsing As Boolean
    isTimerUsing = False
    
    Dim count As Integer
    count = UBound(snapEventSources) - LBound(snapEventSources) + 1
    
    If listSnapSource.SelCount > 0 Then
        ReDim selectedSources(listSnapSource.SelCount - 1) As Long
    End If
    
    For i = 0 To count - 1
        If listSnapSource.Selected(i) Then
            selectedSources(j) = snapEventSources(i)
            j = j + 1
            
            CheckTimerUsingParam snapEventSources(i), timerChan, isTimerUsing
            
            If isTimerUsing Then
             txtTimeInterval.Enabled = True
             Exit For
            End If
        End If
    Next
    
    If i = count Then
        txtTimeInterval.Enabled = False
    End If
End Sub

Private Sub Timer1_Timer()
    UdCounterCtrl1.Enabled = True
    
    Dim cntrValue As Long
    cntrValue = UdCounterCtrl1.Value
    
    txtCounterValue.Text = "0x" + Hex(strValue)
End Sub

Private Sub UdCounterCtrl1_UdCntrEvent(ByVal srcID As Long, ByVal Length As Long, PortData() As Long)
    Dim snapValue As String
    Dim srcIDStr As String
    Dim source As String
    
    snapCount = snapCount + 1
    
    txtSnapCount.Text = str(snapCount)
    
    EventIDtoString srcID, srcIDStr
    
    snapValue = "CntrValue: "
    Dim i As Integer
    For i = 0 To Length - 1
        snapValue = snapValue & Hex(PortData(i)) & " "
    Next
    CounterValueList.ListItems.Add
    CounterValueList.ListItems(CounterValueList.ListItems.count).ListSubItems.Add
    CounterValueList.ListItems(CounterValueList.ListItems.count).ListSubItems(1).Text = snapValue
    
    source = "SrcID: " & srcIDStr
    CounterValueList.ListItems.Add
    CounterValueList.ListItems(CounterValueList.ListItems.count).ListSubItems.Add
    CounterValueList.ListItems(CounterValueList.ListItems.count).ListSubItems(1).Text = source
    
    If CounterValueList.ListItems.count > 40 Then
        CounterValueList.ListItems.Remove (1)
    End If
End Sub
