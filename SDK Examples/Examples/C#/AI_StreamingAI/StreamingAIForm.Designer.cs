namespace AI_StreamingAI
{
   partial class StreamingAIForm
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
         System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(StreamingAIForm));
         this.pictureBox = new System.Windows.Forms.PictureBox();
         this.trackBar_div = new System.Windows.Forms.TrackBar();
         this.button_stop = new System.Windows.Forms.Button();
         this.button_pause = new System.Windows.Forms.Button();
         this.button_start = new System.Windows.Forms.Button();
         this.listView = new System.Windows.Forms.ListView();
         this.label1 = new System.Windows.Forms.Label();
         this.label_YCoordinateMin = new System.Windows.Forms.Label();
         this.label_YCoordinateMax = new System.Windows.Forms.Label();
         this.label_YCoordinateMiddle = new System.Windows.Forms.Label();
         this.label_XCoordinateMin = new System.Windows.Forms.Label();
         this.label_XCoordinateMax = new System.Windows.Forms.Label();
         this.label2 = new System.Windows.Forms.Label();
         this.waveformAiCtrl1 = new Automation.BDaq.WaveformAiCtrl(this.components);
         ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.trackBar_div)).BeginInit();
         this.SuspendLayout();
         // 
         // pictureBox
         // 
         this.pictureBox.BackColor = System.Drawing.SystemColors.ControlText;
         this.pictureBox.Location = new System.Drawing.Point(53, 39);
         this.pictureBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.pictureBox.Name = "pictureBox";
         this.pictureBox.Size = new System.Drawing.Size(660, 340);
         this.pictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
         this.pictureBox.TabIndex = 1;
         this.pictureBox.TabStop = false;
         // 
         // trackBar_div
         // 
         this.trackBar_div.AutoSize = false;
         this.trackBar_div.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
         this.trackBar_div.Location = new System.Drawing.Point(559, 404);
         this.trackBar_div.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.trackBar_div.Maximum = 1000;
         this.trackBar_div.Minimum = 10;
         this.trackBar_div.Name = "trackBar_div";
         this.trackBar_div.Size = new System.Drawing.Size(154, 23);
         this.trackBar_div.TabIndex = 15;
         this.trackBar_div.TickFrequency = 100;
         this.trackBar_div.Value = 100;
         this.trackBar_div.Scroll += new System.EventHandler(this.trackBar_div_Scroll);
         // 
         // button_stop
         // 
         this.button_stop.Location = new System.Drawing.Point(628, 450);
         this.button_stop.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.button_stop.Name = "button_stop";
         this.button_stop.Size = new System.Drawing.Size(76, 26);
         this.button_stop.TabIndex = 19;
         this.button_stop.Text = "Stop";
         this.button_stop.UseVisualStyleBackColor = true;
         this.button_stop.Click += new System.EventHandler(this.button_stop_Click);
         // 
         // button_pause
         // 
         this.button_pause.Location = new System.Drawing.Point(544, 450);
         this.button_pause.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.button_pause.Name = "button_pause";
         this.button_pause.Size = new System.Drawing.Size(76, 26);
         this.button_pause.TabIndex = 18;
         this.button_pause.Text = "Pause";
         this.button_pause.UseVisualStyleBackColor = true;
         this.button_pause.Click += new System.EventHandler(this.button_pause_Click);
         // 
         // button_start
         // 
         this.button_start.Location = new System.Drawing.Point(461, 450);
         this.button_start.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.button_start.Name = "button_start";
         this.button_start.Size = new System.Drawing.Size(76, 26);
         this.button_start.TabIndex = 17;
         this.button_start.Text = "Start";
         this.button_start.UseVisualStyleBackColor = true;
         this.button_start.Click += new System.EventHandler(this.button_start_Click);
         // 
         // listView
         // 
         this.listView.Location = new System.Drawing.Point(161, 396);
         this.listView.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.listView.Name = "listView";
         this.listView.Size = new System.Drawing.Size(352, 37);
         this.listView.TabIndex = 20;
         this.listView.UseCompatibleStateImageBehavior = false;
         // 
         // label1
         // 
         this.label1.AutoSize = true;
         this.label1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
         this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.label1.Location = new System.Drawing.Point(52, 404);
         this.label1.Name = "label1";
         this.label1.Size = new System.Drawing.Size(105, 15);
         this.label1.TabIndex = 21;
         this.label1.Text = "Color of channels:";
         // 
         // label_YCoordinateMin
         // 
         this.label_YCoordinateMin.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
         this.label_YCoordinateMin.Location = new System.Drawing.Point(-1, 361);
         this.label_YCoordinateMin.Name = "label_YCoordinateMin";
         this.label_YCoordinateMin.Size = new System.Drawing.Size(52, 15);
         this.label_YCoordinateMin.TabIndex = 27;
         this.label_YCoordinateMin.Text = "0V";
         this.label_YCoordinateMin.TextAlign = System.Drawing.ContentAlignment.TopRight;
         // 
         // label_YCoordinateMax
         // 
         this.label_YCoordinateMax.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
         this.label_YCoordinateMax.Location = new System.Drawing.Point(-2, 39);
         this.label_YCoordinateMax.Name = "label_YCoordinateMax";
         this.label_YCoordinateMax.Size = new System.Drawing.Size(52, 15);
         this.label_YCoordinateMax.TabIndex = 26;
         this.label_YCoordinateMax.Text = "5V";
         this.label_YCoordinateMax.TextAlign = System.Drawing.ContentAlignment.TopRight;
         // 
         // label_YCoordinateMiddle
         // 
         this.label_YCoordinateMiddle.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
         this.label_YCoordinateMiddle.Location = new System.Drawing.Point(-2, 184);
         this.label_YCoordinateMiddle.Name = "label_YCoordinateMiddle";
         this.label_YCoordinateMiddle.Size = new System.Drawing.Size(52, 15);
         this.label_YCoordinateMiddle.TabIndex = 28;
         this.label_YCoordinateMiddle.Text = "0V";
         this.label_YCoordinateMiddle.TextAlign = System.Drawing.ContentAlignment.TopRight;
         // 
         // label_XCoordinateMin
         // 
         this.label_XCoordinateMin.AutoSize = true;
         this.label_XCoordinateMin.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
         this.label_XCoordinateMin.Location = new System.Drawing.Point(52, 381);
         this.label_XCoordinateMin.Name = "label_XCoordinateMin";
         this.label_XCoordinateMin.Size = new System.Drawing.Size(38, 15);
         this.label_XCoordinateMin.TabIndex = 31;
         this.label_XCoordinateMin.Text = "0 Sec";
         // 
         // label_XCoordinateMax
         // 
         this.label_XCoordinateMax.AutoSize = true;
         this.label_XCoordinateMax.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
         this.label_XCoordinateMax.Location = new System.Drawing.Point(667, 381);
         this.label_XCoordinateMax.Name = "label_XCoordinateMax";
         this.label_XCoordinateMax.Size = new System.Drawing.Size(45, 15);
         this.label_XCoordinateMax.TabIndex = 30;
         this.label_XCoordinateMax.Text = "12 Sec";
         // 
         // label2
         // 
         this.label2.AutoSize = true;
         this.label2.Location = new System.Drawing.Point(527, 407);
         this.label2.Name = "label2";
         this.label2.Size = new System.Drawing.Size(27, 15);
         this.label2.TabIndex = 32;
         this.label2.Text = "Div:";
         // 
         // waveformAiCtrl1
         // 
         this.waveformAiCtrl1._StateStream = ((Automation.BDaq.DeviceStateStreamer)(resources.GetObject("waveformAiCtrl1._StateStream")));
         this.waveformAiCtrl1.Overrun += new System.EventHandler<Automation.BDaq.BfdAiEventArgs>(this.waveformAiCtrl1_Overrun);
         this.waveformAiCtrl1.CacheOverflow += new System.EventHandler<Automation.BDaq.BfdAiEventArgs>(this.waveformAiCtrl1_CacheOverflow);
         this.waveformAiCtrl1.DataReady += new System.EventHandler<Automation.BDaq.BfdAiEventArgs>(this.waveformAiCtrl1_DataReady);
         // 
         // StreamingAIForm
         // 
         this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
         this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
         this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
         this.ClientSize = new System.Drawing.Size(761, 496);
         this.Controls.Add(this.label2);
         this.Controls.Add(this.label_XCoordinateMin);
         this.Controls.Add(this.label_XCoordinateMax);
         this.Controls.Add(this.label_YCoordinateMin);
         this.Controls.Add(this.label_YCoordinateMax);
         this.Controls.Add(this.label_YCoordinateMiddle);
         this.Controls.Add(this.label1);
         this.Controls.Add(this.listView);
         this.Controls.Add(this.button_stop);
         this.Controls.Add(this.button_pause);
         this.Controls.Add(this.button_start);
         this.Controls.Add(this.trackBar_div);
         this.Controls.Add(this.pictureBox);
         this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
         this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.MaximizeBox = false;
         this.MinimizeBox = false;
         this.Name = "StreamingAIForm";
         this.Text = "Streaming AI";
         this.Load += new System.EventHandler(this.StreamingBufferedAiForm_Load);
         ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.trackBar_div)).EndInit();
         this.ResumeLayout(false);
         this.PerformLayout();

      }

      #endregion

      private System.Windows.Forms.PictureBox pictureBox;
      private System.Windows.Forms.TrackBar trackBar_div;
      private System.Windows.Forms.Button button_stop;
      private System.Windows.Forms.Button button_pause;
      private System.Windows.Forms.Button button_start;
      private System.Windows.Forms.ListView listView;
      private System.Windows.Forms.Label label1;
      private System.Windows.Forms.Label label_YCoordinateMin;
      private System.Windows.Forms.Label label_YCoordinateMax;
      private System.Windows.Forms.Label label_YCoordinateMiddle;
      private System.Windows.Forms.Label label_XCoordinateMin;
		private System.Windows.Forms.Label label_XCoordinateMax;
      private System.Windows.Forms.Label label2;
		private Automation.BDaq.WaveformAiCtrl waveformAiCtrl1;
   }
}

