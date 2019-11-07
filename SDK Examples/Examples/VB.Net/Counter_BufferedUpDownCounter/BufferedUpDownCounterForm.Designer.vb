<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class BufferedUpDownCounterForm
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
      Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(BufferedUpDownCounterForm))
      Me.groupBox3 = New System.Windows.Forms.GroupBox
      Me.Label2 = New System.Windows.Forms.Label
      Me.btnStop = New System.Windows.Forms.Button
      Me.btnStart = New System.Windows.Forms.Button
      Me.CounterValueList = New System.Windows.Forms.ListBox
      Me.channelStatus = New System.Windows.Forms.TextBox
      Me.BufferedUdCounterCtrl1 = New Automation.BDaq.BufferedUdCounterCtrl(Me.components)
      Me.Label1 = New System.Windows.Forms.Label
      Me.cbxEventChannel = New System.Windows.Forms.ComboBox
      Me.Label3 = New System.Windows.Forms.Label
      Me.groupBox3.SuspendLayout()
      Me.SuspendLayout()
      '
      'groupBox3
      '
      Me.groupBox3.Controls.Add(Me.Label2)
      Me.groupBox3.Controls.Add(Me.btnStop)
      Me.groupBox3.Controls.Add(Me.btnStart)
      Me.groupBox3.Controls.Add(Me.CounterValueList)
      Me.groupBox3.Controls.Add(Me.channelStatus)
      Me.groupBox3.Location = New System.Drawing.Point(12, 100)
      Me.groupBox3.Name = "groupBox3"
      Me.groupBox3.Size = New System.Drawing.Size(315, 313)
      Me.groupBox3.TabIndex = 5
      Me.groupBox3.TabStop = False
      '
      'Label2
      '
      Me.Label2.AutoSize = True
      Me.Label2.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.Label2.Location = New System.Drawing.Point(17, 21)
      Me.Label2.Name = "Label2"
      Me.Label2.Size = New System.Drawing.Size(60, 20)
      Me.Label2.TabIndex = 5
      Me.Label2.Text = "Status:"
      '
      'btnStop
      '
      Me.btnStop.Location = New System.Drawing.Point(201, 209)
      Me.btnStop.Name = "btnStop"
      Me.btnStop.Size = New System.Drawing.Size(90, 25)
      Me.btnStop.TabIndex = 4
      Me.btnStop.Text = "Stop"
      Me.btnStop.UseVisualStyleBackColor = True
      '
      'btnStart
      '
      Me.btnStart.Location = New System.Drawing.Point(201, 103)
      Me.btnStart.Name = "btnStart"
      Me.btnStart.Size = New System.Drawing.Size(90, 25)
      Me.btnStart.TabIndex = 2
      Me.btnStart.Text = "Start"
      Me.btnStart.UseVisualStyleBackColor = True
      '
      'CounterValueList
      '
      Me.CounterValueList.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.CounterValueList.FormattingEnabled = True
      Me.CounterValueList.ItemHeight = 20
      Me.CounterValueList.Location = New System.Drawing.Point(21, 57)
      Me.CounterValueList.Name = "CounterValueList"
      Me.CounterValueList.Size = New System.Drawing.Size(174, 244)
      Me.CounterValueList.TabIndex = 1
      '
      'channelStatus
      '
      Me.channelStatus.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.channelStatus.Location = New System.Drawing.Point(95, 18)
      Me.channelStatus.Name = "channelStatus"
      Me.channelStatus.ReadOnly = True
      Me.channelStatus.Size = New System.Drawing.Size(100, 26)
      Me.channelStatus.TabIndex = 0
      '
      'BufferedUdCounterCtrl1
      '
      Me.BufferedUdCounterCtrl1._StateStream = CType(resources.GetObject("BufferedUdCounterCtrl1._StateStream"), Automation.BDaq.DeviceStateStreamer)
      '
      'Label1
      '
      Me.Label1.AutoSize = True
      Me.Label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.Label1.Location = New System.Drawing.Point(29, 63)
      Me.Label1.Name = "Label1"
      Me.Label1.Size = New System.Drawing.Size(72, 20)
      Me.Label1.TabIndex = 6
      Me.Label1.Text = "Channel:"
      '
      'cbxEventChannel
      '
      Me.cbxEventChannel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
      Me.cbxEventChannel.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
      Me.cbxEventChannel.FormattingEnabled = True
      Me.cbxEventChannel.Location = New System.Drawing.Point(107, 60)
      Me.cbxEventChannel.Name = "cbxEventChannel"
      Me.cbxEventChannel.Size = New System.Drawing.Size(100, 28)
      Me.cbxEventChannel.TabIndex = 7
      '
      'Label3
      '
      Me.Label3.Location = New System.Drawing.Point(30, 438)
      Me.Label3.Name = "Label3"
      Me.Label3.Size = New System.Drawing.Size(255, 38)
      Me.Label3.TabIndex = 8
      Me.Label3.Text = "Note: The example will display the first ten values on Data Ready Event every tim" & _
          "e."
      '
      'BufferedUpDownCounterForm
      '
      Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
      Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
      Me.BackgroundImage = CType(resources.GetObject("$this.BackgroundImage"), System.Drawing.Image)
      Me.ClientSize = New System.Drawing.Size(341, 505)
      Me.Controls.Add(Me.Label3)
      Me.Controls.Add(Me.cbxEventChannel)
      Me.Controls.Add(Me.Label1)
      Me.Controls.Add(Me.groupBox3)
      Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
      Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
      Me.MaximizeBox = False
      Me.MinimizeBox = False
      Me.Name = "BufferedUpDownCounterForm"
      Me.Text = "Buffered Up Down Counter"
      Me.groupBox3.ResumeLayout(False)
      Me.groupBox3.PerformLayout()
      Me.ResumeLayout(False)
      Me.PerformLayout()

   End Sub
   Private WithEvents groupBox3 As System.Windows.Forms.GroupBox
   Private WithEvents btnStop As System.Windows.Forms.Button
   Private WithEvents btnStart As System.Windows.Forms.Button
   Private WithEvents CounterValueList As System.Windows.Forms.ListBox
   Private WithEvents channelStatus As System.Windows.Forms.TextBox
   Private WithEvents BufferedUdCounterCtrl1 As Automation.BDaq.BufferedUdCounterCtrl
   Friend WithEvents Label1 As System.Windows.Forms.Label
   Friend WithEvents cbxEventChannel As System.Windows.Forms.ComboBox
   Friend WithEvents Label2 As System.Windows.Forms.Label
   Friend WithEvents Label3 As System.Windows.Forms.Label

End Class
