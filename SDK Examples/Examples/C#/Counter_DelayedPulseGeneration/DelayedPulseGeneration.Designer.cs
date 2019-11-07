namespace Counter_DelayedPulseGeneration
{
    partial class DelayedPulseGenerationForm
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
           System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DelayedPulseGenerationForm));
           this.Start = new System.Windows.Forms.Button();
           this.Stop = new System.Windows.Forms.Button();
           this.pictureBox1 = new System.Windows.Forms.PictureBox();
           this.ExecutionStatus = new System.Windows.Forms.Label();
           this.label_shotCount = new System.Windows.Forms.Label();
           this.eventCount = new System.Windows.Forms.TextBox();
           this.label1 = new System.Windows.Forms.Label();
           this.groupBox1 = new System.Windows.Forms.GroupBox();
           this.delayCount = new System.Windows.Forms.TextBox();
           this.m_oneShotCtrl = new Automation.BDaq.OneShotCtrl(this.components);
           ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
           this.groupBox1.SuspendLayout();
           this.SuspendLayout();
           // 
           // Start
           // 
           this.Start.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.Start.Location = new System.Drawing.Point(53, 180);
           this.Start.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.Start.Name = "Start";
           this.Start.Size = new System.Drawing.Size(77, 28);
           this.Start.TabIndex = 3;
           this.Start.Text = "Start";
           this.Start.UseVisualStyleBackColor = true;
           this.Start.Click += new System.EventHandler(this.Start_Click);
           // 
           // Stop
           // 
           this.Stop.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.Stop.Location = new System.Drawing.Point(180, 180);
           this.Stop.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.Stop.Name = "Stop";
           this.Stop.Size = new System.Drawing.Size(77, 28);
           this.Stop.TabIndex = 4;
           this.Stop.Text = "Stop";
           this.Stop.UseVisualStyleBackColor = true;
           this.Stop.Click += new System.EventHandler(this.Stop_Click);
           // 
           // pictureBox1
           // 
           this.pictureBox1.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox1.BackgroundImage")));
           this.pictureBox1.Location = new System.Drawing.Point(116, -19);
           this.pictureBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.pictureBox1.Name = "pictureBox1";
           this.pictureBox1.Size = new System.Drawing.Size(278, 92);
           this.pictureBox1.TabIndex = 10;
           this.pictureBox1.TabStop = false;
           // 
           // ExecutionStatus
           // 
           this.ExecutionStatus.Image = ((System.Drawing.Image)(resources.GetObject("ExecutionStatus.Image")));
           this.ExecutionStatus.Location = new System.Drawing.Point(19, 24);
           this.ExecutionStatus.Name = "ExecutionStatus";
           this.ExecutionStatus.Size = new System.Drawing.Size(246, 29);
           this.ExecutionStatus.TabIndex = 7;
           // 
           // label_shotCount
           // 
           this.label_shotCount.Location = new System.Drawing.Point(28, 103);
           this.label_shotCount.Name = "label_shotCount";
           this.label_shotCount.Size = new System.Drawing.Size(96, 35);
           this.label_shotCount.TabIndex = 8;
           this.label_shotCount.Text = "Delayed Pulse count:";
           // 
           // eventCount
           // 
           this.eventCount.Location = new System.Drawing.Point(132, 103);
           this.eventCount.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.eventCount.Name = "eventCount";
           this.eventCount.ReadOnly = true;
           this.eventCount.Size = new System.Drawing.Size(137, 21);
           this.eventCount.TabIndex = 11;
           // 
           // label1
           // 
           this.label1.AutoSize = true;
           this.label1.Location = new System.Drawing.Point(28, 67);
           this.label1.Name = "label1";
           this.label1.Size = new System.Drawing.Size(74, 15);
           this.label1.TabIndex = 12;
           this.label1.Text = "Delay count:";
           // 
           // groupBox1
           // 
           this.groupBox1.Controls.Add(this.delayCount);
           this.groupBox1.Controls.Add(this.label1);
           this.groupBox1.Controls.Add(this.eventCount);
           this.groupBox1.Controls.Add(this.label_shotCount);
           this.groupBox1.Controls.Add(this.ExecutionStatus);
           this.groupBox1.Location = new System.Drawing.Point(8, 29);
           this.groupBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.groupBox1.Name = "groupBox1";
           this.groupBox1.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.groupBox1.Size = new System.Drawing.Size(294, 143);
           this.groupBox1.TabIndex = 8;
           this.groupBox1.TabStop = false;
           this.groupBox1.Text = "Execution status";
           // 
           // delayCount
           // 
           this.delayCount.Location = new System.Drawing.Point(132, 67);
           this.delayCount.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.delayCount.Name = "delayCount";
           this.delayCount.ReadOnly = true;
           this.delayCount.Size = new System.Drawing.Size(137, 21);
           this.delayCount.TabIndex = 13;
           // 
           // m_oneShotCtrl
           // 
           this.m_oneShotCtrl._StateStream = ((Automation.BDaq.DeviceStateStreamer)(resources.GetObject("m_oneShotCtrl._StateStream")));
           // 
           // DelayedPulseGenerationForm
           // 
           this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
           this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
           this.ClientSize = new System.Drawing.Size(333, 215);
           this.Controls.Add(this.groupBox1);
           this.Controls.Add(this.Stop);
           this.Controls.Add(this.Start);
           this.Controls.Add(this.pictureBox1);
           this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
           this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.MaximizeBox = false;
           this.MinimizeBox = false;
           this.Name = "DelayedPulseGenerationForm";
           this.Text = "Delayed Pulse Generation";
           this.Load += new System.EventHandler(this.DelayedPulseGenerationForm_Load);
           ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
           this.groupBox1.ResumeLayout(false);
           this.groupBox1.PerformLayout();
           this.ResumeLayout(false);

        }

        #endregion

       private System.Windows.Forms.Button Start;
       private System.Windows.Forms.Button Stop;
       private System.Windows.Forms.PictureBox pictureBox1;
       private System.Windows.Forms.Label ExecutionStatus;
       private System.Windows.Forms.Label label_shotCount;
       private System.Windows.Forms.TextBox eventCount;
       private System.Windows.Forms.Label label1;
       private System.Windows.Forms.GroupBox groupBox1;
       private System.Windows.Forms.TextBox delayCount;
       private Automation.BDaq.OneShotCtrl m_oneShotCtrl;
    }
}