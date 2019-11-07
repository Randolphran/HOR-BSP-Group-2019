using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using System.Globalization;
using Automation.BDaq;


namespace DO_StaticDO
{
   public partial class StaticDOForm : Form
   {
      #region
      private Label[] m_portNum;
      private Label[] m_portHex;
      private PictureBox[,] m_pictrueBox;
      
      #endregion

      public StaticDOForm()
      {
         InitializeComponent();
      }

      public StaticDOForm(int deviceNumber)
      {
         InitializeComponent();
         instantDoCtrl1.SelectedDevice = new DeviceInformation(deviceNumber);
      }

      private void StaticDOForm_Load(object sender, EventArgs e)
      {
         //The default device of project is demo device, users can choose other devices according to their needs. 
         if (!instantDoCtrl1.Initialized)
         {
            MessageBox.Show("No device be selected or device open failed!", "StaticDO");
            this.Close();
            return;
         }

         this.Text = "Static DO(" + instantDoCtrl1.SelectedDevice.Description + ")";

         m_portNum = new Label[ConstVal.PortCountShow] { PortNum0, PortNum1, PortNum2, PortNum3 };
         m_portHex = new Label[ConstVal.PortCountShow] { PortHex0, PortHex1, PortHex2, PortHex3 };
         m_pictrueBox = new PictureBox[ConstVal.PortCountShow, 8]{
             {pictureBox00, pictureBox01, pictureBox02, pictureBox03, pictureBox04, pictureBox05,pictureBox06, pictureBox07},
             {pictureBox10, pictureBox11, pictureBox12, pictureBox13, pictureBox14, pictureBox15,pictureBox16, pictureBox17},
             {pictureBox20, pictureBox21, pictureBox22, pictureBox23, pictureBox24, pictureBox25,pictureBox26, pictureBox27},
             {pictureBox30, pictureBox31, pictureBox32, pictureBox33, pictureBox34, pictureBox35,pictureBox36, pictureBox37}
          };

         InitializePortState();
      }

      private void InitializePortState()
      {
         byte portData = 0;
         byte portDir = 0xFF;
         ErrorCode err = ErrorCode.Success;
			byte[] mask = instantDoCtrl1.Features.DoDataMask;
         for (int i = 0; (i + ConstVal.StartPort) < instantDoCtrl1.Features.PortCount && i < ConstVal.PortCountShow; ++i)
         {
            err = instantDoCtrl1.Read(i + ConstVal.StartPort, out portData);
            if (err != ErrorCode.Success)
            {
               HandleError(err);
               return;
            }

            m_portNum[i].Text = (i + ConstVal.StartPort).ToString();
            m_portHex[i].Text = portData.ToString("X2");
				
				if (instantDoCtrl1.Ports != null)
				{
					portDir = (byte)instantDoCtrl1.Ports[i + ConstVal.StartPort].Direction;
				}
            
            // Set picture box state
            for (int j = 0; j < 8; ++j)
            {
               if (((portDir >> j) & 0x1) == 0 || ((mask[i] >> j) & 0x1) == 0)  // Bit direction is input.
               {
                  m_pictrueBox[i, j].Image = imageList1.Images[2];
                  m_pictrueBox[i, j].Enabled = false;
               }
               else
               {
                  m_pictrueBox[i, j].Click += new EventHandler(PictureBox_Click);
                  m_pictrueBox[i, j].Tag = new DoBitInformation((portData >> j) & 0x1, i + ConstVal.StartPort, j);
                  m_pictrueBox[i, j].Image = imageList1.Images[(portData >> j) & 0x1];
               }               
               m_pictrueBox[i, j].Invalidate();
            }
         }
      }

      private void HandleError(ErrorCode err)
      {
         if ((err >= ErrorCode.ErrorHandleNotValid) && (err != ErrorCode.Success))
         {
            MessageBox.Show("Sorry ! Some errors happened, the error code is: " + err.ToString());
         }
      }

      private void PictureBox_Click(object sender, EventArgs e)
      {
         ErrorCode err = ErrorCode.Success;
         PictureBox box = (PictureBox)sender;
         DoBitInformation boxInfo = (DoBitInformation)box.Tag;

         boxInfo.BitValue = (~(int)(boxInfo).BitValue) & 0x1;
         box.Tag = boxInfo;
         box.Image = imageList1.Images[boxInfo.BitValue];
         box.Invalidate();
        
         // refresh hex
         int state = Int32.Parse(m_portHex[boxInfo.PortNum - ConstVal.StartPort].Text, NumberStyles.AllowHexSpecifier);
         state &= ~(0x1 << boxInfo.BitNum); 
         state |= boxInfo.BitValue << boxInfo.BitNum;

         m_portHex[boxInfo.PortNum - ConstVal.StartPort].Text = state.ToString("X2");
         err = instantDoCtrl1.Write(boxInfo.PortNum, (byte)state);
         if (err != ErrorCode.Success)
         {
            HandleError(err);
         }
      }
   }

   public struct DoBitInformation
   {
      #region fields
      private int m_bitValue;
      private int m_portNum;
      private int m_bitNum;
      #endregion

      public DoBitInformation(int bitvalue, int portNum, int bitNum)
      {
         m_bitValue = bitvalue;
         m_portNum = portNum;
         m_bitNum = bitNum;
      }

      #region Properties
      public int BitValue
      {
         get { return m_bitValue; }
         set
         {
            m_bitValue = value & 0x1;
         }
      }
      public int PortNum
      {
         get { return m_portNum; }
         set
         {
            if ((value - ConstVal.StartPort) >= 0
               && (value - ConstVal.StartPort) <= (ConstVal.PortCountShow - 1))
            {
               m_portNum = value;
            }
         }
      }
      public int BitNum
      {
         get { return m_bitNum; }
         set
         {
            if (value >= 0 && value <= 7)
            {
               m_bitNum = value;
            }
         }
      }
      #endregion
   }

   public static class ConstVal
   {
      public const int StartPort = 0;
      public const int PortCountShow = 4;
   }
}
