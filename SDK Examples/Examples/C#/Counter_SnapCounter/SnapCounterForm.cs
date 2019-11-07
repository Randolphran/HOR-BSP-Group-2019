using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using Automation.BDaq;

namespace Counter_SnapCounter
{
    public partial class SnapCounterForm : Form
    {
		  bool m_isTimerUsing;
        int snapCount = 0;

        TimerPulseCtrl timerPulseCtrl1;

        int[] snapSrcs = {0};
		  EventId[] eventId = {0};
        ListBox.SelectedIndexCollection selectedItems;

        protected delegate void UdCntrEvent(int snapCount, UdCntrEventArgs e);
        
        public SnapCounterForm()
        {
            InitializeComponent();
            timerPulseCtrl1 = new TimerPulseCtrl();
        }

        public SnapCounterForm(int deviceNumber)
        {
            InitializeComponent();
            udCounterCtrl1.SelectedDevice = new DeviceInformation(deviceNumber);
            timerPulseCtrl1 = new TimerPulseCtrl();
        }

        protected void DataHandler(int snapCount, UdCntrEventArgs e)
        {
            if (CounterValueList.Items.Count > 40)
            {
                CounterValueList.Items.RemoveAt(0);
            }

            string snapValue;
            string srcID = "";
            string source;

            txtSnapCount.Text = snapCount.ToString();

            EventIDtoString((EventId)e.Id, ref srcID);

            snapValue = "CntrValue: ";
            for (int i = 0; i < e.Length; i++)
            {
                snapValue += e.Data[i].ToString("X");
                snapValue += " ";
            }
            CounterValueList.Items.Add(snapValue);

            source = "SrcID: ";
            source += srcID;
            CounterValueList.Items.Add(source);
        }

        private void SnapCounterForm_Load(object sender, EventArgs e)
        {
            if (!udCounterCtrl1.Initialized)
            {
                MessageBox.Show("No device be selected or device open failed!", "ContinueCompare");
                this.Close();
                return;
            }

            //set the title
            this.Text = "Snap Counter(" + udCounterCtrl1.SelectedDevice.Description + ")";

            selectedItems = listSnapSource.SelectedIndices;

            txtTimeInterval.Text = "5";
            CounterValueList.Items.Clear();
            m_isTimerUsing = false;

            ConfiguratePanel();

            btnStart.Enabled = true;
            btnStop.Enabled = false;
        }

        public void ConfiguratePanel()
        {
            //for reset value
            snapSrcs = udCounterCtrl1.Features.SnapEventSources;
				eventId = udCounterCtrl1.Features.UdSnapEventSources;
            int count = snapSrcs.Length;
            string str = "";

            for (int i = 0; i < count; i++)
            {
                EventIDtoString((EventId)snapSrcs[i], ref str);
                listSnapSource.Items.Add(str);
            }
        }

        private void HandleError(Exception err)
        {
            MessageBox.Show("Sorry ! Some errors happened, the error code is: " + err.ToString(), "Warning Information");
        }

        public void EventIDtoString(EventId id, ref string str)
        {
            switch (id)
            {
                case EventId.EvtUdIndex0:
                    str = "Index0";
                    break;
                case EventId.EvtUdIndex1:
                    str = "Index1";
                    break;
                case EventId.EvtUdIndex2:
                    str = "Index2";
                    break;
                case EventId.EvtUdIndex3:
                    str = "Index3";
                    break;
                case EventId.EvtUdIndex4:
                    str = "Index4";
                    break;
                case EventId.EvtUdIndex5:
                    str = "Index5";
                    break;
                case EventId.EvtUdIndex6:
                    str = "Index6";
                    break;
                case EventId.EvtUdIndex7:
                    str = "Index7";
                    break;
                case EventId.EvtCntTimer0:
                    str = "Timer0";
                    break;
                case EventId.EvtCntTimer1:
                    str = "Timer1";
                    break;
                case EventId.EvtCntTimer2:
                    str = "Timer2";
                    break;
                case EventId.EvtCntTimer3:
                    str = "Timer3";
                    break;
                case EventId.EvtCntTimer4:
                    str = "Timer4";
                    break;
                case EventId.EvtCntTimer5:
                    str = "Timer5";
                    break;
                case EventId.EvtCntTimer6:
                    str = "Timer6";
                    break;
                case EventId.EvtCntTimer7:
                    str = "Timer7";
                    break;
                case EventId.EvtDiintChannel000:
                    str = "DiintChannel0";
                    break;
                case EventId.EvtDiintChannel001:
                    str = "DiintChannel1";
                    break;
                case EventId.EvtDiintChannel002:
                    str = "DiintChannel2";
                    break;
                case EventId.EvtDiintChannel003:
                    str = "DiintChannel3";
                    break;
                case EventId.EvtDiintChannel004:
                    str = "DiintChannel4";
                    break;
                case EventId.EvtDiintChannel005:
                    str = "DiintChannel5";
                    break;
                case EventId.EvtDiintChannel006:
                    str = "DiintChannel6";
                    break;
                case EventId.EvtDiintChannel007:
                    str = "DiintChannel7";
                    break;
                case EventId.EvtDiCosintPort000:
                    str = "DiConsintChannel0";
                    break;
                case EventId.EvtDiCosintPort001:
                    str = "DiConsintChannel1";
                    break;
                case EventId.EvtDiCosintPort002:
                    str = "DiConsintChannel2";
                    break;
                case EventId.EvtDiCosintPort003:
                    str = "DiConsintChannel3";
                    break;
                case EventId.EvtDiPmintPort000:
                    str = "DiPmintChannel0";
                    break;
                case EventId.EvtDiPmintPort001:
                    str = "DiPmintChannel1";
                    break;
                case EventId.EvtDiPmintPort002:
                    str = "DiPmintChannel2";
                    break;
                case EventId.EvtDiPmintPort003:
                    str = "DiPmintChannel3";
                    break;

                default:
                    str = "";
                    break;
            }    
        }

        public void CheckTimerUsingParam(EventId id, ref int timerChan, ref bool isTimerUsing)
        {
            if (id >= EventId.EvtCntTimer0 && id <= EventId.EvtCntTimer7)
            {
                timerChan = id - EventId.EvtCntTimer0;
            }

            if (timerChan != -1)
            {
                isTimerUsing = true;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
			  int value = 0; 
			  try
            {
                //txtCounterValue.Text = ((uint)udCounterCtrl1.Value).ToString();
					 udCounterCtrl1.Read(out value);
					 txtCounterValue.Text = value.ToString();
            }
            catch (Exception ex)
            {
                HandleError(ex);
            }
        }

        private void listSnapSource_SelectedIndexChanged(object sender, EventArgs e)
        {
            selectedItems = listSnapSource.SelectedIndices;

            int timerChan = -1;
            bool isTimerUsing = false;

            if (selectedItems.Count != 0)
            {
                foreach (int index in selectedItems)
                {
                    CheckTimerUsingParam((EventId)snapSrcs[index], ref timerChan, ref isTimerUsing);
                    if (isTimerUsing)
                    {
                        txtTimeInterval.Enabled = true;
                        break;
                    }
                    else
                    {
                        txtTimeInterval.Enabled = false;
                    }
                }
            }
            else
            {
                txtTimeInterval.Enabled = false;
            }
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;

            btnStart.Enabled = true;
            btnStop.Enabled = false;
            listSnapSource.Enabled = true;

            //stop timer pulse
            if (m_isTimerUsing)
            {
                timerPulseCtrl1.Enabled = false;
                timerPulseCtrl1.Dispose();
            }

            //stop snap function
            foreach (int index in selectedItems)
            {
                //udCounterCtrl1.SnapStop(snapSrcs[index]);
					 udCounterCtrl1.SnapStop(eventId[index]);
            }

            try
            {
                //stop updown counter
                udCounterCtrl1.Enabled = false;
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
            CounterValueList.Items.Clear();
            txtCounterValue.Text = "0";
            txtSnapCount.Text = "0";
            snapCount = 0;

            m_isTimerUsing = false;
            int timerChan = -1;
            foreach (int index in selectedItems)
            {
                CheckTimerUsingParam((EventId)snapSrcs[index], ref timerChan, ref m_isTimerUsing);
                //udCounterCtrl1.SnapStart(snapSrcs[index]);
					 udCounterCtrl1.SnapStart(eventId[index]);
            }
            
            try
            {
                if (m_isTimerUsing)
                {
                    int deviceNumber = udCounterCtrl1.SelectedDevice.DeviceNumber;
                    DeviceInformation selectedDevice = new DeviceInformation(deviceNumber);
                    timerPulseCtrl1.SelectedDevice = selectedDevice;
                    double frequency = double.Parse(txtTimeInterval.Text);
                    timerPulseCtrl1.ChannelStart = timerChan;
                    //timerPulseCtrl1.Frequency = frequency;
						  
						  TmrChannel[] tmrChannel = timerPulseCtrl1.Channels;
						  tmrChannel[0].Frequency = frequency;
                    timerPulseCtrl1.Enabled = true;
                }
                
                //Start Snap Counter function.
                udCounterCtrl1.Enabled = true;
            }
            catch (Exception ex)
            {
                HandleError(ex);

                if (!isNum(txtTimeInterval.Text)) txtTimeInterval.Text = "";

                //stop snap function
                foreach (int index in selectedItems)
                {
                    //udCounterCtrl1.SnapStop(snapSrcs[index]);
						  udCounterCtrl1.SnapStop(eventId[index]);
                }

                return;
            }

            timer1.Enabled = true;

            btnStart.Enabled = false;
            btnStop.Enabled = true;
            listSnapSource.Enabled = false;
        }

        private void udCounterCtrl1_UdCntrEvent(object sender, UdCntrEventArgs e)
        {
            snapCount++;

            Invoke(new UdCntrEvent(DataHandler), new object[] { snapCount, e });
        }
    }
}