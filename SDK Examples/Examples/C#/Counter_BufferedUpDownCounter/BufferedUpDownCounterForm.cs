using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Automation.BDaq;

namespace Counter_BufferedUpDownCounter
{
   public partial class BufferedUpDownCounterForm : Form
   {
      protected delegate void UpdateListview(int eventChannel, int displayChannel);
      protected delegate void StopEvent();

      bool m_isRunning = false;
      bool m_isCountingReset = true;
      bool m_flag = false;
      const int m_maxOfCounterValueList = 10; // The max value of lines of CounterValueList.
      int[] m_dataBuf;
      int[][] chs_dataBuf;
      string[] ch_status;
      int m_eventChannel;
      int m_sectionLength;
      int m_samplesCount;
      int m_channelCountMax;
      int m_displayChannel;
      byte[] m_channelEnable;

      public BufferedUpDownCounterForm()
      {
         InitializeComponent();
      }

      public BufferedUpDownCounterForm(int deviceNumber)
      {
         InitializeComponent();
         bufferedUdCounterCtrl1.SelectedDevice = new DeviceInformation(deviceNumber);
      }

      private void BufferedUpDownCounterForm_Load(object sender, EventArgs e)
      {
         if (!bufferedUdCounterCtrl1.Initialized)
         {
             MessageBox.Show("No device be selected or device open failed!", "BufferedUpDownCounter");
             this.Close();
             return;
         }

         cbxEventChannel.SelectedIndexChanged += new EventHandler(cbxEventChannel_SelectedIndexChanged);

         m_channelCountMax = bufferedUdCounterCtrl1.Features.ChannelCountMax;
         m_channelEnable = new byte[m_channelCountMax];
         m_channelEnable = bufferedUdCounterCtrl1.ChannelMap;
         m_sectionLength = bufferedUdCounterCtrl1.Record.SectionLength;
         int sectionCount = bufferedUdCounterCtrl1.Record.SectionCount;
         m_samplesCount = m_sectionLength;
         if (sectionCount != 0){
            m_samplesCount *= sectionCount;
         }
         m_dataBuf = new int[m_samplesCount];
         chs_dataBuf = new int[m_channelCountMax][];
         for (int i = 0; i < m_channelCountMax; i++)
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

         // display the status of default channel .
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
         this.Text = "Buffered UpDown Counter(" + bufferedUdCounterCtrl1.SelectedDevice.Description + ")";

         CounterValueList.Items.Clear();
         btnStart.Enabled = true;
         btnStop.Enabled = false;
      }

      private void HandleError(ErrorCode err)
     {
        if (err != ErrorCode.Success)
        {
           MessageBox.Show("Sorry ! Some errors happened, the error code is: " + err.ToString(), "BufferedUpDownCounter");
        }
     }

     private static void ShowErrorMessage(Exception e)
     {
        string errorInfo;
        errorInfo = "There's some error happened, the error information: ";
        MessageBox.Show(errorInfo + e.Message);
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
            if (bufferedUdCounterCtrl1.State == ControlState.Stopped)
            {
               bufferedUdCounterCtrl1.Enabled = false;
               m_isRunning = false;
               m_isCountingReset = true;
               btnStart.Enabled = true;
               btnStop.Enabled = false;
            }
         }
         catch (Exception ex)
         {
            ShowErrorMessage(ex);
         }

         ChannelStatusStringChange(m_eventChannel, "Stopped");
      
         DisplayChannelStatus(m_displayChannel);
     }

     private void btnStop_Click(object sender, EventArgs e)
     {
         // Stop event counting
         try
         {
            bufferedUdCounterCtrl1.Enabled = false;
            m_isRunning = false;
         }
         catch (Exception ex)
         {
            ShowErrorMessage(ex);
         }

         m_isCountingReset = true;
         btnStart.Enabled = true;
         btnStop.Enabled = false;
         for (int i = 0; i < m_channelCountMax; i++)
         {
            if (m_channelEnable[i] == 1)
            {
               ChannelStatusStringChange(i, "Stopped");
            }
         }
         DisplayChannelStatus(m_displayChannel);
     }
    
     private void btnStart_Click(object sender, EventArgs e)
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

           err = bufferedUdCounterCtrl1.Prepare();
           if (err != ErrorCode.Success)
           {
              HandleError(err);
              return;
           }
           bufferedUdCounterCtrl1.Enabled = true;
           m_isRunning = true;
           btnStart.Enabled = false;
           btnStop.Enabled = true;
           m_isCountingReset = false;
           m_flag = true;
        }
      }

      private void bufferedUdCounterCtrl1_DataReady(object sender, BfdCntrEventArgs e)
      {
         ErrorCode ret = ErrorCode.Success;
         int getDataCount = Math.Min(m_samplesCount, e.Count);
         int returnCount = 0;
         double startTime = 0.0;
         m_eventChannel = e.Channel;
         ret = bufferedUdCounterCtrl1.GetData(e.Channel, getDataCount, m_dataBuf, 0, out returnCount, out startTime);
         if (ret != ErrorCode.Success)
         {
            HandleError(ret);
         }
         try
         {
            Invoke(new UpdateListview(UpdateListviewMethod), new object[] {m_eventChannel, m_displayChannel });
         }
         catch (System.Exception ex) { }
      }

      private void bufferedUdCounterCtrl1_StopEvent(object sender, BfdCntrEventArgs e)
      {
         ErrorCode ret = ErrorCode.Success;
         int getDataCount = Math.Min(m_samplesCount, e.Count);
         int returnCount = 0;
         double startTime = 0.0;
         m_eventChannel = e.Channel;
         if(getDataCount > 0){
            ret = bufferedUdCounterCtrl1.GetData(e.Channel, getDataCount, m_dataBuf, 0, out returnCount, out startTime);
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