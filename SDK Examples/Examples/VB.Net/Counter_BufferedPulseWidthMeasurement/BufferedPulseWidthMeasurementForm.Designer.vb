<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class BufferedPulseWidthMeasurementForm
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
      Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(BufferedPulseWidthMeasurementForm))
      Me.groupBox1 = New System.Windows.Forms.GroupBox
      Me.Label1 = New System.Windows.Forms.Label
      Me.btnStop = New System.Windows.Forms.Button
      Me.channelStatus = New System.Windows.Forms.TextBox
      Me.CounterValueList = New System.Windows.Forms.ListBox
      Me.btnStart = New System.Windows.Forms.Button
      Me.Label4 = New System.Windows.Forms.Label
      Me.pictureBox1 = New System.Windows.Forms.PictureBox
      Me.BufferedPwMeterCtrl1 = New Automation.BDaq.BufferedPwMeterCtrl(Me.components)
      Me.Label2 = New System.Windows.Forms.Label
      Me.cbxEventChannel = New System.Windows.Forms.ComboBox
      Me.groupBox1.SuspendLayout()
      CType(Me.pictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
      Me.SuspendLayout()
      '
      'groupBox1
      '
      Me.groupBox1.Controls.Add(Me.Label1)
      Me.groupBox1.Controls.Add(Me.btnStop)
      Me.groupBox1.Controls.Add(Me.channelStatus)
      Me.groupBox1.Controls.Add(Me.CounterValueList)
      Me.groupBox1.Controls.Add(Me.btnStart)
      Me.groupBox1.Location = New System.Drawing.Point(12, 94)
      Me.groupBox1.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
      Me.groupBox1.Name = "groupBox1"
      Me.groupBox1.Padding = New System.Windows.Forms.Padding(3, 5, 3, 5)
      Me.groupBox1.Size = New System.Drawing.Size(376, 335)
      Me.groupBox1.TabIndex = 5
      Me.groupBox1.TabStop = False
      '
      'Label1
      '
      Me.Label1.AutoSize = True
      Me.Label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.Label1.Location = New System.Drawing.Point(15, 23)
      Me.Label1.Name = "Label1"
      Me.Label1.Size = New System.Drawing.Size(60, 20)
      Me.Label1.TabIndex = 6
      Me.Label1.Text = "Status:"
      '
      'btnStop
      '
      Me.btnStop.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.btnStop.Location = New System.Drawing.Point(278, 228)
      Me.btnStop.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
      Me.btnStop.Name = "btnStop"
      Me.btnStop.Size = New System.Drawing.Size(89, 27)
      Me.btnStop.TabIndex = 5
      Me.btnStop.Text = "Stop"
      Me.btnStop.UseVisualStyleBackColor = True
      '
      'channelStatus
      '
      Me.channelStatus.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.channelStatus.ForeColor = System.Drawing.SystemColors.WindowText
      Me.channelStatus.Location = New System.Drawing.Point(94, 20)
      Me.channelStatus.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
      Me.channelStatus.Name = "channelStatus"
      Me.channelStatus.ReadOnly = True
      Me.channelStatus.Size = New System.Drawing.Size(121, 26)
      Me.channelStatus.TabIndex = 4
      Me.channelStatus.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
      '
      'CounterValueList
      '
      Me.CounterValueList.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.CounterValueList.ForeColor = System.Drawing.SystemColors.WindowText
      Me.CounterValueList.FormattingEnabled = True
      Me.CounterValueList.ItemHeight = 18
      Me.CounterValueList.Location = New System.Drawing.Point(19, 60)
      Me.CounterValueList.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
      Me.CounterValueList.Name = "CounterValueList"
      Me.CounterValueList.RightToLeft = System.Windows.Forms.RightToLeft.No
      Me.CounterValueList.Size = New System.Drawing.Size(253, 256)
      Me.CounterValueList.TabIndex = 3
      '
      'btnStart
      '
      Me.btnStart.Font = New System.Drawing.Font("Arial", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.btnStart.Location = New System.Drawing.Point(278, 119)
      Me.btnStart.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
      Me.btnStart.Name = "btnStart"
      Me.btnStart.Size = New System.Drawing.Size(89, 27)
      Me.btnStart.TabIndex = 0
      Me.btnStart.Text = "Start"
      Me.btnStart.UseVisualStyleBackColor = True
      '
      'Label4
      '
      Me.Label4.AutoSize = True
      Me.Label4.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.Label4.Location = New System.Drawing.Point(27, 58)
      Me.Label4.Name = "Label4"
      Me.Label4.Size = New System.Drawing.Size(72, 20)
      Me.Label4.TabIndex = 9
      Me.Label4.Text = "Channel:"
      '
      'pictureBox1
      '
      Me.pictureBox1.Image = CType(resources.GetObject("pictureBox1.Image"), System.Drawing.Image)
      Me.pictureBox1.Location = New System.Drawing.Point(220, 3)
      Me.pictureBox1.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
      Me.pictureBox1.Name = "pictureBox1"
      Me.pictureBox1.Size = New System.Drawing.Size(168, 58)
      Me.pictureBox1.TabIndex = 6
      Me.pictureBox1.TabStop = False
      '
      'BufferedPwMeterCtrl1
      '
      Me.BufferedPwMeterCtrl1._StateStream = CType(resources.GetObject("BufferedPwMeterCtrl1._StateStream"), Automation.BDaq.DeviceStateStreamer)
      '
      'Label2
      '
      Me.Label2.Location = New System.Drawing.Point(31, 443)
      Me.Label2.Name = "Label2"
      Me.Label2.Size = New System.Drawing.Size(253, 41)
      Me.Label2.TabIndex = 11
      Me.Label2.Text = "Note: The example will display the first ten values on Data Ready Event every tim" & _
          "e."
      '
      'cbxEventChannel
      '
      Me.cbxEventChannel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
      Me.cbxEventChannel.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.cbxEventChannel.FormattingEnabled = True
      Me.cbxEventChannel.Location = New System.Drawing.Point(105, 55)
      Me.cbxEventChannel.Name = "cbxEventChannel"
      Me.cbxEventChannel.Size = New System.Drawing.Size(100, 28)
      Me.cbxEventChannel.TabIndex = 12
      '
      'BufferedPulseWidthMeasurementForm
      '
      Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
      Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
      Me.ClientSize = New System.Drawing.Size(402, 502)
      Me.Controls.Add(Me.cbxEventChannel)
      Me.Controls.Add(Me.Label2)
      Me.Controls.Add(Me.groupBox1)
      Me.Controls.Add(Me.Label4)
      Me.Controls.Add(Me.pictureBox1)
      Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
      Me.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
      Me.MaximizeBox = False
      Me.MinimizeBox = False
      Me.Name = "BufferedPulseWidthMeasurementForm"
      Me.Text = "Buffered Pulse Width Measurement"
      Me.groupBox1.ResumeLayout(False)
      Me.groupBox1.PerformLayout()
      CType(Me.pictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
      Me.ResumeLayout(False)
      Me.PerformLayout()

   End Sub
   Private WithEvents groupBox1 As System.Windows.Forms.GroupBox
   Friend WithEvents btnStop As System.Windows.Forms.Button
   Private WithEvents channelStatus As System.Windows.Forms.TextBox
   Private WithEvents CounterValueList As System.Windows.Forms.ListBox
   Private WithEvents btnStart As System.Windows.Forms.Button
   Private WithEvents pictureBox1 As System.Windows.Forms.PictureBox
   Friend WithEvents Label4 As System.Windows.Forms.Label
   Friend WithEvents Label1 As System.Windows.Forms.Label
   Friend WithEvents BufferedPwMeterCtrl1 As Automation.BDaq.BufferedPwMeterCtrl
   Friend WithEvents Label2 As System.Windows.Forms.Label
   Friend WithEvents cbxEventChannel As System.Windows.Forms.ComboBox

End Class
