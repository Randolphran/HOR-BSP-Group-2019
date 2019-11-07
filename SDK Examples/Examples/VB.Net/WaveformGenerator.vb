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
Imports Advantech.BioDaq

Enum WaveformStyle
   sine
   square
   triangle
End Enum

Class WaveformGenerator
#Region "fields"
   Public m_pointPerPeriod As UInteger
#End Region

#Region "ctor and dtor"
   Public Sub New(ByVal pointPerPeriod As UInteger)
      m_pointPerPeriod = pointPerPeriod
   End Sub
#End Region

#Region "methods"

   Public Function GetOnePoint(ByVal style As WaveformStyle, ByVal index As Integer, ByVal highLevel As [Double], ByVal lowLevel As [Double]) As Double
      Dim amplitude As Double = (highLevel - lowLevel) / 2
      Dim offset As Double = (highLevel + lowLevel) / 2
      Dim data As Double = 0
      System.Diagnostics.Debug.Assert(index >= 0 AndAlso index <= m_pointPerPeriod)
      Select Case style
         Case WaveformStyle.sine
            data = amplitude * Math.Sin(index * 2.0 * Math.PI / m_pointPerPeriod) + offset
            Exit Select
         Case WaveformStyle.triangle
            If index < (m_pointPerPeriod / 4.0) Then
               data = amplitude * (index / (m_pointPerPeriod / 4.0)) + offset
            ElseIf index < 3 * (m_pointPerPeriod / 4.0) Then
               data = amplitude * ((2.0 * (m_pointPerPeriod / 4.0) - index) / (m_pointPerPeriod / 4.0)) + offset
            Else
               data = amplitude * ((index - m_pointPerPeriod) / (m_pointPerPeriod / 4.0)) + offset
            End If
            Exit Select
         Case WaveformStyle.square
            If (index >= 0) AndAlso (index < (m_pointPerPeriod \ 2)) Then
               data = amplitude * 1 + offset
            Else
               data = amplitude * (-1) + offset
            End If
            Exit Select
         Case Else
            Exit Select
      End Select
      Return data
   End Function

   Public Sub GetOnePeriod(ByVal waveformBuffer As [Double](), ByVal style As WaveformStyle, ByVal highLevel As [Double], ByVal lowLevel As [Double])
      For i As Integer = 0 To m_pointPerPeriod - 1
         waveformBuffer(i) = GetOnePoint(style, i, highLevel, lowLevel)
      Next
   End Sub

   Public Sub GetMultipleWaveform(ByVal waveform As [Double](), ByVal waveCount As Integer, ByVal styles As WaveformStyle(), ByVal highLevel As [Double](), ByVal lowLevel As [Double]())
      For i As Integer = 0 To m_pointPerPeriod - 1
         For j As Integer = 0 To waveCount - 1
            waveform(j + i * waveCount) = GetOnePoint(styles(j), i, highLevel(j), lowLevel(j))
         Next
      Next
   End Sub
#End Region
End Class

