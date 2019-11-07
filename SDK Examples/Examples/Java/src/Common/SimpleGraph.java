package Common;

import java.awt.*;
import javax.swing.*;

//import Automation.BDaq.*;

public class SimpleGraph extends JPanel {
	/**
	 * define the serialization number.
	 */
	private static final long serialVersionUID = 1L;

	public Dimension size;

	double[] drawDataBuffer = null;
	Point[][] dataPointBuffer = null;

	double yCordRangeMin = 0.0;
	double yCordRangeMax = 0.0;
	double xIncByTime = 0.0;
	double xCordDividRate = 0.0;
	double xCordTimeDiv = 0.0;
	double xCordTimeOffset = 0.0;

	double shiftCount = 0.0;

	int plotCount = 0;
	int dataCountCachePerPlot = 0;
	int mapDataIndexPerPlot = 0;
	int pointCountPerScreen = 0;
	int dataCountPerPlot = 0;
	
	boolean recordEndFlag = false;
	int xPosition = 0;
	boolean drawRecordEnd = false;
	int recordEndPointX = 0;

	public static Color[] color = {
			new Color(255, 0, 0), new Color(0, 255, 0),
			new Color(185, 99, 188), new Color(255, 0, 255), new Color(0, 255, 255),
			new Color(255, 255, 0), new Color(155, 55, 255), new Color(255, 127, 0),
			new Color(106, 147, 219), new Color(209, 146, 117), new Color(143, 188, 143),
			new Color(245, 182, 204), new Color(40, 193, 164), new Color(165, 228, 64),
			new Color(204, 150, 53), new Color(236, 228, 137) 
	};

	Object lockObject = new Object();

	public double getShiftCount() {
		return shiftCount;
	}

	public void setShiftCount(double value) {
		shiftCount = value;
	}

	public double getXCordTimeDiv() {
		return xCordTimeDiv;
	}

	public void setXCordTimeDiv(double value) {
		xCordTimeDiv = value;
		Div(xCordTimeDiv);
	}

	public double getxCordTimeOffset() {
		return xCordTimeOffset;
	}

	public void setxCordTimeOffest(double value) {
		xCordTimeOffset = value;
		Shift(xCordTimeOffset);
	}

	public double getyCordRangeMin() {
		return yCordRangeMin;
	}

	public void setyCordRangeMin(double value) {
		yCordRangeMin = value;
	}

	public double getyCordRangeMax() {
		return yCordRangeMax;
	}

	public void setyCordRangeMax(double value) {
		yCordRangeMax = value;
	}

	public void Clear() {
		xIncByTime = 0.0;
		plotCount = 0;

		mapDataIndexPerPlot = 0;
		pointCountPerScreen = 0;
		dataCountCachePerPlot = 0;
		dataCountPerPlot = 0;
		drawRecordEnd = false;
		shiftCount = 0;
		xPosition = 0;
		repaint();
	}

	public void Shift(double shiftTime) {
		mapDataIndexPerPlot = 0;
		xCordTimeOffset = shiftTime;
		Draw();
	}

	public void Div(double divValue) {
		xCordTimeDiv = divValue;
		Draw();
	}

	private void Draw() {
		CalcDrawParams(xIncByTime);
		MapDataPoints();
		repaint();
	}
	
	
	public void Chart(double[] data, int PlotCount, int DataCountPerPlot, double xIncBySec) {
		Chart(data, PlotCount, DataCountPerPlot, xIncBySec, false);
	}
	
	//The function Chart previously is four parameters changing to five parameters now.  
	//The fifth parameter recordEndFlag used to determine whether or not draw a mark line when the returned value being WarningRecordEnd.
	//Meanwhile, the previous version four parameters function is still available. 
	public void Chart(double[] data, int PlotCount, int DataCountPerPlot, double xIncBySec, boolean flag) {
		xIncByTime = xIncBySec;
		recordEndFlag = flag;
		dataCountPerPlot = DataCountPerPlot;
		
		if (null == drawDataBuffer || PlotCount != plotCount) {
			drawDataBuffer = new double[PlotCount * (size.width * 4 + 1)];
			dataPointBuffer = new Point[PlotCount][size.width * 4 + 1];
			for (int i = 0; i < PlotCount; i++) {
				for (int j = 0; j < size.width * 4 + 1; j++) {
					dataPointBuffer[i][j] = new Point(0, 0);
				}
			}

			dataCountCachePerPlot = 0;
			plotCount = PlotCount;
		}

		CalcDrawParams(xIncBySec);
		SaveData(data, plotCount, DataCountPerPlot);
		MapDataPoints();
		repaint();
	}

	private void CalcDrawParams(double XIncBySec) {
		if (XIncBySec < 1e-15) {
			return;
		}
		
		synchronized (lockObject) {
			shiftCount = Math.floor(xCordTimeOffset * 1.0 / (XIncBySec * 1000));
			double XcoordinateDivBase = size.width * XIncBySec * 100.0; // ms
			while (XIncBySec * 10 * 1000 <= 1) { 
				shiftCount = Math.floor(shiftCount / 1000);
				XcoordinateDivBase = XcoordinateDivBase * 1000.0;
				XIncBySec = XIncBySec * 1000;
			}
			xCordDividRate = XcoordinateDivBase / xCordTimeDiv;
			pointCountPerScreen = (int) Math.ceil(size.width * xCordTimeDiv / XcoordinateDivBase) + 1;
		}
	}

	private void SaveData(double[] data, int PlotCount, int DataCountPerPlot) {
		if (DataCountPerPlot * plotCount > drawDataBuffer.length) {
			drawDataBuffer = new double[(DataCountPerPlot + 1) * plotCount];
		}
		
		int offset = 0;
		
		if (DataCountPerPlot >= pointCountPerScreen) {
			mapDataIndexPerPlot = (dataCountPerPlot - pointCountPerScreen - 1);
			System.arraycopy(data, 0, drawDataBuffer, 0, PlotCount * DataCountPerPlot);
			dataCountCachePerPlot = DataCountPerPlot;
			offset = dataCountPerPlot;
		} else {
			if (dataCountCachePerPlot + DataCountPerPlot <= pointCountPerScreen) {
				System.arraycopy(data, 0, drawDataBuffer, dataCountCachePerPlot * PlotCount,
						PlotCount * DataCountPerPlot);
				dataCountCachePerPlot += DataCountPerPlot;
				offset = 0;
			} else {
				int overflowCount = PlotCount
						* (dataCountCachePerPlot + DataCountPerPlot - pointCountPerScreen);
				System.arraycopy(drawDataBuffer, overflowCount, drawDataBuffer, 0, PlotCount
						* dataCountCachePerPlot - overflowCount);
				System.arraycopy(data, 0, drawDataBuffer, PlotCount * dataCountCachePerPlot
						- overflowCount, PlotCount * DataCountPerPlot);
				dataCountCachePerPlot = pointCountPerScreen;
				offset = dataCountCachePerPlot + DataCountPerPlot - pointCountPerScreen;
			}
		}
		
		int xPos = dataCountCachePerPlot - mapDataIndexPerPlot - 1;
	      if (recordEndFlag == true)
	      {
	         xPosition = xPos;
	         drawRecordEnd = true;
	      }
	      else
	      {
	         xPosition -= offset;
	         drawRecordEnd = xPosition > 0 && xPosition < pointCountPerScreen;
	      }
	}

	private void MapDataPoints() {
		double YCordDivededRate = 1.0 * (size.height - 1) / (yCordRangeMax - yCordRangeMin);
		int count = (int) (dataCountCachePerPlot - shiftCount - mapDataIndexPerPlot);
		int drawPoint = count > pointCountPerScreen ? pointCountPerScreen : count;
		if (drawPoint < 1) {
			return;
		}		

		for (int offset = mapDataIndexPerPlot; offset < mapDataIndexPerPlot + drawPoint; offset++) {
			for (int i = 0; i < plotCount; i++) {
				dataPointBuffer[i][offset - mapDataIndexPerPlot].y = (int) Math.ceil(YCordDivededRate 
						* (yCordRangeMax - drawDataBuffer[(int) (plotCount* (offset + shiftCount) + i)]));

				dataPointBuffer[i][offset - mapDataIndexPerPlot].x = (int) Math.round((offset 
						- mapDataIndexPerPlot) * xCordDividRate);
			}
		}
		
		if (drawRecordEnd) {
	         recordEndPointX = (int)(xPosition * xCordDividRate);
	      }
	}

	public void paint(Graphics g) {
		super.paint(g);
		g.setColor(Color.green.darker().darker());
		for (int i = 1; i < 10; i++) {
			g.drawLine((int) (1.0 * i * size.width / 10), 0, (int) (1.0 * i * size.width / 10),size.height);
			g.drawLine(0, (int) (1.0 * i * size.height / 10), size.width, (int) (1.0 * i * size.height / 10));
		}

		if (drawRecordEnd == true) {
			g.setColor(Color.YELLOW);
			g.drawLine(recordEndPointX, 0, recordEndPointX, size.height);
		}
		
		if (dataCountCachePerPlot > 0) {
			int count = (int) (dataCountCachePerPlot - shiftCount - mapDataIndexPerPlot);
			int countDrawPerPlot = count > pointCountPerScreen ? pointCountPerScreen : count;
			if (1 > countDrawPerPlot) {
				return;
			}
			Point[] drawData = new Point[countDrawPerPlot];
			for (int plotNumber = 0; plotNumber < plotCount; plotNumber++) {
				g.setColor(SimpleGraph.color[plotNumber]);
				System.arraycopy(dataPointBuffer[plotNumber], 0, drawData, 0, countDrawPerPlot);
				if (countDrawPerPlot > 1) {
					for (int i = 0; i < countDrawPerPlot - 1; i++) {
						g.drawLine(drawData[i].x, drawData[i].y, drawData[i + 1].x, drawData[i + 1].y);
					}
				} else {
					g.drawLine(drawData[0].x, drawData[0].y, drawData[0].x, drawData[0].y);
				}
			}
		}
	}
}
