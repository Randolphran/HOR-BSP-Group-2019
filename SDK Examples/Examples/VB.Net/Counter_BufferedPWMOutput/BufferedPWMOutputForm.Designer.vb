<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class BufferedPWMOutputForm
   Inherits System.Windows.Forms.Form

   'Form overrides dispose to clean up the component list.
   <System.Diagnostics.DebuggerNonUserCode()> _
   Protected Overrides Sub Dispose(ByVal disposing As Boolean)
      If disposing AndAlso components IsNot Nothing Then
         components.Dispose()
      End If
      MyBase.Dispose(disposing)
   End Sub

   'Required by the Windows Form Designer
   Private components As System.ComponentModel.IContainer

   'NOTE: The following procedure is required by the Windows Form Designer
   'It can be modified using the Windows Form Designer.  
   'Do not modify it using the code editor.
   <System.Diagnostics.DebuggerStepThrough()> _
   Private Sub InitializeComponent()
      Me.components = New System.ComponentModel.Container
      Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(BufferedPWMOutputForm))
      Me.btnStart = New System.Windows.Forms.Button
      Me.groupBox1 = New System.Windows.Forms.GroupBox
      Me.ExecutionStatus = New System.Windows.Forms.Label
      Me.Label6 = New System.Windows.Forms.Label
      Me.data2_LoPeriod = New System.Windows.Forms.TextBox
      Me.label4 = New System.Windows.Forms.Label
      Me.data2_HiPeriod = New System.Windows.Forms.TextBox
      Me.label2 = New System.Windows.Forms.Label
      Me.data1_HiPeriod = New System.Windows.Forms.TextBox
      Me.pictureBox1 = New System.Windows.Forms.PictureBox
      Me.btnStop = New System.Windows.Forms.Button
      Me.Label5 = New System.Windows.Forms.Label
      Me.Label7 = New System.Windows.Forms.Label
      Me.Label8 = New System.Windows.Forms.Label
      Me.data1_LoPeriod = New System.Windows.Forms.TextBox
      Me.Label9 = New System.Windows.Forms.Label
      Me.Label10 = New System.Windows.Forms.Label
      Me.GroupBox2 = New System.Windows.Forms.GroupBox
      Me.GroupBox3 = New System.Windows.Forms.GroupBox
      Me.Label1 = New System.Windows.Forms.Label
      Me.BufferedPwModulatorCtrl1 = New Automation.BDaq.BufferedPwModulatorCtrl(Me.components)
      Me.groupBox1.SuspendLayout()
      CType(Me.pictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
      Me.GroupBox2.SuspendLayout()
      Me.GroupBox3.SuspendLayout()
      Me.SuspendLayout()
      '
      'btnStart
      '
      Me.btnStart.Location = New System.Drawing.Point(36, 355)
      Me.btnStart.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
      Me.btnStart.Name = "btnStart"
      Me.btnStart.Size = New System.Drawing.Size(75, 28)
      Me.btnStart.TabIndex = 12
      Me.btnStart.Text = "Start"
      Me.btnStart.UseVisualStyleBackColor = True
      '
      'groupBox1
      '
      Me.groupBox1.Controls.Add(Me.ExecutionStatus)
      Me.groupBox1.Location = New System.Drawing.Point(12, 281)
      Me.groupBox1.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
      Me.groupBox1.Name = "groupBox1"
      Me.groupBox1.Padding = New System.Windows.Forms.Padding(3, 4, 3, 4)
      Me.groupBox1.Size = New System.Drawing.Size(261, 67)
      Me.groupBox1.TabIndex = 11
      Me.groupBox1.TabStop = False
      Me.groupBox1.Text = "Execution status "
      '
      'ExecutionStatus
      '
      Me.ExecutionStatus.Enabled = False
      Me.ExecutionStatus.Image = CType(resources.GetObject("ExecutionStatus.Image"), System.Drawing.Image)
      Me.ExecutionStatus.Location = New System.Drawing.Point(6, 28)
      Me.ExecutionStatus.Name = "ExecutionStatus"
      Me.ExecutionStatus.Size = New System.Drawing.Size(246, 29)
      Me.ExecutionStatus.TabIndex = 5
      '
      'Label6
      '
      Me.Label6.AutoSize = True
      Me.Label6.Location = New System.Drawing.Point(179, 69)
      Me.Label6.Name = "Label6"
      Me.Label6.Size = New System.Drawing.Size(15, 15)
      Me.Label6.TabIndex = 7
      Me.Label6.Text = "S"
      '
      'data2_LoPeriod
      '
      Me.data2_LoPeriod.Location = New System.Drawing.Point(96, 66)
      Me.data2_LoPeriod.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
      Me.data2_LoPeriod.Name = "data2_LoPeriod"
      Me.data2_LoPeriod.RightToLeft = System.Windows.Forms.RightToLeft.No
      Me.data2_LoPeriod.Size = New System.Drawing.Size(77, 21)
      Me.data2_LoPeriod.TabIndex = 6
      Me.data2_LoPeriod.Text = "0.05"
      Me.data2_LoPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
      '
      'label4
      '
      Me.label4.AutoSize = True
      Me.label4.Location = New System.Drawing.Point(179, 30)
      Me.label4.Name = "label4"
      Me.label4.Size = New System.Drawing.Size(15, 15)
      Me.label4.TabIndex = 2
      Me.label4.Text = "S"
      '
      'data2_HiPeriod
      '
      Me.data2_HiPeriod.Location = New System.Drawing.Point(96, 27)
      Me.data2_HiPeriod.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
      Me.data2_HiPeriod.Name = "data2_HiPeriod"
      Me.data2_HiPeriod.RightToLeft = System.Windows.Forms.RightToLeft.No
      Me.data2_HiPeriod.Size = New System.Drawing.Size(77, 21)
      Me.data2_HiPeriod.TabIndex = 0
      Me.data2_HiPeriod.Text = "0.05"
      Me.data2_HiPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
      '
      'label2
      '
      Me.label2.AutoSize = True
      Me.label2.Location = New System.Drawing.Point(179, 29)
      Me.label2.Name = "label2"
      Me.label2.Size = New System.Drawing.Size(15, 15)
      Me.label2.TabIndex = 10
      Me.label2.Text = "S"
      '
      'data1_HiPeriod
      '
      Me.data1_HiPeriod.Location = New System.Drawing.Point(96, 26)
      Me.data1_HiPeriod.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
      Me.data1_HiPeriod.Name = "data1_HiPeriod"
      Me.data1_HiPeriod.RightToLeft = System.Windows.Forms.RightToLeft.No
      Me.data1_HiPeriod.Size = New System.Drawing.Size(77, 21)
      Me.data1_HiPeriod.TabIndex = 9
      Me.data1_HiPeriod.Text = "0.08"
      Me.data1_HiPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
      '
      'pictureBox1
      '
      Me.pictureBox1.Image = CType(resources.GetObject("pictureBox1.Image"), System.Drawing.Image)
      Me.pictureBox1.Location = New System.Drawing.Point(194, 2)
      Me.pictureBox1.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
      Me.pictureBox1.Name = "pictureBox1"
      Me.pictureBox1.Size = New System.Drawing.Size(153, 55)
      Me.pictureBox1.TabIndex = 13
      Me.pictureBox1.TabStop = False
      '
      'btnStop
      '
      Me.btnStop.Location = New System.Drawing.Point(173, 355)
      Me.btnStop.Name = "btnStop"
      Me.btnStop.Size = New System.Drawing.Size(75, 28)
      Me.btnStop.TabIndex = 14
      Me.btnStop.Text = "Stop"
      Me.btnStop.UseVisualStyleBackColor = True
      '
      'Label5
      '
      Me.Label5.AutoSize = True
      Me.Label5.Location = New System.Drawing.Point(15, 29)
      Me.Label5.Name = "Label5"
      Me.Label5.Size = New System.Drawing.Size(75, 15)
      Me.Label5.TabIndex = 6
      Me.Label5.Text = "High Period:"
      '
      'Label7
      '
      Me.Label7.AutoSize = True
      Me.Label7.Location = New System.Drawing.Point(15, 67)
      Me.Label7.Name = "Label7"
      Me.Label7.Size = New System.Drawing.Size(72, 15)
      Me.Label7.TabIndex = 15
      Me.Label7.Text = "Low Period:"
      '
      'Label8
      '
      Me.Label8.AutoSize = True
      Me.Label8.Location = New System.Drawing.Point(179, 67)
      Me.Label8.Name = "Label8"
      Me.Label8.Size = New System.Drawing.Size(15, 15)
      Me.Label8.TabIndex = 17
      Me.Label8.Text = "S"
      '
      'data1_LoPeriod
      '
      Me.data1_LoPeriod.Location = New System.Drawing.Point(96, 64)
      Me.data1_LoPeriod.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
      Me.data1_LoPeriod.Name = "data1_LoPeriod"
      Me.data1_LoPeriod.RightToLeft = System.Windows.Forms.RightToLeft.No
      Me.data1_LoPeriod.Size = New System.Drawing.Size(77, 21)
      Me.data1_LoPeriod.TabIndex = 16
      Me.data1_LoPeriod.Text = "0.02"
      Me.data1_LoPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
      '
      'Label9
      '
      Me.Label9.AutoSize = True
      Me.Label9.Location = New System.Drawing.Point(18, 69)
      Me.Label9.Name = "Label9"
      Me.Label9.Size = New System.Drawing.Size(72, 15)
      Me.Label9.TabIndex = 19
      Me.Label9.Text = "Low Period:"
      '
      'Label10
      '
      Me.Label10.AutoSize = True
      Me.Label10.Location = New System.Drawing.Point(15, 30)
      Me.Label10.Name = "Label10"
      Me.Label10.Size = New System.Drawing.Size(75, 15)
      Me.Label10.TabIndex = 18
      Me.Label10.Text = "High Period:"
      '
      'GroupBox2
      '
      Me.GroupBox2.Controls.Add(Me.Label5)
      Me.GroupBox2.Controls.Add(Me.data1_HiPeriod)
      Me.GroupBox2.Controls.Add(Me.label2)
      Me.GroupBox2.Controls.Add(Me.Label8)
      Me.GroupBox2.Controls.Add(Me.Label7)
      Me.GroupBox2.Controls.Add(Me.data1_LoPeriod)
      Me.GroupBox2.Location = New System.Drawing.Point(12, 53)
      Me.GroupBox2.Name = "GroupBox2"
      Me.GroupBox2.Size = New System.Drawing.Size(205, 100)
      Me.GroupBox2.TabIndex = 20
      Me.GroupBox2.TabStop = False
      Me.GroupBox2.Text = "Data 1"
      '
      'GroupBox3
      '
      Me.GroupBox3.Controls.Add(Me.Label6)
      Me.GroupBox3.Controls.Add(Me.Label10)
      Me.GroupBox3.Controls.Add(Me.data2_LoPeriod)
      Me.GroupBox3.Controls.Add(Me.label4)
      Me.GroupBox3.Controls.Add(Me.Label9)
      Me.GroupBox3.Controls.Add(Me.data2_HiPeriod)
      Me.GroupBox3.Location = New System.Drawing.Point(12, 165)
      Me.GroupBox3.Name = "GroupBox3"
      Me.GroupBox3.Size = New System.Drawing.Size(205, 100)
      Me.GroupBox3.TabIndex = 21
      Me.GroupBox3.TabStop = False
      Me.GroupBox3.Text = "Data 2"
      '
      'Label1
      '
      Me.Label1.Location = New System.Drawing.Point(223, 188)
      Me.Label1.Name = "Label1"
      Me.Label1.Size = New System.Drawing.Size(117, 61)
      Me.Label1.TabIndex = 22
      Me.Label1.Text = "Note: The buffer will be filled with Data 1 and Data 2 in turn."
      '
      'BufferedPwModulatorCtrl1
      '
      Me.BufferedPwModulatorCtrl1._StateStream = CType(resources.GetObject("BufferedPwModulatorCtrl1._StateStream"), Automation.BDaq.DeviceStateStreamer)
      '
      'BufferedPWMOutputForm
      '
      Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
      Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
      Me.ClientSize = New System.Drawing.Size(352, 397)
      Me.Controls.Add(Me.Label1)
      Me.Controls.Add(Me.GroupBox3)
      Me.Controls.Add(Me.GroupBox2)
      Me.Controls.Add(Me.btnStop)
      Me.Controls.Add(Me.btnStart)
      Me.Controls.Add(Me.groupBox1)
      Me.Controls.Add(Me.pictureBox1)
      Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
      Me.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
      Me.MaximizeBox = False
      Me.MinimizeBox = False
      Me.Name = "BufferedPWMOutputForm"
      Me.Text = "Buffered PWM Output"
      Me.groupBox1.ResumeLayout(False)
      CType(Me.pictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
      Me.GroupBox2.ResumeLayout(False)
      Me.GroupBox2.PerformLayout()
      Me.GroupBox3.ResumeLayout(False)
      Me.GroupBox3.PerformLayout()
      Me.ResumeLayout(False)

   End Sub
   Private WithEvents btnStart As System.Windows.Forms.Button
   Private WithEvents groupBox1 As System.Windows.Forms.GroupBox
   Private WithEvents ExecutionStatus As System.Windows.Forms.Label
   Private WithEvents label4 As System.Windows.Forms.Label
   Private WithEvents data2_HiPeriod As System.Windows.Forms.TextBox
   Private WithEvents label2 As System.Windows.Forms.Label
   Private WithEvents data1_HiPeriod As System.Windows.Forms.TextBox
   Private WithEvents pictureBox1 As System.Windows.Forms.PictureBox
   Friend WithEvents btnStop As System.Windows.Forms.Button
   Private WithEvents Label6 As System.Windows.Forms.Label
   Private WithEvents data2_LoPeriod As System.Windows.Forms.TextBox
   Friend WithEvents Label5 As System.Windows.Forms.Label
   Friend WithEvents Label7 As System.Windows.Forms.Label
   Private WithEvents Label8 As System.Windows.Forms.Label
   Private WithEvents data1_LoPeriod As System.Windows.Forms.TextBox
   Friend WithEvents Label9 As System.Windows.Forms.Label
   Friend WithEvents Label10 As System.Windows.Forms.Label
   Friend WithEvents GroupBox2 As System.Windows.Forms.GroupBox
   Friend WithEvents GroupBox3 As System.Windows.Forms.GroupBox
   Friend WithEvents Label1 As System.Windows.Forms.Label
   Friend WithEvents BufferedPwModulatorCtrl1 As Automation.BDaq.BufferedPwModulatorCtrl

End Class
