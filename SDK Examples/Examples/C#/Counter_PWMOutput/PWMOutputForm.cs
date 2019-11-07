using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using Automation.BDaq;

namespace Counter_PWMOutput
{
   public partial class PWMOutputForm : Form
   {
      public PWMOutputForm()
      {
         InitializeComponent();
      }

      private void PwModulatorForm_Load(object sender, EventArgs e)
      {
         //The default device of project is demo device, users can choose other devices according to their needs. 
         // no device is selected
         if (!m_pwModulatorCtrl.Initialized)
         {
            MessageBox.Show("No device be selected or device open failed!");
            this.Close();
            return;
         }

         //set title of the form.
         string description = m_pwModulatorCtrl.SelectedDevice.Description;
         this.Text = "PWM Output(" + description + ")";
			PoChannel[] poChannel = m_pwModulatorCtrl.Channels;
			desiredHiPeriod.Text = poChannel[m_pwModulatorCtrl.ChannelStart].PulseWidth.HiPeriod.ToString();
			desiredLoPeriod.Text = poChannel[m_pwModulatorCtrl.ChannelStart].PulseWidth.LoPeriod.ToString();
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
         // Enable execution status
         ExecutionStatus.Enabled = true;
			PoChannel []poChannel = m_pwModulatorCtrl.Channels;
         try
         {            
            m_pwModulatorCtrl.Enabled = true;
				generatedHiPeriod.Text = poChannel[m_pwModulatorCtrl.ChannelStart].PulseWidth.HiPeriod.ToString();
				generatedLoPeriod.Text = poChannel[m_pwModulatorCtrl.ChannelStart].PulseWidth.LoPeriod.ToString();

         }
         catch (Exception ex)
         {
            ShowErrorMessage(ex);
            generatedHiPeriod.Text = "";
            generatedLoPeriod.Text = "";
         }

         Stop.Enabled = true;
         Start.Enabled = false;
      }

      private void Stop_Click(object sender, EventArgs e)
      {
         try
         {
            m_pwModulatorCtrl.Enabled = false;
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