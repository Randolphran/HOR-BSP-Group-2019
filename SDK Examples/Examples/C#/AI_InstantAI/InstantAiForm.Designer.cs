namespace AI_InstantAI
{
   partial class InstantAIForm
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
         System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(InstantAIForm));
         this.timer_getData = new System.Windows.Forms.Timer(this.components);
         this.button_start = new System.Windows.Forms.Button();
         this.button_pause = new System.Windows.Forms.Button();
         this.button_stop = new System.Windows.Forms.Button();
         this.label_YCoordinateMax = new System.Windows.Forms.Label();
         this.label_YCoordinateMin = new System.Windows.Forms.Label();
         this.label_XCoordinateMax = new System.Windows.Forms.Label();
         this.trackBar = new System.Windows.Forms.TrackBar();
         this.label_XCoordinateMin = new System.Windows.Forms.Label();
         this.pictureBox = new System.Windows.Forms.PictureBox();
         this.label_YCoordinateMiddle = new System.Windows.Forms.Label();
         this.textBox = new System.Windows.Forms.TextBox();
         this.label1 = new System.Windows.Forms.Label();
         this.label2 = new System.Windows.Forms.Label();
         this.label3 = new System.Windows.Forms.Label();
         this.label4 = new System.Windows.Forms.Label();
         this.comboBox_chanStart = new System.Windows.Forms.ComboBox();
         this.comboBox_chanCount = new System.Windows.Forms.ComboBox();
         this.label_chanStart = new System.Windows.Forms.Label();
         this.label_chanCount = new System.Windows.Forms.Label();
         this.instantAiCtrl1 = new Automation.BDaq.InstantAiCtrl(this.components);
         this.listView = new DoubleBufferListView();
         ((System.ComponentModel.ISupportInitialize)(this.trackBar)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
         this.SuspendLayout();
         // 
         // timer_getData
         // 
         this.timer_getData.Tick += new System.EventHandler(this.timer_getData_Tick);
         // 
         // button_start
         // 
         this.button_start.Location = new System.Drawing.Point(471, 466);
         this.button_start.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.button_start.Name = "button_start";
         this.button_start.Size = new System.Drawing.Size(69, 29);
         this.button_start.TabIndex = 2;
         this.button_start.Text = "Start";
         this.button_start.UseVisualStyleBackColor = true;
         this.button_start.Click += new System.EventHandler(this.button_start_Click);
         // 
         // button_pause
         // 
         this.button_pause.Location = new System.Drawing.Point(549, 466);
         this.button_pause.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.button_pause.Name = "button_pause";
         this.button_pause.Size = new System.Drawing.Size(69, 29);
         this.button_pause.TabIndex = 3;
         this.button_pause.Text = "Pause";
         this.button_pause.UseVisualStyleBackColor = true;
         this.button_pause.Click += new System.EventHandler(this.button_pause_Click);
         // 
         // button_stop
         // 
         this.button_stop.Location = new System.Drawing.Point(624, 466);
         this.button_stop.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.button_stop.Name = "button_stop";
         this.button_stop.Size = new System.Drawing.Size(69, 29);
         this.button_stop.TabIndex = 4;
         this.button_stop.Text = "Stop";
         this.button_stop.UseVisualStyleBackColor = true;
         this.button_stop.Click += new System.EventHandler(this.button_stop_Click);
         // 
         // label_YCoordinateMax
         // 
         this.label_YCoordinateMax.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
         this.label_YCoordinateMax.Location = new System.Drawing.Point(-2, 35);
         this.label_YCoordinateMax.Name = "label_YCoordinateMax";
         this.label_YCoordinateMax.Size = new System.Drawing.Size(52, 15);
         this.label_YCoordinateMax.TabIndex = 6;
         this.label_YCoordinateMax.Text = "5V";
         this.label_YCoordinateMax.TextAlign = System.Drawing.ContentAlignment.TopRight;
         // 
         // label_YCoordinateMin
         // 
         this.label_YCoordinateMin.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
         this.label_YCoordinateMin.Location = new System.Drawing.Point(0, 364);
         this.label_YCoordinateMin.Name = "label_YCoordinateMin";
         this.label_YCoordinateMin.Size = new System.Drawing.Size(52, 15);
         this.label_YCoordinateMin.TabIndex = 7;
         this.label_YCoordinateMin.Text = "0V";
         this.label_YCoordinateMin.TextAlign = System.Drawing.ContentAlignment.TopRight;
         // 
         // label_XCoordinateMax
         // 
         this.label_XCoordinateMax.AutoSize = true;
         this.label_XCoordinateMax.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
         this.label_XCoordinateMax.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.label_XCoordinateMax.Location = new System.Drawing.Point(671, 381);
         this.label_XCoordinateMax.Name = "label_XCoordinateMax";
         this.label_XCoordinateMax.Size = new System.Drawing.Size(40, 13);
         this.label_XCoordinateMax.TabIndex = 10;
         this.label_XCoordinateMax.Text = "10 Sec";
         // 
         // trackBar
         // 
         this.trackBar.AutoSize = false;
         this.trackBar.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
         this.trackBar.Location = new System.Drawing.Point(620, 430);
         this.trackBar.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.trackBar.Maximum = 1000;
         this.trackBar.Minimum = 10;
         this.trackBar.Name = "trackBar";
         this.trackBar.Size = new System.Drawing.Size(110, 23);
         this.trackBar.SmallChange = 10;
         this.trackBar.TabIndex = 12;
         this.trackBar.Tag = "ghgfh";
         this.trackBar.TickFrequency = 100;
         this.trackBar.Value = 200;
         this.trackBar.Scroll += new System.EventHandler(this.trackBar_Scroll);
         // 
         // label_XCoordinateMin
         // 
         this.label_XCoordinateMin.AutoSize = true;
         this.label_XCoordinateMin.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
         this.label_XCoordinateMin.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.label_XCoordinateMin.Location = new System.Drawing.Point(49, 381);
         this.label_XCoordinateMin.Name = "label_XCoordinateMin";
         this.label_XCoordinateMin.Size = new System.Drawing.Size(34, 13);
         this.label_XCoordinateMin.TabIndex = 14;
         this.label_XCoordinateMin.Text = "0 Sec";
         // 
         // pictureBox
         // 
         this.pictureBox.BackColor = System.Drawing.SystemColors.ControlText;
         this.pictureBox.Location = new System.Drawing.Point(50, 39);
         this.pictureBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.pictureBox.Name = "pictureBox";
         this.pictureBox.Size = new System.Drawing.Size(660, 340);
         this.pictureBox.TabIndex = 18;
         this.pictureBox.TabStop = false;
         // 
         // label_YCoordinateMiddle
         // 
         this.label_YCoordinateMiddle.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
         this.label_YCoordinateMiddle.Location = new System.Drawing.Point(0, 202);
         this.label_YCoordinateMiddle.Name = "label_YCoordinateMiddle";
         this.label_YCoordinateMiddle.Size = new System.Drawing.Size(52, 15);
         this.label_YCoordinateMiddle.TabIndex = 19;
         this.label_YCoordinateMiddle.Text = "0V";
         this.label_YCoordinateMiddle.TextAlign = System.Drawing.ContentAlignment.TopRight;
         // 
         // textBox
         // 
         this.textBox.Location = new System.Drawing.Point(665, 408);
         this.textBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.textBox.Name = "textBox";
         this.textBox.Size = new System.Drawing.Size(47, 21);
         this.textBox.TabIndex = 20;
         this.textBox.Text = "200";
         this.textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
         // 
         // label1
         // 
         this.label1.AutoSize = true;
         this.label1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
         this.label1.Location = new System.Drawing.Point(712, 412);
         this.label1.Name = "label1";
         this.label1.Size = new System.Drawing.Size(24, 15);
         this.label1.TabIndex = 21;
         this.label1.Text = "ms";
         this.label1.UseWaitCursor = true;
         // 
         // label2
         // 
         this.label2.AllowDrop = true;
         this.label2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
         this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.label2.Location = new System.Drawing.Point(616, 402);
         this.label2.Name = "label2";
         this.label2.Size = new System.Drawing.Size(45, 27);
         this.label2.TabIndex = 22;
         this.label2.Text = "Sample  interval:";
         // 
         // label3
         // 
         this.label3.AutoSize = true;
         this.label3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
         this.label3.Location = new System.Drawing.Point(21, 405);
         this.label3.Name = "label3";
         this.label3.Size = new System.Drawing.Size(14, 15);
         this.label3.TabIndex = 23;
         this.label3.Text = "0";
         // 
         // label4
         // 
         this.label4.AutoSize = true;
         this.label4.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
         this.label4.Location = new System.Drawing.Point(21, 435);
         this.label4.Name = "label4";
         this.label4.Size = new System.Drawing.Size(14, 15);
         this.label4.TabIndex = 24;
         this.label4.Text = "8";
         // 
         // comboBox_chanStart
         // 
         this.comboBox_chanStart.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
         this.comboBox_chanStart.FormattingEnabled = true;
         this.comboBox_chanStart.Location = new System.Drawing.Point(118, 463);
         this.comboBox_chanStart.Name = "comboBox_chanStart";
         this.comboBox_chanStart.Size = new System.Drawing.Size(73, 23);
         this.comboBox_chanStart.TabIndex = 25;
         // 
         // comboBox_chanCount
         // 
         this.comboBox_chanCount.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
         this.comboBox_chanCount.FormattingEnabled = true;
         this.comboBox_chanCount.Location = new System.Drawing.Point(294, 464);
         this.comboBox_chanCount.Name = "comboBox_chanCount";
         this.comboBox_chanCount.Size = new System.Drawing.Size(73, 23);
         this.comboBox_chanCount.TabIndex = 26;
         this.comboBox_chanCount.SelectedIndexChanged += new System.EventHandler(this.comboBox_chanCount_SelectedIndexChanged);
         // 
         // label_chanStart
         // 
         this.label_chanStart.AutoSize = true;
         this.label_chanStart.Location = new System.Drawing.Point(51, 467);
         this.label_chanStart.Name = "label_chanStart";
         this.label_chanStart.Size = new System.Drawing.Size(64, 15);
         this.label_chanStart.TabIndex = 38;
         this.label_chanStart.Text = "ChanStart:";
         // 
         // label_chanCount
         // 
         this.label_chanCount.AutoSize = true;
         this.label_chanCount.Location = new System.Drawing.Point(221, 468);
         this.label_chanCount.Name = "label_chanCount";
         this.label_chanCount.Size = new System.Drawing.Size(71, 15);
         this.label_chanCount.TabIndex = 39;
         this.label_chanCount.Text = "ChanCount:";
         // 
         // instantAiCtrl1
         // 
         this.instantAiCtrl1._StateStream = ((Automation.BDaq.DeviceStateStreamer)(resources.GetObject("instantAiCtrl1._StateStream")));
         // 
         // listView
         // 
         this.listView.ForeColor = System.Drawing.Color.Black;
         this.listView.Location = new System.Drawing.Point(37, 405);
         this.listView.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.listView.Name = "listView";
         this.listView.Size = new System.Drawing.Size(578, 48);
         this.listView.TabIndex = 16;
         this.listView.UseCompatibleStateImageBehavior = false;
         // 
         // InstantAIForm
         // 
         this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
         this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
         this.AutoScroll = true;
         this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
         this.ClientSize = new System.Drawing.Size(758, 508);
         this.Controls.Add(this.label_chanCount);
         this.Controls.Add(this.label_chanStart);
         this.Controls.Add(this.comboBox_chanCount);
         this.Controls.Add(this.comboBox_chanStart);
         this.Controls.Add(this.label4);
         this.Controls.Add(this.label3);
         this.Controls.Add(this.label2);
         this.Controls.Add(this.label1);
         this.Controls.Add(this.textBox);
         this.Controls.Add(this.pictureBox);
         this.Controls.Add(this.listView);
         this.Controls.Add(this.trackBar);
         this.Controls.Add(this.label_XCoordinateMax);
         this.Controls.Add(this.label_YCoordinateMin);
         this.Controls.Add(this.label_YCoordinateMax);
         this.Controls.Add(this.button_stop);
         this.Controls.Add(this.button_pause);
         this.Controls.Add(this.button_start);
         this.Controls.Add(this.label_YCoordinateMiddle);
         this.Controls.Add(this.label_XCoordinateMin);
         this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
         this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.MaximizeBox = false;
         this.MinimizeBox = false;
         this.Name = "InstantAIForm";
         this.Text = "Instant AI";
         this.Load += new System.EventHandler(this.InstantAiForm_Load);
         ((System.ComponentModel.ISupportInitialize)(this.trackBar)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
         this.ResumeLayout(false);
         this.PerformLayout();

      }

      #endregion

      private System.Windows.Forms.Timer timer_getData;
      private System.Windows.Forms.Button button_start;
      private System.Windows.Forms.Button button_pause;
      private System.Windows.Forms.Button button_stop;
      private System.Windows.Forms.Label label_YCoordinateMax;
      private System.Windows.Forms.Label label_YCoordinateMin;
      private System.Windows.Forms.Label label_XCoordinateMin;
      private System.Windows.Forms.TrackBar trackBar;
      private DoubleBufferListView listView;
       private System.Windows.Forms.PictureBox pictureBox;
      private System.Windows.Forms.Label label_YCoordinateMiddle;
      private System.Windows.Forms.TextBox textBox;
      private System.Windows.Forms.Label label1;
      private System.Windows.Forms.Label label2;
      private System.Windows.Forms.Label label3;
      private System.Windows.Forms.Label label4;
		public System.Windows.Forms.Label label_XCoordinateMax;
      private System.Windows.Forms.ComboBox comboBox_chanStart;
      private System.Windows.Forms.ComboBox comboBox_chanCount;
      private System.Windows.Forms.Label label_chanStart;
      private System.Windows.Forms.Label label_chanCount;
		private Automation.BDaq.InstantAiCtrl instantAiCtrl1;
      
   }
}

