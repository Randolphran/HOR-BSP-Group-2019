Imports System.Math
Imports Automation.BDaq

Public Class SnapCounterForm
	Inherits Form

	Private m_isTimerUsing As Boolean
	Private snapSrcs() As EventId
	Private selectedItems As ListBox.SelectedIndexCollection

	Private snapCount As Integer

	Private TimerPulseCtrl1 As TimerPulseCtrl


	Protected Delegate Sub UdCntrEvent(ByVal snapCount As Integer, ByVal e As UdCntrEventArgs)

	Public Sub New()
		InitializeComponent()
		TimerPulseCtrl1 = New TimerPulseCtrl
	End Sub

	Public Sub New(ByVal deviceNumber As Integer)
		InitializeComponent()
		UdCounterCtrl1.SelectedDevice = New DeviceInformation(deviceNumber)
		TimerPulseCtrl1 = New TimerPulseCtrl
	End Sub

	Private Sub HandleError(ByVal err As Exception)
		MessageBox.Show("Sorry ! There're some errors happened, the error code is: " & err.ToString(), "Warning Information")
	End Sub

	Private Sub EventIDtoString(ByVal id As Long, ByRef Str As String)
		Select Case id

			Case 406	  'EvtUdIndex0
				Str = "Index0"
			Case 407	  'EvtUdIndex1
				Str = "Index1"
			Case 408	  'EvtUdIndex2
				Str = "Index2"
			Case 409	  'EvtUdIndex3
				Str = "Index3"
			Case 410	  'EvtUdIndex4
				Str = "Index4"
			Case 411	  'EvtUdIndex5
				Str = "Index5"
			Case 412	  'EvtUdIndex6
				Str = "Index6"
			Case 413	  'EvtUdIndex7
				Str = "Index7"

			Case 390	  'EvtCntTimer0
				Str = "Timer0"
			Case 391	  'EvtCntTimer1
				Str = "Timer1"
			Case 392	  'EvtCntTimer2
				Str = "Timer2"
			Case 393	  'EvtCntTimer3
				Str = "Timer3"
			Case 394	  'EvtCntTimer4
				Str = "Timer4"
			Case 395	  'EvtCntTimer5
				Str = "Timer5"
			Case 396	  'EvtCntTimer6
				Str = "Timer6"
			Case 397	  'EvtCntTimer7
				Str = "Timer7"

			Case 12	  'EvtDiintChannel000
				Str = "DiintChannel0"
			Case 13	  'EvtDiintChannel001
				Str = "DiintChannel1"
			Case 14	  'EvtDiintChannel002
				Str = "DiintChannel2"
			Case 15	  'EvtDiintChannel003
				Str = "DiintChannel3"
			Case 16	  'EvtDiintChannel004
				Str = "DiintChannel4"
			Case 17	  'EvtDiintChannel005
				Str = "DiintChannel5"
			Case 18	  'EvtDiintChannel006
				Str = "DiintChannel6"
			Case 19	  'EvtDiintChannel007
				Str = "DiintChannel7"
			Case Else
				Str = ""
		End Select
	End Sub

	Private Sub CheckTimerUsingParam(ByVal id As Long, ByRef timerChan As Integer, ByRef isTimerUsing As Boolean)
		If id >= 390 And id <= 397 Then
			timerChan = id - 390
		End If

		If timerChan <> -1 Then
			isTimerUsing = True
		End If
	End Sub

	Private Sub ConfiguratePanel()
		'for reset value
		snapSrcs = UdCounterCtrl1.Features.UdSnapEventSources
		Dim srcCount As Integer
		srcCount = UBound(snapSrcs) - LBound(snapSrcs) + 1
		Dim srcSrc As String
		srcSrc = ""

		listSnapSource.Items.Clear()

		Dim i As Integer
		For i = 0 To srcCount - 1
			EventIDtoString(snapSrcs(i), srcSrc)
			listSnapSource.Items.Add(srcSrc)
		Next
	End Sub

	Private Sub btnStart_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnStart.Click
		CounterValueList.Items.Clear()

		txtCounterValue.Text = "0"
		txtSnapCount.Text = "0"
		snapCount = 0

		m_isTimerUsing = False

		Dim timerChan As Integer
		timerChan = -1

		For Each index As Integer In selectedItems
			CheckTimerUsingParam(snapSrcs(index), timerChan, m_isTimerUsing)
			UdCounterCtrl1.SnapStart(snapSrcs(index))
		Next

		If m_isTimerUsing Then
			Dim deviceNum As Integer
			deviceNum = UdCounterCtrl1.SelectedDevice.DeviceNumber
			TimerPulseCtrl1.SelectedDevice = New DeviceInformation(deviceNum)

			Dim frequency As Double
			frequency = CDbl(txtTimeInterval.Text)

			TimerPulseCtrl1.ChannelStart = timerChan
			Dim tmrChannel() As TmrChannel = TimerPulseCtrl1.Channels
			tmrChannel(0).Frequency = frequency

			Try
				TimerPulseCtrl1.Enabled = True
			Catch ex As Exception
				HandleError(ex)
			End Try
		End If

		'Start Snap Counter function.
		Try
			UdCounterCtrl1.Enabled = True
		Catch ex As Exception
			HandleError(ex)
		End Try

		Timer1.Enabled = True

		btnStart.Enabled = False
		btnStop.Enabled = True
		listSnapSource.Enabled = False
	End Sub

	Private Sub btnStop_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnStop.Click
		Timer1.Enabled = False

		btnStart.Enabled = True
		btnStop.Enabled = False
		listSnapSource.Enabled = True

		'stop timer pulse
		If m_isTimerUsing Then
			TimerPulseCtrl1.Enabled = False
			TimerPulseCtrl1.Cleanup()
		End If

		'stop snap function
		For Each index As Integer In selectedItems
			UdCounterCtrl1.SnapStop(snapSrcs(index))
		Next

		'stop updown counter
		Try
			UdCounterCtrl1.Enabled = False
		Catch ex As Exception
			HandleError(ex)
		End Try
	End Sub

	Private Sub SnapCounterForm_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
		'The default device of project is PCI-1784.
		If Not UdCounterCtrl1.Initialized Then
			MsgBox("Please select a device with DAQNavi wizard!", , "Warning Information")
			End
		End If

		'set title of the form
		Me.Text = "Snap Counter(" + UdCounterCtrl1.SelectedDevice.Description + ")"

		selectedItems = listSnapSource.SelectedIndices

		'initial the form
		txtTimeInterval.Text = "5"
		m_isTimerUsing = False
		snapCount = 0
		CounterValueList.Items.Clear()

		ConfiguratePanel()

		btnStart.Enabled = True
		btnStop.Enabled = False
	End Sub

	Private Sub listSnapSource_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles listSnapSource.SelectedIndexChanged
		selectedItems = listSnapSource.SelectedIndices

		Dim timerChan As Integer
		timerChan = -1
		Dim isTimerUsing As Boolean
		isTimerUsing = False

		If selectedItems.Count <> 0 Then
			For Each index As Integer In selectedItems
				CheckTimerUsingParam(snapSrcs(index), timerChan, isTimerUsing)

				If isTimerUsing Then
					txtTimeInterval.Enabled = True
					Exit For
				Else
					txtTimeInterval.Enabled = False
				End If
			Next
		Else
			txtTimeInterval.Enabled = False
		End If
	End Sub

	Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
		Try
			UdCounterCtrl1.Enabled = True
		Catch ex As Exception
			Timer1.Enabled = False
			HandleError(ex)
		End Try

		Dim cntrValue As Integer
		UdCounterCtrl1.Read(cntrValue)

		txtCounterValue.Text = "0x" + Hex(cntrValue)
	End Sub

	Private Sub UdCounterCtrl1_UdCntrEvent(ByVal sender As System.Object, ByVal e As Automation.BDaq.UdCntrEventArgs) Handles UdCounterCtrl1.UdCntrEvent
		snapCount = snapCount + 1

		Try
			Me.Invoke(New UdCntrEvent(AddressOf DataHandler), New Object() {snapCount, e})
		Catch ex As System.Exception
		End Try
	End Sub

	Private Sub DataHandler(ByVal snapCount As Integer, ByVal e As UdCntrEventArgs)
		If CounterValueList.Items.Count > 40 Then
			CounterValueList.Items.RemoveAt(0)
		End If

		Dim snapValue As String
		Dim srcID As String
		srcID = ""
		Dim source As String

		txtSnapCount.Text = Str(snapCount)

		EventIDtoString(e.Id, srcID)

		snapValue = "CntrValue: "
		Dim i As Integer
		For i = 0 To e.Length
			snapValue = snapValue & Hex(e.Data(i))
		Next
		CounterValueList.Items.Add(snapValue)

		source = "SrcID: "
		source = source & srcID
		CounterValueList.Items.Add(source)
	End Sub
End Class
