<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class PWMOutputForm
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(PWMOutputForm))
        Me.Start = New System.Windows.Forms.Button
        Me.groupBox1 = New System.Windows.Forms.GroupBox
        Me.Label6 = New System.Windows.Forms.Label
        Me.generatedLoPeriod = New System.Windows.Forms.TextBox
        Me.ExecutionStatus = New System.Windows.Forms.Label
        Me.label4 = New System.Windows.Forms.Label
        Me.label3 = New System.Windows.Forms.Label
        Me.generatedHiPeriod = New System.Windows.Forms.TextBox
        Me.label2 = New System.Windows.Forms.Label
        Me.desiredHiPeriod = New System.Windows.Forms.TextBox
        Me.label1 = New System.Windows.Forms.Label
        Me.pictureBox1 = New System.Windows.Forms.PictureBox
        Me.Stop_button = New System.Windows.Forms.Button
        Me.Label5 = New System.Windows.Forms.Label
        Me.Label7 = New System.Windows.Forms.Label
        Me.Label8 = New System.Windows.Forms.Label
        Me.desiredLoPeriod = New System.Windows.Forms.TextBox
        Me.Label9 = New System.Windows.Forms.Label
        Me.Label10 = New System.Windows.Forms.Label
        Me.m_PwModulatorCtrl = New Automation.BDaq.PwModulatorCtrl(Me.components)
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
        Me.groupBox1.Controls.Add(Me.Label6)
        Me.groupBox1.Controls.Add(Me.generatedLoPeriod)
        Me.groupBox1.Controls.Add(Me.ExecutionStatus)
        Me.groupBox1.Controls.Add(Me.label4)
        Me.groupBox1.Controls.Add(Me.label3)
        Me.groupBox1.Controls.Add(Me.generatedHiPeriod)
        Me.groupBox1.Location = New System.Drawing.Point(22, 101)
        Me.groupBox1.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.groupBox1.Name = "groupBox1"
        Me.groupBox1.Padding = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.groupBox1.Size = New System.Drawing.Size(301, 130)
        Me.groupBox1.TabIndex = 11
        Me.groupBox1.TabStop = False
        Me.groupBox1.Text = "Execution status "
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Location = New System.Drawing.Point(190, 103)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(15, 15)
        Me.Label6.TabIndex = 7
        Me.Label6.Text = "S"
        '
        'generatedLoPeriod
        '
        Me.generatedLoPeriod.Location = New System.Drawing.Point(105, 100)
        Me.generatedLoPeriod.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.generatedLoPeriod.Name = "generatedLoPeriod"
        Me.generatedLoPeriod.ReadOnly = True
        Me.generatedLoPeriod.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.generatedLoPeriod.Size = New System.Drawing.Size(77, 21)
        Me.generatedLoPeriod.TabIndex = 6
        Me.generatedLoPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'ExecutionStatus
        '
        Me.ExecutionStatus.Enabled = False
        Me.ExecutionStatus.Image = CType(resources.GetObject("ExecutionStatus.Image"), System.Drawing.Image)
        Me.ExecutionStatus.Location = New System.Drawing.Point(7, 20)
        Me.ExecutionStatus.Name = "ExecutionStatus"
        Me.ExecutionStatus.Size = New System.Drawing.Size(246, 29)
        Me.ExecutionStatus.TabIndex = 5
        '
        'label4
        '
        Me.label4.AutoSize = True
        Me.label4.Location = New System.Drawing.Point(190, 76)
        Me.label4.Name = "label4"
        Me.label4.Size = New System.Drawing.Size(15, 15)
        Me.label4.TabIndex = 2
        Me.label4.Text = "S"
        '
        'label3
        '
        Me.label3.AutoSize = True
        Me.label3.Location = New System.Drawing.Point(7, 53)
        Me.label3.Name = "label3"
        Me.label3.Size = New System.Drawing.Size(195, 15)
        Me.label3.TabIndex = 1
        Me.label3.Text = "Device generated pulse frequency:"
        '
        'generatedHiPeriod
        '
        Me.generatedHiPeriod.Location = New System.Drawing.Point(105, 73)
        Me.generatedHiPeriod.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.generatedHiPeriod.Name = "generatedHiPeriod"
        Me.generatedHiPeriod.ReadOnly = True
        Me.generatedHiPeriod.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.generatedHiPeriod.Size = New System.Drawing.Size(77, 21)
        Me.generatedHiPeriod.TabIndex = 0
        Me.generatedHiPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'label2
        '
        Me.label2.AutoSize = True
        Me.label2.Location = New System.Drawing.Point(212, 43)
        Me.label2.Name = "label2"
        Me.label2.Size = New System.Drawing.Size(15, 15)
        Me.label2.TabIndex = 10
        Me.label2.Text = "S"
        '
        'desiredHiPeriod
        '
        Me.desiredHiPeriod.Location = New System.Drawing.Point(127, 41)
        Me.desiredHiPeriod.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.desiredHiPeriod.Name = "desiredHiPeriod"
        Me.desiredHiPeriod.ReadOnly = True
        Me.desiredHiPeriod.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.desiredHiPeriod.Size = New System.Drawing.Size(77, 21)
        Me.desiredHiPeriod.TabIndex = 9
        Me.desiredHiPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
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
        Me.pictureBox1.Location = New System.Drawing.Point(211, -1)
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
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(46, 41)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(75, 15)
        Me.Label5.TabIndex = 6
        Me.Label5.Text = "High Period:"
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.Location = New System.Drawing.Point(45, 67)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(72, 15)
        Me.Label7.TabIndex = 15
        Me.Label7.Text = "Low Period:"
        '
        'Label8
        '
        Me.Label8.AutoSize = True
        Me.Label8.Location = New System.Drawing.Point(212, 69)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(15, 15)
        Me.Label8.TabIndex = 17
        Me.Label8.Text = "S"
        '
        'desiredLoPeriod
        '
        Me.desiredLoPeriod.Location = New System.Drawing.Point(127, 67)
        Me.desiredLoPeriod.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.desiredLoPeriod.Name = "desiredLoPeriod"
        Me.desiredLoPeriod.ReadOnly = True
        Me.desiredLoPeriod.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.desiredLoPeriod.Size = New System.Drawing.Size(77, 21)
        Me.desiredLoPeriod.TabIndex = 16
        Me.desiredLoPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'Label9
        '
        Me.Label9.AutoSize = True
        Me.Label9.Location = New System.Drawing.Point(49, 203)
        Me.Label9.Name = "Label9"
        Me.Label9.Size = New System.Drawing.Size(72, 15)
        Me.Label9.TabIndex = 19
        Me.Label9.Text = "Low Period:"
        '
        'Label10
        '
        Me.Label10.AutoSize = True
        Me.Label10.Location = New System.Drawing.Point(50, 177)
        Me.Label10.Name = "Label10"
        Me.Label10.Size = New System.Drawing.Size(75, 15)
        Me.Label10.TabIndex = 18
        Me.Label10.Text = "High Period:"
        '
        'm_PwModulatorCtrl
        '
        Me.m_PwModulatorCtrl._StateStream = CType(resources.GetObject("m_PwModulatorCtrl._StateStream"), Automation.BDaq.DeviceStateStreamer)
        '
        'PWMOutputForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(359, 269)
        Me.Controls.Add(Me.Label9)
        Me.Controls.Add(Me.Label10)
        Me.Controls.Add(Me.Label7)
        Me.Controls.Add(Me.Label8)
        Me.Controls.Add(Me.desiredLoPeriod)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.Stop_button)
        Me.Controls.Add(Me.Start)
        Me.Controls.Add(Me.groupBox1)
        Me.Controls.Add(Me.label2)
        Me.Controls.Add(Me.desiredHiPeriod)
        Me.Controls.Add(Me.label1)
        Me.Controls.Add(Me.pictureBox1)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "PWMOutputForm"
        Me.Text = "PWMOutput"
        Me.groupBox1.ResumeLayout(False)
        Me.groupBox1.PerformLayout()
        CType(Me.pictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Private WithEvents Start As System.Windows.Forms.Button
    Private WithEvents groupBox1 As System.Windows.Forms.GroupBox
    Private WithEvents ExecutionStatus As System.Windows.Forms.Label
    Private WithEvents label4 As System.Windows.Forms.Label
    Private WithEvents label3 As System.Windows.Forms.Label
    Private WithEvents generatedHiPeriod As System.Windows.Forms.TextBox
    Private WithEvents label2 As System.Windows.Forms.Label
    Private WithEvents desiredHiPeriod As System.Windows.Forms.TextBox
    Private WithEvents label1 As System.Windows.Forms.Label
    Private WithEvents pictureBox1 As System.Windows.Forms.PictureBox
    Friend WithEvents Stop_button As System.Windows.Forms.Button
    Private WithEvents Label6 As System.Windows.Forms.Label
    Private WithEvents generatedLoPeriod As System.Windows.Forms.TextBox
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents Label7 As System.Windows.Forms.Label
    Private WithEvents Label8 As System.Windows.Forms.Label
    Private WithEvents desiredLoPeriod As System.Windows.Forms.TextBox
    Friend WithEvents Label9 As System.Windows.Forms.Label
    Friend WithEvents Label10 As System.Windows.Forms.Label
    Friend WithEvents m_PwModulatorCtrl As Automation.BDaq.PwModulatorCtrl

End Class
