using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Automation.BDaq;

namespace AI_StreamingAI
{
   public partial class StreamingAIForm : Form
   {
      #region fields 
      SimpleGraph  m_simpleGraph;
      TimeUnit     m_timeUnit;
      double[]     m_dataScaled;
      double       m_divideValue;
      bool         m_isFirstOverRun = true;
      double       m_xInc;
      #endregion
		
		public delegate void UpdataButton();
      
		public StreamingAIForm()
      {
         InitializeComponent();
      }

      public StreamingAIForm(int deviceNumber)
      {
         InitializeComponent();
			waveformAiCtrl1.SelectedDevice = new DeviceInformation(deviceNumber);
      }
      
      private void StreamingBufferedAiForm_Load(object sender, EventArgs e)
      {
			if ((!waveformAiCtrl1.Initialized) || (!waveformAiCtrl1.Features.Retriggerable))
         {
            MessageBox.Show("No device be selected or device open failed!", "Streaming AI with Retrigger");
              this.Close();
              return;
         }

			//for trigger0
			if (waveformAiCtrl1.Features.TriggerSupported)
         {
				waveformAiCtrl1.Trigger.Action = TriggerAction.DelayToStart;
         }

         //for trigger1
			if (waveformAiCtrl1.Features.Trigger1Supported)
			{
				waveformAiCtrl1.Trigger1.Action = TriggerAction.DelayToStop;
			}

         //initialize a graph with a picture box control to draw Ai data. 
         m_simpleGraph = new SimpleGraph(pictureBox.Size, pictureBox);
         
			int chanCount = waveformAiCtrl1.Conversion.ChannelCount;
			int sectionlength = waveformAiCtrl1.Record.SectionLength;
			int sectionCount = waveformAiCtrl1.Record.SectionCount;
			int cycles = waveformAiCtrl1.Record.Cycles;

			m_dataScaled = new double[chanCount * sectionlength];
         this.Text = "Streaming AI with Retrigger(" + waveformAiCtrl1.SelectedDevice.Description + ")";

         button_start.Enabled = true;
         button_stop.Enabled = false;
         button_pause.Enabled = false;

         ConfigureGraph();
         InitListView();
      }

      private void ConfigureGraph()
      {
         m_timeUnit = TimeUnit.Millisecond;

         double conversionRate = waveformAiCtrl1.Conversion.ClockRate;
         double timeInterval = 100.0 * pictureBox.Size.Width / conversionRate;
         while (conversionRate >= 10 * 1000)
         {
            timeInterval *= 1000;
            conversionRate /= 1000;
            --m_timeUnit;
         }

         m_divideValue = timeInterval;

         int divValue = (int)Math.Floor(timeInterval);
         trackBar_div.Maximum = 4 * divValue; // 1 pixel to 4 data points
         trackBar_div.Minimum = (int)Math.Ceiling(1.0 * divValue / 10);
         trackBar_div.Value = divValue;

         m_simpleGraph.XCordTimeDiv = trackBar_div.Value;
         m_simpleGraph.XCordTimeOffset = 0;

         SetXCordRangeLabels();

         ValueUnit unit = (ValueUnit)(-1); // Don't show unit in the label.
         string[] Y_CordLables = new string[3];
         Helpers.GetYCordRangeLabels(Y_CordLables, 10, -10, unit);
         label_YCoordinateMax.Text = Y_CordLables[0];
         label_YCoordinateMin.Text = Y_CordLables[1];
         label_YCoordinateMiddle.Text = Y_CordLables[2];

         m_simpleGraph.YCordRangeMax = 10;
         m_simpleGraph.YCordRangeMin = -10;
         m_simpleGraph.Clear();
      }
     
      private void InitListView()
      {
         // listview control ,one grid indicates a channel which specials with color.
         listView.Clear();
         listView.FullRowSelect = false;
         listView.Width = 352;
         listView.Height = 43;
         listView.View = View.Details;// Set the view to show details.
         listView.HeaderStyle = ColumnHeaderStyle.None;
         listView.GridLines = true;
         // there are 8 columns for every item.
         for (int i = 0; i < 8; i++)
         {
            listView.Columns.Add("", 43);
         }

         // modify the grid's height with image Indirectly.
         ImageList imgList = new ImageList();
         imgList.ImageSize = new Size(1, 13);//width and height.
         listView.SmallImageList = imgList; //use imgList to modify the height of listView grids.

         // create two ListViewItem objects,so there are 16 grids for listView.
         ListViewItem firstItem;
         ListViewItem secondItem;

         firstItem = new ListViewItem();
         firstItem.UseItemStyleForSubItems = false;
         firstItem.SubItems.Clear();

         secondItem = new ListViewItem();
         secondItem.UseItemStyleForSubItems = false;
         secondItem.SubItems.Clear();

         // format every grid for output.
         firstItem.SubItems[0].Text = "";
         firstItem.SubItems[0].BackColor = m_simpleGraph.Pens[0].Color;
         for (int i = 1; i < 8; i++)
         {

			    if (i < waveformAiCtrl1.Conversion.ChannelCount)
            {
               firstItem.SubItems.Add((""), Color.Black, Color.Honeydew, new Font("SimSun", 10));
               firstItem.SubItems[i].BackColor = m_simpleGraph.Pens[i].Color;
            }
            else
            {
               firstItem.SubItems.Add("");
               firstItem.SubItems[i].BackColor = Color.White;
            }
         }

			if (8 < waveformAiCtrl1.Conversion.ChannelCount)
         {
            secondItem.SubItems[0].Text = "";
            secondItem.SubItems[0].BackColor = m_simpleGraph.Pens[8].Color;
         }
         else
         {
            secondItem.SubItems[0].Text = "";
            secondItem.SubItems[0].BackColor = Color.White;
         }
         for (int i = 9; i < 16; i++)
         {
				if (i < waveformAiCtrl1.Conversion.ChannelCount)
            {
               secondItem.SubItems.Add((""), Color.Black, Color.Honeydew, new Font("SimSun", 10));
               secondItem.SubItems[i - 8].BackColor = m_simpleGraph.Pens[i].Color;
            }
            else
            {
               secondItem.SubItems.Add("");
               secondItem.SubItems[i - 8].BackColor = Color.White;
            }
         }

         ListViewItem[] list = new ListViewItem[] { firstItem, secondItem };
         listView.Items.AddRange(list);
      }

      private void HandleError(ErrorCode err)
		{
         if ((err >= ErrorCode.ErrorHandleNotValid) && (err != ErrorCode.Success))
			{
				MessageBox.Show("Sorry ! Some errors happened, the error code is: " + err.ToString(), "StreamingAI");
			}
		}

      private void button_start_Click(object sender, EventArgs e)
      {
         ErrorCode err = ErrorCode.Success;
         double delayCountPerChanMax = 0;
			if (waveformAiCtrl1.Features.TriggerSupported)
         {
				Trigger trigger = waveformAiCtrl1.Trigger;
				MathInterval range = waveformAiCtrl1.Features.TriggerDelayRange;
            if (trigger.Source != SignalDrop.SignalNone)
            {
					delayCountPerChanMax = (waveformAiCtrl1.Features.SamplingMethod == SamplingMethod.EqualTimeSwitch) ?
					  (range.Max / waveformAiCtrl1.Conversion.ChannelCount) : range.Max;
               if (trigger.DelayCount > delayCountPerChanMax || trigger.DelayCount < range.Min)
               {
                  string errMessage = @"      parameter error: 
               DelayCount is within " + range.Min.ToString() + "-" + delayCountPerChanMax.ToString() + ".";
                  MessageBox.Show(errMessage);
                  return;
               }
            }
            else { trigger.Source = SignalDrop.SignalNone; }
         }

			err = waveformAiCtrl1.Prepare();
         m_xInc = 1.0 / waveformAiCtrl1.Conversion.ClockRate;
         ConfigureGraph();
         if (err == ErrorCode.Success)
         {
				err = waveformAiCtrl1.Start();
         }

         if (err != ErrorCode.Success)
         {
            HandleError(err);
            return;
         }

         button_start.Enabled = false;
         button_pause.Enabled = true;
         button_stop.Enabled = true;
      }

		private void waveformAiCtrl1_DataReady(object sender, BfdAiEventArgs args)
      {
			try
         {
            //The WaveformAiCtrl has been disposed.
            if (waveformAiCtrl1.State == ControlState.Idle)
            {
               return;
            }

            if (m_dataScaled.Length < args.Count)
            {
               m_dataScaled = new double[args.Count];
            }

				ErrorCode err = ErrorCode.Success;
				int returnedCount = 0;
				double timeStamp = 0.0;
				int markCount = 0;
				bool recordEndFlag = false;	
				int chanCount = waveformAiCtrl1.Conversion.ChannelCount;
				int sectionLength = waveformAiCtrl1.Record.SectionLength;
				err = waveformAiCtrl1.GetData(args.Count, m_dataScaled, 0, out returnedCount, out timeStamp, ref markCount, null);
				if ((err != ErrorCode.Success) && (err != ErrorCode.WarningRecordEnd))
				{
					HandleError(err);
					return;
				}
				if (err == ErrorCode.WarningRecordEnd)
				{
					recordEndFlag = true;
				}

				m_simpleGraph.Chart(m_dataScaled,
										  chanCount,
										  args.Count / chanCount,
										  m_xInc,
										  recordEndFlag);
         }
			catch (System.Exception) { }   
      }

      private void button_pause_Click(object sender, EventArgs e)
      {
         ErrorCode err = ErrorCode.Success;      
         err = waveformAiCtrl1.Stop();
         if (err != ErrorCode.Success)
         {
            HandleError(err);
            return;
         }

         button_start.Enabled = true;
         button_pause.Enabled = false;
      }

      private void button_stop_Click(object sender, EventArgs e)
      {
			ErrorCode err = ErrorCode.Success;
         err = waveformAiCtrl1.Stop();
         if (err != ErrorCode.Success)
         {
            HandleError(err);
            return;
         }   
          
         button_start.Enabled = true;
         button_pause.Enabled = false;
         button_stop.Enabled = false;
         trackBar_div.Enabled = true;
         Array.Clear(m_dataScaled, 0, m_dataScaled.Length);
         m_simpleGraph.Clear();
      }

      private void trackBar_div_Scroll(object sender, EventArgs e)
      {
         m_simpleGraph.Div(trackBar_div.Value);
         SetXCordRangeLabels();
      }

      private void SetXCordRangeLabels()
      {
         string[] X_rangeLabels = new string[2];
         Helpers.GetXCordRangeLabels(X_rangeLabels, ((int)(m_simpleGraph.XCordTimeDiv)) * 10, 0, m_timeUnit);
         label_XCoordinateMax.Text = X_rangeLabels[0];
         label_XCoordinateMin.Text = X_rangeLabels[1];
      }

		private void waveformAiCtrl1_CacheOverflow(object sender, BfdAiEventArgs e)
      {
			MessageBox.Show("WaveformAiCacheOverflow");
      }

		 private void waveformAiCtrl1_Overrun(object sender, BfdAiEventArgs e)
       {
			 if (m_isFirstOverRun)
			 {
				 MessageBox.Show("WaveformAiOverrun");
             m_isFirstOverRun = false;
          }
       }
		
		private void waveformAiCtrl1_Stop(object sender, BfdAiEventArgs e)
		 {
			try
			{
				Invoke(new UpdataButton(UpdataButtonMathod), new object[] {});
			}
			catch (System.Exception) {}
		 }

		public void UpdataButtonMathod()
		{
			button_start.Enabled = true;
			button_pause.Enabled = false;
			button_stop.Enabled = false;
			trackBar_div.Enabled = true;
		}
	}
}