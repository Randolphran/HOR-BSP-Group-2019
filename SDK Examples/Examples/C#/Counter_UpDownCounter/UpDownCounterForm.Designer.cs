namespace Counter_UpDownCounter
{
    partial class UpDownCounterForm
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
           System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UpDownCounterForm));
           this.groupBox1 = new System.Windows.Forms.GroupBox();
           this.txtResetValue = new System.Windows.Forms.TextBox();
           this.label1 = new System.Windows.Forms.Label();
           this.cmbResetValue = new System.Windows.Forms.ComboBox();
           this.groupBox2 = new System.Windows.Forms.GroupBox();
           this.txtResetTimes = new System.Windows.Forms.TextBox();
           this.label2 = new System.Windows.Forms.Label();
           this.radFinite = new System.Windows.Forms.RadioButton();
           this.raInfinite = new System.Windows.Forms.RadioButton();
           this.radDisable = new System.Windows.Forms.RadioButton();
           this.groupBox3 = new System.Windows.Forms.GroupBox();
           this.btnStop = new System.Windows.Forms.Button();
           this.btnValReset = new System.Windows.Forms.Button();
           this.btnStart = new System.Windows.Forms.Button();
           this.CounterValueList = new System.Windows.Forms.ListBox();
           this.txtCounterValue = new System.Windows.Forms.TextBox();
           this.timer1 = new System.Windows.Forms.Timer(this.components);
           this.udCounterCtrl1 = new Automation.BDaq.UdCounterCtrl(this.components);
           this.groupBox1.SuspendLayout();
           this.groupBox2.SuspendLayout();
           this.groupBox3.SuspendLayout();
           this.SuspendLayout();
           // 
           // groupBox1
           // 
           this.groupBox1.Controls.Add(this.txtResetValue);
           this.groupBox1.Controls.Add(this.label1);
           this.groupBox1.Controls.Add(this.cmbResetValue);
           this.groupBox1.Location = new System.Drawing.Point(10, 41);
           this.groupBox1.Name = "groupBox1";
           this.groupBox1.Size = new System.Drawing.Size(190, 87);
           this.groupBox1.TabIndex = 0;
           this.groupBox1.TabStop = false;
           this.groupBox1.Text = "Reset Value";
           // 
           // txtResetValue
           // 
           this.txtResetValue.Enabled = false;
           this.txtResetValue.Location = new System.Drawing.Point(79, 54);
           this.txtResetValue.Name = "txtResetValue";
           this.txtResetValue.Size = new System.Drawing.Size(104, 21);
           this.txtResetValue.TabIndex = 2;
           // 
           // label1
           // 
           this.label1.AutoSize = true;
           this.label1.Location = new System.Drawing.Point(3, 22);
           this.label1.Name = "label1";
           this.label1.Size = new System.Drawing.Size(76, 15);
           this.label1.TabIndex = 1;
           this.label1.Text = "Reset Value:";
           // 
           // cmbResetValue
           // 
           this.cmbResetValue.FormattingEnabled = true;
           this.cmbResetValue.Location = new System.Drawing.Point(79, 20);
           this.cmbResetValue.Name = "cmbResetValue";
           this.cmbResetValue.Size = new System.Drawing.Size(105, 23);
           this.cmbResetValue.TabIndex = 0;
           this.cmbResetValue.SelectedIndexChanged += new System.EventHandler(this.cmbResetValue_SelectedIndexChanged);
           // 
           // groupBox2
           // 
           this.groupBox2.Controls.Add(this.txtResetTimes);
           this.groupBox2.Controls.Add(this.label2);
           this.groupBox2.Controls.Add(this.radFinite);
           this.groupBox2.Controls.Add(this.raInfinite);
           this.groupBox2.Controls.Add(this.radDisable);
           this.groupBox2.Location = new System.Drawing.Point(11, 132);
           this.groupBox2.Name = "groupBox2";
           this.groupBox2.Size = new System.Drawing.Size(188, 161);
           this.groupBox2.TabIndex = 1;
           this.groupBox2.TabStop = false;
           this.groupBox2.Text = "Index Reset";
           // 
           // txtResetTimes
           // 
           this.txtResetTimes.Enabled = false;
           this.txtResetTimes.Location = new System.Drawing.Point(93, 125);
           this.txtResetTimes.Name = "txtResetTimes";
           this.txtResetTimes.Size = new System.Drawing.Size(89, 21);
           this.txtResetTimes.TabIndex = 4;
           // 
           // label2
           // 
           this.label2.AutoSize = true;
           this.label2.Location = new System.Drawing.Point(13, 125);
           this.label2.Name = "label2";
           this.label2.Size = new System.Drawing.Size(79, 15);
           this.label2.TabIndex = 3;
           this.label2.Text = "Reset Times:";
           // 
           // radFinite
           // 
           this.radFinite.AutoSize = true;
           this.radFinite.Location = new System.Drawing.Point(16, 88);
           this.radFinite.Name = "radFinite";
           this.radFinite.Size = new System.Drawing.Size(55, 19);
           this.radFinite.TabIndex = 2;
           this.radFinite.TabStop = true;
           this.radFinite.Text = "Finite";
           this.radFinite.UseVisualStyleBackColor = true;
           this.radFinite.Click += new System.EventHandler(this.radFinite_Click);
           // 
           // raInfinite
           // 
           this.raInfinite.AutoSize = true;
           this.raInfinite.Location = new System.Drawing.Point(16, 60);
           this.raInfinite.Name = "raInfinite";
           this.raInfinite.Size = new System.Drawing.Size(61, 19);
           this.raInfinite.TabIndex = 1;
           this.raInfinite.TabStop = true;
           this.raInfinite.Text = "Infinite";
           this.raInfinite.UseVisualStyleBackColor = true;
           this.raInfinite.Click += new System.EventHandler(this.raInfinite_Click);
           // 
           // radDisable
           // 
           this.radDisable.AutoSize = true;
           this.radDisable.Location = new System.Drawing.Point(16, 34);
           this.radDisable.Name = "radDisable";
           this.radDisable.Size = new System.Drawing.Size(67, 19);
           this.radDisable.TabIndex = 0;
           this.radDisable.TabStop = true;
           this.radDisable.Text = "Disable";
           this.radDisable.UseVisualStyleBackColor = true;
           this.radDisable.Click += new System.EventHandler(this.radDisable_Click);
           // 
           // groupBox3
           // 
           this.groupBox3.Controls.Add(this.btnStop);
           this.groupBox3.Controls.Add(this.btnValReset);
           this.groupBox3.Controls.Add(this.btnStart);
           this.groupBox3.Controls.Add(this.CounterValueList);
           this.groupBox3.Controls.Add(this.txtCounterValue);
           this.groupBox3.Location = new System.Drawing.Point(212, 41);
           this.groupBox3.Name = "groupBox3";
           this.groupBox3.Size = new System.Drawing.Size(300, 251);
           this.groupBox3.TabIndex = 2;
           this.groupBox3.TabStop = false;
           // 
           // btnStop
           // 
           this.btnStop.Location = new System.Drawing.Point(189, 106);
           this.btnStop.Name = "btnStop";
           this.btnStop.Size = new System.Drawing.Size(90, 25);
           this.btnStop.TabIndex = 4;
           this.btnStop.Text = "Stop";
           this.btnStop.UseVisualStyleBackColor = true;
           this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
           // 
           // btnValReset
           // 
           this.btnValReset.Location = new System.Drawing.Point(189, 173);
           this.btnValReset.Name = "btnValReset";
           this.btnValReset.Size = new System.Drawing.Size(90, 25);
           this.btnValReset.TabIndex = 3;
           this.btnValReset.Text = "ValueReset";
           this.btnValReset.UseVisualStyleBackColor = true;
           this.btnValReset.Click += new System.EventHandler(this.btnValReset_Click);
           // 
           // btnStart
           // 
           this.btnStart.Location = new System.Drawing.Point(189, 52);
           this.btnStart.Name = "btnStart";
           this.btnStart.Size = new System.Drawing.Size(90, 25);
           this.btnStart.TabIndex = 2;
           this.btnStart.Text = "Start";
           this.btnStart.UseVisualStyleBackColor = true;
           this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
           // 
           // CounterValueList
           // 
           this.CounterValueList.FormattingEnabled = true;
           this.CounterValueList.ItemHeight = 15;
           this.CounterValueList.Location = new System.Drawing.Point(9, 54);
           this.CounterValueList.Name = "CounterValueList";
           this.CounterValueList.Size = new System.Drawing.Size(156, 184);
           this.CounterValueList.TabIndex = 1;
           // 
           // txtCounterValue
           // 
           this.txtCounterValue.Location = new System.Drawing.Point(9, 23);
           this.txtCounterValue.Name = "txtCounterValue";
           this.txtCounterValue.Size = new System.Drawing.Size(157, 21);
           this.txtCounterValue.TabIndex = 0;
           // 
           // timer1
           // 
           this.timer1.Interval = 50;
           this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
           // 
           // udCounterCtrl1
           // 
           this.udCounterCtrl1._StateStream = ((Automation.BDaq.DeviceStateStreamer)(resources.GetObject("udCounterCtrl1._StateStream")));
           // 
           // UpDownCounterForm
           // 
           this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
           this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
           this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
           this.ClientSize = new System.Drawing.Size(524, 314);
           this.Controls.Add(this.groupBox3);
           this.Controls.Add(this.groupBox2);
           this.Controls.Add(this.groupBox1);
           this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
           this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
           this.MaximizeBox = false;
           this.MinimizeBox = false;
           this.Name = "UpDownCounterForm";
           this.Text = "UpDownCounter";
           this.Load += new System.EventHandler(this.UpDownCounterForm_Load);
           this.groupBox1.ResumeLayout(false);
           this.groupBox1.PerformLayout();
           this.groupBox2.ResumeLayout(false);
           this.groupBox2.PerformLayout();
           this.groupBox3.ResumeLayout(false);
           this.groupBox3.PerformLayout();
           this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ComboBox cmbResetValue;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtResetValue;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.RadioButton radFinite;
        private System.Windows.Forms.RadioButton raInfinite;
        private System.Windows.Forms.RadioButton radDisable;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtResetTimes;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ListBox CounterValueList;
        private System.Windows.Forms.TextBox txtCounterValue;
        private System.Windows.Forms.Button btnStop;
        private System.Windows.Forms.Button btnValReset;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Timer timer1;
        private Automation.BDaq.UdCounterCtrl udCounterCtrl1;
    }
}

