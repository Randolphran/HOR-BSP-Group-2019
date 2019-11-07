Imports System.Math
Imports Automation.BDaq

Public Class BufferedUpDownCounterForm
   Inherits Form
   Protected Delegate Sub UpdateListview(ByVal eventChannel As Integer, ByVal displayChannel As Integer)
   Protected Delegate Sub StoppedEvent()
   Private m_isRunning As Boolean = False
   Private m_isCountingReset As Boolean = True
   Private m_flag As Boolean = False
   Const m_maxOfCounterValueList As Integer = 10 ' The max value of lines of CounterValueList.
   Private m_dataBuf As Integer()
   Private chs_dataBuf As Integer()()
   Private ch_status As String()
   Private m_eventChannel As Integer
   Private m_sectionLength As Integer
   Private m_samplesCount As Integer
   Private m_channelCountMax As Integer
   Private m_displayChannel As Integer
   Private m_channelEnable As Byte()
  
   Public Sub New()
      InitializeComponent()
   End Sub

   Public Sub New(ByVal deviceNumber As Integer)
      InitializeComponent()
      BufferedUdCounterCtrl1.SelectedDevice = New DeviceInformation(deviceNumber)
   End Sub

   Private Sub HandleError(ByVal err As ErrorCode)
      If err <> ErrorCode.Success Then
         MessageBox.Show("Sorry ! There are some errors happened, the error code is: " & err.ToString(), "BuffererEventCounter")
      End If
   End Sub

   Private Shared Sub ShowErrorMessage(ByVal e As Exception)
      Dim errorInfo As String
      errorInfo = "There's some error happened, the error information: "
      MessageBox.Show(errorInfo & e.Message)
   End Sub

   Protected Sub UpdateListviewMethod(ByVal eventChannel As Integer, ByVal displayChannel As Integer)
      CopyChannelData(eventChannel)
      If eventChannel = displayChannel Then
         DisplayChannelValue(displayChannel)
      End If
   End Sub

   Protected Sub StoppedEventMethod()
      Try
         If BufferedUdCounterCtrl1.State = ControlState.Stopped Then
            BufferedUdCounterCtrl1.Enabled = False
            m_isRunning = False
            m_isCountingReset = True
            btnStart.Enabled = True
            btnStop.Enabled = False
         End If
      Catch ex As Exception
         ShowErrorMessage(ex)
      End Try
      ChannelStatusStringChange(m_eventChannel, "Stopped")

      DisplayChannelStatus(m_displayChannel)
   End Sub

   Private Sub btnStop_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnStop.Click
      'Stop event counting
      Try
         BufferedUdCounterCtrl1.Enabled = False
         m_isRunning = False
      Catch ex As Exception
         ShowErrorMessage(ex)
      End Try

      m_isCountingReset = True
      btnStart.Enabled = True
      btnStop.Enabled = False

      Dim i As Int32 = 0
      For i = 0 To m_channelCountMax - 1
         If m_channelEnable(i) = 1 Then
            ChannelStatusStringChange(i, "Stopped")
         End If
      Next
      DisplayChannelStatus(m_displayChannel)
   End Sub

   Private Sub BufferedUpDownCounterForm_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
      'The default device of project is PCIE-1813.
      If Not BufferedUdCounterCtrl1.Initialized Then
         MsgBox("Please select a device with DAQNavi wizard!", , "Warning Information")
         End
      End If

      AddHandler cbxEventChannel.SelectedIndexChanged, AddressOf onCbxEventChannelSelectedIndexChanged

      m_channelCountMax = BufferedUdCounterCtrl1.Features.ChannelCountMax
      m_channelEnable = New Byte(m_channelCountMax) {}
      m_channelEnable = BufferedUdCounterCtrl1.ChannelMap

      m_sectionLength = BufferedUdCounterCtrl1.Record.SectionLength
      Dim sectionCount As Integer = BufferedUdCounterCtrl1.Record.SectionCount
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
      Dim description As String = BufferedUdCounterCtrl1.SelectedDevice.Description
      Me.Text = "Buffered Updown Counter - Run(" & description & ")"
      CounterValueList.Items.Clear()
      btnStart.Enabled = True
      btnStop.Enabled = False
   End Sub

   Private Sub btnStart_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnStart.Click
      If m_isCountingReset = True Then
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
            err = BufferedUdCounterCtrl1.Prepare()
            If err <> ErrorCode.Success Then
               HandleError(err)
               Return
            End If

            BufferedUdCounterCtrl1.Enabled = True
            m_isRunning = True

            btnStop.Enabled = True
            btnStart.Enabled = False
            m_isCountingReset = False
            m_flag = True
         Catch ex As Exception
            ShowErrorMessage(ex)
         End Try
      End If
   End Sub

   Private Sub BufferedUdCounterCtrl1_DataReady(ByVal sender As System.Object, ByVal args As Automation.BDaq.BfdCntrEventArgs) Handles BufferedUdCounterCtrl1.DataReady
      Dim err As ErrorCode = ErrorCode.Success
      Dim getDataCount As Integer = Math.Min(m_samplesCount, args.Count)
      Dim returnedCount As Integer = 0
      Dim startTime As Double = 0.0
      m_eventChannel = args.Channel
      err = BufferedUdCounterCtrl1.GetData(args.Channel, getDataCount, m_dataBuf, 0, returnedCount, startTime)
      If err <> ErrorCode.Success Then
         HandleError(err)
         Return
      End If

      Try
         Me.Invoke(New UpdateListview(AddressOf UpdateListviewMethod), New Object() {m_eventChannel, m_displayChannel})
      Catch ex As System.Exception
      End Try
   End Sub

   Private Sub BufferedUdCounterCtrl1_StoppedEvent(ByVal sender As System.Object, ByVal args As Automation.BDaq.BfdCntrEventArgs) Handles BufferedUdCounterCtrl1.Stopped
      Dim err As ErrorCode = ErrorCode.Success
      Dim getDataCount As Integer = Math.Min(m_samplesCount, args.Count)
      Dim returnedCount As Integer = 0
      Dim startTime As Double = 0.0
      m_eventChannel = args.Channel
      If getDataCount > 0 Then
         err = BufferedUdCounterCtrl1.GetData(args.Channel, getDataCount, m_dataBuf, 0, returnedCount, startTime)
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
         If m_isRunning Or m_flag Then
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
