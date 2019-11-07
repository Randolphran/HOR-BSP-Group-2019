using System;
using System.Collections;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Text;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;
using Automation.BDaq;

enum TimeUnit {Nanosecond, Microsecond, Millisecond, Second };
enum FrequencyUnit { Hz, KHz, MHz };
enum OverOneScreenMode { BeginScreen, EndScreen }

class SimpleGraph
{
   #region fields
   Bitmap   m_bitmap;
   Graphics m_graphics;
   Size     m_size;
   Control  m_control;
   
   Double m_YCordRangeMin;
   Double m_YCordRangeMax;

   Double m_xIncByTime;
   Double[] m_drawDataBuffer;
   PointF[][] m_dataPointBuffer;

   Double m_XCordDividedRate;
   Double m_XCordTimeDiv;
   Double m_XCordTimeOffset;

   Double m_shiftCount;

	bool m_recordEndFlag;
   bool m_drawRecordEnd;
   int m_recordEndPointX;
	int m_xPosition;
   public Double ShiftCount
   {
      get { return m_shiftCount; }
      set { m_shiftCount = value; }
   }
   int m_plotCount;
   int m_dataCountCachePerPlot;
   int m_mapDataIndexPerPlot = 0;
   int m_pointCountPerScreen;
   int m_dataCountPerPlot = 0;

   OverOneScreenMode m_overOneScreenMode;
   static Pen[] m_pens = new Pen[]{
      System.Drawing.Pens.Red,        System.Drawing.Pens.DarkViolet,     System.Drawing.Pens.GreenYellow,  System.Drawing.Pens.Salmon,
      System.Drawing.Pens.SkyBlue,    System.Drawing.Pens.SteelBlue,      System.Drawing.Pens.DarkSeaGreen, System.Drawing.Pens.LightGreen,
      System.Drawing.Pens.NavajoWhite,System.Drawing.Pens.OrangeRed,      System.Drawing.Pens.DeepPink,     System.Drawing.Pens.MediumOrchid,
      System.Drawing.Pens.LightGray,  System.Drawing.Pens.MediumVioletRed,System.Drawing.Pens.MistyRose,    System.Drawing.Pens.PowderBlue};
   object LockObject = new object();
#endregion

   #region ctor and dtor
   public SimpleGraph(Size bmSize, Control control)
   {
      m_control = control;
      m_size = bmSize;
      m_bitmap = new Bitmap(bmSize.Width, bmSize.Height);
      m_overOneScreenMode = OverOneScreenMode.BeginScreen;
      m_control.Paint += new PaintEventHandler(ControlOnPaint);
   }

   #endregion

   #region properties
   
   public Double XCordTimeDiv
   {
      get
      {
         return m_XCordTimeDiv;
      }
      set
      {
         m_XCordTimeDiv = value;
         Div(m_XCordTimeDiv);
      }
   }

   public Double XCordTimeOffset
   {
      get
      {
         return m_XCordTimeOffset;
      }
      set
      {
         m_XCordTimeOffset = value;
         Shift(m_XCordTimeOffset);
      }
   }

   public Double YCordRangeMin
   {
      get
      {
         return m_YCordRangeMin;
      }
      set
      {
         m_YCordRangeMin = value;
      }
   }

   public Double YCordRangeMax
   {
      get
      {
         return m_YCordRangeMax;
      }
      set
      {
         m_YCordRangeMax = value;
      }
   }

   public Pen[] Pens
   {
      get
      {
         return m_pens;
      }
   }

   public OverOneScreenMode OverOneScreenMode
   {
      get
      {
         return m_overOneScreenMode;
      }
      set
      {
         m_overOneScreenMode = value;
      }
   }
   #endregion

   #region methods

   public void Clear()
   {
      m_xIncByTime = 0;
      m_plotCount = 0;
      m_mapDataIndexPerPlot = 0;
      m_pointCountPerScreen = 0;
      m_dataCountPerPlot = 0;
      m_dataCountCachePerPlot = 0;
      m_shiftCount = 0;
		m_recordEndFlag = false;
		m_xPosition = 0;
		m_drawRecordEnd = false;
      m_control.Invalidate();
   }

   public void Shift(double shiftTime)
   {
      m_mapDataIndexPerPlot = 0;
      m_XCordTimeOffset = shiftTime;
      Draw();
   }

   public void Div(double DivValue)
   {
      m_XCordTimeDiv = DivValue;
      Draw(); 
   }

   private void Draw()
   {
      CalcDrawParams(m_xIncByTime);
      MapDataPoints();
      m_control.Invalidate();
   }

	public void Chart(Double[] data, int plotCount, int dataCountPerPlot, double xIncBySec)
	{
		 Chart(data, plotCount, dataCountPerPlot, xIncBySec, false);
	}

	//The function Chart previously has four parameters changing to five parameters now.  
	//The fifth parameter recordEndFlag used to determine whether or not draw a mark line when the returned value being WarningRecordEnd.
	//Meanwhile, the previous version four parameters function is still available. 
   public void Chart(Double[] data, int plotCount, int dataCountPerPlot, double xIncBySec, bool recordEndFlag)
   {
		m_recordEndFlag = recordEndFlag;
		m_xIncByTime = xIncBySec;
      m_dataCountPerPlot = dataCountPerPlot;
      //to be fit for variational for plotCount
      if (null == m_drawDataBuffer || plotCount != m_plotCount)
      {
         m_drawDataBuffer = new double[plotCount * (m_size.Width * 4 + 1)];
         m_dataPointBuffer = new PointF[plotCount][];
         for (int i = 0; i < plotCount; i++)
         {
            m_dataPointBuffer[i] = new PointF[m_size.Width * 4 + 1];
         }
         m_dataCountCachePerPlot = 0;
         m_plotCount = plotCount;
      }

      CalcDrawParams(xIncBySec);
      SaveData(data, m_plotCount, dataCountPerPlot);
      MapDataPoints();
      m_control.Invalidate();
   }

   private void CalcDrawParams(double XIncBySec)
   {
      if (XIncBySec < double.Epsilon)
      {
         return;
      }
 
      lock (LockObject)
      {
         m_shiftCount = (int)(m_XCordTimeOffset * 1.0 / (XIncBySec * 1000));
         Double XcoordinateDivBase = m_size.Width * XIncBySec * 100.0;//ms

         while (XIncBySec * 10 * 1000 <= 1)
         {
            m_shiftCount = (int)(m_shiftCount / 1000);
            XcoordinateDivBase = XcoordinateDivBase * 1000.0;
            XIncBySec *= 1000;
         }

         m_XCordDividedRate = XcoordinateDivBase / m_XCordTimeDiv;
         m_pointCountPerScreen = (int)Math.Ceiling(m_size.Width * m_XCordTimeDiv / XcoordinateDivBase) + 1;
      }
   }

   private void SaveData(Double[] data, int plotCount, int dataCountPerPlot)
   {
		if (dataCountPerPlot * m_plotCount > m_drawDataBuffer.Length)
      {
         m_drawDataBuffer = new Double[(dataCountPerPlot + 1) * m_plotCount];
      }

      int offset = 0;

      if (dataCountPerPlot >= m_pointCountPerScreen)
      {
         m_mapDataIndexPerPlot = m_dataCountPerPlot - m_pointCountPerScreen - 1;
         Array.Copy(data, 0, m_drawDataBuffer, 0, plotCount * dataCountPerPlot);
         m_dataCountCachePerPlot = dataCountPerPlot;
         offset = m_dataCountPerPlot;
      }
      else
      {
         if (m_dataCountCachePerPlot + dataCountPerPlot <= m_pointCountPerScreen)
         {
            Array.Copy(data, 0, m_drawDataBuffer, m_dataCountCachePerPlot * plotCount, plotCount * dataCountPerPlot);
            m_dataCountCachePerPlot += dataCountPerPlot;
            offset = 0;
         }
         else
         {
            int overflowCount = plotCount * (m_dataCountCachePerPlot + dataCountPerPlot - m_pointCountPerScreen);
            Array.Copy(m_drawDataBuffer, overflowCount, m_drawDataBuffer, 0, plotCount * m_dataCountCachePerPlot - overflowCount);
            Array.Copy(data, 0, m_drawDataBuffer, plotCount * m_dataCountCachePerPlot - overflowCount, plotCount * dataCountPerPlot);
            m_dataCountCachePerPlot = m_pointCountPerScreen;
            m_mapDataIndexPerPlot = 0;
            offset = m_dataCountCachePerPlot + dataCountPerPlot - m_pointCountPerScreen;
         }
      }

      int xPos = m_dataCountCachePerPlot - m_mapDataIndexPerPlot - 1;
      if (m_recordEndFlag == true)
      {
         m_xPosition = xPos;
         m_drawRecordEnd = true;
      }
      else
      {
         m_xPosition -= offset;
         m_drawRecordEnd = m_xPosition > 0 && m_xPosition < m_pointCountPerScreen;
      }
   }

   private void MapDataPoints( )
   {
		Double YCordDividedRate = 1.0 * (m_size.Height - 1) / (m_YCordRangeMax - m_YCordRangeMin);
      int count = (int)(m_dataCountCachePerPlot - m_shiftCount - m_mapDataIndexPerPlot);
      int drawPoint = count > m_pointCountPerScreen ? m_pointCountPerScreen : count;

      if (drawPoint < 1)
      {
         return;
      }

      for (int index = 0; index < drawPoint; ++index)
      {
         for (int i = 0; i < m_plotCount; i++)
         {
            m_dataPointBuffer[i][index].Y = (float)Math.Ceiling(YCordDividedRate *
               (m_YCordRangeMax - m_drawDataBuffer[(int)(m_plotCount * (index + m_mapDataIndexPerPlot + m_shiftCount) + i)]));
            m_dataPointBuffer[i][index].X = (float)Math.Round((index) * m_XCordDividedRate);
         }
      }

      if (m_drawRecordEnd)
      {
         m_recordEndPointX = (int)(m_xPosition * m_XCordDividedRate);
      }
   }

   private void PaintTo(Graphics g)
   {
      g.Clear(Color.Black);
      for (int i = 1; i < 10; i++)
      {
         g.DrawLine(System.Drawing.Pens.DarkGreen,
            new Point((int)(1.0 * i * m_size.Width / 10), 0),
            new Point((int)(1.0 * i * m_size.Width / 10), (m_size.Height)));
         g.DrawLine(System.Drawing.Pens.DarkGreen,
            new Point(0, (int)(1.0 * i * m_size.Height / 10)),
            new Point(m_size.Width, (int)(1.0 * i * m_size.Height / 10)));
      }

      if (m_drawRecordEnd)
		{
			g.DrawLine(System.Drawing.Pens.Yellow,
            new Point(m_recordEndPointX, 0),
            new Point(m_recordEndPointX, m_size.Height));
		}
    
      //draw sample data on bitmap.
      if (m_dataCountCachePerPlot > 0)
      {
         Pen plotPen ;
         int count = (int)(m_dataCountCachePerPlot - m_shiftCount - m_mapDataIndexPerPlot);
         int countDrawnPerPlot = count > m_pointCountPerScreen ? m_pointCountPerScreen : count;
         if (1 > countDrawnPerPlot)
         {
            return;
         }
         PointF[] drawData = new PointF[countDrawnPerPlot];
         for (int plotNumber = 0; plotNumber < m_plotCount; plotNumber++)
         {
            plotPen = (plotNumber >= 0 && plotNumber < 16) ? m_pens[plotNumber] : System.Drawing.Pens.Black;
            Array.Copy(m_dataPointBuffer[plotNumber],drawData,countDrawnPerPlot);
            if (countDrawnPerPlot > 1)
            {
               g.DrawLines(plotPen, drawData);
            }
            else
            {
               g.DrawLine(plotPen, drawData[0], drawData[0]);
            }
         }
      }
   }

   private void ControlOnPaint(object sender, PaintEventArgs e)
   {
      if (m_graphics == null)
      {
         m_graphics = Graphics.FromImage(m_bitmap);
      }
      PaintTo(m_graphics);

      e.Graphics.DrawImageUnscaled(m_bitmap, new Point(0, 0));
   }
   #endregion
}

static class Helpers
{
   public static void GetXCordRangeLabels(string[]ranges, Double rangeMax, Double rangeMin, TimeUnit unit)
   {
      string[] tUnit = {"ns", "us", "ms","Sec" };
      int i;
      for (i = (int)unit; i < (int)TimeUnit.Second && rangeMax > 1000; ++i)
      {
         rangeMin /= 1000;
         rangeMax /= 1000;
      }
      ranges[0] = rangeMax.ToString() + " " + tUnit[i];
      ranges[1] = rangeMin.ToString() + " " + tUnit[i];
   }

   public static void GetYCordRangeLabels(string[]ranges,Double rangeMax, Double rangeMin, ValueUnit unit)
   {
      string[] sUnit = { "kV", "V", "mV", "uV", "KA", "A" ,"mA" ,"uA" ,"C" ,""};
      int index = (int)unit;
      if (-1 == index)//No unit
      {
         index = sUnit.Length - 1;
      }
      ranges[0] = rangeMax.ToString() + sUnit[index];
      ranges[1] = rangeMin.ToString() + sUnit[index];
      ranges[2] = (rangeMax == -rangeMin) ? "0" : "";
   }

   public static void GetYCordRangeLabels(string[]ranges,Double rangeMax, Double rangeMin, FrequencyUnit unit)
   {
      string[] sUnit = { "Hz", "k", "M", "" };
      int index = (int)unit;
      if (-1 == index)//No unit
      {
         index = sUnit.Length - 1;
      }
      ranges[0] = rangeMax.ToString() + sUnit[index];
      ranges[1] = rangeMin.ToString() + sUnit[index];
      ranges[2] = (rangeMax == -rangeMin) ? "0" : "";
   }
}