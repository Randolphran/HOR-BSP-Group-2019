VERSION 5.00
Object = "{1752FF26-D6C9-4BC8-BFE9-7D0CA26DED89}#1.0#0"; "BDaqOcx.dll"
Begin VB.Form ContinueCompare 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "ContinueCompare"
   ClientHeight    =   5250
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   7920
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5250
   ScaleWidth      =   7920
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   50
      Left            =   1800
      Top             =   120
   End
   Begin VB.TextBox txtEndCount 
      Height          =   380
      Left            =   6120
      Locked          =   -1  'True
      TabIndex        =   39
      Top             =   4680
      Width           =   1455
   End
   Begin VB.TextBox txtPMCount 
      Height          =   380
      Left            =   2280
      Locked          =   -1  'True
      TabIndex        =   37
      Top             =   4680
      Width           =   1575
   End
   Begin VB.OptionButton radInterval 
      Caption         =   "Compare interval"
      Height          =   255
      Left            =   3480
      TabIndex        =   4
      Top             =   480
      Width           =   1575
   End
   Begin VB.OptionButton radTable 
      Caption         =   "Compare table"
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   480
      Width           =   1455
   End
   Begin VB.Frame Frame3 
      Height          =   2895
      Left            =   6000
      TabIndex        =   2
      Top             =   720
      Width           =   1695
      Begin VB.TextBox txtCounterValue 
         Height          =   380
         Left            =   120
         TabIndex        =   7
         Top             =   360
         Width           =   1455
      End
      Begin VB.CommandButton btnStop 
         Caption         =   "Stop"
         Height          =   375
         Left            =   240
         TabIndex        =   6
         Top             =   2040
         Width           =   1215
      End
      Begin VB.CommandButton btnStart 
         Caption         =   "Start"
         Height          =   375
         Left            =   240
         TabIndex        =   5
         Top             =   1200
         Width           =   1215
      End
   End
   Begin VB.Frame Frame2 
      Height          =   3855
      Left            =   3360
      TabIndex        =   1
      Top             =   720
      Width           =   2415
      Begin VB.Frame Frame7 
         Caption         =   "Interval 2"
         Height          =   1695
         Left            =   120
         TabIndex        =   29
         Top             =   2040
         Width           =   2175
         Begin VB.TextBox txtInt2FirstValue 
            Height          =   375
            Left            =   960
            TabIndex        =   32
            Top             =   240
            Width           =   1095
         End
         Begin VB.TextBox txtInt2Increment 
            Height          =   375
            Left            =   960
            TabIndex        =   31
            Top             =   720
            Width           =   1095
         End
         Begin VB.TextBox txtInt2Count 
            Height          =   375
            Left            =   960
            TabIndex        =   30
            Top             =   1200
            Width           =   1095
         End
         Begin VB.Label Label12 
            Caption         =   "FirstValue:"
            Height          =   255
            Left            =   120
            TabIndex        =   35
            Top             =   240
            Width           =   855
         End
         Begin VB.Label Label11 
            Caption         =   "Increment:"
            Height          =   255
            Left            =   120
            TabIndex        =   34
            Top             =   720
            Width           =   855
         End
         Begin VB.Label Label10 
            Caption         =   "Count:"
            Height          =   255
            Left            =   120
            TabIndex        =   33
            Top             =   1200
            Width           =   855
         End
      End
      Begin VB.Frame Frame6 
         Caption         =   "Interval 1"
         Height          =   1695
         Left            =   120
         TabIndex        =   22
         Top             =   240
         Width           =   2175
         Begin VB.TextBox txtInt1Count 
            Height          =   375
            Left            =   960
            TabIndex        =   28
            Top             =   1200
            Width           =   1095
         End
         Begin VB.TextBox txtInt1Increment 
            Height          =   375
            Left            =   960
            TabIndex        =   26
            Top             =   720
            Width           =   1095
         End
         Begin VB.TextBox txtInt1FirstValue 
            Height          =   375
            Left            =   960
            TabIndex        =   24
            Top             =   240
            Width           =   1095
         End
         Begin VB.Label Label9 
            Caption         =   "Count:"
            Height          =   255
            Left            =   120
            TabIndex        =   27
            Top             =   1200
            Width           =   855
         End
         Begin VB.Label Label8 
            Caption         =   "Increment:"
            Height          =   255
            Left            =   120
            TabIndex        =   25
            Top             =   720
            Width           =   855
         End
         Begin VB.Label Label7 
            Caption         =   "FirstValue:"
            Height          =   255
            Left            =   120
            TabIndex        =   23
            Top             =   240
            Width           =   855
         End
      End
   End
   Begin VB.Frame Frame1 
      Height          =   3855
      Left            =   120
      TabIndex        =   0
      Top             =   720
      Width           =   3015
      Begin VB.Frame Frame5 
         Caption         =   "Tab 2"
         Height          =   1695
         Left            =   120
         TabIndex        =   15
         Top             =   2040
         Width           =   2775
         Begin VB.TextBox txtTab2Data0 
            Height          =   375
            Left            =   1320
            TabIndex        =   18
            Top             =   240
            Width           =   1335
         End
         Begin VB.TextBox txtTab2Data1 
            Height          =   375
            Left            =   1320
            TabIndex        =   17
            Top             =   720
            Width           =   1335
         End
         Begin VB.TextBox txtTab2Data2 
            Height          =   375
            Left            =   1320
            TabIndex        =   16
            Top             =   1200
            Width           =   1335
         End
         Begin VB.Label Label6 
            Caption         =   "CompareData0:"
            Height          =   255
            Left            =   120
            TabIndex        =   21
            Top             =   240
            Width           =   1215
         End
         Begin VB.Label Label5 
            Caption         =   "CompareData1:"
            Height          =   255
            Left            =   120
            TabIndex        =   20
            Top             =   720
            Width           =   1215
         End
         Begin VB.Label Label4 
            Caption         =   "CompareData2:"
            Height          =   255
            Left            =   120
            TabIndex        =   19
            Top             =   1200
            Width           =   1215
         End
      End
      Begin VB.Frame Frame4 
         Caption         =   "Tab 1"
         Height          =   1695
         Left            =   120
         TabIndex        =   8
         Top             =   240
         Width           =   2775
         Begin VB.TextBox txtTab1Data2 
            Height          =   375
            Left            =   1320
            TabIndex        =   14
            Top             =   1200
            Width           =   1335
         End
         Begin VB.TextBox txtTab1Data1 
            Height          =   375
            Left            =   1320
            TabIndex        =   12
            Top             =   720
            Width           =   1335
         End
         Begin VB.TextBox txtTab1Data0 
            Height          =   375
            Left            =   1320
            TabIndex        =   10
            Top             =   240
            Width           =   1335
         End
         Begin VB.Label Label3 
            Caption         =   "CompareData2:"
            Height          =   255
            Left            =   120
            TabIndex        =   13
            Top             =   1200
            Width           =   1215
         End
         Begin VB.Label Label2 
            Caption         =   "CompareData1:"
            Height          =   255
            Left            =   120
            TabIndex        =   11
            Top             =   720
            Width           =   1215
         End
         Begin VB.Label Label1 
            Caption         =   "CompareData0:"
            Height          =   255
            Left            =   120
            TabIndex        =   9
            Top             =   240
            Width           =   1215
         End
      End
   End
   Begin BDaqOcxLibCtl.UdCounterCtrl UdCounterCtrl1 
      Left            =   2640
      OleObjectBlob   =   "ContinueCompare.frx":0000
      Top             =   120
   End
   Begin VB.Label Label14 
      Caption         =   "Compare table end count:"
      Height          =   255
      Left            =   4200
      TabIndex        =   38
      Top             =   4680
      Width           =   1935
   End
   Begin VB.Label Label13 
      Caption         =   "Counter pattern match count:"
      Height          =   255
      Left            =   120
      TabIndex        =   36
      Top             =   4680
      Width           =   2175
   End
   Begin VB.Image Image1 
      Height          =   4725
      Left            =   0
      Picture         =   "ContinueCompare.frx":008A
      Top             =   0
      Width           =   7890
   End
End
Attribute VB_Name = "ContinueCompare"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
 
Private Type LineTabparam
    firstValue As Integer
    increment As Integer
    count As Integer
End Type

Enum TabSel
    dispersed = 0
    lined
End Enum

Private m_tabIndex As Integer
Private m_contCompTabSel As TabSel

'the event handler parameters
Private matchCount As Integer
Private endCount As Integer
Private comTable(2) As Long
Private m_lineTabparam As LineTabparam
Private evntEndID(7) As Integer
Private evntMatchID(7) As Integer
Private matched As Boolean

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

Private Sub EnableCompareTable(ByVal enabled As Boolean)
    radTable.enabled = enabled
    txtTab1Data0.enabled = enabled
    txtTab1Data1.enabled = enabled
    txtTab1Data2.enabled = enabled
    txtTab2Data0.enabled = enabled
    txtTab2Data1.enabled = enabled
    txtTab2Data2.enabled = enabled
    
    radInterval.enabled = enabled
    txtInt1FirstValue.enabled = enabled
    txtInt1Increment.enabled = enabled
    txtInt1Count.enabled = enabled
    txtInt2FirstValue.enabled = enabled
    txtInt2Increment.enabled = enabled
    txtInt2Count.enabled = enabled
End Sub

Private Sub CreateDisperseTable(ByVal tabIndex As Integer, ByRef CompTab() As Long)
    If tabIndex = 0 Then
        CompTab(0) = Int(txtTab1Data0.Text)
        CompTab(1) = Int(txtTab1Data1.Text)
        CompTab(2) = Int(txtTab1Data2.Text)
    Else
        CompTab(0) = Int(txtTab2Data0.Text)
        CompTab(1) = Int(txtTab2Data1.Text)
        CompTab(2) = Int(txtTab2Data2.Text)
    End If
End Sub

Private Sub CreateLineTable(ByVal tabIndex As Integer, ByRef param As LineTabparam)
    If tabIndex = 0 Then
        param.firstValue = Int(txtInt1FirstValue.Text)
        param.increment = Int(txtInt1Increment.Text)
        param.count = Int(txtInt1Count.Text)
    Else
        param.firstValue = Int(txtInt2FirstValue.Text)
        param.increment = Int(txtInt2Increment.Text)
        param.count = Int(txtInt2Count.Text)
    End If
End Sub


Private Sub btnStart_Click()
    'Set compare table
    Dim comTable(2) As Long
    Dim param As LineTabparam
    
    If radTable.Value Then
        m_contCompTabSel = dispersed
    Else
        m_contCompTabSel = lined
    End If
    
    If m_contCompTabSel = dispersed Then
        CreateDisperseTable 0, comTable
        UdCounterCtrl1.CompareSetTable 3, comTable
    Else
        CreateLineTable 0, param
        UdCounterCtrl1.CompareSetInterval param.firstValue, param.increment, param.count
    End If
    
    matchCount = 0
    endCount = 0
    m_tabIndex = 0
    
    'Start Snap Counter function.
    UdCounterCtrl1.enabled = True
    
    Timer1.enabled = True
    
    btnStart.enabled = False
    btnStop.enabled = True
    
    EnableCompareTable False
    
    txtPMCount.Text = "0"
    txtEndCount.Text = "0"
End Sub

Private Sub btnStop_Click()
    'Stop the user Timer
    Timer1.enabled = False
    
    btnStart.enabled = True
    btnStop.enabled = False
    
    EnableCompareTable True
    
    UdCounterCtrl1.enabled = False
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
    ContinueCompare.Caption = "Continue Compare(" + devDesc + ")"
    
    m_tabIndex = 0
    
    'initialize the compare table
    txtTab1Data0.Text = "100"
    txtTab1Data1.Text = "340"
    txtTab1Data2.Text = "720"
    txtTab2Data0.Text = "1000"
    txtTab2Data1.Text = "1980"
    txtTab2Data2.Text = "2510"
    
    txtInt1FirstValue.Text = "150"
    txtInt1Increment.Text = "3"
    txtInt1Count.Text = "3"
    txtInt2FirstValue.Text = "210"
    txtInt2Increment.Text = "3"
    txtInt2Count.Text = "3"
    
    btnStart.enabled = True
    btnStop.enabled = False
    
    'initialize the event handler parameters
    matchCount = 0
    endCount = 0
    matched = False
    Dim i As Integer
    For i = 0 To 7
        evntEndID(i) = 422 + i     'EvtCntCompareTableEnd0 = 422
        evntMatchID(i) = 414 + i   'EvtCntPatternMatch0 = 414
    Next
End Sub

Private Sub Timer1_Timer()
    UdCounterCtrl1.enabled = True
    
    Dim cntrValue As Long
    cntrValue = UdCounterCtrl1.Value
    
    txtCounterValue.Text = "0x" + Hex(cntrValue)
End Sub

Private Sub UdCounterCtrl1_UdCntrEvent(ByVal SrcId As Long, ByVal Length As Long, PortData() As Long)
    'refresh the snap value list
    If evntEndID(UdCounterCtrl1.Channel) = SrcId Then
        endCount = endCount + 1
        m_tabIndex = m_tabIndex + 1
        If m_contCompTabSel = dispersed Then
            CreateDisperseTable m_tabIndex Mod 2, comTable
            UdCounterCtrl1.CompareSetTable 3, comTable
        Else
            CreateLineTable m_tabIndex Mod 2, m_lineTabparam
            UdCounterCtrl1.CompareSetInterval m_lineTabparam.firstValue, m_lineTabparam.increment, m_lineTabparam.count
        End If
        
        matched = True
    Else
        If evntMatchID(UdCounterCtrl1.Channel) = SrcId Then
            matchCount = matchCount + 1
            matched = True
        End If
    End If
    
    If matched Then
        txtPMCount.Text = Str(matchCount)
        txtEndCount.Text = Str(endCount)
        matched = False
    End If
End Sub

