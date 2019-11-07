<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class BufferedEventCounterForm
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
      Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(BufferedEventCounterForm))
      Me.groupBox1 = New System.Windows.Forms.GroupBox
      Me.Label2 = New System.Windows.Forms.Label
      Me.Stop_button = New System.Windows.Forms.Button
      Me.channelStatus = New System.Windows.Forms.TextBox
      Me.CounterValueList = New System.Windows.Forms.ListBox
      Me.Start_button = New System.Windows.Forms.Button
      Me.pictureBox1 = New System.Windows.Forms.PictureBox
      Me.Label1 = New System.Windows.Forms.Label
      Me.cbxEventChannel = New System.Windows.Forms.ComboBox
      Me.Label3 = New System.Windows.Forms.Label
      Me.BufferedEventCounterCtrl1 = New Automation.BDaq.BufferedEventCounterCtrl(Me.components)
      Me.groupBox1.SuspendLayout()
      CType(Me.pictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
      Me.SuspendLayout()
      '
      'groupBox1
      '
      Me.groupBox1.Controls.Add(Me.Label2)
      Me.groupBox1.Controls.Add(Me.Stop_button)
      Me.groupBox1.Controls.Add(Me.channelStatus)
      Me.groupBox1.Controls.Add(Me.CounterValueList)
      Me.groupBox1.Controls.Add(Me.Start_button)
      Me.groupBox1.Location = New System.Drawing.Point(3, 104)
      Me.groupBox1.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
      Me.groupBox1.Name = "groupBox1"
      Me.groupBox1.Padding = New System.Windows.Forms.Padding(3, 5, 3, 5)
      Me.groupBox1.Size = New System.Drawing.Size(315, 339)
      Me.groupBox1.TabIndex = 5
      Me.groupBox1.TabStop = False
      '
      'Label2
      '
      Me.Label2.AutoSize = True
      Me.Label2.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.Label2.Location = New System.Drawing.Point(15, 18)
      Me.Label2.Name = "Label2"
      Me.Label2.Size = New System.Drawing.Size(60, 20)
      Me.Label2.TabIndex = 6
      Me.Label2.Text = "Status:"
      '
      'Stop_button
      '
      Me.Stop_button.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.Stop_button.Location = New System.Drawing.Point(215, 190)
      Me.Stop_button.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
      Me.Stop_button.Name = "Stop_button"
      Me.Stop_button.Size = New System.Drawing.Size(89, 27)
      Me.Stop_button.TabIndex = 5
      Me.Stop_button.Text = "Stop"
      Me.Stop_button.UseVisualStyleBackColor = True
      '
      'channelStatus
      '
      Me.channelStatus.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.channelStatus.ForeColor = System.Drawing.SystemColors.WindowText
      Me.channelStatus.Location = New System.Drawing.Point(93, 16)
      Me.channelStatus.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
      Me.channelStatus.Name = "channelStatus"
      Me.channelStatus.ReadOnly = True
      Me.channelStatus.Size = New System.Drawing.Size(108, 26)
      Me.channelStatus.TabIndex = 4
      Me.channelStatus.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
      '
      'CounterValueList
      '
      Me.CounterValueList.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.CounterValueList.ForeColor = System.Drawing.SystemColors.WindowText
      Me.CounterValueList.FormattingEnabled = True
      Me.CounterValueList.ItemHeight = 18
      Me.CounterValueList.Location = New System.Drawing.Point(14, 55)
      Me.CounterValueList.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
      Me.CounterValueList.Name = "CounterValueList"
      Me.CounterValueList.RightToLeft = System.Windows.Forms.RightToLeft.Yes
      Me.CounterValueList.Size = New System.Drawing.Size(187, 274)
      Me.CounterValueList.TabIndex = 3
      '
      'Start_button
      '
      Me.Start_button.Font = New System.Drawing.Font("Arial", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.Start_button.Location = New System.Drawing.Point(215, 88)
      Me.Start_button.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
      Me.Start_button.Name = "Start_button"
      Me.Start_button.Size = New System.Drawing.Size(89, 27)
      Me.Start_button.TabIndex = 0
      Me.Start_button.Text = "Start"
      Me.Start_button.UseVisualStyleBackColor = True
      '
      'pictureBox1
      '
      Me.pictureBox1.Image = CType(resources.GetObject("pictureBox1.Image"), System.Drawing.Image)
      Me.pictureBox1.Location = New System.Drawing.Point(178, 2)
      Me.pictureBox1.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
      Me.pictureBox1.Name = "pictureBox1"
      Me.pictureBox1.Size = New System.Drawing.Size(165, 61)
      Me.pictureBox1.TabIndex = 6
      Me.pictureBox1.TabStop = False
      '
      'Label1
      '
      Me.Label1.AutoSize = True
      Me.Label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.Label1.Location = New System.Drawing.Point(18, 71)
      Me.Label1.Name = "Label1"
      Me.Label1.Size = New System.Drawing.Size(72, 20)
      Me.Label1.TabIndex = 7
      Me.Label1.Text = "Channel:"
      '
      'cbxEventChannel
      '
      Me.cbxEventChannel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
      Me.cbxEventChannel.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.cbxEventChannel.FormattingEnabled = True
      Me.cbxEventChannel.Location = New System.Drawing.Point(96, 68)
      Me.cbxEventChannel.Name = "cbxEventChannel"
      Me.cbxEventChannel.Size = New System.Drawing.Size(108, 28)
      Me.cbxEventChannel.TabIndex = 8
      '
      'Label3
      '
      Me.Label3.Location = New System.Drawing.Point(19, 464)
      Me.Label3.Name = "Label3"
      Me.Label3.Size = New System.Drawing.Size(259, 38)
      Me.Label3.TabIndex = 9
      Me.Label3.Text = "Note: The example will display the first ten values on Data Ready Event every tim" & _
          "e."
      '
      'BufferedEventCounterCtrl1
      '
      Me.BufferedEventCounterCtrl1._StateStream = CType(resources.GetObject("BufferedEventCounterCtrl1._StateStream"), Automation.BDaq.DeviceStateStreamer)
      '
      'BufferedEventCounterForm
      '
      Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
      Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
      Me.ClientSize = New System.Drawing.Size(343, 531)
      Me.Controls.Add(Me.Label3)
      Me.Controls.Add(Me.cbxEventChannel)
      Me.Controls.Add(Me.Label1)
      Me.Controls.Add(Me.groupBox1)
      Me.Controls.Add(Me.pictureBox1)
      Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
      Me.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
      Me.MaximizeBox = False
      Me.MinimizeBox = False
      Me.Name = "BufferedEventCounterForm"
      Me.Text = "Buffered Event Counter"
      Me.groupBox1.ResumeLayout(False)
      Me.groupBox1.PerformLayout()
      CType(Me.pictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
      Me.ResumeLayout(False)
      Me.PerformLayout()

   End Sub
   Private WithEvents groupBox1 As System.Windows.Forms.GroupBox
   Friend WithEvents Stop_button As System.Windows.Forms.Button
   Private WithEvents channelStatus As System.Windows.Forms.TextBox
   Private WithEvents CounterValueList As System.Windows.Forms.ListBox
   Private WithEvents Start_button As System.Windows.Forms.Button
   Private WithEvents pictureBox1 As System.Windows.Forms.PictureBox
   Friend WithEvents Label2 As System.Windows.Forms.Label
   Friend WithEvents Label1 As System.Windows.Forms.Label
   Friend WithEvents cbxEventChannel As System.Windows.Forms.ComboBox
   Friend WithEvents Label3 As System.Windows.Forms.Label
   Friend WithEvents BufferedEventCounterCtrl1 As Automation.BDaq.BufferedEventCounterCtrl

End Class
