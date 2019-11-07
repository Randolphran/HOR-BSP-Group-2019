<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class PulseWidthMeasurementForm
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(PulseWidthMeasurementForm))
        Me.groupBox1 = New System.Windows.Forms.GroupBox
        Me.Label3 = New System.Windows.Forms.Label
        Me.Label4 = New System.Windows.Forms.Label
        Me.CurLoPeriod = New System.Windows.Forms.TextBox
        Me.Label2 = New System.Windows.Forms.Label
        Me.Label1 = New System.Windows.Forms.Label
        Me.Stop_button = New System.Windows.Forms.Button
        Me.CurHiPeriod = New System.Windows.Forms.TextBox
        Me.CounterValueList = New System.Windows.Forms.ListBox
        Me.Start_button = New System.Windows.Forms.Button
        Me.pictureBox1 = New System.Windows.Forms.PictureBox
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.m_PwMeterCtrl = New Automation.BDaq.PwMeterCtrl(Me.components)
        Me.groupBox1.SuspendLayout()
        CType(Me.pictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'groupBox1
        '
        Me.groupBox1.Controls.Add(Me.Label3)
        Me.groupBox1.Controls.Add(Me.Label4)
        Me.groupBox1.Controls.Add(Me.CurLoPeriod)
        Me.groupBox1.Controls.Add(Me.Label2)
        Me.groupBox1.Controls.Add(Me.Label1)
        Me.groupBox1.Controls.Add(Me.Stop_button)
        Me.groupBox1.Controls.Add(Me.CurHiPeriod)
        Me.groupBox1.Controls.Add(Me.CounterValueList)
        Me.groupBox1.Controls.Add(Me.Start_button)
        Me.groupBox1.Location = New System.Drawing.Point(9, 35)
        Me.groupBox1.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.groupBox1.Name = "groupBox1"
        Me.groupBox1.Padding = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.groupBox1.Size = New System.Drawing.Size(327, 212)
        Me.groupBox1.TabIndex = 5
        Me.groupBox1.TabStop = False
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(201, 54)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(15, 15)
        Me.Label3.TabIndex = 10
        Me.Label3.Text = "S"
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(15, 53)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(72, 15)
        Me.Label4.TabIndex = 9
        Me.Label4.Text = "Low Period:"
        '
        'CurLoPeriod
        '
        Me.CurLoPeriod.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.CurLoPeriod.ForeColor = System.Drawing.SystemColors.WindowText
        Me.CurLoPeriod.Location = New System.Drawing.Point(99, 48)
        Me.CurLoPeriod.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.CurLoPeriod.Name = "CurLoPeriod"
        Me.CurLoPeriod.ReadOnly = True
        Me.CurLoPeriod.Size = New System.Drawing.Size(89, 26)
        Me.CurLoPeriod.TabIndex = 8
        Me.CurLoPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(201, 22)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(15, 15)
        Me.Label2.TabIndex = 7
        Me.Label2.Text = "S"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(15, 21)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(75, 15)
        Me.Label1.TabIndex = 6
        Me.Label1.Text = "High Period:"
        '
        'Stop_button
        '
        Me.Stop_button.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Stop_button.Location = New System.Drawing.Point(229, 98)
        Me.Stop_button.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.Stop_button.Name = "Stop_button"
        Me.Stop_button.Size = New System.Drawing.Size(89, 27)
        Me.Stop_button.TabIndex = 5
        Me.Stop_button.Text = "Stop"
        Me.Stop_button.UseVisualStyleBackColor = True
        '
        'CurHiPeriod
        '
        Me.CurHiPeriod.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.CurHiPeriod.ForeColor = System.Drawing.SystemColors.WindowText
        Me.CurHiPeriod.Location = New System.Drawing.Point(99, 16)
        Me.CurHiPeriod.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.CurHiPeriod.Name = "CurHiPeriod"
        Me.CurHiPeriod.ReadOnly = True
        Me.CurHiPeriod.Size = New System.Drawing.Size(89, 26)
        Me.CurHiPeriod.TabIndex = 4
        Me.CurHiPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'CounterValueList
        '
        Me.CounterValueList.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.CounterValueList.ForeColor = System.Drawing.SystemColors.WindowText
        Me.CounterValueList.FormattingEnabled = True
        Me.CounterValueList.ItemHeight = 18
        Me.CounterValueList.Location = New System.Drawing.Point(8, 91)
        Me.CounterValueList.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.CounterValueList.Name = "CounterValueList"
        Me.CounterValueList.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.CounterValueList.Size = New System.Drawing.Size(214, 112)
        Me.CounterValueList.TabIndex = 3
        '
        'Start_button
        '
        Me.Start_button.Font = New System.Drawing.Font("Arial", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Start_button.Location = New System.Drawing.Point(229, 37)
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
        Me.pictureBox1.Location = New System.Drawing.Point(185, -10)
        Me.pictureBox1.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.pictureBox1.Name = "pictureBox1"
        Me.pictureBox1.Size = New System.Drawing.Size(191, 71)
        Me.pictureBox1.TabIndex = 6
        Me.pictureBox1.TabStop = False
        '
        'Timer1
        '
        Me.Timer1.Interval = 500
        '
        'm_PwMeterCtrl
        '
        Me.m_PwMeterCtrl._StateStream = CType(resources.GetObject("m_PwMeterCtrl._StateStream"), Automation.BDaq.DeviceStateStreamer)
        '
        'PulseWidthMeasurementForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(352, 258)
        Me.Controls.Add(Me.groupBox1)
        Me.Controls.Add(Me.pictureBox1)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "PulseWidthMeasurementForm"
        Me.Text = "PulseWidthMeasurement"
        Me.groupBox1.ResumeLayout(False)
        Me.groupBox1.PerformLayout()
        CType(Me.pictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
    Private WithEvents groupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents Stop_button As System.Windows.Forms.Button
    Private WithEvents CurHiPeriod As System.Windows.Forms.TextBox
    Private WithEvents CounterValueList As System.Windows.Forms.ListBox
    Private WithEvents Start_button As System.Windows.Forms.Button
    Private WithEvents pictureBox1 As System.Windows.Forms.PictureBox
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Private WithEvents CurLoPeriod As System.Windows.Forms.TextBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents m_PwMeterCtrl As Automation.BDaq.PwMeterCtrl

End Class
