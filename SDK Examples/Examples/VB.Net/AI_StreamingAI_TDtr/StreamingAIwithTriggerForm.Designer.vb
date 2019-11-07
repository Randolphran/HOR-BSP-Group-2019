<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class StreamingAIwithTriggerForm
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
		Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(StreamingAIwithTriggerForm))
		Me.label_XCoordinateMin = New System.Windows.Forms.Label
		Me.label_XCoordinateMax = New System.Windows.Forms.Label
		Me.label_YCoordinateMin = New System.Windows.Forms.Label
		Me.label_YCoordinateMax = New System.Windows.Forms.Label
		Me.label_YCoordinateMiddle = New System.Windows.Forms.Label
		Me.label1 = New System.Windows.Forms.Label
		Me.listView = New System.Windows.Forms.ListView
		Me.button_stop = New System.Windows.Forms.Button
		Me.button_pause = New System.Windows.Forms.Button
		Me.button_start = New System.Windows.Forms.Button
		Me.trackBar_div = New System.Windows.Forms.TrackBar
		Me.pictureBox = New System.Windows.Forms.PictureBox
		Me.Label2 = New System.Windows.Forms.Label
		Me.WaveformAiCtrl1 = New Automation.BDaq.WaveformAiCtrl(Me.components)
		CType(Me.trackBar_div, System.ComponentModel.ISupportInitialize).BeginInit()
		CType(Me.pictureBox, System.ComponentModel.ISupportInitialize).BeginInit()
		Me.SuspendLayout()
		'
		'label_XCoordinateMin
		'
		Me.label_XCoordinateMin.AutoSize = True
		Me.label_XCoordinateMin.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
		Me.label_XCoordinateMin.Location = New System.Drawing.Point(54, 380)
		Me.label_XCoordinateMin.Name = "label_XCoordinateMin"
		Me.label_XCoordinateMin.Size = New System.Drawing.Size(38, 15)
		Me.label_XCoordinateMin.TabIndex = 43
		Me.label_XCoordinateMin.Text = "0 Sec"
		'
		'label_XCoordinateMax
		'
		Me.label_XCoordinateMax.AutoSize = True
		Me.label_XCoordinateMax.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
		Me.label_XCoordinateMax.Location = New System.Drawing.Point(669, 380)
		Me.label_XCoordinateMax.Name = "label_XCoordinateMax"
		Me.label_XCoordinateMax.Size = New System.Drawing.Size(45, 15)
		Me.label_XCoordinateMax.TabIndex = 42
		Me.label_XCoordinateMax.Text = "12 Sec"
		'
		'label_YCoordinateMin
		'
		Me.label_YCoordinateMin.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
		Me.label_YCoordinateMin.Location = New System.Drawing.Point(1, 360)
		Me.label_YCoordinateMin.Name = "label_YCoordinateMin"
		Me.label_YCoordinateMin.Size = New System.Drawing.Size(52, 15)
		Me.label_YCoordinateMin.TabIndex = 40
		Me.label_YCoordinateMin.Text = "0V"
		Me.label_YCoordinateMin.TextAlign = System.Drawing.ContentAlignment.TopRight
		'
		'label_YCoordinateMax
		'
		Me.label_YCoordinateMax.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
		Me.label_YCoordinateMax.Location = New System.Drawing.Point(0, 38)
		Me.label_YCoordinateMax.Name = "label_YCoordinateMax"
		Me.label_YCoordinateMax.Size = New System.Drawing.Size(52, 15)
		Me.label_YCoordinateMax.TabIndex = 39
		Me.label_YCoordinateMax.Text = "5V"
		Me.label_YCoordinateMax.TextAlign = System.Drawing.ContentAlignment.TopRight
		'
		'label_YCoordinateMiddle
		'
		Me.label_YCoordinateMiddle.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
		Me.label_YCoordinateMiddle.Location = New System.Drawing.Point(0, 183)
		Me.label_YCoordinateMiddle.Name = "label_YCoordinateMiddle"
		Me.label_YCoordinateMiddle.Size = New System.Drawing.Size(52, 15)
		Me.label_YCoordinateMiddle.TabIndex = 41
		Me.label_YCoordinateMiddle.Text = "0V"
		Me.label_YCoordinateMiddle.TextAlign = System.Drawing.ContentAlignment.TopRight
		'
		'label1
		'
		Me.label1.AutoSize = True
		Me.label1.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
		Me.label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
		Me.label1.Location = New System.Drawing.Point(52, 403)
		Me.label1.Name = "label1"
		Me.label1.Size = New System.Drawing.Size(105, 15)
		Me.label1.TabIndex = 38
		Me.label1.Text = "Color of channels:"
		'
		'listView
		'
		Me.listView.Location = New System.Drawing.Point(161, 395)
		Me.listView.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
		Me.listView.Name = "listView"
		Me.listView.Size = New System.Drawing.Size(351, 37)
		Me.listView.TabIndex = 37
		Me.listView.UseCompatibleStateImageBehavior = False
		'
		'button_stop
		'
		Me.button_stop.Location = New System.Drawing.Point(641, 448)
		Me.button_stop.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
		Me.button_stop.Name = "button_stop"
		Me.button_stop.Size = New System.Drawing.Size(71, 27)
		Me.button_stop.TabIndex = 36
		Me.button_stop.Text = "Stop"
		Me.button_stop.UseVisualStyleBackColor = True
		'
		'button_pause
		'
		Me.button_pause.Location = New System.Drawing.Point(564, 448)
		Me.button_pause.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
		Me.button_pause.Name = "button_pause"
		Me.button_pause.Size = New System.Drawing.Size(71, 27)
		Me.button_pause.TabIndex = 35
		Me.button_pause.Text = "Pause"
		Me.button_pause.UseVisualStyleBackColor = True
		'
		'button_start
		'
		Me.button_start.Location = New System.Drawing.Point(483, 447)
		Me.button_start.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
		Me.button_start.Name = "button_start"
		Me.button_start.Size = New System.Drawing.Size(71, 27)
		Me.button_start.TabIndex = 34
		Me.button_start.Text = "Start"
		Me.button_start.UseVisualStyleBackColor = True
		'
		'trackBar_div
		'
		Me.trackBar_div.AutoSize = False
		Me.trackBar_div.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
		Me.trackBar_div.Location = New System.Drawing.Point(559, 406)
		Me.trackBar_div.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
		Me.trackBar_div.Maximum = 1000
		Me.trackBar_div.Minimum = 10
		Me.trackBar_div.Name = "trackBar_div"
		Me.trackBar_div.Size = New System.Drawing.Size(151, 23)
		Me.trackBar_div.TabIndex = 33
		Me.trackBar_div.TickFrequency = 100
		Me.trackBar_div.Value = 100
		'
		'pictureBox
		'
		Me.pictureBox.BackColor = System.Drawing.SystemColors.ControlText
		Me.pictureBox.Location = New System.Drawing.Point(55, 38)
		Me.pictureBox.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
		Me.pictureBox.Name = "pictureBox"
		Me.pictureBox.Size = New System.Drawing.Size(660, 340)
		Me.pictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
		Me.pictureBox.TabIndex = 32
		Me.pictureBox.TabStop = False
		'
		'Label2
		'
		Me.Label2.AutoSize = True
		Me.Label2.Location = New System.Drawing.Point(529, 406)
		Me.Label2.Name = "Label2"
		Me.Label2.Size = New System.Drawing.Size(27, 15)
		Me.Label2.TabIndex = 44
		Me.Label2.Text = "Div:"
		'
		'WaveformAiCtrl1
		'
		Me.WaveformAiCtrl1._StateStream = CType(resources.GetObject("WaveformAiCtrl1._StateStream"), Automation.BDaq.DeviceStateStreamer)
		'
		'StreamingAIwithTriggerForm
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.BackgroundImage = CType(resources.GetObject("$this.BackgroundImage"), System.Drawing.Image)
		Me.ClientSize = New System.Drawing.Size(761, 486)
		Me.Controls.Add(Me.Label2)
		Me.Controls.Add(Me.label_XCoordinateMin)
		Me.Controls.Add(Me.label_XCoordinateMax)
		Me.Controls.Add(Me.label_YCoordinateMin)
		Me.Controls.Add(Me.label_YCoordinateMax)
		Me.Controls.Add(Me.label_YCoordinateMiddle)
		Me.Controls.Add(Me.label1)
		Me.Controls.Add(Me.listView)
		Me.Controls.Add(Me.button_stop)
		Me.Controls.Add(Me.button_pause)
		Me.Controls.Add(Me.button_start)
		Me.Controls.Add(Me.trackBar_div)
		Me.Controls.Add(Me.pictureBox)
		Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
		Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
		Me.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
		Me.MaximizeBox = False
		Me.MinimizeBox = False
		Me.Name = "StreamingAIwithTriggerForm"
		Me.Text = "Streaming AI with Trigger Delay to Start"
		CType(Me.trackBar_div, System.ComponentModel.ISupportInitialize).EndInit()
		CType(Me.pictureBox, System.ComponentModel.ISupportInitialize).EndInit()
		Me.ResumeLayout(False)
		Me.PerformLayout()

	End Sub
    Private WithEvents label_XCoordinateMin As System.Windows.Forms.Label
    Private WithEvents label_XCoordinateMax As System.Windows.Forms.Label
    Private WithEvents label_YCoordinateMin As System.Windows.Forms.Label
    Private WithEvents label_YCoordinateMax As System.Windows.Forms.Label
    Private WithEvents label_YCoordinateMiddle As System.Windows.Forms.Label
    Private WithEvents label1 As System.Windows.Forms.Label
    Private WithEvents listView As System.Windows.Forms.ListView
    Private WithEvents button_stop As System.Windows.Forms.Button
    Private WithEvents button_pause As System.Windows.Forms.Button
    Private WithEvents button_start As System.Windows.Forms.Button
    Private WithEvents trackBar_div As System.Windows.Forms.TrackBar
    Private WithEvents pictureBox As System.Windows.Forms.PictureBox
	Friend WithEvents Label2 As System.Windows.Forms.Label
	Friend WithEvents WaveformAiCtrl1 As Automation.BDaq.WaveformAiCtrl

End Class
