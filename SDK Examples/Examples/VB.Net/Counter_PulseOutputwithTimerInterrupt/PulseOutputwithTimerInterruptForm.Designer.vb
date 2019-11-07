<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class PulseOutputwithTimerInterruptForm
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(PulseOutputwithTimerInterruptForm))
        Me.Start = New System.Windows.Forms.Button
        Me.groupBox1 = New System.Windows.Forms.GroupBox
        Me.ExecutionStatus = New System.Windows.Forms.Label
        Me.eventCount = New System.Windows.Forms.TextBox
        Me.label_eventCount = New System.Windows.Forms.Label
        Me.label4 = New System.Windows.Forms.Label
        Me.label3 = New System.Windows.Forms.Label
        Me.generatedFrequency = New System.Windows.Forms.TextBox
        Me.label2 = New System.Windows.Forms.Label
        Me.desiredFrequency = New System.Windows.Forms.TextBox
        Me.label1 = New System.Windows.Forms.Label
        Me.pictureBox1 = New System.Windows.Forms.PictureBox
        Me.Stop_button = New System.Windows.Forms.Button
        Me.m_TimerPulseCtrl = New Automation.BDaq.TimerPulseCtrl(Me.components)
        Me.groupBox1.SuspendLayout()
        CType(Me.pictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'Start
        '
        Me.Start.Location = New System.Drawing.Point(63, 237)
        Me.Start.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.Start.Name = "Start"
        Me.Start.Size = New System.Drawing.Size(75, 28)
        Me.Start.TabIndex = 12
        Me.Start.Text = "Start"
        Me.Start.UseVisualStyleBackColor = True
        '
        'groupBox1
        '
        Me.groupBox1.Controls.Add(Me.ExecutionStatus)
        Me.groupBox1.Controls.Add(Me.eventCount)
        Me.groupBox1.Controls.Add(Me.label_eventCount)
        Me.groupBox1.Controls.Add(Me.label4)
        Me.groupBox1.Controls.Add(Me.label3)
        Me.groupBox1.Controls.Add(Me.generatedFrequency)
        Me.groupBox1.Location = New System.Drawing.Point(22, 65)
        Me.groupBox1.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.groupBox1.Name = "groupBox1"
        Me.groupBox1.Padding = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.groupBox1.Size = New System.Drawing.Size(301, 164)
        Me.groupBox1.TabIndex = 11
        Me.groupBox1.TabStop = False
        Me.groupBox1.Text = "Execution status "
        '
        'ExecutionStatus
        '
        Me.ExecutionStatus.Enabled = False
        Me.ExecutionStatus.Image = CType(resources.GetObject("ExecutionStatus.Image"), System.Drawing.Image)
        Me.ExecutionStatus.Location = New System.Drawing.Point(7, 21)
        Me.ExecutionStatus.Name = "ExecutionStatus"
        Me.ExecutionStatus.Size = New System.Drawing.Size(246, 29)
        Me.ExecutionStatus.TabIndex = 5
        '
        'eventCount
        '
        Me.eventCount.Location = New System.Drawing.Point(10, 135)
        Me.eventCount.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.eventCount.Name = "eventCount"
        Me.eventCount.ReadOnly = True
        Me.eventCount.Size = New System.Drawing.Size(172, 21)
        Me.eventCount.TabIndex = 4
        Me.eventCount.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'label_eventCount
        '
        Me.label_eventCount.AutoSize = True
        Me.label_eventCount.Location = New System.Drawing.Point(9, 108)
        Me.label_eventCount.Name = "label_eventCount"
        Me.label_eventCount.Size = New System.Drawing.Size(202, 15)
        Me.label_eventCount.TabIndex = 3
        Me.label_eventCount.Text = "Device generated timer event count:"
        '
        'label4
        '
        Me.label4.AutoSize = True
        Me.label4.Location = New System.Drawing.Point(190, 85)
        Me.label4.Name = "label4"
        Me.label4.Size = New System.Drawing.Size(22, 15)
        Me.label4.TabIndex = 2
        Me.label4.Text = "Hz"
        '
        'label3
        '
        Me.label3.AutoSize = True
        Me.label3.Location = New System.Drawing.Point(7, 55)
        Me.label3.Name = "label3"
        Me.label3.Size = New System.Drawing.Size(195, 15)
        Me.label3.TabIndex = 1
        Me.label3.Text = "Device generated pulse frequency:"
        '
        'generatedFrequency
        '
        Me.generatedFrequency.Location = New System.Drawing.Point(12, 82)
        Me.generatedFrequency.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.generatedFrequency.Name = "generatedFrequency"
        Me.generatedFrequency.ReadOnly = True
        Me.generatedFrequency.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.generatedFrequency.Size = New System.Drawing.Size(172, 21)
        Me.generatedFrequency.TabIndex = 0
        Me.generatedFrequency.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'label2
        '
        Me.label2.AutoSize = True
        Me.label2.Location = New System.Drawing.Point(212, 43)
        Me.label2.Name = "label2"
        Me.label2.Size = New System.Drawing.Size(22, 15)
        Me.label2.TabIndex = 10
        Me.label2.Text = "Hz"
        '
        'desiredFrequency
        '
        Me.desiredFrequency.Location = New System.Drawing.Point(32, 41)
        Me.desiredFrequency.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.desiredFrequency.Name = "desiredFrequency"
        Me.desiredFrequency.ReadOnly = True
        Me.desiredFrequency.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.desiredFrequency.Size = New System.Drawing.Size(172, 21)
        Me.desiredFrequency.TabIndex = 9
        Me.desiredFrequency.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'label1
        '
        Me.label1.AutoSize = True
        Me.label1.Location = New System.Drawing.Point(29, 17)
        Me.label1.Name = "label1"
        Me.label1.Size = New System.Drawing.Size(109, 15)
        Me.label1.TabIndex = 8
        Me.label1.Text = "Desired frequency:"
        '
        'pictureBox1
        '
        Me.pictureBox1.Image = CType(resources.GetObject("pictureBox1.Image"), System.Drawing.Image)
        Me.pictureBox1.Location = New System.Drawing.Point(236, -1)
        Me.pictureBox1.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.pictureBox1.Name = "pictureBox1"
        Me.pictureBox1.Size = New System.Drawing.Size(153, 66)
        Me.pictureBox1.TabIndex = 13
        Me.pictureBox1.TabStop = False
        '
        'Stop_button
        '
        Me.Stop_button.Location = New System.Drawing.Point(200, 237)
        Me.Stop_button.Name = "Stop_button"
        Me.Stop_button.Size = New System.Drawing.Size(75, 28)
        Me.Stop_button.TabIndex = 14
        Me.Stop_button.Text = "Stop"
        Me.Stop_button.UseVisualStyleBackColor = True
        '
        'm_TimerPulseCtrl
        '
        Me.m_TimerPulseCtrl._StateStream = CType(resources.GetObject("m_TimerPulseCtrl._StateStream"), Automation.BDaq.DeviceStateStreamer)
        '
        'PulseOutputwithTimerInterruptForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(359, 269)
        Me.Controls.Add(Me.Stop_button)
        Me.Controls.Add(Me.Start)
        Me.Controls.Add(Me.groupBox1)
        Me.Controls.Add(Me.label2)
        Me.Controls.Add(Me.desiredFrequency)
        Me.Controls.Add(Me.label1)
        Me.Controls.Add(Me.pictureBox1)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "PulseOutputwithTimerInterruptForm"
        Me.Text = "PulseOutputwithTimerInterrupt"
        Me.groupBox1.ResumeLayout(False)
        Me.groupBox1.PerformLayout()
        CType(Me.pictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Private WithEvents Start As System.Windows.Forms.Button
    Private WithEvents groupBox1 As System.Windows.Forms.GroupBox
    Private WithEvents ExecutionStatus As System.Windows.Forms.Label
    Private WithEvents eventCount As System.Windows.Forms.TextBox
    Private WithEvents label_eventCount As System.Windows.Forms.Label
    Private WithEvents label4 As System.Windows.Forms.Label
    Private WithEvents label3 As System.Windows.Forms.Label
    Private WithEvents generatedFrequency As System.Windows.Forms.TextBox
    Private WithEvents label2 As System.Windows.Forms.Label
    Private WithEvents desiredFrequency As System.Windows.Forms.TextBox
    Private WithEvents label1 As System.Windows.Forms.Label
    Private WithEvents pictureBox1 As System.Windows.Forms.PictureBox
    Friend WithEvents Stop_button As System.Windows.Forms.Button
    Friend WithEvents m_TimerPulseCtrl As Automation.BDaq.TimerPulseCtrl

End Class
