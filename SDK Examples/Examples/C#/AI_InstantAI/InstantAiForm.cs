using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Automation.BDaq;

namespace AI_InstantAI
{
   public partial class InstantAIForm : Form
   {
       #region fields

       SimpleGraph m_simpleGraph;
       ListViewItem m_firstItem = new ListViewItem();
       ListViewItem m_secondItem = new ListViewItem();
      
       public const int CHANNEL_COUNT_MAX = 16;
       double[] m_dataScaled = new double[CHANNEL_COUNT_MAX];
       int chanCountSet = 0;

       #endregion

      public InstantAIForm()
      {
         InitializeComponent();
      }
      
      public InstantAIForm(int deviceNumber)
      {
          InitializeComponent();
          instantAiCtrl1.SelectedDevice = new DeviceInformation(deviceNumber);
      }

      private void InstantAiForm_Load(object sender, EventArgs e)
      {
         //The default device of project is demo device, users can choose other devices according to their needs. 
         if (!instantAiCtrl1.Initialized)
          {
             MessageBox.Show("No device be selected or device open failed!", "AI_InstantAI");
              this.Close();
              return;
          }

          //set title of the form.
         this.Text = "Instant AI(" + instantAiCtrl1.SelectedDevice.Description + ")";
         
         button_start.Enabled = true;
         button_stop.Enabled = false;
         button_pause.Enabled = false;

         //initialize a graph with a picture box control to draw Ai data. 
         m_simpleGraph = new SimpleGraph(pictureBox.Size, pictureBox);
         //initialize a timer which drive the data acquisition.
         timer_getData.Interval = trackBar.Value;

         textBox.ReadOnly = true;
         textBox.Text = trackBar.Value.ToString();

         //Add combo Box  to select start channel and channel count
         int chanCount = (instantAiCtrl1.ChannelCount <= CHANNEL_COUNT_MAX) ? instantAiCtrl1.ChannelCount : CHANNEL_COUNT_MAX;

       
         int count = 0;
         for (int i = 0; i < chanCount; ++i)
         {
            comboBox_chanStart.Items.Add(i.ToString());
            count = i + 1;
            comboBox_chanCount.Items.Add(count.ToString());
         }

         comboBox_chanStart.SelectedIndex = 0;
         comboBox_chanCount.SelectedIndex = 1;

         ConfigureGraph();
         InitListView();
      }

      private void ConfigureGraph()
      {
         m_simpleGraph.XCordTimeDiv = 1000;
         string[] X_rangeLabels = new string[2];
         Helpers.GetXCordRangeLabels(X_rangeLabels, 10, 0, TimeUnit.Second);
         label_XCoordinateMax.Text = X_rangeLabels[0];
         label_XCoordinateMin.Text = X_rangeLabels[1];

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

      private void timer_getData_Tick(object sender, EventArgs e)
      {
         PerformanceCounter performanceCounter = new PerformanceCounter();
         ErrorCode err;

         performanceCounter.Start();
         err = instantAiCtrl1.Read(comboBox_chanStart.SelectedIndex, chanCountSet, m_dataScaled);
         if (err != ErrorCode.Success)
         {
             HandleError(err);
             timer_getData.Stop();
         }
         m_simpleGraph.Chart(m_dataScaled, 
									  chanCountSet, 
									  1, 
									  1.0 * trackBar.Value / 1000);
         RefreshListView();

         performanceCounter.Stop();
         int interval = (int)(trackBar.Value - performanceCounter.Duration * 1000 - 0.5);
         if ( interval > 1)
         {
            timer_getData.Interval = interval;
         }
     }

      private void trackBar_Scroll(object sender, EventArgs e)
      {
         m_simpleGraph.Clear();
         timer_getData.Interval = trackBar.Value;
         textBox.Text = trackBar.Value.ToString(); 
      }
      
      private void button_start_Click(object sender, EventArgs e)
       {
           timer_getData.Start();
           button_start.Enabled = false;
           button_pause.Enabled = true;
           button_stop.Enabled = true;
       }

      private void button_pause_Click(object sender, EventArgs e)
      {
         timer_getData.Stop();
         button_start.Enabled = true;
         button_pause.Enabled = false;
      }

      private void button_stop_Click(object sender, EventArgs e)
       {
           timer_getData.Stop();
           button_start.Enabled = true;
           button_stop.Enabled = false;
           button_pause.Enabled = false;
           Array.Clear(m_dataScaled, 0, chanCountSet);
           m_simpleGraph.Clear();
       }

      private void InitListView()
      {
         //control list view ,one grid indicates a channel which specials with color and value.
         listView.Clear();
         listView.FullRowSelect = false;
         listView.Width = 578;
         listView.Height = 53;
         listView.View = View.Details;// Set the view to show details.
         listView.HeaderStyle = ColumnHeaderStyle.None;
         listView.GridLines = true;
         // there are 8 columns for every item.
         for (int i = 0; i < 8; i++)
         {
            listView.Columns.Add("", 71);
         }

         // modify the grid's height with image Indirectly.
         ImageList imgList = new ImageList();
         imgList.ImageSize = new Size(1, 21);//width and height.
         listView.SmallImageList = imgList; //use imgList to modify the height of listView grids.
        
         // create two ListViewItem objects,so there are 16 grids for listView.
         m_firstItem = new ListViewItem();
         m_firstItem.SubItems.Clear();
         m_firstItem.UseItemStyleForSubItems = false;
         m_firstItem.Font = new Font("SimSun", 10);
         m_firstItem.SubItems[0].Text = String.Format("{0:0.0000}", m_dataScaled[0]);
         m_firstItem.SubItems[0].BackColor = m_simpleGraph.Pens[0].Color;
         for (int i = 1; i < 8; i++)
         {
             if (i < chanCountSet)
            {
               m_firstItem.SubItems.Add((String.Format("{0:0.0000}", m_dataScaled[i])), Color.Black, Color.Honeydew, new Font("SimSun", 10));
               m_firstItem.SubItems[i].BackColor = m_simpleGraph.Pens[i].Color;
               
            }else
            {
               m_firstItem.SubItems.Add("");
               m_firstItem.SubItems[i].BackColor = Color.White;
            }
         }

         m_secondItem = new ListViewItem();
         m_secondItem.SubItems.Clear();
         m_secondItem.Font = new Font("SimSun", 10);
         m_secondItem.UseItemStyleForSubItems = false;
         if (8 < chanCountSet)
         {
            m_secondItem.SubItems[0].Text = String.Format("{0:0.0000}", m_dataScaled[8]);
            m_secondItem.SubItems[0].BackColor = m_simpleGraph.Pens[8].Color;
         }else
         {
            m_secondItem.SubItems[0].Text = "";
            m_secondItem.SubItems[0].BackColor = Color.White;
         }
         for (int i = 9; i < 16;i++ )
         {
             if (i < chanCountSet)
            {
               m_secondItem.SubItems.Add((String.Format("{0:0.0000}", m_dataScaled[i])), Color.Black, Color.Honeydew, new Font("SimSun", 10));
               m_secondItem.SubItems[i - 8].BackColor = m_simpleGraph.Pens[i].Color;
            }else
            {
               m_secondItem.SubItems.Add("");
               m_secondItem.SubItems[i-8].BackColor = Color.White;
            }
         }

         ListViewItem[] list = new ListViewItem[]{m_firstItem,m_secondItem};
         listView.Items.AddRange(list);
     }

      private void RefreshListView()
      {
          for (int i = 0; i < chanCountSet; i++)
         {
            if ( i < 8 )
            {
               m_firstItem.SubItems[i].Text = String.Format("{0:0.0000}", m_dataScaled[i]);
            }else
            {
               m_secondItem.SubItems[i%8].Text = String.Format("{0:0.0000}", m_dataScaled[i]);
            }
         }
      }

      private void HandleError(ErrorCode err)
      {
         if ((err >= ErrorCode.ErrorHandleNotValid) && (err != ErrorCode.Success))
         {
            MessageBox.Show("Sorry ! some errors happened, the error code is: " + err.ToString(), "AI_InstantAI");
         }
      }

      private void comboBox_chanCount_SelectedIndexChanged(object sender, EventArgs e)
      {
         chanCountSet = comboBox_chanCount.SelectedIndex + 1;
         InitListView();
      }
   }

   public static class ConstVal
    {
        public const int Channel_Start = 0;
        public const int Channel_Count = 3;
    }
}
