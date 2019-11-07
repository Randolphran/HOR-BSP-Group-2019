<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class DelayedPulseGenerationForm
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(DelayedPulseGenerationForm))
        Me.groupBox1 = New System.Windows.Forms.GroupBox
        Me.delayCount = New System.Windows.Forms.TextBox
        Me.label1 = New System.Windows.Forms.Label
        Me.eventCount = New System.Windows.Forms.TextBox
        Me.label_shotCount = New System.Windows.Forms.Label
        Me.ExecutionStatus = New System.Windows.Forms.Label
        Me.Start_button = New System.Windows.Forms.Button
        Me.pictureBox1 = New System.Windows.Forms.PictureBox
        Me.Stop_button = New System.Windows.Forms.Button
        Me.m_OneShotCtrl = New Automation.BDaq.OneShotCtrl(Me.components)
        Me.groupBox1.SuspendLayout()
        CType(Me.pictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'groupBox1
        '
        Me.groupBox1.Controls.Add(Me.delayCount)
        Me.groupBox1.Controls.Add(Me.label1)
        Me.groupBox1.Controls.Add(Me.eventCount)
        Me.groupBox1.Controls.Add(Me.label_shotCount)
        Me.groupBox1.Controls.Add(Me.ExecutionStatus)
        Me.groupBox1.Location = New System.Drawing.Point(8, 29)
        Me.groupBox1.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.groupBox1.Name = "groupBox1"
        Me.groupBox1.Padding = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.groupBox1.Size = New System.Drawing.Size(294, 143)
        Me.groupBox1.TabIndex = 12
        Me.groupBox1.TabStop = False
        Me.groupBox1.Text = "Execution status"
        '
        'delayCount
        '
        Me.delayCount.Location = New System.Drawing.Point(128, 67)
        Me.delayCount.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.delayCount.Name = "delayCount"
        Me.delayCount.ReadOnly = True
        Me.delayCount.Size = New System.Drawing.Size(137, 21)
        Me.delayCount.TabIndex = 13
        '
        'label1
        '
        Me.label1.AutoSize = True
        Me.label1.Location = New System.Drawing.Point(19, 67)
        Me.label1.Name = "label1"
        Me.label1.Size = New System.Drawing.Size(74, 15)
        Me.label1.TabIndex = 12
        Me.label1.Text = "Delay count:"
        '
        'eventCount
        '
        Me.eventCount.Location = New System.Drawing.Point(128, 103)
        Me.eventCount.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.eventCount.Name = "eventCount"
        Me.eventCount.ReadOnly = True
        Me.eventCount.Size = New System.Drawing.Size(137, 21)
        Me.eventCount.TabIndex = 11
        '
        'label_shotCount
        '
        Me.label_shotCount.Location = New System.Drawing.Point(19, 103)
        Me.label_shotCount.Name = "label_shotCount"
        Me.label_shotCount.Size = New System.Drawing.Size(103, 33)
        Me.label_shotCount.TabIndex = 8
        Me.label_shotCount.Text = "Delayed Pulse count:"
        '
        'ExecutionStatus
        '
        Me.ExecutionStatus.Image = CType(resources.GetObject("ExecutionStatus.Image"), System.Drawing.Image)
        Me.ExecutionStatus.Location = New System.Drawing.Point(19, 24)
        Me.ExecutionStatus.Name = "ExecutionStatus"
        Me.ExecutionStatus.Size = New System.Drawing.Size(246, 29)
        Me.ExecutionStatus.TabIndex = 7
        '
        'Start_button
        '
        Me.Start_button.Font = New System.Drawing.Font("Arial", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Start_button.Location = New System.Drawing.Point(53, 180)
        Me.Start_button.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.Start_button.Name = "Start_button"
        Me.Start_button.Size = New System.Drawing.Size(77, 28)
        Me.Start_button.TabIndex = 11
        Me.Start_button.Text = "Start"
        Me.Start_button.UseVisualStyleBackColor = True
        '
        'pictureBox1
        '
        Me.pictureBox1.BackgroundImage = CType(resources.GetObject("pictureBox1.BackgroundImage"), System.Drawing.Image)
        Me.pictureBox1.Location = New System.Drawing.Point(116, -19)
        Me.pictureBox1.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.pictureBox1.Name = "pictureBox1"
        Me.pictureBox1.Size = New System.Drawing.Size(278, 92)
        Me.pictureBox1.TabIndex = 13
        Me.pictureBox1.TabStop = False
        '
        'Stop_button
        '
        Me.Stop_button.Font = New System.Drawing.Font("Arial", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Stop_button.Location = New System.Drawing.Point(180, 180)
        Me.Stop_button.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.Stop_button.Name = "Stop_button"
        Me.Stop_button.Size = New System.Drawing.Size(77, 28)
        Me.Stop_button.TabIndex = 14
        Me.Stop_button.Text = "Stop"
        Me.Stop_button.UseVisualStyleBackColor = True
        '
        'm_OneShotCtrl
        '
        Me.m_OneShotCtrl._StateStream = CType(resources.GetObject("m_OneShotCtrl._StateStream"), Automation.BDaq.DeviceStateStreamer)
        '
        'DelayedPulseGenerationForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(333, 215)
        Me.Controls.Add(Me.Stop_button)
        Me.Controls.Add(Me.groupBox1)
        Me.Controls.Add(Me.Start_button)
        Me.Controls.Add(Me.pictureBox1)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "DelayedPulseGenerationForm"
        Me.Text = "DelayedPulseGeneration"
        Me.groupBox1.ResumeLayout(False)
        Me.groupBox1.PerformLayout()
        CType(Me.pictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
    Private WithEvents groupBox1 As System.Windows.Forms.GroupBox
    Private WithEvents delayCount As System.Windows.Forms.TextBox
    Private WithEvents label1 As System.Windows.Forms.Label
    Private WithEvents eventCount As System.Windows.Forms.TextBox
    Private WithEvents label_shotCount As System.Windows.Forms.Label
    Private WithEvents ExecutionStatus As System.Windows.Forms.Label
    Private WithEvents Start_button As System.Windows.Forms.Button
    Private WithEvents pictureBox1 As System.Windows.Forms.PictureBox
    Private WithEvents Stop_button As System.Windows.Forms.Button
    Friend WithEvents m_OneShotCtrl As Automation.BDaq.OneShotCtrl

End Class
