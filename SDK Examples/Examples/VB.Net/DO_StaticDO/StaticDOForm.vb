Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms
Imports System.Drawing.Drawing2D
Imports System.Globalization
Imports Automation.BDaq


Public Class StaticDOForm
    Inherits Form
#Region ""
    Private m_portNum As Label()
    Private m_portHex As Label()
    Private m_pictrueBox As PictureBox(,)

#End Region

    Public Sub New()
        InitializeComponent()
    End Sub

    Public Sub New(ByVal deviceNumber As Integer)
        InitializeComponent()
        InstantDoCtrl1.SelectedDevice = New DeviceInformation(deviceNumber)
    End Sub

    Private Sub StaticDOForm_Load(ByVal sender As Object, ByVal e As EventArgs) Handles MyBase.Load
        'The default device of project is demo device, users can choose other devices according to their needs.
        If Not InstantDoCtrl1.Initialized Then
            MessageBox.Show("Please select a device in control property!", "StaticDO")
            Me.Close()
            Return
        End If

      Me.Text = "Static DO - Run(" + InstantDoCtrl1.SelectedDevice.Description + ")"

        m_portNum = New Label(ConstVal.PortCountShow - 1) {PortNum0, PortNum1, PortNum2, PortNum3}
        m_portHex = New Label(ConstVal.PortCountShow - 1) {PortHex0, PortHex1, PortHex2, PortHex3}
        m_pictrueBox = New PictureBox(ConstVal.PortCountShow - 1, 7) {{pictureBox00, pictureBox01, pictureBox02, pictureBox03, pictureBox04, pictureBox05, _
         pictureBox06, pictureBox07}, {pictureBox10, pictureBox11, pictureBox12, pictureBox13, pictureBox14, pictureBox15, _
         pictureBox16, pictureBox17}, {pictureBox20, pictureBox21, pictureBox22, pictureBox23, pictureBox24, pictureBox25, _
         pictureBox26, pictureBox27}, {pictureBox30, pictureBox31, pictureBox32, pictureBox33, pictureBox34, pictureBox35, _
         pictureBox36, pictureBox37}}

        InitializePortState()
    End Sub

    Private Sub InitializePortState()
		Dim portData As Byte = 0
		Dim portDir As Byte = &HFF
		Dim err As ErrorCode = ErrorCode.Success
		Dim mask As Byte() = InstantDoCtrl1.Features.DoDataMask
		Dim i As Integer = 0
		While (i + ConstVal.StartPort) < InstantDoCtrl1.Features.PortCount AndAlso i < ConstVal.PortCountShow
			err = InstantDoCtrl1.Read(i + ConstVal.StartPort, portData)
			If err <> ErrorCode.Success Then
				HandleError(err)
				Return
			End If

			m_portNum(i).Text = (i + ConstVal.StartPort).ToString()
			m_portHex(i).Text = portData.ToString("X2")

			If InstantDoCtrl1.Ports IsNot Nothing Then
				portDir = CByte(InstantDoCtrl1.Ports(i + ConstVal.StartPort).Direction)
			End If

			' Set picture box state
			For j As Integer = 0 To 7
				If ((portDir >> j) And &H1) = 0 OrElse ((mask(i) >> j) And &H1) = 0 Then
					' Bit direction is input.
					m_pictrueBox(i, j).Image = imageList1.Images(2)
					m_pictrueBox(i, j).Enabled = False
				Else
					AddHandler m_pictrueBox(i, j).Click, New EventHandler(AddressOf PictureBox_Click)
					m_pictrueBox(i, j).Tag = New DoBitInformation((portData >> j) And &H1, i + ConstVal.StartPort, j)
					m_pictrueBox(i, j).Image = imageList1.Images((portData >> j) And &H1)
				End If
				m_pictrueBox(i, j).Invalidate()
			Next
			i += 1
		End While
    End Sub

    Private Sub HandleError(ByVal err As ErrorCode)
        If err <> ErrorCode.Success Then
            MessageBox.Show("Sorry ! There're some errors happened, the error code is: " & err.ToString())
        End If
    End Sub

    Private Sub PictureBox_Click(ByVal sender As Object, ByVal e As EventArgs)
        Dim err As ErrorCode = ErrorCode.Success
        Dim box As PictureBox = DirectCast(sender, PictureBox)
        Dim boxInfo As DoBitInformation = CType(box.Tag, DoBitInformation)

        boxInfo.BitValue = (Not CInt((boxInfo).BitValue)) And &H1
        box.Tag = boxInfo
        box.Image = imageList1.Images(boxInfo.BitValue)
        box.Invalidate()

        ' refresh hex
        Dim state As Integer = Int32.Parse(m_portHex(boxInfo.PortNum - ConstVal.StartPort).Text, NumberStyles.AllowHexSpecifier)
        state = state And Not (&H1 << boxInfo.BitNum)
        state = state Or boxInfo.BitValue << boxInfo.BitNum

        m_portHex(boxInfo.PortNum - ConstVal.StartPort).Text = state.ToString("X2")
        err = InstantDoCtrl1.Write(boxInfo.PortNum, CByte(state))
        If err <> ErrorCode.Success Then
            HandleError(err)
        End If
    End Sub
End Class

Public Structure DoBitInformation
#Region "fields"
   Private m_bitValue As Integer
   Private m_portNum As Integer
   Private m_bitNum As Integer
#End Region

   Public Sub New(ByVal bitvalue As Integer, ByVal portNum As Integer, ByVal bitNum As Integer)
      m_bitValue = bitvalue
      m_portNum = portNum
      m_bitNum = bitNum
   End Sub

#Region "Properties"
   Public Property BitValue() As Integer
      Get
         Return m_bitValue
      End Get
      Set(ByVal value As Integer)
         m_bitValue = value And &H1
      End Set
   End Property
   Public Property PortNum() As Integer
      Get
         Return m_portNum
      End Get
      Set(ByVal value As Integer)
         If (value - ConstVal.StartPort) >= 0 AndAlso (value - ConstVal.StartPort) <= (ConstVal.PortCountShow - 1) Then
            m_portNum = value
         End If
      End Set
   End Property
   Public Property BitNum() As Integer
      Get
         Return m_bitNum
      End Get
      Set(ByVal value As Integer)
         If value >= 0 AndAlso value <= 7 Then
            m_bitNum = value
         End If
      End Set
   End Property
#End Region
End Structure

Public NotInheritable Class ConstVal
   Private Sub New()
   End Sub
   Public Const StartPort As Integer = 0
   Public Const PortCountShow As Integer = 4
End Class
