using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

/// <summary>
/// derived from list view to resolve the problem of flicker.
/// </summary>
class DoubleBufferListView : ListView
{
   public DoubleBufferListView()
   {
      SetStyle(ControlStyles.DoubleBuffer | ControlStyles.OptimizedDoubleBuffer | ControlStyles.AllPaintingInWmPaint, true);
      UpdateStyles();
   }
}
