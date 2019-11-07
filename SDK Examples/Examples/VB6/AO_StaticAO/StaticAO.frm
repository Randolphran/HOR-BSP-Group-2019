VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "mscomctl.ocx"
Object = "{1752FF26-D6C9-4BC8-BFE9-7D0CA26DED89}#1.0#0"; "BDaqOcx.dll"
Begin VB.Form StaticAO 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Static AO"
   ClientHeight    =   6795
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   6060
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   453
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   404
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox textBox_highLevelA 
      Alignment       =   1  'Right Justify
      BorderStyle     =   0  'None
      Height          =   195
      Left            =   1200
      TabIndex        =   17
      Text            =   "5"
      Top             =   1320
      Width           =   975
   End
   Begin VB.CommandButton button_manualB 
      Height          =   750
      Left            =   4560
      Picture         =   "StaticAO.frx":0000
      Style           =   1  'Graphical
      TabIndex        =   16
      Top             =   4560
      Width           =   750
   End
   Begin VB.CommandButton button_manualA 
      Height          =   750
      Left            =   4560
      Picture         =   "StaticAO.frx":1DF4
      Style           =   1  'Graphical
      TabIndex        =   15
      Top             =   1800
      Width           =   750
   End
   Begin VB.Timer timer_outputData 
      Enabled         =   0   'False
      Interval        =   100
      Left            =   120
      Top             =   3840
   End
   Begin MSComctlLib.Slider trackBar_Scroll 
      Height          =   375
      Left            =   2280
      TabIndex        =   11
      Top             =   6000
      Width           =   1695
      _ExtentX        =   2990
      _ExtentY        =   661
      _Version        =   393216
      Min             =   10
      Max             =   1000
      SelStart        =   50
      TickStyle       =   3
      TickFrequency   =   100
      Value           =   50
   End
   Begin VB.CheckBox checkBox_triangleB 
      Height          =   750
      Left            =   3120
      Picture         =   "StaticAO.frx":3BE8
      Style           =   1  'Graphical
      TabIndex        =   10
      Top             =   4560
      Width           =   750
   End
   Begin VB.CheckBox checkBox_squareB 
      Height          =   750
      Left            =   2040
      Picture         =   "StaticAO.frx":59DC
      Style           =   1  'Graphical
      TabIndex        =   9
      Top             =   4560
      Width           =   750
   End
   Begin VB.CheckBox checkBox_sineB 
      Height          =   750
      Left            =   960
      Picture         =   "StaticAO.frx":77CE
      Style           =   1  'Graphical
      TabIndex        =   8
      Top             =   4560
      Width           =   750
   End
   Begin VB.CheckBox checkBox_triangleA 
      Height          =   750
      Left            =   3120
      Picture         =   "StaticAO.frx":95C2
      Style           =   1  'Graphical
      TabIndex        =   7
      Top             =   1800
      Width           =   750
   End
   Begin VB.CheckBox checkBox_squareA 
      Height          =   750
      Left            =   2040
      Picture         =   "StaticAO.frx":B3B6
      Style           =   1  'Graphical
      TabIndex        =   6
      Top             =   1800
      Width           =   750
   End
   Begin VB.CheckBox checkBox_sineA 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   750
      Left            =   960
      Picture         =   "StaticAO.frx":D1A8
      Style           =   1  'Graphical
      TabIndex        =   5
      Top             =   1800
      Width           =   750
   End
   Begin MSComctlLib.ImageList ImageList1 
      Left            =   120
      Top             =   2880
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
            Picture         =   "StaticAO.frx":EF9C
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "StaticAO.frx":10DA0
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "StaticAO.frx":12BA2
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "StaticAO.frx":149A6
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "StaticAO.frx":167AA
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "StaticAO.frx":185AE
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.TextBox textBox_valueB 
      Alignment       =   1  'Right Justify
      BorderStyle     =   0  'None
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   4440
      TabIndex        =   4
      Text            =   "2.5"
      Top             =   4080
      Width           =   855
   End
   Begin VB.TextBox textBox_lowLevelB 
      Alignment       =   1  'Right Justify
      BorderStyle     =   0  'None
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   2640
      TabIndex        =   3
      Text            =   "-5"
      Top             =   4080
      Width           =   975
   End
   Begin VB.TextBox textBox_highLevelB 
      Alignment       =   1  'Right Justify
      BorderStyle     =   0  'None
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   1200
      TabIndex        =   2
      Text            =   "5"
      Top             =   4080
      Width           =   1050
   End
   Begin VB.TextBox textBox_lowLevelA 
      Alignment       =   1  'Right Justify
      BorderStyle     =   0  'None
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   2640
      TabIndex        =   1
      Text            =   "-5"
      Top             =   1320
      Width           =   975
   End
   Begin VB.TextBox textBox_valueA 
      Alignment       =   1  'Right Justify
      BorderStyle     =   0  'None
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   195
      Left            =   4440
      TabIndex        =   0
      Text            =   "2.5"
      Top             =   1320
      Width           =   855
   End
   Begin BDaqOcxLibCtl.InstantAoCtrl InstantAoCtrl1 
      Left            =   120
      OleObjectBlob   =   "StaticAO.frx":1A3B2
      Top             =   5640
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
      Height          =   225
      Left            =   4320
      TabIndex        =   14
      Top             =   3120
      Width           =   255
   End
   Begin VB.Label label_chanA 
      BackColor       =   &H80000009&
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
      Height          =   225
      Left            =   4320
      TabIndex        =   13
      Top             =   360
      Width           =   255
   End
   Begin VB.Label label_interval 
      Caption         =   "50ms"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   4080
      TabIndex        =   12
      Top             =   6120
      Width           =   855
   End
   Begin VB.Image imagevalue 
      Height          =   6975
      Left            =   0
      Picture         =   "StaticAO.frx":1A463
      Stretch         =   -1  'True
      ToolTipText     =   "0"
      Top             =   -120
      Width           =   6135
   End
End
Attribute VB_Name = "StaticAO"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
 Option Explicit
 
 Private channelStart As Integer
 Private channelCount As Integer
 Private pointPerPeriod As Integer
 Private dataScaled(1) As Double
 Private wavePointsIndexA As Integer
 Private wavePointsIndexB As Integer
 Private highLevelA As Double
 Private lowLevelA As Double
 Private highLevelB As Double
 Private lowLevelB As Double
 Private isCheckedA As Boolean
 Private isCheckedB As Boolean
 Private err As ErrorCode
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
    Dim offset As Double
    offset = (highLevel + lowLevel) / 2
    Dim data As Double
    data = 0
    
    Select Case style
        Case WaveformStyle.sine
            data = amplitude * Math.Sin(index * 2# * PI / pointPerPeriod) + offset
        Case WaveformStyle.triangle
            If index < (pointPerPeriod / 4#) Then
               data = amplitude * (index / (pointPerPeriod / 4#)) + offset
            ElseIf index < 3 * (pointPerPeriod / 4#) Then
               data = amplitude * ((2# * (pointPerPeriod / 4#) - index) / (pointPerPeriod / 4#)) + offset
            Else
               data = amplitude * ((index - pointPerPeriod) / (pointPerPeriod / 4#)) + offset
            End If
        Case WaveformStyle.square
            If (index >= 0) And (index < (pointPerPeriod / 2)) Then
               data = amplitude * 1 + offset
            Else
               data = amplitude * (-1) + offset
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
        timer_outputData.Enabled = False
        MsgBox "Error: " & errorMessage
    End If
 End Sub
 
 Private Sub ConfigurePanel()
    If InstantAoCtrl1.channelCount = 1 Then
        channelStart = 0
        channelCount = 1
        
        checkBox_sineB.Enabled = False
        checkBox_squareB.Enabled = False
        checkBox_triangleB.Enabled = False
        textBox_highLevelB.Enabled = False
        textBox_lowLevelB.Enabled = False
        textBox_valueB.Enabled = False
        button_manualB.Enabled = False
        label_chanB.Caption = " "
    Else
        channelStart = 0
        channelCount = 2
        checkBox_sineB.Enabled = True
        checkBox_squareB.Enabled = True
        checkBox_triangleB.Enabled = True
        textBox_highLevelB.Enabled = True
        textBox_lowLevelB.Enabled = True
        textBox_valueB.Enabled = True
        button_manualB.Enabled = True
        label_chanB.Caption = Str(channelStart + 1)
    End If
    label_chanA.Caption = Str(channelStart)
        
 End Sub
 
Private Sub button_manualA_Click()
    checkBox_sineA.Value = Unchecked
    checkBox_squareA.Value = Unchecked
    checkBox_triangleA.Value = Unchecked
    
    checkBox_sineA.Picture = ImageList1.ListImages(1).Picture
    checkBox_squareA.Picture = ImageList1.ListImages(2).Picture
    checkBox_triangleA.Picture = ImageList1.ListImages(3).Picture
    
    isCheckedA = False
    dataScaled(0) = CDbl(textBox_valueA.Text)
End Sub

Private Sub button_manualB_Click()
    checkBox_sineB.Value = Unchecked
    checkBox_squareB.Value = Unchecked
    checkBox_triangleB.Value = Unchecked
    
    checkBox_sineB.Picture = ImageList1.ListImages(1).Picture
    checkBox_squareB.Picture = ImageList1.ListImages(2).Picture
    checkBox_triangleB.Picture = ImageList1.ListImages(3).Picture
    
    isCheckedB = False
    dataScaled(1) = CDbl(textBox_valueB.Text)
End Sub

Private Sub checkBox_sineA_Click()
    highLevelA = Val(textBox_highLevelA.Text)
    lowLevelA = Val(textBox_lowLevelA.Text)
    
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
    highLevelB = Val(textBox_highLevelB.Text)
    lowLevelB = Val(textBox_lowLevelB.Text)
    
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
    highLevelA = Val(textBox_highLevelA.Text)
    lowLevelA = Val(textBox_lowLevelA.Text)
    
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
    highLevelB = Val(textBox_highLevelB.Text)
    lowLevelB = Val(textBox_lowLevelB.Text)
    
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
    highLevelA = Val(textBox_highLevelA.Text)
    lowLevelA = Val(textBox_lowLevelA.Text)
    
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
    highLevelB = Val(textBox_highLevelB.Text)
    lowLevelB = Val(textBox_lowLevelB.Text)
    
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
    'initialize these variables
    channelStart = 0
    channelCount = 0
    pointPerPeriod = 400
    wavePointsIndexA = 0
    wavePointsIndexB = 0
    err = Success
    
    'initialize a timer which drive the data acquisition.
    timer_outputData.Interval = 50
    
    'The default device of project is demo device, users can choose other devices according to their needs.
    If Not InstantAoCtrl1.Initialized Then
        MsgBox "Please select a device with DAQNavi wizard!"
        End
    End If
    
    'set title of the form.
    Dim devNum As Long
    Dim devDesc As String
    Dim devMode As AccessMode
    Dim modIndex As Long
    InstantAoCtrl1.getSelectedDevice devNum, devDesc, devMode, modIndex
    StaticAO.Caption = "Static AO(" + devDesc + ")"
    
    ConfigurePanel
    timer_outputData.Enabled = True
    
End Sub

Private Sub timer_outputData_Timer()
    If isCheckedA Then
        dataScaled(0) = GetOnePoint(formStyleA, wavePointsIndexA, highLevelA, lowLevelA)
        wavePointsIndexA = wavePointsIndexA + 1
         
        If wavePointsIndexA = pointPerPeriod Then
            wavePointsIndexA = 0
        End If
    End If
    
    If isCheckedB Then
        If channelCount > 1 Then
            dataScaled(1) = GetOnePoint(formStyleB, wavePointsIndexB, highLevelB, lowLevelB)
            wavePointsIndexB = wavePointsIndexB + 1
        End If
        
        If wavePointsIndexB = pointPerPeriod Then
            wavePointsIndexB = 0
        End If
    End If
    
    err = InstantAoCtrl1.WriteChannels(channelStart, channelCount, dataScaled)
    CheckError (err)
End Sub

Private Sub trackBar_Scroll_Scroll()
    timer_outputData.Interval = trackBar_Scroll.Value
    label_interval.Caption = Str(trackBar_Scroll.Value) + "ms"
End Sub
