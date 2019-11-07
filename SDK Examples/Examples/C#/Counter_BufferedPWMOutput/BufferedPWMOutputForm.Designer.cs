namespace Counter_BufferedPWMOutput
{
    partial class BufferedPWMOutputForm
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
           System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BufferedPWMOutputForm));
           this.groupBox1 = new System.Windows.Forms.GroupBox();
           this.ExecutionStatus = new System.Windows.Forms.Label();
           this.Start = new System.Windows.Forms.Button();
           this.Stop = new System.Windows.Forms.Button();
           this.pictureBox1 = new System.Windows.Forms.PictureBox();
           this.label2 = new System.Windows.Forms.Label();
           this.data1_HiPeriod = new System.Windows.Forms.TextBox();
           this.label6 = new System.Windows.Forms.Label();
           this.label7 = new System.Windows.Forms.Label();
           this.label8 = new System.Windows.Forms.Label();
           this.data1_LoPeriod = new System.Windows.Forms.TextBox();
           this.bufferedPwModulatorCtrl1 = new Automation.BDaq.BufferedPwModulatorCtrl(this.components);
           this.groupBox2 = new System.Windows.Forms.GroupBox();
           this.groupBox3 = new System.Windows.Forms.GroupBox();
           this.label12 = new System.Windows.Forms.Label();
           this.data2_LoPeriod = new System.Windows.Forms.TextBox();
           this.data2_HiPeriod = new System.Windows.Forms.TextBox();
           this.label13 = new System.Windows.Forms.Label();
           this.label11 = new System.Windows.Forms.Label();
           this.label1 = new System.Windows.Forms.Label();
           this.label3 = new System.Windows.Forms.Label();
           this.groupBox1.SuspendLayout();
           ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
           this.groupBox2.SuspendLayout();
           this.groupBox3.SuspendLayout();
           this.SuspendLayout();
           // 
           // groupBox1
           // 
           this.groupBox1.Controls.Add(this.ExecutionStatus);
           this.groupBox1.Location = new System.Drawing.Point(22, 261);
           this.groupBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.groupBox1.Name = "groupBox1";
           this.groupBox1.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.groupBox1.Size = new System.Drawing.Size(260, 57);
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
           // Start
           // 
           this.Start.Location = new System.Drawing.Point(38, 339);
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
           this.Stop.Location = new System.Drawing.Point(167, 339);
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
           this.pictureBox1.Location = new System.Drawing.Point(228, 4);
           this.pictureBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.pictureBox1.Name = "pictureBox1";
           this.pictureBox1.Size = new System.Drawing.Size(153, 53);
           this.pictureBox1.TabIndex = 7;
           this.pictureBox1.TabStop = false;
           // 
           // label2
           // 
           this.label2.AutoSize = true;
           this.label2.Location = new System.Drawing.Point(183, 29);
           this.label2.Name = "label2";
           this.label2.Size = new System.Drawing.Size(15, 15);
           this.label2.TabIndex = 2;
           this.label2.Text = "S";
           // 
           // data1_HiPeriod
           // 
           this.data1_HiPeriod.Location = new System.Drawing.Point(95, 26);
           this.data1_HiPeriod.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.data1_HiPeriod.Name = "data1_HiPeriod";
           this.data1_HiPeriod.RightToLeft = System.Windows.Forms.RightToLeft.No;
           this.data1_HiPeriod.Size = new System.Drawing.Size(82, 21);
           this.data1_HiPeriod.TabIndex = 1;
           this.data1_HiPeriod.Text = "0.08";
           this.data1_HiPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // label6
           // 
           this.label6.AutoSize = true;
           this.label6.Location = new System.Drawing.Point(10, 26);
           this.label6.Name = "label6";
           this.label6.Size = new System.Drawing.Size(75, 15);
           this.label6.TabIndex = 8;
           this.label6.Text = "High Period:";
           // 
           // label7
           // 
           this.label7.AutoSize = true;
           this.label7.Location = new System.Drawing.Point(10, 58);
           this.label7.Name = "label7";
           this.label7.Size = new System.Drawing.Size(72, 15);
           this.label7.TabIndex = 11;
           this.label7.Text = "Low Period:";
           // 
           // label8
           // 
           this.label8.AutoSize = true;
           this.label8.Location = new System.Drawing.Point(183, 61);
           this.label8.Name = "label8";
           this.label8.Size = new System.Drawing.Size(15, 15);
           this.label8.TabIndex = 10;
           this.label8.Text = "S";
           // 
           // data1_LoPeriod
           // 
           this.data1_LoPeriod.Location = new System.Drawing.Point(95, 58);
           this.data1_LoPeriod.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.data1_LoPeriod.Name = "data1_LoPeriod";
           this.data1_LoPeriod.RightToLeft = System.Windows.Forms.RightToLeft.No;
           this.data1_LoPeriod.Size = new System.Drawing.Size(82, 21);
           this.data1_LoPeriod.TabIndex = 9;
           this.data1_LoPeriod.Text = "0.02";
           this.data1_LoPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // bufferedPwModulatorCtrl1
           // 
           this.bufferedPwModulatorCtrl1._StateStream = ((Automation.BDaq.DeviceStateStreamer)(resources.GetObject("bufferedPwModulatorCtrl1._StateStream")));
           // 
           // groupBox2
           // 
           this.groupBox2.Controls.Add(this.label6);
           this.groupBox2.Controls.Add(this.label8);
           this.groupBox2.Controls.Add(this.label7);
           this.groupBox2.Controls.Add(this.data1_LoPeriod);
           this.groupBox2.Controls.Add(this.data1_HiPeriod);
           this.groupBox2.Controls.Add(this.label2);
           this.groupBox2.Location = new System.Drawing.Point(22, 54);
           this.groupBox2.Name = "groupBox2";
           this.groupBox2.Size = new System.Drawing.Size(220, 91);
           this.groupBox2.TabIndex = 12;
           this.groupBox2.TabStop = false;
           this.groupBox2.Text = "Data 1";
           // 
           // groupBox3
           // 
           this.groupBox3.Controls.Add(this.label12);
           this.groupBox3.Controls.Add(this.data2_LoPeriod);
           this.groupBox3.Controls.Add(this.data2_HiPeriod);
           this.groupBox3.Controls.Add(this.label13);
           this.groupBox3.Controls.Add(this.label11);
           this.groupBox3.Controls.Add(this.label1);
           this.groupBox3.Location = new System.Drawing.Point(22, 151);
           this.groupBox3.Name = "groupBox3";
           this.groupBox3.Size = new System.Drawing.Size(220, 91);
           this.groupBox3.TabIndex = 13;
           this.groupBox3.TabStop = false;
           this.groupBox3.Text = "Data 2";
           // 
           // label12
           // 
           this.label12.AutoSize = true;
           this.label12.Location = new System.Drawing.Point(183, 55);
           this.label12.Name = "label12";
           this.label12.Size = new System.Drawing.Size(15, 15);
           this.label12.TabIndex = 14;
           this.label12.Text = "S";
           // 
           // data2_LoPeriod
           // 
           this.data2_LoPeriod.Location = new System.Drawing.Point(95, 52);
           this.data2_LoPeriod.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.data2_LoPeriod.Name = "data2_LoPeriod";
           this.data2_LoPeriod.RightToLeft = System.Windows.Forms.RightToLeft.No;
           this.data2_LoPeriod.Size = new System.Drawing.Size(82, 21);
           this.data2_LoPeriod.TabIndex = 13;
           this.data2_LoPeriod.Text = "0.05";
           this.data2_LoPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // data2_HiPeriod
           // 
           this.data2_HiPeriod.Location = new System.Drawing.Point(95, 21);
           this.data2_HiPeriod.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.data2_HiPeriod.Name = "data2_HiPeriod";
           this.data2_HiPeriod.RightToLeft = System.Windows.Forms.RightToLeft.No;
           this.data2_HiPeriod.Size = new System.Drawing.Size(82, 21);
           this.data2_HiPeriod.TabIndex = 11;
           this.data2_HiPeriod.Text = "0.05";
           this.data2_HiPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // label13
           // 
           this.label13.AutoSize = true;
           this.label13.Location = new System.Drawing.Point(183, 24);
           this.label13.Name = "label13";
           this.label13.Size = new System.Drawing.Size(15, 15);
           this.label13.TabIndex = 12;
           this.label13.Text = "S";
           // 
           // label11
           // 
           this.label11.AutoSize = true;
           this.label11.Location = new System.Drawing.Point(13, 55);
           this.label11.Name = "label11";
           this.label11.Size = new System.Drawing.Size(72, 15);
           this.label11.TabIndex = 1;
           this.label11.Text = "Low Period:";
           // 
           // label1
           // 
           this.label1.AutoSize = true;
           this.label1.Location = new System.Drawing.Point(14, 23);
           this.label1.Name = "label1";
           this.label1.Size = new System.Drawing.Size(75, 15);
           this.label1.TabIndex = 0;
           this.label1.Text = "High Period:";
           // 
           // label3
           // 
           this.label3.Location = new System.Drawing.Point(248, 172);
           this.label3.Name = "label3";
           this.label3.Size = new System.Drawing.Size(122, 70);
           this.label3.TabIndex = 14;
           this.label3.Text = "Note: The buffer will be filled with Data 1 and Data 2 in turn.";
           // 
           // BufferedPWMOutputForm
           // 
           this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
           this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
           this.ClientSize = new System.Drawing.Size(382, 381);
           this.Controls.Add(this.label3);
           this.Controls.Add(this.groupBox3);
           this.Controls.Add(this.groupBox2);
           this.Controls.Add(this.Stop);
           this.Controls.Add(this.Start);
           this.Controls.Add(this.groupBox1);
           this.Controls.Add(this.pictureBox1);
           this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
           this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.MaximizeBox = false;
           this.MinimizeBox = false;
           this.Name = "BufferedPWMOutputForm";
           this.Text = "BufferedPWMOutput";
           this.Load += new System.EventHandler(this.BufferedPwModulatorForm_Load);
           this.groupBox1.ResumeLayout(false);
           ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
           this.groupBox2.ResumeLayout(false);
           this.groupBox2.PerformLayout();
           this.groupBox3.ResumeLayout(false);
           this.groupBox3.PerformLayout();
           this.ResumeLayout(false);

        }

        #endregion

         private System.Windows.Forms.GroupBox groupBox1;
         private System.Windows.Forms.Button Start;
         private System.Windows.Forms.Button Stop;
         private System.Windows.Forms.Label ExecutionStatus;
         private System.Windows.Forms.PictureBox pictureBox1;
         private System.Windows.Forms.Label label2;
         private System.Windows.Forms.TextBox data1_HiPeriod;
         private System.Windows.Forms.Label label6;
         private System.Windows.Forms.Label label7;
         private System.Windows.Forms.Label label8;
         private System.Windows.Forms.TextBox data1_LoPeriod;
         private Automation.BDaq.BufferedPwModulatorCtrl bufferedPwModulatorCtrl1;
         private System.Windows.Forms.GroupBox groupBox2;
         private System.Windows.Forms.GroupBox groupBox3;
         private System.Windows.Forms.Label label11;
         private System.Windows.Forms.Label label1;
         private System.Windows.Forms.Label label12;
         private System.Windows.Forms.TextBox data2_LoPeriod;
         private System.Windows.Forms.TextBox data2_HiPeriod;
         private System.Windows.Forms.Label label13;
         private System.Windows.Forms.Label label3;
    }
}