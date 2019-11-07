Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms
Imports System.Threading
Imports Automation.BDaq


Partial Public Class PWMOutputForm
	Inherits Form
	' private double m_frequency;
	Private m_TPevtCount As Integer = 0

	Public Sub New()
		InitializeComponent()
	End Sub

	Private Sub PWMOutputForm_Load(ByVal sender As Object, ByVal e As EventArgs) Handles MyBase.Load
		' no device is selected
		If Not m_PwModulatorCtrl.Initialized Then
			MessageBox.Show("Please select a device in control property!")
			Me.Close()
			Return
		End If

		'set title of the form.
		Dim description As String = m_PwModulatorCtrl.SelectedDevice.Description
		Me.Text = "PWM Output - Run(" & description & ")"

		Dim poChannel() As PoChannel = m_PwModulatorCtrl.Channels
		desiredHiPeriod.Text = poChannel(m_PwModulatorCtrl.ChannelStart).PulseWidth.HiPeriod.ToString()
		desiredLoPeriod.Text = poChannel(m_PwModulatorCtrl.ChannelStart).PulseWidth.LoPeriod.ToString()
		Stop_button.Enabled = False
	End Sub

	Private Shared Sub ShowErrorMessage(ByVal e As Exception)
		Dim errorInfo As String
		errorInfo = "There's some error happened, the error information: "
		MessageBox.Show(errorInfo & e.Message)
	End Sub

	Private Sub Start_Click(ByVal sender As Object, ByVal e As EventArgs) Handles Start.Click
		' Enable execution status
		ExecutionStatus.Enabled = True
		Dim poChannel() As PoChannel = m_PwModulatorCtrl.Channels
		Try
			m_PwModulatorCtrl.Enabled = True
			generatedHiPeriod.Text = poChannel(m_PwModulatorCtrl.ChannelStart).PulseWidth.HiPeriod.ToString()
			generatedLoPeriod.Text = poChannel(m_PwModulatorCtrl.ChannelStart).PulseWidth.LoPeriod.ToString()
		Catch ex As Exception
			ShowErrorMessage(ex)
			generatedHiPeriod.Text = ""
			generatedLoPeriod.Text = ""
		End Try

		Stop_button.Enabled = True
		Start.Enabled = False
	End Sub

	Private Sub Stop_Click(ByVal sender As Object, ByVal e As EventArgs) Handles Stop_button.Click
		Try
			m_PwModulatorCtrl.Enabled = False
		Catch ex As Exception
			ShowErrorMessage(ex)
		End Try
		' Disable execution status
		ExecutionStatus.Enabled = False
		Start.Enabled = True
		Stop_button.Enabled = False
	End Sub

End Class


