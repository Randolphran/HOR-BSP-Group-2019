<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class SnapCounterForm
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(SnapCounterForm))
        Me.groupBox3 = New System.Windows.Forms.GroupBox
        Me.btnStop = New System.Windows.Forms.Button
        Me.btnStart = New System.Windows.Forms.Button
        Me.CounterValueList = New System.Windows.Forms.ListBox
        Me.txtCounterValue = New System.Windows.Forms.TextBox
        Me.txtSnapCount = New System.Windows.Forms.TextBox
        Me.label4 = New System.Windows.Forms.Label
        Me.groupBox1 = New System.Windows.Forms.GroupBox
        Me.label3 = New System.Windows.Forms.Label
        Me.txtTimeInterval = New System.Windows.Forms.TextBox
        Me.label2 = New System.Windows.Forms.Label
        Me.listSnapSource = New System.Windows.Forms.ListBox
        Me.label1 = New System.Windows.Forms.Label
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.UdCounterCtrl1 = New Automation.BDaq.UdCounterCtrl(Me.components)
        Me.groupBox3.SuspendLayout()
        Me.groupBox1.SuspendLayout()
        Me.SuspendLayout()
        '
        'groupBox3
        '
        Me.groupBox3.Controls.Add(Me.btnStop)
        Me.groupBox3.Controls.Add(Me.btnStart)
        Me.groupBox3.Controls.Add(Me.CounterValueList)
        Me.groupBox3.Controls.Add(Me.txtCounterValue)
        Me.groupBox3.Location = New System.Drawing.Point(213, 45)
        Me.groupBox3.Name = "groupBox3"
        Me.groupBox3.Size = New System.Drawing.Size(300, 251)
        Me.groupBox3.TabIndex = 9
        Me.groupBox3.TabStop = False
        '
        'btnStop
        '
        Me.btnStop.Location = New System.Drawing.Point(189, 127)
        Me.btnStop.Name = "btnStop"
        Me.btnStop.Size = New System.Drawing.Size(90, 25)
        Me.btnStop.TabIndex = 4
        Me.btnStop.Text = "Stop"
        Me.btnStop.UseVisualStyleBackColor = True
        '
        'btnStart
        '
        Me.btnStart.Location = New System.Drawing.Point(189, 73)
        Me.btnStart.Name = "btnStart"
        Me.btnStart.Size = New System.Drawing.Size(90, 25)
        Me.btnStart.TabIndex = 2
        Me.btnStart.Text = "Start"
        Me.btnStart.UseVisualStyleBackColor = True
        '
        'CounterValueList
        '
        Me.CounterValueList.FormattingEnabled = True
        Me.CounterValueList.ItemHeight = 15
        Me.CounterValueList.Location = New System.Drawing.Point(9, 54)
        Me.CounterValueList.Name = "CounterValueList"
        Me.CounterValueList.Size = New System.Drawing.Size(156, 184)
        Me.CounterValueList.TabIndex = 1
        '
        'txtCounterValue
        '
        Me.txtCounterValue.Location = New System.Drawing.Point(9, 23)
        Me.txtCounterValue.Name = "txtCounterValue"
        Me.txtCounterValue.Size = New System.Drawing.Size(157, 21)
        Me.txtCounterValue.TabIndex = 0
        '
        'txtSnapCount
        '
        Me.txtSnapCount.Enabled = False
        Me.txtSnapCount.Location = New System.Drawing.Point(101, 266)
        Me.txtSnapCount.Name = "txtSnapCount"
        Me.txtSnapCount.Size = New System.Drawing.Size(81, 21)
        Me.txtSnapCount.TabIndex = 8
        '
        'label4
        '
        Me.label4.AutoSize = True
        Me.label4.Location = New System.Drawing.Point(28, 267)
        Me.label4.Name = "label4"
        Me.label4.Size = New System.Drawing.Size(72, 15)
        Me.label4.TabIndex = 7
        Me.label4.Text = "Snap count:"
        '
        'groupBox1
        '
        Me.groupBox1.Controls.Add(Me.label3)
        Me.groupBox1.Controls.Add(Me.txtTimeInterval)
        Me.groupBox1.Controls.Add(Me.label2)
        Me.groupBox1.Controls.Add(Me.listSnapSource)
        Me.groupBox1.Controls.Add(Me.label1)
        Me.groupBox1.Location = New System.Drawing.Point(11, 45)
        Me.groupBox1.Name = "groupBox1"
        Me.groupBox1.Size = New System.Drawing.Size(190, 214)
        Me.groupBox1.TabIndex = 6
        Me.groupBox1.TabStop = False
        '
        'label3
        '
        Me.label3.AutoSize = True
        Me.label3.Location = New System.Drawing.Point(20, 191)
        Me.label3.Name = "label3"
        Me.label3.Size = New System.Drawing.Size(137, 15)
        Me.label3.TabIndex = 4
        Me.label3.Text = "(From 0.02Hz to 50kHz)"
        '
        'txtTimeInterval
        '
        Me.txtTimeInterval.Enabled = False
        Me.txtTimeInterval.Location = New System.Drawing.Point(90, 168)
        Me.txtTimeInterval.Name = "txtTimeInterval"
        Me.txtTimeInterval.Size = New System.Drawing.Size(81, 21)
        Me.txtTimeInterval.TabIndex = 3
        '
        'label2
        '
        Me.label2.AutoSize = True
        Me.label2.Location = New System.Drawing.Point(8, 168)
        Me.label2.Name = "label2"
        Me.label2.Size = New System.Drawing.Size(80, 15)
        Me.label2.TabIndex = 2
        Me.label2.Text = "Time interval:"
        '
        'listSnapSource
        '
        Me.listSnapSource.FormattingEnabled = True
        Me.listSnapSource.ItemHeight = 15
        Me.listSnapSource.Location = New System.Drawing.Point(11, 34)
        Me.listSnapSource.Name = "listSnapSource"
        Me.listSnapSource.SelectionMode = System.Windows.Forms.SelectionMode.MultiSimple
        Me.listSnapSource.Size = New System.Drawing.Size(161, 124)
        Me.listSnapSource.TabIndex = 1
        '
        'label1
        '
        Me.label1.AutoSize = True
        Me.label1.Location = New System.Drawing.Point(7, 12)
        Me.label1.Name = "label1"
        Me.label1.Size = New System.Drawing.Size(79, 15)
        Me.label1.TabIndex = 0
        Me.label1.Text = "Snap source:"
        '
        'Timer1
        '
        Me.Timer1.Interval = 40
        '
        'UdCounterCtrl1
        '
        Me.UdCounterCtrl1._StateStream = CType(resources.GetObject("UdCounterCtrl1._StateStream"), Automation.BDaq.DeviceStateStreamer)
        '
        'SnapCounterForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackgroundImage = CType(resources.GetObject("$this.BackgroundImage"), System.Drawing.Image)
        Me.ClientSize = New System.Drawing.Size(525, 313)
        Me.Controls.Add(Me.groupBox3)
        Me.Controls.Add(Me.txtSnapCount)
        Me.Controls.Add(Me.label4)
        Me.Controls.Add(Me.groupBox1)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "SnapCounterForm"
        Me.Text = "SnapCounter"
        Me.groupBox3.ResumeLayout(False)
        Me.groupBox3.PerformLayout()
        Me.groupBox1.ResumeLayout(False)
        Me.groupBox1.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Private WithEvents groupBox3 As System.Windows.Forms.GroupBox
    Private WithEvents btnStop As System.Windows.Forms.Button
    Private WithEvents btnStart As System.Windows.Forms.Button
    Private WithEvents CounterValueList As System.Windows.Forms.ListBox
    Private WithEvents txtCounterValue As System.Windows.Forms.TextBox
    Private WithEvents txtSnapCount As System.Windows.Forms.TextBox
    Private WithEvents label4 As System.Windows.Forms.Label
    Private WithEvents groupBox1 As System.Windows.Forms.GroupBox
    Private WithEvents label3 As System.Windows.Forms.Label
    Private WithEvents txtTimeInterval As System.Windows.Forms.TextBox
    Private WithEvents label2 As System.Windows.Forms.Label
    Private WithEvents listSnapSource As System.Windows.Forms.ListBox
    Private WithEvents label1 As System.Windows.Forms.Label
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents UdCounterCtrl1 As Automation.BDaq.UdCounterCtrl

End Class
