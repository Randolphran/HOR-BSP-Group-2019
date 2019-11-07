<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class DIPatternMatchInterruptForm
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(DIPatternMatchInterruptForm))
        Me.ExecutionStatus = New System.Windows.Forms.PictureBox
        Me.buttonStart = New System.Windows.Forms.Button
        Me.buttonStop = New System.Windows.Forms.Button
        Me.InstantDiCtrl1 = New Automation.BDaq.InstantDiCtrl(Me.components)
        Me.listViewForData = New MyListView.DoubleBufferListView
        Me.MatchedNo = New System.Windows.Forms.ColumnHeader
        Me.PortsData = New System.Windows.Forms.ColumnHeader
        CType(Me.ExecutionStatus, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'ExecutionStatus
        '
        Me.ExecutionStatus.Image = CType(resources.GetObject("ExecutionStatus.Image"), System.Drawing.Image)
        Me.ExecutionStatus.Location = New System.Drawing.Point(282, 4)
        Me.ExecutionStatus.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.ExecutionStatus.Name = "ExecutionStatus"
        Me.ExecutionStatus.Size = New System.Drawing.Size(20, 20)
        Me.ExecutionStatus.TabIndex = 7
        Me.ExecutionStatus.TabStop = False
        '
        'buttonStart
        '
        Me.buttonStart.Location = New System.Drawing.Point(332, 82)
        Me.buttonStart.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.buttonStart.Name = "buttonStart"
        Me.buttonStart.Size = New System.Drawing.Size(96, 30)
        Me.buttonStart.TabIndex = 9
        Me.buttonStart.Text = "Start"
        Me.buttonStart.UseVisualStyleBackColor = True
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
        'InstantDiCtrl1
        '
        Me.InstantDiCtrl1._StateStream = CType(resources.GetObject("InstantDiCtrl1._StateStream"), Automation.BDaq.DeviceStateStreamer)
        '
        'listViewForData
        '
        Me.listViewForData.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.MatchedNo, Me.PortsData})
        Me.listViewForData.Location = New System.Drawing.Point(14, 26)
        Me.listViewForData.Name = "listViewForData"
        Me.listViewForData.OwnerDraw = True
        Me.listViewForData.Size = New System.Drawing.Size(315, 240)
        Me.listViewForData.TabIndex = 1
        Me.listViewForData.UseCompatibleStateImageBehavior = False
        Me.listViewForData.View = System.Windows.Forms.View.Details
        '
        'MatchedNo
        '
        Me.MatchedNo.Text = "Matched No#"
        Me.MatchedNo.Width = 101
        '
        'PortsData
        '
        Me.PortsData.Text = "DI ports value"
        Me.PortsData.Width = 210
        '
        'DIPatternMatchInterruptForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 15.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackgroundImage = CType(resources.GetObject("$this.BackgroundImage"), System.Drawing.Image)
        Me.ClientSize = New System.Drawing.Size(436, 275)
        Me.Controls.Add(Me.buttonStart)
        Me.Controls.Add(Me.buttonStop)
        Me.Controls.Add(Me.ExecutionStatus)
        Me.Controls.Add(Me.listViewForData)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Margin = New System.Windows.Forms.Padding(3, 4, 3, 4)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "DIPatternMatchInterruptForm"
        Me.Text = "DI Pattern Match Interrupt"
        CType(Me.ExecutionStatus, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents listViewForData As MyListView.DoubleBufferListView
    Friend WithEvents MatchedNo As System.Windows.Forms.ColumnHeader
    Friend WithEvents PortsData As System.Windows.Forms.ColumnHeader
    Private WithEvents ExecutionStatus As System.Windows.Forms.PictureBox
    Private WithEvents buttonStart As System.Windows.Forms.Button
    Private WithEvents buttonStop As System.Windows.Forms.Button
    Friend WithEvents InstantDiCtrl1 As Automation.BDaq.InstantDiCtrl

End Class
