VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{1752FF26-D6C9-4BC8-BFE9-7D0CA26DED89}#1.0#0"; "BDaqOcx.dll"
Begin VB.Form StaticDI 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Static DI"
   ClientHeight    =   4305
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   6900
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   287
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   460
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.ImageList ImageList1 
      Left            =   1560
      Top             =   0
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   26
      ImageHeight     =   26
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   2
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "StaticDI.frx":0000
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "StaticDI.frx":0872
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   960
      Top             =   0
   End
   Begin VB.Frame Frame1 
      Height          =   3255
      Left            =   240
      TabIndex        =   0
      Top             =   840
      Width           =   6135
      Begin VB.Frame Frame9 
         Height          =   615
         Left            =   3000
         TabIndex        =   16
         Top             =   2400
         Width           =   2055
         Begin VB.Image Image3 
            Height          =   495
            Index           =   0
            Left            =   1560
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image3 
            Height          =   495
            Index           =   1
            Left            =   1080
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image3 
            Height          =   495
            Index           =   2
            Left            =   600
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image3 
            Height          =   495
            Index           =   3
            Left            =   120
            Top             =   120
            Width           =   495
         End
      End
      Begin VB.Frame Frame8 
         Height          =   615
         Left            =   720
         TabIndex        =   15
         Top             =   2400
         Width           =   2055
         Begin VB.Image Image3 
            Height          =   495
            Index           =   4
            Left            =   1560
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image3 
            Height          =   495
            Index           =   5
            Left            =   1080
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image3 
            Height          =   495
            Index           =   6
            Left            =   600
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image3 
            Height          =   495
            Index           =   7
            Left            =   120
            Top             =   120
            Width           =   495
         End
      End
      Begin VB.Frame Frame7 
         Height          =   615
         Left            =   3000
         TabIndex        =   14
         Top             =   1680
         Width           =   2055
         Begin VB.Image Image2 
            Height          =   495
            Index           =   0
            Left            =   1560
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image2 
            Height          =   495
            Index           =   1
            Left            =   1080
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image2 
            Height          =   495
            Index           =   2
            Left            =   600
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image2 
            Height          =   495
            Index           =   3
            Left            =   120
            Top             =   120
            Width           =   495
         End
      End
      Begin VB.Frame Frame6 
         Height          =   615
         Left            =   720
         TabIndex        =   13
         Top             =   1680
         Width           =   2055
         Begin VB.Image Image2 
            Height          =   495
            Index           =   4
            Left            =   1560
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image2 
            Height          =   495
            Index           =   5
            Left            =   1080
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image2 
            Height          =   495
            Index           =   6
            Left            =   600
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image2 
            Height          =   495
            Index           =   7
            Left            =   120
            Top             =   120
            Width           =   495
         End
      End
      Begin VB.Frame Frame5 
         Height          =   615
         Left            =   3000
         TabIndex        =   12
         Top             =   960
         Width           =   2055
         Begin VB.Image Image1 
            Height          =   495
            Index           =   0
            Left            =   1560
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image1 
            Height          =   495
            Index           =   1
            Left            =   1080
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image1 
            Height          =   495
            Index           =   2
            Left            =   600
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image1 
            Height          =   495
            Index           =   3
            Left            =   120
            Top             =   120
            Width           =   495
         End
      End
      Begin VB.Frame Frame4 
         Height          =   615
         Left            =   720
         TabIndex        =   11
         Top             =   960
         Width           =   2055
         Begin VB.Image Image1 
            Height          =   495
            Index           =   4
            Left            =   1560
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image1 
            Height          =   495
            Index           =   5
            Left            =   1080
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image1 
            Height          =   495
            Index           =   6
            Left            =   600
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image1 
            Height          =   495
            Index           =   7
            Left            =   120
            Top             =   120
            Width           =   495
         End
      End
      Begin VB.Frame Frame3 
         Height          =   615
         Left            =   3000
         TabIndex        =   10
         Top             =   240
         Width           =   2055
         Begin VB.Image Image0 
            Height          =   495
            Index           =   0
            Left            =   1560
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image0 
            Height          =   495
            Index           =   1
            Left            =   1080
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image0 
            Height          =   495
            Index           =   2
            Left            =   600
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image0 
            Height          =   495
            Index           =   3
            Left            =   120
            Top             =   120
            Width           =   495
         End
      End
      Begin VB.Frame Frame2 
         Height          =   615
         Left            =   720
         TabIndex        =   5
         Top             =   240
         Width           =   2055
         Begin VB.Image Image0 
            Height          =   495
            Index           =   4
            Left            =   1560
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image0 
            Height          =   495
            Index           =   5
            Left            =   1080
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image0 
            Height          =   495
            Index           =   6
            Left            =   600
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image0 
            Height          =   495
            Index           =   7
            Left            =   120
            Top             =   120
            Width           =   495
         End
      End
      Begin VB.Label PortHex 
         Alignment       =   2  'Center
         BorderStyle     =   1  'Fixed Single
         Height          =   495
         Index           =   3
         Left            =   5280
         TabIndex        =   9
         Top             =   2520
         Width           =   495
      End
      Begin VB.Label PortHex 
         Alignment       =   2  'Center
         BorderStyle     =   1  'Fixed Single
         Height          =   495
         Index           =   2
         Left            =   5280
         TabIndex        =   8
         Top             =   1800
         Width           =   495
      End
      Begin VB.Label PortHex 
         Alignment       =   2  'Center
         BorderStyle     =   1  'Fixed Single
         Height          =   495
         Index           =   1
         Left            =   5280
         TabIndex        =   7
         Top             =   1080
         Width           =   495
      End
      Begin VB.Label PortHex 
         Alignment       =   2  'Center
         BorderStyle     =   1  'Fixed Single
         Height          =   495
         Index           =   0
         Left            =   5280
         TabIndex        =   6
         Top             =   360
         Width           =   495
      End
      Begin VB.Label PortNum 
         Alignment       =   2  'Center
         BorderStyle     =   1  'Fixed Single
         Height          =   495
         Index           =   3
         Left            =   120
         TabIndex        =   4
         Top             =   2520
         Width           =   495
      End
      Begin VB.Label PortNum 
         Alignment       =   2  'Center
         BorderStyle     =   1  'Fixed Single
         Height          =   495
         Index           =   2
         Left            =   120
         TabIndex        =   3
         Top             =   1800
         Width           =   495
      End
      Begin VB.Label PortNum 
         Alignment       =   2  'Center
         BorderStyle     =   1  'Fixed Single
         Height          =   495
         Index           =   1
         Left            =   120
         TabIndex        =   2
         Top             =   1080
         Width           =   495
      End
      Begin VB.Label PortNum 
         Alignment       =   2  'Center
         BorderStyle     =   1  'Fixed Single
         Height          =   495
         Index           =   0
         Left            =   120
         TabIndex        =   1
         Top             =   360
         Width           =   495
      End
   End
   Begin BDaqOcxLibCtl.InstantDiCtrl InstantDiCtrl1 
      Left            =   480
      OleObjectBlob   =   "StaticDI.frx":10E6
      Top             =   120
   End
   Begin VB.Label Label12 
      Caption         =   "Hex"
      Height          =   255
      Left            =   5640
      TabIndex        =   20
      Top             =   600
      Width           =   375
   End
   Begin VB.Label Label11 
      Caption         =   "3                               0 "
      Height          =   255
      Left            =   3480
      TabIndex        =   19
      Top             =   600
      Width           =   1575
   End
   Begin VB.Label Label10 
      Caption         =   "Bit  7                              4"
      Height          =   255
      Left            =   960
      TabIndex        =   18
      Top             =   600
      Width           =   1815
   End
   Begin VB.Label Label9 
      Caption         =   "Port No."
      Height          =   255
      Left            =   240
      TabIndex        =   17
      Top             =   600
      Width           =   735
   End
   Begin VB.Image Imageback 
      Height          =   1455
      Left            =   4440
      Picture         =   "StaticDI.frx":117F
      Top             =   -240
      Width           =   2775
   End
End
Attribute VB_Name = "StaticDI"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Const startPort As Integer = 0
Private Const portCountShow As Integer = 4

Private Sub HandleError(ByVal err As ErrorCode)
    Dim utility As BDaqUtility
    Dim errorMessage As String
    Dim res As ErrorCode
        
    Set utility = New BDaqUtility
        
    res = utility.EnumToString("ErrorCode", err, errorMessage)
    
    If err <> Success Then
        MsgBox "Sorry ! Some errors happened, the error code is: " & errorMessage, , "StaticDI"
    End If
End Sub

Private Sub Form_Load()
    'The default device of project is demo device, users can choose other devices according to their needs.
    If Not InstantDiCtrl1.Initialized Then
        MsgBox "Please select a device with DAQNavi wizard!", , "StaticDI"
        End
    End If
    
    'set the title
    Dim devNum As Long
    Dim devDesc As String
    Dim devMode As AccessMode
    Dim modIndex As Long
    InstantDiCtrl1.getSelectedDevice devNum, devDesc, devMode, modIndex
    StaticDI.Caption = "Static DI(" + devDesc + ")"
    
    'enable the timer to read DI ports status
    Timer1.Enabled = True
End Sub

Private Sub Timer1_Timer()
    'read Di port state
    Dim err As ErrorCode
    err = Success
    Dim portData As Byte
    
    Dim i As Integer
    i = 0
    While (i + startPort) < InstantDiCtrl1.Features.PortCount And i < portCountShow
        portData = 0
        err = InstantDiCtrl1.ReadPort(i + startPort, portData)
        If err <> Success Then
            Timer1.Enabled = False
            HandleError (err)
            Exit Sub
        End If
        
        PortNum.Item(i).Caption = Str(i + startPort)
        PortHex.Item(i).Caption = Format(Hex(portData), "00")
        
        'Set image box state
        Dim j As Integer
        Dim Index As Integer
        For j = 0 To 7
            Index = (Int(portData / 2 ^ j) And 1) + 1
            If i = 0 Then
                Image0.Item(j).Picture = ImageList1.ListImages(Index).Picture
            End If
            
            If i = 1 Then
                Image1.Item(j).Picture = ImageList1.ListImages(Index).Picture
            End If
            
            If i = 2 Then
                Image2.Item(j).Picture = ImageList1.ListImages(Index).Picture
            End If
            
            If i = 3 Then
                Image3.Item(j).Picture = ImageList1.ListImages(Index).Picture
            End If
        Next j
                        
        i = i + 1
    Wend
End Sub
