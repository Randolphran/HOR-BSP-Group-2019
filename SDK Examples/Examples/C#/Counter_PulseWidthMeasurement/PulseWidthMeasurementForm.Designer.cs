namespace Counter_PulseWidthMeasurement
{
    partial class PulseWidthMeasurementForm
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
           System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PulseWidthMeasurementForm));
           this.timer1 = new System.Windows.Forms.Timer(this.components);
           this.Start = new System.Windows.Forms.Button();
           this.Stop = new System.Windows.Forms.Button();
           this.curHiPeriod = new System.Windows.Forms.TextBox();
           this.CounterValueList = new System.Windows.Forms.ListBox();
           this.pictureBox1 = new System.Windows.Forms.PictureBox();
           this.groupBox1 = new System.Windows.Forms.GroupBox();
           this.label4 = new System.Windows.Forms.Label();
           this.label3 = new System.Windows.Forms.Label();
           this.label2 = new System.Windows.Forms.Label();
           this.curLoPeriod = new System.Windows.Forms.TextBox();
           this.label1 = new System.Windows.Forms.Label();
           this.m_pwMeterCtrl = new Automation.BDaq.PwMeterCtrl(this.components);
           ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
           this.groupBox1.SuspendLayout();
           this.SuspendLayout();
           // 
           // timer1
           // 
           this.timer1.Interval = 40;
           this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
           // 
           // Start
           // 
           this.Start.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.Start.Location = new System.Drawing.Point(223, 37);
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
           this.Stop.Location = new System.Drawing.Point(223, 98);
           this.Stop.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.Stop.Name = "Stop";
           this.Stop.Size = new System.Drawing.Size(89, 27);
           this.Stop.TabIndex = 1;
           this.Stop.Text = "Stop";
           this.Stop.UseVisualStyleBackColor = true;
           this.Stop.Click += new System.EventHandler(this.Stop_Click);
           // 
           // curHiPeriod
           // 
           this.curHiPeriod.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.curHiPeriod.ForeColor = System.Drawing.SystemColors.WindowText;
           this.curHiPeriod.Location = new System.Drawing.Point(85, 16);
           this.curHiPeriod.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.curHiPeriod.Name = "curHiPeriod";
           this.curHiPeriod.ReadOnly = true;
           this.curHiPeriod.Size = new System.Drawing.Size(100, 26);
           this.curHiPeriod.TabIndex = 4;
           this.curHiPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // CounterValueList
           // 
           this.CounterValueList.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.CounterValueList.ForeColor = System.Drawing.SystemColors.WindowText;
           this.CounterValueList.FormattingEnabled = true;
           this.CounterValueList.ItemHeight = 18;
           this.CounterValueList.Location = new System.Drawing.Point(3, 91);
           this.CounterValueList.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.CounterValueList.Name = "CounterValueList";
           this.CounterValueList.RightToLeft = System.Windows.Forms.RightToLeft.No;
           this.CounterValueList.Size = new System.Drawing.Size(211, 112);
           this.CounterValueList.TabIndex = 3;
           // 
           // pictureBox1
           // 
           this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
           this.pictureBox1.Location = new System.Drawing.Point(185, -10);
           this.pictureBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.pictureBox1.Name = "pictureBox1";
           this.pictureBox1.Size = new System.Drawing.Size(191, 71);
           this.pictureBox1.TabIndex = 4;
           this.pictureBox1.TabStop = false;
           // 
           // groupBox1
           // 
           this.groupBox1.Controls.Add(this.label4);
           this.groupBox1.Controls.Add(this.label3);
           this.groupBox1.Controls.Add(this.label2);
           this.groupBox1.Controls.Add(this.curLoPeriod);
           this.groupBox1.Controls.Add(this.label1);
           this.groupBox1.Controls.Add(this.curHiPeriod);
           this.groupBox1.Controls.Add(this.CounterValueList);
           this.groupBox1.Controls.Add(this.Start);
           this.groupBox1.Controls.Add(this.Stop);
           this.groupBox1.Location = new System.Drawing.Point(9, 34);
           this.groupBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.groupBox1.Name = "groupBox1";
           this.groupBox1.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.groupBox1.Size = new System.Drawing.Size(323, 212);
           this.groupBox1.TabIndex = 3;
           this.groupBox1.TabStop = false;
           // 
           // label4
           // 
           this.label4.AutoSize = true;
           this.label4.Location = new System.Drawing.Point(195, 53);
           this.label4.Name = "label4";
           this.label4.Size = new System.Drawing.Size(15, 15);
           this.label4.TabIndex = 9;
           this.label4.Text = "S";
           // 
           // label3
           // 
           this.label3.AutoSize = true;
           this.label3.Location = new System.Drawing.Point(195, 23);
           this.label3.Name = "label3";
           this.label3.Size = new System.Drawing.Size(15, 15);
           this.label3.TabIndex = 8;
           this.label3.Text = "S";
           // 
           // label2
           // 
           this.label2.AutoSize = true;
           this.label2.Location = new System.Drawing.Point(8, 52);
           this.label2.Name = "label2";
           this.label2.Size = new System.Drawing.Size(72, 15);
           this.label2.TabIndex = 7;
           this.label2.Text = "Low Period:";
           // 
           // curLoPeriod
           // 
           this.curLoPeriod.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.curLoPeriod.ForeColor = System.Drawing.SystemColors.WindowText;
           this.curLoPeriod.Location = new System.Drawing.Point(85, 48);
           this.curLoPeriod.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.curLoPeriod.Name = "curLoPeriod";
           this.curLoPeriod.ReadOnly = true;
           this.curLoPeriod.Size = new System.Drawing.Size(100, 26);
           this.curLoPeriod.TabIndex = 6;
           this.curLoPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // label1
           // 
           this.label1.AutoSize = true;
           this.label1.Location = new System.Drawing.Point(8, 22);
           this.label1.Name = "label1";
           this.label1.Size = new System.Drawing.Size(75, 15);
           this.label1.TabIndex = 5;
           this.label1.Text = "High Period:";
           // 
           // m_pwMeterCtrl
           // 
           this.m_pwMeterCtrl._StateStream = ((Automation.BDaq.DeviceStateStreamer)(resources.GetObject("m_pwMeterCtrl._StateStream")));
           // 
           // PulseWidthMeasurementForm
           // 
           this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
           this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
           this.BackColor = System.Drawing.SystemColors.Control;
           this.ClientSize = new System.Drawing.Size(351, 250);
           this.Controls.Add(this.groupBox1);
           this.Controls.Add(this.pictureBox1);
           this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.ForeColor = System.Drawing.SystemColors.ControlText;
           this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
           this.Location = new System.Drawing.Point(300, 300);
           this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.MaximizeBox = false;
           this.MinimizeBox = false;
           this.Name = "PulseWidthMeasurementForm";
           this.Text = "Pulse Width Measurement";
           this.Load += new System.EventHandler(this.PulseWidthMeasurementForm_Load);
           ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
           this.groupBox1.ResumeLayout(false);
           this.groupBox1.PerformLayout();
           this.ResumeLayout(false);

        }

        #endregion

       private System.Windows.Forms.Timer timer1;
       private System.Windows.Forms.Button Start;
       private System.Windows.Forms.Button Stop;
       private System.Windows.Forms.TextBox curHiPeriod;
       private System.Windows.Forms.ListBox CounterValueList;
       private System.Windows.Forms.PictureBox pictureBox1;
       private System.Windows.Forms.GroupBox groupBox1;
       private Automation.BDaq.PwMeterCtrl m_pwMeterCtrl;
       private System.Windows.Forms.Label label2;
       private System.Windows.Forms.TextBox curLoPeriod;
       private System.Windows.Forms.Label label1;
       private System.Windows.Forms.Label label4;
       private System.Windows.Forms.Label label3;
    
    }
}

