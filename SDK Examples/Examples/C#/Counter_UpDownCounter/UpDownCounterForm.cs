using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Automation.BDaq;

namespace Counter_UpDownCounter
{
    public partial class UpDownCounterForm : Form
    {
        int cntrValue = 0;
        
        public UpDownCounterForm()
        {
            InitializeComponent();
        }

        public UpDownCounterForm(int deviceNumber)
        {
            InitializeComponent();
            udCounterCtrl1.SelectedDevice = new DeviceInformation(deviceNumber);
        }

        private void UpDownCounterForm_Load(object sender, EventArgs e)
        {   
            if (!udCounterCtrl1.Initialized)
            {
                MessageBox.Show("No device be selected or device open failed!", "UpDownCounter");
                this.Close();
                return;
            }

            //set the title
            this.Text = "UpDown Counter(" + udCounterCtrl1.SelectedDevice.Description + ")";

            CounterValueList.Items.Clear();

            ConfiguratePanel();

            btnStart.Enabled = true;
            btnStop.Enabled = false;
            btnValReset.Enabled = false;
        }

        public void ConfiguratePanel()
        {
            cmbResetValue.Items.Clear();
				UdChannel[] udChannel = udCounterCtrl1.Channels;

            // for reset value
            int[] resetValues = udCounterCtrl1.Features.UdInitialValues;
            int count = resetValues.Length;

            int i = 0;
            for (; i < count; i++)
            {
                if (resetValues[i] != -1)
                {
                    string str = resetValues[i].ToString("X");
                    int length = str.Length;
                    if (length > 8)
                    {
                        cmbResetValue.Items.Add("0x" + str.Substring(length - 8, 8));
                    }
                    else
                    {
                        cmbResetValue.Items.Add("0x" + str);
                    }
                }
                else
                {
                    cmbResetValue.Items.Add("-1");
                }
            }

				int resetValue = udChannel[udCounterCtrl1.ChannelStart].InitialValue;
            if (i != 0)
            {
                if (0 == resetValue)
                {
                    cmbResetValue.SelectedIndex = 0;
                }
                else
                {
                    cmbResetValue.SelectedIndex = 1;
                }
                
            }

            //for using edit text as reset value
            txtResetValue.Text = "0";

            //reset times
            txtResetTimes.Text = "0";
            txtResetTimes.Enabled = false;

            //radio button for reset value.
				int resetTimesByIndex = udChannel[udCounterCtrl1.ChannelStart].ResetTimesByIndex;
            if (0 == resetTimesByIndex)
            {
                radDisable.Checked = true;
                radFinite.Checked = false;
                raInfinite.Checked = false;
            }
            else if (-1 == resetTimesByIndex)
            {
                radDisable.Checked = false;
                radFinite.Checked = false;
                raInfinite.Checked = true;
            }
            else
            {
                radDisable.Checked = false;
                radFinite.Checked = true;
                raInfinite.Checked = false;

                txtResetTimes.Text = resetTimesByIndex.ToString();
                txtResetTimes.Enabled = true;
            }
        }

        private void HandleError(Exception err)
        {
            MessageBox.Show("Sorry ! Some errors happened, the error code is: " + err.ToString(), "Warning Information");
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            try
            {
                udCounterCtrl1.Enabled = true;
            }
            catch (System.Exception ex)
            {
                HandleError(ex);
            }

				udCounterCtrl1.Read(out cntrValue);
            txtCounterValue.Text = ((uint)cntrValue).ToString();
        }

        private void btnValReset_Click(object sender, EventArgs e)
        {
            udCounterCtrl1.ValueReset();
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            //Stop the user Timer
            timer1.Enabled = false;

            btnStart.Text = "Start";
            btnStop.Enabled = false;
            btnValReset.Enabled = false;

            cmbResetValue.Enabled = true;
            radDisable.Enabled = true;
            raInfinite.Enabled = true;
            radFinite.Enabled = true;

            try
            {
                udCounterCtrl1.Enabled = false;
            }
            catch (System.Exception ex)
            {
                HandleError(ex);
            }
        }

        private void radDisable_Click(object sender, EventArgs e)
        {
            if (radDisable.Checked)
            {
                txtResetTimes.Enabled = false;
            }
        }

        private void raInfinite_Click(object sender, EventArgs e)
        {
            if (raInfinite.Checked)
            {
                txtResetTimes.Enabled = false;
            }
        }

        private void radFinite_Click(object sender, EventArgs e)
        {
            if (radFinite.Checked)
            {
                txtResetTimes.Enabled = true;
					UdChannel[] udChannel = udCounterCtrl1.Channels;
					txtResetTimes.Text = udChannel[udCounterCtrl1.ChannelStart].ResetTimesByIndex.ToString();

            }
        }

        private void cmbResetValue_SelectedIndexChanged(object sender, EventArgs e)
        {
            int[] resetValues = udCounterCtrl1.Features.UdInitialValues;
            int resetValue = resetValues[cmbResetValue.SelectedIndex];

            if (resetValue == -1)
            {
                txtResetValue.Enabled = true;
            } 
            else
            {
                txtResetValue.Enabled = false;
            }
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            if (btnStart.Text == "Start")
            {
                CounterValueList.Items.Clear();

                //Set reset times for counter value
                int resetTimes = 0;

                if (radFinite.Checked)
                {
                    try
                    {
                        resetTimes = int.Parse(txtResetTimes.Text);
                    }
                    catch (Exception ex)
                    {
                        HandleError(ex);
                        txtResetTimes.Text = "";
                        return;
                    }
                }
                else if (raInfinite.Checked)
                {
                    resetTimes = -1;
                } 
                else
                {
                    resetTimes = 0;
                }

                //udCounterCtrl1.ResetTimesByIndex = resetTimes;
					 UdChannel[] udChannel = udCounterCtrl1.Channels;
					 udChannel[udCounterCtrl1.ChannelStart].ResetTimesByIndex = resetTimes;

                //set reset value
                int[] resetValues = udCounterCtrl1.Features.UdInitialValues;
                int resetValue = resetValues[cmbResetValue.SelectedIndex];

                if (resetValue == -1)
                {
                    try
                    {
                        resetValue = int.Parse(txtResetValue.Text);
                    }
                    catch (Exception ex)
                    {
                        HandleError(ex);
                        txtResetValue.Text = "";
                        return;
                    }
                }
					 udChannel[udCounterCtrl1.ChannelStart].InitialValue = resetValue;

                //Start UpDown Counter function.
                try
                {
                    udCounterCtrl1.Enabled = true;
                }
                catch (System.Exception ex)
                {
                    HandleError(ex);
                }

                timer1.Enabled = true;

                btnStart.Text = "Latch";
                btnStop.Enabled = true;
                btnValReset.Enabled = true;

                cmbResetValue.Enabled = false;
                radDisable.Enabled = false;
                raInfinite.Enabled = false;
                radFinite.Enabled = false;
            }
            else
            {
                if (CounterValueList.Items.Count > 12)
                {
                    CounterValueList.Items.RemoveAt(0);
                }

                CounterValueList.Items.Add(txtCounterValue.Text);
            }
        }
    }
}