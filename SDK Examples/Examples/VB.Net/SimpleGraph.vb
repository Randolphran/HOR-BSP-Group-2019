Imports System
Imports System.Collections
Imports System.IO
Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Drawing.Text
Imports System.Text
Imports System.Windows.Forms
Imports System.Drawing.Drawing2D
Imports Automation.BDaq

Namespace MySimpleGraph
    Enum TimeUnit
		Nanosecond
        Microsecond
        Millisecond
        Second
    End Enum 'TimeUnit
    Enum FrequencyUnit
        Hz
        KHz
        MHz
    End Enum 'FrequencyUnit
   Class SimpleGraph

      Dim m_bitmap As Bitmap
      Dim m_size As Size
      Dim m_control As Control

      Dim m_YCordRangeMin As [Double]
      Dim m_YCordRangeMax As [Double]

      Dim m_xIncByTime As [Double]

      Private m_drawDataBuffer As [Double]()
      Private m_dataPointBuffer As PointF()()

      Dim m_XCordDividedRate As [Double]
      Dim m_XCordTimeDiv As [Double]
      Dim m_XCordTimeOffset As [Double]

      Dim m_shiftCount As Double
      Dim m_plotCount As Integer
      Dim m_dataCountCachePerPlot As Integer
      Dim m_mapDataIndexPerPlot As Integer
      Dim m_pointCountPerScreen As Integer
		Dim m_dataCountPerPlot As Integer

		Dim m_recordEndFlag As Boolean
		Dim m_xPosition As Integer
		Dim m_drawRecordEnd As Boolean
		Dim m_recordEndPointX As Integer

      Dim LockObject As New Object()
      Shared m_pens() As Pen = {System.Drawing.Pens.Red, System.Drawing.Pens.DarkViolet, System.Drawing.Pens.GreenYellow, System.Drawing.Pens.Salmon, System.Drawing.Pens.SkyBlue, System.Drawing.Pens.SteelBlue, System.Drawing.Pens.DarkSeaGreen, System.Drawing.Pens.LightGreen, System.Drawing.Pens.NavajoWhite, System.Drawing.Pens.OrangeRed, System.Drawing.Pens.DeepPink, System.Drawing.Pens.MediumOrchid, System.Drawing.Pens.LightGray, System.Drawing.Pens.MediumVioletRed, System.Drawing.Pens.MistyRose, System.Drawing.Pens.PowderBlue}

      Public Sub New(ByVal bmSize As Size, ByVal control As Control)
         m_control = control
         m_size = bmSize
         m_bitmap = New Bitmap(bmSize.Width, bmSize.Height)
         AddHandler m_control.Paint, AddressOf ControlOnPaint
      End Sub 'New 
      Public Property XCordTimeDiv() As [Double]
         Get
            Return m_XCordTimeDiv
         End Get
         Set(ByVal value As [Double])
            m_XCordTimeDiv = value
            Div(m_XCordTimeDiv)
         End Set
      End Property
      Public Property XCordTimeOffset() As [Double]
         Get
            Return m_XCordTimeOffset
         End Get
         Set(ByVal value As [Double])
            m_XCordTimeOffset = value
            Shift(m_XCordTimeOffset)
         End Set
      End Property
      Public Property YCordRangeMin() As [Double]
         Get
            Return m_YCordRangeMin
         End Get
         Set(ByVal value As [Double])
            m_YCordRangeMin = value
         End Set
      End Property
      Public Property YCordRangeMax() As [Double]
         Get
            Return m_YCordRangeMax
         End Get
         Set(ByVal value As [Double])
            m_YCordRangeMax = value
         End Set
      End Property
      Public ReadOnly Property Pens() As Pen()
         Get
            Return m_pens
         End Get
      End Property
      Public Sub Clear()
         m_plotCount = 0
         m_mapDataIndexPerPlot = 0
         m_pointCountPerScreen = 0
         m_dataCountPerPlot = 0
         m_dataCountCachePerPlot = 0
			m_shiftCount = 0
			m_xPosition = 0
			m_drawRecordEnd = False
         m_control.Invalidate()
      End Sub 'Clear

      Public Sub Shift(ByVal shiftTime As Double)
         m_XCordTimeOffset = shiftTime
         m_mapDataIndexPerPlot = 0
         Draw()
      End Sub 'Shift

		Public Sub Div(ByVal DivValue As Double)
			m_XCordTimeDiv = DivValue
			Draw()
		End Sub	'Div

		Private Sub Draw()
			CalcDrawParams(m_xIncByTime)
			MapDataPoints()
			m_control.Invalidate()
		End Sub	'Draw
		'The function Chart previously is four parameters changing to five parameters now.  
		'The fifth parameter recordEndFlag used to determine whether or not draw a mark line when the returned value being WarningRecordEnd.
		'Meanwhile, the previous version four parameters function is still available. 
		Public Sub Chart(ByVal data() As [Double], ByVal plotCount As Integer, ByVal dataCountPerPlot As Integer, ByVal xIncBySec As Double, Optional ByVal flag As Boolean = False)
			m_recordEndFlag = flag
			m_xIncByTime = xIncBySec
			m_dataCountPerPlot = dataCountPerPlot
			'to be fit for variational for plotCount
			If m_drawDataBuffer Is Nothing Or plotCount <> m_plotCount Then
				m_drawDataBuffer = New Double(plotCount * ((m_size.Width * 4) + 2)) {}
				m_dataPointBuffer = New PointF(plotCount)() {}
				Dim i As Integer
				For i = 0 To plotCount - 1
					m_dataPointBuffer(i) = New PointF(m_size.Width * 4 + 2) {}
				Next i
				m_dataCountCachePerPlot = 0
				m_plotCount = plotCount
			End If
			CalcDrawParams(xIncBySec)
			SaveData(data, m_plotCount, dataCountPerPlot)
			MapDataPoints()
			m_control.Invalidate()
		End Sub 'Chart

		Private Sub CalcDrawParams(ByVal XIncBySec As Double)

			If XIncBySec < Double.Epsilon Then
				Return
			End If

			SyncLock LockObject
				m_shiftCount = Math.Truncate(m_XCordTimeOffset * 1.0 / (XIncBySec * 1000))
				Dim XcoordinateDivBase As [Double] = m_size.Width * XIncBySec * 100.0 'ms

				While XIncBySec * 10 * 1000 <= 1
					m_shiftCount = Math.Truncate(m_shiftCount / 1000)
					XcoordinateDivBase = XcoordinateDivBase * 1000.0
					XIncBySec *= 1000
				End While

				If 0 < m_XCordTimeDiv And 0 < XcoordinateDivBase Then
					m_XCordDividedRate = XcoordinateDivBase / m_XCordTimeDiv
					m_pointCountPerScreen = CInt(Math.Ceiling((m_size.Width * m_XCordTimeDiv / XcoordinateDivBase))) + 1
				End If
			End SyncLock
		End Sub	'CalcDrawParams

      Private Sub SaveData(ByVal data() As [Double], ByVal plotCount As Integer, ByVal dataCountPerPlot As Integer)

			If dataCountPerPlot * m_plotCount > m_drawDataBuffer.Length Then
				m_drawDataBuffer = New [Double]((dataCountPerPlot + 3) * m_plotCount) {}
			End If

			Dim offset As Integer = 0

			If dataCountPerPlot >= m_pointCountPerScreen Then
				m_mapDataIndexPerPlot = (m_dataCountPerPlot - m_pointCountPerScreen - 1)
				Array.Copy(data, 0, m_drawDataBuffer, 0, plotCount * dataCountPerPlot)
				m_dataCountCachePerPlot = dataCountPerPlot
				offset = m_dataCountPerPlot
			Else
				If m_dataCountCachePerPlot + dataCountPerPlot <= m_pointCountPerScreen Then
					Array.Copy(data, 0, m_drawDataBuffer, m_dataCountCachePerPlot * plotCount, plotCount * dataCountPerPlot)
					m_dataCountCachePerPlot += dataCountPerPlot
					offset = 0
				Else
					Dim overflowCount As Integer = plotCount * (m_dataCountCachePerPlot + dataCountPerPlot - m_pointCountPerScreen)
					Array.Copy(m_drawDataBuffer, overflowCount, m_drawDataBuffer, 0, plotCount * m_dataCountCachePerPlot - overflowCount)
					Array.Copy(data, 0, m_drawDataBuffer, plotCount * m_dataCountCachePerPlot - overflowCount, plotCount * dataCountPerPlot)
					m_dataCountCachePerPlot = m_pointCountPerScreen
					offset = m_dataCountCachePerPlot + dataCountPerPlot - m_pointCountPerScreen
				End If
			End If

			Dim xPos As Integer = 0
			xPos = m_dataCountCachePerPlot - m_mapDataIndexPerPlot - 1
			If m_recordEndFlag Then
				m_xPosition = xPos
				m_drawRecordEnd = True
			Else
				m_xPosition -= offset
				m_drawRecordEnd = m_xPosition > 0 And m_xPosition < m_pointCountPerScreen
			End If
		End Sub	'SaveData

		Private Sub MapDataPoints()

			Dim YCordDividedRate As [Double] = 1.0 * (m_size.Height - 1) / (m_YCordRangeMax - m_YCordRangeMin)
			Dim drawPoint As Integer = 0

			If m_dataCountCachePerPlot - m_shiftCount - m_mapDataIndexPerPlot > m_pointCountPerScreen Then
				drawPoint = m_pointCountPerScreen
			Else
				drawPoint = m_dataCountCachePerPlot - m_shiftCount - m_mapDataIndexPerPlot
			End If

			If drawPoint < 1 Then
				Return
			End If

			Dim offset As Integer
			For offset = m_mapDataIndexPerPlot To (m_mapDataIndexPerPlot + drawPoint) - 1
				Dim i As Integer
				For i = 0 To m_plotCount - 1
					m_dataPointBuffer(i)((offset - m_mapDataIndexPerPlot)).Y = CSng(Math.Ceiling((YCordDividedRate * (m_YCordRangeMax - m_drawDataBuffer((m_plotCount * (offset + m_shiftCount) + i))))))
					m_dataPointBuffer(i)((offset - m_mapDataIndexPerPlot)).X = CSng(Math.Round(((offset - m_mapDataIndexPerPlot) * m_XCordDividedRate)))
				Next i
			Next offset

			If m_drawRecordEnd Then
				m_recordEndPointX = Int(m_xPosition * m_XCordDividedRate)
			End If
		End Sub	'MapDataPoints

      Private Sub PaintTo(ByVal g As Graphics)
         g.Clear(Color.Black)
         Dim i As Integer
         For i = 1 To 9
				g.DrawLine(System.Drawing.Pens.DarkGreen, New Point(CInt(1.0 * i * m_size.Width / 10), 0), New Point(CInt(1.0 * i * m_size.Width / 10), m_size.Height))
            g.DrawLine(System.Drawing.Pens.DarkGreen, New Point(0, CInt(1.0 * i * m_size.Height / 10)), New Point(m_size.Width, CInt(1.0 * i * m_size.Height / 10)))
			Next i

			'draw make line
			If m_drawRecordEnd Then
				g.DrawLine(System.Drawing.Pens.Yellow, New Point(m_recordEndPointX, 0), New Point(m_recordEndPointX, m_size.Height))
			End If

			'draw sample data on bitmap.
			If m_dataCountCachePerPlot > 0 Then
				Dim plotPen As Pen
				Dim countDrawnPerPlot As Integer = 0
				If m_dataCountCachePerPlot - m_shiftCount - m_mapDataIndexPerPlot > m_pointCountPerScreen Then
					countDrawnPerPlot = m_pointCountPerScreen
				Else
					countDrawnPerPlot = m_dataCountCachePerPlot - m_shiftCount - m_mapDataIndexPerPlot
				End If
				If 1 > countDrawnPerPlot Then
					Return
				End If
				Dim drawData(countDrawnPerPlot - 1) As PointF
				Dim plotNumber As Integer
				For plotNumber = 0 To m_plotCount - 1
					If plotNumber >= 0 And plotNumber < 16 Then
						plotPen = m_pens(plotNumber)
					Else
						plotPen = System.Drawing.Pens.Black
					End If
					Array.Copy(m_dataPointBuffer(plotNumber), drawData, countDrawnPerPlot)
					If countDrawnPerPlot > 1 Then
						g.DrawLines(plotPen, drawData)
					Else
						g.DrawLine(plotPen, drawData(0), drawData(0))
					End If
				Next plotNumber
			End If
		End Sub	'PaintTo

      Private Sub ControlOnPaint(ByVal sender As Object, ByVal e As PaintEventArgs)
         PaintTo(Graphics.FromImage(m_bitmap))
         e.Graphics.DrawImage(m_bitmap, New Point(0, 0))
      End Sub 'ControlOnPaint
   End Class


    Class Helpers

        Public Shared Sub GetXCordRangeLabels(ByVal ranges() As String, ByVal rangeMax As [Double], ByVal rangeMin As [Double], ByVal unit As TimeUnit)
			Dim tUnit As String() = {"ns", "us", "ms", "Sec"}
            Dim i As Integer = CInt(unit)
			While i < CInt(TimeUnit.Second) And rangeMax > 1000
				rangeMin /= 1000
				rangeMax /= 1000
				i += 1
			End While
            ranges(0) = rangeMax.ToString() + " " + tUnit(i) '
            ranges(1) = rangeMin.ToString() + " " + tUnit(i) '
        End Sub 'GetXCordRangeLabels

        Public Overloads Shared Sub GetYCordRangeLabels(ByVal ranges() As String, ByVal rangeMax As [Double], ByVal rangeMin As [Double], ByVal unit As ValueUnit)
            Dim sUnit As String() = {"kV", "V", "mV", "uV", "KA", "A", "mA", "uA", "C", ""}
            Dim index As Integer = CInt(unit)
            If -1 = index Then 'No unit
                index = sUnit.Length - 1
            End If
            ranges(0) = rangeMax.ToString() + sUnit(index) '
            ranges(1) = rangeMin.ToString() + sUnit(index) '

            If rangeMax = -rangeMin Then
                ranges(2) = " 0"
            Else
                ranges(2) = ""
            End If
        End Sub 'GetYCordRangeLabels

        Public Overloads Shared Sub GetYCordRangeLabels(ByVal ranges() As String, ByVal rangeMax As [Double], ByVal rangeMin As [Double], ByVal unit As FrequencyUnit)

            Dim sUnit As String() = {"Hz", "k", "M", ""}
            Dim index As Integer = CInt(unit)
            If -1 = index Then 'No unit
                index = sUnit.Length - 1
            End If
            ranges(0) = rangeMax.ToString() + sUnit(index) '
            ranges(1) = rangeMin.ToString() + sUnit(index) '
            If rangeMax = -rangeMin Then
                ranges(2) = " 0"
            Else
                ranges(2) = ""
            End If
        End Sub 'GetYCordRangeLabels
    End Class 'Helpers
End Namespace