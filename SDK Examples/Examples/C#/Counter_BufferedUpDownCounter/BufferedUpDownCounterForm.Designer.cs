namespace Counter_BufferedUpDownCounter
{
    partial class BufferedUpDownCounterForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
           this.components = new System.ComponentModel.Container();
           System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BufferedUpDownCounterForm));
           this.groupBox3 = new System.Windows.Forms.GroupBox();
           this.label3 = new System.Windows.Forms.Label();
           this.label1 = new System.Windows.Forms.Label();
           this.btnStop = new System.Windows.Forms.Button();
           this.btnStart = new System.Windows.Forms.Button();
           this.CounterValueList = new System.Windows.Forms.ListBox();
           this.channelStatus = new System.Windows.Forms.TextBox();
           this.label2 = new System.Windows.Forms.Label();
           this.cbxEventChannel = new System.Windows.Forms.ComboBox();
           this.bufferedUdCounterCtrl1 = new Automation.BDaq.BufferedUdCounterCtrl(this.components);
           this.groupBox3.SuspendLayout();
           this.SuspendLayout();
           // 
           // groupBox3
           // 
           this.groupBox3.Controls.Add(this.label3);
           this.groupBox3.Controls.Add(this.label1);
           this.groupBox3.Controls.Add(this.btnStop);
           this.groupBox3.Controls.Add(this.btnStart);
           this.groupBox3.Controls.Add(this.CounterValueList);
           this.groupBox3.Controls.Add(this.channelStatus);
           this.groupBox3.Location = new System.Drawing.Point(12, 100);
           this.groupBox3.Name = "groupBox3";
           this.groupBox3.Size = new System.Drawing.Size(315, 385);
           this.groupBox3.TabIndex = 2;
           this.groupBox3.TabStop = false;
           // 
           // label3
           // 
           this.label3.Location = new System.Drawing.Point(6, 318);
           this.label3.Name = "label3";
           this.label3.Size = new System.Drawing.Size(205, 57);
           this.label3.TabIndex = 6;
           this.label3.Text = "Note: The example will display the first ten values on Data Ready Event every tim" +
               "e.";
           // 
           // label1
           // 
           this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.label1.Location = new System.Drawing.Point(21, 23);
           this.label1.Name = "label1";
           this.label1.Size = new System.Drawing.Size(67, 20);
           this.label1.TabIndex = 5;
           this.label1.Text = "Satus:";
           // 
           // btnStop
           // 
           this.btnStop.Location = new System.Drawing.Point(217, 236);
           this.btnStop.Name = "btnStop";
           this.btnStop.Size = new System.Drawing.Size(90, 30);
           this.btnStop.TabIndex = 4;
           this.btnStop.Text = "Stop";
           this.btnStop.UseVisualStyleBackColor = true;
           this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
           // 
           // btnStart
           // 
           this.btnStart.Location = new System.Drawing.Point(217, 115);
           this.btnStart.Name = "btnStart";
           this.btnStart.Size = new System.Drawing.Size(90, 30);
           this.btnStart.TabIndex = 2;
           this.btnStart.Text = "Start";
           this.btnStart.UseVisualStyleBackColor = true;
           this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
           // 
           // CounterValueList
           // 
           this.CounterValueList.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.CounterValueList.FormattingEnabled = true;
           this.CounterValueList.ItemHeight = 20;
           this.CounterValueList.Location = new System.Drawing.Point(9, 54);
           this.CounterValueList.Name = "CounterValueList";
           this.CounterValueList.RightToLeft = System.Windows.Forms.RightToLeft.No;
           this.CounterValueList.Size = new System.Drawing.Size(202, 244);
           this.CounterValueList.TabIndex = 1;
           // 
           // channelStatus
           // 
           this.channelStatus.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.channelStatus.Location = new System.Drawing.Point(94, 20);
           this.channelStatus.Name = "channelStatus";
           this.channelStatus.ReadOnly = true;
           this.channelStatus.Size = new System.Drawing.Size(117, 26);
           this.channelStatus.TabIndex = 0;
           // 
           // label2
           // 
           this.label2.AutoSize = true;
           this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.label2.Location = new System.Drawing.Point(28, 65);
           this.label2.Name = "label2";
           this.label2.Size = new System.Drawing.Size(72, 20);
           this.label2.TabIndex = 3;
           this.label2.Text = "Channel:";
           // 
           // cbxEventChannel
           // 
           this.cbxEventChannel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
           this.cbxEventChannel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.cbxEventChannel.FormattingEnabled = true;
           this.cbxEventChannel.Location = new System.Drawing.Point(106, 62);
           this.cbxEventChannel.Name = "cbxEventChannel";
           this.cbxEventChannel.Size = new System.Drawing.Size(121, 28);
           this.cbxEventChannel.TabIndex = 4;
           // 
           // bufferedUdCounterCtrl1
           // 
           this.bufferedUdCounterCtrl1._StateStream = ((Automation.BDaq.DeviceStateStreamer)(resources.GetObject("bufferedUdCounterCtrl1._StateStream")));
           this.bufferedUdCounterCtrl1.Stopped += new System.EventHandler<Automation.BDaq.BfdCntrEventArgs>(this.bufferedUdCounterCtrl1_StopEvent);
           this.bufferedUdCounterCtrl1.DataReady += new System.EventHandler<Automation.BDaq.BfdCntrEventArgs>(this.bufferedUdCounterCtrl1_DataReady);
           // 
           // BufferedUpDownCounterForm
           // 
           this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
           this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
           this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
           this.ClientSize = new System.Drawing.Size(342, 499);
           this.Controls.Add(this.cbxEventChannel);
           this.Controls.Add(this.label2);
           this.Controls.Add(this.groupBox3);
           this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
           this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
           this.MaximizeBox = false;
           this.MinimizeBox = false;
           this.Name = "BufferedUpDownCounterForm";
           this.Text = "Buffered UpDown Counter";
           this.Load += new System.EventHandler(this.BufferedUpDownCounterForm_Load);
           this.groupBox3.ResumeLayout(false);
           this.groupBox3.PerformLayout();
           this.ResumeLayout(false);
           this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ListBox CounterValueList;
        private System.Windows.Forms.TextBox channelStatus;
        private System.Windows.Forms.Button btnStop;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cbxEventChannel;
        private System.Windows.Forms.Label label3;
        private Automation.BDaq.BufferedUdCounterCtrl bufferedUdCounterCtrl1;
    }
}

