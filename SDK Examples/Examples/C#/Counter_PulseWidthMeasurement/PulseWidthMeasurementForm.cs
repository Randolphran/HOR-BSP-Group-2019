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


namespace Counter_PulseWidthMeasurement
{
   public partial class PulseWidthMeasurementForm : Form
   {
      bool m_ECisRunning = true;
      bool m_isPwMeterReset = true;
      const int m_maxOfCounterValueList = 7; // The max value of lines of CounterValueList.

      public PulseWidthMeasurementForm()
      {
         InitializeComponent();
      }

      private void PulseWidthMeasurementForm_Load(object sender, EventArgs e)
      {
         //The default device of project is demo device, users can choose other devices according to their needs. 
         //// no device is selected
         if (!m_pwMeterCtrl.Initialized)
         {
            MessageBox.Show("No device be selected or device open failed!");
            this.Close();
            return;
         }
         int t = m_pwMeterCtrl.Features.ChannelCountMax;
         //set title of the form.
         string description = m_pwMeterCtrl.SelectedDevice.Description;
         this.Text = "Pulse Width Measurement(" + description + ")";

         timer1.Enabled = false;
         Stop.Enabled = false;
      }

      private void timer1_Tick(object sender, EventArgs e)
      {
			PulseWidth value;
			try
         {
            if (m_ECisRunning)
            {
               // Show PwmIn value
					m_pwMeterCtrl.Read(out value);
					curHiPeriod.Text = value.HiPeriod.ToString("0.00000");
					curLoPeriod.Text = value.LoPeriod.ToString("0.00000");
            }
         }
         catch (Exception ex)
         {
            ShowErrorMessage(ex);
         }
      }

      private void Start_Click(object sender, EventArgs e)
      {
         if (m_isPwMeterReset == true)
         {
            CounterValueList.Items.Clear();
            try
            {
               m_pwMeterCtrl.Enabled = true;
               m_ECisRunning = true;
               if (false == timer1.Enabled)
               {
                  timer1.Start();
               }
               Stop.Enabled = true;
               Start.Text = "Latch";
               m_isPwMeterReset = false;
            }
            catch (Exception ex)
            {
               ShowErrorMessage(ex);
            }
         }
         else
         {
            CounterValueList.Items.Add("High:"+curHiPeriod.Text+" Low:"+curLoPeriod.Text);
            if (CounterValueList.Items.Count > m_maxOfCounterValueList)
            {
               CounterValueList.Items.RemoveAt(0);
            }
         }
      }

      private void Stop_Click(object sender, EventArgs e)
      {
         // Stop event counting
         try
         {
            m_pwMeterCtrl.Enabled = false;
            m_ECisRunning = false;
         }
         catch (Exception ex)
         {
            ShowErrorMessage(ex);
         }

         m_isPwMeterReset = true;
         Start.Enabled = true;
         Start.Text = "Start";
         Stop.Enabled = false;
         //stop the timer
         if (false == m_ECisRunning)
         {
            timer1.Enabled = false;
         }
      }
      private static void ShowErrorMessage(Exception e)
      {
         string errorInfo;
         errorInfo = "There's some error happened, the error information: ";
         MessageBox.Show(errorInfo + e.Message);
      }
   }
}