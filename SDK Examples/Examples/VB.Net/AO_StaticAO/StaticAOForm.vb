Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms
Imports Automation.BDaq


Partial Public Class StaticAOForm
    Inherits Form
#Region "fileds"

    Private m_channelStart As Integer = 0
    Private m_channelCount As Integer = 0
    Private m_PointCountPerWave As UInteger = 32
    Private m_dataScaled As Double() = New Double(1) {}
    Private m_wavePointsIndexA As Integer = 0
    Private m_wavePointsIndexB As Integer = 0
    Private m_highLevelA As Double
    Private m_lowLevelA As Double
    Private m_highLevelB As Double
    Private m_lowLevelB As Double
    Private m_isCheckedA As Boolean
    Private m_isCheckedB As Boolean
    Private m_waveformGenerator As WaveformGenerator
    Private m_formStyleA As WaveformStyle
    Private m_formStyleB As WaveformStyle
    Private m_err As ErrorCode = ErrorCode.Success
    Private m_waveSelectCheckBox As CheckBox() = New CheckBox(5) {}

#End Region

    Public Sub New()
        InitializeComponent()
    End Sub

    Private Sub StaticAOForm_Load(ByVal sender As Object, ByVal e As EventArgs) Handles MyBase.Load
        'initialize a timer which drive the data acquisition.
        timer_outputData.Interval = 50
        'initialize the scrollbar
        trackBar_Scroll.Maximum = 1000
        trackBar_Scroll.Minimum = 10
        trackBar_Scroll.Value = 50
        'initialize the checkbox
        m_waveSelectCheckBox(0) = checkBox_sineA
        m_waveSelectCheckBox(1) = checkBox_squareA
        m_waveSelectCheckBox(2) = checkBox_triangleA
        m_waveSelectCheckBox(3) = checkBox_sineB
        m_waveSelectCheckBox(4) = checkBox_squareB
        m_waveSelectCheckBox(5) = checkBox_triangleB

        'The default device of project is demo device, users can choose other devices according to their needs.
        If Not m_InstantAoCtrl.Initialized Then
            MessageBox.Show("Please select a device in control property!")
            Me.Close()
            Return
        End If

        m_waveformGenerator = New WaveformGenerator(m_PointCountPerWave)
        'set title of the form.
        Dim text As String = m_InstantAoCtrl.SelectedDevice.Description
      Me.Text = "Static AO - Run(" & text & ")"

        ConfigurePanel()
        timer_outputData.Start()
    End Sub

    Private Sub ConfigurePanel()
        If m_InstantAoCtrl.ChannelCount = 1 Then
            m_channelStart = 0
            m_channelCount = 1
            For i As Integer = 3 To 5
                m_waveSelectCheckBox(i).Enabled = False
            Next
            textBox_highLevelB.Enabled = False
            textBox_lowLevelB.Enabled = False
            textBox_valueB.Enabled = False
            button_manualB.Enabled = False
            label_chanB.Text = " "
        Else
            m_channelStart = 0
            m_channelCount = 2
            For i As Integer = 3 To 5
                m_waveSelectCheckBox(i).Enabled = True
            Next
            textBox_highLevelB.Enabled = True
            textBox_lowLevelB.Enabled = True
            textBox_valueB.Enabled = True
            button_manualB.Enabled = True
            Dim chanNumberB As Integer = m_channelStart + 1
            label_chanB.Text = chanNumberB.ToString()
        End If
        label_chanA.Text = m_channelStart.ToString()
    End Sub

    Private Sub CheckError(ByVal err As ErrorCode)
        If err <> ErrorCode.Success Then
            timer_outputData.[Stop]()
            MessageBox.Show("Error: " & err.ToString())
        End If
    End Sub

    Private Sub timer_outputData_Tick(ByVal sender As Object, ByVal e As EventArgs) Handles timer_outputData.Tick
        If m_isCheckedA Then
            m_dataScaled(0) = m_waveformGenerator.GetOnePoint(m_formStyleA, System.Math.Max(System.Threading.Interlocked.Increment(m_wavePointsIndexA), m_wavePointsIndexA - 1), m_highLevelA, m_lowLevelA)
            If m_wavePointsIndexA = m_PointCountPerWave Then
                m_wavePointsIndexA = 0
            End If
        End If
        If m_isCheckedB Then
            If m_channelCount > 1 Then
                m_dataScaled(1) = m_waveformGenerator.GetOnePoint(m_formStyleB, System.Math.Max(System.Threading.Interlocked.Increment(m_wavePointsIndexB), m_wavePointsIndexB - 1), m_highLevelB, m_lowLevelB)
            End If
            If m_wavePointsIndexB = m_PointCountPerWave Then
                m_wavePointsIndexB = 0
            End If
        End If
        m_err = m_InstantAoCtrl.Write(m_channelStart, m_channelCount, m_dataScaled)
        CheckError(m_err)
    End Sub

    Private Sub checkBox_AoDataOut_MouseClick(ByVal sender As Object, ByVal e As MouseEventArgs) Handles checkBox_squareA.MouseClick, checkBox_sineA.MouseClick, checkBox_triangleA.MouseClick, checkBox_triangleB.MouseClick, checkBox_squareB.MouseClick, checkBox_sineB.MouseClick
        Dim index As Integer = Array.IndexOf(m_waveSelectCheckBox, sender)
        Dim currentcheckedBox As CheckBox = DirectCast(sender, CheckBox)
        If currentcheckedBox.Checked Then
            If index < 3 Then
                ' make all the checkBoxes is unchecked
                For i As Integer = 0 To 2
                    m_waveSelectCheckBox(i).Checked = False
                    m_waveSelectCheckBox(i).BackgroundImage = imageList.Images(i)
                Next
                ' make the checkBox clicked is checked
                m_waveSelectCheckBox(index).BackgroundImage = imageList.Images(index + 3)
                ' read the user input value
                Double.TryParse(textBox_highLevelA.Text, m_highLevelA)
                Double.TryParse(textBox_lowLevelA.Text, m_lowLevelA)
                m_isCheckedA = True
                m_wavePointsIndexA = 0
                m_formStyleA = DirectCast(index Mod 3, WaveformStyle)
            Else
                For j As Integer = 3 To 5
                    m_waveSelectCheckBox(j).Checked = False
                    m_waveSelectCheckBox(j).BackgroundImage = imageList.Images(j - 3)
                Next
                m_waveSelectCheckBox(index).BackgroundImage = imageList.Images(index)
                Double.TryParse(textBox_highLevelB.Text, m_highLevelB)
                Double.TryParse(textBox_lowLevelB.Text, m_lowLevelB)
                m_isCheckedB = True
                m_wavePointsIndexB = 0
                m_formStyleB = DirectCast(index Mod 3, WaveformStyle)
            End If
            currentcheckedBox.Checked = True
        Else
            If index < 3 Then
                m_waveSelectCheckBox(index).BackgroundImage = imageList.Images(index)
                m_isCheckedA = False
            Else
                m_waveSelectCheckBox(index).BackgroundImage = imageList.Images(index - 3)
                m_isCheckedB = False
            End If
        End If
    End Sub

    Private Sub trackBar_Scroll_Scroll(ByVal sender As Object, ByVal e As EventArgs) Handles trackBar_Scroll.Scroll
        timer_outputData.Interval = trackBar_Scroll.Value
        label_interval.Text = trackBar_Scroll.Value.ToString() & "ms"
    End Sub

    Private Sub button_manualA_Click(ByVal sender As Object, ByVal e As EventArgs) Handles button_manualA.Click
        For i As Integer = 0 To 2
            m_waveSelectCheckBox(i).Checked = False
            m_waveSelectCheckBox(i).BackgroundImage = imageList.Images(i)
        Next
        m_isCheckedA = False
        Double.TryParse(textBox_valueA.Text, m_dataScaled(0))
    End Sub

    Private Sub button_manualB_Click(ByVal sender As Object, ByVal e As EventArgs) Handles button_manualB.Click
        For i As Integer = 3 To 5
            m_waveSelectCheckBox(i).Checked = False
            m_waveSelectCheckBox(i).BackgroundImage = imageList.Images(i - 3)
        Next
        m_isCheckedB = False
        Double.TryParse(textBox_valueB.Text, m_dataScaled(1))
    End Sub
End Class
