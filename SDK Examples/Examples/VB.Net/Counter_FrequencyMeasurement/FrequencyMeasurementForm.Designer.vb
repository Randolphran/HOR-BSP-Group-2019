<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class FrequencyMeasurementForm
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(FrequencyMeasurementForm))
        Me.TimeInterval = New System.Windows.Forms.Label
        Me.GraphPicture = New System.Windows.Forms.PictureBox
        Me.Start = New System.Windows.Forms.Button
        Me.smaller = New System.Windows.Forms.PictureBox
        Me.larger = New System.Windows.Forms.PictureBox
        Me.Pause = New System.Windows.Forms.Button
        Me.trackBar = New System.Windows.Forms.TrackBar
        Me.label_XCoordinateMax = New System.Windows.Forms.Label
        Me.label_XCoordinateMin = New System.Windows.Forms.Label
        Me.label_YCoordinateMin = New System.Windows.Forms.Label
        Me.label_YCoordinateMiddle = New System.Windows.Forms.Label
        Me.label_YCoordinateMax = New System.Windows.Forms.Label
        Me.pictureBox1 = New System.Windows.Forms.PictureBox
        Me.Stop_button = New System.Windows.Forms.Button
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.fm1_Label = New System.Windows.Forms.Label
        Me.fm2_Label = New System.Windows.Forms.Label
        Me.label1 = New System.Windows.Forms.Label
        Me.FreqMeterCtrl1 = New Automation.BDaq.FreqMeterCtrl(Me.components)
        Me.FreqMeterCtrl2 = New Automation.BDaq.FreqMeterCtrl(Me.components)
        CType(Me.GraphPicture, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.smaller, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.larger, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.trackBar, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.pictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'TimeInterval
        '
        Me.TimeInterval.AutoSize = True
        Me.TimeInterval.Location = New System.Drawing.Point(388, 439)
        Me.TimeInterval.Name = "TimeInterval"
        Me.TimeInterval.Size = New System.Drawing.Size(41, 15)
        Me.TimeInterval.TabIndex = 30
        Me.TimeInterval.Text = "50 ms"
        '
        'GraphPicture
        '
        Me.GraphPicture.BackColor = System.Drawing.SystemColors.ControlText
        Me.GraphPicture.Location = New System.Drawing.Point(68, 29)
        Me.GraphPicture.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.GraphPicture.Name = "GraphPicture"
        Me.GraphPicture.Size = New System.Drawing.Size(505, 388)
        Me.GraphPicture.TabIndex = 17
        Me.GraphPicture.TabStop = False
        '
        'Start
        '
        Me.Start.Location = New System.Drawing.Point(585, 80)
        Me.Start.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.Start.Name = "Start"
        Me.Start.Size = New System.Drawing.Size(75, 28)
        Me.Start.TabIndex = 28
        Me.Start.Text = "Start"
        Me.Start.UseVisualStyleBackColor = True
        '
        'smaller
        '
        Me.smaller.Image = CType(resources.GetObject("smaller.Image"), System.Drawing.Image)
        Me.smaller.Location = New System.Drawing.Point(27, 330)
        Me.smaller.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.smaller.Name = "smaller"
        Me.smaller.Size = New System.Drawing.Size(22, 24)
        Me.smaller.TabIndex = 27
        Me.smaller.TabStop = False
        '
        'larger
        '
        Me.larger.Image = CType(resources.GetObject("larger.Image"), System.Drawing.Image)
        Me.larger.Location = New System.Drawing.Point(27, 296)
        Me.larger.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.larger.Name = "larger"
        Me.larger.Size = New System.Drawing.Size(22, 24)
        Me.larger.TabIndex = 26
        Me.larger.TabStop = False
        '
        'Pause
        '
        Me.Pause.Location = New System.Drawing.Point(585, 142)
        Me.Pause.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.Pause.Name = "Pause"
        Me.Pause.Size = New System.Drawing.Size(75, 28)
        Me.Pause.TabIndex = 25
        Me.Pause.Text = "Pause"
        Me.Pause.UseVisualStyleBackColor = True
        '
        'trackBar
        '
        Me.trackBar.Location = New System.Drawing.Point(263, 436)
        Me.trackBar.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.trackBar.Maximum = 1000
        Me.trackBar.Minimum = 10
        Me.trackBar.Name = "trackBar"
        Me.trackBar.Size = New System.Drawing.Size(121, 45)
        Me.trackBar.TabIndex = 24
        Me.trackBar.TickStyle = System.Windows.Forms.TickStyle.None
        Me.trackBar.Value = 50
        '
        'label_XCoordinateMax
        '
        Me.label_XCoordinateMax.AutoSize = True
        Me.label_XCoordinateMax.Location = New System.Drawing.Point(551, 428)
        Me.label_XCoordinateMax.Name = "label_XCoordinateMax"
        Me.label_XCoordinateMax.Size = New System.Drawing.Size(43, 15)
        Me.label_XCoordinateMax.TabIndex = 23
        Me.label_XCoordinateMax.Text = "10 sec"
        '
        'label_XCoordinateMin
        '
        Me.label_XCoordinateMin.AutoSize = True
        Me.label_XCoordinateMin.Location = New System.Drawing.Point(61, 428)
        Me.label_XCoordinateMin.Name = "label_XCoordinateMin"
        Me.label_XCoordinateMin.Size = New System.Drawing.Size(36, 15)
        Me.label_XCoordinateMin.TabIndex = 21
        Me.label_XCoordinateMin.Text = "0 sec"
        '
        'label_YCoordinateMin
        '
        Me.label_YCoordinateMin.AutoSize = True
        Me.label_YCoordinateMin.Location = New System.Drawing.Point(23, 403)
        Me.label_YCoordinateMin.Name = "label_YCoordinateMin"
        Me.label_YCoordinateMin.Size = New System.Drawing.Size(29, 15)
        Me.label_YCoordinateMin.TabIndex = 20
        Me.label_YCoordinateMin.Text = "0Hz"
        '
        'label_YCoordinateMiddle
        '
        Me.label_YCoordinateMiddle.AutoSize = True
        Me.label_YCoordinateMiddle.Location = New System.Drawing.Point(13, 210)
        Me.label_YCoordinateMiddle.Name = "label_YCoordinateMiddle"
        Me.label_YCoordinateMiddle.Size = New System.Drawing.Size(44, 15)
        Me.label_YCoordinateMiddle.TabIndex = 19
        Me.label_YCoordinateMiddle.Text = "50KHz"
        '
        'label_YCoordinateMax
        '
        Me.label_YCoordinateMax.AutoSize = True
        Me.label_YCoordinateMax.Location = New System.Drawing.Point(10, 24)
        Me.label_YCoordinateMax.Name = "label_YCoordinateMax"
        Me.label_YCoordinateMax.Size = New System.Drawing.Size(51, 15)
        Me.label_YCoordinateMax.TabIndex = 18
        Me.label_YCoordinateMax.Text = "100KHz"
        '
        'pictureBox1
        '
        Me.pictureBox1.Image = CType(resources.GetObject("pictureBox1.Image"), System.Drawing.Image)
        Me.pictureBox1.InitialImage = CType(resources.GetObject("pictureBox1.InitialImage"), System.Drawing.Image)
        Me.pictureBox1.Location = New System.Drawing.Point(513, -3)
        Me.pictureBox1.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.pictureBox1.Name = "pictureBox1"
        Me.pictureBox1.Size = New System.Drawing.Size(189, 58)
        Me.pictureBox1.TabIndex = 29
        Me.pictureBox1.TabStop = False
        '
        'Stop_button
        '
        Me.Stop_button.Location = New System.Drawing.Point(585, 183)
        Me.Stop_button.Name = "Stop_button"
        Me.Stop_button.Size = New System.Drawing.Size(75, 28)
        Me.Stop_button.TabIndex = 31
        Me.Stop_button.Text = "Stop"
        Me.Stop_button.UseVisualStyleBackColor = True
        '
        'Timer1
        '
        Me.Timer1.Interval = 50
        '
        'fm1_Label
        '
        Me.fm1_Label.BackColor = System.Drawing.Color.DarkOrange
        Me.fm1_Label.Location = New System.Drawing.Point(586, 259)
        Me.fm1_Label.Name = "fm1_Label"
        Me.fm1_Label.Size = New System.Drawing.Size(75, 22)
        Me.fm1_Label.TabIndex = 32
        '
        'fm2_Label
        '
        Me.fm2_Label.BackColor = System.Drawing.Color.DarkViolet
        Me.fm2_Label.Location = New System.Drawing.Point(586, 284)
        Me.fm2_Label.Name = "fm2_Label"
        Me.fm2_Label.Size = New System.Drawing.Size(75, 22)
        Me.fm2_Label.TabIndex = 33
        '
        'label1
        '
        Me.label1.AutoSize = True
        Me.label1.Location = New System.Drawing.Point(162, 439)
        Me.label1.Name = "label1"
        Me.label1.Size = New System.Drawing.Size(95, 15)
        Me.label1.TabIndex = 34
        Me.label1.Text = "Sample interval:"
        '
        'FreqMeterCtrl1
        '
        Me.FreqMeterCtrl1._StateStream = CType(resources.GetObject("FreqMeterCtrl1._StateStream"), Automation.BDaq.DeviceStateStreamer)
        '
        'FreqMeterCtrl2
        '
        Me.FreqMeterCtrl2._StateStream = CType(resources.GetObject("FreqMeterCtrl2._StateStream"), Automation.BDaq.DeviceStateStreamer)
        '
        'FrequencyMeasurementForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(673, 471)
        Me.Controls.Add(Me.label1)
        Me.Controls.Add(Me.fm2_Label)
        Me.Controls.Add(Me.fm1_Label)
        Me.Controls.Add(Me.Stop_button)
        Me.Controls.Add(Me.TimeInterval)
        Me.Controls.Add(Me.GraphPicture)
        Me.Controls.Add(Me.Start)
        Me.Controls.Add(Me.smaller)
        Me.Controls.Add(Me.larger)
        Me.Controls.Add(Me.Pause)
        Me.Controls.Add(Me.trackBar)
        Me.Controls.Add(Me.label_XCoordinateMax)
        Me.Controls.Add(Me.label_XCoordinateMin)
        Me.Controls.Add(Me.label_YCoordinateMin)
        Me.Controls.Add(Me.label_YCoordinateMiddle)
        Me.Controls.Add(Me.label_YCoordinateMax)
        Me.Controls.Add(Me.pictureBox1)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "FrequencyMeasurementForm"
        Me.Text = "Frequency Meter"
        CType(Me.GraphPicture, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.smaller, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.larger, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.trackBar, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.pictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Private WithEvents TimeInterval As System.Windows.Forms.Label
    Private WithEvents GraphPicture As System.Windows.Forms.PictureBox
    Private WithEvents Start As System.Windows.Forms.Button
    Private WithEvents smaller As System.Windows.Forms.PictureBox
    Private WithEvents larger As System.Windows.Forms.PictureBox
    Private WithEvents Pause As System.Windows.Forms.Button
    Private WithEvents trackBar As System.Windows.Forms.TrackBar
    Private WithEvents label_XCoordinateMax As System.Windows.Forms.Label
    Private WithEvents label_XCoordinateMin As System.Windows.Forms.Label
    Private WithEvents label_YCoordinateMin As System.Windows.Forms.Label
    Private WithEvents label_YCoordinateMiddle As System.Windows.Forms.Label
    Private WithEvents label_YCoordinateMax As System.Windows.Forms.Label
    Private WithEvents pictureBox1 As System.Windows.Forms.PictureBox
    Friend WithEvents Stop_button As System.Windows.Forms.Button
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents fm1_Label As System.Windows.Forms.Label
    Friend WithEvents fm2_Label As System.Windows.Forms.Label
    Private WithEvents label1 As System.Windows.Forms.Label
    Friend WithEvents FreqMeterCtrl1 As Automation.BDaq.FreqMeterCtrl
    Friend WithEvents FreqMeterCtrl2 As Automation.BDaq.FreqMeterCtrl

End Class
