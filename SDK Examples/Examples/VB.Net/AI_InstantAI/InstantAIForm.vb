Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms

Imports Automation.BDaq
Imports MyListView
Imports MySimpleGraph

Public Class InstantAiForm
   Inherits Form
#Region "fields"

   Private m_simpleGraph As MySimpleGraph.SimpleGraph
   Private m_firstItem As New ListViewItem()
   Private m_secondItem As New ListViewItem()

   Public Const CHANNEL_COUNT_MAX As Integer = 16
   Private m_dataScaled As Double() = New Double(CHANNEL_COUNT_MAX - 1) {}
   Private chanCountSet As Integer = 0


#End Region

   Public Sub New()
      InitializeComponent()
   End Sub

   Public Sub New(ByVal deviceNumber As Integer)
      InitializeComponent()
      InstantAiCtrl1.SelectedDevice = New DeviceInformation(deviceNumber)
   End Sub

   Private Sub InstantAIForm_Load(ByVal sender As Object, ByVal e As EventArgs) Handles MyBase.Load
      'The default device of project is demo device, users can choose other devices according to their needs.
      If Not InstantAiCtrl1.Initialized Then
            MessageBox.Show("Please select a device in control property!", "InstantAI")
         Me.Close()
         Return
      End If

      'set title of the form.
      Me.Text = "Instant AI - Run(" + InstantAiCtrl1.SelectedDevice.Description + ")"

      button_start.Enabled = True
      button_stop.Enabled = False
      button_pause.Enabled = False

      'initialize a graph with a picture box control to draw Ai data. 
      m_simpleGraph = New MySimpleGraph.SimpleGraph(pictureBox.Size, pictureBox)
        'initialize a timer which drive the data acquisition.
      timer_getData.Interval = trackBar.Value

      textBox.[ReadOnly] = True
      textBox.Text = trackBar.Value.ToString()

      'Add combo Box  to select start channel and channel count
      Dim chanCount As Integer
      If InstantAiCtrl1.ChannelCount <= CHANNEL_COUNT_MAX Then
         chanCount = InstantAiCtrl1.ChannelCount
      Else
         chanCount = CHANNEL_COUNT_MAX
      End If

      Dim count As Integer = 0
      For i As Integer = 0 To chanCount - 1
         comboBox_chanStart.Items.Add(i.ToString())
         count = i + 1
         comboBox_chanCount.Items.Add(count.ToString())
      Next

      comboBox_chanStart.SelectedIndex = 0
		comboBox_chanCount.SelectedIndex = 1

      ConfigureGraph()
      InitListView()
   End Sub

    Private Sub ConfigureGraph()
        Dim X_rangeLabels(2) As String
        Helpers.GetXCordRangeLabels(X_rangeLabels, 10, 0, TimeUnit.Second)
        label_XCoordinateMax.Text = X_rangeLabels(0)
        label_XCoordinateMin.Text = X_rangeLabels(1)

        m_simpleGraph.XCordTimeDiv = 1000

        Dim unit As ValueUnit = CType(-1, ValueUnit) ' Don't show unit in the label.
        Dim Y_CordLables(3) As String
        Helpers.GetYCordRangeLabels(Y_CordLables, 10, -10, unit)
        label_YCoordinateMax.Text = Y_CordLables(0)
        label_YCoordinateMin.Text = Y_CordLables(1)
        label_YCoordinateMiddle.Text = Y_CordLables(2)
        m_simpleGraph.YCordRangeMax = 10
        m_simpleGraph.YCordRangeMin = -10

        m_simpleGraph.Clear()
    End Sub

   Private Sub timer_getData_Tick(ByVal sender As Object, ByVal e As EventArgs) Handles timer_getData.Tick
      Dim performanceCounter As New MyPerformanceCounter.PerformanceCounter()
      Dim err As ErrorCode

      performanceCounter.Start()
      err = InstantAiCtrl1.Read(comboBox_chanStart.SelectedIndex, chanCountSet, m_dataScaled)
      If err <> ErrorCode.Success Then
         HandleError(err)
         timer_getData.[Stop]()
        End If
      m_simpleGraph.Chart(m_dataScaled, chanCountSet, 1, 1.0 * trackBar.Value / 1000)
        RefreshListView()

      performanceCounter.[Stop]()
      Dim interval As Integer = CInt(Math.Truncate(trackBar.Value - performanceCounter.Duration * 1000 - 0.5))
      If interval > 1 Then
         timer_getData.Interval = interval
      End If
   End Sub

   Private Sub trackBar_Scroll(ByVal sender As Object, ByVal e As EventArgs) Handles trackBar.Scroll
      m_simpleGraph.clear()
      timer_getData.Interval = trackBar.Value
      textBox.Text = trackBar.Value.ToString()
   End Sub

   Private Sub button_start_Click(ByVal sender As Object, ByVal e As EventArgs) Handles button_start.Click
      timer_getData.Start()
      button_start.Enabled = False
      button_pause.Enabled = True
      button_stop.Enabled = True
   End Sub

   Private Sub button_pause_Click(ByVal sender As Object, ByVal e As EventArgs) Handles button_pause.Click
      timer_getData.[Stop]()
      button_start.Enabled = True
      button_pause.Enabled = False
   End Sub

   Private Sub button_stop_Click(ByVal sender As Object, ByVal e As EventArgs) Handles button_stop.Click
      timer_getData.[Stop]()
      button_start.Enabled = True
      button_stop.Enabled = False
      button_pause.Enabled = False
      Array.Clear(m_dataScaled, 0, chanCountSet)
      m_simpleGraph.clear()
   End Sub

   Private Sub InitListView()
      'control list view ,one grid indicates a channel which specials with color and value.
      ListView.Clear()
      ListView.FullRowSelect = False
      ListView.Width = 578
      ListView.Height = 53
      ListView.View = View.Details
      ' Set the view to show details.
      ListView.HeaderStyle = ColumnHeaderStyle.None
      ListView.GridLines = True
      ' there are 8 columns for every item.
      For i As Integer = 0 To 7
         ListView.Columns.Add("", 71)
      Next

      ' modify the grid's height with image Indirectly.
      Dim imgList As New ImageList()
      imgList.ImageSize = New Size(1, 21)
      'width and height.
      ListView.SmallImageList = imgList
      'use imgList to modify the height of listView grids.
      ' create two ListViewItem objects,so there are 16 grids for listView.
      m_firstItem = New ListViewItem()
      m_firstItem.SubItems.Clear()
      m_firstItem.UseItemStyleForSubItems = False
      m_firstItem.Font = New Font("SimSun", 10)
      m_firstItem.SubItems(0).Text = [String].Format("{0:0.0000}", m_dataScaled(0))
        m_firstItem.SubItems(0).BackColor = m_simpleGraph.Pens(0).Color
      For i As Integer = 1 To 7
         If i < chanCountSet Then
            m_firstItem.SubItems.Add(([String].Format("{0:0.0000}", m_dataScaled(i))), Color.Black, Color.Honeydew, New Font("SimSun", 10))

            m_firstItem.SubItems(i).BackColor = m_simpleGraph.Pens(i).Color
         Else
            m_firstItem.SubItems.Add("")
            m_firstItem.SubItems(i).BackColor = Color.White
         End If
      Next

      m_secondItem = New ListViewItem()
      m_secondItem.SubItems.Clear()
      m_secondItem.Font = New Font("SimSun", 10)
      m_secondItem.UseItemStyleForSubItems = False
      If 8 < chanCountSet Then
         m_secondItem.SubItems(0).Text = [String].Format("{0:0.0000}", m_dataScaled(8))
         m_secondItem.SubItems(0).BackColor = m_simpleGraph.Pens(8).Color
      Else
         m_secondItem.SubItems(0).Text = ""
         m_secondItem.SubItems(0).BackColor = Color.White
      End If
      For i As Integer = 9 To 15
         If i < chanCountSet Then
            m_secondItem.SubItems.Add(([String].Format("{0:0.0000}", m_dataScaled(i))), Color.Black, Color.Honeydew, New Font("SimSun", 10))
            m_secondItem.SubItems(i - 8).BackColor = m_simpleGraph.Pens(i).Color
         Else
            m_secondItem.SubItems.Add("")
            m_secondItem.SubItems(i - 8).BackColor = Color.White
         End If
      Next

      Dim list As ListViewItem() = New ListViewItem() {m_firstItem, m_secondItem}
      ListView.Items.AddRange(list)
   End Sub

   Private Sub RefreshListView()
      For i As Integer = 0 To chanCountSet - 1
         If i < 8 Then
            m_firstItem.SubItems(i).Text = [String].Format("{0:0.0000}", m_dataScaled(i))
         Else
            m_secondItem.SubItems(i Mod 8).Text = [String].Format("{0:0.0000}", m_dataScaled(i))
         End If
      Next
   End Sub

   Private Sub HandleError(ByVal err As ErrorCode)
      If err <> ErrorCode.Success Then
            MessageBox.Show("Sorry ! Some errors happened, the error code is: " & err.ToString(), "InstantAI")
      End If
   End Sub

   Private Sub comboBox_chanCount_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles comboBox_chanCount.SelectedIndexChanged
      chanCountSet = comboBox_chanCount.SelectedIndex + 1
      InitListView()
   End Sub
End Class

Public NotInheritable Class ConstVal
   Private Sub New()
   End Sub
   Public Const Channel_Start As Integer = 0
   Public Const Channel_Count As Integer = 1
End Class

