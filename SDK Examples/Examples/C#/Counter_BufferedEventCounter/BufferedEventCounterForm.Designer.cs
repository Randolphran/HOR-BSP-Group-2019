namespace Counter_BufferedEventCounter
{
    partial class BufferedEventCounterForm
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
           System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BufferedEventCounterForm));
           this.Start = new System.Windows.Forms.Button();
           this.Stop = new System.Windows.Forms.Button();
           this.channelStatus = new System.Windows.Forms.TextBox();
           this.CounterValueList = new System.Windows.Forms.ListBox();
           this.pictureBox1 = new System.Windows.Forms.PictureBox();
           this.groupBox1 = new System.Windows.Forms.GroupBox();
           this.label2 = new System.Windows.Forms.Label();
           this.label1 = new System.Windows.Forms.Label();
           this.cbxEventChannel = new System.Windows.Forms.ComboBox();
           this.label3 = new System.Windows.Forms.Label();
           this.bufferedEventCounterCtrl1 = new Automation.BDaq.BufferedEventCounterCtrl(this.components);
           ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
           this.groupBox1.SuspendLayout();
           this.SuspendLayout();
           // 
           // Start
           // 
           this.Start.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.Start.Location = new System.Drawing.Point(225, 170);
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
           this.Stop.Location = new System.Drawing.Point(225, 312);
           this.Stop.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.Stop.Name = "Stop";
           this.Stop.Size = new System.Drawing.Size(89, 27);
           this.Stop.TabIndex = 1;
           this.Stop.Text = "Stop";
           this.Stop.UseVisualStyleBackColor = true;
           this.Stop.Click += new System.EventHandler(this.Stop_Click);
           // 
           // channelStatus
           // 
           this.channelStatus.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.channelStatus.ForeColor = System.Drawing.SystemColors.WindowText;
           this.channelStatus.Location = new System.Drawing.Point(94, 16);
           this.channelStatus.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.channelStatus.Name = "channelStatus";
           this.channelStatus.ReadOnly = true;
           this.channelStatus.Size = new System.Drawing.Size(100, 26);
           this.channelStatus.TabIndex = 4;
           this.channelStatus.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // CounterValueList
           // 
           this.CounterValueList.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.CounterValueList.ForeColor = System.Drawing.SystemColors.WindowText;
           this.CounterValueList.FormattingEnabled = true;
           this.CounterValueList.ItemHeight = 18;
           this.CounterValueList.Location = new System.Drawing.Point(14, 55);
           this.CounterValueList.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.CounterValueList.Name = "CounterValueList";
           this.CounterValueList.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
           this.CounterValueList.Size = new System.Drawing.Size(180, 256);
           this.CounterValueList.TabIndex = 3;
           // 
           // pictureBox1
           // 
           this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
           this.pictureBox1.Location = new System.Drawing.Point(165, 1);
           this.pictureBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.pictureBox1.Name = "pictureBox1";
           this.pictureBox1.Size = new System.Drawing.Size(168, 60);
           this.pictureBox1.TabIndex = 4;
           this.pictureBox1.TabStop = false;
           // 
           // groupBox1
           // 
           this.groupBox1.Controls.Add(this.label2);
           this.groupBox1.Controls.Add(this.label1);
           this.groupBox1.Controls.Add(this.channelStatus);
           this.groupBox1.Controls.Add(this.CounterValueList);
           this.groupBox1.Location = new System.Drawing.Point(12, 98);
           this.groupBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.groupBox1.Name = "groupBox1";
           this.groupBox1.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.groupBox1.Size = new System.Drawing.Size(207, 387);
           this.groupBox1.TabIndex = 3;
           this.groupBox1.TabStop = false;
           // 
           // label2
           // 
           this.label2.Location = new System.Drawing.Point(11, 315);
           this.label2.Name = "label2";
           this.label2.Size = new System.Drawing.Size(180, 57);
           this.label2.TabIndex = 6;
           this.label2.Text = "Note: The example will display the first ten values on Data Ready Event every tim" +
               "e.";
           // 
           // label1
           // 
           this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.label1.Location = new System.Drawing.Point(10, 18);
           this.label1.Name = "label1";
           this.label1.Size = new System.Drawing.Size(67, 20);
           this.label1.TabIndex = 5;
           this.label1.Text = "Status:";
           // 
           // cbxEventChannel
           // 
           this.cbxEventChannel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
           this.cbxEventChannel.FormattingEnabled = true;
           this.cbxEventChannel.Location = new System.Drawing.Point(106, 65);
           this.cbxEventChannel.Name = "cbxEventChannel";
           this.cbxEventChannel.Size = new System.Drawing.Size(100, 23);
           this.cbxEventChannel.TabIndex = 5;
           this.cbxEventChannel.SelectedIndexChanged += new System.EventHandler(this.cbxEventChannel_SelectedIndexChanged);
           // 
           // label3
           // 
           this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.label3.Location = new System.Drawing.Point(22, 68);
           this.label3.Name = "label3";
           this.label3.Size = new System.Drawing.Size(78, 20);
           this.label3.TabIndex = 6;
           this.label3.Text = "Channel:";
           // 
           // bufferedEventCounterCtrl1
           // 
           this.bufferedEventCounterCtrl1._StateStream = ((Automation.BDaq.DeviceStateStreamer)(resources.GetObject("bufferedEventCounterCtrl1._StateStream")));
           this.bufferedEventCounterCtrl1.Stopped += new System.EventHandler<Automation.BDaq.BfdCntrEventArgs>(this.bufferedEventCounterCtrl1_StopEvent);
           this.bufferedEventCounterCtrl1.DataReady += new System.EventHandler<Automation.BDaq.BfdCntrEventArgs>(this.bufferedEventCounterCtrl1_DataReady);
           // 
           // BufferedEventCounterForm
           // 
           this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
           this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
           this.BackColor = System.Drawing.SystemColors.Control;
           this.ClientSize = new System.Drawing.Size(338, 500);
           this.Controls.Add(this.label3);
           this.Controls.Add(this.cbxEventChannel);
           this.Controls.Add(this.groupBox1);
           this.Controls.Add(this.pictureBox1);
           this.Controls.Add(this.Start);
           this.Controls.Add(this.Stop);
           this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.ForeColor = System.Drawing.SystemColors.ControlText;
           this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
           this.Location = new System.Drawing.Point(300, 300);
           this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.MaximizeBox = false;
           this.MinimizeBox = false;
           this.Name = "BufferedEventCounterForm";
           this.Text = "Buffered Event Counter";
           this.Load += new System.EventHandler(this.BufferedEventCounterForm_Load);
           ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
           this.groupBox1.ResumeLayout(false);
           this.groupBox1.PerformLayout();
           this.ResumeLayout(false);

        }

        #endregion

       private System.Windows.Forms.Button Start;
       private System.Windows.Forms.Button Stop;
       private System.Windows.Forms.TextBox channelStatus;
       private System.Windows.Forms.ListBox CounterValueList;
       private System.Windows.Forms.PictureBox pictureBox1;
       private System.Windows.Forms.GroupBox groupBox1;
       private System.Windows.Forms.Label label1;
       private System.Windows.Forms.Label label2;
       private System.Windows.Forms.ComboBox cbxEventChannel;
       private System.Windows.Forms.Label label3;
       private Automation.BDaq.BufferedEventCounterCtrl bufferedEventCounterCtrl1;
    
    }
}

