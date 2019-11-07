<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class StaticAOForm
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(StaticAOForm))
        Me.button_manualB = New System.Windows.Forms.Button
        Me.button_manualA = New System.Windows.Forms.Button
        Me.label_interval = New System.Windows.Forms.Label
        Me.label_chanA = New System.Windows.Forms.Label
        Me.label_chanB = New System.Windows.Forms.Label
        Me.textBox_lowLevelB = New System.Windows.Forms.TextBox
        Me.textBox_highLevelB = New System.Windows.Forms.TextBox
        Me.textBox_lowLevelA = New System.Windows.Forms.TextBox
        Me.textBox_highLevelA = New System.Windows.Forms.TextBox
        Me.textBox_valueB = New System.Windows.Forms.TextBox
        Me.textBox_valueA = New System.Windows.Forms.TextBox
        Me.checkBox_sineB = New System.Windows.Forms.CheckBox
        Me.checkBox_squareB = New System.Windows.Forms.CheckBox
        Me.checkBox_triangleB = New System.Windows.Forms.CheckBox
        Me.checkBox_sineA = New System.Windows.Forms.CheckBox
        Me.checkBox_squareA = New System.Windows.Forms.CheckBox
        Me.checkBox_triangleA = New System.Windows.Forms.CheckBox
        Me.trackBar_Scroll = New System.Windows.Forms.TrackBar
        Me.timer_outputData = New System.Windows.Forms.Timer(Me.components)
        Me.imageList = New System.Windows.Forms.ImageList(Me.components)
        Me.m_InstantAoCtrl = New Automation.BDaq.InstantAoCtrl(Me.components)
        CType(Me.trackBar_Scroll, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'button_manualB
        '
        Me.button_manualB.BackgroundImage = CType(resources.GetObject("button_manualB.BackgroundImage"), System.Drawing.Image)
        Me.button_manualB.Location = New System.Drawing.Point(287, 301)
        Me.button_manualB.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.button_manualB.Name = "button_manualB"
        Me.button_manualB.Size = New System.Drawing.Size(53, 50)
        Me.button_manualB.TabIndex = 65
        Me.button_manualB.UseVisualStyleBackColor = True
        '
        'button_manualA
        '
        Me.button_manualA.BackgroundImage = CType(resources.GetObject("button_manualA.BackgroundImage"), System.Drawing.Image)
        Me.button_manualA.Location = New System.Drawing.Point(287, 123)
        Me.button_manualA.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.button_manualA.Name = "button_manualA"
        Me.button_manualA.Size = New System.Drawing.Size(53, 50)
        Me.button_manualA.TabIndex = 64
        Me.button_manualA.UseVisualStyleBackColor = True
        '
        'label_interval
        '
        Me.label_interval.AutoSize = True
        Me.label_interval.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label_interval.ForeColor = System.Drawing.SystemColors.ControlText
        Me.label_interval.Image = CType(resources.GetObject("label_interval.Image"), System.Drawing.Image)
        Me.label_interval.Location = New System.Drawing.Point(259, 403)
        Me.label_interval.Name = "label_interval"
        Me.label_interval.Size = New System.Drawing.Size(38, 15)
        Me.label_interval.TabIndex = 63
        Me.label_interval.Text = "50ms"
        '
        'label_chanA
        '
        Me.label_chanA.AutoSize = True
        Me.label_chanA.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label_chanA.ForeColor = System.Drawing.Color.BurlyWood
        Me.label_chanA.Image = CType(resources.GetObject("label_chanA.Image"), System.Drawing.Image)
        Me.label_chanA.Location = New System.Drawing.Point(286, 33)
        Me.label_chanA.Name = "label_chanA"
        Me.label_chanA.Size = New System.Drawing.Size(15, 15)
        Me.label_chanA.TabIndex = 62
        Me.label_chanA.Text = "0"
        '
        'label_chanB
        '
        Me.label_chanB.AutoSize = True
        Me.label_chanB.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.label_chanB.ForeColor = System.Drawing.Color.BurlyWood
        Me.label_chanB.Image = CType(resources.GetObject("label_chanB.Image"), System.Drawing.Image)
        Me.label_chanB.Location = New System.Drawing.Point(286, 210)
        Me.label_chanB.Name = "label_chanB"
        Me.label_chanB.Size = New System.Drawing.Size(15, 15)
        Me.label_chanB.TabIndex = 61
        Me.label_chanB.Text = "1"
        '
        'textBox_lowLevelB
        '
        Me.textBox_lowLevelB.BackColor = System.Drawing.SystemColors.HighlightText
        Me.textBox_lowLevelB.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.textBox_lowLevelB.ForeColor = System.Drawing.SystemColors.ControlText
        Me.textBox_lowLevelB.Location = New System.Drawing.Point(164, 267)
        Me.textBox_lowLevelB.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.textBox_lowLevelB.Name = "textBox_lowLevelB"
        Me.textBox_lowLevelB.Size = New System.Drawing.Size(74, 21)
        Me.textBox_lowLevelB.TabIndex = 60
        Me.textBox_lowLevelB.Text = "-5"
        Me.textBox_lowLevelB.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'textBox_highLevelB
        '
        Me.textBox_highLevelB.BackColor = System.Drawing.SystemColors.HighlightText
        Me.textBox_highLevelB.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.textBox_highLevelB.ForeColor = System.Drawing.SystemColors.ControlText
        Me.textBox_highLevelB.Location = New System.Drawing.Point(74, 267)
        Me.textBox_highLevelB.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.textBox_highLevelB.Name = "textBox_highLevelB"
        Me.textBox_highLevelB.Size = New System.Drawing.Size(74, 21)
        Me.textBox_highLevelB.TabIndex = 59
        Me.textBox_highLevelB.Text = "5"
        Me.textBox_highLevelB.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'textBox_lowLevelA
        '
        Me.textBox_lowLevelA.BackColor = System.Drawing.SystemColors.HighlightText
        Me.textBox_lowLevelA.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.textBox_lowLevelA.ForeColor = System.Drawing.SystemColors.ControlText
        Me.textBox_lowLevelA.Location = New System.Drawing.Point(164, 89)
        Me.textBox_lowLevelA.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.textBox_lowLevelA.Name = "textBox_lowLevelA"
        Me.textBox_lowLevelA.Size = New System.Drawing.Size(74, 21)
        Me.textBox_lowLevelA.TabIndex = 58
        Me.textBox_lowLevelA.Text = "-5"
        Me.textBox_lowLevelA.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'textBox_highLevelA
        '
        Me.textBox_highLevelA.BackColor = System.Drawing.SystemColors.HighlightText
        Me.textBox_highLevelA.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.textBox_highLevelA.ForeColor = System.Drawing.SystemColors.ControlText
        Me.textBox_highLevelA.Location = New System.Drawing.Point(74, 89)
        Me.textBox_highLevelA.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.textBox_highLevelA.Name = "textBox_highLevelA"
        Me.textBox_highLevelA.Size = New System.Drawing.Size(74, 21)
        Me.textBox_highLevelA.TabIndex = 57
        Me.textBox_highLevelA.Text = "5"
        Me.textBox_highLevelA.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'textBox_valueB
        '
        Me.textBox_valueB.BackColor = System.Drawing.SystemColors.HighlightText
        Me.textBox_valueB.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.textBox_valueB.ForeColor = System.Drawing.SystemColors.ControlText
        Me.textBox_valueB.Location = New System.Drawing.Point(278, 267)
        Me.textBox_valueB.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.textBox_valueB.Name = "textBox_valueB"
        Me.textBox_valueB.Size = New System.Drawing.Size(65, 21)
        Me.textBox_valueB.TabIndex = 56
        Me.textBox_valueB.Text = "2.5"
        Me.textBox_valueB.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'textBox_valueA
        '
        Me.textBox_valueA.BackColor = System.Drawing.SystemColors.HighlightText
        Me.textBox_valueA.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.textBox_valueA.ForeColor = System.Drawing.SystemColors.ControlText
        Me.textBox_valueA.Location = New System.Drawing.Point(278, 89)
        Me.textBox_valueA.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.textBox_valueA.Name = "textBox_valueA"
        Me.textBox_valueA.Size = New System.Drawing.Size(65, 21)
        Me.textBox_valueA.TabIndex = 55
        Me.textBox_valueA.Text = "2.5"
        Me.textBox_valueA.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'checkBox_sineB
        '
        Me.checkBox_sineB.Appearance = System.Windows.Forms.Appearance.Button
        Me.checkBox_sineB.BackColor = System.Drawing.Color.Transparent
        Me.checkBox_sineB.BackgroundImage = CType(resources.GetObject("checkBox_sineB.BackgroundImage"), System.Drawing.Image)
        Me.checkBox_sineB.CheckAlign = System.Drawing.ContentAlignment.TopCenter
        Me.checkBox_sineB.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me.checkBox_sineB.Location = New System.Drawing.Point(63, 301)
        Me.checkBox_sineB.Margin = New System.Windows.Forms.Padding(1)
        Me.checkBox_sineB.Name = "checkBox_sineB"
        Me.checkBox_sineB.Size = New System.Drawing.Size(53, 50)
        Me.checkBox_sineB.TabIndex = 54
        Me.checkBox_sineB.UseVisualStyleBackColor = False
        '
        'checkBox_squareB
        '
        Me.checkBox_squareB.Appearance = System.Windows.Forms.Appearance.Button
        Me.checkBox_squareB.BackColor = System.Drawing.Color.Transparent
        Me.checkBox_squareB.BackgroundImage = CType(resources.GetObject("checkBox_squareB.BackgroundImage"), System.Drawing.Image)
        Me.checkBox_squareB.CheckAlign = System.Drawing.ContentAlignment.TopCenter
        Me.checkBox_squareB.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me.checkBox_squareB.Location = New System.Drawing.Point(131, 301)
        Me.checkBox_squareB.Margin = New System.Windows.Forms.Padding(1)
        Me.checkBox_squareB.Name = "checkBox_squareB"
        Me.checkBox_squareB.Size = New System.Drawing.Size(53, 50)
        Me.checkBox_squareB.TabIndex = 53
        Me.checkBox_squareB.UseVisualStyleBackColor = False
        '
        'checkBox_triangleB
        '
        Me.checkBox_triangleB.Appearance = System.Windows.Forms.Appearance.Button
        Me.checkBox_triangleB.BackColor = System.Drawing.Color.Transparent
        Me.checkBox_triangleB.BackgroundImage = CType(resources.GetObject("checkBox_triangleB.BackgroundImage"), System.Drawing.Image)
        Me.checkBox_triangleB.CheckAlign = System.Drawing.ContentAlignment.TopCenter
        Me.checkBox_triangleB.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me.checkBox_triangleB.Location = New System.Drawing.Point(197, 301)
        Me.checkBox_triangleB.Margin = New System.Windows.Forms.Padding(1)
        Me.checkBox_triangleB.Name = "checkBox_triangleB"
        Me.checkBox_triangleB.Size = New System.Drawing.Size(53, 50)
        Me.checkBox_triangleB.TabIndex = 52
        Me.checkBox_triangleB.UseVisualStyleBackColor = False
        '
        'checkBox_sineA
        '
        Me.checkBox_sineA.Appearance = System.Windows.Forms.Appearance.Button
        Me.checkBox_sineA.BackColor = System.Drawing.Color.Transparent
        Me.checkBox_sineA.BackgroundImage = CType(resources.GetObject("checkBox_sineA.BackgroundImage"), System.Drawing.Image)
        Me.checkBox_sineA.CheckAlign = System.Drawing.ContentAlignment.TopCenter
        Me.checkBox_sineA.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me.checkBox_sineA.Location = New System.Drawing.Point(63, 123)
        Me.checkBox_sineA.Margin = New System.Windows.Forms.Padding(1)
        Me.checkBox_sineA.Name = "checkBox_sineA"
        Me.checkBox_sineA.Size = New System.Drawing.Size(53, 50)
        Me.checkBox_sineA.TabIndex = 51
        Me.checkBox_sineA.UseVisualStyleBackColor = False
        '
        'checkBox_squareA
        '
        Me.checkBox_squareA.Appearance = System.Windows.Forms.Appearance.Button
        Me.checkBox_squareA.BackColor = System.Drawing.Color.Transparent
        Me.checkBox_squareA.BackgroundImage = CType(resources.GetObject("checkBox_squareA.BackgroundImage"), System.Drawing.Image)
        Me.checkBox_squareA.CheckAlign = System.Drawing.ContentAlignment.TopCenter
        Me.checkBox_squareA.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me.checkBox_squareA.Location = New System.Drawing.Point(131, 123)
        Me.checkBox_squareA.Margin = New System.Windows.Forms.Padding(1)
        Me.checkBox_squareA.Name = "checkBox_squareA"
        Me.checkBox_squareA.Size = New System.Drawing.Size(53, 50)
        Me.checkBox_squareA.TabIndex = 50
        Me.checkBox_squareA.UseVisualStyleBackColor = False
        '
        'checkBox_triangleA
        '
        Me.checkBox_triangleA.Appearance = System.Windows.Forms.Appearance.Button
        Me.checkBox_triangleA.BackColor = System.Drawing.Color.Transparent
        Me.checkBox_triangleA.BackgroundImage = CType(resources.GetObject("checkBox_triangleA.BackgroundImage"), System.Drawing.Image)
        Me.checkBox_triangleA.CheckAlign = System.Drawing.ContentAlignment.TopCenter
        Me.checkBox_triangleA.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me.checkBox_triangleA.Location = New System.Drawing.Point(197, 123)
        Me.checkBox_triangleA.Margin = New System.Windows.Forms.Padding(1)
        Me.checkBox_triangleA.Name = "checkBox_triangleA"
        Me.checkBox_triangleA.Size = New System.Drawing.Size(53, 50)
        Me.checkBox_triangleA.TabIndex = 48
        Me.checkBox_triangleA.UseVisualStyleBackColor = False
        '
        'trackBar_Scroll
        '
        Me.trackBar_Scroll.AutoSize = False
        Me.trackBar_Scroll.BackColor = System.Drawing.Color.FromArgb(CType(CType(236, Byte), Integer), CType(CType(233, Byte), Integer), CType(CType(216, Byte), Integer))
        Me.trackBar_Scroll.Location = New System.Drawing.Point(149, 400)
        Me.trackBar_Scroll.Margin = New System.Windows.Forms.Padding(3, 5, 3, 5)
        Me.trackBar_Scroll.Maximum = 1000
        Me.trackBar_Scroll.Minimum = 10
        Me.trackBar_Scroll.Name = "trackBar_Scroll"
        Me.trackBar_Scroll.Size = New System.Drawing.Size(103, 23)
        Me.trackBar_Scroll.TabIndex = 49
        Me.trackBar_Scroll.TickFrequency = 100
        Me.trackBar_Scroll.Value = 50
        '
        'timer_outputData
        '
        '
        'imageList
        '
        Me.imageList.ImageStream = CType(resources.GetObject("imageList.ImageStream"), System.Windows.Forms.ImageListStreamer)
        Me.imageList.TransparentColor = System.Drawing.Color.Transparent
        Me.imageList.Images.SetKeyName(0, "sine.bmp")
        Me.imageList.Images.SetKeyName(1, "square.bmp")
        Me.imageList.Images.SetKeyName(2, "triangle.bmp")
        Me.imageList.Images.SetKeyName(3, "sine_down.bmp")
        Me.imageList.Images.SetKeyName(4, "square_down.bmp")
        Me.imageList.Images.SetKeyName(5, "triangle_down.bmp")
        '
        'm_InstantAoCtrl
        '
        Me.m_InstantAoCtrl._StateStream = CType(resources.GetObject("m_InstantAoCtrl._StateStream"), Automation.BDaq.DeviceStateStreamer)
        '
        'StaticAOForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackgroundImage = CType(resources.GetObject("$this.BackgroundImage"), System.Drawing.Image)
        Me.ClientSize = New System.Drawing.Size(391, 451)
        Me.Controls.Add(Me.button_manualB)
        Me.Controls.Add(Me.button_manualA)
        Me.Controls.Add(Me.label_interval)
        Me.Controls.Add(Me.label_chanA)
        Me.Controls.Add(Me.label_chanB)
        Me.Controls.Add(Me.textBox_lowLevelB)
        Me.Controls.Add(Me.textBox_highLevelB)
        Me.Controls.Add(Me.textBox_lowLevelA)
        Me.Controls.Add(Me.textBox_highLevelA)
        Me.Controls.Add(Me.textBox_valueB)
        Me.Controls.Add(Me.textBox_valueA)
        Me.Controls.Add(Me.checkBox_sineB)
        Me.Controls.Add(Me.checkBox_squareB)
        Me.Controls.Add(Me.checkBox_triangleB)
        Me.Controls.Add(Me.checkBox_sineA)
        Me.Controls.Add(Me.checkBox_squareA)
        Me.Controls.Add(Me.checkBox_triangleA)
        Me.Controls.Add(Me.trackBar_Scroll)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "StaticAOForm"
        Me.Text = "Static AO"
        CType(Me.trackBar_Scroll, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Private WithEvents button_manualB As System.Windows.Forms.Button
    Private WithEvents button_manualA As System.Windows.Forms.Button
    Private WithEvents label_interval As System.Windows.Forms.Label
    Private WithEvents label_chanA As System.Windows.Forms.Label
    Private WithEvents label_chanB As System.Windows.Forms.Label
    Private WithEvents textBox_lowLevelB As System.Windows.Forms.TextBox
    Private WithEvents textBox_highLevelB As System.Windows.Forms.TextBox
    Private WithEvents textBox_lowLevelA As System.Windows.Forms.TextBox
    Private WithEvents textBox_highLevelA As System.Windows.Forms.TextBox
    Private WithEvents textBox_valueB As System.Windows.Forms.TextBox
    Private WithEvents textBox_valueA As System.Windows.Forms.TextBox
    Private WithEvents checkBox_sineB As System.Windows.Forms.CheckBox
    Private WithEvents checkBox_squareB As System.Windows.Forms.CheckBox
    Private WithEvents checkBox_triangleB As System.Windows.Forms.CheckBox
    Private WithEvents checkBox_sineA As System.Windows.Forms.CheckBox
    Private WithEvents checkBox_squareA As System.Windows.Forms.CheckBox
    Private WithEvents checkBox_triangleA As System.Windows.Forms.CheckBox
    Private WithEvents trackBar_Scroll As System.Windows.Forms.TrackBar
    Private WithEvents timer_outputData As System.Windows.Forms.Timer
    Private WithEvents imageList As System.Windows.Forms.ImageList
    Friend WithEvents m_InstantAoCtrl As Automation.BDaq.InstantAoCtrl

End Class
