Imports System.Math
Imports Automation.BDaq


Public Class UpDownCounterForm
	Inherits Form

	Private cntrValue As Integer

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

	Private Sub ConfiguratePanel()
		cmbResetValue.Items.Clear()

		'for reset value
		Dim resetValues() As Integer
		resetValues = UdCounterCtrl1.Features.UdInitialValues

		Dim count As Integer
		count = UBound(resetValues) - LBound(resetValues) + 1

		Dim i As Integer
		i = 0
		Dim valueStr As String
		For i = 0 To count - 1
			If resetValues(i) <> -1 Then
				valueStr = Hex(resetValues(i))
				If valueStr.Length > 8 Then
					cmbResetValue.Items.Add("0x" & valueStr.Substring(valueStr.Length - 8, 8))
				Else
					cmbResetValue.Items.Add("0x" & valueStr)
				End If
			Else
				cmbResetValue.Items.Add("-1")
			End If
		Next

		Dim resetValue As Long
		Dim udChannel() As UdChannel = UdCounterCtrl1.Channels
		resetValue = udChannel(0).InitialValue

		If 0 = resetValue Then
			cmbResetValue.SelectedIndex = 0
		Else
			cmbResetValue.SelectedIndex = 1
		End If


		'for using edit text as reset value
		txtResetValue.Text = Str(Hex(0))

		'reset times
		txtResetTimes.Text = "0"
		txtResetTimes.Enabled = False

		'radio button for reset value.
		Dim resetTimesByIndex As Integer
		resetTimesByIndex = udChannel(0).ResetTimesByIndex
		If 0 = resetTimesByIndex Then
			radDisable.Checked = True
			raInfinite.Checked = False
			radFinite.Checked = False
		ElseIf -1 = resetTimesByIndex Then
			radDisable.Checked = False
			raInfinite.Checked = True
			radFinite.Checked = False
		Else
			radDisable.Checked = False
			raInfinite.Checked = False
			radFinite.Checked = True

			txtResetTimes.Text = resetTimesByIndex.ToString
			txtResetTimes.Enabled = True
		End If
	End Sub

	Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
		Try
			UdCounterCtrl1.Enabled = True
		Catch ex As Exception
			Timer1.Enabled = False
			HandleError(ex)
		End Try
		UdCounterCtrl1.Read(cntrValue)

		txtCounterValue.Text = "0x" + Hex(cntrValue)

	End Sub

	Private Sub btnValReset_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnValReset.Click
		UdCounterCtrl1.ValueReset()
	End Sub

	Private Sub btnStop_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnStop.Click
		'Stop the user Timer
		Timer1.Enabled = False

		btnStart.Text = "Start"
		btnStop.Enabled = False
		btnValReset.Enabled = False

		cmbResetValue.Enabled = True
		radDisable.Enabled = True
		radFinite.Enabled = True
		raInfinite.Enabled = True

		Dim err As ErrorCode
		err = ErrorCode.Success

		Try
			UdCounterCtrl1.Enabled = False
		Catch ex As Exception
			HandleError(ex)
		End Try
	End Sub

	Private Sub UpDownCounterForm_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
		'The default device of project is PCI-1784.
		If Not UdCounterCtrl1.Initialized Then
			MsgBox("Please select a device with DAQNavi wizard!", , "Warning Information")
			End
		End If

		'set title of the form
		Me.Text = "UpDown Counter(" + UdCounterCtrl1.SelectedDevice.Description + ")"

		CounterValueList.Items.Clear()

		ConfiguratePanel()

		btnStart.Enabled = True
		btnStop.Enabled = False
		btnValReset.Enabled = False
	End Sub

	Private Sub radDisable_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles radDisable.Click
		If radDisable.Checked Then
			txtResetTimes.Enabled = False
		End If
	End Sub

	Private Sub raInfinite_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles raInfinite.Click
		If raInfinite.Checked Then
			txtResetTimes.Enabled = False
		End If
	End Sub

	Private Sub radFinite_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles radFinite.Click
		Dim udChannel() As UdChannel = UdCounterCtrl1.Channels
		If radFinite.Checked Then
			txtResetTimes.Enabled = True
			txtResetTimes.Text = udChannel(0).ResetTimesByIndex.ToString
		End If
	End Sub

	Private Sub cmbResetValue_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmbResetValue.SelectedIndexChanged
		Dim resetValues() As Integer
		resetValues = UdCounterCtrl1.Features.UdInitialValues
		Dim resetValue As Long
		resetValue = resetValues(cmbResetValue.SelectedIndex)

		If resetValue = -1 Then
			txtResetValue.Enabled = True
		Else
			txtResetValue.Enabled = False
		End If
	End Sub

	Private Sub btnStart_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnStart.Click
		txtCounterValue.Text = "0"

		If btnStart.Text = "Start" Then
			CounterValueList.Items.Clear()

			'Set reset times for counter value
			Dim resetTimes As Integer
			resetTimes = 0

			If radFinite.Checked Then
				resetTimes = CInt(txtResetTimes.Text)
			ElseIf raInfinite.Checked Then
				resetTimes = -1
			ElseIf radDisable.Checked Then
				resetTimes = 0
			End If
			Dim udChannel() As UdChannel = UdCounterCtrl1.Channels
			udChannel(0).ResetTimesByIndex = resetTimes

			'set reset value
			Dim resetValues() As Integer
			resetValues = UdCounterCtrl1.Features.UdInitialValues
			Dim resetValue As Long
			resetValue = resetValues(cmbResetValue.SelectedIndex)

			If resetValue = -1 Then
				resetValue = Val(txtResetValue.Text)
			End If

			udChannel(0).InitialValue = resetValue

			'Start UpDown Counter function.
			Try
				UdCounterCtrl1.Enabled = True
			Catch ex As Exception
				HandleError(ex)
			End Try

			Timer1.Enabled = True

			btnStop.Enabled = True
			btnValReset.Enabled = True
			cmbResetValue.Enabled = False
			radDisable.Enabled = False
			radFinite.Enabled = False
			raInfinite.Enabled = False

			btnStart.Text = "Latch"
		Else
			If CounterValueList.Items.Count > 12 Then
				CounterValueList.Items.RemoveAt(0)
			End If

			CounterValueList.Items.Add("0x" + Hex(cntrValue))
		End If
	End Sub
End Class
