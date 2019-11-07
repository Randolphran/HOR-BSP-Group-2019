using System.Windows.Forms;
using System.Drawing;

namespace DI_DIPatternMatchInterrupt
{
   partial class DIPatternMatchInterruptForm
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
         System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DIPatternMatchInterruptForm));
         this.buttonStop = new System.Windows.Forms.Button();
         this.buttonStart = new System.Windows.Forms.Button();
         this.pictureBox1 = new System.Windows.Forms.PictureBox();
         this.ExecutionStatus = new System.Windows.Forms.PictureBox();
         this.instantDiCtrl1 = new Automation.BDaq.InstantDiCtrl(this.components);
         this.listViewForData = new DoubleBufferListView();
         this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
         this.columnHeader2 = new System.Windows.Forms.ColumnHeader();
         ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
         ((System.ComponentModel.ISupportInitialize)(this.ExecutionStatus)).BeginInit();
         this.SuspendLayout();
         // 
         // buttonStop
         // 
         this.buttonStop.Location = new System.Drawing.Point(333, 113);
         this.buttonStop.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.buttonStop.Name = "buttonStop";
         this.buttonStop.Size = new System.Drawing.Size(96, 30);
         this.buttonStop.TabIndex = 3;
         this.buttonStop.Text = "Stop";
         this.buttonStop.UseVisualStyleBackColor = true;
         this.buttonStop.Click += new System.EventHandler(this.buttonStop_Click);
         // 
         // buttonStart
         // 
         this.buttonStart.Location = new System.Drawing.Point(333, 68);
         this.buttonStart.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.buttonStart.Name = "buttonStart";
         this.buttonStart.Size = new System.Drawing.Size(96, 30);
         this.buttonStart.TabIndex = 5;
         this.buttonStart.Text = "Start";
         this.buttonStart.UseVisualStyleBackColor = true;
         this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
         // 
         // pictureBox1
         // 
         this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
         this.pictureBox1.Location = new System.Drawing.Point(-33, -29);
         this.pictureBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.pictureBox1.Name = "pictureBox1";
         this.pictureBox1.Size = new System.Drawing.Size(474, 307);
         this.pictureBox1.TabIndex = 0;
         this.pictureBox1.TabStop = false;
         // 
         // ExecutionStatus
         // 
         this.ExecutionStatus.Image = ((System.Drawing.Image)(resources.GetObject("ExecutionStatus.Image")));
         this.ExecutionStatus.Location = new System.Drawing.Point(264, 5);
         this.ExecutionStatus.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.ExecutionStatus.Name = "ExecutionStatus";
         this.ExecutionStatus.Size = new System.Drawing.Size(20, 20);
         this.ExecutionStatus.TabIndex = 6;
         this.ExecutionStatus.TabStop = false;
         // 
         // instantDiCtrl1
         // 
         this.instantDiCtrl1._StateStream = ((Automation.BDaq.DeviceStateStreamer)(resources.GetObject("instantDiCtrl1._StateStream")));
         this.instantDiCtrl1.PatternMatch += new System.EventHandler<Automation.BDaq.DiSnapEventArgs>(this.instantDiCtrl1_PatternMatch);
         // 
         // listViewForData
         // 
         this.listViewForData.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2});
         this.listViewForData.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.listViewForData.Location = new System.Drawing.Point(14, 26);
         this.listViewForData.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.listViewForData.Name = "listViewForData";
         this.listViewForData.OwnerDraw = true;
         this.listViewForData.Size = new System.Drawing.Size(315, 240);
         this.listViewForData.TabIndex = 1;
         this.listViewForData.UseCompatibleStateImageBehavior = false;
         this.listViewForData.View = System.Windows.Forms.View.Details;
         this.listViewForData.DrawColumnHeader += new System.Windows.Forms.DrawListViewColumnHeaderEventHandler(this.listView1_DrawColumnHeader);
         this.listViewForData.DrawSubItem += new System.Windows.Forms.DrawListViewSubItemEventHandler(this.listViewForData_DrawSubItem);
         // 
         // columnHeader1
         // 
         this.columnHeader1.Text = "Matched No#";
         this.columnHeader1.Width = 101;
         // 
         // columnHeader2
         // 
         this.columnHeader2.Text = "DI ports value";
         this.columnHeader2.Width = 210;
         // 
         // DIPatternMatchInterruptForm
         // 
         this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
         this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
         this.ClientSize = new System.Drawing.Size(436, 275);
         this.Controls.Add(this.ExecutionStatus);
         this.Controls.Add(this.buttonStart);
         this.Controls.Add(this.buttonStop);
         this.Controls.Add(this.listViewForData);
         this.Controls.Add(this.pictureBox1);
         this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
         this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
         this.MaximizeBox = false;
         this.MinimizeBox = false;
         this.Name = "DIPatternMatchInterruptForm";
         this.Text = "DI Pattern Match Interrupt - Run";
         this.Load += new System.EventHandler(this.DIPatternMatchInterruptForm_Load);
         ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
         ((System.ComponentModel.ISupportInitialize)(this.ExecutionStatus)).EndInit();
         this.ResumeLayout(false);

      }

      #endregion

      private DoubleBufferListView listViewForData;
      private ColumnHeader columnHeader1;
      private System.Windows.Forms.Button buttonStop;
      private System.Windows.Forms.Button buttonStart;
      private ColumnHeader columnHeader2;
      private PictureBox pictureBox1;
      private PictureBox ExecutionStatus;
      private Automation.BDaq.InstantDiCtrl instantDiCtrl1;
   }
}