<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class InstantAiForm
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(InstantAiForm))
        Me.InstantAiCtrl1 = New Automation.BDaq.InstantAiCtrl(Me.components)
        Me.timer_getData = New System.Windows.Forms.Timer(Me.components)
        Me.label4 = New System.Windows.Forms.Label
        Me.label3 = New System.Windows.Forms.Label
        Me.label2 = New System.Windows.Forms.Label
        Me.label1 = New System.Windows.Forms.Label
        Me.textBox = New System.Windows.Forms.TextBox
        Me.pictureBox = New System.Windows.Forms.PictureBox
        Me.label_YCoordinateMiddle = New System.Windows.Forms.Label
        Me.label_YCoordinateMax = New System.Windows.Forms.Label
        Me.button_stop = New System.Windows.Forms.Button
        Me.button_pause = New System.Windows.Forms.Button
        Me.button_start = New System.Windows.Forms.Button
        Me.trackBar = New System.Windows.Forms.TrackBar
        Me.label_XCoordinateMax = New System.Windows.Forms.Label
        Me.label_YCoordinateMin = New System.Windows.Forms.Label
        Me.label_XCoordinateMin = New System.Windows.Forms.Label
        Me.ListView = New MyListView.DoubleBufferListView
        Me.comboBox_chanStart = New System.Windows.Forms.ComboBox
        Me.comboBox_chanCount = New System.Windows.Forms.ComboBox
        Me.Label5 = New System.Windows.Forms.Label
        Me.Label6 = New System.Windows.Forms.Label
        CType(Me.pictureBox, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.trackBar, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'InstantAiCtrl1
        '
        Me.InstantAiCtrl1._StateStream = CType(resources.GetObject("InstantAiCtrl1._StateStream"), Automation.BDaq.DeviceStateStreamer)
        '
        'timer_getData
        '
        '
        'label4
        '
        Me.label4.AutoSize = True
        Me.label4.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label4.Location = New System.Drawing.Point(19, 438)
        Me.label4.Name = "label4"
        Me.label4.Size = New System.Drawing.Size(14, 15)
        Me.label4.TabIndex = 39
        Me.label4.Text = "8"
        '
        'label3
        '
        Me.label3.AutoSize = True
        Me.label3.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label3.Location = New System.Drawing.Point(19, 402)
        Me.label3.Name = "label3"
        Me.label3.Size = New System.Drawing.Size(14, 15)
        Me.label3.TabIndex = 38
        Me.label3.Text = "0"
        '
        'label2
        '
        Me.label2.AllowDrop = True
        Me.label2.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label2.Font = New System.Drawing.Font("Microsoft Sans Serif", 7.5!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label2.Location = New System.Drawing.Point(616, 402)
        Me.label2.Name = "label2"
        Me.label2.Size = New System.Drawing.Size(45, 27)
        Me.label2.TabIndex = 37
        Me.label2.Text = "Sample  interval:"
        '
        'label1
        '
        Me.label1.AutoSize = True
        Me.label1.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label1.Location = New System.Drawing.Point(710, 410)
        Me.label1.Name = "label1"
        Me.label1.Size = New System.Drawing.Size(24, 15)
        Me.label1.TabIndex = 36
        Me.label1.Text = "ms"
        Me.label1.UseWaitCursor = True
        '
        'textBox
        '
        Me.textBox.Location = New System.Drawing.Point(663, 406)
        Me.textBox.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.textBox.Name = "textBox"
        Me.textBox.Size = New System.Drawing.Size(47, 21)
        Me.textBox.TabIndex = 35
        Me.textBox.Text = "200"
        Me.textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'pictureBox
        '
        Me.pictureBox.BackColor = System.Drawing.SystemColors.ControlText
        Me.pictureBox.Location = New System.Drawing.Point(50, 39)
        Me.pictureBox.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.pictureBox.Name = "pictureBox"
        Me.pictureBox.Size = New System.Drawing.Size(660, 340)
        Me.pictureBox.TabIndex = 33
        Me.pictureBox.TabStop = False
        '
        'label_YCoordinateMiddle
        '
        Me.label_YCoordinateMiddle.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label_YCoordinateMiddle.Location = New System.Drawing.Point(0, 202)
        Me.label_YCoordinateMiddle.Name = "label_YCoordinateMiddle"
        Me.label_YCoordinateMiddle.Size = New System.Drawing.Size(52, 15)
        Me.label_YCoordinateMiddle.TabIndex = 34
        Me.label_YCoordinateMiddle.Text = "0V"
        Me.label_YCoordinateMiddle.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'label_YCoordinateMax
        '
        Me.label_YCoordinateMax.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label_YCoordinateMax.Location = New System.Drawing.Point(-2, 35)
        Me.label_YCoordinateMax.Name = "label_YCoordinateMax"
        Me.label_YCoordinateMax.Size = New System.Drawing.Size(52, 15)
        Me.label_YCoordinateMax.TabIndex = 28
        Me.label_YCoordinateMax.Text = "5V"
        Me.label_YCoordinateMax.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'button_stop
        '
        Me.button_stop.Location = New System.Drawing.Point(628, 466)
        Me.button_stop.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.button_stop.Name = "button_stop"
        Me.button_stop.Size = New System.Drawing.Size(69, 29)
        Me.button_stop.TabIndex = 27
        Me.button_stop.Text = "Stop"
        Me.button_stop.UseVisualStyleBackColor = True
        '
        'button_pause
        '
        Me.button_pause.Location = New System.Drawing.Point(549, 466)
        Me.button_pause.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.button_pause.Name = "button_pause"
        Me.button_pause.Size = New System.Drawing.Size(69, 29)
        Me.button_pause.TabIndex = 26
        Me.button_pause.Text = "Pause"
        Me.button_pause.UseVisualStyleBackColor = True
        '
        'button_start
        '
        Me.button_start.Location = New System.Drawing.Point(471, 466)
        Me.button_start.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.button_start.Name = "button_start"
        Me.button_start.Size = New System.Drawing.Size(69, 29)
        Me.button_start.TabIndex = 25
        Me.button_start.Text = "Start"
        Me.button_start.UseVisualStyleBackColor = True
        '
        'trackBar
        '
        Me.trackBar.AutoSize = False
        Me.trackBar.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.trackBar.Location = New System.Drawing.Point(620, 430)
        Me.trackBar.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.trackBar.Maximum = 1000
        Me.trackBar.Minimum = 10
        Me.trackBar.Name = "trackBar"
        Me.trackBar.Size = New System.Drawing.Size(110, 23)
        Me.trackBar.SmallChange = 10
        Me.trackBar.TabIndex = 31
        Me.trackBar.Tag = "ghgfh"
        Me.trackBar.TickFrequency = 100
        Me.trackBar.Value = 200
        '
        'label_XCoordinateMax
        '
        Me.label_XCoordinateMax.AutoSize = True
        Me.label_XCoordinateMax.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label_XCoordinateMax.Font = New System.Drawing.Font("Microsoft Sans Serif", 7.5!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label_XCoordinateMax.Location = New System.Drawing.Point(671, 384)
        Me.label_XCoordinateMax.Name = "label_XCoordinateMax"
        Me.label_XCoordinateMax.Size = New System.Drawing.Size(40, 13)
        Me.label_XCoordinateMax.TabIndex = 30
        Me.label_XCoordinateMax.Text = "10 Sec"
        '
        'label_YCoordinateMin
        '
        Me.label_YCoordinateMin.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label_YCoordinateMin.Location = New System.Drawing.Point(0, 364)
        Me.label_YCoordinateMin.Name = "label_YCoordinateMin"
        Me.label_YCoordinateMin.Size = New System.Drawing.Size(52, 15)
        Me.label_YCoordinateMin.TabIndex = 29
        Me.label_YCoordinateMin.Text = "0V"
        Me.label_YCoordinateMin.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'label_XCoordinateMin
        '
        Me.label_XCoordinateMin.AutoSize = True
        Me.label_XCoordinateMin.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label_XCoordinateMin.Font = New System.Drawing.Font("Microsoft Sans Serif", 7.5!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label_XCoordinateMin.Location = New System.Drawing.Point(49, 382)
        Me.label_XCoordinateMin.Name = "label_XCoordinateMin"
        Me.label_XCoordinateMin.Size = New System.Drawing.Size(34, 13)
        Me.label_XCoordinateMin.TabIndex = 32
        Me.label_XCoordinateMin.Text = "0 Sec"
        '
        'ListView
        '
        Me.ListView.Location = New System.Drawing.Point(37, 405)
        Me.ListView.Name = "ListView"
        Me.ListView.Size = New System.Drawing.Size(578, 48)
        Me.ListView.TabIndex = 40
        Me.ListView.UseCompatibleStateImageBehavior = False
        '
        'comboBox_chanStart
        '
        Me.comboBox_chanStart.AccessibleRole = System.Windows.Forms.AccessibleRole.None
        Me.comboBox_chanStart.FormattingEnabled = True
        Me.comboBox_chanStart.Location = New System.Drawing.Point(119, 471)
        Me.comboBox_chanStart.Name = "comboBox_chanStart"
        Me.comboBox_chanStart.Size = New System.Drawing.Size(81, 23)
        Me.comboBox_chanStart.TabIndex = 41
        '
        'comboBox_chanCount
        '
        Me.comboBox_chanCount.FormattingEnabled = True
        Me.comboBox_chanCount.Location = New System.Drawing.Point(289, 472)
        Me.comboBox_chanCount.Name = "comboBox_chanCount"
        Me.comboBox_chanCount.Size = New System.Drawing.Size(81, 23)
        Me.comboBox_chanCount.TabIndex = 42
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(53, 474)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(64, 15)
        Me.Label5.TabIndex = 43
        Me.Label5.Text = "ChanStart:"
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Location = New System.Drawing.Point(215, 476)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(71, 15)
        Me.Label6.TabIndex = 44
        Me.Label6.Text = "ChanCount:"
        '
        'InstantAiForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackgroundImage = CType(resources.GetObject("$this.BackgroundImage"), System.Drawing.Image)
        Me.ClientSize = New System.Drawing.Size(756, 506)
        Me.Controls.Add(Me.Label6)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.comboBox_chanCount)
        Me.Controls.Add(Me.comboBox_chanStart)
        Me.Controls.Add(Me.ListView)
        Me.Controls.Add(Me.label4)
        Me.Controls.Add(Me.label3)
        Me.Controls.Add(Me.label2)
        Me.Controls.Add(Me.label1)
        Me.Controls.Add(Me.textBox)
        Me.Controls.Add(Me.pictureBox)
        Me.Controls.Add(Me.label_YCoordinateMiddle)
        Me.Controls.Add(Me.label_YCoordinateMax)
        Me.Controls.Add(Me.button_stop)
        Me.Controls.Add(Me.button_pause)
        Me.Controls.Add(Me.button_start)
        Me.Controls.Add(Me.trackBar)
        Me.Controls.Add(Me.label_XCoordinateMax)
        Me.Controls.Add(Me.label_YCoordinateMin)
        Me.Controls.Add(Me.label_XCoordinateMin)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "InstantAiForm"
        Me.Text = "Instant AI"
        CType(Me.pictureBox, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.trackBar, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
   Private WithEvents timer_getData As System.Windows.Forms.Timer
   Private WithEvents label4 As System.Windows.Forms.Label
   Private WithEvents label3 As System.Windows.Forms.Label
   Private WithEvents label2 As System.Windows.Forms.Label
   Private WithEvents label1 As System.Windows.Forms.Label
   Private WithEvents textBox As System.Windows.Forms.TextBox
   Private WithEvents pictureBox As System.Windows.Forms.PictureBox
   Private WithEvents label_YCoordinateMiddle As System.Windows.Forms.Label
   Private WithEvents label_YCoordinateMax As System.Windows.Forms.Label
   Private WithEvents button_stop As System.Windows.Forms.Button
   Private WithEvents button_pause As System.Windows.Forms.Button
   Private WithEvents button_start As System.Windows.Forms.Button
   Private WithEvents trackBar As System.Windows.Forms.TrackBar
   Public WithEvents label_XCoordinateMax As System.Windows.Forms.Label
   Private WithEvents label_YCoordinateMin As System.Windows.Forms.Label
   Private WithEvents label_XCoordinateMin As System.Windows.Forms.Label
   Friend WithEvents ListView As MyListView.DoubleBufferListView
   Friend WithEvents InstantAiCtrl1 As Automation.BDaq.InstantAiCtrl
   Friend WithEvents comboBox_chanStart As System.Windows.Forms.ComboBox
   Friend WithEvents comboBox_chanCount As System.Windows.Forms.ComboBox
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents Label6 As System.Windows.Forms.Label

End Class
