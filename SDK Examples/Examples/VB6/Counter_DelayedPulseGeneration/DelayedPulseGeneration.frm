VERSION 5.00
Object = "{1752FF26-D6C9-4BC8-BFE9-7D0CA26DED89}#1.0#0"; "BDaqOcx.dll"
Object = "{82351433-9094-11D1-A24B-00A0C932C7DF}#1.5#0"; "AniGIF.ocx"
Begin VB.Form DelayedPulseGeneration 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Delayed Pulse Generation"
   ClientHeight    =   3285
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   5010
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   219
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   334
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
      TabIndex        =   2
      Top             =   2760
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
      Height          =   375
      Left            =   960
      TabIndex        =   1
      Top             =   2760
      Width           =   1095
   End
   Begin VB.Frame Frame1 
      Caption         =   "Execution status"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000002&
      Height          =   2175
      Left            =   240
      TabIndex        =   0
      Top             =   480
      Width           =   4335
      Begin VB.TextBox eventCount 
         BackColor       =   &H80000016&
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
         Left            =   1800
         Locked          =   -1  'True
         TabIndex        =   7
         Top             =   1560
         Width           =   2055
      End
      Begin VB.TextBox delayCount 
         BackColor       =   &H80000016&
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
         Left            =   1800
         Locked          =   -1  'True
         TabIndex        =   5
         Top             =   960
         Width           =   2055
      End
      Begin AniGIFCtrl.AniGIF ExecutionStatus 
         Height          =   375
         Left            =   240
         TabIndex        =   3
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
         GIF             =   "DelayedPulseGeneration.frx":0000
         ExtendWidth     =   6376
         ExtendHeight    =   661
         Loop            =   0
         AutoRewind      =   0   'False
         Synchronized    =   -1  'True
      End
      Begin VB.Label label_shotCount 
         Caption         =   "Delayed Pulse count:"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   240
         TabIndex        =   6
         Top             =   1560
         Width           =   1335
      End
      Begin VB.Label Label1 
         Caption         =   "Delay count:"
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
   End
   Begin BDaqOcxLibCtl.OneShotCtrl OneShotCtrl1 
      Left            =   480
      OleObjectBlob   =   "DelayedPulseGeneration.frx":5F12
      Top             =   120
   End
   Begin VB.Image Image1 
      Height          =   1905
      Left            =   1800
      Picture         =   "DelayedPulseGeneration.frx":5F78
      Top             =   -240
      Width           =   3555
   End
End
Attribute VB_Name = "DelayedPulseGeneration"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private DelayedPulseCount As Integer

Private Sub Form_Load()
    'The default device of project is demo device, users can choose other devices according to their needs.
    If Not OneShotCtrl1.Initialized Then
        MsgBox "Please select a device with DAQNavi wizard!"
        End
    End If
    
    'set title of the form.
    Dim devNum As Long
    Dim devDesc As String
    Dim devMode As AccessMode
    Dim modIndex As Long
    OneShotCtrl1.getSelectedDevice devNum, devDesc, devMode, modIndex
    DelayedPulseGeneration.Caption = "Delayed Pulse Generation(" + devDesc + ")"
    
    delayCount.Text = Str(OneShotCtrl1.delayCount)
    ExecutionStatus.Playing = False
    label_shotCount.Enabled = False
    Stop_button.Enabled = False
End Sub

'Private Sub OneShotCtrl1_OneShot(ByVal Channel As Long)
'    DelayedPulseCount = DelayedPulseCount + 1
'    label_shotCount.Enabled = True
'    eventCount.Text = DelayedPulseCount
'End Sub

Private Sub Start_button_Click()
    DelayedPulseCount = 0
    
    eventCount.Text = ""
    ExecutionStatus.Playing = True
    
    'start oneShot
    OneShotCtrl1.Enabled = True
    
    Stop_button.Enabled = True
    Start_button.Enabled = False
End Sub

Private Sub Stop_button_Click()
    'stop oneShot
    OneShotCtrl1.Enabled = False
    
    Start_button.Enabled = True
    Stop_button.Enabled = False
    ExecutionStatus.Playing = False
End Sub
