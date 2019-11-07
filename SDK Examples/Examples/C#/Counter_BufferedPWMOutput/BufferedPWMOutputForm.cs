using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using Automation.BDaq;

namespace Counter_BufferedPWMOutput
{
   public partial class BufferedPWMOutputForm : Form
   {
      public BufferedPWMOutputForm()
      {
         InitializeComponent();
      }

      private void HandleError(ErrorCode err)
      {
         if (err != ErrorCode.Success)
         {
            MessageBox.Show("Sorry ! Some errors happened, the error code is: " + err.ToString(), "BufferedPWMOutput");
         }
      }

      private void BufferedPwModulatorForm_Load(object sender, EventArgs e)
      {
         //The default device of project is demo device, users can choose other devices according to their needs. 
         // no device is selected
         if (!bufferedPwModulatorCtrl1.Initialized)
         {
            MessageBox.Show("No device be selected or device open failed!");
            this.Close();
            return;
         }

         //set title of the form.
         string description = bufferedPwModulatorCtrl1.SelectedDevice.Description;
         this.Text = "Buffered PWM Output(" + description + ")";
         Stop.Enabled = false;
      }

      private static void ShowErrorMessage(Exception e)
      {
         string errorInfo;
         errorInfo = "There's some error happened, the error information: ";
         MessageBox.Show(errorInfo + e.Message);
      }

      private void Start_Click(object sender, EventArgs e)
      {
         ErrorCode ret = ErrorCode.Success;
         // Enable execution status
         ExecutionStatus.Enabled = true;
         int channelCountMax = bufferedPwModulatorCtrl1.Features.ChannelCountMax;
         PoChannel[] poChannel = bufferedPwModulatorCtrl1.Channels;
         int sampleCount = bufferedPwModulatorCtrl1.Samples;
         int intervelCount = bufferedPwModulatorCtrl1.IntervalCount;
         PulseWidth[] dataBuf;
         dataBuf = new PulseWidth[sampleCount];
         byte[] channelEnable;
         channelEnable = new byte[channelCountMax];
         channelEnable = bufferedPwModulatorCtrl1.ChannelMap;

         for (int i = 0; i < sampleCount; i++)
         {
            if ((i & 1) == 0)
            {
               dataBuf[i].HiPeriod = Double.Parse(data1_HiPeriod.Text);
               dataBuf[i].LoPeriod = Double.Parse(data1_LoPeriod.Text);
            }
            else
            {
               dataBuf[i].HiPeriod = Double.Parse(data2_HiPeriod.Text);
               dataBuf[i].LoPeriod = Double.Parse(data2_LoPeriod.Text);
            }
         }

         bufferedPwModulatorCtrl1.IntervalCount = intervelCount;
         bufferedPwModulatorCtrl1.Samples = sampleCount;

         for (int i = 0; i < channelCountMax; i++ )
         {
            if(channelEnable[i] == 1)
            {
               bufferedPwModulatorCtrl1.SetData(i, sampleCount, dataBuf);
            }
         }

         ret = bufferedPwModulatorCtrl1.Prepare();
         if (ret != ErrorCode.Success)
         {
            HandleError(ret);
            return;
         }
        
         try
         {
            bufferedPwModulatorCtrl1.Enabled = true;
         }
         catch (Exception ex)
         {
            ShowErrorMessage(ex);
         }

         Stop.Enabled = true;
         Start.Enabled = false;
      }

      private void Stop_Click(object sender, EventArgs e)
      {
         try
         {
            bufferedPwModulatorCtrl1.Enabled = false;
         }
         catch (Exception ex)
         {
            ShowErrorMessage(ex);
         }
         // Disable execution status
         ExecutionStatus.Enabled = false;
         Start.Enabled = true;
         Stop.Enabled = false;
      }
   }
}