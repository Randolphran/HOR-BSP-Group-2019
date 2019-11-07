Imports Microsoft.VisualBasic
Imports System.Collections.Generic
Imports System.ComponentModel
Imports System.Data
Imports System.Drawing
Imports System.Text
Imports System.Windows.Forms

Namespace MyListView
   ''' <summary>
   ''' derived from listview and start double buffer to resolve the problem of flicker.
   ''' </summary>
   Public Class DoubleBufferListView
      Inherits ListView
      Public Sub New()
         SetStyle(ControlStyles.DoubleBuffer Or ControlStyles.OptimizedDoubleBuffer Or ControlStyles.AllPaintingInWmPaint, True)
         UpdateStyles()
      End Sub
   End Class
End Namespace
