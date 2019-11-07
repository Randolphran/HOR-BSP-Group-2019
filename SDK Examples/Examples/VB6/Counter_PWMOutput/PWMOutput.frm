VERSION 5.00
Object = "{1752FF26-D6C9-4BC8-BFE9-7D0CA26DED89}#1.0#0"; "BDaqOcx.dll"
Object = "{82351433-9094-11D1-A24B-00A0C932C7DF}#1.5#0"; "AniGIF.ocx"
Begin VB.Form PWMOutput 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "PWM Output"
   ClientHeight    =   4440
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   5460
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   296
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   364
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox generatedLoPeriod 
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
      Height          =   360
      Left            =   1920
      Locked          =   -1  'True
      TabIndex        =   16
      Top             =   3240
      Width           =   1215
   End
   Begin VB.TextBox generatedHiPeriod 
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
      Height          =   360
      Left            =   1920
      Locked          =   -1  'True
      TabIndex        =   13
      Top             =   2760
      Width           =   1215
   End
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
      Left            =   2880
      TabIndex        =   9
      Top             =   3840
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
      TabIndex        =   8
      Top             =   3840
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
      ForeColor       =   &H00C00000&
      Height          =   2175
      Left            =   240
      TabIndex        =   7
      Top             =   1560
      Width           =   4575
      Begin AniGIFCtrl.AniGIF ExecutionStatus 
         Height          =   375
         Left            =   120
         TabIndex        =   10
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
         GIF             =   "PWMOutput.frx":0000
         ExtendWidth     =   6376
         ExtendHeight    =   661
         Loop            =   0
         AutoRewind      =   0   'False
         Synchronized    =   -1  'True
      End
      Begin VB.Label Label10 
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
         TabIndex        =   17
         Top             =   1800
         Width           =   255
      End
      Begin VB.Label Label9 
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
         Left            =   480
         TabIndex        =   15
         Top             =   1800
         Width           =   1095
      End
      Begin VB.Label Label8 
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
         TabIndex        =   14
         Top             =   1320
         Width           =   255
      End
      Begin VB.Label Label7 
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
         Left            =   480
         TabIndex        =   12
         Top             =   1320
         Width           =   1095
      End
      Begin VB.Label Label6 
         Caption         =   "Device generated pulse period:"
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
         Left            =   120
         TabIndex        =   11
         Top             =   840
         Width           =   2655
      End
   End
   Begin VB.TextBox desiredLoPeriod 
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
      Height          =   360
      Left            =   1920
      Locked          =   -1  'True
      TabIndex        =   5
      Top             =   1080
      Width           =   1215
   End
   Begin VB.TextBox desiredHiPeriod 
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
      Height          =   360
      Left            =   1920
      Locked          =   -1  'True
      TabIndex        =   2
      Top             =   600
      Width           =   1215
   End
   Begin BDaqOcxLibCtl.PwModulatorCtrl PwModulatorCtrl1 
      Left            =   4920
      OleObjectBlob   =   "PWMOutput.frx":5F12
      Top             =   3960
   End
   Begin VB.Label Label5 
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
      Left            =   3240
      TabIndex        =   6
      Top             =   1200
      Width           =   255
   End
   Begin VB.Label Label4 
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
      Left            =   720
      TabIndex        =   4
      Top             =   1200
      Width           =   975
   End
   Begin VB.Label Label3 
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
      Left            =   3240
      TabIndex        =   3
      Top             =   720
      Width           =   255
   End
   Begin VB.Label Label2 
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
      Left            =   720
      TabIndex        =   1
      Top             =   720
      Width           =   1095
   End
   Begin VB.Label Label1 
      Caption         =   "Desired period:"
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
      Left            =   360
      TabIndex        =   0
      Top             =   240
      Width           =   1335
   End
   Begin VB.Image Image1 
      Height          =   750
      Left            =   3240
      Picture         =   "PWMOutput.frx":5F84
      Top             =   0
      Width           =   2400
   End
End
Attribute VB_Name = "PWMOutput"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()
    'no device is selected
    If Not PwModulatorCtrl1.Initialized Then
        MsgBox "Please select a device with DAQNavi wizard!"
        End
    End If
    
    'set title of the form.
    Dim devNum As Long
    Dim devDesc As String
    Dim devMode As AccessMode
    Dim modIndex As Long
    PwModulatorCtrl1.getSelectedDevice devNum, devDesc, devMode, modIndex
    PWMOutput.Caption = "PWM Output(" + devDesc + ")"
    
    desiredHiPeriod.Text = Format(PwModulatorCtrl1.getPulseWidth.HiPeriod, "#0.00#")
    desiredLoPeriod.Text = Format(PwModulatorCtrl1.getPulseWidth.LoPeriod, "#0.00#")
    
    ExecutionStatus.Playing = False
    Stop_button.Enabled = False
End Sub

Private Sub Start_button_Click()
    'Enable execution status
    ExecutionStatus.Playing = True
    
    PwModulatorCtrl1.Enabled = True
    generatedHiPeriod.Text = Format(PwModulatorCtrl1.getPulseWidth.HiPeriod, "#0.00#")
    generatedLoPeriod.Text = Format(PwModulatorCtrl1.getPulseWidth.LoPeriod, "#0.00#")
    
    Stop_button.Enabled = True
    Start_button.Enabled = False
End Sub

Private Sub Stop_button_Click()
    'stop the PwModulator
    PwModulatorCtrl1.Enabled = False
    
    'Disable execution status
    ExecutionStatus.Playing = False
    Start_button.Enabled = True
    Stop_button.Enabled = False
End Sub
