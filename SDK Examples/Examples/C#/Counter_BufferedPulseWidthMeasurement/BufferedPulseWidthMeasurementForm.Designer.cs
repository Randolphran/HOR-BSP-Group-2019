namespace Counter_BufferedPulseWidthMeasurement
{
    partial class BufferedPulseWidthMeasurementForm
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
           System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BufferedPulseWidthMeasurementForm));
           this.Start = new System.Windows.Forms.Button();
           this.Stop = new System.Windows.Forms.Button();
           this.CounterValueList = new System.Windows.Forms.ListBox();
           this.pictureBox1 = new System.Windows.Forms.PictureBox();
           this.groupBox1 = new System.Windows.Forms.GroupBox();
           this.label1 = new System.Windows.Forms.Label();
           this.channelStatus = new System.Windows.Forms.TextBox();
           this.bufferedPwMeterCtrl1 = new Automation.BDaq.BufferedPwMeterCtrl(this.components);
           this.label5 = new System.Windows.Forms.Label();
           this.cbxEventChannel = new System.Windows.Forms.ComboBox();
           this.label2 = new System.Windows.Forms.Label();
           ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
           this.groupBox1.SuspendLayout();
           this.SuspendLayout();
           // 
           // Start
           // 
           this.Start.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.Start.Location = new System.Drawing.Point(255, 95);
           this.Start.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.Start.Name = "Start";
           this.Start.Size = new System.Drawing.Size(89, 27);
           this.Start.TabIndex = 0;
           this.Start.Text = "Start";
           this.Start.UseVisualStyleBackColor = true;
           this.Start.Click += new System.EventHandler(this.Start_Click);
           // 
           // Stop
           // 
           this.Stop.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.Stop.Location = new System.Drawing.Point(255, 197);
           this.Stop.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.Stop.Name = "Stop";
           this.Stop.Size = new System.Drawing.Size(89, 27);
           this.Stop.TabIndex = 1;
           this.Stop.Text = "Stop";
           this.Stop.UseVisualStyleBackColor = true;
           this.Stop.Click += new System.EventHandler(this.Stop_Click);
           // 
           // CounterValueList
           // 
           this.CounterValueList.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.CounterValueList.ForeColor = System.Drawing.SystemColors.WindowText;
           this.CounterValueList.FormattingEnabled = true;
           this.CounterValueList.ItemHeight = 18;
           this.CounterValueList.Location = new System.Drawing.Point(12, 54);
           this.CounterValueList.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.CounterValueList.Name = "CounterValueList";
           this.CounterValueList.RightToLeft = System.Windows.Forms.RightToLeft.No;
           this.CounterValueList.Size = new System.Drawing.Size(237, 238);
           this.CounterValueList.TabIndex = 3;
           // 
           // pictureBox1
           // 
           this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
           this.pictureBox1.Location = new System.Drawing.Point(171, 4);
           this.pictureBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.pictureBox1.Name = "pictureBox1";
           this.pictureBox1.Size = new System.Drawing.Size(191, 61);
           this.pictureBox1.TabIndex = 4;
           this.pictureBox1.TabStop = false;
           // 
           // groupBox1
           // 
           this.groupBox1.Controls.Add(this.label1);
           this.groupBox1.Controls.Add(this.channelStatus);
           this.groupBox1.Controls.Add(this.CounterValueList);
           this.groupBox1.Controls.Add(this.Start);
           this.groupBox1.Controls.Add(this.Stop);
           this.groupBox1.Location = new System.Drawing.Point(12, 102);
           this.groupBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.groupBox1.Name = "groupBox1";
           this.groupBox1.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.groupBox1.Size = new System.Drawing.Size(350, 307);
           this.groupBox1.TabIndex = 3;
           this.groupBox1.TabStop = false;
           // 
           // label1
           // 
           this.label1.AutoSize = true;
           this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.label1.Location = new System.Drawing.Point(20, 22);
           this.label1.Name = "label1";
           this.label1.Size = new System.Drawing.Size(60, 20);
           this.label1.TabIndex = 5;
           this.label1.Text = "Status:";
           // 
           // channelStatus
           // 
           this.channelStatus.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.channelStatus.ForeColor = System.Drawing.SystemColors.WindowText;
           this.channelStatus.Location = new System.Drawing.Point(89, 20);
           this.channelStatus.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.channelStatus.Name = "channelStatus";
           this.channelStatus.ReadOnly = true;
           this.channelStatus.Size = new System.Drawing.Size(125, 26);
           this.channelStatus.TabIndex = 4;
           this.channelStatus.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // bufferedPwMeterCtrl1
           // 
           this.bufferedPwMeterCtrl1._StateStream = ((Automation.BDaq.DeviceStateStreamer)(resources.GetObject("bufferedPwMeterCtrl1._StateStream")));
           this.bufferedPwMeterCtrl1.Stopped += new System.EventHandler<Automation.BDaq.BfdCntrEventArgs>(this.bufferedPwMeterCtrl1_StopEvent);
           this.bufferedPwMeterCtrl1.DataReady += new System.EventHandler<Automation.BDaq.BfdCntrEventArgs>(this.bufferedPwMeterCtrl1_DataReady);
           // 
           // label5
           // 
           this.label5.AutoSize = true;
           this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.label5.Location = new System.Drawing.Point(20, 75);
           this.label5.Name = "label5";
           this.label5.Size = new System.Drawing.Size(72, 20);
           this.label5.TabIndex = 5;
           this.label5.Text = "Channel:";
           // 
           // cbxEventChannel
           // 
           this.cbxEventChannel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
           this.cbxEventChannel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.cbxEventChannel.FormattingEnabled = true;
           this.cbxEventChannel.Location = new System.Drawing.Point(101, 72);
           this.cbxEventChannel.Name = "cbxEventChannel";
           this.cbxEventChannel.Size = new System.Drawing.Size(125, 28);
           this.cbxEventChannel.TabIndex = 6;
           // 
           // label2
           // 
           this.label2.Location = new System.Drawing.Point(21, 423);
           this.label2.Name = "label2";
           this.label2.Size = new System.Drawing.Size(244, 45);
           this.label2.TabIndex = 7;
           this.label2.Text = "Note: The example will display the first ten values on Data Ready Event every tim" +
               "e.";
           // 
           // BufferedPulseWidthMeasurementForm
           // 
           this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
           this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
           this.BackColor = System.Drawing.SystemColors.Control;
           this.ClientSize = new System.Drawing.Size(378, 474);
           this.Controls.Add(this.label2);
           this.Controls.Add(this.cbxEventChannel);
           this.Controls.Add(this.label5);
           this.Controls.Add(this.groupBox1);
           this.Controls.Add(this.pictureBox1);
           this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.ForeColor = System.Drawing.SystemColors.ControlText;
           this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
           this.Location = new System.Drawing.Point(300, 300);
           this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.MaximizeBox = false;
           this.MinimizeBox = false;
           this.Name = "BufferedPulseWidthMeasurementForm";
           this.Text = "Buffered Pulse Width Measurement";
           this.Load += new System.EventHandler(this.BufferedPulseWidthMeasurementForm_Load);
           ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
           this.groupBox1.ResumeLayout(false);
           this.groupBox1.PerformLayout();
           this.ResumeLayout(false);
           this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Start;
        private System.Windows.Forms.Button Stop;
       private System.Windows.Forms.ListBox CounterValueList;
       private System.Windows.Forms.PictureBox pictureBox1;
       private System.Windows.Forms.GroupBox groupBox1;
       private System.Windows.Forms.Label label1;
       private Automation.BDaq.BufferedPwMeterCtrl bufferedPwMeterCtrl1;
       private System.Windows.Forms.Label label5;
       private System.Windows.Forms.ComboBox cbxEventChannel;
       private System.Windows.Forms.TextBox channelStatus;
       private System.Windows.Forms.Label label2;
    
    }
}

