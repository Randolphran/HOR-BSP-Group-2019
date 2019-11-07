namespace Counter_FrequencyMeasurement
{
    partial class FrequencyMeasurementForm
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
           System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrequencyMeasurementForm));
           this.GraphPicture = new System.Windows.Forms.PictureBox();
           this.label_YCoordinateMax = new System.Windows.Forms.Label();
           this.label_YCoordinateMiddle = new System.Windows.Forms.Label();
           this.label_YCoordinateMin = new System.Windows.Forms.Label();
           this.label_XCoordinateMin = new System.Windows.Forms.Label();
           this.label_XCoordinateMax = new System.Windows.Forms.Label();
           this.trackBar = new System.Windows.Forms.TrackBar();
           this.Pause = new System.Windows.Forms.Button();
           this.Stop = new System.Windows.Forms.Button();
           this.ZoomIn = new System.Windows.Forms.PictureBox();
           this.ZoomOut = new System.Windows.Forms.PictureBox();
           this.timer1 = new System.Windows.Forms.Timer(this.components);
           this.Start = new System.Windows.Forms.Button();
           this.pictureBox1 = new System.Windows.Forms.PictureBox();
           this.TimeInterval = new System.Windows.Forms.Label();
           this.label1 = new System.Windows.Forms.Label();
           this.fm1_label = new System.Windows.Forms.Label();
           this.fm2_label = new System.Windows.Forms.Label();
           this.freqMeterCtrl1 = new Automation.BDaq.FreqMeterCtrl(this.components);
           this.freqMeterCtrl2 = new Automation.BDaq.FreqMeterCtrl(this.components);
           ((System.ComponentModel.ISupportInitialize)(this.GraphPicture)).BeginInit();
           ((System.ComponentModel.ISupportInitialize)(this.trackBar)).BeginInit();
           ((System.ComponentModel.ISupportInitialize)(this.ZoomIn)).BeginInit();
           ((System.ComponentModel.ISupportInitialize)(this.ZoomOut)).BeginInit();
           ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
           this.SuspendLayout();
           // 
           // GraphPicture
           // 
           this.GraphPicture.BackColor = System.Drawing.SystemColors.ControlText;
           this.GraphPicture.Location = new System.Drawing.Point(68, 29);
           this.GraphPicture.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.GraphPicture.Name = "GraphPicture";
           this.GraphPicture.Size = new System.Drawing.Size(505, 388);
           this.GraphPicture.TabIndex = 0;
           this.GraphPicture.TabStop = false;
           // 
           // label_YCoordinateMax
           // 
           this.label_YCoordinateMax.AutoSize = true;
           this.label_YCoordinateMax.Location = new System.Drawing.Point(10, 24);
           this.label_YCoordinateMax.Name = "label_YCoordinateMax";
           this.label_YCoordinateMax.Size = new System.Drawing.Size(51, 15);
           this.label_YCoordinateMax.TabIndex = 0;
           this.label_YCoordinateMax.Text = "100KHz";
           // 
           // label_YCoordinateMiddle
           // 
           this.label_YCoordinateMiddle.AutoSize = true;
           this.label_YCoordinateMiddle.Location = new System.Drawing.Point(13, 210);
           this.label_YCoordinateMiddle.Name = "label_YCoordinateMiddle";
           this.label_YCoordinateMiddle.Size = new System.Drawing.Size(44, 15);
           this.label_YCoordinateMiddle.TabIndex = 2;
           this.label_YCoordinateMiddle.Text = "50KHz";
           // 
           // label_YCoordinateMin
           // 
           this.label_YCoordinateMin.AutoSize = true;
           this.label_YCoordinateMin.Location = new System.Drawing.Point(23, 403);
           this.label_YCoordinateMin.Name = "label_YCoordinateMin";
           this.label_YCoordinateMin.Size = new System.Drawing.Size(32, 15);
           this.label_YCoordinateMin.TabIndex = 3;
           this.label_YCoordinateMin.Text = "0 Hz";
           // 
           // label_XCoordinateMin
           // 
           this.label_XCoordinateMin.AutoSize = true;
           this.label_XCoordinateMin.Location = new System.Drawing.Point(61, 428);
           this.label_XCoordinateMin.Name = "label_XCoordinateMin";
           this.label_XCoordinateMin.Size = new System.Drawing.Size(36, 15);
           this.label_XCoordinateMin.TabIndex = 5;
           this.label_XCoordinateMin.Text = "0 sec";
           // 
           // label_XCoordinateMax
           // 
           this.label_XCoordinateMax.AutoSize = true;
           this.label_XCoordinateMax.Location = new System.Drawing.Point(562, 428);
           this.label_XCoordinateMax.Name = "label_XCoordinateMax";
           this.label_XCoordinateMax.Size = new System.Drawing.Size(43, 15);
           this.label_XCoordinateMax.TabIndex = 7;
           this.label_XCoordinateMax.Text = "10 sec";
           // 
           // trackBar
           // 
           this.trackBar.Location = new System.Drawing.Point(263, 436);
           this.trackBar.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.trackBar.Maximum = 1000;
           this.trackBar.Minimum = 10;
           this.trackBar.Name = "trackBar";
           this.trackBar.Size = new System.Drawing.Size(121, 45);
           this.trackBar.TabIndex = 4;
           this.trackBar.TickStyle = System.Windows.Forms.TickStyle.None;
           this.trackBar.Value = 50;
           this.trackBar.Scroll += new System.EventHandler(this.trackBar_Scroll);
           // 
           // Pause
           // 
           this.Pause.Location = new System.Drawing.Point(585, 132);
           this.Pause.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.Pause.Name = "Pause";
           this.Pause.Size = new System.Drawing.Size(75, 28);
           this.Pause.TabIndex = 1;
           this.Pause.Text = "Pause";
           this.Pause.UseVisualStyleBackColor = true;
           this.Pause.Click += new System.EventHandler(this.Pause_Click);
           // 
           // Stop
           // 
           this.Stop.Location = new System.Drawing.Point(585, 183);
           this.Stop.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.Stop.Name = "Stop";
           this.Stop.Size = new System.Drawing.Size(75, 28);
           this.Stop.TabIndex = 2;
           this.Stop.Text = "Stop";
           this.Stop.UseVisualStyleBackColor = true;
           this.Stop.Click += new System.EventHandler(this.Stop_Click);
           // 
           // ZoomIn
           // 
           this.ZoomIn.Image = ((System.Drawing.Image)(resources.GetObject("ZoomIn.Image")));
           this.ZoomIn.Location = new System.Drawing.Point(27, 298);
           this.ZoomIn.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.ZoomIn.Name = "ZoomIn";
           this.ZoomIn.Size = new System.Drawing.Size(22, 24);
           this.ZoomIn.TabIndex = 12;
           this.ZoomIn.TabStop = false;
           this.ZoomIn.Click += new System.EventHandler(this.ZoomIn_Click);
           // 
           // ZoomOut
           // 
           this.ZoomOut.Image = ((System.Drawing.Image)(resources.GetObject("ZoomOut.Image")));
           this.ZoomOut.Location = new System.Drawing.Point(27, 330);
           this.ZoomOut.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.ZoomOut.Name = "ZoomOut";
           this.ZoomOut.Size = new System.Drawing.Size(22, 24);
           this.ZoomOut.TabIndex = 13;
           this.ZoomOut.TabStop = false;
           this.ZoomOut.Click += new System.EventHandler(this.ZoomOut_Click);
           // 
           // timer1
           // 
           this.timer1.Interval = 50;
           this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
           // 
           // Start
           // 
           this.Start.Location = new System.Drawing.Point(585, 80);
           this.Start.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.Start.Name = "Start";
           this.Start.Size = new System.Drawing.Size(75, 28);
           this.Start.TabIndex = 0;
           this.Start.Text = "Start";
           this.Start.UseVisualStyleBackColor = true;
           this.Start.Click += new System.EventHandler(this.Start_Click);
           // 
           // pictureBox1
           // 
           this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
           this.pictureBox1.InitialImage = ((System.Drawing.Image)(resources.GetObject("pictureBox1.InitialImage")));
           this.pictureBox1.Location = new System.Drawing.Point(513, -3);
           this.pictureBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.pictureBox1.Name = "pictureBox1";
           this.pictureBox1.Size = new System.Drawing.Size(189, 58);
           this.pictureBox1.TabIndex = 15;
           this.pictureBox1.TabStop = false;
           // 
           // TimeInterval
           // 
           this.TimeInterval.AutoSize = true;
           this.TimeInterval.Location = new System.Drawing.Point(388, 439);
           this.TimeInterval.Name = "TimeInterval";
           this.TimeInterval.Size = new System.Drawing.Size(41, 15);
           this.TimeInterval.TabIndex = 16;
           this.TimeInterval.Text = "50 ms";
           // 
           // label1
           // 
           this.label1.AutoSize = true;
           this.label1.Location = new System.Drawing.Point(162, 439);
           this.label1.Name = "label1";
           this.label1.Size = new System.Drawing.Size(95, 15);
           this.label1.TabIndex = 17;
           this.label1.Text = "Sample interval:";
           // 
           // fm1_label
           // 
           this.fm1_label.BackColor = System.Drawing.Color.DarkOrange;
           this.fm1_label.Location = new System.Drawing.Point(586, 259);
           this.fm1_label.Name = "fm1_label";
           this.fm1_label.Size = new System.Drawing.Size(75, 22);
           this.fm1_label.TabIndex = 18;
           this.fm1_label.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
           // 
           // fm2_label
           // 
           this.fm2_label.BackColor = System.Drawing.Color.DarkViolet;
           this.fm2_label.Location = new System.Drawing.Point(586, 284);
           this.fm2_label.Name = "fm2_label";
           this.fm2_label.Size = new System.Drawing.Size(75, 22);
           this.fm2_label.TabIndex = 19;
           this.fm2_label.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
           // 
           // freqMeterCtrl1
           // 
           this.freqMeterCtrl1._StateStream = ((Automation.BDaq.DeviceStateStreamer)(resources.GetObject("freqMeterCtrl1._StateStream")));
           // 
           // freqMeterCtrl2
           // 
           this.freqMeterCtrl2._StateStream = ((Automation.BDaq.DeviceStateStreamer)(resources.GetObject("freqMeterCtrl2._StateStream")));
           // 
           // FrequencyMeasurementForm
           // 
           this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
           this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
           this.ClientSize = new System.Drawing.Size(673, 471);
           this.Controls.Add(this.fm2_label);
           this.Controls.Add(this.fm1_label);
           this.Controls.Add(this.label1);
           this.Controls.Add(this.TimeInterval);
           this.Controls.Add(this.GraphPicture);
           this.Controls.Add(this.Start);
           this.Controls.Add(this.ZoomOut);
           this.Controls.Add(this.ZoomIn);
           this.Controls.Add(this.Stop);
           this.Controls.Add(this.Pause);
           this.Controls.Add(this.trackBar);
           this.Controls.Add(this.label_XCoordinateMax);
           this.Controls.Add(this.label_XCoordinateMin);
           this.Controls.Add(this.label_YCoordinateMin);
           this.Controls.Add(this.label_YCoordinateMiddle);
           this.Controls.Add(this.label_YCoordinateMax);
           this.Controls.Add(this.pictureBox1);
           this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.MaximizeBox = false;
           this.MinimizeBox = false;
           this.Name = "FrequencyMeasurementForm";
           this.Text = "Frequency Measurement";
           this.Load += new System.EventHandler(this.FrequencyMeasurementForm_Load);
           ((System.ComponentModel.ISupportInitialize)(this.GraphPicture)).EndInit();
           ((System.ComponentModel.ISupportInitialize)(this.trackBar)).EndInit();
           ((System.ComponentModel.ISupportInitialize)(this.ZoomIn)).EndInit();
           ((System.ComponentModel.ISupportInitialize)(this.ZoomOut)).EndInit();
           ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
           this.ResumeLayout(false);
           this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox GraphPicture;
        private System.Windows.Forms.Label label_YCoordinateMax;
        private System.Windows.Forms.Label label_YCoordinateMiddle;
        private System.Windows.Forms.Label label_YCoordinateMin;
        private System.Windows.Forms.Label label_XCoordinateMin;
        private System.Windows.Forms.Label label_XCoordinateMax;
        private System.Windows.Forms.TrackBar trackBar;
        private System.Windows.Forms.Button Pause;
        private System.Windows.Forms.Button Stop;
        private System.Windows.Forms.PictureBox ZoomIn;
        private System.Windows.Forms.PictureBox ZoomOut;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button Start;
        private System.Windows.Forms.PictureBox pictureBox1;
       private System.Windows.Forms.Label TimeInterval;
       private System.Windows.Forms.Label label1;
       private System.Windows.Forms.Label fm1_label;
       private System.Windows.Forms.Label fm2_label;
       private Automation.BDaq.FreqMeterCtrl freqMeterCtrl1;
       private Automation.BDaq.FreqMeterCtrl freqMeterCtrl2;
    }
}