Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms
Imports System.Collections
Imports Automation.BDaq
Imports MySimpleGraph


Public Class FrequencyMeasurementForm
    Inherits Form
    Private m_frequecy As Double()
    ' selected counter channel' frequency.
    Private m_index As Integer = 1
    Private m_isCounterReseted As Boolean = True
    Private m_channelCount As Integer = 2
    Private m_simpleGraph As MySimpleGraph.SimpleGraph
    Private m_rangeX As MathInterval
    Private m_rangeYTypeList As New ArrayList()

	Public Sub New()
		InitializeComponent()
		'initialize the range of Y coordinate
		InitRangeYTypeList()
	End Sub

	''' <summary>
	'''  Init rangeYType list to larger and smaller the rangeY type
	''' </summary>
	Private Sub InitRangeYTypeList()
		Dim rangeYType As New RangeYType()
		rangeYType.rangeY = New MathInterval()
		Dim i As Integer = 10000000
		While i >= 1
			'10 MHz
			If i >= 1000000 Then
				rangeYType.rangeY.Max = i \ 1000000
				'MHz
				rangeYType.rangeY.Min = 0
				rangeYType.unit = MySimpleGraph.FrequencyUnit.MHz
				m_rangeYTypeList.Add(rangeYType)
				i /= 10
				Continue While
			End If
			If i >= 1000 Then
				rangeYType.rangeY.Max = i \ 1000
				'KHz
				rangeYType.rangeY.Min = 0
				rangeYType.unit = MySimpleGraph.FrequencyUnit.KHz
				m_rangeYTypeList.Add(rangeYType)
				i /= 10
				Continue While
			End If
			' Hz
			rangeYType.rangeY.Max = i
			rangeYType.rangeY.Min = 0
			rangeYType.unit = MySimpleGraph.FrequencyUnit.Hz
			m_rangeYTypeList.Add(rangeYType)
			i /= 10
		End While
	End Sub

    Private Sub FrequencyMeasurementForm_Load(ByVal sender As Object, ByVal e As EventArgs) Handles MyBase.Load
		'The default device of project is demo device, users can choose other devices according to their needs.
		If Not FreqMeterCtrl1.Initialized AndAlso Not FreqMeterCtrl2.Initialized Then
			MessageBox.Show("Please select the devices correctly!!")
			Me.Close()
			Return
		End If
		'set the title of form
		SetFormTitle()
		'initialize the value of label
		fm1_Label.Text = "0.0"
		fm2_Label.Text = "0.0"

		' initialize a graph with a picture box control to draw frequency data. 
		m_simpleGraph = New MySimpleGraph.SimpleGraph(GraphPicture.Size, GraphPicture)

		Timer1.Interval = 50
		TimeInterval.Text = trackBar.Value.ToString() & "ms"
		'set coordinate value.
		m_simpleGraph.XCordTimeDiv = 1000

		Dim X_rangeLabels(2) As String
		Helpers.GetXCordRangeLabels(X_rangeLabels, 10, 0, TimeUnit.Second)
		label_XCoordinateMax.Text = X_rangeLabels(0)
		label_XCoordinateMin.Text = X_rangeLabels(1)

		SetYCord(m_index)
		m_simpleGraph.Clear()
		Start.Enabled = True
		Pause.Enabled = False
		Stop_button.Enabled = False
    End Sub

	Private Sub SetYCord(ByVal index As Integer)
		Dim rangeYType As RangeYType = CType(m_rangeYTypeList(index), RangeYType)

		Dim Y_CordLables(3) As String
		Helpers.GetYCordRangeLabels(Y_CordLables, rangeYType.rangeY.Max, rangeYType.rangeY.Min, rangeYType.unit)
		label_YCoordinateMax.Text = Y_CordLables(0)
		label_YCoordinateMin.Text = Y_CordLables(1)
		label_YCoordinateMiddle.Text = Y_CordLables(2)

		Dim rate As Integer = 1
		If rangeYType.unit = FrequencyUnit.KHz Then
			rate = 1000
		Else
			If rangeYType.unit = FrequencyUnit.MHz Then
				rate = 1000 * 1000
			End If
		End If
		m_simpleGraph.YCordRangeMax = rangeYType.rangeY.Max * rate
		m_simpleGraph.YCordRangeMin = rangeYType.rangeY.Min * rate
	End Sub 'SetYCord

	Private Sub SetFormTitle()
		Dim description1 As String = FreqMeterCtrl1.SelectedDevice.Description
		Dim description2 As String = FreqMeterCtrl2.SelectedDevice.Description
		If description1 IsNot Nothing AndAlso description2 Is Nothing Then
			Me.Text = "Frequency Measurement(" & description1 & ")"
		Else
			If description1 Is Nothing AndAlso description2 IsNot Nothing Then
				Me.Text = "Frequency Measurement(" & description2 & ")"
			Else
				If FreqMeterCtrl1.SelectedDevice.DeviceNumber = FreqMeterCtrl2.SelectedDevice.DeviceNumber Then
					Me.Text = "Frequency Measurement - Run(" & description1 & ")"
				Else
					Me.Text = "Frequency Measurement - Run(" & description1 & "," & description2 & ")"
				End If
			End If
		End If
	End Sub

	Private Sub Stop_Click(ByVal sender As Object, ByVal e As EventArgs) Handles Stop_button.Click
		If FreqMeterCtrl1.Enabled Then
			Try
				FreqMeterCtrl1.Enabled = False
			Catch ex As Exception
				ShowErrorMessage(ex)
			End Try
		End If
		If FreqMeterCtrl2.Enabled Then
			Try
				FreqMeterCtrl2.Enabled = False
			Catch ex As Exception
				ShowErrorMessage(ex)
			End Try
		End If
		Timer1.[Stop]()
		Stop_button.Enabled = False
		Pause.Enabled = False
		Start.Enabled = True
		m_isCounterReseted = True
		m_simpleGraph.Clear()
	End Sub

	Private Shared Sub ShowErrorMessage(ByVal e As Exception)
		Dim errorInfo As String
		errorInfo = "There's some error happened, the error information: "
		MessageBox.Show(errorInfo & e.Message)
	End Sub

    Private Sub Pause_Click(ByVal sender As Object, ByVal e As EventArgs) Handles Pause.Click
        Timer1.[Stop]()
        Pause.Enabled = False
        Start.Enabled = True
        Stop_button.Enabled = True
        m_isCounterReseted = False
    End Sub

	Private Sub Start_Click(ByVal sender As Object, ByVal e As EventArgs) Handles Start.Click
		If m_isCounterReseted = True Then
			Try
				If FreqMeterCtrl1.Initialized AndAlso FreqMeterCtrl1.ChannelStart <> -1 Then
					FreqMeterCtrl1.Enabled = True
				End If
				If FreqMeterCtrl2.Initialized AndAlso FreqMeterCtrl2.ChannelStart <> -1 Then
					FreqMeterCtrl2.Enabled = True
				End If
			Catch ex As Exception
				ShowErrorMessage(ex)
			End Try
			m_frequecy = New Double(m_channelCount - 1) {}
			Stop_button.Enabled = True
		End If
		Timer1.Start()
		Start.Enabled = False
		Pause.Enabled = True
	End Sub

	Private Sub timer1_Tick(ByVal sender As Object, ByVal e As EventArgs) Handles Timer1.Tick
		If FreqMeterCtrl1.Initialized AndAlso FreqMeterCtrl1.ChannelStart <> -1 Then
			FreqMeterCtrl1.Read(m_frequecy(0))
		Else
			m_frequecy(0) = 0.0
		End If

		If FreqMeterCtrl2.Initialized AndAlso FreqMeterCtrl2.ChannelStart <> -1 Then
			FreqMeterCtrl2.Read(m_frequecy(1))
		Else
			m_frequecy(1) = 0.0
		End If
		RefreshListView()
		m_simpleGraph.Chart(m_frequecy, m_channelCount, 1, 1.0 * Timer1.Interval / 1000)
	End Sub

	Private Sub trackBar_Scroll(ByVal sender As Object, ByVal e As EventArgs) Handles trackBar.Scroll
		Timer1.Interval = trackBar.Value
		TimeInterval.Text = trackBar.Value.ToString() & "ms"
		m_simpleGraph.Clear()
	End Sub

	Private Sub larger_Click(ByVal sender As Object, ByVal e As EventArgs) Handles larger.Click
		If m_index <= 0 Then
			Return
		End If
		m_index -= 1
		SetYCord(m_index)
		m_simpleGraph.Clear()
	End Sub

	Private Sub smaller_Click(ByVal sender As Object, ByVal e As EventArgs) Handles smaller.Click
		If m_index >= 7 Then
			Return
		End If
		m_index += 1
		SetYCord(m_index)
		m_simpleGraph.Clear()
	End Sub

	' refresh the text of listViewItem with frequency value. 
	Private Sub RefreshListView()
		'control label ,one item indicates a channel which specials with color and value.
		fm1_Label.Text = [String].Format("{0:0.0}", m_frequecy(0))
		fm2_Label.Text = [String].Format("{0:0.0}", m_frequecy(1))
	End Sub
End Class

Structure RangeYType
	Public rangeY As MathInterval
	Public unit As MySimpleGraph.FrequencyUnit
End Structure



