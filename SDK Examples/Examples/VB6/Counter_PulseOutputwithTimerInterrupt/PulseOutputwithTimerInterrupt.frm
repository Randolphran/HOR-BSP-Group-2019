VERSION 5.00
Object = "{1752FF26-D6C9-4BC8-BFE9-7D0CA26DED89}#1.0#0"; "BDaqOcx.dll"
Object = "{82351433-9094-11D1-A24B-00A0C932C7DF}#1.5#0"; "AniGIF.ocx"
Begin VB.Form PulseOutputwithTimerInterrupt 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Pulse Output with Timer Interrupt"
   ClientHeight    =   4440
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   5415
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   296
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   361
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
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
      Left            =   2760
      TabIndex        =   11
      Top             =   3960
      Width           =   1095
   End
   Begin VB.CommandButton Start_button 
      BackColor       =   &H80000016&
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
      Left            =   720
      TabIndex        =   10
      Top             =   3960
      Width           =   1095
   End
   Begin VB.Frame Frame1 
      Caption         =   "Execution status "
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00C00000&
      Height          =   2775
      Left            =   240
      TabIndex        =   3
      Top             =   1080
      Width           =   4455
      Begin VB.TextBox eventCount 
         Alignment       =   1  'Right Justify
         BackColor       =   &H80000016&
         Height          =   435
         Left            =   240
         Locked          =   -1  'True
         TabIndex        =   9
         Top             =   2160
         Width           =   2535
      End
      Begin VB.TextBox generatedFrequency 
         Alignment       =   1  'Right Justify
         BackColor       =   &H80000016&
         Height          =   435
         Left            =   240
         Locked          =   -1  'True
         TabIndex        =   6
         Top             =   1200
         Width           =   2535
      End
      Begin AniGIFCtrl.AniGIF ExecutionStatus 
         Height          =   375
         Left            =   240
         TabIndex        =   4
         Top             =   360
         Width           =   3615
         BackColor       =   12632256
         PLaying         =   -1  'True
         Transparent     =   -1  'True
         Speed           =   1
         Stretch         =   0
         AutoSize        =   0   'False
         SequenceString  =   ""
         Sequence        =   0
         HTTPProxy       =   ""
         HTTPUserName    =   ""
         HTTPPassword    =   ""
         MousePointer    =   0
         GIF             =   "PulseOutputwithTimerInterrupt.frx":0000
         ExtendWidth     =   6376
         ExtendHeight    =   661
         Loop            =   0
         AutoRewind      =   0   'False
         Synchronized    =   -1  'True
      End
      Begin VB.Label label_eventCount 
         Caption         =   "Device generated timer event count:"
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
         TabIndex        =   8
         Top             =   1800
         Width           =   3135
      End
      Begin VB.Label Label4 
         Caption         =   "Hz"
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
         Left            =   2880
         TabIndex        =   7
         Top             =   1320
         Width           =   255
      End
      Begin VB.Label Label3 
         Caption         =   "Device generated pulse frequency:"
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
         TabIndex        =   5
         Top             =   840
         Width           =   3135
      End
   End
   Begin VB.TextBox desiredFrequency 
      Alignment       =   1  'Right Justify
      BackColor       =   &H80000016&
      Height          =   405
      Left            =   480
      Locked          =   -1  'True
      TabIndex        =   1
      Top             =   600
      Width           =   2535
   End
   Begin BDaqOcxLibCtl.TimerPulseCtrl TimerPulseCtrl1 
      Left            =   4920
      OleObjectBlob   =   "PulseOutputwithTimerInterrupt.frx":5F12
      Top             =   3360
   End
   Begin VB.Label Label2 
      Caption         =   "Hz"
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
      Left            =   3120
      TabIndex        =   2
      Top             =   720
      Width           =   255
   End
   Begin VB.Label Label1 
      Caption         =   "Desired frequency:"
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
      Left            =   480
      TabIndex        =   0
      Top             =   240
      Width           =   1695
   End
   Begin VB.Image Image1 
      Height          =   750
      Left            =   3600
      Picture         =   "PulseOutputwithTimerInterrupt.frx":5F7C
      Top             =   0
      Width           =   2400
   End
End
Attribute VB_Name = "PulseOutputwithTimerInterrupt"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private TPevtCount As Integer

Private Sub Form_Load()
    'The default device of project is demo device, users can choose other devices according to their needs.
    If Not TimerPulseCtrl1.Initialized Then
        MsgBox "Please select a device with DAQNavi wizard!"
        End
    End If
    
    'set title of the form.
    Dim devNum As Long
    Dim devDesc As String
    Dim devMode As AccessMode
    Dim modIndex As Long
    TimerPulseCtrl1.getSelectedDevice devNum, devDesc, devMode, modIndex
    PulseOutputwithTimerInterrupt.Caption = "Pulse Output with Timer Interrupt(" + devDesc + ")"
    
    desiredFrequency.Text = Str(TimerPulseCtrl1.Frequency)
    ExecutionStatus.Playing = False
    label_eventCount.Enabled = False
    Stop_button.Enabled = False
End Sub

Private Sub Start_button_Click()
    'TimerPulse event count
    TPevtCount = 0
    eventCount.Text = ""

    'Enable execution status
    ExecutionStatus.Playing = True
    
    'start the timer pulse
    TimerPulseCtrl1.Enabled = True
    generatedFrequency.Text = Str(TimerPulseCtrl1.Frequency)
    
    Stop_button.Enabled = True
    Start_button.Enabled = False
End Sub

Private Sub Stop_button_Click()
    'stop the timer pulse
    TimerPulseCtrl1.Enabled = False
    
    'Disable execution status
    ExecutionStatus.Playing = False
    Start_button.Enabled = True
    Stop_button.Enabled = False
End Sub

'Private Sub TimerPulseCtrl1_TimerTick(ByVal Channel As Long)
'    TPevtCount = TPevtCount + 1
'    label_eventCount.Enabled = True
'    eventCount.Text = Str(TPevtCount)
'End Sub
