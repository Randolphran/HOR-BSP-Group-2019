using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Automation.BDaq;

namespace AO_StaticAO
{
   public partial class StaticAOForm : Form
   {
      #region fileds

      int m_channelStart = 0;
      int m_channelCount = 0;
      uint m_PointCountPerWave = 32; 
      double[] m_dataScaled = new double[2];
      int m_wavePointsIndexA = 0;
      int m_wavePointsIndexB = 0;
      double m_highLevelA;
      double m_lowLevelA;
      double m_highLevelB;
      double m_lowLevelB;
      private bool m_isCheckedA;
      private bool m_isCheckedB;
      WaveformGenerator m_waveformGenerator;
      WaveformStyle m_formStyleA;
      WaveformStyle m_formStyleB;
      ErrorCode m_err = ErrorCode.Success;
      CheckBox[] m_waveSelectCheckBox = new CheckBox[6];

      #endregion   

      public StaticAOForm()
      {
         InitializeComponent();
      }

      private void InstantAoForm_Load(object sender, EventArgs e)
      {
         //The default device of project is demo device, users can choose other devices according to their needs. 
         //initialize a timer which drive the data acquisition.
         timer_outputData.Interval = 50;
         //initialize the scrollbar
         trackBar_Scroll.Maximum = 1000;
         trackBar_Scroll.Minimum = 10;
         trackBar_Scroll.Value = 50;
         //initialize the checkbox
         m_waveSelectCheckBox[0] = checkBox_sineA;
         m_waveSelectCheckBox[1] = checkBox_squareA;
         m_waveSelectCheckBox[2] = checkBox_triangleA;
         m_waveSelectCheckBox[3] = checkBox_sineB;
         m_waveSelectCheckBox[4] = checkBox_squareB;
         m_waveSelectCheckBox[5] = checkBox_triangleB;
         // no device is selected
         if (!m_instantAoCtrl.Initialized)
         {
            MessageBox.Show("No device be selected or device open failed!", "StaticAO");
            this.Close();
            return;
         }
 
         m_waveformGenerator = new WaveformGenerator(m_PointCountPerWave);
         //set title of the form.
         string text = m_instantAoCtrl.SelectedDevice.Description;
         this.Text = "Static AO(" + text + ")";


         ConfigurePanel();
         timer_outputData.Start();
      }

      private void ConfigurePanel()
      {
         if (m_instantAoCtrl.ChannelCount == 1)
         {
            m_channelStart = 0;
            m_channelCount = 1;
            for (int i = 3; i < 6; i++)
            {
               m_waveSelectCheckBox[i].Enabled = false;
            }
            textBox_highLevelB.Enabled = false;
            textBox_lowLevelB.Enabled = false;
            textBox_valueB.Enabled = false;
            button_manualB.Enabled = false;
            label_chanB.Text = " ";
         }
         else
         {
            m_channelStart = 0;
            m_channelCount = 2;
            for (int i = 3; i < 6; i++)
            {
               m_waveSelectCheckBox[i].Enabled = true;
            }
            textBox_highLevelB.Enabled = true;
            textBox_lowLevelB.Enabled = true;
            textBox_valueB.Enabled = true;
            button_manualB.Enabled = true;
            int chanNumberB = m_channelStart + 1;
            label_chanB.Text = chanNumberB.ToString();
         }
         label_chanA.Text = m_channelStart.ToString();
      }

      private void CheckError(ErrorCode err)
      {
         if ((err >= ErrorCode.ErrorHandleNotValid) && (err != ErrorCode.Success))
         {
            timer_outputData.Stop();
            MessageBox.Show("Error: " + err.ToString());         
         }
      }

      private void timer_outputData_Tick(object sender, EventArgs e)
      {
         if (m_isCheckedA)
         {
            m_dataScaled[0] = m_waveformGenerator.GetOnePoint(m_formStyleA, m_wavePointsIndexA++, m_highLevelA, m_lowLevelA);
            if (m_wavePointsIndexA == m_PointCountPerWave)
            {
                m_wavePointsIndexA = 0;
            }
         }
         if (m_isCheckedB)
         {
            if (m_channelCount > 1)
            {
                m_dataScaled[1] = m_waveformGenerator.GetOnePoint(m_formStyleB, m_wavePointsIndexB++, m_highLevelB, m_lowLevelB);
            }
            if (m_wavePointsIndexB == m_PointCountPerWave)
            {
                m_wavePointsIndexB = 0;
            }
         }
         m_err = m_instantAoCtrl.Write(m_channelStart,m_channelCount,m_dataScaled);
         CheckError(m_err);      
      }

      private void checkBox_AoDataOut_MouseClick(object sender, MouseEventArgs e)
      {
         int index = Array.IndexOf(m_waveSelectCheckBox, sender);
         CheckBox currentcheckedBox = (CheckBox)sender;
         if (currentcheckedBox.Checked)
         {
            if (index < 3)
            {
               // make all the checkBoxes is unchecked
               for (int i = 0; i < 3; i++)
               {
                  m_waveSelectCheckBox[i].Checked = false;
                  m_waveSelectCheckBox[i].BackgroundImage = imageList.Images[i];
               }
               // make the checkBox clicked is checked
               m_waveSelectCheckBox[index].BackgroundImage = imageList.Images[index + 3];
               // read the user input value
               double.TryParse(textBox_highLevelA.Text, out m_highLevelA);
               double.TryParse(textBox_lowLevelA.Text, out m_lowLevelA);
               m_isCheckedA = true;
               m_wavePointsIndexA = 0;
               m_formStyleA = (WaveformStyle)(index % 3);
            }
            else
            {
               for (int j = 3; j < 6; j++)
               {
                  m_waveSelectCheckBox[j].Checked = false;
                  m_waveSelectCheckBox[j].BackgroundImage = imageList.Images[j - 3];
               }
               m_waveSelectCheckBox[index].BackgroundImage = imageList.Images[index];
               double.TryParse(textBox_highLevelB.Text, out m_highLevelB);
               double.TryParse(textBox_lowLevelB.Text, out m_lowLevelB);
               m_isCheckedB = true;
               m_wavePointsIndexB = 0;
               m_formStyleB = (WaveformStyle)(index % 3);
            }
            currentcheckedBox.Checked = true;
         }
         else
         {
            if (index < 3)
            {
               m_waveSelectCheckBox[index].BackgroundImage = imageList.Images[index];
               m_isCheckedA = false;           
            }
            else
            {
               m_waveSelectCheckBox[index].BackgroundImage = imageList.Images[index - 3];
               m_isCheckedB = false;              
            }
         }       
      }

      private void trackBar_Scroll_Scroll(object sender, EventArgs e)
      {
         timer_outputData.Interval = trackBar_Scroll.Value;
         label_interval.Text = trackBar_Scroll.Value.ToString() + "ms";
      }
    
      private void button_manualA_Click(object sender, EventArgs e)
      {
         for (int i = 0; i < 3; i++)
         {
            m_waveSelectCheckBox[i].Checked = false;
            m_waveSelectCheckBox[i].BackgroundImage = imageList.Images[i];
         }
         m_isCheckedA = false;
         double.TryParse(textBox_valueA.Text, out m_dataScaled[0]);
      }

      private void button_manualB_Click(object sender, EventArgs e)
      {
         for (int i = 3; i < 6; i++)
         {
            m_waveSelectCheckBox[i].Checked = false;
            m_waveSelectCheckBox[i].BackgroundImage = imageList.Images[i-3];
         }
         m_isCheckedB = false;
         double.TryParse(textBox_valueB.Text, out m_dataScaled[1]);
      }     
   }

}