Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms
Imports Automation.BDaq


Partial Public Class SynchronousOneWaveformAOForm
   Inherits Form
#Region "fileds"

   Private m_err As ErrorCode
   Private m_PointCountPerWave As UInteger
   Private m_dataScaled As Double()
   Private m_waveSelectCheckBox As CheckBox() = New CheckBox(5) {}
   Private m_waveformGenerator As WaveformGenerator
   Private m_formStyleB As WaveformStyle
   Private m_formStyleA As WaveformStyle
   Private m_isCheckedA As Boolean
   Private m_isCheckedB As Boolean
   Private m_highLevelA As Double
   Private m_lowLevelA As Double
   Private m_highLevelB As Double
   Private m_lowLevelB As Double

#End Region

   Public Sub New()
      InitializeComponent()
   End Sub

    Private Sub SyncOneWaveOutAoForm_Load(ByVal sender As Object, ByVal e As EventArgs) Handles MyBase.Load
      ' The default device of project is demo device, users can choose other devices according to their needs.
        If Not m_BufferedAoCtrl.Initialized Then
            MessageBox.Show("Please select a device in control property!")
            Me.Close()
            Return
        End If

        'initialize the checkBox
        m_waveSelectCheckBox = New CheckBox(5) {}
        m_waveSelectCheckBox(0) = checkBox_sineA
        m_waveSelectCheckBox(1) = checkBox_squareA
        m_waveSelectCheckBox(2) = checkBox_triangleA
        m_waveSelectCheckBox(3) = checkBox_sineB
        m_waveSelectCheckBox(4) = checkBox_squareB
        m_waveSelectCheckBox(5) = checkBox_triangleB

        'set the ChannelCount
        If m_BufferedAoCtrl.ScanChannel.ChannelCount > 1 Then
            m_BufferedAoCtrl.ScanChannel.ChannelCount = 2
        End If

        ' initialize the sine as the default choice
        checkBox_sineA.Checked = True
        checkBox_AoDataOut_MouseClick(checkBox_sineA, Nothing)
        checkBox_sineA.BackgroundImage = ImageList.Images(3)
        If m_BufferedAoCtrl.ScanChannel.ChannelCount > 1 Then
            checkBox_sineB.Checked = True
            checkBox_AoDataOut_MouseClick(checkBox_sineB, Nothing)
            checkBox_sineB.BackgroundImage = ImageList.Images(3)
        End If

        'set title of the form.
        Dim description As String = m_BufferedAoCtrl.SelectedDevice.Description
      Me.Text = "Synchronous One Waveform AO - Run(" & description & ")"

        ConfigurePanel()
    End Sub

   Private Sub ConfigurePanel()
      If 1 = m_BufferedAoCtrl.ScanChannel.ChannelCount Then
         For i As Integer = 3 To 5
            m_waveSelectCheckBox(i).Enabled = False
            m_waveSelectCheckBox(i).Checked = False
         Next
         textBox_highLevelB.Enabled = False
         textBox_lowLevelB.Enabled = False
         label_chanB.Text = " "
      Else
         For i As Integer = 3 To 5
            m_waveSelectCheckBox(i).Enabled = True
         Next
         textBox_highLevelB.Enabled = True
         textBox_lowLevelB.Enabled = True
         label_chanB.Text = ((m_BufferedAoCtrl.ScanChannel.ChannelStart + 1) Mod m_BufferedAoCtrl.ChannelCount).ToString()
      End If
      label_chanA.Text = m_BufferedAoCtrl.ScanChannel.ChannelStart.ToString()
   End Sub

   Private Sub CheckError(ByVal err As ErrorCode)
      If err <> ErrorCode.Success Then
         MessageBox.Show("Error: " & err.ToString())
      End If
   End Sub

   Private Sub checkBox_AoDataOut_MouseClick(ByVal sender As Object, ByVal e As MouseEventArgs) Handles checkBox_triangleB.MouseClick, checkBox_triangleA.MouseClick, checkBox_squareB.MouseClick, checkBox_squareA.MouseClick, checkBox_sineB.MouseClick, checkBox_sineA.MouseClick
      Dim index As Integer = Array.IndexOf(m_waveSelectCheckBox, sender)
      Dim currentcheckedBox As CheckBox = DirectCast(sender, CheckBox)
      If currentcheckedBox.Checked Then
         If index < 3 Then
            For i As Integer = 0 To 2
               m_waveSelectCheckBox(i).Checked = False
               m_waveSelectCheckBox(i).BackgroundImage = ImageList.Images(i)
            Next
            m_waveSelectCheckBox(index).BackgroundImage = ImageList.Images(index + 3)
            Double.TryParse(textBox_highLevelA.Text, m_highLevelA)
            Double.TryParse(textBox_lowLevelA.Text, m_lowLevelA)
            m_isCheckedA = True
            m_formStyleA = DirectCast(index Mod 3, WaveformStyle)
         Else
            For j As Integer = 3 To 5
               m_waveSelectCheckBox(j).Checked = False
               m_waveSelectCheckBox(j).BackgroundImage = ImageList.Images(j - 3)
            Next
            m_waveSelectCheckBox(index).BackgroundImage = ImageList.Images(index)
            Double.TryParse(textBox_highLevelB.Text, m_highLevelB)
            Double.TryParse(textBox_lowLevelB.Text, m_lowLevelB)
            m_isCheckedB = True
            m_formStyleB = DirectCast(index Mod 3, WaveformStyle)
         End If
         currentcheckedBox.Checked = True
      Else
         If index < 3 Then
            m_waveSelectCheckBox(index).BackgroundImage = ImageList.Images(index)
            m_isCheckedA = False
         Else
            m_waveSelectCheckBox(index).BackgroundImage = ImageList.Images(index - 3)
            m_isCheckedB = False
         End If
      End If
   End Sub

   Private Sub button_start_Click(ByVal sender As Object, ByVal e As EventArgs) Handles button_start.Click
      If m_isCheckedA = False AndAlso m_isCheckedB = False Then
         MessageBox.Show("Please select a waveform !")
         Return
      End If
      'prepare the AO
      m_err = m_BufferedAoCtrl.Prepare()
      CheckError(m_err)
      'generator the wave
      Double.TryParse(textBox_highLevelA.Text, m_highLevelA)
      Double.TryParse(textBox_lowLevelA.Text, m_lowLevelA)
      Double.TryParse(textBox_highLevelB.Text, m_highLevelB)
      Double.TryParse(textBox_lowLevelB.Text, m_lowLevelB)
      Dim styles As WaveformStyle() = New WaveformStyle() {m_formStyleA, m_formStyleB}
      Dim highLevels As Double() = New Double() {m_highLevelA, m_highLevelB}
      Dim lowLevels As Double() = New Double() {m_lowLevelA, m_lowLevelB}

      m_PointCountPerWave = CUInt(m_BufferedAoCtrl.ScanChannel.Samples)
      m_waveformGenerator = New WaveformGenerator(m_PointCountPerWave)
      m_dataScaled = New Double(m_BufferedAoCtrl.ScanChannel.ChannelCount * m_PointCountPerWave - 1) {}

      If m_BufferedAoCtrl.ScanChannel.ChannelCount <= 1 Then
         m_waveformGenerator.GetOnePeriod(m_dataScaled, m_formStyleA, m_highLevelA, m_lowLevelA)
      Else
         If m_isCheckedA = True AndAlso m_isCheckedB = False Then
            styles(0) = m_formStyleA
            highLevels(0) = m_highLevelA
            highLevels(1) = 0
            lowLevels(0) = m_lowLevelA
            lowLevels(1) = 0
         ElseIf m_isCheckedB = True AndAlso m_isCheckedA = False Then
            styles(1) = m_formStyleB
            highLevels(0) = 0
            highLevels(1) = m_highLevelB
            lowLevels(0) = 0
            lowLevels(1) = m_lowLevelB
         ElseIf m_isCheckedB = False AndAlso m_isCheckedA = False Then
            highLevels(0) = 0
            highLevels(1) = 0
            lowLevels(0) = 0
            lowLevels(1) = 0
         End If
         m_waveformGenerator.GetMultipleWaveform(m_dataScaled, 2, styles, highLevels, lowLevels)
      End If
      ' Convert scaled  data to raw data
      Dim offSet As Integer = 0
        m_err = m_BufferedAoCtrl.SetData(CInt(m_BufferedAoCtrl.ScanChannel.ChannelCount * m_PointCountPerWave), m_dataScaled)
      CheckError(m_err)
      ' Start buffered AO in synchronous
        m_err = m_BufferedAoCtrl.RunOnce()
      CheckError(m_err)
   End Sub
End Class


