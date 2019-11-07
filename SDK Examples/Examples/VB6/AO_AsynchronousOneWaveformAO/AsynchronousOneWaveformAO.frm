VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Object = "{1752FF26-D6C9-4BC8-BFE9-7D0CA26DED89}#1.0#0"; "BDaqOcx.dll"
Begin VB.Form AsynchronousOneWaveformAO 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Asynchronous One Waveform AO"
   ClientHeight    =   6570
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   5250
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   438
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   350
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.ImageList ImageList1 
      Left            =   120
      Top             =   3000
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   50
      ImageHeight     =   50
      MaskColor       =   12632256
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   6
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "AsynchronousOneWaveformAO.frx":0000
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "AsynchronousOneWaveformAO.frx":1D3A
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "AsynchronousOneWaveformAO.frx":3B3C
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "AsynchronousOneWaveformAO.frx":5A06
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "AsynchronousOneWaveformAO.frx":7C18
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "AsynchronousOneWaveformAO.frx":9AB2
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.TextBox textBox_lowLevelB 
      Alignment       =   1  'Right Justify
      BorderStyle     =   0  'None
      Height          =   195
      Left            =   3000
      TabIndex        =   10
      Text            =   "-5"
      Top             =   4200
      Width           =   1095
   End
   Begin VB.TextBox textBox_highLevelB 
      Alignment       =   1  'Right Justify
      BorderStyle     =   0  'None
      Height          =   195
      Left            =   1320
      TabIndex        =   9
      Text            =   "5"
      Top             =   4200
      Width           =   1050
   End
   Begin VB.TextBox textBox_lowLevelA 
      Alignment       =   1  'Right Justify
      BorderStyle     =   0  'None
      Height          =   195
      Left            =   3000
      TabIndex        =   8
      Text            =   "-5"
      Top             =   1440
      Width           =   1095
   End
   Begin VB.TextBox textBox_highLevelA 
      Alignment       =   1  'Right Justify
      BorderStyle     =   0  'None
      Height          =   195
      Left            =   1320
      TabIndex        =   7
      Text            =   "5"
      Top             =   1440
      Width           =   1035
   End
   Begin VB.CommandButton button_start 
      Caption         =   "Start"
      Height          =   375
      Left            =   3120
      TabIndex        =   6
      Top             =   5880
      Width           =   1335
   End
   Begin VB.CheckBox checkBox_triangleB 
      Height          =   750
      Left            =   3480
      Picture         =   "AsynchronousOneWaveformAO.frx":B9E4
      Style           =   1  'Graphical
      TabIndex        =   5
      Top             =   4680
      Width           =   750
   End
   Begin VB.CheckBox checkBox_squareB 
      Height          =   750
      Left            =   2280
      Picture         =   "AsynchronousOneWaveformAO.frx":D89E
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   4680
      Width           =   750
   End
   Begin VB.CheckBox checkBox_sineB 
      Height          =   750
      Left            =   1080
      Picture         =   "AsynchronousOneWaveformAO.frx":F690
      Style           =   1  'Graphical
      TabIndex        =   3
      Top             =   4680
      Width           =   750
   End
   Begin VB.CheckBox checkBox_triangleA 
      Height          =   750
      Left            =   3480
      Picture         =   "AsynchronousOneWaveformAO.frx":113BA
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   1920
      Width           =   750
   End
   Begin VB.CheckBox checkBox_squareA 
      Height          =   750
      Left            =   2280
      Picture         =   "AsynchronousOneWaveformAO.frx":13274
      Style           =   1  'Graphical
      TabIndex        =   1
      Top             =   1920
      Width           =   750
   End
   Begin VB.CheckBox checkBox_sineA 
      Height          =   750
      Left            =   1080
      Picture         =   "AsynchronousOneWaveformAO.frx":15066
      Style           =   1  'Graphical
      TabIndex        =   0
      Top             =   1920
      Width           =   750
   End
   Begin BDaqOcxLibCtl.BufferedAoCtrl BufferedAoCtrl1 
      Left            =   360
      OleObjectBlob   =   "AsynchronousOneWaveformAO.frx":16D90
      Top             =   6000
   End
   Begin VB.Label label_chanB 
      BackStyle       =   0  'Transparent
      Caption         =   "1"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00008000&
      Height          =   255
      Left            =   3600
      TabIndex        =   12
      Top             =   3240
      Width           =   255
   End
   Begin VB.Label label_chanA 
      BackStyle       =   0  'Transparent
      Caption         =   "0"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00008000&
      Height          =   255
      Left            =   3600
      TabIndex        =   11
      Top             =   480
      Width           =   255
   End
   Begin VB.Image Image1 
      Height          =   6615
      Left            =   0
      Picture         =   "AsynchronousOneWaveformAO.frx":16E78
      Stretch         =   -1  'True
      Top             =   0
      Width           =   5415
   End
End
Attribute VB_Name = "AsynchronousOneWaveformAO"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
 Option Explicit

 Private pointPerPeriod As Integer
 Private dataScaled() As Double
 Private highLevelA As Double
 Private lowLevelA As Double
 Private highLevelB As Double
 Private lowLevelB As Double
 Private isCheckedA As Boolean
 Private isCheckedB As Boolean
 Private err As ErrorCode
 Private formCloseFlag As Boolean
 Private Const PI As Double = 3.14159265358979
 
 Enum WaveformStyle
   sine
   square
   triangle
 End Enum
 Private formStyleA As WaveformStyle
 Private formStyleB As WaveformStyle
 
 Private Function GetOnePoint(ByVal style As WaveformStyle, ByVal index As Integer, ByVal highLevel As Double, ByVal lowLevel As Double) As Double
    Dim amplitude As Double
    amplitude = (highLevel - lowLevel) / 2
    Dim Offset As Double
    Offset = (highLevel + lowLevel) / 2
    Dim data As Double
    data = 0
    
    Select Case style
        Case WaveformStyle.sine
            data = amplitude * Math.Sin(index * 2# * PI / pointPerPeriod) + Offset
        Case WaveformStyle.triangle
            If index < (pointPerPeriod / 4#) Then
               data = amplitude * (index / (pointPerPeriod / 4#)) + Offset
            ElseIf index < 3 * (pointPerPeriod / 4#) Then
               data = amplitude * ((2# * (pointPerPeriod / 4#) - index) / (pointPerPeriod / 4#)) + Offset
            Else
               data = amplitude * ((index - pointPerPeriod) / (pointPerPeriod / 4#)) + Offset
            End If
        Case WaveformStyle.square
            If (index >= 0) And (index < (pointPerPeriod / 2)) Then
               data = amplitude * 1 + Offset
            Else
               data = amplitude * (-1) + Offset
            End If
        Case Else
            GetOnePoint = data
            Exit Function
    End Select
    
        GetOnePoint = data
 End Function
 
 Public Sub GetOnePeriod(ByRef waveformBuffer() As Double, ByVal style As WaveformStyle, ByVal highLevel As Double, ByVal lowLevel As Double)
    Dim i As Integer
    For i = 0 To pointPerPeriod - 1
        waveformBuffer(i) = GetOnePoint(style, i, highLevel, lowLevel)
    Next i
 End Sub
 
 Public Sub GetMultipleWaveform(ByRef waveform() As Double, ByVal waveCount As Integer, ByRef styles() As WaveformStyle, ByRef highLevel() As Double, ByRef lowLevel() As Double)
    Dim i As Integer
    Dim j As Integer
    For i = 0 To pointPerPeriod - 1
        For j = 0 To waveCount - 1
            waveform(j + i * waveCount) = GetOnePoint(styles(j), i, highLevel(j), lowLevel(j))
        Next j
    Next i
 End Sub
 
 Private Sub CheckError(ByVal err As ErrorCode)
    Dim utility As BDaqUtility
    Dim errorMessage As String
    Dim res As ErrorCode
        
    Set utility = New BDaqUtility
        
    res = utility.EnumToString("ErrorCode", err, errorMessage)
    
    If err <> Success Then
        MsgBox "Error: " & errorMessage
    End If
 End Sub
 
 Private Sub ConfigurePanel()
    If BufferedAoCtrl1.ScanChannel.ChannelCount = 1 Then
        checkBox_sineB.Enabled = False
        checkBox_squareB.Enabled = False
        checkBox_triangleB.Enabled = False
        textBox_highLevelB.Enabled = False
        textBox_lowLevelB.Enabled = False
        label_chanB.Caption = " "
    Else
        checkBox_sineB.Enabled = True
        checkBox_squareB.Enabled = True
        checkBox_triangleB.Enabled = True
        textBox_highLevelB.Enabled = True
        textBox_lowLevelB.Enabled = True
        label_chanB.Caption = Str((BufferedAoCtrl1.ScanChannel.ChannelStart + 1) Mod BufferedAoCtrl1.ChannelCount)
    End If
    
    label_chanA.Caption = Str(BufferedAoCtrl1.ScanChannel.ChannelStart)
 End Sub

Private Sub BufferedAoCtrl1_Stopped(ByVal Offset As Long, ByVal Count As Long)
    If Not formCloseFlag Then
        button_start.Enabled = True
    End If
End Sub

Private Sub button_start_Click()
    If isCheckedA = False And isCheckedB = False Then
        MsgBox "Please select a waveform !"
        Exit Sub
    End If
    
    'prepare the AO
    err = BufferedAoCtrl1.Prepare
    CheckError (err)
    
    'generator the wave
    highLevelA = Val(textBox_highLevelA.Text)
    lowLevelA = Val(textBox_lowLevelA.Text)
    highLevelB = Val(textBox_highLevelB.Text)
    lowLevelB = Val(textBox_lowLevelB.Text)
    
    Dim styles(1) As WaveformStyle
    styles(0) = formStyleA
    styles(1) = formStyleB
    
    Dim highLevels(1) As Double
    highLevels(0) = highLevelA
    highLevels(1) = highLevelB
    
    Dim lowLevels(1) As Double
    lowLevels(0) = lowLevelA
    lowLevels(1) = lowLevelA
    
    pointPerPeriod = CInt(BufferedAoCtrl1.ScanChannel.Samples)
    ReDim dataScaled(BufferedAoCtrl1.ScanChannel.ChannelCount * pointPerPeriod - 1) As Double
    
    If BufferedAoCtrl1.ScanChannel.ChannelCount <= 1 Then
        GetOnePeriod dataScaled, formStyleA, highLevelA, lowLevelA
    Else
        If isCheckedA = True And isCheckedB = False Then
            styles(0) = formStyleA
            highLevels(0) = highLevelA
            highLevels(1) = 0
            lowLevels(0) = lowLevelA
            lowLevels(1) = 0
        ElseIf isCheckedA = False And isCheckedB = True Then
            styles(1) = formStyleB
            highLevels(0) = 0
            highLevels(1) = highLevelB
            lowLevels(0) = 0
            lowLevels(1) = lowLevelB
        ElseIf isCheckedA = False And isCheckedB = False Then
            highLevels(0) = 0
            highLevels(1) = 0
            lowLevels(0) = 0
            lowLevels(1) = 0
        End If
            
        GetMultipleWaveform dataScaled, 2, styles, highLevels, lowLevels
    End If
    
    'Convert scaled  data to raw data
    err = BufferedAoCtrl1.SetData(CInt(BufferedAoCtrl1.ScanChannel.ChannelCount * pointPerPeriod), dataScaled)
    CheckError (err)
    
    'Start buffered AO in asynchronous
    err = BufferedAoCtrl1.Start
    CheckError (err)
    button_start.Enabled = False
End Sub

Private Sub checkBox_sineA_Click()
    checkBox_squareA.Picture = ImageList1.ListImages(2).Picture
    checkBox_triangleA.Picture = ImageList1.ListImages(3).Picture
    
    If checkBox_sineA.Value = Checked Then
        checkBox_sineA.Picture = ImageList1.ListImages(4).Picture
        formStyleA = sine
        isCheckedA = True
    Else
        checkBox_sineA.Picture = ImageList1.ListImages(1).Picture
        formStyleA = -1
        isCheckedA = False
    End If
End Sub

Private Sub checkBox_sineB_Click()
    checkBox_squareB.Picture = ImageList1.ListImages(2).Picture
    checkBox_triangleB.Picture = ImageList1.ListImages(3).Picture
    
    If checkBox_sineB.Value = Checked Then
        checkBox_sineB.Picture = ImageList1.ListImages(4).Picture
        formStyleB = sine
        isCheckedB = True
    Else
        checkBox_sineB.Picture = ImageList1.ListImages(1).Picture
        formStyleB = -1
        isCheckedB = False
    End If
End Sub

Private Sub checkBox_squareA_Click()
    checkBox_sineA.Picture = ImageList1.ListImages(1).Picture
    checkBox_triangleA.Picture = ImageList1.ListImages(3).Picture
    
    If checkBox_squareA.Value = Checked Then
        checkBox_squareA.Picture = ImageList1.ListImages(5).Picture
        formStyleA = square
        isCheckedA = True
    Else
        checkBox_squareA.Picture = ImageList1.ListImages(2).Picture
        formStyleA = -1
        isCheckedA = False
    End If
End Sub

Private Sub checkBox_squareB_Click()
    checkBox_sineB.Picture = ImageList1.ListImages(1).Picture
    checkBox_triangleB.Picture = ImageList1.ListImages(3).Picture
    
    If checkBox_squareB.Value = Checked Then
        checkBox_squareB.Picture = ImageList1.ListImages(5).Picture
        formStyleB = square
        isCheckedB = True
    Else
        checkBox_squareB.Picture = ImageList1.ListImages(2).Picture
        formStyleB = -1
        isCheckedB = False
    End If
End Sub

Private Sub checkBox_triangleA_Click()
    checkBox_sineA.Picture = ImageList1.ListImages(1).Picture
    checkBox_squareA.Picture = ImageList1.ListImages(2).Picture
    
    If checkBox_triangleA.Value = Checked Then
        checkBox_triangleA.Picture = ImageList1.ListImages(6).Picture
        formStyleA = triangle
        isCheckedA = True
    Else
        checkBox_triangleA.Picture = ImageList1.ListImages(3).Picture
        formStyleA = -1
        isCheckedA = False
    End If
End Sub

Private Sub checkBox_triangleB_Click()
    checkBox_sineB.Picture = ImageList1.ListImages(1).Picture
    checkBox_squareB.Picture = ImageList1.ListImages(2).Picture
    
    If checkBox_triangleB.Value = Checked Then
        checkBox_triangleB.Picture = ImageList1.ListImages(6).Picture
        formStyleB = triangle
        isCheckedB = True
    Else
        checkBox_triangleB.Picture = ImageList1.ListImages(3).Picture
        formStyleB = -1
        isCheckedB = False
    End If
End Sub

Private Sub Form_Load()
    ' The default device of project is demo device, users can choose other devices according to their needs.
    If Not BufferedAoCtrl1.Initialized Then
        MsgBox "Please select a device with DAQNavi wizard!"
        End
    End If
    
    'initialize the formCloseFlag
    formCloseFlag = False
    
    'set the ChannelCount
    If BufferedAoCtrl1.ScanChannel.ChannelCount > 1 Then
        BufferedAoCtrl1.ScanChannel.ChannelCount = 2
    End If
    
    'initialize the sine as the default choice
    checkBox_sineA.Value = Checked
    checkBox_sineA.Picture = ImageList1.ListImages(4).Picture
    formStyleA = sine
    isCheckedA = True
    
    If BufferedAoCtrl1.ScanChannel.ChannelCount > 1 Then
        checkBox_sineB.Value = Checked
        checkBox_sineB.Picture = ImageList1.ListImages(4).Picture
        formStyleB = sine
        isCheckedB = True
    End If
    
    'set title of the form.
    Dim devNum As Long
    Dim devDesc As String
    Dim devMode As AccessMode
    Dim modIndex As Long
    BufferedAoCtrl1.getSelectedDevice devNum, devDesc, devMode, modIndex
    AsynchronousOneWaveformAO.Caption = "Asynchronous One Waveform AO(" + devDesc + ")"
    
    ConfigurePanel
       
End Sub

Private Sub Form_Unload(Cancel As Integer)
    formCloseFlag = True
End Sub
