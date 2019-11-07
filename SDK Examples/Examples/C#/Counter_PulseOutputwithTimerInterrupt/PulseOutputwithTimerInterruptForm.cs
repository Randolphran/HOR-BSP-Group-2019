using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using Automation.BDaq;

namespace Counter_PulseOutputwithTimerInterrupt
{
   public partial class PulseOutputwithTimerInterruptForm : Form
   {
     // private double m_frequency;
      int m_TPevtCount = 0;

      public PulseOutputwithTimerInterruptForm()
      {
         InitializeComponent();
      }

      private void PulseOutputwithTimerInterruptForm_Load(object sender, EventArgs e)
      {
         //The default device of project is demo device, users can choose other devices according to their needs. 
         // no device is selected
         if (!m_timerPulseCtrl.Initialized)
         {
            MessageBox.Show("No device be selected or device open failed!");
            this.Close();
            return;
         }

         //set title of the form.
         string description = m_timerPulseCtrl.SelectedDevice.Description;
         this.Text = "Pulse Output with Timer Interrupt(" + description + ")";
        
			TmrChannel[] tmrChannel = m_timerPulseCtrl.Channels;
			desiredFrequency.Text = tmrChannel[m_timerPulseCtrl.ChannelStart].Frequency.ToString();
         label_eventCount.Enabled = false;
         Stop.Enabled = false;

         //Caution: When TimerTick interrupt is too frequent, the operating system may hang.
         //The following is the suggestion:
         //1.If you use the pulse output function only, you don't need to deal with TimerTick event.
         //2.If you want to use timer interrupt function, uncomment the following codes.
         
         //m_timerPulseCtrl.TimerTick += new EventHandler<CntrEventArgs>(m_timerPulseCtrl_Timer);
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
				TmrChannel[] tmrChannel = m_timerPulseCtrl.Channels;
				generatedFrequency.Text = tmrChannel[m_timerPulseCtrl.ChannelStart].Frequency.ToString();
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

      private void m_timerPulseCtrl_Timer(object sender, Automation.BDaq.CntrEventArgs e)
      {
         try
         {
            m_TPevtCount++;
            Invoke(new MethodInvoker(delegate
            {
               label_eventCount.Enabled = true;
               eventCount.Text = m_TPevtCount.ToString();
            }));
         }
         catch (System.Exception) { }
      }
   }
}