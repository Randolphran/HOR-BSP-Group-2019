Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms

Imports Automation.BDaq
Imports MySimpleGraph

Public Class AsynOneBufferedAI_TDtrtpForm
    Inherits Form
#Region "fields"
    Private m_simpleGraph As MySimpleGraph.SimpleGraph
    Private m_firstItem As ListViewItem
    Private m_secondItem As ListViewItem

    Dim dataReadyCount As Integer = 0

    Private m_dataScaled As Double()

    Private m_timeUnit As MySimpleGraph.TimeUnit
    Private m_rangeX As MathInterval
    Private m_rangeY As MathInterval
    Private sampleCountPerChan As Integer
    Private Delegate Sub UpdateUI()
#End Region

	Public Sub New()
		InitializeComponent()
	End Sub

	Public Sub New(ByVal deviceNumber As Integer)
		InitializeComponent()
		WaveformAiCtrl1.SelectedDevice = New DeviceInformation(deviceNumber)
	End Sub

	Private Sub AsynchronousOneBufferedAIForm_Load(ByVal sender As Object, ByVal e As EventArgs) Handles MyBase.Load
		'The default device of project is demo device, users can choose other devices according to their needs.
		If Not WaveformAiCtrl1.Initialized Then
			MessageBox.Show("Please select a device in control property!", "AsynOneBufferedAI_TDtrtp")
			Me.Close()
			Return
		End If

		'initialize a graph with a picture box control to draw Ai data. 
		m_simpleGraph = New MySimpleGraph.SimpleGraph(pictureBox.Size, pictureBox)

		Dim chanCount As Integer = WaveformAiCtrl1.Conversion.ChannelCount
		Dim sectionLength As Integer = WaveformAiCtrl1.Record.SectionLength
		m_dataScaled = New Double(chanCount * sectionLength - 1) {}

		Me.Text = "Asynchronous One Buffered AI with Trigger Delay to Start and Delay to Stop - Run(" + WaveformAiCtrl1.SelectedDevice.Description + ")"
		trackBar_div.Enabled = False
		trackBar_shift.Enabled = False
		textBox_div.[ReadOnly] = True
		textBox_shift.[ReadOnly] = True

		If Not (WaveformAiCtrl1.Features.TriggerSupported AndAlso WaveformAiCtrl1.Features.Trigger1Supported) Then
			MessageBox.Show("the selected device does not support double trigger for delay to start and delay to stop!", "AsynOneBufferedAI_TDtrtp")
			Me.Close()
			Return
		End If

		If WaveformAiCtrl1.Features.TriggerSupported Then
			WaveformAiCtrl1.Trigger.Action = TriggerAction.DelayToStart
		End If
		triggerPointFlag.Hide()
		label_triggerPoint.Hide()

		If WaveformAiCtrl1.Features.Trigger1Supported Then
			If Not WaveformAiCtrl1.Trigger1.Source = SignalDrop.SignalNone Then
				triggerPointFlag.Show()
				label_triggerPoint.Show()
			End If
			WaveformAiCtrl1.Trigger1.Action = TriggerAction.DelayToStop
		Else
			triggerPointFlag.Hide()
			label_triggerPoint.Hide()
		End If

		ConfigureGraph()
		InitListView()
	End Sub

	Private Sub ConfigureGraph()
		WaveformAiCtrl1.Prepare()
		m_timeUnit = TimeUnit.Millisecond
		Dim conversionRate As Double
		Dim timeInterval As Double
		Dim shiftMax As Double

		conversionRate = WaveformAiCtrl1.Conversion.ClockRate
		'1 pixel to 1 data point. How much time plotting pictureBox.Size.Width / 10(panelLineCount) data points requires in ms. 
		timeInterval = 100.0 * pictureBox.Size.Width / conversionRate
		shiftMax = 1000.0 * WaveformAiCtrl1.Record.SectionLength / conversionRate
		While conversionRate >= 10 * 1000
			timeInterval *= 1000
			conversionRate /= 1000
			shiftMax *= 1000
			m_timeUnit = m_timeUnit - 1
		End While

		trackBar_shift.Maximum = CInt(Math.Floor(shiftMax))
		trackBar_shift.Value = 0
		textBox_shift.Text = trackBar_shift.Value.ToString()
		trackBar_div.Maximum = 4 * timeInterval
		trackBar_div.Minimum = CInt(Math.Ceiling(timeInterval / 10))
		trackBar_div.Value = CInt(Math.Floor(timeInterval))
		textBox_div.Text = trackBar_div.Value.ToString()

		Dim tUnit As String() = {"ns", "us", "ms", "Sec"}
		label_divide.Text = tUnit(CInt(m_timeUnit))
		label_shift.Text = tUnit(CInt(m_timeUnit))
		SetXCord() 'm_rangeX.Max is decided by X-coordinate div and shift time

		Dim rangeY As New MathInterval()
		Dim unit As ValueUnit = CType(-1, ValueUnit)	' Don't show unit in the label.
		rangeY.Max = 10
		rangeY.Min = -10
		Dim Y_CordLables(3) As String
		Helpers.GetYCordRangeLabels(Y_CordLables, rangeY.Max, rangeY.Min, unit)
		label_YCoordinateMax.Text = Y_CordLables(0)
		label_YCoordinateMin.Text = Y_CordLables(1)
		label_YCoordinateMiddle.Text = Y_CordLables(2)

		m_simpleGraph.YCordRangeMax = rangeY.Max
		m_simpleGraph.YCordRangeMin = rangeY.Min
		m_simpleGraph.Clear()
	End Sub

    Private Sub SetXCord()
        m_simpleGraph.XCordTimeDiv = CType(trackBar_div.Value, [Double])
        m_simpleGraph.XCordTimeOffset = CType(trackBar_shift.Value, [Double])
        Dim rangeMax As Double = m_simpleGraph.XCordTimeDiv * 10 + trackBar_shift.Value
        Dim X_rangeLabels(2) As String
        Helpers.GetXCordRangeLabels(X_rangeLabels, rangeMax, trackBar_shift.Value, m_timeUnit)
        label_XCoordinateMax.Text = X_rangeLabels(0)
        label_XCoordinateMin.Text = X_rangeLabels(1)
    End Sub 'SetXCord

    Private Sub ConfigureGraph2(ByVal sampleCountPerChan As Integer)
		m_timeUnit = TimeUnit.Millisecond
		Dim conversionRate As Double
		Dim timeInterval As Double
		Dim shiftMax As Double

		conversionRate = WaveformAiCtrl1.Conversion.ClockRate
		'1 pixel to 1 data point. How much time plotting pictureBox.Size.Width / 10(panelLineCount) data points requires in ms. 
		timeInterval = 100.0 * pictureBox.Size.Width / conversionRate
		shiftMax = 1000.0 * sampleCountPerChan / conversionRate
		While conversionRate >= 10 * 1000
			timeInterval *= 1000
			conversionRate /= 1000
			shiftMax *= 1000
			m_timeUnit = m_timeUnit - 1
		End While

		trackBar_shift.Maximum = CInt(Math.Floor(shiftMax))
		trackBar_shift.Value = 0
		textBox_shift.Text = trackBar_shift.Value.ToString()
		trackBar_div.Maximum = 4 * timeInterval
		trackBar_div.Minimum = CInt(Math.Ceiling(timeInterval / 10))
		trackBar_div.Value = CInt(Math.Floor(timeInterval))
		textBox_div.Text = trackBar_div.Value.ToString()

		Dim tUnit As String() = {"ns", "us", "ms", "Sec"}
		label_divide.Text = tUnit(CInt(m_timeUnit))
		label_shift.Text = tUnit(CInt(m_timeUnit))

		SetXCord() 'm_rangeX.Max is decided by X-coordinate div and shift time

		Dim rangeY As New MathInterval()
		Dim unit As ValueUnit = CType(-1, ValueUnit) ' Don't show unit in the label.
		rangeY.Max = 10
		rangeY.Min = -10
		Dim Y_CordLables(3) As String
		Helpers.GetYCordRangeLabels(Y_CordLables, rangeY.Max, rangeY.Min, unit)
		label_YCoordinateMax.Text = Y_CordLables(0)
		label_YCoordinateMin.Text = Y_CordLables(1)
		label_YCoordinateMiddle.Text = Y_CordLables(2)

		m_simpleGraph.YCordRangeMax = rangeY.Max
		m_simpleGraph.YCordRangeMin = rangeY.Min
		m_simpleGraph.Clear()
	End Sub

	Private Function GetArrowXCordLocation(ByVal dataCount As Integer, ByVal delayCount As Integer, ByVal pixelCount As Integer) As Integer
		WaveformAiCtrl1.Prepare()
		Dim relativePixelWidth As Integer = 0
		Dim rate As Double = WaveformAiCtrl1.Conversion.ClockRate
		Dim shift As Double = trackBar_shift.Value
		trackBar_shift.Tag = dataCount
		Dim divide As Double = trackBar_div.Value
		trackBar_div.Tag = dataCount
		Dim samples As Integer = (WaveformAiCtrl1.BufferCapacity / WaveformAiCtrl1.Conversion.ChannelCount)
		If rate > 1000 Then
			rate /= 1000
		End If
		Dim screenCount As Integer = CInt(Math.Truncate(divide * 10 * rate / 1000))
		Dim shiftCount As Integer = CInt(Math.Truncate(shift * rate / 1000))

		If samples - delayCount - shiftCount > 0 AndAlso samples - delayCount - shiftCount < screenCount Then
			' 
			relativePixelWidth = pixelCount * (samples - delayCount - shiftCount) \ screenCount
		Else
			relativePixelWidth = 0
		End If
		Return relativePixelWidth
	End Function

	Private Sub SetTriggerPointFlagLoacation(ByVal delayCount As Integer)
		Dim dataCount As Integer = CInt(trackBar_shift.Tag)
		Dim flagInitialLocation As New Point(pictureBox.Location.X, pictureBox.Location.Y + pictureBox.Height)

		Dim relativeWidth As Integer = GetArrowXCordLocation(dataCount, delayCount, pictureBox.Size.Width)
		If relativeWidth = 0 Then
			triggerPointFlag.Hide()
			label_triggerPoint.Hide()
		Else
			triggerPointFlag.Show()
			label_triggerPoint.Show()
			triggerPointFlag.Location = New Point(flagInitialLocation.X + relativeWidth - triggerPointFlag.Width / 2, flagInitialLocation.Y)
			label_triggerPoint.Location = New Point(pictureBox.Location.X + relativeWidth + triggerPointFlag.Width, flagInitialLocation.Y)
		End If
	End Sub


	Private Sub trackBar_shift_Scroll(ByVal sender As Object, ByVal e As EventArgs) Handles trackBar_shift.Scroll
		SetXCord()
		textBox_shift.Text = trackBar_shift.Value.ToString()
		m_simpleGraph.Shift(trackBar_shift.Value)
		If WaveformAiCtrl1.Features.Trigger1Supported And Not (WaveformAiCtrl1.Trigger1.Source = SignalDrop.SignalNone) Then
			SetTriggerPointFlagLoacation(WaveformAiCtrl1.Trigger1.DelayCount)
		End If
	End Sub

	Private Sub trackBar_div_Scroll(ByVal sender As Object, ByVal e As EventArgs) Handles trackBar_div.Scroll
		m_simpleGraph.Div(trackBar_div.Value)
		SetXCord()
		textBox_div.Text = trackBar_div.Value.ToString()
		If WaveformAiCtrl1.Features.Trigger1Supported And Not (WaveformAiCtrl1.Trigger1.Source = SignalDrop.SignalNone) Then
			SetTriggerPointFlagLoacation(WaveformAiCtrl1.Trigger1.DelayCount)
		End If

	End Sub

	Private Sub button_getData_Click(ByVal sender As Object, ByVal e As EventArgs) Handles button_getData.Click
		Dim err As ErrorCode = ErrorCode.Success
		WaveformAiCtrl1.Prepare()
		sampleCountPerChan = WaveformAiCtrl1.Record.SectionLength
		If WaveformAiCtrl1.Features.TriggerSupported Then
			Dim trigger As Trigger = WaveformAiCtrl1.Trigger
			Dim delayCountPerChanMax As Double = 0
			Dim range As MathInterval = WaveformAiCtrl1.Features.TriggerDelayRange
			If trigger.Source <> SignalDrop.SignalNone Then

				If WaveformAiCtrl1.Features.SamplingMethod = SamplingMethod.EqualTimeSwitch Then
					delayCountPerChanMax = range.Max / WaveformAiCtrl1.Conversion.ChannelCount
				Else
					delayCountPerChanMax = range.Max
				End If

				If trigger.DelayCount > delayCountPerChanMax OrElse trigger.DelayCount < range.Min Then
					Dim errMessage As String = "      parameter error: " & vbCr & vbLf & "               DelayCount is within " & range.Min.ToString() & "-" & delayCountPerChanMax.ToString() & "."
					MessageBox.Show(errMessage)
					Return
				ElseIf trigger.DelayCount > (WaveformAiCtrl1.BufferCapacity / WaveformAiCtrl1.Conversion.ChannelCount) Then
					MessageBox.Show("trigger DelayCount should be smaller than scanChannel Samples")
				End If
			Else
				trigger.Source = SignalDrop.SignalNone
			End If
		End If

		ConfigureGraph()
		If err = ErrorCode.Success Then
			err = WaveformAiCtrl1.Start()
		End If

		If err <> ErrorCode.Success Then
			HandleError(err)
			Return
		End If

		trackBar_div.Enabled = True
		trackBar_shift.Enabled = True
		button_getData.Enabled = False
	End Sub

	Private Sub waveformAiCtrl1_Stopped(ByVal sender As Object, ByVal args As BfdAiEventArgs) Handles WaveformAiCtrl1.Stopped
		Dim err As ErrorCode

		Try
			'The BufferedAiCtrl has been disposed.
			If WaveformAiCtrl1.State = ControlState.Idle Then
				Return
			End If

			Dim chanCount As Integer = WaveformAiCtrl1.Conversion.ChannelCount
			Dim sectionLength As Integer = WaveformAiCtrl1.Record.SectionLength
			Dim realCount As Integer

			If args.Count < (chanCount * sectionLength) Then
				realCount = args.Count
			Else
				realCount = (chanCount * sectionLength)
			End If

			err = WaveformAiCtrl1.GetData(realCount, m_dataScaled)
			If err <> ErrorCode.Success And err <> ErrorCode.WarningRecordEnd Then
				HandleError(err)
				Return
			End If

			Me.Invoke(New UpdateUI(AddressOf UpdateUIConfigGraph2))

			m_simpleGraph.Chart(m_dataScaled, chanCount, realCount / chanCount, 1.0 / WaveformAiCtrl1.Conversion.ClockRate)
			Me.Invoke(New UpdateUI(AddressOf UpdateUIMethod))
		Catch ex As System.Exception
		End Try
	End Sub

	Private Sub InitListView()
		'control list view ,one grid indicates a channel which specials with color.
		listView.Clear()
		listView.FullRowSelect = False
		listView.Width = 512
		listView.Height = 43
		listView.View = View.Details
		' Set the view to show details.
		listView.HeaderStyle = ColumnHeaderStyle.None
		listView.GridLines = True
		'listView.Activation = ItemActivation.OneClick;
		listView.AllowDrop = False
		'listView.CanSelect = false;
		listView.Capture = False
		'listView.ContainsFocus = false;
		'listView.HideSelection = false;
		'listView.MultiSelect = true;
		' there are 8 columns for every item.
		For i As Integer = 0 To 7
			listView.Columns.Add("", 63)
		Next

		' modify the grid's height with image Indirectly.
		Dim imgList As New ImageList()
		imgList.ImageSize = New Size(1, 16)
		'width and height.
		listView.SmallImageList = imgList
		'use imgList to modify the height of listView grids.
		' create two ListViewItem objects,so there are 16 grids for listView.
		m_firstItem = New ListViewItem()
		m_firstItem.SubItems.Clear()
		m_firstItem.UseItemStyleForSubItems = False
		m_firstItem.Font = New Font("SimSun", 10)

		m_secondItem = New ListViewItem()
		m_secondItem.SubItems.Clear()
		m_secondItem.UseItemStyleForSubItems = False
		m_secondItem.Font = New Font("SimSun", 10)

		' format every grid for output.
		m_firstItem.SubItems(0).Text = ""
		m_firstItem.SubItems(0).BackColor = m_simpleGraph.Pens(0).Color
		For i As Integer = 1 To 7
			If i < WaveformAiCtrl1.Conversion.ChannelCount Then
				m_firstItem.SubItems.Add((""), Color.Black, Color.Honeydew, New Font("SimSun", 10))
				m_firstItem.SubItems(i).BackColor = m_simpleGraph.Pens(i).Color
			Else
				m_firstItem.SubItems.Add("")
				m_firstItem.SubItems(i).BackColor = Color.White
			End If
		Next

		If 8 < WaveformAiCtrl1.Conversion.ChannelCount Then
			m_secondItem.SubItems(0).Text = ""
			m_secondItem.SubItems(0).BackColor = m_simpleGraph.Pens(8).Color
		Else
			m_secondItem.SubItems(0).Text = ""
			m_secondItem.SubItems(0).BackColor = Color.White
		End If
		For i As Integer = 9 To 15
			If i < WaveformAiCtrl1.Conversion.ChannelCount Then
				m_secondItem.SubItems.Add((""), Color.Black, Color.Honeydew, New Font("SimSun", 10))
				m_secondItem.SubItems(i - 8).BackColor = m_simpleGraph.Pens(i).Color
			Else
				m_secondItem.SubItems.Add("")
				m_secondItem.SubItems(i - 8).BackColor = Color.White
			End If
		Next

		Dim list As ListViewItem() = New ListViewItem() {m_firstItem, m_secondItem}
		listView.Items.AddRange(list)
		listView.SendToBack()
	End Sub

	Private Sub HandleError(ByVal err As ErrorCode)
		If err <> ErrorCode.Success Then
			MessageBox.Show("Sorry ! Some errors happened, the error code is: " & err.ToString(), "AsynOneBufferedAI_TDtp")
		End If
	End Sub

	Private Sub UpdateUIMethod()
		button_getData.Enabled = True
		If WaveformAiCtrl1.Features.TriggerSupported Then
			triggerPointFlag.Location = New Point(pictureBox.Location.X, pictureBox.Location.Y + pictureBox.Height)
			label_triggerPoint.Location = New Point(pictureBox.Location.X, pictureBox.Location.Y + pictureBox.Height)
			Dim totalDataCountPerChan As Integer = dataReadyCount / WaveformAiCtrl1.Conversion.ChannelCount
			Dim delayCount As Integer = WaveformAiCtrl1.Trigger1.DelayCount
			Dim rate As [Double] = WaveformAiCtrl1.Conversion.ClockRate
			If rate > 1000 Then
				rate /= 100
			End If
			Dim triggerTime As Double = rate * (totalDataCountPerChan - delayCount) / 1000.0
			label_triggerPoint.Text = triggerTime.ToString("F3") & "ms Triggered."
			Dim relativeWidth As Integer = GetArrowXCordLocation(dataReadyCount, WaveformAiCtrl1.Trigger1.DelayCount, pictureBox.Size.Width)
			If relativeWidth = 0 Then
				triggerPointFlag.Hide()
				label_triggerPoint.Hide()
			Else
				triggerPointFlag.Show()
				triggerPointFlag.Location = New Point(triggerPointFlag.Location.X + relativeWidth - triggerPointFlag.Width / 2, triggerPointFlag.Location.Y)
				label_triggerPoint.Location = New Point(label_triggerPoint.Location.X + relativeWidth + triggerPointFlag.Width, triggerPointFlag.Location.Y)
				label_triggerPoint.Show()
			End If
		End If

	End Sub

	Private Sub UpdateUIConfigGraph2()
		ConfigureGraph2(sampleCountPerChan)
	End Sub
End Class
