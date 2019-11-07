using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using System.Drawing.Drawing2D;
using System.Threading;
using System.Runtime.InteropServices;
using Automation.BDaq;


namespace Counter_DelayedPulseGeneration
{
   public partial class DelayedPulseGenerationForm : Form
   {
     // private int m_clockCount;
      int m_OneShotEventCount;

      public DelayedPulseGenerationForm()
      {
         InitializeComponent();
      }

      private void DelayedPulseGenerationForm_Load(object sender, EventArgs e)
      {
         //The default device of project is demo device, users can choose other devices according to their needs. 
         // no device is selected
         if (!m_oneShotCtrl.Initialized)
         {
            MessageBox.Show("No device be selected or device open failed!");
            this.Close();
            return;
         }
         //set title of the form.
         string description = m_oneShotCtrl.SelectedDevice.Description;
         this.Text = "Delayed Pulse Generation(" + description + ")";

			OsChannel []osChannel = m_oneShotCtrl.Channels;
			delayCount.Text = osChannel[m_oneShotCtrl.ChannelStart].DelayCount.ToString();
			
         ExecutionStatus.Enabled = false;
         label_shotCount.Enabled = false;
         Stop.Enabled = false;

         //Caution: When OneShot interrupt is too frequent, the operating system may hang.
         //The following is the suggestion:
         //1.If you generate delayed pulse only, you don't need to deal with OneShot event.
         //2.If you want to use OneShot interrupt function, uncomment the following codes.
         
         //m_oneShotCtrl.OneShot += new EventHandler<CntrEventArgs>(m_OneShotCtrl_OneShot);
      }

      private static void ShowErrorMessage(Exception e)
      {
         string errorInfo;
         errorInfo = "There's some error happened, the error information: ";
         MessageBox.Show(errorInfo + e.Message);
      }

      private void Start_Click(object sender, EventArgs e)
      {
         m_OneShotEventCount = 0;
         eventCount.Text = "";
         ExecutionStatus.Enabled = true;
         try
         {
            m_oneShotCtrl.Enabled = true;
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
            m_oneShotCtrl.Enabled = false;
         }
         catch (Exception ex)
         {
            ShowErrorMessage(ex);
         }

         Start.Enabled = true;
         Stop.Enabled = false;
         ExecutionStatus.Enabled = false;
      }

      private void m_OneShotCtrl_OneShot(object sender, CntrEventArgs e)
      {
         m_OneShotEventCount++;
         try
         {
            m_OneShotEventCount++;
            Invoke(new MethodInvoker(delegate
            {
               label_shotCount.Enabled = true;
               eventCount.Text = m_OneShotEventCount.ToString();
            }));
         }catch (System.Exception){}
      }
   }
}