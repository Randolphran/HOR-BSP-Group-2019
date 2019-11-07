namespace Counter_EventCounter
{
    partial class EventCounterForm
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
           System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(EventCounterForm));
           this.timer1 = new System.Windows.Forms.Timer(this.components);
           this.Start = new System.Windows.Forms.Button();
           this.Stop = new System.Windows.Forms.Button();
           this.CurCounterValue = new System.Windows.Forms.TextBox();
           this.CounterValueList = new System.Windows.Forms.ListBox();
           this.pictureBox1 = new System.Windows.Forms.PictureBox();
           this.groupBox1 = new System.Windows.Forms.GroupBox();
           this.m_eventCounterCtrl = new Automation.BDaq.EventCounterCtrl(this.components);
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
           this.Start.Location = new System.Drawing.Point(213, 37);
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
           this.Stop.Location = new System.Drawing.Point(213, 98);
           this.Stop.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.Stop.Name = "Stop";
           this.Stop.Size = new System.Drawing.Size(89, 27);
           this.Stop.TabIndex = 1;
           this.Stop.Text = "Stop";
           this.Stop.UseVisualStyleBackColor = true;
           this.Stop.Click += new System.EventHandler(this.Stop_Click);
           // 
           // CurCounterValue
           // 
           this.CurCounterValue.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.CurCounterValue.ForeColor = System.Drawing.SystemColors.WindowText;
           this.CurCounterValue.Location = new System.Drawing.Point(15, 16);
           this.CurCounterValue.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.CurCounterValue.Name = "CurCounterValue";
           this.CurCounterValue.ReadOnly = true;
           this.CurCounterValue.Size = new System.Drawing.Size(186, 26);
           this.CurCounterValue.TabIndex = 4;
           this.CurCounterValue.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
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
           this.CounterValueList.Size = new System.Drawing.Size(187, 148);
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
           this.groupBox1.Controls.Add(this.CurCounterValue);
           this.groupBox1.Controls.Add(this.CounterValueList);
           this.groupBox1.Controls.Add(this.Start);
           this.groupBox1.Controls.Add(this.Stop);
           this.groupBox1.Location = new System.Drawing.Point(9, 28);
           this.groupBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.groupBox1.Name = "groupBox1";
           this.groupBox1.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.groupBox1.Size = new System.Drawing.Size(315, 212);
           this.groupBox1.TabIndex = 3;
           this.groupBox1.TabStop = false;
           // 
           // m_eventCounterCtrl
           // 
           this.m_eventCounterCtrl._StateStream = ((Automation.BDaq.DeviceStateStreamer)(resources.GetObject("m_eventCounterCtrl._StateStream")));
           // 
           // EventCounterForm
           // 
           this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
           this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
           this.BackColor = System.Drawing.SystemColors.Control;
           this.ClientSize = new System.Drawing.Size(343, 250);
           this.Controls.Add(this.groupBox1);
           this.Controls.Add(this.pictureBox1);
           this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.ForeColor = System.Drawing.SystemColors.ControlText;
           this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
           this.Location = new System.Drawing.Point(300, 300);
           this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.MaximizeBox = false;
           this.MinimizeBox = false;
           this.Name = "EventCounterForm";
           this.Text = "Event Counter";
           this.Load += new System.EventHandler(this.EventCounterForm_Load);
           ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
           this.groupBox1.ResumeLayout(false);
           this.groupBox1.PerformLayout();
           this.ResumeLayout(false);

        }

        #endregion

       private System.Windows.Forms.Timer timer1;
       private System.Windows.Forms.Button Start;
       private System.Windows.Forms.Button Stop;
       private System.Windows.Forms.TextBox CurCounterValue;
       private System.Windows.Forms.ListBox CounterValueList;
       private System.Windows.Forms.PictureBox pictureBox1;
       private System.Windows.Forms.GroupBox groupBox1;
       private Automation.BDaq.EventCounterCtrl m_eventCounterCtrl;
    
    }
}

