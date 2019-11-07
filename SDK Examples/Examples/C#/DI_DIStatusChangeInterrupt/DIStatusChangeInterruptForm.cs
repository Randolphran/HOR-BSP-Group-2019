using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Automation.BDaq;


namespace DI_DIStatusChangeInterrupt
{
   public partial class DIStatusChangeInterruptForm : Form
   {
      protected delegate void UpdateListview(int portNum, byte[] portData);
      int m_changedNum = 0;

      public DIStatusChangeInterruptForm()
      {
         InitializeComponent();
      }

      public DIStatusChangeInterruptForm(int deviceNumber)
      {
          InitializeComponent();
          instantDiCtrl1.SelectedDevice = new DeviceInformation(deviceNumber);
      }

      private void StatusChangeForm_Load(object sender, EventArgs e)
      {
         //DI status change interrupt need to be enabled, please use Wizard to enable it.
         //The default device of project is demo device, users can choose other devices according to their needs. 
         if (!instantDiCtrl1.Initialized)
         {
            MessageBox.Show("No device be selected or device open failed!", "DIStatusChangeInterrupt");
            this.Close();
            return;
         }

         this.Text = "DI Status Change Interrupt(" + instantDiCtrl1.SelectedDevice.Description + ")";

         // change the columnHeader2.Width according the portCount
         this.columnHeader2.Text = "DI ports value (Port 0~" + (instantDiCtrl1.Features.PortCount - 1) + ")";
         if (instantDiCtrl1.Features.PortCount > 10)
         {
            columnHeader2.Width = 211 + 22 * (instantDiCtrl1.Features.PortCount - 10);
            listViewForData.Height = 240;
         }
         else
         {
            columnHeader2.Width = 211;
            listViewForData.Height = 225;
         }
         buttonStop.Enabled = false;
         ExecutionStatus.Enabled = false;
      }

      private void listView1_DrawColumnHeader(object sender, DrawListViewColumnHeaderEventArgs e)
      {
         e.DrawBackground();
         e.DrawText();
      }

      private void buttonStart_Click(object sender, EventArgs e)
      {
         ErrorCode err = ErrorCode.Success;

         listViewForData.Items.Clear();
         m_changedNum = 0;
         err = instantDiCtrl1.SnapStart();
         if (err != ErrorCode.Success)
         {
            HandleError(err);
            return;
         }

         buttonStop.Enabled = true;
         buttonStart.Enabled = false;
         ExecutionStatus.Enabled = true;
      }

      private void UpdateListviewMethod(int portNum, byte[] portData)
      {
         if (listViewForData.Items.Count > 10)
         {
            listViewForData.Items[0].Remove();
         }

         listViewForData.Items.Add("");

         // column 0
         listViewForData.Items[listViewForData.Items.Count - 1].SubItems.Add("");
         listViewForData.Items[listViewForData.Items.Count - 1].SubItems[0].Tag = ++m_changedNum;

         // column 1
         listViewForData.Items[listViewForData.Items.Count - 1].SubItems.Add("");

         string valueString = null;
         for (int j = 0; j < portData.Length; j++)
         {
            valueString += portData[j].ToString("X2");
            if (j < portData.Length - 1)
            {
               valueString += ", ";
            }
         }
         listViewForData.Items[listViewForData.Items.Count - 1].SubItems[1].Tag = valueString;
      }

      private void buttonStop_Click(object sender, EventArgs e)
      {
         ErrorCode err = ErrorCode.Success;

         err = instantDiCtrl1.SnapStop();

         buttonStart.Enabled = true;
         buttonStop.Enabled = false;
         ExecutionStatus.Enabled = false;
      }

      private void listViewForData_DrawSubItem(object sender, DrawListViewSubItemEventArgs e)
      {
         switch (e.Header.Index)
         {
            case 0:// StatusChange number
               e.Graphics.DrawString(e.SubItem.Tag.ToString(), this.Font, new SolidBrush(Color.Black), new Point(e.Bounds.X + 35, e.Bounds.Y + 5));
               break;
            default:// port value
               e.Graphics.DrawString(e.SubItem.Tag.ToString(), this.Font, new SolidBrush(Color.Black), new Point(e.Bounds.X, e.Bounds.Y + 5));
               break;
         }
      }

      private void HandleError(ErrorCode err)
      {
         if ((err >= ErrorCode.ErrorHandleNotValid) && (err != ErrorCode.Success))
         {
            MessageBox.Show("Sorry ! Some errors happened, the error code is: " + err.ToString(), "DI_StatusChange");
         }
      }

      private void instantDiCtrl1_ChangeOfState(object sender, DiSnapEventArgs e)
      {
         try
         {
            Invoke(new UpdateListview(UpdateListviewMethod), new object[] { e.SrcNum, e.PortData });
         }
         catch (System.Exception) { } 
      }
   }

}