VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{1752FF26-D6C9-4BC8-BFE9-7D0CA26DED89}#1.0#0"; "BDaqOcx.dll"
Begin VB.Form EventCounter 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Event Counter"
   ClientHeight    =   3750
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   5220
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   250
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   348
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   40
      Left            =   960
      Top             =   0
   End
   Begin VB.Frame Frame1 
      Height          =   3135
      Left            =   120
      TabIndex        =   0
      Top             =   480
      Width           =   4935
      Begin VB.Frame Frame2 
         Height          =   580
         Left            =   120
         TabIndex        =   4
         Top             =   120
         Width           =   3015
         Begin VB.Label CurCounterValue 
            Alignment       =   1  'Right Justify
            BeginProperty Font 
               Name            =   "Arial"
               Size            =   12
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Left            =   240
            TabIndex        =   5
            Top             =   240
            Width           =   2655
         End
      End
      Begin VB.CommandButton Stop_button 
         Caption         =   "Stop"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   3360
         TabIndex        =   3
         Top             =   1440
         Width           =   1335
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
         Height          =   375
         Left            =   3360
         TabIndex        =   2
         Top             =   600
         Width           =   1335
      End
      Begin MSComctlLib.ListView CounterValueList 
         Height          =   2175
         Left            =   120
         TabIndex        =   1
         Top             =   840
         Width           =   3015
         _ExtentX        =   5318
         _ExtentY        =   3836
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
         BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         NumItems        =   0
      End
   End
   Begin BDaqOcxLibCtl.EventCounterCtrl EventCounterCtrl1 
      Left            =   360
      OleObjectBlob   =   "EventCounter.frx":0000
      Top             =   120
   End
   Begin VB.Image Image1 
      Height          =   885
      Left            =   2880
      Picture         =   "EventCounter.frx":0062
      Top             =   -120
      Width           =   2490
   End
End
Attribute VB_Name = "EventCounter"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private ECisRunning As Boolean
Private isEventCountingReset As Boolean
Private Const maxOfCounterValueList As Integer = 7   'The max value of lines of CounterValueList.

Private Sub InitListView()
    'add the columnHeaders for every column
    CounterValueList.ColumnHeaders.Add , , , 0
    CounterValueList.ColumnHeaders.Add , , , CounterValueList.Width
End Sub

Private Sub Form_Load()
    'The default device of project is demo device, users can choose other devices according to their needs.
    If Not EventCounterCtrl1.Initialized Then
        MsgBox "Please select a device with DAQNavi wizard!"
        End
    End If
    
    Dim t As Integer
    t = EventCounterCtrl1.Features.ChannelCountMax
    
     'set title of the form.
     Dim devNum As Long
     Dim devDesc As String
     Dim devMode As AccessMode
     Dim modIndex As Long
     EventCounterCtrl1.getSelectedDevice devNum, devDesc, devMode, modIndex
     EventCounter.Caption = "Event Counter(" + devDesc + ")"
     
     ECisRunning = True
     isEventCountingReset = True
     
     Timer1.Enabled = False
     Stop_button.Enabled = False
     
     InitListView
End Sub

Private Sub Start_button_Click()
    If isEventCountingReset = True Then
        CounterValueList.ListItems.Clear
        
        EventCounterCtrl1.Enabled = True
        ECisRunning = True
        
        If Timer1.Enabled = False Then
            Timer1.Enabled = True
        End If
        
        Stop_button.Enabled = True
        Start_button.Caption = "Latch"
        isEventCountingReset = False
    Else
        CounterValueList.ListItems.Add
        CounterValueList.ListItems(CounterValueList.ListItems.Count).ListSubItems.Add
        CounterValueList.ListItems(CounterValueList.ListItems.Count).ListSubItems(1).Text = Str(EventCounterCtrl1.Value)
        If CounterValueList.ListItems.Count > maxOfCounterValueList Then
            CounterValueList.ListItems.Remove (1)
        End If
    End If
End Sub

Private Sub Stop_button_Click()
    'Stop event counting
    EventCounterCtrl1.Enabled = False
    ECisRunning = False
    
    isEventCountingReset = True
    Start_button.Enabled = True
    Start_button.Caption = "Start"
    Stop_button.Enabled = False
    
    'stop the timer
    If ECisRunning = False Then
        Timer1.Enabled = False
    End If
End Sub

Private Sub Timer1_Timer()
    If ECisRunning Then
        'Show event counting value
        CurCounterValue.Caption = Str(EventCounterCtrl1.Value)
    End If
End Sub
