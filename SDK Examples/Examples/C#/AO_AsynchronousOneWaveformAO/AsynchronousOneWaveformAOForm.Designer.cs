namespace AO_AsynchronousOneWaveformAO
{
    partial class AsynchronousOneWaveformAOForm
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
           System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AsynchronousOneWaveformAOForm));
           this.checkBox_triangleA = new System.Windows.Forms.CheckBox();
           this.checkBox_squareA = new System.Windows.Forms.CheckBox();
           this.checkBox_sineA = new System.Windows.Forms.CheckBox();
           this.checkBox_sineB = new System.Windows.Forms.CheckBox();
           this.checkBox_squareB = new System.Windows.Forms.CheckBox();
           this.checkBox_triangleB = new System.Windows.Forms.CheckBox();
           this.textBox_highLevelA = new System.Windows.Forms.TextBox();
           this.textBox_lowLevelA = new System.Windows.Forms.TextBox();
           this.textBox_highLevelB = new System.Windows.Forms.TextBox();
           this.textBox_lowLevelB = new System.Windows.Forms.TextBox();
           this.label_chanB = new System.Windows.Forms.Label();
           this.label_chanA = new System.Windows.Forms.Label();
           this.button_start = new System.Windows.Forms.Button();
           this.imageList = new System.Windows.Forms.ImageList(this.components);
           this.m_bufferedAoCtrl = new Automation.BDaq.BufferedAoCtrl(this.components);
           this.SuspendLayout();
           // 
           // checkBox_triangleA
           // 
           this.checkBox_triangleA.Appearance = System.Windows.Forms.Appearance.Button;
           this.checkBox_triangleA.BackColor = System.Drawing.Color.Transparent;
           this.checkBox_triangleA.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("checkBox_triangleA.BackgroundImage")));
           this.checkBox_triangleA.CheckAlign = System.Drawing.ContentAlignment.TopCenter;
           this.checkBox_triangleA.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
           this.checkBox_triangleA.Location = new System.Drawing.Point(226, 120);
           this.checkBox_triangleA.Margin = new System.Windows.Forms.Padding(1);
           this.checkBox_triangleA.Name = "checkBox_triangleA";
           this.checkBox_triangleA.Size = new System.Drawing.Size(53, 50);
           this.checkBox_triangleA.TabIndex = 3;
           this.checkBox_triangleA.UseVisualStyleBackColor = false;
           this.checkBox_triangleA.MouseClick += new System.Windows.Forms.MouseEventHandler(this.checkBox_AoDataOut_MouseClick);
           // 
           // checkBox_squareA
           // 
           this.checkBox_squareA.Appearance = System.Windows.Forms.Appearance.Button;
           this.checkBox_squareA.BackColor = System.Drawing.Color.Transparent;
           this.checkBox_squareA.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("checkBox_squareA.BackgroundImage")));
           this.checkBox_squareA.CheckAlign = System.Drawing.ContentAlignment.TopCenter;
           this.checkBox_squareA.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
           this.checkBox_squareA.Location = new System.Drawing.Point(146, 120);
           this.checkBox_squareA.Margin = new System.Windows.Forms.Padding(1);
           this.checkBox_squareA.Name = "checkBox_squareA";
           this.checkBox_squareA.Size = new System.Drawing.Size(53, 50);
           this.checkBox_squareA.TabIndex = 2;
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
           this.checkBox_sineA.Location = new System.Drawing.Point(68, 120);
           this.checkBox_sineA.Margin = new System.Windows.Forms.Padding(1);
           this.checkBox_sineA.Name = "checkBox_sineA";
           this.checkBox_sineA.Size = new System.Drawing.Size(53, 50);
           this.checkBox_sineA.TabIndex = 1;
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
           this.checkBox_sineB.Location = new System.Drawing.Point(68, 306);
           this.checkBox_sineB.Margin = new System.Windows.Forms.Padding(1);
           this.checkBox_sineB.Name = "checkBox_sineB";
           this.checkBox_sineB.Size = new System.Drawing.Size(53, 50);
           this.checkBox_sineB.TabIndex = 4;
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
           this.checkBox_squareB.Location = new System.Drawing.Point(146, 306);
           this.checkBox_squareB.Margin = new System.Windows.Forms.Padding(1);
           this.checkBox_squareB.Name = "checkBox_squareB";
           this.checkBox_squareB.Size = new System.Drawing.Size(53, 50);
           this.checkBox_squareB.TabIndex = 5;
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
           this.checkBox_triangleB.Location = new System.Drawing.Point(226, 306);
           this.checkBox_triangleB.Margin = new System.Windows.Forms.Padding(1);
           this.checkBox_triangleB.Name = "checkBox_triangleB";
           this.checkBox_triangleB.Size = new System.Drawing.Size(53, 50);
           this.checkBox_triangleB.TabIndex = 6;
           this.checkBox_triangleB.UseVisualStyleBackColor = false;
           this.checkBox_triangleB.MouseClick += new System.Windows.Forms.MouseEventHandler(this.checkBox_AoDataOut_MouseClick);
           // 
           // textBox_highLevelA
           // 
           this.textBox_highLevelA.BackColor = System.Drawing.SystemColors.HighlightText;
           this.textBox_highLevelA.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.textBox_highLevelA.ForeColor = System.Drawing.SystemColors.ControlText;
           this.textBox_highLevelA.Location = new System.Drawing.Point(81, 89);
           this.textBox_highLevelA.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.textBox_highLevelA.Name = "textBox_highLevelA";
           this.textBox_highLevelA.Size = new System.Drawing.Size(75, 21);
           this.textBox_highLevelA.TabIndex = 7;
           this.textBox_highLevelA.Text = "5";
           this.textBox_highLevelA.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // textBox_lowLevelA
           // 
           this.textBox_lowLevelA.BackColor = System.Drawing.SystemColors.HighlightText;
           this.textBox_lowLevelA.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.textBox_lowLevelA.ForeColor = System.Drawing.SystemColors.ControlText;
           this.textBox_lowLevelA.Location = new System.Drawing.Point(192, 88);
           this.textBox_lowLevelA.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.textBox_lowLevelA.Name = "textBox_lowLevelA";
           this.textBox_lowLevelA.Size = new System.Drawing.Size(75, 21);
           this.textBox_lowLevelA.TabIndex = 8;
           this.textBox_lowLevelA.Text = "-5";
           this.textBox_lowLevelA.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // textBox_highLevelB
           // 
           this.textBox_highLevelB.BackColor = System.Drawing.SystemColors.HighlightText;
           this.textBox_highLevelB.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.textBox_highLevelB.ForeColor = System.Drawing.SystemColors.ControlText;
           this.textBox_highLevelB.Location = new System.Drawing.Point(81, 274);
           this.textBox_highLevelB.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.textBox_highLevelB.Name = "textBox_highLevelB";
           this.textBox_highLevelB.Size = new System.Drawing.Size(75, 21);
           this.textBox_highLevelB.TabIndex = 9;
           this.textBox_highLevelB.Text = "5";
           this.textBox_highLevelB.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // textBox_lowLevelB
           // 
           this.textBox_lowLevelB.BackColor = System.Drawing.SystemColors.HighlightText;
           this.textBox_lowLevelB.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.textBox_lowLevelB.ForeColor = System.Drawing.SystemColors.ControlText;
           this.textBox_lowLevelB.Location = new System.Drawing.Point(192, 273);
           this.textBox_lowLevelB.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.textBox_lowLevelB.Name = "textBox_lowLevelB";
           this.textBox_lowLevelB.Size = new System.Drawing.Size(75, 21);
           this.textBox_lowLevelB.TabIndex = 10;
           this.textBox_lowLevelB.Text = "-5";
           this.textBox_lowLevelB.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
           // 
           // label_chanB
           // 
           this.label_chanB.AutoSize = true;
           this.label_chanB.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.label_chanB.ForeColor = System.Drawing.Color.BurlyWood;
           this.label_chanB.Image = ((System.Drawing.Image)(resources.GetObject("label_chanB.Image")));
           this.label_chanB.Location = new System.Drawing.Point(241, 216);
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
           this.label_chanA.Location = new System.Drawing.Point(241, 31);
           this.label_chanA.Name = "label_chanA";
           this.label_chanA.Size = new System.Drawing.Size(15, 15);
           this.label_chanA.TabIndex = 44;
           this.label_chanA.Text = "0";
           // 
           // button_start
           // 
           this.button_start.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.button_start.ForeColor = System.Drawing.SystemColors.ControlText;
           this.button_start.Location = new System.Drawing.Point(196, 390);
           this.button_start.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.button_start.Name = "button_start";
           this.button_start.Size = new System.Drawing.Size(90, 28);
           this.button_start.TabIndex = 0;
           this.button_start.Text = "Start";
           this.button_start.UseVisualStyleBackColor = true;
           this.button_start.Click += new System.EventHandler(this.button_start_Click);
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
           // m_bufferedAoCtrl
           // 
           this.m_bufferedAoCtrl._StateStream = ((Automation.BDaq.DeviceStateStreamer)(resources.GetObject("m_bufferedAoCtrl._StateStream")));
           this.m_bufferedAoCtrl.Stopped += new System.EventHandler<Automation.BDaq.BfdAoEventArgs>(this.m_bufferedAoCtrl_Stopped);
           // 
           // AsynchronousOneWaveformAOForm
           // 
           this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
           this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
           this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
           this.ClientSize = new System.Drawing.Size(350, 439);
           this.Controls.Add(this.button_start);
           this.Controls.Add(this.label_chanA);
           this.Controls.Add(this.label_chanB);
           this.Controls.Add(this.textBox_lowLevelB);
           this.Controls.Add(this.textBox_highLevelB);
           this.Controls.Add(this.textBox_lowLevelA);
           this.Controls.Add(this.textBox_highLevelA);
           this.Controls.Add(this.checkBox_sineB);
           this.Controls.Add(this.checkBox_squareB);
           this.Controls.Add(this.checkBox_triangleB);
           this.Controls.Add(this.checkBox_sineA);
           this.Controls.Add(this.checkBox_squareA);
           this.Controls.Add(this.checkBox_triangleA);
           this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
           this.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
           this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
           this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
           this.MaximizeBox = false;
           this.MinimizeBox = false;
           this.Name = "AsynchronousOneWaveformAOForm";
           this.Text = "Asynchronous One Waveform AO";
           this.Load += new System.EventHandler(this.AsynchronousOneWaveformAOForm_Load);
           this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.AsyncOneWaveOutAoForm_FormClosed);
           this.ResumeLayout(false);
           this.PerformLayout();

        }

        #endregion

       private System.Windows.Forms.CheckBox checkBox_triangleA;
       private System.Windows.Forms.CheckBox checkBox_squareA;
       private System.Windows.Forms.CheckBox checkBox_sineA;
       private System.Windows.Forms.CheckBox checkBox_sineB;
       private System.Windows.Forms.CheckBox checkBox_squareB;
       private System.Windows.Forms.CheckBox checkBox_triangleB;
       private System.Windows.Forms.TextBox textBox_highLevelA;
       private System.Windows.Forms.TextBox textBox_lowLevelA;
       private System.Windows.Forms.TextBox textBox_highLevelB;
       private System.Windows.Forms.TextBox textBox_lowLevelB;
       private System.Windows.Forms.Label label_chanB;
       private System.Windows.Forms.Label label_chanA;
       private System.Windows.Forms.Button button_start;
       private System.Windows.Forms.ImageList imageList;
       private Automation.BDaq.BufferedAoCtrl m_bufferedAoCtrl;

    }
}

