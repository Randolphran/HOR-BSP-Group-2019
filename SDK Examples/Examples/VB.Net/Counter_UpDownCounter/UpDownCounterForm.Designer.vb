<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class UpDownCounterForm
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(UpDownCounterForm))
        Me.groupBox3 = New System.Windows.Forms.GroupBox
        Me.btnStop = New System.Windows.Forms.Button
        Me.btnValReset = New System.Windows.Forms.Button
        Me.btnStart = New System.Windows.Forms.Button
        Me.CounterValueList = New System.Windows.Forms.ListBox
        Me.txtCounterValue = New System.Windows.Forms.TextBox
        Me.groupBox2 = New System.Windows.Forms.GroupBox
        Me.txtResetTimes = New System.Windows.Forms.TextBox
        Me.label2 = New System.Windows.Forms.Label
        Me.radFinite = New System.Windows.Forms.RadioButton
        Me.raInfinite = New System.Windows.Forms.RadioButton
        Me.radDisable = New System.Windows.Forms.RadioButton
        Me.groupBox1 = New System.Windows.Forms.GroupBox
        Me.txtResetValue = New System.Windows.Forms.TextBox
        Me.label1 = New System.Windows.Forms.Label
        Me.cmbResetValue = New System.Windows.Forms.ComboBox
        Me.UdCounterCtrl1 = New Automation.BDaq.UdCounterCtrl(Me.components)
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.groupBox3.SuspendLayout()
        Me.groupBox2.SuspendLayout()
        Me.groupBox1.SuspendLayout()
        Me.SuspendLayout()
        '
        'groupBox3
        '
        Me.groupBox3.Controls.Add(Me.btnStop)
        Me.groupBox3.Controls.Add(Me.btnValReset)
        Me.groupBox3.Controls.Add(Me.btnStart)
        Me.groupBox3.Controls.Add(Me.CounterValueList)
        Me.groupBox3.Controls.Add(Me.txtCounterValue)
        Me.groupBox3.Location = New System.Drawing.Point(214, 45)
        Me.groupBox3.Name = "groupBox3"
        Me.groupBox3.Size = New System.Drawing.Size(300, 251)
        Me.groupBox3.TabIndex = 5
        Me.groupBox3.TabStop = False
        '
        'btnStop
        '
        Me.btnStop.Location = New System.Drawing.Point(189, 106)
        Me.btnStop.Name = "btnStop"
        Me.btnStop.Size = New System.Drawing.Size(90, 25)
        Me.btnStop.TabIndex = 4
        Me.btnStop.Text = "Stop"
        Me.btnStop.UseVisualStyleBackColor = True
        '
        'btnValReset
        '
        Me.btnValReset.Location = New System.Drawing.Point(189, 173)
        Me.btnValReset.Name = "btnValReset"
        Me.btnValReset.Size = New System.Drawing.Size(90, 25)
        Me.btnValReset.TabIndex = 3
        Me.btnValReset.Text = "ValueReset"
        Me.btnValReset.UseVisualStyleBackColor = True
        '
        'btnStart
        '
        Me.btnStart.Location = New System.Drawing.Point(189, 52)
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
        'groupBox2
        '
        Me.groupBox2.Controls.Add(Me.txtResetTimes)
        Me.groupBox2.Controls.Add(Me.label2)
        Me.groupBox2.Controls.Add(Me.radFinite)
        Me.groupBox2.Controls.Add(Me.raInfinite)
        Me.groupBox2.Controls.Add(Me.radDisable)
        Me.groupBox2.Location = New System.Drawing.Point(13, 136)
        Me.groupBox2.Name = "groupBox2"
        Me.groupBox2.Size = New System.Drawing.Size(188, 161)
        Me.groupBox2.TabIndex = 4
        Me.groupBox2.TabStop = False
        Me.groupBox2.Text = "Index Reset"
        '
        'txtResetTimes
        '
        Me.txtResetTimes.Enabled = False
        Me.txtResetTimes.Location = New System.Drawing.Point(93, 125)
        Me.txtResetTimes.Name = "txtResetTimes"
        Me.txtResetTimes.Size = New System.Drawing.Size(89, 21)
        Me.txtResetTimes.TabIndex = 4
        '
        'label2
        '
        Me.label2.AutoSize = True
        Me.label2.Location = New System.Drawing.Point(13, 125)
        Me.label2.Name = "label2"
        Me.label2.Size = New System.Drawing.Size(79, 15)
        Me.label2.TabIndex = 3
        Me.label2.Text = "Reset Times:"
        '
        'radFinite
        '
        Me.radFinite.AutoSize = True
        Me.radFinite.Location = New System.Drawing.Point(16, 88)
        Me.radFinite.Name = "radFinite"
        Me.radFinite.Size = New System.Drawing.Size(55, 19)
        Me.radFinite.TabIndex = 2
        Me.radFinite.TabStop = True
        Me.radFinite.Text = "Finite"
        Me.radFinite.UseVisualStyleBackColor = True
        '
        'raInfinite
        '
        Me.raInfinite.AutoSize = True
        Me.raInfinite.Location = New System.Drawing.Point(16, 60)
        Me.raInfinite.Name = "raInfinite"
        Me.raInfinite.Size = New System.Drawing.Size(61, 19)
        Me.raInfinite.TabIndex = 1
        Me.raInfinite.TabStop = True
        Me.raInfinite.Text = "Infinite"
        Me.raInfinite.UseVisualStyleBackColor = True
        '
        'radDisable
        '
        Me.radDisable.AutoSize = True
        Me.radDisable.Location = New System.Drawing.Point(16, 34)
        Me.radDisable.Name = "radDisable"
        Me.radDisable.Size = New System.Drawing.Size(67, 19)
        Me.radDisable.TabIndex = 0
        Me.radDisable.TabStop = True
        Me.radDisable.Text = "Disable"
        Me.radDisable.UseVisualStyleBackColor = True
        '
        'groupBox1
        '
        Me.groupBox1.Controls.Add(Me.txtResetValue)
        Me.groupBox1.Controls.Add(Me.label1)
        Me.groupBox1.Controls.Add(Me.cmbResetValue)
        Me.groupBox1.Location = New System.Drawing.Point(12, 45)
        Me.groupBox1.Name = "groupBox1"
        Me.groupBox1.Size = New System.Drawing.Size(190, 87)
        Me.groupBox1.TabIndex = 3
        Me.groupBox1.TabStop = False
        Me.groupBox1.Text = "Reset Value"
        '
        'txtResetValue
        '
        Me.txtResetValue.Enabled = False
        Me.txtResetValue.Location = New System.Drawing.Point(79, 54)
        Me.txtResetValue.Name = "txtResetValue"
        Me.txtResetValue.Size = New System.Drawing.Size(104, 21)
        Me.txtResetValue.TabIndex = 2
        '
        'label1
        '
        Me.label1.AutoSize = True
        Me.label1.Location = New System.Drawing.Point(3, 22)
        Me.label1.Name = "label1"
        Me.label1.Size = New System.Drawing.Size(76, 15)
        Me.label1.TabIndex = 1
        Me.label1.Text = "Reset Value:"
        '
        'cmbResetValue
        '
        Me.cmbResetValue.FormattingEnabled = True
        Me.cmbResetValue.Location = New System.Drawing.Point(79, 20)
        Me.cmbResetValue.Name = "cmbResetValue"
        Me.cmbResetValue.Size = New System.Drawing.Size(105, 23)
        Me.cmbResetValue.TabIndex = 0
        '
        'UdCounterCtrl1
        '
        Me.UdCounterCtrl1._StateStream = CType(resources.GetObject("UdCounterCtrl1._StateStream"), Automation.BDaq.DeviceStateStreamer)
        '
        'Timer1
        '
        Me.Timer1.Interval = 40
        '
        'UpDownCounterForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackgroundImage = CType(resources.GetObject("$this.BackgroundImage"), System.Drawing.Image)
        Me.ClientSize = New System.Drawing.Size(526, 314)
        Me.Controls.Add(Me.groupBox3)
        Me.Controls.Add(Me.groupBox2)
        Me.Controls.Add(Me.groupBox1)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "UpDownCounterForm"
        Me.Text = "UpDownCounter"
        Me.groupBox3.ResumeLayout(False)
        Me.groupBox3.PerformLayout()
        Me.groupBox2.ResumeLayout(False)
        Me.groupBox2.PerformLayout()
        Me.groupBox1.ResumeLayout(False)
        Me.groupBox1.PerformLayout()
        Me.ResumeLayout(False)

    End Sub
    Private WithEvents groupBox3 As System.Windows.Forms.GroupBox
    Private WithEvents btnStop As System.Windows.Forms.Button
    Private WithEvents btnValReset As System.Windows.Forms.Button
    Private WithEvents btnStart As System.Windows.Forms.Button
    Private WithEvents CounterValueList As System.Windows.Forms.ListBox
    Private WithEvents txtCounterValue As System.Windows.Forms.TextBox
    Private WithEvents groupBox2 As System.Windows.Forms.GroupBox
    Private WithEvents txtResetTimes As System.Windows.Forms.TextBox
    Private WithEvents label2 As System.Windows.Forms.Label
    Private WithEvents radFinite As System.Windows.Forms.RadioButton
    Private WithEvents raInfinite As System.Windows.Forms.RadioButton
    Private WithEvents radDisable As System.Windows.Forms.RadioButton
    Private WithEvents groupBox1 As System.Windows.Forms.GroupBox
    Private WithEvents txtResetValue As System.Windows.Forms.TextBox
    Private WithEvents label1 As System.Windows.Forms.Label
    Private WithEvents cmbResetValue As System.Windows.Forms.ComboBox
    Friend WithEvents UdCounterCtrl1 As Automation.BDaq.UdCounterCtrl
    Friend WithEvents Timer1 As System.Windows.Forms.Timer

End Class
