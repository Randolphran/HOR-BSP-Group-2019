<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class EventCounterForm
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(EventCounterForm))
        Me.groupBox1 = New System.Windows.Forms.GroupBox
        Me.Stop_button = New System.Windows.Forms.Button
        Me.CurCounterValue = New System.Windows.Forms.TextBox
        Me.CounterValueList = New System.Windows.Forms.ListBox
        Me.Start_button = New System.Windows.Forms.Button
        Me.pictureBox1 = New System.Windows.Forms.PictureBox
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.m_EventCountCtrl = New Automation.BDaq.EventCounterCtrl(Me.components)
        Me.groupBox1.SuspendLayout()
        CType(Me.pictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'groupBox1
        '
        Me.groupBox1.Controls.Add(Me.Stop_button)
        Me.groupBox1.Controls.Add(Me.CurCounterValue)
        Me.groupBox1.Controls.Add(Me.CounterValueList)
        Me.groupBox1.Controls.Add(Me.Start_button)
        Me.groupBox1.Location = New System.Drawing.Point(9, 28)
        Me.groupBox1.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.groupBox1.Name = "groupBox1"
        Me.groupBox1.Padding = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.groupBox1.Size = New System.Drawing.Size(315, 212)
        Me.groupBox1.TabIndex = 5
        Me.groupBox1.TabStop = False
        '
        'Stop_button
        '
        Me.Stop_button.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Stop_button.Location = New System.Drawing.Point(215, 98)
        Me.Stop_button.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.Stop_button.Name = "Stop_button"
        Me.Stop_button.Size = New System.Drawing.Size(89, 27)
        Me.Stop_button.TabIndex = 5
        Me.Stop_button.Text = "Stop"
        Me.Stop_button.UseVisualStyleBackColor = True
        '
        'CurCounterValue
        '
        Me.CurCounterValue.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.CurCounterValue.ForeColor = System.Drawing.SystemColors.WindowText
        Me.CurCounterValue.Location = New System.Drawing.Point(15, 16)
        Me.CurCounterValue.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.CurCounterValue.Name = "CurCounterValue"
        Me.CurCounterValue.ReadOnly = True
        Me.CurCounterValue.Size = New System.Drawing.Size(186, 26)
        Me.CurCounterValue.TabIndex = 4
        Me.CurCounterValue.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
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
        Me.CounterValueList.Size = New System.Drawing.Size(187, 148)
        Me.CounterValueList.TabIndex = 3
        '
        'Start_button
        '
        Me.Start_button.Font = New System.Drawing.Font("Arial", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Start_button.Location = New System.Drawing.Point(215, 37)
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
        Me.Timer1.Interval = 40
        '
        'm_EventCountCtrl
        '
        Me.m_EventCountCtrl._StateStream = CType(resources.GetObject("m_EventCountCtrl._StateStream"), Automation.BDaq.DeviceStateStreamer)
        '
        'EventCounterForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(343, 250)
        Me.Controls.Add(Me.groupBox1)
        Me.Controls.Add(Me.pictureBox1)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "EventCounterForm"
        Me.Text = "Event Counter"
        Me.groupBox1.ResumeLayout(False)
        Me.groupBox1.PerformLayout()
        CType(Me.pictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
    Private WithEvents groupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents Stop_button As System.Windows.Forms.Button
    Private WithEvents CurCounterValue As System.Windows.Forms.TextBox
    Private WithEvents CounterValueList As System.Windows.Forms.ListBox
    Private WithEvents Start_button As System.Windows.Forms.Button
    Private WithEvents pictureBox1 As System.Windows.Forms.PictureBox
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents m_EventCountCtrl As Automation.BDaq.EventCounterCtrl

End Class
