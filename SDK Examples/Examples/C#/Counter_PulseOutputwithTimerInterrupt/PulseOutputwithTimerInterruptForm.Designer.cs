namespace Counter_PulseOutputwithTimerInterrupt
{
    partial class PulseOutputwithTimerInterruptForm
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
           System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PulseOutputwithTimerInterruptForm));
           this.groupBox1 = new System.Windows.Forms.GroupBox();
           this.ExecutionStatus = new System.Windows.Forms.Label();
           this.eventCount = new System.Windows.Forms.TextBox();
           this.label_eventCount = new System.Windows.Forms.Label();
           this.label4 = new System.Windows.Forms.Label();
           this.label3 = new System.Windows.Forms.Label();
           this.generatedFrequency = new System.Windows.Forms.TextBox();
           this.Start = new System.Windows.Forms.Button();
           this.Stop = new System.Windows.Forms.Button();
           this.pictureBox1 = new System.Windows.Forms.PictureBox();
           this.label1 = new System.Windows.Forms.Label();
           this.label2 = new System.Windows.Forms.Label();
           this.desiredFrequency = new System.Windows.Forms.TextBox();
           this.m_timerPulseCtrl = new Automation.BDaq.TimerPulseCtrl(this.components);
           this.groupBox1.SuspendLayout();
           ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
           this.SuspendLayout();
           // 
           // groupBox1
           // 
           this.groupBox1.Controls.Add(this.ExecutionStatus);
           this.groupBox1.Controls.Add(this.eventCount);
           this.groupBox1.Controls.Add(this.label_eventCount);
           this.groupBox1.Controls.Add(this.label4);
           this.groupBox1.Controls.Add(this.label3);
           this.groupBox1.Controls.Add(this.generatedFrequency);
           this.groupBox1.Location = new System.Drawing.Point(22, 65);
           this.groupBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.groupBox1.Name = "groupBox1";
           this.groupBox1.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.groupBox1.Size = new System.Drawing.Size(301, 164);
           this.groupBox1.TabIndex = 3;
           this.groupBox1.TabStop = false;
           this.groupBox1.Text = "Execution status ";
           // 
           // ExecutionStatus
           // 
           this.ExecutionStatus.Enabled = false;
           this.ExecutionStatus.Image = ((System.Drawing.Image)(resources.GetObject("ExecutionStatus.Image")));
           this.ExecutionStatus.Location = new System.Drawing.Point(7, 21);
           this.ExecutionStatus.Name = "ExecutionStatus";
           this.ExecutionStatus.Size = new System.Drawing.Size(246, 29);
           this.ExecutionStatus.TabIndex = 5;
           // 
           // eventCount
           // 
           this.eventCount.Location = new System.Drawing.Point(10, 135);
           this.eventCount.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.eventCount.Name = "eventCount";
           this.eventCount.ReadOnly = true;
           this.eventCount.Size = new System.Drawing.Size(172, 21);
           this.eventCount.TabIndex = 4;
           this.eventCount.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // label_eventCount
           // 
           this.label_eventCount.AutoSize = true;
           this.label_eventCount.Location = new System.Drawing.Point(9, 108);
           this.label_eventCount.Name = "label_eventCount";
           this.label_eventCount.Size = new System.Drawing.Size(202, 15);
           this.label_eventCount.TabIndex = 3;
           this.label_eventCount.Text = "Device generated timer event count:";
           // 
           // label4
           // 
           this.label4.AutoSize = true;
           this.label4.Location = new System.Drawing.Point(190, 85);
           this.label4.Name = "label4";
           this.label4.Size = new System.Drawing.Size(22, 15);
           this.label4.TabIndex = 2;
           this.label4.Text = "Hz";
           // 
           // label3
           // 
           this.label3.AutoSize = true;
           this.label3.Location = new System.Drawing.Point(7, 55);
           this.label3.Name = "label3";
           this.label3.Size = new System.Drawing.Size(195, 15);
           this.label3.TabIndex = 1;
           this.label3.Text = "Device generated pulse frequency:";
           // 
           // generatedFrequency
           // 
           this.generatedFrequency.Location = new System.Drawing.Point(12, 82);
           this.generatedFrequency.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.generatedFrequency.Name = "generatedFrequency";
           this.generatedFrequency.ReadOnly = true;
           this.generatedFrequency.RightToLeft = System.Windows.Forms.RightToLeft.No;
           this.generatedFrequency.Size = new System.Drawing.Size(172, 21);
           this.generatedFrequency.TabIndex = 0;
           this.generatedFrequency.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // Start
           // 
           this.Start.Location = new System.Drawing.Point(63, 237);
           this.Start.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.Start.Name = "Start";
           this.Start.Size = new System.Drawing.Size(75, 28);
           this.Start.TabIndex = 5;
           this.Start.Text = "Start";
           this.Start.UseVisualStyleBackColor = true;
           this.Start.Click += new System.EventHandler(this.Start_Click);
           // 
           // Stop
           // 
           this.Stop.Location = new System.Drawing.Point(200, 237);
           this.Stop.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.Stop.Name = "Stop";
           this.Stop.Size = new System.Drawing.Size(75, 28);
           this.Stop.TabIndex = 6;
           this.Stop.Text = "Stop";
           this.Stop.UseVisualStyleBackColor = true;
           this.Stop.Click += new System.EventHandler(this.Stop_Click);
           // 
           // pictureBox1
           // 
           this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
           this.pictureBox1.Location = new System.Drawing.Point(236, -1);
           this.pictureBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.pictureBox1.Name = "pictureBox1";
           this.pictureBox1.Size = new System.Drawing.Size(153, 66);
           this.pictureBox1.TabIndex = 7;
           this.pictureBox1.TabStop = false;
           // 
           // label1
           // 
           this.label1.AutoSize = true;
           this.label1.Location = new System.Drawing.Point(29, 17);
           this.label1.Name = "label1";
           this.label1.Size = new System.Drawing.Size(109, 15);
           this.label1.TabIndex = 0;
           this.label1.Text = "Desired frequency:";
           // 
           // label2
           // 
           this.label2.AutoSize = true;
           this.label2.Location = new System.Drawing.Point(207, 45);
           this.label2.Name = "label2";
           this.label2.Size = new System.Drawing.Size(22, 15);
           this.label2.TabIndex = 2;
           this.label2.Text = "Hz";
           // 
           // desiredFrequency
           // 
           this.desiredFrequency.Location = new System.Drawing.Point(32, 41);
           this.desiredFrequency.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.desiredFrequency.Name = "desiredFrequency";
           this.desiredFrequency.ReadOnly = true;
           this.desiredFrequency.RightToLeft = System.Windows.Forms.RightToLeft.No;
           this.desiredFrequency.Size = new System.Drawing.Size(172, 21);
           this.desiredFrequency.TabIndex = 1;
           this.desiredFrequency.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // m_timerPulseCtrl
           // 
           this.m_timerPulseCtrl._StateStream = ((Automation.BDaq.DeviceStateStreamer)(resources.GetObject("m_timerPulseCtrl._StateStream")));
           // 
           // PulseOutputwithTimerInterruptForm
           // 
           this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
           this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
           this.ClientSize = new System.Drawing.Size(361, 272);
           this.Controls.Add(this.Stop);
           this.Controls.Add(this.Start);
           this.Controls.Add(this.groupBox1);
           this.Controls.Add(this.label2);
           this.Controls.Add(this.desiredFrequency);
           this.Controls.Add(this.label1);
           this.Controls.Add(this.pictureBox1);
           this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
           this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.MaximizeBox = false;
           this.MinimizeBox = false;
           this.Name = "PulseOutputwithTimerInterruptForm";
           this.Text = "Pulse Output with Timer Interrupt";
           this.Load += new System.EventHandler(this.PulseOutputwithTimerInterruptForm_Load);
           this.groupBox1.ResumeLayout(false);
           this.groupBox1.PerformLayout();
           ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
           this.ResumeLayout(false);
           this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button Start;
        private System.Windows.Forms.Button Stop;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox generatedFrequency;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label_eventCount;
        private System.Windows.Forms.TextBox eventCount;
        private System.Windows.Forms.Label ExecutionStatus;
       private System.Windows.Forms.PictureBox pictureBox1;
       private System.Windows.Forms.Label label1;
       private System.Windows.Forms.Label label2;
       private System.Windows.Forms.TextBox desiredFrequency;
       private Automation.BDaq.TimerPulseCtrl m_timerPulseCtrl;
    }
}