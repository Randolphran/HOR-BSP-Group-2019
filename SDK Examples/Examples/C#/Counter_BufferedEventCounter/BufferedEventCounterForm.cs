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

namespace Counter_BufferedEventCounter
{
   public partial class BufferedEventCounterForm : Form
   {
      protected delegate void UpdateListview(int eventChannel, int displayChannel);
      protected delegate void StopEvent();

      bool m_ECisRunning = false;
      bool m_isEventCountingReset = true;
      bool m_flag = false;
      const int m_maxOfCounterValueList = 10; // The max value of lines of CounterValueList.
      int[] m_dataBuf;
      int[][] chs_dataBuf;
      string[] ch_status;
      int m_eventChannel;
      int m_samplesCount;
      int m_sectionLength;
      int m_channelCountMax;
      int m_displayChannel;
      byte[] m_channelEnable;

      public BufferedEventCounterForm()
      {
         InitializeComponent();
      }

      private void HandleError(ErrorCode err)
      {
         if (err != ErrorCode.Success)
         {
            MessageBox.Show("Sorry ! Some errors happened, the error code is: " + err.ToString(), "BufferedEventCounter");
         }
      }

      private static void ShowErrorMessage(Exception e)
      {
         string errorInfo;
         errorInfo = "There's some error happened, the error information: ";
         MessageBox.Show(errorInfo + e.Message);
      }

      private void BufferedEventCounterForm_Load(object sender, EventArgs e)
      {
         //The default device of project is pcie-1813, users can choose other devices according to their needs. 
         //// no device is selected
         if (!bufferedEventCounterCtrl1.Initialized)
         {
            MessageBox.Show("No device be selected or device open failed!");
            this.Close();
            return;
         }

         cbxEventChannel.SelectedIndexChanged += new EventHandler(cbxEventChannel_SelectedIndexChanged);
         
         m_channelCountMax = bufferedEventCounterCtrl1.Features.ChannelCountMax;
         m_channelEnable = new byte[m_channelCountMax];
         m_channelEnable =  bufferedEventCounterCtrl1.ChannelMap;
         m_sectionLength = bufferedEventCounterCtrl1.Record.SectionLength;
         int sectionCount  = bufferedEventCounterCtrl1.Record.SectionCount;
         m_samplesCount    = m_sectionLength;
         if (sectionCount != 0){
            m_samplesCount *= sectionCount;
         } 
         m_dataBuf  = new int[m_samplesCount];
         chs_dataBuf = new int[m_channelCountMax][];
         for (int i = 0; i < m_channelCountMax; i++ )
         {
            chs_dataBuf[i] = new int[m_samplesCount];
         }
         
         //initial all channels status are Ready.
         ch_status = new string[m_channelCountMax];

         //configure combobox;
         for (int i = 0; i < m_channelCountMax; i++)
         {
             if (m_channelEnable[i] == 1){
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
         string description = bufferedEventCounterCtrl1.SelectedDevice.Description;
         this.Text = "Buffered Event Counter(" + description + ")";
         CounterValueList.Items.Clear();
         Stop.Enabled = false;
      }

      private void UpdateListviewMethod(int eventChannel,  int displayChannel)
      {
         CopyChannelData(eventChannel);
         if(eventChannel == displayChannel){
            DisplayChannelValue(displayChannel);
         }
      }

      private void StopEventMethod()
      {
         try
         {
            if (bufferedEventCounterCtrl1.State == ControlState.Stopped)
            {
               bufferedEventCounterCtrl1.Enabled = false;
               m_ECisRunning = false;
               m_isEventCountingReset = true;
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
         if (m_isEventCountingReset == true)
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

            err = bufferedEventCounterCtrl1.Prepare();
            if (err != ErrorCode.Success)
            {
               HandleError(err);
               return;
            }
            bufferedEventCounterCtrl1.Enabled = true;
            m_ECisRunning = true;
            Start.Enabled = false;
            Stop.Enabled = true;
            m_isEventCountingReset = false;
            m_flag = true;
         }
      }

      private void Stop_Click(object sender, EventArgs e)
      {
         // Stop event counting
         try
         {
            bufferedEventCounterCtrl1.Enabled = false;
            m_ECisRunning = false;
         }
         catch (Exception ex)
         {
            ShowErrorMessage(ex);
         }

         m_isEventCountingReset = true;
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
      
      private void bufferedEventCounterCtrl1_DataReady(object sender, BfdCntrEventArgs e)
      {
         ErrorCode ret = ErrorCode.Success;
         int getDataCount = Math.Min(m_samplesCount, e.Count);
         int returnCount = 0;
         double startTime = 0.0;
         m_eventChannel = e.Channel;
         ret = bufferedEventCounterCtrl1.GetData(e.Channel, getDataCount, m_dataBuf, 0, out returnCount, out startTime);
         if (ret != ErrorCode.Success)
         {
            HandleError(ret);
         }

         try
         {
            Invoke(new UpdateListview(UpdateListviewMethod), new object[] { m_eventChannel, m_displayChannel});
         }
         catch (System.Exception ex){ }
      }

      private void bufferedEventCounterCtrl1_StopEvent(object sender, BfdCntrEventArgs e)
      {
         ErrorCode ret = ErrorCode.Success;
         int getDataCount = Math.Min(m_samplesCount, e.Count);
         int returnCount = 0;
         double startTime = 0.0;
         m_eventChannel = e.Channel;
         if(getDataCount > 0){
            ret = bufferedEventCounterCtrl1.GetData(e.Channel, getDataCount, m_dataBuf, 0, out returnCount, out startTime);
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
         } else{
            listCount = m_sectionLength;
         }
         try
         {
            if (m_ECisRunning | m_flag)
            {
               for (int i = 0; i < listCount; i++)
               {
                  CounterValueList.Items.Add(chs_dataBuf[channel][i].ToString());
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