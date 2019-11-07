<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class DIInterruptForm
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(DIInterruptForm))
        Me.columnHeader1 = New System.Windows.Forms.ColumnHeader
        Me.columnHeader2 = New System.Windows.Forms.ColumnHeader
        Me.ColumnHeader3 = New System.Windows.Forms.ColumnHeader
        Me.ColumnHeader4 = New System.Windows.Forms.ColumnHeader
        Me.buttonStop = New System.Windows.Forms.Button
        Me.ExecutionStatus = New System.Windows.Forms.PictureBox
        Me.buttonStart = New System.Windows.Forms.Button
        Me.pictureBox2 = New System.Windows.Forms.PictureBox
        Me.InstantDiCtrl1 = New Automation.BDaq.InstantDiCtrl(Me.components)
        Me.listViewForData = New MyListView.DoubleBufferListView
        Me.IntChannel = New System.Windows.Forms.ColumnHeader
        Me.PortsData = New System.Windows.Forms.ColumnHeader
        CType(Me.ExecutionStatus, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.pictureBox2, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'buttonStop
        '
        Me.buttonStop.Location = New System.Drawing.Point(332, 127)
        Me.buttonStop.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.buttonStop.Name = "buttonStop"
        Me.buttonStop.Size = New System.Drawing.Size(96, 30)
        Me.buttonStop.TabIndex = 8
        Me.buttonStop.Text = "Stop"
        Me.buttonStop.UseVisualStyleBackColor = True
        '
        'ExecutionStatus
        '
        Me.ExecutionStatus.Image = CType(resources.GetObject("ExecutionStatus.Image"), System.Drawing.Image)
        Me.ExecutionStatus.Location = New System.Drawing.Point(255, 8)
        Me.ExecutionStatus.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.ExecutionStatus.Name = "ExecutionStatus"
        Me.ExecutionStatus.Size = New System.Drawing.Size(20, 20)
        Me.ExecutionStatus.TabIndex = 11
        Me.ExecutionStatus.TabStop = False
        '
        'buttonStart
        '
        Me.buttonStart.Location = New System.Drawing.Point(332, 85)
        Me.buttonStart.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.buttonStart.Name = "buttonStart"
        Me.buttonStart.Size = New System.Drawing.Size(96, 30)
        Me.buttonStart.TabIndex = 9
        Me.buttonStart.Text = "Start"
        Me.buttonStart.UseVisualStyleBackColor = True
        '
        'pictureBox2
        '
        Me.pictureBox2.Image = CType(resources.GetObject("pictureBox2.Image"), System.Drawing.Image)
        Me.pictureBox2.Location = New System.Drawing.Point(314, 4)
        Me.pictureBox2.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.pictureBox2.Name = "pictureBox2"
        Me.pictureBox2.Size = New System.Drawing.Size(153, 185)
        Me.pictureBox2.TabIndex = 10
        Me.pictureBox2.TabStop = False
        '
        'InstantDiCtrl1
        '
        Me.InstantDiCtrl1._StateStream = CType(resources.GetObject("InstantDiCtrl1._StateStream"), Automation.BDaq.DeviceStateStreamer)
        '
        'listViewForData
        '
        Me.listViewForData.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.IntChannel, Me.PortsData})
        Me.listViewForData.Location = New System.Drawing.Point(14, 28)
        Me.listViewForData.Name = "listViewForData"
        Me.listViewForData.OwnerDraw = True
        Me.listViewForData.Size = New System.Drawing.Size(310, 240)
        Me.listViewForData.TabIndex = 0
        Me.listViewForData.UseCompatibleStateImageBehavior = False
        Me.listViewForData.View = System.Windows.Forms.View.Details
        '
        'IntChannel
        '
        Me.IntChannel.Text = "INT channel"
        Me.IntChannel.Width = 96
        '
        'PortsData
        '
        Me.PortsData.Text = "DI ports value"
        Me.PortsData.Width = 212
        '
        'DIInterruptForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(434, 278)
        Me.Controls.Add(Me.buttonStop)
        Me.Controls.Add(Me.ExecutionStatus)
        Me.Controls.Add(Me.buttonStart)
        Me.Controls.Add(Me.listViewForData)
        Me.Controls.Add(Me.pictureBox2)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "DIInterruptForm"
        Me.Text = "DI Interrupt"
        CType(Me.ExecutionStatus, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.pictureBox2, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
    Private WithEvents columnHeader1 As System.Windows.Forms.ColumnHeader
    Private WithEvents columnHeader2 As System.Windows.Forms.ColumnHeader
    Private WithEvents ColumnHeader3 As System.Windows.Forms.ColumnHeader
    Private WithEvents ColumnHeader4 As System.Windows.Forms.ColumnHeader
    Friend WithEvents listViewForData As MyListView.DoubleBufferListView
    Friend WithEvents IntChannel As System.Windows.Forms.ColumnHeader
    Friend WithEvents PortsData As System.Windows.Forms.ColumnHeader
    Private WithEvents buttonStop As System.Windows.Forms.Button
    Private WithEvents ExecutionStatus As System.Windows.Forms.PictureBox
    Private WithEvents buttonStart As System.Windows.Forms.Button
    Private WithEvents pictureBox2 As System.Windows.Forms.PictureBox
    Friend WithEvents InstantDiCtrl1 As Automation.BDaq.InstantDiCtrl

End Class
