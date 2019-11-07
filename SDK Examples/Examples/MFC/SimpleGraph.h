#pragma once
#include <stdio.h>
#include "../../Inc/bdaqctrl.h"
using namespace Automation::BDaq;

enum TimeUnit {Nanosecond, Microsecond, Millisecond, Second };
enum FrequencyUnit { Hz, KHz, MHz };
class SimpleGraph : public CStatic
{
	DECLARE_DYNAMIC(SimpleGraph)
public:
	SimpleGraph();
	virtual ~SimpleGraph();
	DECLARE_MESSAGE_MAP()
public:
   DOUBLE       m_XCordTimeDiv;
   DOUBLE       m_XCordTimeOffset;
   DOUBLE       m_YCordRangeMax;
   DOUBLE       m_YCordRangeMin;
   static COLORREF LinesColor[16];
   static void GetXCordRangeLabels(CString * rangeStrs,DOUBLE rangeMax, DOUBLE rangeMin, TimeUnit unit);
   static void GetYCordRangeLabels(CString * rangeStrs,DOUBLE rangeMax, DOUBLE rangeMin, FrequencyUnit unit);
   static void GetYCordRangeLabels(CString * rangeStrs,DOUBLE rangeMax, DOUBLE rangeMin, ValueUnit unit);  
public:
	//The function Chart previously is four parameters changing to five parameters now.  
	//The fifth parameter recordEndFlag used to determine whether or not draw a mark line when the returned value being WarningRecordEnd.
	//Meanwhile, the previous version four parameters function is still available. 
   void Chart(DOUBLE* dataScaled, int channelCount, int dataCountOfPerChan, double xIncBySec, bool recordEndFlag = false);
   void Clear(void);
   void Shift(int shiftTime);
   void Div(int divTime);
   void InitGraph();

private:
	CDC			m_memDc;
	CRect		   m_rect;
	CBitmap		m_bitmap;
	int			m_plotCount;
	int			m_pointCountPerScreen;
	int         m_copyDataCountPerChan;	
	DOUBLE      m_xIncByTime;
	DOUBLE      m_XCordDividedRate;
	DOUBLE*		m_drawDataBuffer;
	POINT*		m_dataPointBuffer;
	DOUBLE      m_shiftCount;
	int         m_drawDataBufferLength;
	int         m_dataCountCachePerPlot;
	int         m_mapDataIndexPerPlot;
	int         m_dataCountPerPlot;
	bool        m_recordEndFlag;
	int	      m_xPosition;
	bool        m_drawRecordEnd;
	int         m_recordEndPointX;
	CRITICAL_SECTION criticalSection;
	void CalcDrawParams(double XIncBySec);
	void MapDataPoints( );
	void SaveData(DOUBLE * data, int plotCount, int dataCountPerPlot);
	void Draw();

protected:
   afx_msg void OnPaint();
};


