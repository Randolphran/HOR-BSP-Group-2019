<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class SynchronousOneWaveformAOForm
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(SynchronousOneWaveformAOForm))
        Me.button_start = New System.Windows.Forms.Button
        Me.label_chanA = New System.Windows.Forms.Label
        Me.label_chanB = New System.Windows.Forms.Label
        Me.textBox_lowLevelB = New System.Windows.Forms.TextBox
        Me.textBox_highLevelB = New System.Windows.Forms.TextBox
        Me.textBox_lowLevelA = New System.Windows.Forms.TextBox
        Me.textBox_highLevelA = New System.Windows.Forms.TextBox
        Me.checkBox_sineB = New System.Windows.Forms.CheckBox
        Me.checkBox_squareB = New System.Windows.Forms.CheckBox
        Me.checkBox_triangleB = New System.Windows.Forms.CheckBox
        Me.checkBox_sineA = New System.Windows.Forms.CheckBox
        Me.checkBox_squareA = New System.Windows.Forms.CheckBox
        Me.checkBox_triangleA = New System.Windows.Forms.CheckBox
        Me.ImageList = New System.Windows.Forms.ImageList(Me.components)
        Me.m_BufferedAoCtrl = New Automation.BDaq.BufferedAoCtrl(Me.components)
        Me.SuspendLayout()
        '
        'button_start
        '
        Me.button_start.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.button_start.ForeColor = System.Drawing.SystemColors.ControlText
        Me.button_start.Location = New System.Drawing.Point(190, 393)
        Me.button_start.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.button_start.Name = "button_start"
        Me.button_start.Size = New System.Drawing.Size(92, 28)
        Me.button_start.TabIndex = 58
        Me.button_start.Text = "Start"
        Me.button_start.UseVisualStyleBackColor = True
        '
        'label_chanA
        '
        Me.label_chanA.AutoSize = True
        Me.label_chanA.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label_chanA.ForeColor = System.Drawing.Color.BurlyWood
        Me.label_chanA.Image = CType(resources.GetObject("label_chanA.Image"), System.Drawing.Image)
        Me.label_chanA.Location = New System.Drawing.Point(238, 31)
        Me.label_chanA.Name = "label_chanA"
        Me.label_chanA.Size = New System.Drawing.Size(15, 15)
        Me.label_chanA.TabIndex = 57
        Me.label_chanA.Text = "0"
        '
        'label_chanB
        '
        Me.label_chanB.AutoSize = True
        Me.label_chanB.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label_chanB.ForeColor = System.Drawing.Color.BurlyWood
        Me.label_chanB.Image = CType(resources.GetObject("label_chanB.Image"), System.Drawing.Image)
        Me.label_chanB.Location = New System.Drawing.Point(238, 217)
        Me.label_chanB.Name = "label_chanB"
        Me.label_chanB.Size = New System.Drawing.Size(15, 15)
        Me.label_chanB.TabIndex = 56
        Me.label_chanB.Text = "1"
        '
        'textBox_lowLevelB
        '
        Me.textBox_lowLevelB.BackColor = System.Drawing.SystemColors.HighlightText
        Me.textBox_lowLevelB.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.textBox_lowLevelB.ForeColor = System.Drawing.SystemColors.ControlText
        Me.textBox_lowLevelB.Location = New System.Drawing.Point(192, 274)
        Me.textBox_lowLevelB.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.textBox_lowLevelB.Name = "textBox_lowLevelB"
        Me.textBox_lowLevelB.Size = New System.Drawing.Size(74, 21)
        Me.textBox_lowLevelB.TabIndex = 55
        Me.textBox_lowLevelB.Text = "-5"
        Me.textBox_lowLevelB.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'textBox_highLevelB
        '
        Me.textBox_highLevelB.BackColor = System.Drawing.SystemColors.HighlightText
        Me.textBox_highLevelB.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.textBox_highLevelB.ForeColor = System.Drawing.SystemColors.ControlText
        Me.textBox_highLevelB.Location = New System.Drawing.Point(82, 274)
        Me.textBox_highLevelB.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.textBox_highLevelB.Name = "textBox_highLevelB"
        Me.textBox_highLevelB.Size = New System.Drawing.Size(74, 21)
        Me.textBox_highLevelB.TabIndex = 54
        Me.textBox_highLevelB.Text = "5"
        Me.textBox_highLevelB.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'textBox_lowLevelA
        '
        Me.textBox_lowLevelA.BackColor = System.Drawing.SystemColors.HighlightText
        Me.textBox_lowLevelA.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.textBox_lowLevelA.ForeColor = System.Drawing.SystemColors.ControlText
        Me.textBox_lowLevelA.Location = New System.Drawing.Point(192, 88)
        Me.textBox_lowLevelA.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.textBox_lowLevelA.Name = "textBox_lowLevelA"
        Me.textBox_lowLevelA.Size = New System.Drawing.Size(75, 21)
        Me.textBox_lowLevelA.TabIndex = 53
        Me.textBox_lowLevelA.Text = "-5"
        Me.textBox_lowLevelA.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'textBox_highLevelA
        '
        Me.textBox_highLevelA.BackColor = System.Drawing.SystemColors.HighlightText
        Me.textBox_highLevelA.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.textBox_highLevelA.ForeColor = System.Drawing.SystemColors.ControlText
        Me.textBox_highLevelA.Location = New System.Drawing.Point(82, 89)
        Me.textBox_highLevelA.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.textBox_highLevelA.Name = "textBox_highLevelA"
        Me.textBox_highLevelA.Size = New System.Drawing.Size(74, 21)
        Me.textBox_highLevelA.TabIndex = 52
        Me.textBox_highLevelA.Text = "5"
        Me.textBox_highLevelA.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'checkBox_sineB
        '
        Me.checkBox_sineB.Appearance = System.Windows.Forms.Appearance.Button
        Me.checkBox_sineB.BackColor = System.Drawing.Color.Transparent
        Me.checkBox_sineB.BackgroundImage = CType(resources.GetObject("checkBox_sineB.BackgroundImage"), System.Drawing.Image)
        Me.checkBox_sineB.CheckAlign = System.Drawing.ContentAlignment.TopCenter
        Me.checkBox_sineB.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me.checkBox_sineB.Location = New System.Drawing.Point(69, 307)
        Me.checkBox_sineB.Margin = New System.Windows.Forms.Padding(1)
        Me.checkBox_sineB.Name = "checkBox_sineB"
        Me.checkBox_sineB.Size = New System.Drawing.Size(53, 50)
        Me.checkBox_sineB.TabIndex = 51
        Me.checkBox_sineB.UseVisualStyleBackColor = False
        '
        'checkBox_squareB
        '
        Me.checkBox_squareB.Appearance = System.Windows.Forms.Appearance.Button
        Me.checkBox_squareB.BackColor = System.Drawing.Color.Transparent
        Me.checkBox_squareB.BackgroundImage = CType(resources.GetObject("checkBox_squareB.BackgroundImage"), System.Drawing.Image)
        Me.checkBox_squareB.CheckAlign = System.Drawing.ContentAlignment.TopCenter
        Me.checkBox_squareB.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me.checkBox_squareB.Location = New System.Drawing.Point(149, 307)
        Me.checkBox_squareB.Margin = New System.Windows.Forms.Padding(1)
        Me.checkBox_squareB.Name = "checkBox_squareB"
        Me.checkBox_squareB.Size = New System.Drawing.Size(53, 50)
        Me.checkBox_squareB.TabIndex = 50
        Me.checkBox_squareB.UseVisualStyleBackColor = False
        '
        'checkBox_triangleB
        '
        Me.checkBox_triangleB.Appearance = System.Windows.Forms.Appearance.Button
        Me.checkBox_triangleB.BackColor = System.Drawing.Color.Transparent
        Me.checkBox_triangleB.BackgroundImage = CType(resources.GetObject("checkBox_triangleB.BackgroundImage"), System.Drawing.Image)
        Me.checkBox_triangleB.CheckAlign = System.Drawing.ContentAlignment.TopCenter
        Me.checkBox_triangleB.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me.checkBox_triangleB.Location = New System.Drawing.Point(227, 307)
        Me.checkBox_triangleB.Margin = New System.Windows.Forms.Padding(1)
        Me.checkBox_triangleB.Name = "checkBox_triangleB"
        Me.checkBox_triangleB.Size = New System.Drawing.Size(53, 50)
        Me.checkBox_triangleB.TabIndex = 49
        Me.checkBox_triangleB.UseVisualStyleBackColor = False
        '
        'checkBox_sineA
        '
        Me.checkBox_sineA.Appearance = System.Windows.Forms.Appearance.Button
        Me.checkBox_sineA.BackColor = System.Drawing.Color.Transparent
        Me.checkBox_sineA.BackgroundImage = CType(resources.GetObject("checkBox_sineA.BackgroundImage"), System.Drawing.Image)
        Me.checkBox_sineA.CheckAlign = System.Drawing.ContentAlignment.TopCenter
        Me.checkBox_sineA.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me.checkBox_sineA.Location = New System.Drawing.Point(69, 121)
        Me.checkBox_sineA.Margin = New System.Windows.Forms.Padding(1)
        Me.checkBox_sineA.Name = "checkBox_sineA"
        Me.checkBox_sineA.Size = New System.Drawing.Size(53, 50)
        Me.checkBox_sineA.TabIndex = 48
        Me.checkBox_sineA.UseVisualStyleBackColor = False
        '
        'checkBox_squareA
        '
        Me.checkBox_squareA.Appearance = System.Windows.Forms.Appearance.Button
        Me.checkBox_squareA.BackColor = System.Drawing.Color.Transparent
        Me.checkBox_squareA.BackgroundImage = CType(resources.GetObject("checkBox_squareA.BackgroundImage"), System.Drawing.Image)
        Me.checkBox_squareA.CheckAlign = System.Drawing.ContentAlignment.TopCenter
        Me.checkBox_squareA.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me.checkBox_squareA.Location = New System.Drawing.Point(149, 121)
        Me.checkBox_squareA.Margin = New System.Windows.Forms.Padding(1)
        Me.checkBox_squareA.Name = "checkBox_squareA"
        Me.checkBox_squareA.Size = New System.Drawing.Size(53, 50)
        Me.checkBox_squareA.TabIndex = 47
        Me.checkBox_squareA.UseVisualStyleBackColor = False
        '
        'checkBox_triangleA
        '
        Me.checkBox_triangleA.Appearance = System.Windows.Forms.Appearance.Button
        Me.checkBox_triangleA.BackColor = System.Drawing.Color.Transparent
        Me.checkBox_triangleA.BackgroundImage = CType(resources.GetObject("checkBox_triangleA.BackgroundImage"), System.Drawing.Image)
        Me.checkBox_triangleA.CheckAlign = System.Drawing.ContentAlignment.TopCenter
        Me.checkBox_triangleA.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me.checkBox_triangleA.Location = New System.Drawing.Point(227, 121)
        Me.checkBox_triangleA.Margin = New System.Windows.Forms.Padding(1)
        Me.checkBox_triangleA.Name = "checkBox_triangleA"
        Me.checkBox_triangleA.Size = New System.Drawing.Size(53, 50)
        Me.checkBox_triangleA.TabIndex = 46
        Me.checkBox_triangleA.UseVisualStyleBackColor = False
        '
        'ImageList
        '
        Me.ImageList.ImageStream = CType(resources.GetObject("ImageList.ImageStream"), System.Windows.Forms.ImageListStreamer)
        Me.ImageList.TransparentColor = System.Drawing.Color.Transparent
        Me.ImageList.Images.SetKeyName(0, "sine.bmp")
        Me.ImageList.Images.SetKeyName(1, "square.bmp")
        Me.ImageList.Images.SetKeyName(2, "triangle.bmp")
        Me.ImageList.Images.SetKeyName(3, "sine_down.bmp")
        Me.ImageList.Images.SetKeyName(4, "square_down.bmp")
        Me.ImageList.Images.SetKeyName(5, "triangle_down.bmp")
        '
        'm_BufferedAoCtrl
        '
        Me.m_BufferedAoCtrl._StateStream = CType(resources.GetObject("m_BufferedAoCtrl._StateStream"), Automation.BDaq.DeviceStateStreamer)
        '
        'SynchronousOneWaveformAOForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackgroundImage = CType(resources.GetObject("$this.BackgroundImage"), System.Drawing.Image)
        Me.ClientSize = New System.Drawing.Size(349, 438)
        Me.Controls.Add(Me.button_start)
        Me.Controls.Add(Me.label_chanA)
        Me.Controls.Add(Me.label_chanB)
        Me.Controls.Add(Me.textBox_lowLevelB)
        Me.Controls.Add(Me.textBox_highLevelB)
        Me.Controls.Add(Me.textBox_lowLevelA)
        Me.Controls.Add(Me.textBox_highLevelA)
        Me.Controls.Add(Me.checkBox_sineB)
        Me.Controls.Add(Me.checkBox_squareB)
        Me.Controls.Add(Me.checkBox_triangleB)
        Me.Controls.Add(Me.checkBox_sineA)
        Me.Controls.Add(Me.checkBox_squareA)
        Me.Controls.Add(Me.checkBox_triangleA)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "SynchronousOneWaveformAOForm"
        Me.Text = "Synchronous One Waveform out"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Private WithEvents button_start As System.Windows.Forms.Button
    Private WithEvents label_chanA As System.Windows.Forms.Label
    Private WithEvents label_chanB As System.Windows.Forms.Label
    Private WithEvents textBox_lowLevelB As System.Windows.Forms.TextBox
    Private WithEvents textBox_highLevelB As System.Windows.Forms.TextBox
    Private WithEvents textBox_lowLevelA As System.Windows.Forms.TextBox
    Private WithEvents textBox_highLevelA As System.Windows.Forms.TextBox
    Private WithEvents checkBox_sineB As System.Windows.Forms.CheckBox
    Private WithEvents checkBox_squareB As System.Windows.Forms.CheckBox
    Private WithEvents checkBox_triangleB As System.Windows.Forms.CheckBox
    Private WithEvents checkBox_sineA As System.Windows.Forms.CheckBox
    Private WithEvents checkBox_squareA As System.Windows.Forms.CheckBox
    Private WithEvents checkBox_triangleA As System.Windows.Forms.CheckBox
    Friend WithEvents ImageList As System.Windows.Forms.ImageList
    Friend WithEvents m_BufferedAoCtrl As Automation.BDaq.BufferedAoCtrl

End Class
