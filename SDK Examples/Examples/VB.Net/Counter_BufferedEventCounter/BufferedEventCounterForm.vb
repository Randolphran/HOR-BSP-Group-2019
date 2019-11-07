Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms
Imports System.Collections
Imports System.Drawing.Drawing2D
Imports Automation.BDaq

Partial Public Class BufferedEventCounterForm
   Inherits Form
   Protected Delegate Sub UpdateListview(ByVal eventChannel As Integer, ByVal displayChannel As Integer)
   Protected Delegate Sub StoppedEvent()
   Private m_ECisRunning As Boolean = False
   Private m_isEventCountingReset As Boolean = True
   Private m_flag As Boolean = False
   Const m_maxOfCounterValueList As Integer = 10 ' The max value of lines of CounterValueList.
   Private m_dataBuf As Integer()
   Private chs_dataBuf As Integer()()
   Private ch_status As String()
   Private m_eventChannel As Integer
   Private m_samplesCount As Integer
   Private m_sectionLength As Integer
   Private m_channelCountMax As Integer
   Private m_displayChannel As Integer
   Private m_channelEnable As Byte()

   Public Sub New()
      InitializeComponent()
   End Sub

   Private Sub BufferedEventCounterForm_Load(ByVal sender As Object, ByVal e As EventArgs) Handles MyBase.Load
      'The default device of project is demo device, users can choose other devices according to their needs.
      If Not BufferedEventCounterCtrl1.Initialized Then
         MessageBox.Show("Please select a device in control property!")
         Me.Close()
         Return
      End If

      AddHandler cbxEventChannel.SelectedIndexChanged, AddressOf onCbxEventChannelSelectedIndexChanged

      m_channelCountMax = BufferedEventCounterCtrl1.Features.ChannelCountMax
      m_channelEnable = New Byte(m_channelCountMax) {}
      m_channelEnable = BufferedEventCounterCtrl1.ChannelMap

      m_sectionLength = BufferedEventCounterCtrl1.Record.SectionLength
      Dim sectionCount As Integer = BufferedEventCounterCtrl1.Record.SectionCount
      m_samplesCount = m_sectionLength
      If sectionCount Then
         m_samplesCount = sectionCount * m_samplesCount
      End If
      m_dataBuf = New Integer(m_samplesCount) {}
      chs_dataBuf = New Integer(m_channelCountMax)() {}
      Dim i As Integer = 0
      For i = 0 To m_channelCountMax - 1
         chs_dataBuf(i) = New Integer(m_samplesCount) {}
      Next

      'initial all channels status are Ready.
      ch_status = New String(m_channelCountMax) {}

      'configure combox;
      cbxEventChannel.BeginUpdate()
      For i = 0 To m_channelCountMax - 1
         If m_channelEnable(i) = 1 Then
            cbxEventChannel.Items.Add(i.ToString)
         End If
      Next
      cbxEventChannel.EndUpdate()
      cbxEventChannel.SelectedIndex = 0

      'display the status of default channel.
      For i = 0 To m_channelCountMax - 1
         If m_channelEnable(i) = 1 Then
            ChannelStatusStringChange(i, "Ready")
         End If
      Next
      Dim str As String = cbxEventChannel.Text
      m_displayChannel = Convert.ToInt32(str)
      DisplayChannelStatus(m_displayChannel)

      'set title of the form.
      Dim description As String = BufferedEventCounterCtrl1.SelectedDevice.Description
      Me.Text = "Buffered Event Counter - Run(" & description & ")"
      CounterValueList.Items.Clear()
      Start_button.Enabled = True
      Stop_button.Enabled = False
   End Sub

   Private Sub HandleError(ByVal err As ErrorCode)
      If err <> ErrorCode.Success Then
         MessageBox.Show("Sorry ! There are some errors happened, the error code is: " & err.ToString(), "BuffererEventCounter")
      End If
   End Sub

   Private Sub Start_Click(ByVal sender As Object, ByVal e As EventArgs) Handles Start_button.Click
      If m_isEventCountingReset = True Then
         CounterValueList.Items.Clear()
         Dim i As Int32 = 0
         For i = 0 To m_channelCountMax - 1
            If m_channelEnable(i) = 1 Then
               ChannelStatusStringChange(i, "Running")
            End If
         Next
         DisplayChannelStatus(m_displayChannel)

         Try
            Dim err As ErrorCode = ErrorCode.Success
            err = BufferedEventCounterCtrl1.Prepare()
            If err <> ErrorCode.Success Then
               HandleError(err)
               Return
            End If

            BufferedEventCounterCtrl1.Enabled = True
            m_ECisRunning = True

            Stop_button.Enabled = True
            Start_button.Enabled = False
            m_isEventCountingReset = False
            m_flag = True
         Catch ex As Exception
            ShowErrorMessage(ex)
         End Try
      End If
   End Sub

   Protected Sub UpdateListviewMethod(ByVal eventChannel As Integer, ByVal displayChannel As Integer)
      CopyChannelData(eventChannel)
      If eventChannel = displayChannel Then
         DisplayChannelValue(displayChannel)
      End If
   End Sub

   Protected Sub StoppedEventMethod()
      Try
         If BufferedEventCounterCtrl1.State = ControlState.Stopped Then
            BufferedEventCounterCtrl1.Enabled = False
            m_ECisRunning = False
            m_isEventCountingReset = True
            Start_button.Enabled = True
            Stop_button.Enabled = False
         End If
      Catch ex As Exception
         ShowErrorMessage(ex)
      End Try
      ChannelStatusStringChange(m_eventChannel, "Stopped")

      DisplayChannelStatus(m_displayChannel)
   End Sub

   Private Sub Stop_Click(ByVal sender As Object, ByVal e As EventArgs) Handles Stop_button.Click
      'Stop event counting
      Try
         BufferedEventCounterCtrl1.Enabled = False
         m_ECisRunning = False
      Catch ex As Exception
         ShowErrorMessage(ex)
      End Try

      m_isEventCountingReset = True
      Start_button.Enabled = True
      Stop_button.Enabled = False

      Dim i As Int32 = 0
      For i = 0 To m_channelCountMax - 1
         If m_channelEnable(i) = 1 Then
            ChannelStatusStringChange(i, "Stopped")
         End If
      Next
      DisplayChannelStatus(m_displayChannel)
   End Sub

   Private Shared Sub ShowErrorMessage(ByVal e As Exception)
      Dim errorInfo As String
      errorInfo = "There's some error happened, the error information: "
      MessageBox.Show(errorInfo & e.Message)
   End Sub

   Private Sub BufferedEventCounterCtrl1_DataReady(ByVal sender As Object, ByVal args As BfdCntrEventArgs) Handles BufferedEventCounterCtrl1.DataReady
      Dim err As ErrorCode = ErrorCode.Success
      Dim getDataCount As Integer = Math.Min(m_samplesCount, args.Count)
      Dim returnedCount As Integer = 0
      Dim startTime As Double = 0.0
      m_eventChannel = args.Channel
      err = BufferedEventCounterCtrl1.GetData(args.Channel, getDataCount, m_dataBuf, 0, returnedCount, startTime)
      If err <> ErrorCode.Success Then
         HandleError(err)
         Return
      End If

      Try
         Me.Invoke(New UpdateListview(AddressOf UpdateListviewMethod), New Object() {m_eventChannel, m_displayChannel})
      Catch ex As System.Exception
      End Try
   End Sub

   Private Sub BufferedEventCounterCtrl1_StoppedEvent(ByVal sender As System.Object, ByVal args As Automation.BDaq.BfdCntrEventArgs) Handles BufferedEventCounterCtrl1.Stopped
      Dim err As ErrorCode = ErrorCode.Success
      Dim getDataCount As Integer = Math.Min(m_samplesCount, args.Count)
      Dim returnedCount As Integer = 0
      Dim startTime As Double = 0.0
      m_eventChannel = args.Channel
      If getDataCount > 0 Then
         err = BufferedEventCounterCtrl1.GetData(args.Channel, getDataCount, m_dataBuf, 0, returnedCount, startTime)
         If err <> ErrorCode.Success Then
            HandleError(err)
            Return
         End If

         Try
            Me.Invoke(New UpdateListview(AddressOf UpdateListviewMethod), New Object() {m_eventChannel, m_displayChannel})
         Catch ex As System.Exception
         End Try
      End If

      Try
         Me.Invoke(New StoppedEvent(AddressOf StoppedEventMethod), New Object() {})
      Catch ex As Exception
      End Try
   End Sub

   Private Sub onCbxEventChannelSelectedIndexChanged(ByVal sender As Object, ByVal e As System.EventArgs)
      m_displayChannel = Convert.ToInt32(cbxEventChannel.Text)
      DisplayChannelValue(m_displayChannel)
      DisplayChannelStatus(m_displayChannel)
   End Sub

   Private Sub ChannelStatusStringChange(ByVal channel As Integer, ByVal status As String)
      Dim str As String = status
      Dim ch As Integer = channel
      ch_status(ch) = str
   End Sub

   Private Sub DisplayChannelStatus(ByVal channel As Integer)
      channelStatus.Text = ch_status(channel)
   End Sub

   Private Sub DisplayChannelValue(ByVal channel As Integer)
      Dim i As Int32 = 0
      CounterValueList.Items.Clear()
      Dim itemCount As Integer = 0
      If m_sectionLength >= 10 Then
         itemCount = 10
      ElseIf m_sectionLength < 10 Then
         itemCount = m_sectionLength
      End If

      Try
         DisplayChannelStatus(channel)
         If m_ECisRunning Or m_flag Then
            For i = 0 To itemCount - 1
               CounterValueList.Items.Add(chs_dataBuf(channel)(i).ToString())
            Next
         End If
      Catch ex As Exception
         ShowErrorMessage(ex)
      End Try
   End Sub

   Private Sub CopyChannelData(ByVal channel As Integer)
      Dim ch As Integer = channel
      Array.Copy(m_dataBuf, chs_dataBuf(ch), m_dataBuf.Length)
   End Sub
End Class


