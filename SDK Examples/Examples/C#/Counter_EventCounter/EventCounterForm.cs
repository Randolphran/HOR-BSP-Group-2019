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


namespace Counter_EventCounter
{
   public partial class EventCounterForm : Form
   {
      bool m_ECisRunning = true;
      bool m_isEventCountingReset = true;
      const int m_maxOfCounterValueList = 7; // The max value of lines of CounterValueList.

      public EventCounterForm()
      {
         InitializeComponent();
      }

      private void EventCounterForm_Load(object sender, EventArgs e)
      {
         //The default device of project is demo device, users can choose other devices according to their needs. 
         //// no device is selected
         if (!m_eventCounterCtrl.Initialized)
         {
            MessageBox.Show("No device be selected or device open failed!");
            this.Close();
            return;
         }
         int t = m_eventCounterCtrl.Features.ChannelCountMax;
         //set title of the form.
         string description = m_eventCounterCtrl.SelectedDevice.Description;
         this.Text = "Event Counter(" + description + ")";

         timer1.Enabled = false;
         Stop.Enabled = false;
      }

      private void timer1_Tick(object sender, EventArgs e)
      {
			int value = 0;
			try
         {
            if (m_ECisRunning)
            {
               // Show event counting value
					m_eventCounterCtrl.Read(out value);
					CurCounterValue.Text = value.ToString();
            }
         }
         catch (Exception ex)
         {
            ShowErrorMessage(ex);
         }
      }

      private void Start_Click(object sender, EventArgs e)
      {
         if (m_isEventCountingReset == true)
         {
            CounterValueList.Items.Clear();
            try
            {
               m_eventCounterCtrl.Enabled = true;
               m_ECisRunning = true;
               if (false == timer1.Enabled)
               {
                  timer1.Start();
               }
               Stop.Enabled = true;
               Start.Text = "Latch";
               m_isEventCountingReset = false;
            }
            catch (Exception ex)
            {
               ShowErrorMessage(ex);
            }
         }
         else
         {
            CounterValueList.Items.Add(CurCounterValue.Text);
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
            m_eventCounterCtrl.Enabled = false;
            m_ECisRunning = false;
         }
         catch (Exception ex)
         {
            ShowErrorMessage(ex);
         }

         m_isEventCountingReset = true;
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