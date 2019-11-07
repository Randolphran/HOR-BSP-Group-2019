namespace Counter_PWMOutput
{
    partial class PWMOutputForm
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
           System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PWMOutputForm));
           this.groupBox1 = new System.Windows.Forms.GroupBox();
           this.label9 = new System.Windows.Forms.Label();
           this.label10 = new System.Windows.Forms.Label();
           this.label5 = new System.Windows.Forms.Label();
           this.generatedLoPeriod = new System.Windows.Forms.TextBox();
           this.ExecutionStatus = new System.Windows.Forms.Label();
           this.label4 = new System.Windows.Forms.Label();
           this.label3 = new System.Windows.Forms.Label();
           this.generatedHiPeriod = new System.Windows.Forms.TextBox();
           this.Start = new System.Windows.Forms.Button();
           this.Stop = new System.Windows.Forms.Button();
           this.pictureBox1 = new System.Windows.Forms.PictureBox();
           this.label1 = new System.Windows.Forms.Label();
           this.label2 = new System.Windows.Forms.Label();
           this.desiredHiPeriod = new System.Windows.Forms.TextBox();
           this.label6 = new System.Windows.Forms.Label();
           this.label7 = new System.Windows.Forms.Label();
           this.label8 = new System.Windows.Forms.Label();
           this.desiredLoPeriod = new System.Windows.Forms.TextBox();
           this.m_pwModulatorCtrl = new Automation.BDaq.PwModulatorCtrl(this.components);
           this.groupBox1.SuspendLayout();
           ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
           this.SuspendLayout();
           // 
           // groupBox1
           // 
           this.groupBox1.Controls.Add(this.label9);
           this.groupBox1.Controls.Add(this.label10);
           this.groupBox1.Controls.Add(this.label5);
           this.groupBox1.Controls.Add(this.generatedLoPeriod);
           this.groupBox1.Controls.Add(this.ExecutionStatus);
           this.groupBox1.Controls.Add(this.label4);
           this.groupBox1.Controls.Add(this.label3);
           this.groupBox1.Controls.Add(this.generatedHiPeriod);
           this.groupBox1.Location = new System.Drawing.Point(22, 92);
           this.groupBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.groupBox1.Name = "groupBox1";
           this.groupBox1.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.groupBox1.Size = new System.Drawing.Size(301, 139);
           this.groupBox1.TabIndex = 3;
           this.groupBox1.TabStop = false;
           this.groupBox1.Text = "Execution status ";
           // 
           // label9
           // 
           this.label9.AutoSize = true;
           this.label9.Location = new System.Drawing.Point(20, 112);
           this.label9.Name = "label9";
           this.label9.Size = new System.Drawing.Size(72, 15);
           this.label9.TabIndex = 13;
           this.label9.Text = "Low Period:";
           // 
           // label10
           // 
           this.label10.AutoSize = true;
           this.label10.Location = new System.Drawing.Point(20, 85);
           this.label10.Name = "label10";
           this.label10.Size = new System.Drawing.Size(75, 15);
           this.label10.TabIndex = 12;
           this.label10.Text = "High Period:";
           // 
           // label5
           // 
           this.label5.AutoSize = true;
           this.label5.Location = new System.Drawing.Point(190, 113);
           this.label5.Name = "label5";
           this.label5.Size = new System.Drawing.Size(15, 15);
           this.label5.TabIndex = 7;
           this.label5.Text = "S";
           // 
           // generatedLoPeriod
           // 
           this.generatedLoPeriod.Location = new System.Drawing.Point(100, 110);
           this.generatedLoPeriod.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.generatedLoPeriod.Name = "generatedLoPeriod";
           this.generatedLoPeriod.ReadOnly = true;
           this.generatedLoPeriod.RightToLeft = System.Windows.Forms.RightToLeft.No;
           this.generatedLoPeriod.Size = new System.Drawing.Size(84, 21);
           this.generatedLoPeriod.TabIndex = 6;
           this.generatedLoPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
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
           // label4
           // 
           this.label4.AutoSize = true;
           this.label4.Location = new System.Drawing.Point(190, 85);
           this.label4.Name = "label4";
           this.label4.Size = new System.Drawing.Size(15, 15);
           this.label4.TabIndex = 2;
           this.label4.Text = "S";
           // 
           // label3
           // 
           this.label3.AutoSize = true;
           this.label3.Location = new System.Drawing.Point(7, 57);
           this.label3.Name = "label3";
           this.label3.Size = new System.Drawing.Size(177, 15);
           this.label3.TabIndex = 1;
           this.label3.Text = "Device generated pulse period:";
           // 
           // generatedHiPeriod
           // 
           this.generatedHiPeriod.Location = new System.Drawing.Point(100, 82);
           this.generatedHiPeriod.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.generatedHiPeriod.Name = "generatedHiPeriod";
           this.generatedHiPeriod.ReadOnly = true;
           this.generatedHiPeriod.RightToLeft = System.Windows.Forms.RightToLeft.No;
           this.generatedHiPeriod.Size = new System.Drawing.Size(84, 21);
           this.generatedHiPeriod.TabIndex = 0;
           this.generatedHiPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
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
           this.pictureBox1.Location = new System.Drawing.Point(208, -1);
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
           this.label1.Size = new System.Drawing.Size(91, 15);
           this.label1.TabIndex = 0;
           this.label1.Text = "Desired period:";
           // 
           // label2
           // 
           this.label2.AutoSize = true;
           this.label2.Location = new System.Drawing.Point(207, 45);
           this.label2.Name = "label2";
           this.label2.Size = new System.Drawing.Size(15, 15);
           this.label2.TabIndex = 2;
           this.label2.Text = "S";
           // 
           // desiredHiPeriod
           // 
           this.desiredHiPeriod.Location = new System.Drawing.Point(122, 41);
           this.desiredHiPeriod.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.desiredHiPeriod.Name = "desiredHiPeriod";
           this.desiredHiPeriod.ReadOnly = true;
           this.desiredHiPeriod.RightToLeft = System.Windows.Forms.RightToLeft.No;
           this.desiredHiPeriod.Size = new System.Drawing.Size(82, 21);
           this.desiredHiPeriod.TabIndex = 1;
           this.desiredHiPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // label6
           // 
           this.label6.AutoSize = true;
           this.label6.Location = new System.Drawing.Point(41, 44);
           this.label6.Name = "label6";
           this.label6.Size = new System.Drawing.Size(75, 15);
           this.label6.TabIndex = 8;
           this.label6.Text = "High Period:";
           // 
           // label7
           // 
           this.label7.AutoSize = true;
           this.label7.Location = new System.Drawing.Point(41, 71);
           this.label7.Name = "label7";
           this.label7.Size = new System.Drawing.Size(72, 15);
           this.label7.TabIndex = 11;
           this.label7.Text = "Low Period:";
           // 
           // label8
           // 
           this.label8.AutoSize = true;
           this.label8.Location = new System.Drawing.Point(208, 72);
           this.label8.Name = "label8";
           this.label8.Size = new System.Drawing.Size(15, 15);
           this.label8.TabIndex = 10;
           this.label8.Text = "S";
           // 
           // desiredLoPeriod
           // 
           this.desiredLoPeriod.Location = new System.Drawing.Point(122, 68);
           this.desiredLoPeriod.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.desiredLoPeriod.Name = "desiredLoPeriod";
           this.desiredLoPeriod.ReadOnly = true;
           this.desiredLoPeriod.RightToLeft = System.Windows.Forms.RightToLeft.No;
           this.desiredLoPeriod.Size = new System.Drawing.Size(82, 21);
           this.desiredLoPeriod.TabIndex = 9;
           this.desiredLoPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // m_pwModulatorCtrl
           // 
           this.m_pwModulatorCtrl._StateStream = ((Automation.BDaq.DeviceStateStreamer)(resources.GetObject("m_pwModulatorCtrl._StateStream")));
           // 
           // PWMOutputForm
           // 
           this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
           this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
           this.ClientSize = new System.Drawing.Size(361, 272);
           this.Controls.Add(this.label7);
           this.Controls.Add(this.label8);
           this.Controls.Add(this.desiredLoPeriod);
           this.Controls.Add(this.label6);
           this.Controls.Add(this.Stop);
           this.Controls.Add(this.Start);
           this.Controls.Add(this.groupBox1);
           this.Controls.Add(this.label2);
           this.Controls.Add(this.desiredHiPeriod);
           this.Controls.Add(this.label1);
           this.Controls.Add(this.pictureBox1);
           this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
           this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.MaximizeBox = false;
           this.MinimizeBox = false;
           this.Name = "PWMOutputForm";
           this.Text = "PWM Output";
           this.Load += new System.EventHandler(this.PwModulatorForm_Load);
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
        private System.Windows.Forms.TextBox generatedHiPeriod;
       private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label ExecutionStatus;
       private System.Windows.Forms.PictureBox pictureBox1;
       private System.Windows.Forms.Label label1;
       private System.Windows.Forms.Label label2;
       private System.Windows.Forms.TextBox desiredHiPeriod;
       private System.Windows.Forms.Label label5;
       private System.Windows.Forms.TextBox generatedLoPeriod;
       private System.Windows.Forms.Label label6;
       private System.Windows.Forms.Label label9;
       private System.Windows.Forms.Label label10;
       private System.Windows.Forms.Label label7;
       private System.Windows.Forms.Label label8;
       private System.Windows.Forms.TextBox desiredLoPeriod;
       private Automation.BDaq.PwModulatorCtrl m_pwModulatorCtrl;
    }
}