using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Automation.BDaq;

namespace AI_AsynchronousOneBufferedAI
{
   public partial class AsynchronousOneBufferedAIForm : Form
   {
      #region fields
      SimpleGraph m_simpleGraph;
      double[] m_dataScaled;

      TimeUnit m_timeUnit;
      
      delegate void UpdateUIDelegate();

      int dataReadyCountAllChan;

      #endregion

      public AsynchronousOneBufferedAIForm()
		{
         InitializeComponent();
      }

      public AsynchronousOneBufferedAIForm(int deviceNumber)
      {
         InitializeComponent();
         waveformAiCtrl1.SelectedDevice = new DeviceInformation(deviceNumber);
      }
      
      private void AsyncOneBufferedAiForm_Load(object sender, EventArgs e)
      {
			//The default device of project is demo device, users can choose other devices according to their needs. 
			if (!waveformAiCtrl1.Initialized)
			{
				MessageBox.Show("No device be selected or device open failed!", "AsynchronousOneBufferedAI");
				this.Close();
				return;
			}


         if (waveformAiCtrl1.Features.TriggerSupported)
         {
				waveformAiCtrl1.Trigger.Action = TriggerAction.DelayToStop;
         }

         //for trigger1. user can use trigger1 for delay to stop function. 
         //set Trigger1.Action = TriggerAction.DelayToStop and Trigger.Source = SignalDrop.SignalNone
         if (waveformAiCtrl1.Features.Trigger1Supported)
         {
            waveformAiCtrl1.Trigger1.Source = SignalDrop.SignalNone;
         }
         //initialize a graph with a picture box control to draw Ai data. 
         m_simpleGraph = new SimpleGraph(pictureBox.Size, pictureBox);
			int chanCount = waveformAiCtrl1.Conversion.ChannelCount;
			int sectionLength = waveformAiCtrl1.Record.SectionLength;
			m_dataScaled = new double[chanCount * sectionLength];
         
         this.Text = "Asynchronous One Buffered AI with Trigger Delay to Stop (" + waveformAiCtrl1.SelectedDevice.Description + ")";
         trackBar_div.Enabled = false;
         trackBar_shift.Enabled = false;
         textBox_div.ReadOnly = true;
         textBox_shift.ReadOnly = true;

         if (waveformAiCtrl1.Trigger.Source != SignalDrop.SignalNone)
         {
				triggerPointFlag.Show();
            label_triggerPoint.Show();
         }
         else
         {
				triggerPointFlag.Hide();
            label_triggerPoint.Hide();
         }
         ConfigureGraph();
         InitListView();
      }

      private void ConfigureGraph(int sampleCountPerChan)
      {
         m_timeUnit = TimeUnit.Millisecond;
         double conversionRate = waveformAiCtrl1.Conversion.ClockRate;
         //1 pixel to 1 data point. How much time plotting pictureBox.Size.Width / 10(panelLineCount) data points requires in ms. 
         double timeInterval = 100.0 * pictureBox.Size.Width / conversionRate;
         double shiftMax = 1000.0 * sampleCountPerChan / conversionRate;
         while (conversionRate >= 10 * 1000)
         {
            timeInterval *= 1000;
            conversionRate /= 1000;
            shiftMax *= 1000;
            --m_timeUnit;
         }

         trackBar_shift.Maximum = (int)Math.Floor(shiftMax);
         trackBar_shift.Minimum = 0;
         trackBar_shift.Value = 0;
         textBox_shift.Text = trackBar_shift.Value.ToString();

         trackBar_div.Maximum = 4 * trackBar_div.Value; // 1 pixel to 4 data points
         trackBar_div.Minimum = (int)Math.Ceiling(1.0 * trackBar_div.Value / 10);
         trackBar_div.Value = (int)Math.Floor(timeInterval);
         textBox_div.Text = trackBar_div.Value.ToString();

         string[] tUnit = { "ns", "us", "ms", "Sec" };
         label_divide.Text = tUnit[(int)m_timeUnit];
         label_shift.Text = tUnit[(int)m_timeUnit];
         m_timeUnit = TimeUnit.Millisecond;
         trackBar_div.Maximum = 1000000;
         trackBar_div.Minimum = 0;

         SetXCord();
         MathInterval rangeY = new MathInterval();
         ValueUnit unit = (ValueUnit)(-1); // Don't show unit in the label.
         rangeY.Max = 10;
         rangeY.Min = -10;

         string[] Y_CordLables = new string[3];
         Helpers.GetYCordRangeLabels(Y_CordLables, rangeY.Max, rangeY.Min, unit);
         label_YCoordinateMax.Text = Y_CordLables[0];
         label_YCoordinateMin.Text = Y_CordLables[1];
         label_YCoordinateMiddle.Text = Y_CordLables[2];

         if (ValueUnit.Millivolt == unit)
         {
				rangeY.Max /= 1000;
            rangeY.Min /= 1000;
         }
         m_simpleGraph.YCordRangeMax = rangeY.Max;
         m_simpleGraph.YCordRangeMin = rangeY.Min;
         m_simpleGraph.Clear();
      }

      private void ConfigureGraph( )
      {
			waveformAiCtrl1.Prepare();
         m_timeUnit = TimeUnit.Millisecond;
         double conversionRate = waveformAiCtrl1.Conversion.ClockRate;
         //1 pixel to 1 data point. How much time plotting pictureBox.Size.Width / 10(panelLineCount) data points requires in ms. 
         double timeInterval = 100.0 * pictureBox.Size.Width / conversionRate;
         double shiftMax = 1000.0 * waveformAiCtrl1.Record.SectionLength / conversionRate;
         while (conversionRate >= 10 * 1000)
         {
            timeInterval *= 1000;
            conversionRate /= 1000;
            shiftMax *= 1000;
            --m_timeUnit;
         }

         trackBar_shift.Maximum = (int)Math.Floor(shiftMax);
         trackBar_shift.Minimum = 0;
         trackBar_shift.Value = 0;
         textBox_shift.Text = trackBar_shift.Value.ToString();

         int divValue = (int)Math.Floor(timeInterval);
         trackBar_div.Maximum = 4 * divValue; // 1 pixel to 4 data points
         trackBar_div.Minimum = (int)Math.Ceiling(1.0 * divValue / 10);
         trackBar_div.Value = divValue;
         textBox_div.Text = trackBar_div.Value.ToString();

         string[] tUnit = { "ns", "us", "ms", "Sec" };
         label_divide.Text = tUnit[(int)m_timeUnit];
         label_shift.Text = tUnit[(int)m_timeUnit];

          SetXCord();
          MathInterval rangeY = new MathInterval();
          ValueUnit unit = (ValueUnit)(-1); // Don't show unit in the label.
          rangeY.Max = 10;
          rangeY.Min = -10;

          string[] Y_CordLables = new string[3];
          Helpers.GetYCordRangeLabels(Y_CordLables,rangeY.Max, rangeY.Min, unit);
          label_YCoordinateMax.Text = Y_CordLables[0];
          label_YCoordinateMin.Text = Y_CordLables[1];
          label_YCoordinateMiddle.Text = Y_CordLables[2];

          if (ValueUnit.Millivolt == unit)
          {
             rangeY.Max /= 1000;
             rangeY.Min /= 1000;
          }
          m_simpleGraph.YCordRangeMax = rangeY.Max;
          m_simpleGraph.YCordRangeMin = rangeY.Min;
          m_simpleGraph.Clear();
      }

      private void SetXCord()
      {
         m_simpleGraph.XCordTimeDiv = trackBar_div.Value;
         m_simpleGraph.XCordTimeOffset = trackBar_shift.Value;
         double rangeMax = m_simpleGraph.XCordTimeDiv * 10 + trackBar_shift.Value;
         string[] X_rangeLabels = new string[2];
         Helpers.GetXCordRangeLabels(X_rangeLabels,rangeMax, trackBar_shift.Value, m_timeUnit);
         label_XCoordinateMax.Text = X_rangeLabels[0];
         label_XCoordinateMin.Text = X_rangeLabels[1];
      }

      private int GetArrowXCordLocation(int dataReadyCountPerChan, int delayCountPerChan, int pixelCount)
      {
         int relativePixelWidth = 0;
         double rate = waveformAiCtrl1.Conversion.ClockRate;
         double shift = trackBar_shift.Value;
         double divide = trackBar_div.Value;
         if (rate > 1000*10)
         {
            rate /= 1000;
         }
         int screenCount = (int)(divide * 10 * rate / 1000);
         int shiftCount = (int)(shift * rate / 1000);

         int showCount = dataReadyCountPerChan - delayCountPerChan - shiftCount;
         if (showCount >= 0 && showCount <= screenCount)// 
         {
            relativePixelWidth = pixelCount * showCount / screenCount;
         }else{
            relativePixelWidth = -1;
         }
         return relativePixelWidth;
      }

      private void SetTriggerPointFlagProperty(int delayCountPerChan)
      {
			int DataReadyCountPerChan = dataReadyCountAllChan / waveformAiCtrl1.Conversion.ChannelCount;
         Double rate = waveformAiCtrl1.Conversion.ClockRate;

         string unit = "ms";
         double triggerTime = 0;
         double timeFactor = 1000;
         if (rate > 1000 * 1000)
         {
            unit = "us";
            timeFactor = 1000 * 1000;
         }

         triggerTime = timeFactor * (DataReadyCountPerChan - delayCountPerChan) / rate;
         if (triggerTime > 1000 && unit == "us")
         {
            triggerTime /= 1000;
            unit = "ms";
         }
         if (triggerTime < 1 && unit == "ms")
         {
            triggerTime *= 1000;
            unit = "us";
         }
         label_triggerPoint.Text = triggerTime.ToString("F3") + unit + " Triggered.";

         int relativeWidth = GetArrowXCordLocation(DataReadyCountPerChan, delayCountPerChan, pictureBox.Size.Width);
         if (relativeWidth < 0)
         {
            triggerPointFlag.Hide();
            label_triggerPoint.Hide();
         }
         else{
            triggerPointFlag.Show();
            label_triggerPoint.Show();
            triggerPointFlag.Location = new Point(pictureBox.Location.X + relativeWidth - triggerPointFlag.Width / 2, pictureBox.Location.Y + pictureBox.Height);
            label_triggerPoint.Location = new Point(pictureBox.Location.X + relativeWidth + triggerPointFlag.Width, pictureBox.Location.Y + pictureBox.Height);
         }
      }

      private void trackBar_shift_Scroll(object sender, EventArgs e)
      {
         SetXCord();
         textBox_shift.Text = trackBar_shift.Value.ToString();
         m_simpleGraph.Shift(trackBar_shift.Value);
			if (waveformAiCtrl1.Features.TriggerSupported)
         {
            if (waveformAiCtrl1.Trigger.Source != SignalDrop.SignalNone)
            {
					Trigger trigger = waveformAiCtrl1.Trigger;
               SetTriggerPointFlagProperty(trigger.DelayCount);
            }
         }
      }

      private void trackBar_div_Scroll(object sender, EventArgs e)
      {
         m_simpleGraph.Div(trackBar_div.Value);
         SetXCord();
         textBox_div.Text = trackBar_div.Value.ToString();
			if (waveformAiCtrl1.Features.TriggerSupported)
         {
				if (waveformAiCtrl1.Trigger.Source != SignalDrop.SignalNone)
            {
					Trigger trigger = waveformAiCtrl1.Trigger;
               SetTriggerPointFlagProperty(trigger.DelayCount);
            }
         }
      }

      private void button_getData_Click(object sender, EventArgs e)
      {
         ErrorCode err = ErrorCode.Success;
			err = waveformAiCtrl1.Prepare();
         if (waveformAiCtrl1.Features.TriggerSupported)
         {
				Trigger trigger = waveformAiCtrl1.Trigger;
            double delayCountPerChanMax = 0;
            double delayCountPerChanMin = 0;
				MathInterval range = waveformAiCtrl1.Features.TriggerDelayRange;
            if (trigger.Source != SignalDrop.SignalNone)
            {
					delayCountPerChanMax = (waveformAiCtrl1.Features.SamplingMethod == SamplingMethod.EqualTimeSwitch) ?
                  (range.Max / waveformAiCtrl1.Conversion.ChannelCount):range.Max;
               delayCountPerChanMin = (waveformAiCtrl1.Features.SamplingMethod == SamplingMethod.EqualTimeSwitch)?
						(range.Min / waveformAiCtrl1.Conversion.ChannelCount) : range.Min;

               if (trigger.DelayCount > delayCountPerChanMax || trigger.DelayCount < delayCountPerChanMin)
               {
                  string errMessage = @"      parameter error: 
               DelayCount is out of range:[" +  delayCountPerChanMin.ToString() + "-" + delayCountPerChanMax.ToString() + "].";
                  MessageBox.Show(errMessage);
                  return;
               }
               else if (trigger.DelayCount > waveformAiCtrl1.BufferCapacity)
               {
                  MessageBox.Show("Error : trigger0 DelayCount should be smaller than scanChannel Samples");
                  return;
               }
            }
            else { trigger.Source = SignalDrop.SignalNone; }
         }

         if (waveformAiCtrl1.Features.Trigger1Supported)
         {
				Trigger trigger = waveformAiCtrl1.Trigger1;
            double delayCountPerChanMax = 0;
            double delayCountPerChanMin = 0;
				MathInterval range = waveformAiCtrl1.Features.Trigger1DelayRange;
            if (trigger.Source != SignalDrop.SignalNone)
            {
					delayCountPerChanMax = (waveformAiCtrl1.Features.SamplingMethod == SamplingMethod.EqualTimeSwitch) ?
                  (range.Max / waveformAiCtrl1.Conversion.ChannelCount) : range.Max;
					delayCountPerChanMin = (waveformAiCtrl1.Features.SamplingMethod == SamplingMethod.EqualTimeSwitch) ?
						(range.Min / waveformAiCtrl1.Conversion.ChannelCount) : range.Min;

               if (trigger.DelayCount > delayCountPerChanMax || trigger.DelayCount < delayCountPerChanMin)
               {
                  string errMessage = @"      parameter error: 
               DelayCount is out of range:[" + delayCountPerChanMin.ToString() + "-" + delayCountPerChanMax.ToString() + "].";
                  MessageBox.Show(errMessage);
                  return;
               }
               else if (trigger.DelayCount > waveformAiCtrl1.BufferCapacity)
               {
                  MessageBox.Show("Error : trigger1 DelayCount should be smaller than scanChannel Samples");
                  return;
               }
            }
            else { trigger.Source = SignalDrop.SignalNone; }
         }

          m_simpleGraph.Clear();
			 //err = waveformAiCtrl1.Prepare();
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

         trackBar_div.Enabled = true;
         trackBar_shift.Enabled = true;
         button_getData.Enabled = false;
      }

      private void bufferedAiCtrl1_Stopped(object sender, BfdAiEventArgs args)
		{
			ErrorCode err;
			int chanCount = waveformAiCtrl1.Conversion.ChannelCount;
			int sectionLength = waveformAiCtrl1.Record.SectionLength;
			int realCount = (args.Count < (chanCount * sectionLength)) ? args.Count : (chanCount * sectionLength);			  
			try
			{
				//The WaveformAi has been disposed.
				if (waveformAiCtrl1.State == ControlState.Idle)
				{
					return;
				}

				err = waveformAiCtrl1.GetData(realCount, m_dataScaled);
				if (err != ErrorCode.Success && err != ErrorCode.WarningRecordEnd)
				{
					HandleError(err);
					return;
				}

				this.Invoke((UpdateUIDelegate)delegate()
				{
					ConfigureGraph(realCount/chanCount);
					m_simpleGraph.Chart(m_dataScaled, 
											  chanCount, 
						                 realCount / chanCount, 
											  1.0 / waveformAiCtrl1.Conversion.ClockRate);
					dataReadyCountAllChan = args.Count;

					if (waveformAiCtrl1.Features.TriggerSupported)
					{
						if (waveformAiCtrl1.Trigger.Source != SignalDrop.SignalNone)
						{
							Trigger trigger = waveformAiCtrl1.Trigger;
							// if user using trigger1 for delay to stop function, the parameter is waveformAiCtrl.Trigger1.DelayCount. 
							SetTriggerPointFlagProperty(trigger.DelayCount);
						}
					}
					button_getData.Enabled = true;
				});
			}
			catch (System.Exception) { }
		}

      private void InitListView()
      {
         //control list view ,one grid indicates a channel which specials with color.
         listView.Clear();
         listView.FullRowSelect = false;
         listView.Width = 500;
         listView.Height = 38;
         listView.View = View.Details;// Set the view to show details.
         listView.HeaderStyle = ColumnHeaderStyle.None;
         listView.GridLines = true;
         listView.AllowDrop = false;
         listView.Capture = false;
         // there are 8 columns for every item.
         for (int i = 0; i < 8; i++)
         {
            listView.Columns.Add("", 55);
         }

         // modify the grid's height with image Indirectly.
         ImageList imgList = new ImageList();
         imgList.ImageSize = new Size(1, 14);//width and height.
         listView.SmallImageList = imgList; //use imgList to modify the height of listView grids.

         // create two ListViewItem objects,so there are 16 grids for listView.
         ListViewItem firstItem;
         ListViewItem secondItem;

         firstItem = new ListViewItem();
         firstItem.SubItems.Clear();
         firstItem.UseItemStyleForSubItems = false;
         firstItem.Font = new Font("SimSun", 10);

         secondItem = new ListViewItem();
         secondItem.SubItems.Clear();
         secondItem.UseItemStyleForSubItems = false;
         secondItem.Font = new Font("SimSun", 10);

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
         listView.SendToBack();
      }

      private void HandleError(ErrorCode err)
      {
         if ((err >= ErrorCode.ErrorHandleNotValid) && (err != ErrorCode.Success))
         {
            MessageBox.Show("Sorry ! There are some errors happened, the error code is: " + err.ToString(), "AsynchronousOneBufferedAI");
         }
      }
   }
}