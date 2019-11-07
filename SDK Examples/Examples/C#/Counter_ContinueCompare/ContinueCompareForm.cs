using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using Automation.BDaq;

namespace Counter_ContinueCompare
{
    enum TabSel
    {
        dispersed = 0,
        lined
    };

    public struct LineTabParam
    {
        public int firstValue;
        public int increment;
        public int count;
    };

    public partial class ContinueCompareForm : Form
    {
        int m_tabIndex;
        TabSel m_contCompTabSel;

        int matchCount;
		int endCount;
		int[] comTable = new int[3];
		LineTabParam lineTabparam;
		EventId[] evntEndID = new EventId[8];
		EventId[] evntMatchID = new EventId[8];
		bool matched;

        protected delegate void UdCntrEvent(int matchCount, int endCount);

        public ContinueCompareForm()
        {
            InitializeComponent();
        }

        public ContinueCompareForm(int deviceNumber)
        {
            InitializeComponent();
            udCounterCtrl1.SelectedDevice = new DeviceInformation(deviceNumber);
        }

        private void ContinueCompareForm_Load(object sender, EventArgs e)
        {
            if (!udCounterCtrl1.Initialized)
            {
                MessageBox.Show("No device be selected or device open failed!", "ContinueCompare");
                this.Close();
                return;
            }

            //set the title
            this.Text = "Continue Compare(" + udCounterCtrl1.SelectedDevice.Description + ")";

            m_tabIndex = 0;

            matchCount = 0;
            endCount = 0;
            matched = false;
            for (int i = 0; i < 8; ++i)
            {
                evntEndID[i] = EventId.EvtCntCompareTableEnd0 + i;
                evntMatchID[i] = EventId.EvtCntPatternMatch0 + i;
            }

            //initialize the compare table
            txtTab1Data0.Text = "100";
            txtTab1Data1.Text = "340";
            txtTab1Data2.Text = "720";
            txtTab2Data0.Text = "1000";
            txtTab2Data1.Text = "1980";
            txtTab2Data2.Text = "2510";

            txtInt1FirstValue.Text = "150";
            txtInt1Increment.Text = "3";
            txtInt1Count.Text = "3";
            txtInt2FirstValue.Text = "210";
            txtInt2Increment.Text = "3";
            txtInt2Count.Text = "3";

            btnStart.Enabled = true;
            btnStop.Enabled = false;
        }

        public void EnableCompareTable(bool enabled)
        {
            radTable.Enabled = enabled;
            txtTab1Data0.Enabled = enabled;
            txtTab1Data1.Enabled = enabled;
            txtTab1Data2.Enabled = enabled;
            txtTab2Data0.Enabled = enabled;
            txtTab2Data1.Enabled = enabled;
            txtTab2Data2.Enabled = enabled;

            radInterval.Enabled = enabled;
            txtInt1FirstValue.Enabled = enabled;
            txtInt1Increment.Enabled = enabled;
            txtInt1Count.Enabled = enabled;
            txtInt2FirstValue.Enabled = enabled;
            txtInt2Increment.Enabled = enabled;
            txtInt2Count.Enabled = enabled;
        }

        protected void DataHandler(int matchCount, int endCount) 
        {
            txtPMCount.Text = matchCount.ToString();
            txtEndCount.Text = endCount.ToString();
        }

        private void HandleError(Exception err)
        {
            MessageBox.Show("Sorry ! Some errors happened, the error code is: " + err.ToString(), "Warning Information");
        }

        public void CreateDisperseTable(int tabIndex, int[] CompTab) 
        {
            if (tabIndex == 0)
            {
                CompTab[0] = int.Parse(txtTab1Data0.Text);
                CompTab[1] = int.Parse(txtTab1Data1.Text);
                CompTab[2] = int.Parse(txtTab1Data2.Text);
            } 
            else 
            {
                CompTab[0] = int.Parse(txtTab2Data0.Text);
                CompTab[1] = int.Parse(txtTab2Data1.Text);
                CompTab[2] = int.Parse(txtTab2Data2.Text);
            }
        }

        public void CreateLineTable(int tabIndex, ref LineTabParam param)
        {
            if (tabIndex == 0)
            {
                param.firstValue = int.Parse(txtInt1FirstValue.Text);
                param.increment = int.Parse(txtInt1Increment.Text);
                param.count = int.Parse(txtInt1Count.Text);
            }
            else
            {
                param.firstValue = int.Parse(txtInt2FirstValue.Text);
                param.increment = int.Parse(txtInt2Increment.Text);
                param.count = int.Parse(txtInt2Count.Text);
            }  
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            try
            {
					int value = 0; 
					udCounterCtrl1.Enabled = true;
					udCounterCtrl1.Read(out value);
               txtCounterValue.Text = "0x" + value.ToString("X2");
            }
            catch (Exception ex)
            {
                HandleError(ex);	
            }
        }

        public bool isNum(string str)
        {
            bool num;
            if (str != null && Regex.IsMatch(str, @"^\d+$"))
            {
                num = true;
            }
            else
            {
                num = false;
            }
            return num;
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            //Set compare table
            int[] ComTable = new int[] { 0, 0, 0 };
            LineTabParam param = new LineTabParam();

            if (radTable.Checked)
            {
                m_contCompTabSel = TabSel.dispersed;
            }
            else
            {
                m_contCompTabSel = TabSel.lined;
            }

            try
            {
                if (TabSel.dispersed == m_contCompTabSel)
                {

                    CreateDisperseTable(0, ComTable);
						  udCounterCtrl1.CompareSetTable(udCounterCtrl1.ChannelStart, 3, ComTable);

                    //check the table2.
                    int[] ComTable2 = new int[] { 0, 0, 0 };
                    CreateDisperseTable(1, ComTable2);
                }
                else
                {
                    CreateLineTable(0, ref param);
						  udCounterCtrl1.CompareSetInterval(udCounterCtrl1.ChannelStart, param.firstValue, param.increment, param.count);

                    //check the interval2.
                    LineTabParam param2 = new LineTabParam();
                    CreateLineTable(1, ref param2);
                }
            }
            catch (System.Exception ex)
            {
                HandleError(ex);

                if (!isNum(txtTab1Data0.Text)) txtTab1Data0.Text = "";
                if (!isNum(txtTab1Data1.Text)) txtTab1Data1.Text = "";
                if (!isNum(txtTab1Data2.Text)) txtTab1Data2.Text = "";
                if (!isNum(txtTab2Data0.Text)) txtTab2Data0.Text = "";
                if (!isNum(txtTab2Data1.Text)) txtTab2Data1.Text = "";
                if (!isNum(txtTab2Data2.Text)) txtTab2Data2.Text = "";

                if (!isNum(txtInt1FirstValue.Text)) txtInt1FirstValue.Text = "";
                if (!isNum(txtInt1Increment.Text)) txtInt1Increment.Text = "";
                if (!isNum(txtInt1Count.Text)) txtInt1Count.Text = "";
                if (!isNum(txtInt2FirstValue.Text)) txtInt2FirstValue.Text = "";
                if (!isNum(txtInt2Increment.Text)) txtInt2Increment.Text = "";
                if (!isNum(txtInt2Count.Text)) txtInt2Count.Text = "";

                return;
            }
            finally
            {
                if (!isNum(txtTab1Data0.Text)) txtTab1Data0.Text = "";
                if (!isNum(txtTab1Data1.Text)) txtTab1Data1.Text = "";
                if (!isNum(txtTab1Data2.Text)) txtTab1Data2.Text = "";
                if (!isNum(txtTab2Data0.Text)) txtTab2Data0.Text = "";
                if (!isNum(txtTab2Data1.Text)) txtTab2Data1.Text = "";
                if (!isNum(txtTab2Data2.Text)) txtTab2Data2.Text = "";

                if (!isNum(txtInt1FirstValue.Text)) txtInt1FirstValue.Text = "";
                if (!isNum(txtInt1Increment.Text)) txtInt1Increment.Text = "";
                if (!isNum(txtInt1Count.Text)) txtInt1Count.Text = "";
                if (!isNum(txtInt2FirstValue.Text)) txtInt2FirstValue.Text = "";
                if (!isNum(txtInt2Increment.Text)) txtInt2Increment.Text = "";
                if (!isNum(txtInt2Count.Text)) txtInt2Count.Text = "";
            }

            matchCount = 0;
            endCount = 0;
            m_tabIndex = 0;

            //Start Snap Counter function.
            try
            {
                udCounterCtrl1.Enabled = true;
            }
            catch (System.Exception ex)
            {
                HandleError(ex);
            }

            timer1.Enabled = true;

            btnStart.Enabled = false;
            btnStop.Enabled = true;

            EnableCompareTable(false);

            txtPMCount.Text = "0";
            txtEndCount.Text = "0";
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            //Stop the user Timer
            timer1.Enabled = false;

            btnStart.Enabled = true;
            btnStop.Enabled = false;

            EnableCompareTable(true);

            try
            {
                udCounterCtrl1.Enabled = false;
            }
            catch (System.Exception ex)
            {
                HandleError(ex);
            }
        }

        private void udCounterCtrl1_UdCntrEvent(object sender, UdCntrEventArgs e)
        {
            //refresh the snap value list
            UdCounterCtrl udCounterCtrl = (UdCounterCtrl)sender;

            if (evntEndID[udCounterCtrl.ChannelStart] == e.Id)
            {
                endCount++;
                m_tabIndex++;
                if (m_contCompTabSel == TabSel.dispersed)
                {
                    CreateDisperseTable(m_tabIndex % 2, comTable);
                    udCounterCtrl.CompareSetTable(udCounterCtrl.ChannelStart, 3, comTable);
                }
                else
                {
                    CreateLineTable(m_tabIndex % 2, ref lineTabparam);
                    udCounterCtrl.CompareSetInterval(udCounterCtrl.ChannelStart, lineTabparam.firstValue, lineTabparam.increment, lineTabparam.count);
                }
                matched = true;
            }
            else if (evntMatchID[udCounterCtrl.ChannelStart] == e.Id)
            {
                ++matchCount;
                matched = true;
            }
            if (matched)
            {
                try
                {
                    Invoke(new UdCntrEvent(DataHandler), new object[] { matchCount, endCount });
                }
                catch (System.Exception ex)
                {
                    HandleError(ex);
                }

                matched = false;
            }
        }
    }
}