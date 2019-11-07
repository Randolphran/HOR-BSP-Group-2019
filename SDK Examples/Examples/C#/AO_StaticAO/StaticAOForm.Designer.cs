namespace AO_StaticAO
{
    partial class StaticAOForm
    {
        private System.ComponentModel.IContainer components = null;
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 

        private void InitializeComponent()
        {
           this.components = new System.ComponentModel.Container();
           System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(StaticAOForm));
           this.checkBox_triangleA = new System.Windows.Forms.CheckBox();
           this.trackBar_Scroll = new System.Windows.Forms.TrackBar();
           this.checkBox_squareA = new System.Windows.Forms.CheckBox();
           this.checkBox_sineA = new System.Windows.Forms.CheckBox();
           this.checkBox_sineB = new System.Windows.Forms.CheckBox();
           this.checkBox_squareB = new System.Windows.Forms.CheckBox();
           this.checkBox_triangleB = new System.Windows.Forms.CheckBox();
           this.timer_outputData = new System.Windows.Forms.Timer(this.components);
           this.textBox_valueA = new System.Windows.Forms.TextBox();
           this.textBox_valueB = new System.Windows.Forms.TextBox();
           this.textBox_highLevelA = new System.Windows.Forms.TextBox();
           this.textBox_lowLevelA = new System.Windows.Forms.TextBox();
           this.textBox_highLevelB = new System.Windows.Forms.TextBox();
           this.textBox_lowLevelB = new System.Windows.Forms.TextBox();
           this.label_chanB = new System.Windows.Forms.Label();
           this.label_chanA = new System.Windows.Forms.Label();
           this.label_interval = new System.Windows.Forms.Label();
           this.button_manualA = new System.Windows.Forms.Button();
           this.button_manualB = new System.Windows.Forms.Button();
           this.imageList = new System.Windows.Forms.ImageList(this.components);
           this.m_instantAoCtrl = new Automation.BDaq.InstantAoCtrl(this.components);
           this.label1 = new System.Windows.Forms.Label();
           ((System.ComponentModel.ISupportInitialize)(this.trackBar_Scroll)).BeginInit();
           this.SuspendLayout();
           // 
           // checkBox_triangleA
           // 
           this.checkBox_triangleA.Appearance = System.Windows.Forms.Appearance.Button;
           this.checkBox_triangleA.BackColor = System.Drawing.Color.Transparent;
           this.checkBox_triangleA.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("checkBox_triangleA.BackgroundImage")));
           this.checkBox_triangleA.CheckAlign = System.Drawing.ContentAlignment.TopCenter;
           this.checkBox_triangleA.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
           this.checkBox_triangleA.Location = new System.Drawing.Point(197, 123);
           this.checkBox_triangleA.Margin = new System.Windows.Forms.Padding(1);
           this.checkBox_triangleA.Name = "checkBox_triangleA";
           this.checkBox_triangleA.Size = new System.Drawing.Size(53, 50);
           this.checkBox_triangleA.TabIndex = 0;
           this.checkBox_triangleA.UseVisualStyleBackColor = false;
           this.checkBox_triangleA.MouseClick += new System.Windows.Forms.MouseEventHandler(this.checkBox_AoDataOut_MouseClick);
           // 
           // trackBar_Scroll
           // 
           this.trackBar_Scroll.AutoSize = false;
           this.trackBar_Scroll.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(236)))), ((int)(((byte)(233)))), ((int)(((byte)(216)))));
           this.trackBar_Scroll.Location = new System.Drawing.Point(150, 400);
           this.trackBar_Scroll.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.trackBar_Scroll.Maximum = 1000;
           this.trackBar_Scroll.Minimum = 10;
           this.trackBar_Scroll.Name = "trackBar_Scroll";
           this.trackBar_Scroll.Size = new System.Drawing.Size(119, 23);
           this.trackBar_Scroll.TabIndex = 24;
           this.trackBar_Scroll.TickFrequency = 100;
           this.trackBar_Scroll.Value = 50;
           this.trackBar_Scroll.Scroll += new System.EventHandler(this.trackBar_Scroll_Scroll);
           // 
           // checkBox_squareA
           // 
           this.checkBox_squareA.Appearance = System.Windows.Forms.Appearance.Button;
           this.checkBox_squareA.BackColor = System.Drawing.Color.Transparent;
           this.checkBox_squareA.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("checkBox_squareA.BackgroundImage")));
           this.checkBox_squareA.CheckAlign = System.Drawing.ContentAlignment.TopCenter;
           this.checkBox_squareA.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
           this.checkBox_squareA.Location = new System.Drawing.Point(131, 123);
           this.checkBox_squareA.Margin = new System.Windows.Forms.Padding(1);
           this.checkBox_squareA.Name = "checkBox_squareA";
           this.checkBox_squareA.Size = new System.Drawing.Size(53, 50);
           this.checkBox_squareA.TabIndex = 28;
           this.checkBox_squareA.UseVisualStyleBackColor = false;
           this.checkBox_squareA.MouseClick += new System.Windows.Forms.MouseEventHandler(this.checkBox_AoDataOut_MouseClick);
           // 
           // checkBox_sineA
           // 
           this.checkBox_sineA.Appearance = System.Windows.Forms.Appearance.Button;
           this.checkBox_sineA.BackColor = System.Drawing.Color.Transparent;
           this.checkBox_sineA.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("checkBox_sineA.BackgroundImage")));
           this.checkBox_sineA.CheckAlign = System.Drawing.ContentAlignment.TopCenter;
           this.checkBox_sineA.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
           this.checkBox_sineA.Location = new System.Drawing.Point(63, 123);
           this.checkBox_sineA.Margin = new System.Windows.Forms.Padding(1);
           this.checkBox_sineA.Name = "checkBox_sineA";
           this.checkBox_sineA.Size = new System.Drawing.Size(53, 50);
           this.checkBox_sineA.TabIndex = 29;
           this.checkBox_sineA.UseVisualStyleBackColor = false;
           this.checkBox_sineA.MouseClick += new System.Windows.Forms.MouseEventHandler(this.checkBox_AoDataOut_MouseClick);
           // 
           // checkBox_sineB
           // 
           this.checkBox_sineB.Appearance = System.Windows.Forms.Appearance.Button;
           this.checkBox_sineB.BackColor = System.Drawing.Color.Transparent;
           this.checkBox_sineB.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("checkBox_sineB.BackgroundImage")));
           this.checkBox_sineB.CheckAlign = System.Drawing.ContentAlignment.TopCenter;
           this.checkBox_sineB.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
           this.checkBox_sineB.Location = new System.Drawing.Point(63, 301);
           this.checkBox_sineB.Margin = new System.Windows.Forms.Padding(1);
           this.checkBox_sineB.Name = "checkBox_sineB";
           this.checkBox_sineB.Size = new System.Drawing.Size(53, 50);
           this.checkBox_sineB.TabIndex = 32;
           this.checkBox_sineB.UseVisualStyleBackColor = false;
           this.checkBox_sineB.MouseClick += new System.Windows.Forms.MouseEventHandler(this.checkBox_AoDataOut_MouseClick);
           // 
           // checkBox_squareB
           // 
           this.checkBox_squareB.Appearance = System.Windows.Forms.Appearance.Button;
           this.checkBox_squareB.BackColor = System.Drawing.Color.Transparent;
           this.checkBox_squareB.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("checkBox_squareB.BackgroundImage")));
           this.checkBox_squareB.CheckAlign = System.Drawing.ContentAlignment.TopCenter;
           this.checkBox_squareB.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
           this.checkBox_squareB.Location = new System.Drawing.Point(131, 301);
           this.checkBox_squareB.Margin = new System.Windows.Forms.Padding(1);
           this.checkBox_squareB.Name = "checkBox_squareB";
           this.checkBox_squareB.Size = new System.Drawing.Size(53, 50);
           this.checkBox_squareB.TabIndex = 31;
           this.checkBox_squareB.UseVisualStyleBackColor = false;
           this.checkBox_squareB.MouseClick += new System.Windows.Forms.MouseEventHandler(this.checkBox_AoDataOut_MouseClick);
           // 
           // checkBox_triangleB
           // 
           this.checkBox_triangleB.Appearance = System.Windows.Forms.Appearance.Button;
           this.checkBox_triangleB.BackColor = System.Drawing.Color.Transparent;
           this.checkBox_triangleB.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("checkBox_triangleB.BackgroundImage")));
           this.checkBox_triangleB.CheckAlign = System.Drawing.ContentAlignment.TopCenter;
           this.checkBox_triangleB.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
           this.checkBox_triangleB.Location = new System.Drawing.Point(197, 301);
           this.checkBox_triangleB.Margin = new System.Windows.Forms.Padding(1);
           this.checkBox_triangleB.Name = "checkBox_triangleB";
           this.checkBox_triangleB.Size = new System.Drawing.Size(53, 50);
           this.checkBox_triangleB.TabIndex = 30;
           this.checkBox_triangleB.UseVisualStyleBackColor = false;
           this.checkBox_triangleB.MouseClick += new System.Windows.Forms.MouseEventHandler(this.checkBox_AoDataOut_MouseClick);
           // 
           // timer_outputData
           // 
           this.timer_outputData.Tick += new System.EventHandler(this.timer_outputData_Tick);
           // 
           // textBox_valueA
           // 
           this.textBox_valueA.BackColor = System.Drawing.SystemColors.HighlightText;
           this.textBox_valueA.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.textBox_valueA.ForeColor = System.Drawing.SystemColors.ControlText;
           this.textBox_valueA.Location = new System.Drawing.Point(278, 89);
           this.textBox_valueA.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.textBox_valueA.Name = "textBox_valueA";
           this.textBox_valueA.Size = new System.Drawing.Size(65, 21);
           this.textBox_valueA.TabIndex = 36;
           this.textBox_valueA.Text = "2.5";
           this.textBox_valueA.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // textBox_valueB
           // 
           this.textBox_valueB.BackColor = System.Drawing.SystemColors.HighlightText;
           this.textBox_valueB.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.textBox_valueB.ForeColor = System.Drawing.SystemColors.ControlText;
           this.textBox_valueB.Location = new System.Drawing.Point(278, 267);
           this.textBox_valueB.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.textBox_valueB.Name = "textBox_valueB";
           this.textBox_valueB.Size = new System.Drawing.Size(65, 21);
           this.textBox_valueB.TabIndex = 37;
           this.textBox_valueB.Text = "2.5";
           this.textBox_valueB.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // textBox_highLevelA
           // 
           this.textBox_highLevelA.BackColor = System.Drawing.SystemColors.HighlightText;
           this.textBox_highLevelA.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.textBox_highLevelA.ForeColor = System.Drawing.SystemColors.ControlText;
           this.textBox_highLevelA.Location = new System.Drawing.Point(74, 89);
           this.textBox_highLevelA.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.textBox_highLevelA.Name = "textBox_highLevelA";
           this.textBox_highLevelA.Size = new System.Drawing.Size(74, 21);
           this.textBox_highLevelA.TabIndex = 38;
           this.textBox_highLevelA.Text = "5";
           this.textBox_highLevelA.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // textBox_lowLevelA
           // 
           this.textBox_lowLevelA.BackColor = System.Drawing.SystemColors.HighlightText;
           this.textBox_lowLevelA.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.textBox_lowLevelA.ForeColor = System.Drawing.SystemColors.ControlText;
           this.textBox_lowLevelA.Location = new System.Drawing.Point(164, 89);
           this.textBox_lowLevelA.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.textBox_lowLevelA.Name = "textBox_lowLevelA";
           this.textBox_lowLevelA.Size = new System.Drawing.Size(74, 21);
           this.textBox_lowLevelA.TabIndex = 39;
           this.textBox_lowLevelA.Text = "-5";
           this.textBox_lowLevelA.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // textBox_highLevelB
           // 
           this.textBox_highLevelB.BackColor = System.Drawing.SystemColors.HighlightText;
           this.textBox_highLevelB.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.textBox_highLevelB.ForeColor = System.Drawing.SystemColors.ControlText;
           this.textBox_highLevelB.Location = new System.Drawing.Point(74, 267);
           this.textBox_highLevelB.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.textBox_highLevelB.Name = "textBox_highLevelB";
           this.textBox_highLevelB.Size = new System.Drawing.Size(74, 21);
           this.textBox_highLevelB.TabIndex = 40;
           this.textBox_highLevelB.Text = "5";
           this.textBox_highLevelB.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // textBox_lowLevelB
           // 
           this.textBox_lowLevelB.BackColor = System.Drawing.SystemColors.HighlightText;
           this.textBox_lowLevelB.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.textBox_lowLevelB.ForeColor = System.Drawing.SystemColors.ControlText;
           this.textBox_lowLevelB.Location = new System.Drawing.Point(164, 267);
           this.textBox_lowLevelB.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.textBox_lowLevelB.Name = "textBox_lowLevelB";
           this.textBox_lowLevelB.Size = new System.Drawing.Size(74, 21);
           this.textBox_lowLevelB.TabIndex = 41;
           this.textBox_lowLevelB.Text = "-5";
           this.textBox_lowLevelB.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // label_chanB
           // 
           this.label_chanB.AutoSize = true;
           this.label_chanB.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.label_chanB.ForeColor = System.Drawing.Color.BurlyWood;
           this.label_chanB.Image = ((System.Drawing.Image)(resources.GetObject("label_chanB.Image")));
           this.label_chanB.Location = new System.Drawing.Point(284, 211);
           this.label_chanB.Name = "label_chanB";
           this.label_chanB.Size = new System.Drawing.Size(15, 15);
           this.label_chanB.TabIndex = 43;
           this.label_chanB.Text = "1";
           // 
           // label_chanA
           // 
           this.label_chanA.AutoSize = true;
           this.label_chanA.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.label_chanA.ForeColor = System.Drawing.Color.BurlyWood;
           this.label_chanA.Image = ((System.Drawing.Image)(resources.GetObject("label_chanA.Image")));
           this.label_chanA.Location = new System.Drawing.Point(281, 33);
           this.label_chanA.Name = "label_chanA";
           this.label_chanA.Size = new System.Drawing.Size(15, 15);
           this.label_chanA.TabIndex = 44;
           this.label_chanA.Text = "0";
           // 
           // label_interval
           // 
           this.label_interval.AutoSize = true;
           this.label_interval.ForeColor = System.Drawing.SystemColors.ControlText;
           this.label_interval.Image = ((System.Drawing.Image)(resources.GetObject("label_interval.Image")));
           this.label_interval.Location = new System.Drawing.Point(277, 402);
           this.label_interval.Name = "label_interval";
           this.label_interval.Size = new System.Drawing.Size(38, 15);
           this.label_interval.TabIndex = 45;
           this.label_interval.Text = "50ms";
           // 
           // button_manualA
           // 
           this.button_manualA.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("button_manualA.BackgroundImage")));
           this.button_manualA.Location = new System.Drawing.Point(287, 123);
           this.button_manualA.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.button_manualA.Name = "button_manualA";
           this.button_manualA.Size = new System.Drawing.Size(53, 50);
           this.button_manualA.TabIndex = 46;
           this.button_manualA.UseVisualStyleBackColor = true;
           this.button_manualA.Click += new System.EventHandler(this.button_manualA_Click);
           // 
           // button_manualB
           // 
           this.button_manualB.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("button_manualB.BackgroundImage")));
           this.button_manualB.Location = new System.Drawing.Point(287, 301);
           this.button_manualB.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.button_manualB.Name = "button_manualB";
           this.button_manualB.Size = new System.Drawing.Size(53, 50);
           this.button_manualB.TabIndex = 47;
           this.button_manualB.UseVisualStyleBackColor = true;
           this.button_manualB.Click += new System.EventHandler(this.button_manualB_Click);
           // 
           // imageList
           // 
           this.imageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList.ImageStream")));
           this.imageList.TransparentColor = System.Drawing.Color.Transparent;
           this.imageList.Images.SetKeyName(0, "sine.bmp");
           this.imageList.Images.SetKeyName(1, "square.bmp");
           this.imageList.Images.SetKeyName(2, "triangle.bmp");
           this.imageList.Images.SetKeyName(3, "sine_down.bmp");
           this.imageList.Images.SetKeyName(4, "square_down.bmp");
           this.imageList.Images.SetKeyName(5, "triangle_down.bmp");
           // 
           // m_instantAoCtrl
           // 
           this.m_instantAoCtrl._StateStream = ((Automation.BDaq.DeviceStateStreamer)(resources.GetObject("m_instantAoCtrl._StateStream")));
           // 
           // label1
           // 
           this.label1.ForeColor = System.Drawing.SystemColors.ControlText;
           this.label1.Location = new System.Drawing.Point(83, 374);
           this.label1.Name = "label1";
           this.label1.Size = new System.Drawing.Size(244, 25);
           this.label1.TabIndex = 48;
           this.label1.Text = "The points number of each waveform is 32";
           // 
           // StaticAOForm
           // 
           this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
           this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
           this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
           this.ClientSize = new System.Drawing.Size(391, 451);
           this.Controls.Add(this.label1);
           this.Controls.Add(this.button_manualB);
           this.Controls.Add(this.button_manualA);
           this.Controls.Add(this.label_interval);
           this.Controls.Add(this.label_chanA);
           this.Controls.Add(this.label_chanB);
           this.Controls.Add(this.textBox_lowLevelB);
           this.Controls.Add(this.textBox_highLevelB);
           this.Controls.Add(this.textBox_lowLevelA);
           this.Controls.Add(this.textBox_highLevelA);
           this.Controls.Add(this.textBox_valueB);
           this.Controls.Add(this.textBox_valueA);
           this.Controls.Add(this.checkBox_sineB);
           this.Controls.Add(this.checkBox_squareB);
           this.Controls.Add(this.checkBox_triangleB);
           this.Controls.Add(this.checkBox_sineA);
           this.Controls.Add(this.checkBox_squareA);
           this.Controls.Add(this.checkBox_triangleA);
           this.Controls.Add(this.trackBar_Scroll);
           this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
           this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
           this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.MaximizeBox = false;
           this.MinimizeBox = false;
           this.Name = "StaticAOForm";
           this.Text = "Static AO";
           this.Load += new System.EventHandler(this.InstantAoForm_Load);
           ((System.ComponentModel.ISupportInitialize)(this.trackBar_Scroll)).EndInit();
           this.ResumeLayout(false);
           this.PerformLayout();

        }

        #endregion

       private System.Windows.Forms.CheckBox checkBox_triangleA;
       private System.Windows.Forms.TrackBar trackBar_Scroll;
       private System.Windows.Forms.CheckBox checkBox_squareA;
       private System.Windows.Forms.CheckBox checkBox_sineA;
       private System.Windows.Forms.CheckBox checkBox_sineB;
       private System.Windows.Forms.CheckBox checkBox_squareB;
       private System.Windows.Forms.CheckBox checkBox_triangleB;
       private System.Windows.Forms.Timer timer_outputData;
       private System.Windows.Forms.TextBox textBox_valueA;
       private System.Windows.Forms.TextBox textBox_valueB;
       private System.Windows.Forms.TextBox textBox_highLevelA;
       private System.Windows.Forms.TextBox textBox_lowLevelA;
       private System.Windows.Forms.TextBox textBox_highLevelB;
       private System.Windows.Forms.TextBox textBox_lowLevelB;
       private System.Windows.Forms.Label label_chanB;
       private System.Windows.Forms.Label label_chanA;
       private System.Windows.Forms.Label label_interval;
       private System.Windows.Forms.Button button_manualA;
       private System.Windows.Forms.Button button_manualB;
       private System.Windows.Forms.ImageList imageList;
       private Automation.BDaq.InstantAoCtrl m_instantAoCtrl;
		 private System.Windows.Forms.Label label1;
 
    }
}

