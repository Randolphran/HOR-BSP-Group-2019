<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class ContinueCompareForm
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(ContinueCompareForm))
        Me.radTable = New System.Windows.Forms.RadioButton
        Me.label14 = New System.Windows.Forms.Label
        Me.txtEndCount = New System.Windows.Forms.TextBox
        Me.txtPMCount = New System.Windows.Forms.TextBox
        Me.label13 = New System.Windows.Forms.Label
        Me.groupBox3 = New System.Windows.Forms.GroupBox
        Me.btnStop = New System.Windows.Forms.Button
        Me.btnStart = New System.Windows.Forms.Button
        Me.txtCounterValue = New System.Windows.Forms.TextBox
        Me.groupBox2 = New System.Windows.Forms.GroupBox
        Me.groupBox7 = New System.Windows.Forms.GroupBox
        Me.txtInt2Count = New System.Windows.Forms.TextBox
        Me.label10 = New System.Windows.Forms.Label
        Me.txtInt2Increment = New System.Windows.Forms.TextBox
        Me.label11 = New System.Windows.Forms.Label
        Me.txtInt2FirstValue = New System.Windows.Forms.TextBox
        Me.label12 = New System.Windows.Forms.Label
        Me.groupBox6 = New System.Windows.Forms.GroupBox
        Me.txtInt1Count = New System.Windows.Forms.TextBox
        Me.label7 = New System.Windows.Forms.Label
        Me.txtInt1Increment = New System.Windows.Forms.TextBox
        Me.label8 = New System.Windows.Forms.Label
        Me.txtInt1FirstValue = New System.Windows.Forms.TextBox
        Me.label9 = New System.Windows.Forms.Label
        Me.groupBox1 = New System.Windows.Forms.GroupBox
        Me.groupBox5 = New System.Windows.Forms.GroupBox
        Me.txtTab2Data2 = New System.Windows.Forms.TextBox
        Me.label4 = New System.Windows.Forms.Label
        Me.txtTab2Data1 = New System.Windows.Forms.TextBox
        Me.label5 = New System.Windows.Forms.Label
        Me.txtTab2Data0 = New System.Windows.Forms.TextBox
        Me.label6 = New System.Windows.Forms.Label
        Me.groupBox4 = New System.Windows.Forms.GroupBox
        Me.txtTab1Data2 = New System.Windows.Forms.TextBox
        Me.label3 = New System.Windows.Forms.Label
        Me.txtTab1Data1 = New System.Windows.Forms.TextBox
        Me.label2 = New System.Windows.Forms.Label
        Me.txtTab1Data0 = New System.Windows.Forms.TextBox
        Me.label1 = New System.Windows.Forms.Label
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.UdCounterCtrl1 = New Automation.BDaq.UdCounterCtrl(Me.components)
        Me.radInterval = New System.Windows.Forms.RadioButton
        Me.groupBox3.SuspendLayout()
        Me.groupBox2.SuspendLayout()
        Me.groupBox7.SuspendLayout()
        Me.groupBox6.SuspendLayout()
        Me.groupBox1.SuspendLayout()
        Me.groupBox5.SuspendLayout()
        Me.groupBox4.SuspendLayout()
        Me.SuspendLayout()
        '
        'radTable
        '
        Me.radTable.AutoSize = True
        Me.radTable.Checked = True
        Me.radTable.Location = New System.Drawing.Point(19, 32)
        Me.radTable.Name = "radTable"
        Me.radTable.Size = New System.Drawing.Size(106, 19)
        Me.radTable.TabIndex = 15
        Me.radTable.TabStop = True
        Me.radTable.Text = "Compare table"
        Me.radTable.UseVisualStyleBackColor = True
        '
        'label14
        '
        Me.label14.AutoSize = True
        Me.label14.Location = New System.Drawing.Point(270, 281)
        Me.label14.Name = "label14"
        Me.label14.Size = New System.Drawing.Size(148, 15)
        Me.label14.TabIndex = 14
        Me.label14.Text = "Compare table end count:"
        '
        'txtEndCount
        '
        Me.txtEndCount.Location = New System.Drawing.Point(421, 280)
        Me.txtEndCount.Name = "txtEndCount"
        Me.txtEndCount.ReadOnly = True
        Me.txtEndCount.Size = New System.Drawing.Size(76, 21)
        Me.txtEndCount.TabIndex = 13
        '
        'txtPMCount
        '
        Me.txtPMCount.Location = New System.Drawing.Point(174, 280)
        Me.txtPMCount.Name = "txtPMCount"
        Me.txtPMCount.ReadOnly = True
        Me.txtPMCount.Size = New System.Drawing.Size(76, 21)
        Me.txtPMCount.TabIndex = 12
        '
        'label13
        '
        Me.label13.AutoSize = True
        Me.label13.Location = New System.Drawing.Point(9, 281)
        Me.label13.Name = "label13"
        Me.label13.Size = New System.Drawing.Size(164, 15)
        Me.label13.TabIndex = 11
        Me.label13.Text = "Counter pattern match count:"
        '
        'groupBox3
        '
        Me.groupBox3.Controls.Add(Me.btnStop)
        Me.groupBox3.Controls.Add(Me.btnStart)
        Me.groupBox3.Controls.Add(Me.txtCounterValue)
        Me.groupBox3.Location = New System.Drawing.Point(386, 44)
        Me.groupBox3.Name = "groupBox3"
        Me.groupBox3.Size = New System.Drawing.Size(129, 222)
        Me.groupBox3.TabIndex = 10
        Me.groupBox3.TabStop = False
        '
        'btnStop
        '
        Me.btnStop.Location = New System.Drawing.Point(21, 170)
        Me.btnStop.Name = "btnStop"
        Me.btnStop.Size = New System.Drawing.Size(87, 24)
        Me.btnStop.TabIndex = 2
        Me.btnStop.Text = "Stop"
        Me.btnStop.UseVisualStyleBackColor = True
        '
        'btnStart
        '
        Me.btnStart.Location = New System.Drawing.Point(20, 106)
        Me.btnStart.Name = "btnStart"
        Me.btnStart.Size = New System.Drawing.Size(87, 24)
        Me.btnStart.TabIndex = 1
        Me.btnStart.Text = "Start"
        Me.btnStart.UseVisualStyleBackColor = True
        '
        'txtCounterValue
        '
        Me.txtCounterValue.Location = New System.Drawing.Point(9, 27)
        Me.txtCounterValue.Name = "txtCounterValue"
        Me.txtCounterValue.Size = New System.Drawing.Size(110, 21)
        Me.txtCounterValue.TabIndex = 0
        '
        'groupBox2
        '
        Me.groupBox2.Controls.Add(Me.groupBox7)
        Me.groupBox2.Controls.Add(Me.groupBox6)
        Me.groupBox2.Location = New System.Drawing.Point(206, 44)
        Me.groupBox2.Name = "groupBox2"
        Me.groupBox2.Size = New System.Drawing.Size(169, 222)
        Me.groupBox2.TabIndex = 9
        Me.groupBox2.TabStop = False
        '
        'groupBox7
        '
        Me.groupBox7.Controls.Add(Me.txtInt2Count)
        Me.groupBox7.Controls.Add(Me.label10)
        Me.groupBox7.Controls.Add(Me.txtInt2Increment)
        Me.groupBox7.Controls.Add(Me.label11)
        Me.groupBox7.Controls.Add(Me.txtInt2FirstValue)
        Me.groupBox7.Controls.Add(Me.label12)
        Me.groupBox7.Location = New System.Drawing.Point(10, 115)
        Me.groupBox7.Name = "groupBox7"
        Me.groupBox7.Size = New System.Drawing.Size(149, 101)
        Me.groupBox7.TabIndex = 1
        Me.groupBox7.TabStop = False
        Me.groupBox7.Text = "Interval 2"
        '
        'txtInt2Count
        '
        Me.txtInt2Count.Location = New System.Drawing.Point(81, 72)
        Me.txtInt2Count.Name = "txtInt2Count"
        Me.txtInt2Count.Size = New System.Drawing.Size(60, 21)
        Me.txtInt2Count.TabIndex = 11
        '
        'label10
        '
        Me.label10.AutoSize = True
        Me.label10.Location = New System.Drawing.Point(5, 73)
        Me.label10.Name = "label10"
        Me.label10.Size = New System.Drawing.Size(42, 15)
        Me.label10.TabIndex = 10
        Me.label10.Text = "Count:"
        '
        'txtInt2Increment
        '
        Me.txtInt2Increment.Location = New System.Drawing.Point(80, 44)
        Me.txtInt2Increment.Name = "txtInt2Increment"
        Me.txtInt2Increment.Size = New System.Drawing.Size(60, 21)
        Me.txtInt2Increment.TabIndex = 9
        '
        'label11
        '
        Me.label11.AutoSize = True
        Me.label11.Location = New System.Drawing.Point(4, 44)
        Me.label11.Name = "label11"
        Me.label11.Size = New System.Drawing.Size(65, 15)
        Me.label11.TabIndex = 8
        Me.label11.Text = "Increment:"
        '
        'txtInt2FirstValue
        '
        Me.txtInt2FirstValue.Location = New System.Drawing.Point(80, 15)
        Me.txtInt2FirstValue.Name = "txtInt2FirstValue"
        Me.txtInt2FirstValue.Size = New System.Drawing.Size(60, 21)
        Me.txtInt2FirstValue.TabIndex = 7
        '
        'label12
        '
        Me.label12.AutoSize = True
        Me.label12.Location = New System.Drawing.Point(3, 18)
        Me.label12.Name = "label12"
        Me.label12.Size = New System.Drawing.Size(64, 15)
        Me.label12.TabIndex = 6
        Me.label12.Text = "FirstValue:"
        '
        'groupBox6
        '
        Me.groupBox6.Controls.Add(Me.txtInt1Count)
        Me.groupBox6.Controls.Add(Me.label7)
        Me.groupBox6.Controls.Add(Me.txtInt1Increment)
        Me.groupBox6.Controls.Add(Me.label8)
        Me.groupBox6.Controls.Add(Me.txtInt1FirstValue)
        Me.groupBox6.Controls.Add(Me.label9)
        Me.groupBox6.Location = New System.Drawing.Point(10, 13)
        Me.groupBox6.Name = "groupBox6"
        Me.groupBox6.Size = New System.Drawing.Size(149, 101)
        Me.groupBox6.TabIndex = 0
        Me.groupBox6.TabStop = False
        Me.groupBox6.Text = "Interval 1"
        '
        'txtInt1Count
        '
        Me.txtInt1Count.Location = New System.Drawing.Point(81, 72)
        Me.txtInt1Count.Name = "txtInt1Count"
        Me.txtInt1Count.Size = New System.Drawing.Size(60, 21)
        Me.txtInt1Count.TabIndex = 11
        '
        'label7
        '
        Me.label7.AutoSize = True
        Me.label7.Location = New System.Drawing.Point(5, 73)
        Me.label7.Name = "label7"
        Me.label7.Size = New System.Drawing.Size(42, 15)
        Me.label7.TabIndex = 10
        Me.label7.Text = "Count:"
        '
        'txtInt1Increment
        '
        Me.txtInt1Increment.Location = New System.Drawing.Point(80, 44)
        Me.txtInt1Increment.Name = "txtInt1Increment"
        Me.txtInt1Increment.Size = New System.Drawing.Size(60, 21)
        Me.txtInt1Increment.TabIndex = 9
        '
        'label8
        '
        Me.label8.AutoSize = True
        Me.label8.Location = New System.Drawing.Point(4, 44)
        Me.label8.Name = "label8"
        Me.label8.Size = New System.Drawing.Size(65, 15)
        Me.label8.TabIndex = 8
        Me.label8.Text = "Increment:"
        '
        'txtInt1FirstValue
        '
        Me.txtInt1FirstValue.Location = New System.Drawing.Point(80, 15)
        Me.txtInt1FirstValue.Name = "txtInt1FirstValue"
        Me.txtInt1FirstValue.Size = New System.Drawing.Size(60, 21)
        Me.txtInt1FirstValue.TabIndex = 7
        '
        'label9
        '
        Me.label9.AutoSize = True
        Me.label9.Location = New System.Drawing.Point(3, 18)
        Me.label9.Name = "label9"
        Me.label9.Size = New System.Drawing.Size(64, 15)
        Me.label9.TabIndex = 6
        Me.label9.Text = "FirstValue:"
        '
        'groupBox1
        '
        Me.groupBox1.Controls.Add(Me.groupBox5)
        Me.groupBox1.Controls.Add(Me.groupBox4)
        Me.groupBox1.Location = New System.Drawing.Point(13, 44)
        Me.groupBox1.Name = "groupBox1"
        Me.groupBox1.Size = New System.Drawing.Size(183, 222)
        Me.groupBox1.TabIndex = 8
        Me.groupBox1.TabStop = False
        '
        'groupBox5
        '
        Me.groupBox5.Controls.Add(Me.txtTab2Data2)
        Me.groupBox5.Controls.Add(Me.label4)
        Me.groupBox5.Controls.Add(Me.txtTab2Data1)
        Me.groupBox5.Controls.Add(Me.label5)
        Me.groupBox5.Controls.Add(Me.txtTab2Data0)
        Me.groupBox5.Controls.Add(Me.label6)
        Me.groupBox5.Location = New System.Drawing.Point(8, 114)
        Me.groupBox5.Name = "groupBox5"
        Me.groupBox5.Size = New System.Drawing.Size(167, 101)
        Me.groupBox5.TabIndex = 1
        Me.groupBox5.TabStop = False
        Me.groupBox5.Text = "Table 2"
        '
        'txtTab2Data2
        '
        Me.txtTab2Data2.Location = New System.Drawing.Point(101, 72)
        Me.txtTab2Data2.Name = "txtTab2Data2"
        Me.txtTab2Data2.Size = New System.Drawing.Size(60, 21)
        Me.txtTab2Data2.TabIndex = 5
        '
        'label4
        '
        Me.label4.AutoSize = True
        Me.label4.Location = New System.Drawing.Point(6, 72)
        Me.label4.Name = "label4"
        Me.label4.Size = New System.Drawing.Size(94, 15)
        Me.label4.TabIndex = 4
        Me.label4.Text = "CompareData2:"
        '
        'txtTab2Data1
        '
        Me.txtTab2Data1.Location = New System.Drawing.Point(101, 44)
        Me.txtTab2Data1.Name = "txtTab2Data1"
        Me.txtTab2Data1.Size = New System.Drawing.Size(60, 21)
        Me.txtTab2Data1.TabIndex = 3
        '
        'label5
        '
        Me.label5.AutoSize = True
        Me.label5.Location = New System.Drawing.Point(6, 44)
        Me.label5.Name = "label5"
        Me.label5.Size = New System.Drawing.Size(94, 15)
        Me.label5.TabIndex = 2
        Me.label5.Text = "CompareData1:"
        '
        'txtTab2Data0
        '
        Me.txtTab2Data0.Location = New System.Drawing.Point(101, 17)
        Me.txtTab2Data0.Name = "txtTab2Data0"
        Me.txtTab2Data0.Size = New System.Drawing.Size(60, 21)
        Me.txtTab2Data0.TabIndex = 1
        '
        'label6
        '
        Me.label6.AutoSize = True
        Me.label6.Location = New System.Drawing.Point(6, 17)
        Me.label6.Name = "label6"
        Me.label6.Size = New System.Drawing.Size(94, 15)
        Me.label6.TabIndex = 0
        Me.label6.Text = "CompareData0:"
        '
        'groupBox4
        '
        Me.groupBox4.Controls.Add(Me.txtTab1Data2)
        Me.groupBox4.Controls.Add(Me.label3)
        Me.groupBox4.Controls.Add(Me.txtTab1Data1)
        Me.groupBox4.Controls.Add(Me.label2)
        Me.groupBox4.Controls.Add(Me.txtTab1Data0)
        Me.groupBox4.Controls.Add(Me.label1)
        Me.groupBox4.Location = New System.Drawing.Point(10, 13)
        Me.groupBox4.Name = "groupBox4"
        Me.groupBox4.Size = New System.Drawing.Size(167, 101)
        Me.groupBox4.TabIndex = 0
        Me.groupBox4.TabStop = False
        Me.groupBox4.Text = "Table 1"
        '
        'txtTab1Data2
        '
        Me.txtTab1Data2.Location = New System.Drawing.Point(101, 72)
        Me.txtTab1Data2.Name = "txtTab1Data2"
        Me.txtTab1Data2.Size = New System.Drawing.Size(60, 21)
        Me.txtTab1Data2.TabIndex = 5
        '
        'label3
        '
        Me.label3.AutoSize = True
        Me.label3.Location = New System.Drawing.Point(6, 72)
        Me.label3.Name = "label3"
        Me.label3.Size = New System.Drawing.Size(94, 15)
        Me.label3.TabIndex = 4
        Me.label3.Text = "CompareData2:"
        '
        'txtTab1Data1
        '
        Me.txtTab1Data1.Location = New System.Drawing.Point(101, 44)
        Me.txtTab1Data1.Name = "txtTab1Data1"
        Me.txtTab1Data1.Size = New System.Drawing.Size(60, 21)
        Me.txtTab1Data1.TabIndex = 3
        '
        'label2
        '
        Me.label2.AutoSize = True
        Me.label2.Location = New System.Drawing.Point(6, 44)
        Me.label2.Name = "label2"
        Me.label2.Size = New System.Drawing.Size(94, 15)
        Me.label2.TabIndex = 2
        Me.label2.Text = "CompareData1:"
        '
        'txtTab1Data0
        '
        Me.txtTab1Data0.Location = New System.Drawing.Point(101, 17)
        Me.txtTab1Data0.Name = "txtTab1Data0"
        Me.txtTab1Data0.Size = New System.Drawing.Size(60, 21)
        Me.txtTab1Data0.TabIndex = 1
        '
        'label1
        '
        Me.label1.AutoSize = True
        Me.label1.Location = New System.Drawing.Point(6, 17)
        Me.label1.Name = "label1"
        Me.label1.Size = New System.Drawing.Size(94, 15)
        Me.label1.TabIndex = 0
        Me.label1.Text = "CompareData0:"
        '
        'Timer1
        '
        Me.Timer1.Interval = 40
        '
        'UdCounterCtrl1
        '
        Me.UdCounterCtrl1._StateStream = CType(resources.GetObject("UdCounterCtrl1._StateStream"), Automation.BDaq.DeviceStateStreamer)
        '
        'radInterval
        '
        Me.radInterval.AutoSize = True
        Me.radInterval.Location = New System.Drawing.Point(214, 31)
        Me.radInterval.Name = "radInterval"
        Me.radInterval.Size = New System.Drawing.Size(118, 19)
        Me.radInterval.TabIndex = 16
        Me.radInterval.TabStop = True
        Me.radInterval.Text = "Compare interval"
        Me.radInterval.UseVisualStyleBackColor = True
        '
        'ContinueCompareForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackgroundImage = CType(resources.GetObject("$this.BackgroundImage"), System.Drawing.Image)
        Me.ClientSize = New System.Drawing.Size(525, 314)
        Me.Controls.Add(Me.radInterval)
        Me.Controls.Add(Me.radTable)
        Me.Controls.Add(Me.label14)
        Me.Controls.Add(Me.txtEndCount)
        Me.Controls.Add(Me.txtPMCount)
        Me.Controls.Add(Me.label13)
        Me.Controls.Add(Me.groupBox3)
        Me.Controls.Add(Me.groupBox2)
        Me.Controls.Add(Me.groupBox1)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "ContinueCompareForm"
        Me.Text = "ContinueCompare"
        Me.groupBox3.ResumeLayout(False)
        Me.groupBox3.PerformLayout()
        Me.groupBox2.ResumeLayout(False)
        Me.groupBox7.ResumeLayout(False)
        Me.groupBox7.PerformLayout()
        Me.groupBox6.ResumeLayout(False)
        Me.groupBox6.PerformLayout()
        Me.groupBox1.ResumeLayout(False)
        Me.groupBox5.ResumeLayout(False)
        Me.groupBox5.PerformLayout()
        Me.groupBox4.ResumeLayout(False)
        Me.groupBox4.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Private WithEvents radTable As System.Windows.Forms.RadioButton
    Private WithEvents label14 As System.Windows.Forms.Label
    Private WithEvents txtEndCount As System.Windows.Forms.TextBox
    Private WithEvents txtPMCount As System.Windows.Forms.TextBox
    Private WithEvents label13 As System.Windows.Forms.Label
    Private WithEvents groupBox3 As System.Windows.Forms.GroupBox
    Private WithEvents btnStop As System.Windows.Forms.Button
    Private WithEvents btnStart As System.Windows.Forms.Button
    Private WithEvents txtCounterValue As System.Windows.Forms.TextBox
    Private WithEvents groupBox2 As System.Windows.Forms.GroupBox
    Private WithEvents groupBox7 As System.Windows.Forms.GroupBox
    Private WithEvents txtInt2Count As System.Windows.Forms.TextBox
    Private WithEvents label10 As System.Windows.Forms.Label
    Private WithEvents txtInt2Increment As System.Windows.Forms.TextBox
    Private WithEvents label11 As System.Windows.Forms.Label
    Private WithEvents txtInt2FirstValue As System.Windows.Forms.TextBox
    Private WithEvents label12 As System.Windows.Forms.Label
    Private WithEvents groupBox6 As System.Windows.Forms.GroupBox
    Private WithEvents txtInt1Count As System.Windows.Forms.TextBox
    Private WithEvents label7 As System.Windows.Forms.Label
    Private WithEvents txtInt1Increment As System.Windows.Forms.TextBox
    Private WithEvents label8 As System.Windows.Forms.Label
    Private WithEvents txtInt1FirstValue As System.Windows.Forms.TextBox
    Private WithEvents label9 As System.Windows.Forms.Label
    Private WithEvents groupBox1 As System.Windows.Forms.GroupBox
    Private WithEvents groupBox5 As System.Windows.Forms.GroupBox
    Private WithEvents txtTab2Data2 As System.Windows.Forms.TextBox
    Private WithEvents label4 As System.Windows.Forms.Label
    Private WithEvents txtTab2Data1 As System.Windows.Forms.TextBox
    Private WithEvents label5 As System.Windows.Forms.Label
    Private WithEvents txtTab2Data0 As System.Windows.Forms.TextBox
    Private WithEvents label6 As System.Windows.Forms.Label
    Private WithEvents groupBox4 As System.Windows.Forms.GroupBox
    Private WithEvents txtTab1Data2 As System.Windows.Forms.TextBox
    Private WithEvents label3 As System.Windows.Forms.Label
    Private WithEvents txtTab1Data1 As System.Windows.Forms.TextBox
    Private WithEvents label2 As System.Windows.Forms.Label
    Private WithEvents txtTab1Data0 As System.Windows.Forms.TextBox
    Private WithEvents label1 As System.Windows.Forms.Label
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents UdCounterCtrl1 As Automation.BDaq.UdCounterCtrl
    Friend WithEvents radInterval As System.Windows.Forms.RadioButton

End Class
