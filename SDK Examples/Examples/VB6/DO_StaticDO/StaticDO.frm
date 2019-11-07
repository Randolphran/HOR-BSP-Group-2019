VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Object = "{1752FF26-D6C9-4BC8-BFE9-7D0CA26DED89}#1.0#0"; "BDaqOcx.dll"
Begin VB.Form StaticDO 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Static DO"
   ClientHeight    =   4470
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   7110
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   298
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   474
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.ImageList ImageList1 
      Left            =   960
      Top             =   0
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   27
      ImageHeight     =   27
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   3
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "StaticDO.frx":0000
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "StaticDO.frx":0422
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "StaticDO.frx":0883
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Frame Frame1 
      Height          =   3255
      Left            =   240
      TabIndex        =   0
      Top             =   960
      Width           =   6135
      Begin VB.Frame Frame9 
         Height          =   615
         Left            =   3000
         TabIndex        =   16
         Top             =   2400
         Width           =   1935
         Begin VB.Image Image3 
            Enabled         =   0   'False
            Height          =   495
            Index           =   0
            Left            =   1440
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image3 
            Enabled         =   0   'False
            Height          =   495
            Index           =   1
            Left            =   960
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image3 
            Enabled         =   0   'False
            Height          =   495
            Index           =   2
            Left            =   480
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image3 
            Enabled         =   0   'False
            Height          =   495
            Index           =   3
            Left            =   0
            Top             =   120
            Width           =   495
         End
      End
      Begin VB.Frame Frame8 
         Height          =   615
         Left            =   840
         TabIndex        =   15
         Top             =   2400
         Width           =   1935
         Begin VB.Image Image3 
            Enabled         =   0   'False
            Height          =   495
            Index           =   4
            Left            =   1440
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image3 
            Enabled         =   0   'False
            Height          =   495
            Index           =   5
            Left            =   960
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image3 
            Enabled         =   0   'False
            Height          =   495
            Index           =   6
            Left            =   480
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image3 
            Enabled         =   0   'False
            Height          =   495
            Index           =   7
            Left            =   0
            Top             =   120
            Width           =   495
         End
      End
      Begin VB.Frame Frame7 
         Height          =   615
         Left            =   3000
         TabIndex        =   14
         Top             =   1680
         Width           =   1935
         Begin VB.Image Image2 
            Enabled         =   0   'False
            Height          =   495
            Index           =   0
            Left            =   1440
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image2 
            Enabled         =   0   'False
            Height          =   495
            Index           =   1
            Left            =   960
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image2 
            Enabled         =   0   'False
            Height          =   495
            Index           =   2
            Left            =   480
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image2 
            Enabled         =   0   'False
            Height          =   495
            Index           =   3
            Left            =   0
            Top             =   120
            Width           =   495
         End
      End
      Begin VB.Frame Frame6 
         Height          =   615
         Left            =   840
         TabIndex        =   13
         Top             =   1680
         Width           =   1935
         Begin VB.Image Image2 
            Enabled         =   0   'False
            Height          =   495
            Index           =   4
            Left            =   1440
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image2 
            Enabled         =   0   'False
            Height          =   495
            Index           =   5
            Left            =   960
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image2 
            Enabled         =   0   'False
            Height          =   495
            Index           =   6
            Left            =   480
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image2 
            Enabled         =   0   'False
            Height          =   495
            Index           =   7
            Left            =   0
            Top             =   120
            Width           =   495
         End
      End
      Begin VB.Frame Frame5 
         Height          =   615
         Left            =   3000
         TabIndex        =   12
         Top             =   960
         Width           =   1935
         Begin VB.Image Image1 
            Enabled         =   0   'False
            Height          =   495
            Index           =   0
            Left            =   1440
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image1 
            Enabled         =   0   'False
            Height          =   495
            Index           =   1
            Left            =   960
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image1 
            Enabled         =   0   'False
            Height          =   495
            Index           =   2
            Left            =   480
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image1 
            Enabled         =   0   'False
            Height          =   495
            Index           =   3
            Left            =   0
            Top             =   120
            Width           =   495
         End
      End
      Begin VB.Frame Frame4 
         Height          =   615
         Left            =   840
         TabIndex        =   11
         Top             =   960
         Width           =   1935
         Begin VB.Image Image1 
            Enabled         =   0   'False
            Height          =   495
            Index           =   4
            Left            =   1440
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image1 
            Enabled         =   0   'False
            Height          =   495
            Index           =   5
            Left            =   960
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image1 
            Enabled         =   0   'False
            Height          =   495
            Index           =   6
            Left            =   480
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image1 
            Enabled         =   0   'False
            Height          =   495
            Index           =   7
            Left            =   0
            Top             =   120
            Width           =   495
         End
      End
      Begin VB.Frame Frame3 
         Height          =   615
         Left            =   3000
         TabIndex        =   10
         Top             =   240
         Width           =   1935
         Begin VB.Image Image0 
            Enabled         =   0   'False
            Height          =   495
            Index           =   0
            Left            =   1440
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image0 
            Enabled         =   0   'False
            Height          =   495
            Index           =   1
            Left            =   960
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image0 
            Enabled         =   0   'False
            Height          =   495
            Index           =   2
            Left            =   480
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image0 
            Enabled         =   0   'False
            Height          =   495
            Index           =   3
            Left            =   0
            Top             =   120
            Width           =   495
         End
      End
      Begin VB.Frame Frame2 
         Height          =   615
         Left            =   840
         TabIndex        =   5
         Top             =   240
         Width           =   1935
         Begin VB.Image Image0 
            Enabled         =   0   'False
            Height          =   495
            Index           =   4
            Left            =   1440
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image0 
            Enabled         =   0   'False
            Height          =   495
            Index           =   5
            Left            =   960
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image0 
            Enabled         =   0   'False
            Height          =   495
            Index           =   6
            Left            =   480
            Top             =   120
            Width           =   495
         End
         Begin VB.Image Image0 
            Enabled         =   0   'False
            Height          =   495
            Index           =   7
            Left            =   0
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
   Begin BDaqOcxLibCtl.InstantDoCtrl InstantDoCtrl1 
      Left            =   360
      OleObjectBlob   =   "StaticDO.frx":0CBF
      Top             =   240
   End
   Begin VB.Label Label12 
      Caption         =   "Hex"
      Height          =   255
      Left            =   5640
      TabIndex        =   20
      Top             =   720
      Width           =   375
   End
   Begin VB.Label Label11 
      Caption         =   "3                               0 "
      Height          =   255
      Left            =   3360
      TabIndex        =   19
      Top             =   720
      Width           =   1575
   End
   Begin VB.Label Label10 
      Caption         =   "Bit  7                              4"
      Height          =   255
      Left            =   960
      TabIndex        =   18
      Top             =   720
      Width           =   1815
   End
   Begin VB.Label Label9 
      Caption         =   "Port No."
      Height          =   255
      Left            =   240
      TabIndex        =   17
      Top             =   720
      Width           =   735
   End
   Begin VB.Image Imageback 
      Height          =   1515
      Left            =   4320
      Picture         =   "StaticDO.frx":0D1D
      Top             =   -120
      Width           =   3510
   End
End
Attribute VB_Name = "StaticDO"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Const StartPort As Integer = 0
Private Const PortCountShow As Integer = 4
Private portDatas(3) As Byte

Private Sub HandleError(ByVal err As ErrorCode)
    Dim utility As BDaqUtility
    Dim errorMessage As String
    Dim res As ErrorCode
        
    Set utility = New BDaqUtility
        
    res = utility.EnumToString("ErrorCode", err, errorMessage)
    
    If err <> Success Then
        MsgBox "Sorry ! There're some errors happened, the error code is: " & errorMessage
    End If
End Sub

Private Sub InitializePortState()
    On Error GoTo 0
    Dim portData As Byte
    portData = 0
    Dim portDir As Byte
    portDir = &HFF
    Dim err As ErrorCode
    err = Success
    Dim portDirs() As IPortDirection

    Dim i As Integer
    i = 0
    While (i + StartPort) < InstantDoCtrl1.Features.PortCount And i < PortCountShow
        err = InstantDoCtrl1.ReadPort(i + StartPort, portData)
        If err <> Success Then
            HandleError (err)
            Exit Sub
        End If
        
        PortNum.Item(i).Caption = Str(i + StartPort)
        PortHex.Item(i).Caption = Format(Hex(portData), "00")
        portDatas(i) = portData
        
        'set the port direction
        If InstantDoCtrl1.Features.PortProgrammable Then
            portDirs = InstantDoCtrl1.PortDirection
            portDir = portDirs(i).Direction
        End If
        
        'Set image state
        Dim j As Integer
        Dim Index As Integer
        For j = 0 To 7
            Index = (Int(portData / 2 ^ j) And &H1) + 1
            If i = 0 Then
                If (Int(portDir / 2 ^ j) And &H1) = 0 Then  'Bit direction is input.
                    Image0.Item(j).Picture = ImageList1.ListImages(3).Picture
                Else
                    Image0.Item(j).Picture = ImageList1.ListImages(Index).Picture
                    Image0.Item(j).Tag = (Int(portData / 2 ^ j) And &H1)
                    Image0.Item(j).Enabled = True
                End If
            End If

            If i = 1 Then
                If (Int(portDir / 2 ^ j) And &H1) = 0 Then  'Bit direction is input.
                    Image1.Item(j).Picture = ImageList1.ListImages(3).Picture
                Else
                    Image1.Item(j).Picture = ImageList1.ListImages(Index).Picture
                    Image1.Item(j).Tag = (Int(portData / 2 ^ j) And &H1)
                    Image1.Item(j).Enabled = True
                End If
            End If
                
            If i = 2 Then
                If (Int(portDir / 2 ^ j) And &H1) = 0 Then  'Bit direction is input.
                    Image2.Item(j).Picture = ImageList1.ListImages(3).Picture
                Else
                    Image2.Item(j).Picture = ImageList1.ListImages(Index).Picture
                    Image2.Item(j).Tag = (Int(portData / 2 ^ j) And &H1)
                    Image2.Item(j).Enabled = True
                End If
            End If

            If i = 3 Then
                If (Int(portDir / 2 ^ j) And &H1) = 0 Then  'Bit direction is input.
                    Image3.Item(j).Picture = ImageList1.ListImages(3).Picture
                Else
                    Image3.Item(j).Picture = ImageList1.ListImages(Index).Picture
                    Image3.Item(j).Tag = (Int(portData / 2 ^ j) And &H1)
                    Image3.Item(j).Enabled = True
                End If
            End If
        Next j
            
        i = i + 1

    Wend
End Sub

Private Sub Form_Load()
    'The default device of project is demo device, users can choose other devices according to their needs.
    If Not InstantDoCtrl1.Initialized Then
        MsgBox "Please select a device with DAQNavi wizard!", , "StaticDO"
        End
    End If
    
    'set the title of the form.
    Dim devNum As Long
    Dim devDesc As String
    Dim devMode As AccessMode
    Dim modIndex As Long
    InstantDoCtrl1.getSelectedDevice devNum, devDesc, devMode, modIndex
    StaticDO.Caption = "Static DO(" + devDesc + ")"
    
    InitializePortState
End Sub

Private Sub Image0_Click(Index As Integer)
    Dim bitValue As Integer
    bitValue = Val(Image0.Item(Index).Tag)
    If bitValue = 0 Then
        portDatas(0) = portDatas(0) + 2 ^ Index
        Image0.Item(Index).Picture = ImageList1.ListImages(2).Picture
        Image0.Item(Index).Tag = 1
    ElseIf bitValue = 1 Then
        portDatas(0) = portDatas(0) - 2 ^ Index
        Image0.Item(Index).Picture = ImageList1.ListImages(1).Picture
        Image0.Item(Index).Tag = 0
    End If
    
    PortHex.Item(0).Caption = Format(Hex(portDatas(0)), "00")
    Dim err As ErrorCode
    err = Success
    err = InstantDoCtrl1.WritePort(0 + StartPort, portDatas(0))
    If err <> Success Then
        HandleError (err)
    End If
End Sub

Private Sub Image1_Click(Index As Integer)
    Dim bitValue As Integer
    bitValue = Val(Image1.Item(Index).Tag)
    If bitValue = 0 Then
        portDatas(1) = portDatas(1) + 2 ^ Index
        Image1.Item(Index).Picture = ImageList1.ListImages(2).Picture
        Image1.Item(Index).Tag = 1
    ElseIf bitValue = 1 Then
        portDatas(1) = portDatas(1) - 2 ^ Index
        Image1.Item(Index).Picture = ImageList1.ListImages(1).Picture
        Image1.Item(Index).Tag = 0
    End If
    
    PortHex.Item(1).Caption = Format(Hex(portDatas(1)), "00")
    Dim err As ErrorCode
    err = Success
    err = InstantDoCtrl1.WritePort(1 + StartPort, portDatas(1))
    If err <> Success Then
        HandleError (err)
    End If
End Sub

Private Sub Image2_Click(Index As Integer)
    Dim bitValue As Integer
    bitValue = Val(Image2.Item(Index).Tag)
    If bitValue = 0 Then
        portDatas(2) = portDatas(2) + 2 ^ Index
        Image2.Item(Index).Picture = ImageList1.ListImages(2).Picture
        Image2.Item(Index).Tag = 1
    ElseIf bitValue = 1 Then
        portDatas(2) = portDatas(2) - 2 ^ Index
        Image2.Item(Index).Picture = ImageList1.ListImages(1).Picture
        Image2.Item(Index).Tag = 0
    End If
    
    PortHex.Item(2).Caption = Format(Hex(portDatas(2)), "00")
    Dim err As ErrorCode
    err = Success
    err = InstantDoCtrl1.WritePort(2 + StartPort, portDatas(2))
    If err <> Success Then
        HandleError (err)
    End If
End Sub

Private Sub Image3_Click(Index As Integer)
    Dim bitValue As Integer
    bitValue = Val(Image3.Item(Index).Tag)
    If bitValue = 0 Then
        portDatas(3) = portDatas(3) + 2 ^ Index
        Image3.Item(Index).Picture = ImageList1.ListImages(2).Picture
        Image3.Item(Index).Tag = 1
    ElseIf bitValue = 1 Then
        portDatas(3) = portDatas(3) - 2 ^ Index
        Image3.Item(Index).Picture = ImageList1.ListImages(1).Picture
        Image3.Item(Index).Tag = 0
    End If
    
    PortHex.Item(3).Caption = Format(Hex(portDatas(3)), "00")
    Dim err As ErrorCode
    err = Success
    err = InstantDoCtrl1.WritePort(3 + StartPort, portDatas(3))
    If err <> Success Then
        HandleError (err)
    End If
End Sub

