Imports System.Security
Imports System.Runtime.InteropServices
Imports System.ComponentModel

Namespace MyPerformanceCounter
   Public Class PerformanceCounter
      Public StartTime As Long
      ' start time, in cpu ticks
      Public StopTime As Long
      ' stop time, in cpu ticks
      Public CPUFreq As Long
      ' CPU frequency, ticks per second
      Public Sub New()
         If QueryPerformanceFrequency(CPUFreq) = False Then
            ' high-performance counter not supported
            Throw New Win32Exception()
         End If
      End Sub
      Public Sub Start()
         QueryPerformanceCounter(StartTime)
      End Sub
      Public Sub [Stop]()
         QueryPerformanceCounter(StopTime)
      End Sub
      Public ReadOnly Property Duration() As Double
         ' Returns the duration of the timer (in seconds)
         Get
            Return CDbl(StopTime - StartTime) / CDbl(CPUFreq)
         End Get
      End Property

      <SuppressUnmanagedCodeSecurity()> _
      <DllImport("Kernel32.dll")> _
      Public Shared Function QueryPerformanceFrequency(ByRef freq As Long) As Boolean
      End Function

      <SuppressUnmanagedCodeSecurity()> _
      <DllImport("Kernel32.dll")> _
      Public Shared Function QueryPerformanceCounter(ByRef count As Long) As Boolean
      End Function
   End Class
End Namespace
