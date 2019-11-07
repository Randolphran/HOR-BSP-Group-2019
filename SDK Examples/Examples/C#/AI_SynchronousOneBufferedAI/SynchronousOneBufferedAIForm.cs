using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using Automation.BDaq;

namespace AI_SynchronousOneBufferedAI
{
   public partial class SynchronousOneBufferedAIForm : Form
   {
      #region fields
      SimpleGraph  m_simpleGraph;
     
      
      double[]   m_dataScaled;
     
      TimeUnit   m_timeUnit;
      #endregion

      public SynchronousOneBufferedAIForm()
      {
		 InitializeComponent();
      }

      public SynchronousOneBufferedAIForm(int deviceNumber)
      {
         InitializeComponent();
         waveformAiCtrl1.SelectedDevice = new DeviceInformation(deviceNumber);
      }

      private void SyncOneBufferedAiForm_Load(object sender, EventArgs e)
      {
		 //The default device of project is demo device, users can choose other devices according to their needs. 
		 if (!waveformAiCtrl1.Initialized)
         {
            MessageBox.Show("No device be selected or device open failed!", "SynchronousOneBufferedAI");
			   this.Close();
		   	return;
         }
		   int chanCount = waveformAiCtrl1.Conversion.ChannelCount;
			int sectionLength = waveformAiCtrl1.Record.SectionLength;
			m_dataScaled = new double[chanCount * sectionLength];

         //initialize a graph with a picture box control to draw Ai data. 
         m_simpleGraph = new SimpleGraph(pictureBox.Size, pictureBox);
         this.Text = "Synchronous One Buffered AI(" + waveformAiCtrl1.SelectedDevice.Description + ")";
         trackBar_div.Enabled = false;
         trackBar_shift.Enabled = false;
         textBox_div.ReadOnly = true;
         textBox_shift.ReadOnly = true;
         
         ConfigureGraph();
         InitListView();
      }

      private void ConfigureGraph()
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

      private void SetXCord()
      {
          m_simpleGraph.XCordTimeDiv = trackBar_div.Value;
          m_simpleGraph.XCordTimeOffset = trackBar_shift.Value;
          double rangeMax = m_simpleGraph.XCordTimeDiv * 10 + trackBar_shift.Value;
          string[] X_rangeLabels = new string[2];
          Helpers.GetXCordRangeLabels(X_rangeLabels, rangeMax, trackBar_shift.Value, m_timeUnit);
          label_XCoordinateMax.Text = X_rangeLabels[0];
          label_XCoordinateMin.Text = X_rangeLabels[1];
      }

      private void HandleError(ErrorCode err)
		{
         if ((err >= ErrorCode.ErrorHandleNotValid) && (err != ErrorCode.Success))
			{
				MessageBox.Show("Sorry ! There are some errors happened, the error code is: " + err.ToString(), "AI_OneShotSynchronousBuffered");
			}
		}

      private void button_getData_Click(object sender, EventArgs e)
      {
			ErrorCode err = ErrorCode.Success;
			int chanCount = waveformAiCtrl1.Conversion.ChannelCount;
			int sectionLength = waveformAiCtrl1.Record.SectionLength;
			int realCount = chanCount * sectionLength;
         m_simpleGraph.Clear();
         ConfigureGraph();
         if (err == ErrorCode.Success)
         {
				err = waveformAiCtrl1.Start();
            if (err == ErrorCode.Success)
            {
					int returnValue = 0;
					err = waveformAiCtrl1.GetData(realCount, m_dataScaled, -1, out returnValue);
            }
         }

         if (err != ErrorCode.Success)
         {
				button_getData.Enabled = true;
				HandleError(err);
				return;
         }
			
			waveformAiCtrl1.Release();
         trackBar_div.Enabled = true;
         trackBar_shift.Enabled = true;
         m_simpleGraph.Chart(m_dataScaled,
                             chanCount,
                             realCount / chanCount,
                             1.0/waveformAiCtrl1.Conversion.ClockRate);
      }

      private void trackBar_shift_Scroll(object sender, EventArgs e)
      {
			SetXCord();
         textBox_shift.Text = trackBar_shift.Value.ToString();
         m_simpleGraph.Shift(trackBar_shift.Value);
      }

      private void trackBar_div_Scroll(object sender, EventArgs e)
      {
         m_simpleGraph.Div(trackBar_div.Value);
         SetXCord();
         textBox_div.Text = trackBar_div.Value.ToString();
      }

      private void InitListView()
      {
         //control list view ,one grid indicates a channel which specials with color.
         listView.Clear();
         listView.FullRowSelect = false;
         listView.Width = 512;
         listView.Height = 43;
         listView.View = View.Details;// Set the view to show details.
         listView.HeaderStyle = ColumnHeaderStyle.None;
         listView.GridLines = true;
         // there are 8 columns for every item.
         for (int i = 0; i < 8; i++)
         {
            listView.Columns.Add("", 63);
         }

         // modify the grid's height with image Indirectly.
         ImageList imgList = new ImageList();
         imgList.ImageSize = new Size(1, 16);//width and height.
         listView.SmallImageList = imgList; //use imgList to modify the height of listView grids.

         // create two ListViewItem objects,so there are 16 grids for listView.
         ListViewItem firstItem;
         ListViewItem secondItem;

         firstItem = new ListViewItem();
         firstItem.SubItems.Clear();
         firstItem.UseItemStyleForSubItems = false;
         firstItem.Font = new Font("Microsoft Sans Serif", 10);

         secondItem = new ListViewItem();
         secondItem.SubItems.Clear();
         secondItem.UseItemStyleForSubItems = false;
         secondItem.Font = new Font("Microsoft Sans Serif", 10);

         // format every grid for output.
         firstItem.SubItems[0].Text = "";
         firstItem.SubItems[0].BackColor = m_simpleGraph.Pens[0].Color;
         for (int i = 1; i < 8; i++)
         {
            if (i < waveformAiCtrl1.Conversion.ChannelCount)
            {
               firstItem.SubItems.Add((""), Color.Black, Color.Honeydew, new Font("Microsoft Sans Serif", 10));
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
                secondItem.SubItems.Add((""), Color.Black, Color.Honeydew, new Font("Microsoft Sans Serif", 10));
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
   }
}