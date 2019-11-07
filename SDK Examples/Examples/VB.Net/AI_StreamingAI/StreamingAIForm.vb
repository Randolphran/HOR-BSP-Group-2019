Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms
Imports Automation.BDaq
Imports MySimpleGraph


Public Class StreamingAIForm
    Inherits Form
#Region "fields"
    Private m_simpleGraph As MySimpleGraph.SimpleGraph
    Private m_firstItem As ListViewItem
    Private m_secondItem As ListViewItem

    Private m_rangeX As New MathInterval()
    Private m_rangeY As New MathInterval()
    Private m_timeUnit As MySimpleGraph.TimeUnit
    Private m_dataScaled As Double()
    Private m_divideValue As Double
	Private m_isFirstOverRun As Boolean = True
	Private m_xInc As Double
#End Region

    Public Sub New()
		InitializeComponent()
    End Sub

    Public Sub New(ByVal deviceNumber As Integer)
		InitializeComponent()
		WaveformAiCtrl1.SelectedDevice = New DeviceInformation(deviceNumber)
    End Sub

    Private Sub StreamingAIForm_Load(ByVal sender As Object, ByVal e As EventArgs) Handles MyBase.Load
        'The default device of project is demo device, users can choose other devices according to their needs.
		If Not WaveformAiCtrl1.Initialized Then
			MessageBox.Show("Please select a device in control property!", "StreamingAI")
			Me.Close()
			Return
		End If

		'initialize a graph with a picture box control to draw Ai data. 
		m_simpleGraph = New MySimpleGraph.SimpleGraph(pictureBox.Size, pictureBox)

		Dim chanCount As Integer
		Dim sectionLength As Integer
		chanCount = WaveformAiCtrl1.Conversion.ChannelCount
		sectionLength = WaveformAiCtrl1.Record.SectionLength
		m_dataScaled = New Double(chanCount * sectionLength - 1) {}
		Me.Text = "Streaming AI - Run(" + WaveformAiCtrl1.SelectedDevice.Description + ")"

		button_start.Enabled = True
		button_stop.Enabled = False
		button_pause.Enabled = False

		ConfigureGraph()
		InitListView()
	End Sub
	Private Sub bufferedAiCtrl1_CacheOverflow(ByVal sender As Object, ByVal args As BfdAiEventArgs) Handles WaveformAiCtrl1.CacheOverflow
		MessageBox.Show("BufferedAiCacheOverflow")
	End Sub

	Private Sub bufferedAiCtrl1_Overrun(ByVal sender As Object, ByVal args As BfdAiEventArgs) Handles WaveformAiCtrl1.MarkOverrun
		If m_isFirstOverRun Then
			MessageBox.Show("BufferedAiOverrun")
			m_isFirstOverRun = False
		End If
	End Sub

	Private Sub ConfigureGraph()

		m_timeUnit = MySimpleGraph.TimeUnit.Millisecond
		Dim conversionRate As Double
		Dim timeInterval As Double

		conversionRate = WaveformAiCtrl1.Conversion.ClockRate
		timeInterval = 100.0 * pictureBox.Size.Width / conversionRate

		While conversionRate >= 10 * 1000
			timeInterval *= 1000
			conversionRate /= 1000
			m_timeUnit = m_timeUnit - 1
		End While

		m_divideValue = timeInterval
		trackBar_div.Maximum = 4 * m_divideValue
		trackBar_div.Minimum = CInt(Math.Ceiling(timeInterval / 10))
		trackBar_div.Value = CInt(Math.Floor(m_divideValue))

		m_simpleGraph.XCordTimeDiv = m_divideValue
		m_simpleGraph.XCordTimeOffset = 0
		SetXCordRangeLabels()

		Dim unit As ValueUnit = CType(-1, ValueUnit)	' Don't show unit in the label.
		Dim Y_CordLables(3) As String
		Helpers.GetYCordRangeLabels(Y_CordLables, 10, -10, unit)
		label_YCoordinateMax.Text = Y_CordLables(0)
		label_YCoordinateMin.Text = Y_CordLables(1)
		label_YCoordinateMiddle.Text = Y_CordLables(2)

		m_simpleGraph.YCordRangeMax = 10
		m_simpleGraph.YCordRangeMin = -10
		m_simpleGraph.Clear()
	End Sub


    Private Sub SetXCordRangeLabels()
        Dim X_rangeLabels(2) As String
        Helpers.GetXCordRangeLabels(X_rangeLabels, CInt(m_simpleGraph.XCordTimeDiv) * 10, 0, m_timeUnit)
        label_XCoordinateMax.Text = X_rangeLabels(0)
        label_XCoordinateMin.Text = X_rangeLabels(1)
    End Sub 'SetXCordRangeLabels

    Private Sub InitListView()
        ' listview control ,one grid indicates a channel which specials with color.
        listView.Clear()
        listView.FullRowSelect = False
        listView.Width = 352
        listView.Height = 43
        listView.View = View.Details
        ' Set the view to show details.
        listView.HeaderStyle = ColumnHeaderStyle.None
        listView.GridLines = True
        ' there are 8 columns for every item.
        For i As Integer = 0 To 7
            listView.Columns.Add("", 43)
        Next

        ' modify the grid's height with image Indirectly.
        Dim imgList As New ImageList()
        imgList.ImageSize = New Size(1, 13)
        'width and height.
        listView.SmallImageList = imgList
        'use imgList to modify the height of listView grids.
        ' create two ListViewItem objects,so there are 16 grids for listView.
        m_firstItem = New ListViewItem()
        m_firstItem.UseItemStyleForSubItems = False
        m_firstItem.SubItems.Clear()

        m_secondItem = New ListViewItem()
        m_secondItem.UseItemStyleForSubItems = False
        m_secondItem.SubItems.Clear()

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
	End Sub

    Private Sub HandleError(ByVal err As ErrorCode)
        If err <> ErrorCode.Success Then
            MessageBox.Show("Sorry ! There are some errors happened, the error code is: " & err.ToString(), "StreamingAI")
        End If
    End Sub

	Private Sub button_start_Click(ByVal sender As Object, ByVal e As EventArgs) Handles button_start.Click
		Dim err As ErrorCode = ErrorCode.Success
		err = WaveformAiCtrl1.Prepare()
		m_xInc = 1.0 / WaveformAiCtrl1.Conversion.ClockRate
		ConfigureGraph()
		If err = ErrorCode.Success Then
			err = WaveformAiCtrl1.Start()
		End If

		If err <> ErrorCode.Success Then
			HandleError(err)
			Return
		End If

		button_start.Enabled = False
		button_pause.Enabled = True
		button_stop.Enabled = True
	End Sub

	Private Sub bufferedAiCtrl1_DataReady(ByVal sender As Object, ByVal args As BfdAiEventArgs) Handles WaveformAiCtrl1.DataReady
		Dim err As ErrorCode = ErrorCode.Success

		Try
			'The WaveformAiCtrl has been disposed.
			If WaveformAiCtrl1.State = ControlState.Idle Then
				Return
			End If

			If m_dataScaled.Length < args.Count Then
				m_dataScaled = New Double(args.Count) {}
			End If

			Dim chanCount As Integer = WaveformAiCtrl1.Conversion.ChannelCount
			Dim sectionLength As Integer = WaveformAiCtrl1.Record.SectionLength

			err = WaveformAiCtrl1.GetData(args.Count, m_dataScaled)
			If err <> ErrorCode.Success Then
				HandleError(err)
				Return
			End If
			m_simpleGraph.Chart(m_dataScaled, chanCount, args.Count / chanCount, m_xInc)
		Catch ex As System.Exception
		End Try
	End Sub

    Private Sub button_pause_Click(ByVal sender As Object, ByVal e As EventArgs) Handles button_pause.Click
        Dim err As ErrorCode = ErrorCode.Success
		err = WaveformAiCtrl1.[Stop]()
        If err <> ErrorCode.Success Then
            HandleError(err)
            Return
        End If

        button_start.Enabled = True
        button_pause.Enabled = False
    End Sub

    Private Sub button_stop_Click(ByVal sender As Object, ByVal e As EventArgs) Handles button_stop.Click
        Dim err As ErrorCode = ErrorCode.Success
		err = WaveformAiCtrl1.[Stop]()
        If err <> ErrorCode.Success Then
            HandleError(err)
            Return
        End If

        button_start.Enabled = True
        button_pause.Enabled = False
        button_stop.Enabled = False
        Array.Clear(m_dataScaled, 0, m_dataScaled.Length)
        m_simpleGraph.clear()
    End Sub

    Private Sub trackBar_div_Scroll(ByVal sender As Object, ByVal e As EventArgs) Handles trackBar_div.Scroll
        m_simpleGraph.Div(trackBar_div.Value)
        SetXCordRangeLabels()
    End Sub
End Class

