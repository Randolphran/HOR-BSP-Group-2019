Imports System.Math
Imports Automation.BDaq

Structure LineTabparam
	Dim firstValue As Integer
	Dim increment As Integer
	Dim count As Integer
End Structure

Enum TabSel
	dispersed = 0
	lined
End Enum

Public Class ContinueCompareForm
	Inherits Form

	Private m_tabIndex As Integer
	Private m_contCompTabSel As TabSel

	'the event handler parameters
	Private matchCount As Integer
	Private endCount As Integer
	Private comTable(3) As Integer
	Private m_lineTabparam As LineTabparam
	Private evntEndID(7) As Integer
	Private evntMatchID(7) As Integer
	Private matched As Boolean
	Private counterValue As Integer

	Protected Delegate Sub UdCntrEvent(ByVal matchCount As Integer, ByVal endCount As Integer)

	Public Sub New()
		InitializeComponent()
	End Sub

	Public Sub New(ByVal deviceNumber As Integer)
		InitializeComponent()
		UdCounterCtrl1.SelectedDevice = New DeviceInformation(deviceNumber)
	End Sub

	Private Sub HandleError(ByVal err As Exception)
		MessageBox.Show("Sorry ! There're some errors happened, the error code is: " & err.ToString(), "Warning Information")
	End Sub

	Private Sub EnableCompareTable(ByVal enabled As Boolean)
		radTable.Enabled = enabled
		txtTab1Data0.Enabled = enabled
		txtTab1Data1.Enabled = enabled
		txtTab1Data2.Enabled = enabled
		txtTab2Data0.Enabled = enabled
		txtTab2Data1.Enabled = enabled
		txtTab2Data2.Enabled = enabled

		radInterval.Enabled = enabled
		txtInt1FirstValue.Enabled = enabled
		txtInt1Increment.Enabled = enabled
		txtInt1Count.Enabled = enabled
		txtInt2FirstValue.Enabled = enabled
		txtInt2Increment.Enabled = enabled
		txtInt2Count.Enabled = enabled
	End Sub

	Private Sub CreateDisperseTable(ByVal tabIndex As Integer, ByRef CompTab() As Integer)
		If tabIndex = 0 Then
			CompTab(0) = Int(txtTab1Data0.Text)
			CompTab(1) = Int(txtTab1Data1.Text)
			CompTab(2) = Int(txtTab1Data2.Text)
		Else
			CompTab(0) = Int(txtTab2Data0.Text)
			CompTab(1) = Int(txtTab2Data1.Text)
			CompTab(2) = Int(txtTab2Data2.Text)
		End If
	End Sub

	Private Sub CreateLineTable(ByVal tabIndex As Integer, ByRef param As LineTabparam)
		If tabIndex = 0 Then
			param.firstValue = Int(txtInt1FirstValue.Text)
			param.increment = Int(txtInt1Increment.Text)
			param.count = Int(txtInt1Count.Text)
		Else
			param.firstValue = Int(txtInt2FirstValue.Text)
			param.increment = Int(txtInt2Increment.Text)
			param.count = Int(txtInt2Count.Text)
		End If
	End Sub

	Private Sub btnStart_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnStart.Click
		'Set compare table
		Dim comTable(2) As Integer
		Dim param As LineTabparam

		If radTable.Checked Then
			m_contCompTabSel = TabSel.dispersed
		Else
			m_contCompTabSel = TabSel.lined
		End If

		If m_contCompTabSel = TabSel.dispersed Then
			CreateDisperseTable(0, comTable)
			UdCounterCtrl1.CompareSetTable(UdCounterCtrl1.ChannelStart, 3, comTable)
		Else
			CreateLineTable(0, param)
			UdCounterCtrl1.CompareSetInterval(UdCounterCtrl1.ChannelStart, param.firstValue, param.increment, param.count)
		End If

		matchCount = 0
		endCount = 0
		m_tabIndex = 0
		counterValue = 0

		'Start Snap Counter function.
		Try
			UdCounterCtrl1.Enabled = True
		Catch ex As Exception
			HandleError(ex)
		End Try

		Timer1.Enabled = True

		btnStart.Enabled = False
		btnStop.Enabled = True

		EnableCompareTable(False)

		txtPMCount.Text = "0"
		txtEndCount.Text = "0"
		txtCounterValue.Text = "0"
	End Sub

	Private Sub btnStop_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnStop.Click
		'Stop the user Timer
		Timer1.Enabled = False

		btnStart.Enabled = True
		btnStop.Enabled = False

		EnableCompareTable(True)

		Try
			UdCounterCtrl1.Enabled = False
		Catch ex As Exception
			HandleError(ex)
		End Try
	End Sub

	Private Sub ContinueCompareForm_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
		'The default device of project is PCI-1784.
		If Not UdCounterCtrl1.Initialized Then
			MsgBox("Please select a device with DAQNavi wizard!", , "Warning Information")
			End
		End If

		'set title of the form
		Me.Text = "Continue Compare(" + UdCounterCtrl1.SelectedDevice.Description + ")"

		m_tabIndex = 0

		'initialize the compare table
		txtTab1Data0.Text = "100"
		txtTab1Data1.Text = "340"
		txtTab1Data2.Text = "720"
		txtTab2Data0.Text = "1000"
		txtTab2Data1.Text = "1980"
		txtTab2Data2.Text = "2510"

		txtInt1FirstValue.Text = "150"
		txtInt1Increment.Text = "3"
		txtInt1Count.Text = "3"
		txtInt2FirstValue.Text = "210"
		txtInt2Increment.Text = "3"
		txtInt2Count.Text = "3"

		btnStart.Enabled = True
		btnStop.Enabled = False

		'initialize the event handler parameters
		matchCount = 0
		endCount = 0
		matched = False
		Dim i As Integer
		For i = 0 To 7
			evntEndID(i) = 422 + i		'EvtCntCompareTableEnd0 = 422
			evntMatchID(i) = 414 + i	'EvtCntPatternMatch0 = 414
		Next
	End Sub

	Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
		Try
			UdCounterCtrl1.Enabled = True
		Catch ex As Exception
			Timer1.Enabled = False
			HandleError(ex)
		End Try
		UdCounterCtrl1.Read(counterValue)
		txtCounterValue.Text = "0x" + counterValue.ToString("X")
	End Sub

	Private Sub DataHandler(ByVal matchCount As Integer, ByVal endCount As Integer)
		txtPMCount.Text = Str(matchCount)
		txtEndCount.Text = Str(endCount)
	End Sub

	Private Sub UdCounterCtrl1_UdCntrEvent_1(ByVal sender As System.Object, ByVal e As Automation.BDaq.UdCntrEventArgs) Handles UdCounterCtrl1.UdCntrEvent
		'refresh the snap value list
		If evntEndID(UdCounterCtrl1.ChannelStart) = e.Id Then
			endCount = endCount + 1
			m_tabIndex = m_tabIndex + 1
			If m_contCompTabSel = TabSel.dispersed Then
				CreateDisperseTable(m_tabIndex Mod 2, comTable)
				UdCounterCtrl1.CompareSetTable(UdCounterCtrl1.ChannelStart, 3, comTable)
			Else
				CreateLineTable(m_tabIndex Mod 2, m_lineTabparam)
				UdCounterCtrl1.CompareSetInterval(UdCounterCtrl1.ChannelStart, m_lineTabparam.firstValue, m_lineTabparam.increment, m_lineTabparam.count)
			End If

			matched = True
		Else
			If evntMatchID(UdCounterCtrl1.ChannelStart) = e.Id Then
				matchCount = matchCount + 1
				matched = True
			End If
		End If

		If matched Then
			Try
				Me.Invoke(New UdCntrEvent(AddressOf DataHandler), New Object() {matchCount, endCount})
			Catch ex As System.Exception
			End Try

			matched = False
		End If
	End Sub
End Class
