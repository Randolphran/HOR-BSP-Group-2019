Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms
Imports System.Threading
Imports Automation.BDaq


Partial Public Class BufferedPWMOutputForm
   Inherits Form
   Private m_sampleCount As UInteger
   Private m_intervelCount As UInteger
   Private m_channelEnable As Byte()
   Private m_channelCountMax As Integer

   Public Sub New()
      InitializeComponent()
   End Sub

   Private Sub BufferedePWMOutputForm_Load(ByVal sender As Object, ByVal e As EventArgs) Handles MyBase.Load
      ' no device is selected
      If Not BufferedPwModulatorCtrl1.Initialized Then
         MessageBox.Show("Please select a device in control property!")
         Me.Close()
         Return
      End If

      'set title of the form.
      Dim description As String = BufferedPwModulatorCtrl1.SelectedDevice.Description
      Me.Text = "Buffered PWM Output - Run(" & description & ")"

      btnStart.Enabled = True
      btnStop.Enabled = False

   End Sub

   Private Shared Sub ShowErrorMessage(ByVal e As Exception)
      Dim errorInfo As String
      errorInfo = "There's some error happened, the error information: "
      MessageBox.Show(errorInfo & e.Message)
   End Sub

   Private Sub HandleError(ByVal err As ErrorCode)
      If err <> ErrorCode.Success Then
         MessageBox.Show("Sorry ! There are some errors happened, the error code is: " & err.ToString(), "BuffererPWMOutput")
      End If
   End Sub

   Private Sub Start_Click(ByVal sender As Object, ByVal e As EventArgs) Handles btnStart.Click
      Dim err As ErrorCode = ErrorCode.Success
      m_channelCountMax = BufferedPwModulatorCtrl1.Features.ChannelCountMax
      m_channelEnable = New Byte(m_channelCountMax) {}
      m_channelEnable = BufferedPwModulatorCtrl1.ChannelMap

      m_sampleCount = BufferedPwModulatorCtrl1.Samples
      m_intervelCount = BufferedPwModulatorCtrl1.IntervalCount

      Dim dataBuf(m_sampleCount - 1) As Automation.BDaq.PulseWidth
      For i As Integer = 0 To m_sampleCount - 1
         If (i And 1) = 0 Then
            dataBuf(i).HiPeriod = Val(data1_HiPeriod.Text)
            dataBuf(i).LoPeriod = Val(data1_LoPeriod.Text)
         Else
            dataBuf(i).HiPeriod = Val(data2_HiPeriod.Text)
            dataBuf(i).LoPeriod = Val(data2_LoPeriod.Text)
         End If
      Next

      BufferedPwModulatorCtrl1.IntervalCount = m_intervelCount

      BufferedPwModulatorCtrl1.Samples = m_sampleCount

      BufferedPwModulatorCtrl1.Streaming = True

      For j As Integer = 0 To m_channelCountMax - 1
         If m_channelEnable(j) = 1 Then
            BufferedPwModulatorCtrl1.SetData(j, m_sampleCount, dataBuf)
         End If
      Next

      err = BufferedPwModulatorCtrl1.Prepare()
      If err <> ErrorCode.Success Then
         HandleError(err)
         Return
      End If
      ' Enable execution status
      ExecutionStatus.Enabled = True
      Try
         BufferedPwModulatorCtrl1.Enabled = True
      Catch ex As Exception
         ShowErrorMessage(ex)
      End Try

      btnStop.Enabled = True
      btnStart.Enabled = False
   End Sub

   Private Sub Stop_Click(ByVal sender As Object, ByVal e As EventArgs) Handles btnStop.Click
      Try
         BufferedPwModulatorCtrl1.Enabled = False
      Catch ex As Exception
         ShowErrorMessage(ex)
      End Try
      ' Disable execution status
      ExecutionStatus.Enabled = False
      btnStart.Enabled = True
      btnStop.Enabled = False
   End Sub
End Class


