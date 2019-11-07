using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.Drawing.Drawing2D;
using Automation.BDaq;


namespace Counter_BufferedPulseWidthMeasurement
{
   public partial class BufferedPulseWidthMeasurementForm : Form
   {
      protected delegate void UpdateListview(int eventChannel, int displayChannel);
      protected delegate void StopEvent();

      bool m_isRunning = false;
      bool m_isCountingReset = true;
      bool m_flag = false;
      const int m_maxOfCounterValueList = 10; // The max value of lines of CounterValueList.
      PulseWidth[] m_dataBuf;
      PulseWidth[][] chs_dataBuf;
      string[] ch_status;
      int m_eventChannel;
      int m_samplesCount;
      int m_sectionLength;
      int m_channelCountMax;
      int m_displayChannel;
      byte[] m_channelEnable;

      public BufferedPulseWidthMeasurementForm()
      {
         InitializeComponent();
      }

      private void HandleError(ErrorCode err)
      {
         if (err != ErrorCode.Success)
         {
            MessageBox.Show("Sorry ! Some errors happened, the error code is: " + err.ToString(), "BufferedPulseWidthMeasurement");
         }
      }

      private static void ShowErrorMessage(Exception e)
      {
         string errorInfo;
         errorInfo = "There's some error happened, the error information: ";
         MessageBox.Show(errorInfo + e.Message);
      }

      private void BufferedPulseWidthMeasurementForm_Load(object sender, EventArgs e)
      {
         //The default device of project is demo device, users can choose other devices according to their needs. 
         //// no device is selected
         if (!bufferedPwMeterCtrl1.Initialized)
         {
            MessageBox.Show("No device be selected or device open failed!");
            this.Close();
            return;
         }

         cbxEventChannel.SelectedIndexChanged += new EventHandler(cbxEventChannel_SelectedIndexChanged);

         m_channelCountMax = bufferedPwMeterCtrl1.Features.ChannelCountMax;
         m_channelEnable = new byte[m_channelCountMax];
         m_channelEnable = bufferedPwMeterCtrl1.ChannelMap;
         m_sectionLength = bufferedPwMeterCtrl1.Record.SectionLength;
         int sectionCount = bufferedPwMeterCtrl1.Record.SectionCount;
         m_samplesCount = m_sectionLength;
         if (sectionCount != 0)
         {
            m_samplesCount *= sectionCount;
         }
         m_dataBuf = new PulseWidth[m_samplesCount];

         chs_dataBuf = new PulseWidth[m_channelCountMax][];
         for (int i = 0; i < m_channelCountMax; i++)
         {
            chs_dataBuf[i] = new PulseWidth[m_samplesCount];
         } 
         //initial all channels status are Ready.
         ch_status = new string[m_channelCountMax];

         //configure combobox;
         for (int i = 0; i < m_channelCountMax; i++)
         {
            if (m_channelEnable[i] == 1)
            {
               cbxEventChannel.Items.Add(i);
            }
         }
         cbxEventChannel.SelectedIndex = 0;

         // display the status of default channel.
         for (int i = 0; i < m_channelCountMax; i++)
         {
            if (m_channelEnable[i] == 1)
            {
               ChannelStatusStringChange(i, "Ready");
            }
         }
         m_displayChannel = Convert.ToInt32(cbxEventChannel.Text);
         DisplayChannelStatus(m_displayChannel);

         //set title of the form.
         string description = bufferedPwMeterCtrl1.SelectedDevice.Description;
         this.Text = "Buffered Pulse Width Measurement(" + description + ")";

         CounterValueList.Items.Clear();
         Start.Enabled = true;
         Stop.Enabled = false;
      }

      private void UpdateListviewMethod(int eventChannel, int displayChannel)
      {
         CopyChannelData(eventChannel);
         if (eventChannel == displayChannel){
            DisplayChannelValue(displayChannel);
         }
      }

      private void StopEventMethod()
      {
         try
         {
            if (bufferedPwMeterCtrl1.State == ControlState.Stopped)
            {
               bufferedPwMeterCtrl1.Enabled = false;
               m_isRunning = false;
               m_isCountingReset = true;
               Start.Enabled = true;
               Stop.Enabled = false;
            }
         }
         catch (Exception ex)
         {
            ShowErrorMessage(ex);
         }

         ChannelStatusStringChange(m_eventChannel, "Stopped");
         DisplayChannelStatus(m_displayChannel);
      }

      private void Start_Click(object sender, EventArgs e)
      {
         ErrorCode err = ErrorCode.Success;
         if (m_isCountingReset == true)
         {
            CounterValueList.Items.Clear();
            for (int i = 0; i < m_channelCountMax; i++)
            {
               if (m_channelEnable[i] == 1)
               {
                  ChannelStatusStringChange(i, "Running");
               }
            }
            DisplayChannelStatus(m_displayChannel);

            err = bufferedPwMeterCtrl1.Prepare();
            if (err != ErrorCode.Success)
            {
               HandleError(err);
               return;
            }
            bufferedPwMeterCtrl1.Enabled = true;
            m_isRunning = true;
            Start.Enabled = false;
            Stop.Enabled = true;
            m_isCountingReset = false;
            m_flag = true;
         }
      }

      private void Stop_Click(object sender, EventArgs e)
      {
         // Stop event counting
         try
         {
            bufferedPwMeterCtrl1.Enabled = false;
            m_isRunning = false;
         }
         catch (Exception ex)
         {
            ShowErrorMessage(ex);
         }

         m_isCountingReset = true;
         Start.Enabled = true;
         Stop.Enabled = false;
         for (int i = 0; i < m_channelCountMax; i++)
         {
            if (m_channelEnable[i] == 1)
            {
               ChannelStatusStringChange(i, "Stopped");
            }
         }
         DisplayChannelStatus(m_displayChannel);
      }

      private void bufferedPwMeterCtrl1_DataReady(object sender, BfdCntrEventArgs e)
      {
         ErrorCode ret = ErrorCode.Success;
         int getDataCount = Math.Min(m_samplesCount, e.Count);
         int returnCount = 0;
         double startTime = 0.0;
         m_eventChannel = e.Channel;
         ret = bufferedPwMeterCtrl1.GetData(e.Channel, getDataCount, m_dataBuf, 0, out returnCount, out startTime);
         if (ret != ErrorCode.Success)
         {
            HandleError(ret);
         }

         try
         {
            Invoke(new UpdateListview(UpdateListviewMethod), new object[] {m_eventChannel, m_displayChannel});
         }
         catch (System.Exception ex) { }
      }

      private void bufferedPwMeterCtrl1_StopEvent(object sender, BfdCntrEventArgs e)
      {
         ErrorCode ret = ErrorCode.Success;
         int getDataCount = Math.Min(m_samplesCount, e.Count);
         int returnCount = 0;
         double startTime = 0.0;
         m_eventChannel = e.Channel;
         if(getDataCount > 0){
            ret = bufferedPwMeterCtrl1.GetData(e.Channel, getDataCount, m_dataBuf, 0, out returnCount, out startTime);
            if (ret != ErrorCode.Success)
            {
               HandleError(ret);
            }

            try
            {
               Invoke(new UpdateListview(UpdateListviewMethod), new object[] { m_eventChannel, m_displayChannel });
            }
            catch (System.Exception ex) { }
         }
         
         try
         {
            Invoke(new StopEvent(StopEventMethod), new object[] { });
         }
         catch (System.Exception ex) { }
      }

      private void cbxEventChannel_SelectedIndexChanged(object sender, EventArgs e)
      {
         m_displayChannel = Convert.ToInt32((cbxEventChannel.Text));
         DisplayChannelValue(m_displayChannel);
         DisplayChannelStatus(m_displayChannel);
      }

      void ChannelStatusStringChange(int channel, string status)
      {
         string str = status;
         int ch = channel;
         ch_status[ch] = str;
      }

      void DisplayChannelStatus(int channel)
      {
         channelStatus.Text = ch_status[channel];
      }

      void DisplayChannelValue(int channel)
      {
         CounterValueList.Items.Clear();
         int listCount = 0;
         if (m_sectionLength >= 10){
            listCount = 10;
         }else{
            listCount = m_sectionLength;
         }

         try
         {
            if (m_isRunning | m_flag)
            {
               for (int i = 0; i < listCount; i++)
               {
                  CounterValueList.Items.Add("High:" + chs_dataBuf[channel][i].HiPeriod.ToString("0.000000") + " s Low:" + chs_dataBuf[channel][i].LoPeriod.ToString("0.000000") + " s");
               }
            }
         }
         catch (Exception ex)
         {
            ShowErrorMessage(ex);
         }
      }

      void CopyChannelData(int channel)
      {
         int ch = channel;
         Array.Copy(m_dataBuf, 0, chs_dataBuf[ch], 0, m_dataBuf.Length);
      }
   }
}