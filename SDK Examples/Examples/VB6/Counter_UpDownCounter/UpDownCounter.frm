VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{1752FF26-D6C9-4BC8-BFE9-7D0CA26DED89}#1.0#0"; "BDaqOcx.dll"
Begin VB.Form UpDownCounter 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "UpDownCounter"
   ClientHeight    =   4770
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   7890
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4770
   ScaleWidth      =   7890
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   50
      Left            =   2040
      Top             =   120
   End
   Begin VB.Frame Frame3 
      Caption         =   "Index Reset"
      Height          =   2295
      Left            =   240
      TabIndex        =   9
      Top             =   2280
      Width           =   2775
      Begin VB.TextBox txtResetTimes 
         Enabled         =   0   'False
         Height          =   380
         Left            =   1200
         TabIndex        =   14
         Top             =   1680
         Width           =   1335
      End
      Begin VB.OptionButton radFinite 
         Caption         =   "Finite"
         Height          =   255
         Left            =   240
         TabIndex        =   12
         Top             =   1320
         Width           =   1575
      End
      Begin VB.OptionButton raInfinite 
         Caption         =   "Infinite"
         Height          =   255
         Left            =   240
         TabIndex        =   11
         Top             =   840
         Width           =   1575
      End
      Begin VB.OptionButton radDisable 
         Caption         =   "Disable"
         Height          =   255
         Left            =   240
         TabIndex        =   10
         Top             =   360
         Width           =   1575
      End
      Begin VB.Label Label2 
         Caption         =   "Reset Times:"
         Height          =   255
         Left            =   240
         TabIndex        =   13
         Top             =   1800
         Width           =   975
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Reset Value"
      Height          =   1455
      Left            =   240
      TabIndex        =   5
      Top             =   720
      Width           =   2775
      Begin VB.TextBox txtResetValue 
         Enabled         =   0   'False
         Height          =   380
         Left            =   1080
         TabIndex        =   8
         Top             =   840
         Width           =   1455
      End
      Begin VB.ComboBox cmbResetValue 
         Height          =   315
         Left            =   1080
         TabIndex        =   7
         Top             =   360
         Width           =   1575
      End
      Begin VB.Label Label1 
         Caption         =   "Reset Value:"
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   360
         Width           =   975
      End
   End
   Begin VB.Frame Frame2 
      Height          =   3855
      Left            =   3240
      TabIndex        =   0
      Top             =   720
      Width           =   4335
      Begin VB.CommandButton btnValReset 
         Caption         =   "ValueReset"
         Height          =   375
         Left            =   2880
         TabIndex        =   15
         Top             =   1320
         Width           =   1215
      End
      Begin MSComctlLib.ListView CounterValueList 
         Height          =   2655
         Left            =   240
         TabIndex        =   4
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
         TabIndex        =   3
         Top             =   360
         Width           =   2295
      End
      Begin VB.CommandButton btnStart 
         Caption         =   "Start"
         Height          =   375
         Left            =   2880
         TabIndex        =   2
         Top             =   600
         Width           =   1215
      End
      Begin VB.CommandButton btnStop 
         Caption         =   "Stop"
         Height          =   375
         Left            =   2880
         TabIndex        =   1
         Top             =   2160
         Width           =   1215
      End
   End
   Begin BDaqOcxLibCtl.UdCounterCtrl UdCounterCtrl1 
      Left            =   2880
      OleObjectBlob   =   "UpDownCounter.frx":0000
      Top             =   120
   End
   Begin VB.Image Image1 
      Height          =   4725
      Left            =   0
      Picture         =   "UpDownCounter.frx":008A
      Top             =   0
      Width           =   7890
   End
End
Attribute VB_Name = "UpDownCounter"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private cntrValue As Long

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

Private Sub ConfiguratePanel()
    cmbResetValue.Clear
    
    Dim resetValues() As Long
    resetValues = UdCounterCtrl1.Features.InitailValues
    
    Dim count As Integer
    count = UBound(resetValues) - LBound(resetValues) + 1
    
    Dim i As Integer
    i = 0
    Dim valueStr As String
    
    For i = 0 To count - 1
        If resetValues(i) <> -1 Then
            valueStr = "0x" & Right(Str(Hex(resetValues(i))), 8)
            cmbResetValue.AddItem valueStr
        Else
            cmbResetValue.AddItem "-1"
        End If
    Next
    
    Dim resetValue As Long
    resetValue = UdCounterCtrl1.InitialValue
    
    If 0 = resetValue Then
        cmbResetValue.ListIndex = 0
    Else
        cmbResetValue.ListIndex = 1
    End If
    
    'for using edit text as reset value
    txtResetValue.Text = Str(Hex(0))
    
    'reset times
    txtResetTimes.Text = "0"
    txtResetTimes.Enabled = False
    
    'radio button for reset value.
    Dim resetTimesByIndex As Integer
    resetTimesByIndex = UdCounterCtrl1.resetTimesByIndex
    If 0 = resetTimesByIndex Then
        radDisable.Value = True
        raInfinite.Value = False
        radFinite.Value = False
    ElseIf -1 = resetTimesByIndex Then
        radDisable.Value = False
        raInfinite.Value = True
        radFinite.Value = False
    Else
        radDisable.Value = False
        raInfinite.Value = False
        radFinite.Value = True

        txtResetTimes.Text = Str(resetTimesByIndex)
        txtResetTimes.Enabled = True
    End If
End Sub

Private Sub btnStart_Click()
    txtCounterValue.Text = "0"
    
    If btnStart.Caption = "Start" Then
        CounterValueList.ListItems.Clear
        
        'Set reset times for counter value
        Dim resetTimes As Integer
        resetTimes = 0
        
        If radFinite.Value Then
            resetTimes = CInt(txtResetTimes.Text)
        ElseIf raInfinite.Value Then
            resetTimes = -1
        ElseIf radDisable.Value Then
            resetTimes = 0
        End If
        
        UdCounterCtrl1.resetTimesByIndex = resetTimes
        
        'set reset value
        Dim resetValues() As Long
        resetValues = UdCounterCtrl1.Features.InitailValues
        Dim resetValue As Long
        resetValue = resetValues(cmbResetValue.ListIndex)
        
        If resetValue = -1 Then
            resetValue = Val(txtResetValue.Text)
        End If
        
        UdCounterCtrl1.InitialValue = resetValue
        
        'Start UpDown Counter function.
        UdCounterCtrl1.Enabled = True
        
        Timer1.Enabled = True
        
        btnStop.Enabled = True
        btnValReset.Enabled = True
        cmbResetValue.Enabled = False
        radDisable.Enabled = False
        radFinite.Enabled = False
        raInfinite.Enabled = False
        
        btnStart.Caption = "Latch"
    Else
        If CounterValueList.ListItems.count > 12 Then
            CounterValueList.ListItems.Remove 1
        End If
        
        CounterValueList.ListItems.Add
        CounterValueList.ListItems(CounterValueList.ListItems.count).ListSubItems.Add
        
        CounterValueList.ListItems(CounterValueList.ListItems.count).ListSubItems(1).Text = "0x" + Hex(cntrValue)
    End If
End Sub

Private Sub btnStop_Click()
    'Stop the user Timer
    Timer1.Enabled = False
    
    btnStart.Caption = "Start"
    btnStop.Enabled = False
    btnValReset.Enabled = False
    
    cmbResetValue.Enabled = True
    radDisable.Enabled = True
    radFinite.Enabled = True
    raInfinite.Enabled = True
    
    UdCounterCtrl1.Enabled = False
End Sub

Private Sub btnValReset_Click()
    UdCounterCtrl1.ValueReset
End Sub

Private Sub cmbResetValue_Click()
    Dim resetValues() As Long
    resetValues = UdCounterCtrl1.Features.InitailValues
    Dim resetValue As Long
    resetValue = resetValues(cmbResetValue.ListIndex)
    
    If resetValue = -1 Then
        txtResetValue.Enabled = True
    Else
        txtResetValue.Enabled = False
    End If
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
    UpDownCounter.Caption = "UpDown Counter(" + devDesc + ")"
    
    CounterValueList.ListItems.Clear
    
    ConfiguratePanel
    InitListView
    
    btnStart.Enabled = True
    btnStop.Enabled = False
    btnValReset.Enabled = False
End Sub

Private Sub radDisable_Click()
    If radDisable.Value Then
        txtResetTimes.Enabled = False
    End If
End Sub

Private Sub radFinite_Click()
    If radFinite.Value Then
         txtResetTimes.Enabled = True
         txtResetTimes.Text = Str(UdCounterCtrl1.resetTimesByIndex)
    End If
End Sub

Private Sub raInfinite_Click()
    If raInfinite.Value Then
        txtResetTimes.Enabled = False
    End If
End Sub

Private Sub Timer1_Timer()
    UdCounterCtrl1.Enabled = True
    
    cntrValue = UdCounterCtrl1.Value
    
    txtCounterValue.Text = "0x" + Hex(cntrValue)
End Sub
