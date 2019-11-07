using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using Automation.BDaq;

namespace AO_AsynchronousOneWaveformAO
{
   public partial class AsynchronousOneWaveformAOForm : Form
   {
      #region fileds

      WaveformGenerator m_waveformGenerator;
      uint m_PointCountPerWave;
      ErrorCode m_err;
      double[] m_dataScaled;
      CheckBox[] m_waveSelectCheckBox;
      bool formCloseFlag = false;

      private WaveformStyle m_formStyleB;
      private WaveformStyle m_formStyleA;
      private bool m_isCheckedA;
      private bool m_isCheckedB;
      double m_highLevelA;
      double m_lowLevelA;
      double m_highLevelB;
      double m_lowLevelB;

      #endregion

      public AsynchronousOneWaveformAOForm()
      {
         InitializeComponent();
      }

      private void AsynchronousOneWaveformAOForm_Load(object sender, EventArgs e)
      {
         //The default device of project is demo device, users can choose other devices according to their needs. 
         // no device is selected
         if (!m_bufferedAoCtrl.Initialized)
         {
            MessageBox.Show("No device be selected or device open failed!", "AsynchronousOneWaveformAO");
            this.Close();
            return;
         }

         m_bufferedAoCtrl.Streaming = false; // specify the running mode: one-buffered.
         //initialize the checkBox
         m_waveSelectCheckBox = new CheckBox[6];
         m_waveSelectCheckBox[0] = checkBox_sineA;
         m_waveSelectCheckBox[1] = checkBox_squareA;
         m_waveSelectCheckBox[2] = checkBox_triangleA;
         m_waveSelectCheckBox[3] = checkBox_sineB;
         m_waveSelectCheckBox[4] = checkBox_squareB;
         m_waveSelectCheckBox[5] = checkBox_triangleB;

         //set the ChannelCount
         if (m_bufferedAoCtrl.ScanChannel.ChannelCount > 1)
         {
            m_bufferedAoCtrl.ScanChannel.ChannelCount = 2;
         }
         ConfigurePanel();
         // initialize the sine as the default choice
         checkBox_sineA.Checked = true;
         checkBox_AoDataOut_MouseClick(checkBox_sineA, null);
         checkBox_sineA.BackgroundImage = imageList.Images[3];
         if (m_bufferedAoCtrl.ScanChannel.ChannelCount > 1)
         {
            checkBox_sineB.Checked = true;
            checkBox_AoDataOut_MouseClick(checkBox_sineB, null);
            checkBox_sineB.BackgroundImage = imageList.Images[3];
         }

         //set title of the form.
         string description = m_bufferedAoCtrl.SelectedDevice.Description;
         this.Text = "Asynchronous One Waveform AO(" + description + ")";
      }

      private void ConfigurePanel()
      {
         if (1 == m_bufferedAoCtrl.ScanChannel.ChannelCount)
         {
            for (int i = 3; i < 6; i++)
            {
               m_waveSelectCheckBox[i].Enabled = false;
               m_waveSelectCheckBox[i].Checked = false;
            }
            textBox_highLevelB.Enabled = false;
            textBox_lowLevelB.Enabled = false;
            label_chanB.Text = " ";
         }
         else
         {
            for (int i = 3; i < 6; i++)
            {
               m_waveSelectCheckBox[i].Enabled = true;
            }
            textBox_highLevelB.Enabled = true;
            textBox_lowLevelB.Enabled = true;
            label_chanB.Text = ((m_bufferedAoCtrl.ScanChannel.ChannelStart + 1) % m_bufferedAoCtrl.ChannelCount).ToString();
         }
         label_chanA.Text = m_bufferedAoCtrl.ScanChannel.ChannelStart.ToString();
      }

      private void CheckError(ErrorCode err)
      {
         if ((err >= ErrorCode.ErrorHandleNotValid) && (err != ErrorCode.Success))
         {
            MessageBox.Show("Error: " + err.ToString());
         }
      }

      private void checkBox_AoDataOut_MouseClick(object sender, MouseEventArgs e)
      {
         int index = Array.IndexOf(m_waveSelectCheckBox, sender);
         CheckBox currentcheckedBox = (CheckBox)sender;
         if (currentcheckedBox.Checked)
         {
            if (index < 3)
            {
               for (int i = 0; i < 3; i++)
               {
                  m_waveSelectCheckBox[i].Checked = false;
                  m_waveSelectCheckBox[i].BackgroundImage = imageList.Images[i];
               }
               m_waveSelectCheckBox[index].BackgroundImage = imageList.Images[index + 3];
               double.TryParse(textBox_highLevelA.Text, out m_highLevelA);
               double.TryParse(textBox_lowLevelA.Text, out m_lowLevelA);
               m_isCheckedA = true;
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

      private void button_start_Click(object sender, EventArgs e)
      {
         if (m_isCheckedA == false && m_isCheckedB == false)
         {
            MessageBox.Show("Please select a waveform !");
            return;
         }
         //prepare the AO
         m_err = m_bufferedAoCtrl.Prepare();
         CheckError(m_err);
         //generator the wave
         double.TryParse(textBox_highLevelA.Text, out m_highLevelA);
         double.TryParse(textBox_lowLevelA.Text, out m_lowLevelA);
         double.TryParse(textBox_highLevelB.Text, out m_highLevelB);
         double.TryParse(textBox_lowLevelB.Text, out m_lowLevelB);
         WaveformStyle[] styles = new WaveformStyle[] { m_formStyleA, m_formStyleB };
         double[] highLevels = new double[] { m_highLevelA, m_highLevelB };
         double[] lowLevels = new double[] { m_lowLevelA, m_lowLevelB };

         m_PointCountPerWave = (uint)m_bufferedAoCtrl.ScanChannel.Samples;
         m_waveformGenerator = new WaveformGenerator(m_PointCountPerWave);
         m_dataScaled = new double[m_bufferedAoCtrl.ScanChannel.ChannelCount * m_PointCountPerWave];

         if (m_bufferedAoCtrl.ScanChannel.ChannelCount <= 1)
         {
            m_waveformGenerator.GetOnePeriod(m_dataScaled, m_formStyleA, m_highLevelA, m_lowLevelA);
         }
         else
         {
            if (m_isCheckedA == true && m_isCheckedB == false)
            {
               styles[0] = m_formStyleA;
               highLevels[0] = m_highLevelA;
               highLevels[1] = 0;
               lowLevels[0] = m_lowLevelA;
               lowLevels[1] = 0;
            }
            else if (m_isCheckedB == true && m_isCheckedA == false)
            {
               styles[1] = m_formStyleB;
               highLevels[0] = 0;
               highLevels[1] = m_highLevelB;
               lowLevels[0] = 0;
               lowLevels[1] = m_lowLevelB;
            }
            else if (m_isCheckedB == false && m_isCheckedA == false)
            {
               highLevels[0] = 0;
               highLevels[1] = 0;
               lowLevels[0] = 0;
               lowLevels[1] = 0;
            }
            m_waveformGenerator.GetMultipleWaveform(m_dataScaled, 2, styles, highLevels, lowLevels);
         }

         // Convert scaled  data to raw data
         int chanCount = m_bufferedAoCtrl.ScanChannel.ChannelCount;
         m_err = m_bufferedAoCtrl.SetData((int)(chanCount * m_PointCountPerWave), m_dataScaled);
         CheckError(m_err);
         // Start buffered AO in asynchronous
         m_err = m_bufferedAoCtrl.Start();
         CheckError(m_err);
         button_start.Enabled = false;
      }

      private void m_bufferedAoCtrl_Stopped(object sender, BfdAoEventArgs e)
      {
         if (!formCloseFlag)
         {
            Invoke(new MethodInvoker(delegate{
               button_start.Enabled = true;
            } ));
         }
      }

      private void AsyncOneWaveOutAoForm_FormClosed(object sender, FormClosedEventArgs e)
      {
         formCloseFlag = true;
      }
   }
}