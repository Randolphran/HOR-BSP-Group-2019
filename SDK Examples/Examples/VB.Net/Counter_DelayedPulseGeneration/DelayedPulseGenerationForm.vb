Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms
Imports System.Collections
Imports System.Drawing.Drawing2D
Imports System.Threading
Imports System.Runtime.InteropServices
Imports Automation.BDaq


Partial Public Class DelayedPulseGenerationForm
    Inherits Form
	Private m_DelayedPulseCount As Integer

	Public Sub New()
		InitializeComponent()
	End Sub
	Public Delegate Sub SetOccuredCount()

	Private Sub m_OneShotCtrl_OneShot(ByVal sender As Object, ByVal e As CntrEventArgs)
		Try
			m_DelayedPulseCount += 1
			Invoke(New SetOccuredCount(AddressOf SetOccuredCountMethod))
		Catch ex As Exception
		End Try
	End Sub
	Private Sub DelayedPulseGenerationForm_Load(ByVal sender As Object, ByVal e As EventArgs) Handles MyBase.Load
		' The default device of project is demo device, users can choose other devices according to their needs.
		If Not m_OneShotCtrl.Initialized Then
			MessageBox.Show("Please select a device in control property!")
			Me.Close()
			Return
		End If
		'set title of the form.
		Dim description As String = m_OneShotCtrl.SelectedDevice.Description
		Me.Text = "Delayed Pulse Generation - Run(" & description & ")"

		Dim osChannel() As OsChannel = m_OneShotCtrl.Channels
		delayCount.Text = osChannel(m_OneShotCtrl.ChannelStart).DelayCount.ToString

		ExecutionStatus.Enabled = False
		label_shotCount.Enabled = False
		Stop_button.Enabled = False

		'Caution: When OneShot interrupt is too frequent, the operating system may hang.
		'The following is the suggestion:
		'1.If you generate delayed pulse only, you don't need to deal with OneShot event.
		'2.If you want to use OneShot interrupt function, uncomment the following codes.

		'AddHandler m_OneShotCtrl.OneShot, New EventHandler(Of CntrEventArgs)(AddressOf m_OneShotCtrl_OneShot)
	End Sub

	Private Shared Sub ShowErrorMessage(ByVal e As Exception)
		Dim errorInfo As String
		errorInfo = "There's some error happened, the error information: "
		MessageBox.Show(errorInfo & e.Message)
	End Sub

	Private Sub Start_Click(ByVal sender As Object, ByVal e As EventArgs) Handles Start_button.Click
		m_DelayedPulseCount = 0

		eventCount.Text = ""
		ExecutionStatus.Enabled = True
		Try
			m_OneShotCtrl.Enabled = True
		Catch ex As Exception
			ShowErrorMessage(ex)
		End Try

		Stop_button.Enabled = True
		Start_button.Enabled = False
	End Sub

	Private Sub Stop_Click(ByVal sender As Object, ByVal e As EventArgs) Handles Stop_button.Click
		Try
			m_OneShotCtrl.Enabled = False
		Catch ex As Exception
			ShowErrorMessage(ex)
		End Try
		Start_button.Enabled = True
		Stop_button.Enabled = False
		ExecutionStatus.Enabled = False
	End Sub

	Public Sub SetOccuredCountMethod()
		label_shotCount.Enabled = True
		eventCount.Text = m_DelayedPulseCount.ToString()
	End Sub
End Class



