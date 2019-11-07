<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class AsynchronousOneBufferedAIForm
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(AsynchronousOneBufferedAIForm))
        Me.listView = New System.Windows.Forms.ListView
        Me.label_YCoordinateMin = New System.Windows.Forms.Label
        Me.label_YCoordinateMiddle = New System.Windows.Forms.Label
        Me.label_YCoordinateMax = New System.Windows.Forms.Label
        Me.label_XCoordinateMax = New System.Windows.Forms.Label
        Me.label_XCoordinateMin = New System.Windows.Forms.Label
        Me.label_divide = New System.Windows.Forms.Label
        Me.button_getData = New System.Windows.Forms.Button
        Me.label_shift = New System.Windows.Forms.Label
        Me.trackBar_div = New System.Windows.Forms.TrackBar
        Me.trackBar_shift = New System.Windows.Forms.TrackBar
        Me.textBox_div = New System.Windows.Forms.TextBox
        Me.label3 = New System.Windows.Forms.Label
        Me.textBox_shift = New System.Windows.Forms.TextBox
        Me.label2 = New System.Windows.Forms.Label
        Me.label1 = New System.Windows.Forms.Label
        Me.pictureBox = New System.Windows.Forms.PictureBox
        Me.WaveformAiCtrl1 = New Automation.BDaq.WaveformAiCtrl(Me.components)
        CType(Me.trackBar_div, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.trackBar_shift, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.pictureBox, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'listView
        '
        Me.listView.Location = New System.Drawing.Point(154, 397)
        Me.listView.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.listView.Name = "listView"
        Me.listView.Size = New System.Drawing.Size(512, 38)
        Me.listView.TabIndex = 59
        Me.listView.TabStop = False
        Me.listView.UseCompatibleStateImageBehavior = False
        '
        'label_YCoordinateMin
        '
        Me.label_YCoordinateMin.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label_YCoordinateMin.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label_YCoordinateMin.Location = New System.Drawing.Point(-5, 359)
        Me.label_YCoordinateMin.Name = "label_YCoordinateMin"
        Me.label_YCoordinateMin.Size = New System.Drawing.Size(52, 15)
        Me.label_YCoordinateMin.TabIndex = 58
        Me.label_YCoordinateMin.Text = "0V"
        Me.label_YCoordinateMin.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'label_YCoordinateMiddle
        '
        Me.label_YCoordinateMiddle.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label_YCoordinateMiddle.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label_YCoordinateMiddle.Location = New System.Drawing.Point(-3, 204)
        Me.label_YCoordinateMiddle.Name = "label_YCoordinateMiddle"
        Me.label_YCoordinateMiddle.Size = New System.Drawing.Size(52, 15)
        Me.label_YCoordinateMiddle.TabIndex = 57
        Me.label_YCoordinateMiddle.Text = "0V"
        Me.label_YCoordinateMiddle.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'label_YCoordinateMax
        '
        Me.label_YCoordinateMax.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label_YCoordinateMax.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label_YCoordinateMax.Location = New System.Drawing.Point(-4, 36)
        Me.label_YCoordinateMax.Name = "label_YCoordinateMax"
        Me.label_YCoordinateMax.Size = New System.Drawing.Size(52, 15)
        Me.label_YCoordinateMax.TabIndex = 56
        Me.label_YCoordinateMax.Text = "5V"
        Me.label_YCoordinateMax.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'label_XCoordinateMax
        '
        Me.label_XCoordinateMax.AutoSize = True
        Me.label_XCoordinateMax.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label_XCoordinateMax.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label_XCoordinateMax.Location = New System.Drawing.Point(669, 379)
        Me.label_XCoordinateMax.Name = "label_XCoordinateMax"
        Me.label_XCoordinateMax.Size = New System.Drawing.Size(45, 15)
        Me.label_XCoordinateMax.TabIndex = 55
        Me.label_XCoordinateMax.Text = "10 Sec"
        '
        'label_XCoordinateMin
        '
        Me.label_XCoordinateMin.AutoSize = True
        Me.label_XCoordinateMin.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label_XCoordinateMin.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label_XCoordinateMin.Location = New System.Drawing.Point(49, 380)
        Me.label_XCoordinateMin.Name = "label_XCoordinateMin"
        Me.label_XCoordinateMin.Size = New System.Drawing.Size(38, 15)
        Me.label_XCoordinateMin.TabIndex = 54
        Me.label_XCoordinateMin.Text = "0 Sec"
        '
        'label_divide
        '
        Me.label_divide.AutoSize = True
        Me.label_divide.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label_divide.Location = New System.Drawing.Point(508, 450)
        Me.label_divide.Name = "label_divide"
        Me.label_divide.Size = New System.Drawing.Size(24, 15)
        Me.label_divide.TabIndex = 53
        Me.label_divide.Text = "ms"
        '
        'button_getData
        '
        Me.button_getData.CausesValidation = False
        Me.button_getData.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.button_getData.Location = New System.Drawing.Point(604, 483)
        Me.button_getData.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.button_getData.Name = "button_getData"
        Me.button_getData.Size = New System.Drawing.Size(87, 25)
        Me.button_getData.TabIndex = 52
        Me.button_getData.Text = "Get Data"
        Me.button_getData.UseVisualStyleBackColor = True
        '
        'label_shift
        '
        Me.label_shift.AutoSize = True
        Me.label_shift.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label_shift.Location = New System.Drawing.Point(168, 451)
        Me.label_shift.Name = "label_shift"
        Me.label_shift.Size = New System.Drawing.Size(24, 15)
        Me.label_shift.TabIndex = 51
        Me.label_shift.Text = "ms"
        '
        'trackBar_div
        '
        Me.trackBar_div.AutoSize = False
        Me.trackBar_div.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.trackBar_div.Location = New System.Drawing.Point(536, 449)
        Me.trackBar_div.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.trackBar_div.Maximum = 1000
        Me.trackBar_div.Minimum = 10
        Me.trackBar_div.Name = "trackBar_div"
        Me.trackBar_div.Size = New System.Drawing.Size(173, 23)
        Me.trackBar_div.TabIndex = 50
        Me.trackBar_div.TickFrequency = 100
        Me.trackBar_div.Value = 100
        '
        'trackBar_shift
        '
        Me.trackBar_shift.AutoSize = False
        Me.trackBar_shift.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.trackBar_shift.Location = New System.Drawing.Point(195, 450)
        Me.trackBar_shift.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.trackBar_shift.Maximum = 1000
        Me.trackBar_shift.Name = "trackBar_shift"
        Me.trackBar_shift.Size = New System.Drawing.Size(149, 25)
        Me.trackBar_shift.TabIndex = 49
        Me.trackBar_shift.TickFrequency = 100
        '
        'textBox_div
        '
        Me.textBox_div.Location = New System.Drawing.Point(425, 449)
        Me.textBox_div.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.textBox_div.Name = "textBox_div"
        Me.textBox_div.Size = New System.Drawing.Size(81, 21)
        Me.textBox_div.TabIndex = 48
        Me.textBox_div.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'label3
        '
        Me.label3.AutoSize = True
        Me.label3.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label3.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label3.Location = New System.Drawing.Point(391, 452)
        Me.label3.Name = "label3"
        Me.label3.Size = New System.Drawing.Size(27, 15)
        Me.label3.TabIndex = 47
        Me.label3.Text = "Div:"
        '
        'textBox_shift
        '
        Me.textBox_shift.Location = New System.Drawing.Point(86, 449)
        Me.textBox_shift.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.textBox_shift.Name = "textBox_shift"
        Me.textBox_shift.Size = New System.Drawing.Size(81, 21)
        Me.textBox_shift.TabIndex = 46
        Me.textBox_shift.Text = "10"
        Me.textBox_shift.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'label2
        '
        Me.label2.AutoSize = True
        Me.label2.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label2.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label2.Location = New System.Drawing.Point(47, 453)
        Me.label2.Name = "label2"
        Me.label2.Size = New System.Drawing.Size(34, 15)
        Me.label2.TabIndex = 45
        Me.label2.Text = "Shift:"
        '
        'label1
        '
        Me.label1.AutoSize = True
        Me.label1.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label1.Location = New System.Drawing.Point(49, 409)
        Me.label1.Name = "label1"
        Me.label1.Size = New System.Drawing.Size(105, 15)
        Me.label1.TabIndex = 44
        Me.label1.Text = "Color of channels:"
        '
        'pictureBox
        '
        Me.pictureBox.BackColor = System.Drawing.SystemColors.ControlText
        Me.pictureBox.Location = New System.Drawing.Point(50, 36)
        Me.pictureBox.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.pictureBox.Name = "pictureBox"
        Me.pictureBox.Size = New System.Drawing.Size(660, 340)
        Me.pictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.pictureBox.TabIndex = 43
        Me.pictureBox.TabStop = False
        '
        'WaveformAiCtrl1
        '
        Me.WaveformAiCtrl1._StateStream = CType(resources.GetObject("WaveformAiCtrl1._StateStream"), Automation.BDaq.DeviceStateStreamer)
        '
        'AsynchronousOneBufferedAIForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackgroundImage = CType(resources.GetObject("$this.BackgroundImage"), System.Drawing.Image)
        Me.ClientSize = New System.Drawing.Size(756, 517)
        Me.Controls.Add(Me.listView)
        Me.Controls.Add(Me.label_YCoordinateMin)
        Me.Controls.Add(Me.label_YCoordinateMiddle)
        Me.Controls.Add(Me.label_YCoordinateMax)
        Me.Controls.Add(Me.label_XCoordinateMax)
        Me.Controls.Add(Me.label_XCoordinateMin)
        Me.Controls.Add(Me.label_divide)
        Me.Controls.Add(Me.button_getData)
        Me.Controls.Add(Me.label_shift)
        Me.Controls.Add(Me.trackBar_div)
        Me.Controls.Add(Me.trackBar_shift)
        Me.Controls.Add(Me.textBox_div)
        Me.Controls.Add(Me.label3)
        Me.Controls.Add(Me.textBox_shift)
        Me.Controls.Add(Me.label2)
        Me.Controls.Add(Me.label1)
        Me.Controls.Add(Me.pictureBox)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "AsynchronousOneBufferedAIForm"
        Me.Text = "Asynchronous One Buffered AI"
        CType(Me.trackBar_div, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.trackBar_shift, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.pictureBox, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Private WithEvents listView As System.Windows.Forms.ListView
    Private WithEvents label_YCoordinateMin As System.Windows.Forms.Label
    Private WithEvents label_YCoordinateMiddle As System.Windows.Forms.Label
    Private WithEvents label_YCoordinateMax As System.Windows.Forms.Label
    Public WithEvents label_XCoordinateMax As System.Windows.Forms.Label
    Private WithEvents label_XCoordinateMin As System.Windows.Forms.Label
    Private WithEvents label_divide As System.Windows.Forms.Label
    Private WithEvents button_getData As System.Windows.Forms.Button
    Public WithEvents label_shift As System.Windows.Forms.Label
    Private WithEvents trackBar_div As System.Windows.Forms.TrackBar
    Private WithEvents trackBar_shift As System.Windows.Forms.TrackBar
    Private WithEvents textBox_div As System.Windows.Forms.TextBox
    Private WithEvents label3 As System.Windows.Forms.Label
    Private WithEvents textBox_shift As System.Windows.Forms.TextBox
    Private WithEvents label2 As System.Windows.Forms.Label
    Private WithEvents label1 As System.Windows.Forms.Label
	Private WithEvents pictureBox As System.Windows.Forms.PictureBox
	Friend WithEvents WaveformAiCtrl1 As Automation.BDaq.WaveformAiCtrl

End Class
