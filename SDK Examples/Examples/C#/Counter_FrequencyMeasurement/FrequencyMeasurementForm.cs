using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Collections;
using Automation.BDaq;

namespace Counter_FrequencyMeasurement
{
   public partial class FrequencyMeasurementForm : Form
   {
      double[] m_frequecy; // selected counter channel' frequency.
      bool m_isCounterReseted = true;
      int m_channelCount = 2;
      int m_index = 1;
      SimpleGraph m_simpleGraph;
      ArrayList m_rangeYTypeList = new ArrayList();

      public FrequencyMeasurementForm()
      {
         InitializeComponent();
         InitRangeYTypeList();
      }

      /// <summary>
      ///  Init rangeYType list to larger and smaller the rangeY type
      /// </summary>
      private void InitRangeYTypeList()
      {
         RangeYType rangeYType = new RangeYType();
         rangeYType.rangeY = new MathInterval();
         for (int i = 10000000; i >= 1; i /= 10) //10 MHz
         {
            if (i >= 1000000)
            {
               rangeYType.rangeY.Max = i / 1000000;//MHz
               rangeYType.rangeY.Min = 0;
               rangeYType.unit = FrequencyUnit.MHz;
               m_rangeYTypeList.Add(rangeYType);
               continue;
            }
            if (i >= 1000)
            {
               rangeYType.rangeY.Max = i / 1000;//KHz
               rangeYType.rangeY.Min = 0;
               rangeYType.unit = FrequencyUnit.KHz;
               m_rangeYTypeList.Add(rangeYType);
               continue;
            }
            // Hz
            rangeYType.rangeY.Max = i;
            rangeYType.rangeY.Min = 0;
            rangeYType.unit = FrequencyUnit.Hz;
            m_rangeYTypeList.Add(rangeYType);
         }
      }

      private void FrequencyMeasurementForm_Load(object sender, EventArgs e)
      {
         //The default device of project is demo device, users can choose other devices according to their needs. 
         if (!freqMeterCtrl1.Initialized)
         {
            MessageBox.Show("No device be selected or device open failed!");
            this.Close();
            return;
         }
         // set the title of form
         SetFormTitle();
         //initialize the value of label
         fm1_label.Text = "0.0";
         fm2_label.Text = "0.0";
         // initialize a graph with a picture box control to draw frequency data. 
         m_simpleGraph = new SimpleGraph(GraphPicture.Size, GraphPicture);

         timer1.Interval = 50;
         TimeInterval.Text = trackBar.Value.ToString() + "ms";
         //set coordinate value.

         m_simpleGraph.XCordTimeDiv = 1000;
         string[] X_rangeLabels = new string[2];
         Helpers.GetXCordRangeLabels(X_rangeLabels, 10, 0, TimeUnit.Second);
         label_XCoordinateMax.Text = X_rangeLabels[0];
         label_XCoordinateMin.Text = X_rangeLabels[1];

         SetYCord(m_index);
         m_simpleGraph.Clear();
         Start.Enabled = true;
         Pause.Enabled = false;
         Stop.Enabled = false;
      }

      private void SetYCord(int index)
      {
         RangeYType rangeYType = (RangeYType)m_rangeYTypeList[index];

         string[] Y_CordLables = new string[3];
         Helpers.GetYCordRangeLabels(Y_CordLables, rangeYType.rangeY.Max, rangeYType.rangeY.Min, rangeYType.unit);
         label_YCoordinateMax.Text = Y_CordLables[0];
         label_YCoordinateMin.Text = Y_CordLables[1];
         label_YCoordinateMiddle.Text = Y_CordLables[2];

         int rate = 1;
         if (rangeYType.unit == FrequencyUnit.KHz)
         {
            rate = 1000;
         }
         else if (rangeYType.unit == FrequencyUnit.MHz)
         {
            rate = 1000 * 1000;
         }
         m_simpleGraph.YCordRangeMax = rangeYType.rangeY.Max * rate;
         m_simpleGraph.YCordRangeMin = rangeYType.rangeY.Min * rate;
      }


      private void SetFormTitle()
      {
         string description1 = freqMeterCtrl1.SelectedDevice.Description;
         string description2 = freqMeterCtrl2.SelectedDevice.Description;
         if (description1 != null && description2 == null)
         {
            this.Text = "Frequency Measurement(" + description1 + ")";
         }
         else
         {
            if (description1 == null && description2 != null)
            {
               this.Text = "Frequency Measurement(" + description2 + ")";
            }
            else
            {
               if (freqMeterCtrl1.SelectedDevice.DeviceNumber == freqMeterCtrl2.SelectedDevice.DeviceNumber)
               {
                  this.Text = "Frequency Measurement(" + description1 + ")";
               }
               else 
               {
                  this.Text = "Frequency Measurement(" + description1 + "," + description2 + ")";
               }
            }
         }
      }

      private void Stop_Click(object sender, EventArgs e)
      {
         if (freqMeterCtrl1.Enabled)
         {
            try
            {
               freqMeterCtrl1.Enabled = false;
            }
            catch (Exception ex)
            {
               ShowErrorMessage(ex);
            }
         }
         if (freqMeterCtrl2.Enabled)
         {
            try
            {
               freqMeterCtrl2.Enabled = false;
            }
            catch (Exception ex)
            {
               ShowErrorMessage(ex);
            }
         }
         timer1.Stop();
         Stop.Enabled = false;
         Pause.Enabled = false;
         Start.Enabled = true;
         m_isCounterReseted = true;
         m_simpleGraph.Clear();
      }

      private static void ShowErrorMessage(Exception e)
      {
         string errorInfo;
         errorInfo = "There's some error happened, the error information: ";
         MessageBox.Show(errorInfo + e.Message);
      }

      private void Pause_Click(object sender, EventArgs e)
      {
         timer1.Stop();
         Pause.Enabled = false;
         Start.Enabled = true;
         Stop.Enabled = true;
         m_isCounterReseted = false;
      }

      private void Start_Click(object sender, EventArgs e)
      {
         if (m_isCounterReseted == true)
         {
            try
            {
               if (freqMeterCtrl1.Initialized && freqMeterCtrl1.ChannelStart != -1)
               {
                  freqMeterCtrl1.Enabled = true;
               }
               if (freqMeterCtrl2.Initialized && freqMeterCtrl2.ChannelStart!= -1)
               {
                  freqMeterCtrl2.Enabled = true;
               }
            }
            catch (Exception ex)
            {
               ShowErrorMessage(ex);
            }
            m_frequecy = new double[m_channelCount];
            Stop.Enabled = true;
         }
         timer1.Start();
         Start.Enabled = false;
         Pause.Enabled = true;
      }

      private void timer1_Tick(object sender, EventArgs e)
      {
			if (freqMeterCtrl1.Initialized && freqMeterCtrl1.ChannelStart != -1)
         {
				freqMeterCtrl1.Read( out m_frequecy[0]);
         }
         else 
         {
            m_frequecy[0] = 0.0;
         }

			if (freqMeterCtrl2.Initialized && freqMeterCtrl2.ChannelStart != -1)
         {
				freqMeterCtrl2.Read(out m_frequecy[1]);
         }
         else
         {
            m_frequecy[1] = 0.0;
         }

         RefreshListView();
         m_simpleGraph.Chart(m_frequecy, 
				                 m_channelCount, 
									  1, 
									  1.0 * timer1.Interval / 1000);
      }

      private void trackBar_Scroll(object sender, EventArgs e)
      {
         timer1.Interval = trackBar.Value;
         TimeInterval.Text = trackBar.Value.ToString() + "ms";
         m_simpleGraph.Clear();
      }

      private void ZoomIn_Click(object sender, EventArgs e)
      {
         if (m_index <= 0)
         {
            return;
         }
         m_index--;
         SetYCord(m_index);
         m_simpleGraph.Clear();
      }

      private void ZoomOut_Click(object sender, EventArgs e)
      {
         if (m_index >= 7)
         {
            return;
         }
         m_index++;
         SetYCord(m_index);
         m_simpleGraph.Clear();
      }

      // refresh the text of listViewItem with frequency value. 
      private void RefreshListView()
      {
         //control lablel ,one item indicates a channel which specials with color and value.
         fm1_label.Text = String.Format("{0:0.0}", m_frequecy[0]);
         fm2_label.Text = String.Format("{0:0.0}", m_frequecy[1]);
      }
   }

   struct RangeYType
   {
      public MathInterval rangeY;
      public FrequencyUnit unit;
   }
}