Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms
Imports System.Collections
Imports System.Drawing.Drawing2D
Imports Automation.BDaq

Partial Public Class PulseWidthMeasurementForm
	Inherits Form
	Private m_ECisRunning As Boolean = True
	Private m_isPwMeterReset As Boolean = True
	Const m_maxOfCounterValueList As Integer = 7
	' The max value of lines of CounterValueList.
	Public Sub New()
		InitializeComponent()
	End Sub

	Private Sub PulseWidthMeasurementrForm_Load(ByVal sender As Object, ByVal e As EventArgs) Handles MyBase.Load
		'no device is selected
		If Not m_PwMeterCtrl.Initialized Then
			MessageBox.Show("Please select a device in control property!")
			Me.Close()
			Return
		End If
		Dim t As Integer = m_PwMeterCtrl.Features.ChannelCountMax
		'set title of the form.
		Dim description As String = m_PwMeterCtrl.SelectedDevice.Description
		Me.Text = "Pulse Width Measurement - Run(" & description & ")"

		Timer1.Enabled = False
		Stop_button.Enabled = False
	End Sub

	Private Sub timer1_Tick(ByVal sender As Object, ByVal e As EventArgs) Handles Timer1.Tick
		Dim value As PulseWidth

		Try
			If m_ECisRunning Then
				' Show event counting value
				m_PwMeterCtrl.Read(value)
				CurHiPeriod.Text = value.HiPeriod.ToString("F5")
				CurLoPeriod.Text = value.LoPeriod.ToString("F5")
			End If
		Catch ex As Exception
			ShowErrorMessage(ex)
		End Try
	End Sub

	Private Sub Start_Click(ByVal sender As Object, ByVal e As EventArgs) Handles Start_button.Click
		If m_isPwMeterReset = True Then
			CounterValueList.Items.Clear()
			Try
				m_PwMeterCtrl.Enabled = True
				m_ECisRunning = True
				If False = Timer1.Enabled Then
					Timer1.Start()
				End If
				Stop_button.Enabled = True
				Start_button.Text = "Latch"
				m_isPwMeterReset = False
			Catch ex As Exception
				ShowErrorMessage(ex)
			End Try
		Else
			CounterValueList.Items.Add("High:" + CurHiPeriod.Text + " Low:" + CurLoPeriod.Text)
			If CounterValueList.Items.Count > m_maxOfCounterValueList Then
				CounterValueList.Items.RemoveAt(0)
			End If
		End If
	End Sub

	Private Sub Stop_Click(ByVal sender As Object, ByVal e As EventArgs) Handles Stop_button.Click
		' Stop event counting
		Try
			m_PwMeterCtrl.Enabled = False
			m_ECisRunning = False
		Catch ex As Exception
			ShowErrorMessage(ex)
		End Try

		m_isPwMeterReset = True
		Start_button.Enabled = True
		Start_button.Text = "Start"
		Stop_button.Enabled = False
		'stop the timer
		If False = m_ECisRunning Then
			Timer1.Enabled = False
		End If
	End Sub
	Private Shared Sub ShowErrorMessage(ByVal e As Exception)
		Dim errorInfo As String
		errorInfo = "There's some error happened, the error information: "
		MessageBox.Show(errorInfo & e.Message)
	End Sub
End Class


