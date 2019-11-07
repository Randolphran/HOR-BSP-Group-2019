Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms
Imports Automation.BDaq

Imports MyListView

Public Class DIStatusChangeInterruptForm
    Inherits Form
    Protected Delegate Sub UpdateListview(ByVal portNum As Integer, ByVal portData As Byte())
    Dim m_changedNum As Integer = 0

    Public Sub New()
        InitializeComponent()
    End Sub

    Public Sub New(ByVal deviceNumber As Integer)
        InitializeComponent()
        InstantDiCtrl1.SelectedDevice = New DeviceInformation(deviceNumber)
    End Sub

    Private Sub DIStatusChangeInterruptForm_Load(ByVal sender As Object, ByVal e As EventArgs) Handles MyBase.Load
        'The default device of project is demo device, users can choose other devices according to their needs.
        If Not InstantDiCtrl1.Initialized Then
            MessageBox.Show("Please select a device in control property!", "DI_StatusChange")
            Me.Close()
            Return
        End If

      Me.Text = "DI Status Change Interrupt - Run(" + InstantDiCtrl1.SelectedDevice.Description + ")"

        ' change the columnHeader2.Width according the portCount
        Me.PortsData.Text = "DI ports value (Port 0~" + (InstantDiCtrl1.Features.PortCount - 1).ToString + ")"
        If InstantDiCtrl1.Features.PortCount > 10 Then
            PortsData.Width = 211 + 22 * (InstantDiCtrl1.Features.PortCount - 10)
            listViewForData.Height = 240
        Else
            PortsData.Width = 211
            listViewForData.Height = 225
        End If
        buttonStop.Enabled = False
        ExecutionStatus.Enabled = False
    End Sub

    Private Sub InstantDiCtrl1_DiCosIntPortX(ByVal src As Object, ByVal args As DiSnapEventArgs) Handles InstantDiCtrl1.ChangeOfState
        Try
            Me.Invoke(New UpdateListview(AddressOf UpdateListviewMethod), New Object() {args.SrcNum, args.PortData})
        Catch ex As System.Exception
        End Try
    End Sub

    Private Sub listView1_DrawColumnHeader(ByVal sender As Object, ByVal e As DrawListViewColumnHeaderEventArgs) Handles listViewForData.DrawColumnHeader
        e.DrawBackground()
        e.DrawText()
    End Sub

    Private Sub buttonStart_Click(ByVal sender As Object, ByVal e As EventArgs) Handles buttonStart.Click
        Dim err As ErrorCode = ErrorCode.Success

        listViewForData.Items.Clear()
        m_changedNum = 0
        err = InstantDiCtrl1.SnapStart()
        If err <> ErrorCode.Success Then
            HandleError(err)
            Return
        End If

        buttonStop.Enabled = True
        buttonStart.Enabled = False
        ExecutionStatus.Enabled = True
    End Sub

    Private Sub UpdateListviewMethod(ByVal portNum As Integer, ByVal portData As Byte())
        If listViewForData.Items.Count > 10 Then
            listViewForData.Items(0).Remove()
        End If

        listViewForData.Items.Add("")

        ' column 0
        listViewForData.Items(listViewForData.Items.Count - 1).SubItems.Add("")
        listViewForData.Items(listViewForData.Items.Count - 1).SubItems(0).Tag = System.Math.Max(System.Threading.Interlocked.Increment(m_changedNum), m_changedNum - 1)

        ' column 1
        listViewForData.Items(listViewForData.Items.Count - 1).SubItems.Add("")

        Dim valueString As String = Nothing
        For j As Integer = 0 To portData.Length - 1
            valueString += portData(j).ToString("X2")
            If j < portData.Length - 1 Then
                valueString += ", "
            End If
        Next
        listViewForData.Items(listViewForData.Items.Count - 1).SubItems(1).Tag = valueString
    End Sub

    Private Sub buttonStop_Click(ByVal sender As Object, ByVal e As EventArgs) Handles buttonStop.Click
        Dim err As ErrorCode = ErrorCode.Success

        err = InstantDiCtrl1.SnapStop()

        buttonStart.Enabled = True
        buttonStop.Enabled = False
        ExecutionStatus.Enabled = False
    End Sub

    Private Sub listViewForData_DrawSubItem(ByVal sender As Object, ByVal e As DrawListViewSubItemEventArgs) Handles listViewForData.DrawSubItem
        Select Case e.Header.Index
            Case 0
                ' StatusChange number
                e.Graphics.DrawString(e.SubItem.Tag.ToString(), Me.Font, New SolidBrush(Color.Black), New Point(e.Bounds.X + 35, e.Bounds.Y + 5))
                Exit Select
            Case Else
                ' port value
                e.Graphics.DrawString(e.SubItem.Tag.ToString(), Me.Font, New SolidBrush(Color.Black), New Point(e.Bounds.X, e.Bounds.Y + 5))
                Exit Select
        End Select
    End Sub

    Private Sub HandleError(ByVal err As ErrorCode)
        If err <> ErrorCode.Success Then
            MessageBox.Show("Sorry ! Some errors happened, the error code is: " & err.ToString(), "DIStatusChangeInterrupt")
        End If
    End Sub
End Class
