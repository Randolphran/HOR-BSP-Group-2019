Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms
Imports System.Threading
Imports Automation.BDaq


Partial Public Class PulseOutputwithTimerInterruptForm
	Inherits Form
	Private m_TPevtCount As Integer = 0

	Public Sub New()
		InitializeComponent()
	End Sub
	Public Delegate Sub SetOccuredCount()

	Private Sub m_TimerPulseCtrl_TimerTick(ByVal sender As System.Object, ByVal e As Automation.BDaq.CntrEventArgs)
		Try
			m_TPevtCount += 1
			Invoke(New SetOccuredCount(AddressOf SetOccuredCountMethod))
		Catch ex As Exception
		End Try
	End Sub

	Private Sub PulseOutputwithTimerInterruptForm_Load(ByVal sender As Object, ByVal e As EventArgs) Handles MyBase.Load
		' The default device of project is demo device, users can choose other devices according to their needs.
		If Not m_TimerPulseCtrl.Initialized Then
			MessageBox.Show("Please select a device in control property!")
			Me.Close()
			Return
		End If

		'set title of the form.
		Dim description As String = m_TimerPulseCtrl.SelectedDevice.Description
		Me.Text = "Pulse Output with Timer Interrupt - Run(" & description & ")"

		Dim tmrChannel() As TmrChannel = m_TimerPulseCtrl.Channels
		desiredFrequency.Text = tmrChannel(m_TimerPulseCtrl.ChannelStart).Frequency.ToString()
		label_eventCount.Enabled = False
		Stop_button.Enabled = False

		'Caution: When TimerTick interrupt is too frequent, the operating system may hang.
		'The following is the suggestion:
		'1.If you use the pulse output function only, you don't need to deal with TimerTick event.
		'2.If you want to use timer interrupt function, uncomment the following codes.

		'AddHandler m_TimerPulseCtrl.TimerTick, New EventHandler(Of CntrEventArgs)(AddressOf m_TimerPulseCtrl_TimerTick)

	End Sub

	Private Shared Sub ShowErrorMessage(ByVal e As Exception)
		Dim errorInfo As String
		errorInfo = "There's some error happened, the error information: "
		MessageBox.Show(errorInfo & e.Message)
	End Sub

	Private Sub Start_Click(ByVal sender As Object, ByVal e As EventArgs) Handles Start.Click
		' TimerPulse event count 
		m_TPevtCount = 0
		eventCount.Text = ""
		Dim tmrChannel() As TmrChannel = m_TimerPulseCtrl.Channels

		' Enable execution status
		ExecutionStatus.Enabled = True
		Try
			m_TimerPulseCtrl.Enabled = True
			generatedFrequency.Text = tmrChannel(m_TimerPulseCtrl.ChannelStart).Frequency.ToString()
		Catch ex As Exception
			ShowErrorMessage(ex)
			generatedFrequency.Text = ""
		End Try

		Stop_button.Enabled = True
		Start.Enabled = False
	End Sub

	Private Sub Stop_Click(ByVal sender As Object, ByVal e As EventArgs) Handles Stop_button.Click
		Try
			m_TimerPulseCtrl.Enabled = False
		Catch ex As Exception
			ShowErrorMessage(ex)
		End Try
		' Disable execution status
		ExecutionStatus.Enabled = False
		Start.Enabled = True
		Stop_button.Enabled = False
	End Sub

	Public Sub SetOccuredCountMethod()
		label_eventCount.Enabled = True
		eventCount.Text = m_TPevtCount.ToString()
	End Sub
End Class


