using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using Advantech.BioDaq;
using Advantech.BioDaq.DeviceCtrl;

namespace TimerPulse
{
   public partial class TimerPulse : Form
   {
     // private double m_frequency;
      int m_TPevtCount = 0;

      public TimerPulse()
      {
         InitializeComponent();
      }

      public TimerPulse(int deviceNumber, int channel)
      {
         InitializeComponent();
         m_timerPulseCtrl.SelectedDevice = new DeviceInformation(deviceNumber);
         m_timerPulseCtrl.Channel = channel;
      }

      private void TimerPulse_Load(object sender, EventArgs e)
      {
         // no device is selected
         if (!m_timerPulseCtrl.IsDeviceOK)
         {
            MessageBox.Show("Please select a device in control property!");
            this.Close();
            return;
         }

         //set title of the form.
         string description = m_timerPulseCtrl.SelectedDevice.Description;
         description = description.Substring(0, description.IndexOf('\0'));
         this.Text = "Timer Pulse (" + description + ")";

         desiredFrequency.Text = m_timerPulseCtrl.Frequecny.ToString();
         label_eventCount.Enabled = false;
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
         // TimerPulse event count 
         m_TPevtCount = 0;
         eventCount.Text = "";

         // Enable execution status
         ExecutionStatus.Enabled = true;
         try
         {            
            m_timerPulseCtrl.Enabled = true;
            generatedFrequency.Text = m_timerPulseCtrl.Frequecny.ToString();
         }
         catch (Exception ex)
         {
            ShowErrorMessage(ex);
            generatedFrequency.Text = "";
         }

         Stop.Enabled = true;
         Start.Enabled = false;
      }

      private void Stop_Click(object sender, EventArgs e)
      {
         try
         {
            m_timerPulseCtrl.Enabled = false;
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

      private void m_timerPulseCtrl_Timer(object sender, Advantech.BioDaq.DeviceCtrl.CntrEventArgs e)
      {
         m_TPevtCount++;
         Invoke(new MethodInvoker(delegate {
            label_eventCount.Enabled = true;
            eventCount.Text = m_TPevtCount.ToString();}));
      }
   }
}