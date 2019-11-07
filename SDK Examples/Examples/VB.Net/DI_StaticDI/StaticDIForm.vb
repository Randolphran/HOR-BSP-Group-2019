Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms
Imports System.Drawing.Drawing2D
Imports Automation.BDaq

Imports System.Globalization

Public Class StaticDIForm
    Inherits Form
#Region ""
    Private m_portNum As Label()
    Private m_portHex As Label()
    Private m_pictrueBox As PictureBox(,)
    Private Const m_startPort As Integer = 0
    Private Const m_portCountShow As Integer = 4
#End Region

    Public Sub New()
        InitializeComponent()
    End Sub

    Public Sub New(ByVal deviceNumber As Integer)
        InitializeComponent()
        InstantDiCtrl1.SelectedDevice = New DeviceInformation(deviceNumber)
    End Sub

    Private Sub StaticDIForm_Load(ByVal sender As Object, ByVal e As EventArgs) Handles MyBase.Load
        'The default device of project is demo device, users can choose other devices according to their needs.
        If Not InstantDiCtrl1.Initialized Then
            MessageBox.Show("Please select a device in control property!", "StaticDI")
            Me.Close()
            Return
        End If

      Me.Text = "Static DI - Run(" + InstantDiCtrl1.SelectedDevice.Description + ")"

        m_portNum = New Label(m_portCountShow - 1) {PortNum0, PortNum1, PortNum2, PortNum3}
        m_portHex = New Label(m_portCountShow - 1) {PortHex0, PortHex1, PortHex2, PortHex3}
        m_pictrueBox = New PictureBox(m_portCountShow - 1, 7) {{pictureBox00, pictureBox01, pictureBox02, pictureBox03, pictureBox04, pictureBox05, _
         pictureBox06, pictureBox07}, {pictureBox10, pictureBox11, pictureBox12, pictureBox13, pictureBox14, pictureBox15, _
         pictureBox16, pictureBox17}, {pictureBox20, pictureBox21, pictureBox22, pictureBox23, pictureBox24, pictureBox25, _
         pictureBox26, pictureBox27}, {pictureBox30, pictureBox31, pictureBox32, pictureBox33, pictureBox34, pictureBox35, _
         pictureBox36, pictureBox37}}

        'enable the timer to read DI ports status
        timer1.Enabled = True
    End Sub

    Private Sub timer1_Tick(ByVal sender As Object, ByVal e As EventArgs) Handles timer1.Tick
        ' read Di port state
        Dim portData As Byte = 0
        Dim err As ErrorCode = ErrorCode.Success

        Dim i As Integer = 0
        While (i + m_startPort) < InstantDiCtrl1.Features.PortCount AndAlso i < m_portCountShow
            err = InstantDiCtrl1.Read(i + m_startPort, portData)
            If err <> ErrorCode.Success Then
                timer1.Enabled = False
                HandleError(err)
                Return
            End If

            m_portNum(i).Text = (i + m_startPort).ToString()
            m_portHex(i).Text = portData.ToString("X2")

            ' Set picture box state
            For j As Integer = 0 To 7
                m_pictrueBox(i, j).Image = imageList1.Images((portData >> j) And &H1)
                m_pictrueBox(i, j).Invalidate()
            Next
            i += 1
        End While
    End Sub

    Private Sub HandleError(ByVal err As ErrorCode)
        If err <> ErrorCode.Success Then
            MessageBox.Show("Sorry ! Some errors happened, the error code is: " & err.ToString(), "StaticDI")
        End If
    End Sub
End Class

