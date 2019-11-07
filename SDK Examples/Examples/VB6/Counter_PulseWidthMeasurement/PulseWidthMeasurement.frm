VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{1752FF26-D6C9-4BC8-BFE9-7D0CA26DED89}#1.0#0"; "BDaqOcx.dll"
Begin VB.Form PulseWidthMeasurement 
   Caption         =   "Pulse Width Measurement"
   ClientHeight    =   4140
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   5325
   LinkTopic       =   "Form1"
   ScaleHeight     =   276
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   355
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   500
      Left            =   960
      Top             =   0
   End
   Begin VB.Frame Frame1 
      Height          =   3375
      Left            =   120
      TabIndex        =   0
      Top             =   600
      Width           =   5055
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
         Height          =   375
         Left            =   3600
         TabIndex        =   9
         Top             =   1680
         Width           =   1215
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
         Left            =   3600
         TabIndex        =   8
         Top             =   720
         Width           =   1215
      End
      Begin MSComctlLib.ListView CounterValueList 
         Height          =   1695
         Left            =   120
         TabIndex        =   7
         Top             =   1560
         Width           =   3255
         _ExtentX        =   5741
         _ExtentY        =   2990
         View            =   3
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
      Begin VB.TextBox CurLoPeriod 
         Alignment       =   1  'Right Justify
         BackColor       =   &H80000016&
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   460
         Left            =   1440
         Locked          =   -1  'True
         TabIndex        =   5
         Top             =   840
         Width           =   1455
      End
      Begin VB.TextBox CurHiPeriod 
         Alignment       =   1  'Right Justify
         BackColor       =   &H80000016&
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   460
         Left            =   1440
         Locked          =   -1  'True
         TabIndex        =   2
         Top             =   240
         Width           =   1455
      End
      Begin VB.Label Label4 
         Alignment       =   2  'Center
         Caption         =   "S"
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
         Left            =   3000
         TabIndex        =   6
         Top             =   960
         Width           =   255
      End
      Begin VB.Label Label3 
         Caption         =   "Low Period:"
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
         Left            =   240
         TabIndex        =   4
         Top             =   960
         Width           =   1095
      End
      Begin VB.Label Label2 
         Alignment       =   2  'Center
         Caption         =   "S"
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
         Left            =   3000
         TabIndex        =   3
         Top             =   360
         Width           =   255
      End
      Begin VB.Label Label1 
         Caption         =   "High Period:"
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
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Width           =   1095
      End
   End
   Begin BDaqOcxLibCtl.PwMeterCtrl PwMeterCtrl1 
      Left            =   360
      OleObjectBlob   =   "PulseWidthMeasurement.frx":0000
      Top             =   120
   End
   Begin VB.Image Image1 
      Height          =   885
      Left            =   2880
      Picture         =   "PulseWidthMeasurement.frx":0062
      Top             =   -120
      Width           =   2490
   End
End
Attribute VB_Name = "PulseWidthMeasurement"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private ECisRunning As Boolean
Private isPwMeterReset As Boolean
Private Const maxOfCounterValueList As Integer = 5   'The max value of lines of CounterValueList.

Private Sub InitListView()
    'add the columnHeaders for every column
    CounterValueList.ColumnHeaders.Add , , , 0
    CounterValueList.ColumnHeaders.Add , , , CounterValueList.Width
End Sub

Private Sub Form_Load()
    'no device is selected
    If Not PwMeterCtrl1.Initialized Then
        MsgBox "Please select a device with DAQNavi wizard!"
        End
    End If
      
    'set title of the form.
    Dim devNum As Long
    Dim devDesc As String
    Dim devMode As AccessMode
    Dim modIndex As Long
    PwMeterCtrl1.getSelectedDevice devNum, devDesc, devMode, modIndex
    PulseWidthMeasurement.Caption = "Pulse Width Measurement(" + devDesc + ")"
    
    ECisRunning = True
    isPwMeterReset = True
    Timer1.Enabled = False
    Stop_button.Enabled = False
    
    InitListView
End Sub

Private Sub Start_button_Click()
    If isPwMeterReset = True Then
        CounterValueList.ListItems.Clear
        
        'start PwMeter
        PwMeterCtrl1.Enabled = True
        ECisRunning = True
        
        If Timer1.Enabled = False Then
            Timer1.Enabled = True
        End If
        
        Stop_button.Enabled = True
        Start_button.Caption = "Latch"
        isPwMeterReset = False
    Else
        CounterValueList.ListItems.Add
        CounterValueList.ListItems(CounterValueList.ListItems.Count).ListSubItems.Add
        CounterValueList.ListItems(CounterValueList.ListItems.Count).ListSubItems(1).Text = "High:" + CurHiPeriod.Text + " Low:" + CurLoPeriod.Text
        
        If CounterValueList.ListItems.Count > maxOfCounterValueList Then
            CounterValueList.ListItems.Remove (1)
        End If
    End If
End Sub

Private Sub Stop_button_Click()
    'Stop event counting
        PwMeterCtrl1.Enabled = False
        ECisRunning = False
        
        isPwMeterReset = True
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
        CurHiPeriod.Text = Format(PwMeterCtrl1.getValue.HiPeriod, "#0.00#")
        CurLoPeriod.Text = Format(PwMeterCtrl1.getValue.LoPeriod, "#0.00#")
    End If
End Sub
