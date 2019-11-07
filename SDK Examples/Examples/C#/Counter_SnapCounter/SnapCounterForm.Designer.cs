namespace Counter_SnapCounter
{
    partial class SnapCounterForm
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
           System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SnapCounterForm));
           this.groupBox1 = new System.Windows.Forms.GroupBox();
           this.label3 = new System.Windows.Forms.Label();
           this.txtTimeInterval = new System.Windows.Forms.TextBox();
           this.label2 = new System.Windows.Forms.Label();
           this.listSnapSource = new System.Windows.Forms.ListBox();
           this.label1 = new System.Windows.Forms.Label();
           this.label4 = new System.Windows.Forms.Label();
           this.txtSnapCount = new System.Windows.Forms.TextBox();
           this.groupBox3 = new System.Windows.Forms.GroupBox();
           this.btnStop = new System.Windows.Forms.Button();
           this.btnStart = new System.Windows.Forms.Button();
           this.CounterValueList = new System.Windows.Forms.ListBox();
           this.txtCounterValue = new System.Windows.Forms.TextBox();
           this.timer1 = new System.Windows.Forms.Timer(this.components);
           this.udCounterCtrl1 = new Automation.BDaq.UdCounterCtrl(this.components);
           this.groupBox1.SuspendLayout();
           this.groupBox3.SuspendLayout();
           this.SuspendLayout();
           // 
           // groupBox1
           // 
           this.groupBox1.Controls.Add(this.label3);
           this.groupBox1.Controls.Add(this.txtTimeInterval);
           this.groupBox1.Controls.Add(this.label2);
           this.groupBox1.Controls.Add(this.listSnapSource);
           this.groupBox1.Controls.Add(this.label1);
           this.groupBox1.Location = new System.Drawing.Point(12, 43);
           this.groupBox1.Name = "groupBox1";
           this.groupBox1.Size = new System.Drawing.Size(190, 214);
           this.groupBox1.TabIndex = 0;
           this.groupBox1.TabStop = false;
           // 
           // label3
           // 
           this.label3.AutoSize = true;
           this.label3.Location = new System.Drawing.Point(20, 191);
           this.label3.Name = "label3";
           this.label3.Size = new System.Drawing.Size(137, 15);
           this.label3.TabIndex = 4;
           this.label3.Text = "(From 0.02Hz to 50kHz)";
           // 
           // txtTimeInterval
           // 
           this.txtTimeInterval.Enabled = false;
           this.txtTimeInterval.Location = new System.Drawing.Point(90, 168);
           this.txtTimeInterval.Name = "txtTimeInterval";
           this.txtTimeInterval.Size = new System.Drawing.Size(81, 21);
           this.txtTimeInterval.TabIndex = 3;
           // 
           // label2
           // 
           this.label2.AutoSize = true;
           this.label2.Location = new System.Drawing.Point(8, 168);
           this.label2.Name = "label2";
           this.label2.Size = new System.Drawing.Size(80, 15);
           this.label2.TabIndex = 2;
           this.label2.Text = "Time interval:";
           // 
           // listSnapSource
           // 
           this.listSnapSource.FormattingEnabled = true;
           this.listSnapSource.ItemHeight = 15;
           this.listSnapSource.Location = new System.Drawing.Point(11, 34);
           this.listSnapSource.Name = "listSnapSource";
           this.listSnapSource.SelectionMode = System.Windows.Forms.SelectionMode.MultiSimple;
           this.listSnapSource.Size = new System.Drawing.Size(161, 124);
           this.listSnapSource.TabIndex = 1;
           this.listSnapSource.SelectedIndexChanged += new System.EventHandler(this.listSnapSource_SelectedIndexChanged);
           // 
           // label1
           // 
           this.label1.AutoSize = true;
           this.label1.Location = new System.Drawing.Point(7, 12);
           this.label1.Name = "label1";
           this.label1.Size = new System.Drawing.Size(79, 15);
           this.label1.TabIndex = 0;
           this.label1.Text = "Snap source:";
           // 
           // label4
           // 
           this.label4.AutoSize = true;
           this.label4.Location = new System.Drawing.Point(29, 265);
           this.label4.Name = "label4";
           this.label4.Size = new System.Drawing.Size(72, 15);
           this.label4.TabIndex = 1;
           this.label4.Text = "Snap count:";
           // 
           // txtSnapCount
           // 
           this.txtSnapCount.Enabled = false;
           this.txtSnapCount.Location = new System.Drawing.Point(102, 264);
           this.txtSnapCount.Name = "txtSnapCount";
           this.txtSnapCount.ReadOnly = true;
           this.txtSnapCount.Size = new System.Drawing.Size(81, 21);
           this.txtSnapCount.TabIndex = 4;
           // 
           // groupBox3
           // 
           this.groupBox3.Controls.Add(this.btnStop);
           this.groupBox3.Controls.Add(this.btnStart);
           this.groupBox3.Controls.Add(this.CounterValueList);
           this.groupBox3.Controls.Add(this.txtCounterValue);
           this.groupBox3.Location = new System.Drawing.Point(214, 43);
           this.groupBox3.Name = "groupBox3";
           this.groupBox3.Size = new System.Drawing.Size(300, 251);
           this.groupBox3.TabIndex = 5;
           this.groupBox3.TabStop = false;
           // 
           // btnStop
           // 
           this.btnStop.Location = new System.Drawing.Point(189, 127);
           this.btnStop.Name = "btnStop";
           this.btnStop.Size = new System.Drawing.Size(90, 25);
           this.btnStop.TabIndex = 4;
           this.btnStop.Text = "Stop";
           this.btnStop.UseVisualStyleBackColor = true;
           this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
           // 
           // btnStart
           // 
           this.btnStart.Location = new System.Drawing.Point(189, 73);
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
           this.txtCounterValue.ReadOnly = true;
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
           this.udCounterCtrl1.UdCntrEvent += new System.EventHandler<Automation.BDaq.UdCntrEventArgs>(this.udCounterCtrl1_UdCntrEvent);
           // 
           // SnapCounterForm
           // 
           this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
           this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
           this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
           this.ClientSize = new System.Drawing.Size(526, 314);
           this.Controls.Add(this.groupBox3);
           this.Controls.Add(this.txtSnapCount);
           this.Controls.Add(this.label4);
           this.Controls.Add(this.groupBox1);
           this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
           this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
           this.MaximizeBox = false;
           this.MinimizeBox = false;
           this.Name = "SnapCounterForm";
           this.Text = "SnapCounter";
           this.Load += new System.EventHandler(this.SnapCounterForm_Load);
           this.groupBox1.ResumeLayout(false);
           this.groupBox1.PerformLayout();
           this.groupBox3.ResumeLayout(false);
           this.groupBox3.PerformLayout();
           this.ResumeLayout(false);
           this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ListBox listSnapSource;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtTimeInterval;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtSnapCount;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btnStop;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.ListBox CounterValueList;
        private System.Windows.Forms.TextBox txtCounterValue;
        private System.Windows.Forms.Timer timer1;
        private Automation.BDaq.UdCounterCtrl udCounterCtrl1;
    }
}

