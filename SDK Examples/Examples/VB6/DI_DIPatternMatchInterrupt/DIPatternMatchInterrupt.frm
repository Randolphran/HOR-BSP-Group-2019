VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{1752FF26-D6C9-4BC8-BFE9-7D0CA26DED89}#1.0#0"; "BDaqOcx.dll"
Object = "{82351433-9094-11D1-A24B-00A0C932C7DF}#1.5#0"; "AniGIF.ocx"
Begin VB.Form DIPatternMatchInterrupt 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "DI Pattern Match Interrupt"
   ClientHeight    =   4185
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   6540
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   279
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   436
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton buttonStart 
      Caption         =   "Start"
      Height          =   375
      Left            =   5040
      TabIndex        =   2
      Top             =   1200
      Width           =   1335
   End
   Begin VB.CommandButton buttonStop 
      Caption         =   "Stop"
      Height          =   375
      Left            =   5040
      TabIndex        =   1
      Top             =   1920
      Width           =   1335
   End
   Begin AniGIFCtrl.AniGIF ExecutionStatus 
      Height          =   375
      Left            =   4080
      TabIndex        =   0
      Top             =   120
      Width           =   375
      BackColor       =   -2147483648
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
      GIF             =   "DIPatternMatchInterrupt.frx":0000
      ExtendWidth     =   661
      ExtendHeight    =   661
      Loop            =   0
      AutoRewind      =   0   'False
      Synchronized    =   -1  'True
   End
   Begin MSComctlLib.ListView listViewForData 
      Height          =   3615
      Left            =   240
      TabIndex        =   3
      Top             =   480
      Width           =   4695
      _ExtentX        =   8281
      _ExtentY        =   6376
      View            =   3
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      FlatScrollBar   =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      Appearance      =   1
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      NumItems        =   0
   End
   Begin BDaqOcxLibCtl.InstantDiCtrl InstantDiCtrl1 
      Left            =   5400
      OleObjectBlob   =   "DIPatternMatchInterrupt.frx":0672
      Top             =   3360
   End
   Begin VB.Image Image1 
      Height          =   6600
      Left            =   0
      Picture         =   "DIPatternMatchInterrupt.frx":070B
      Top             =   0
      Width           =   7500
   End
End
Attribute VB_Name = "DIPatternMatchInterrupt"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private matchedNum As Integer

Private Sub InitListView()
    'add the columnHeaders for every column
    listViewForData.ColumnHeaders.Add , , , 0
    listViewForData.ColumnHeaders.Add , , " Matched No#", 100
    Dim text As String
    text = "DI ports value (Port 0~" + Str(InstantDiCtrl1.Features.PortCount - 1) + ")"
    listViewForData.ColumnHeaders.Add , , text, 213
     
    'change the columnHeader2.Width according the portCount
    If InstantDiCtrl1.Features.PortCount > 10 Then
        listViewForData.ColumnHeaders(3).Width = 213 + 22 * (InstantDiCtrl1.Features.PortCount - 10)
        listViewForData.Height = 241
    Else
        listViewForData.ColumnHeaders(3).Width = 213
        listViewForData.Height = 225
    End If
End Sub
Private Sub HandleError(ByVal err As ErrorCode)
    Dim utility As BDaqUtility
    Dim errorMessage As String
    Dim res As ErrorCode
        
    Set utility = New BDaqUtility
        
    res = utility.EnumToString("ErrorCode", err, errorMessage)
    
    If err <> Success Then
        MsgBox "Sorry ! There're some errors happened, the error code is: " & errorMessage, , "DIPatternMatchInterrupt"
    End If
End Sub
Private Sub buttonStart_Click()
    Dim err As ErrorCode
    err = Success
    matchedNum = 0
    
    listViewForData.ListItems.Clear
    err = InstantDiCtrl1.SnapStart
    If err <> Success Then
        HandleError (err)
        Exit Sub
    End If
    
    buttonStop.Enabled = True
    buttonStart.Enabled = False
    ExecutionStatus.Playing = True
End Sub

Private Sub buttonStop_Click()
    Dim err As ErrorCode
    err = Success
    
    err = InstantDiCtrl1.SnapStop
    If err <> Success Then
        HandleError (err)
        Exit Sub
    End If
    
    buttonStart.Enabled = True
    buttonStop.Enabled = False
    ExecutionStatus.Playing = False
End Sub

Private Sub Form_Load()
    'The default device of project is demo device, users can choose other devices according to their needs.
    If Not InstantDiCtrl1.Initialized Then
        MsgBox "Please select a device with DAQNavi wizard!", , "DI_PatternMatch"
        End
    End If
    
    'set the title
    Dim devNum As Long
    Dim devDesc As String
    Dim devMode As AccessMode
    Dim modIndex As Long
    InstantDiCtrl1.getSelectedDevice devNum, devDesc, devMode, modIndex
    DIPatternMatchInterrupt.Caption = "DI Pattern Match Interrupt(" + devDesc + ")"
    
    InitListView
    
    buttonStop.Enabled = False
    ExecutionStatus.Playing = False
End Sub

Private Sub InstantDiCtrl1_PatternMatch(ByVal SrcNum As Long, PortData() As Byte)
    If listViewForData.ListItems.Count > 10 Then
        listViewForData.ListItems.Remove (1)
    End If

    listViewForData.ListItems.Add

    'column 0
    listViewForData.ListItems(listViewForData.ListItems.Count).ListSubItems.Add
    matchedNum = matchedNum + 1
    listViewForData.ListItems(listViewForData.ListItems.Count).ListSubItems(1).text = "         " + Str(matchedNum)

    'column 1
    listViewForData.ListItems(listViewForData.ListItems.Count).ListSubItems.Add
    Dim valueString As String
    valueString = ""
    Dim j As Long
    For j = 0 To UBound(PortData) - LBound(PortData)
        valueString = valueString + Hex(PortData(j))
        If j < UBound(PortData) - LBound(PortData) Then
            valueString = valueString + ", "
        End If
    Next j
    listViewForData.ListItems(listViewForData.ListItems.Count).ListSubItems(2).text = valueString
End Sub
