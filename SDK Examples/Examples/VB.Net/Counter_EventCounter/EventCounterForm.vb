Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms
Imports System.Collections
Imports System.Drawing.Drawing2D
Imports Automation.BDaq

Partial Public Class EventCounterForm
    Inherits Form
    Private m_ECisRunning As Boolean = True
    Private m_isEventCountingReset As Boolean = True
    Const m_maxOfCounterValueList As Integer = 7
    ' The max value of lines of CounterValueList.
    Public Sub New()
        InitializeComponent()
    End Sub

	Private Sub EventCounterForm_Load(ByVal sender As Object, ByVal e As EventArgs) Handles MyBase.Load
		'The default device of project is demo device, users can choose other devices according to their needs.
		If Not m_EventCountCtrl.Initialized Then
			MessageBox.Show("Please select a device in control property!")
			Me.Close()
			Return
		End If
		Dim t As Integer = m_EventCountCtrl.Features.ChannelCountMax
		'set title of the form.
		Dim description As String = m_EventCountCtrl.SelectedDevice.Description
		Me.Text = "Event Counter - Run(" & description & ")"

		Timer1.Enabled = False
		Stop_button.Enabled = False
	End Sub

	Private Sub timer1_Tick(ByVal sender As Object, ByVal e As EventArgs) Handles Timer1.Tick
		Dim value As Integer
		Try
			If m_ECisRunning Then
				' Show event counting value
				m_EventCountCtrl.Read(value)
				CurCounterValue.Text = value.ToString()
			End If
		Catch ex As Exception
			ShowErrorMessage(ex)
		End Try
	End Sub

	Private Sub Start_Click(ByVal sender As Object, ByVal e As EventArgs) Handles Start_button.Click
		If m_isEventCountingReset = True Then
			CounterValueList.Items.Clear()
			Try
				m_EventCountCtrl.Enabled = True
				m_ECisRunning = True
				If False = Timer1.Enabled Then
					Timer1.Start()
				End If
				Stop_button.Enabled = True
				Start_button.Text = "Latch"
				m_isEventCountingReset = False
			Catch ex As Exception
				ShowErrorMessage(ex)
			End Try
		Else
			CounterValueList.Items.Add(CurCounterValue.Text)
			If CounterValueList.Items.Count > m_maxOfCounterValueList Then
				CounterValueList.Items.RemoveAt(0)
			End If
		End If
	End Sub

	Private Sub Stop_Click(ByVal sender As Object, ByVal e As EventArgs) Handles Stop_button.Click
		' Stop event counting
		Try
			m_EventCountCtrl.Enabled = False
			m_ECisRunning = False
		Catch ex As Exception
			ShowErrorMessage(ex)
		End Try

		m_isEventCountingReset = True
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


