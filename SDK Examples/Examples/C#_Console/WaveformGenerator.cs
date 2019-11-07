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



    enum WaveformStyle { sine, square,triangle};
    class WaveformGenerator
    {
        #region fields
       public uint m_pointPerPeriod;
        #endregion

        #region ctor and dtor
        public WaveformGenerator(uint pointPerPeriod)
        {
            m_pointPerPeriod = pointPerPeriod;
        }
        #endregion

        #region methods

        public double GetOnePoint(WaveformStyle style, int index, Double highLevel, Double lowLevel)
        {
            double amplitude = (highLevel - lowLevel) / 2;
            double offset = (highLevel + lowLevel) / 2;
            double data = 0;
            System.Diagnostics.Debug.Assert(index >= 0 && index <= m_pointPerPeriod);
            switch (style)
            {
            case WaveformStyle.sine:
                data = amplitude * Math.Sin(index * 2.0 * Math.PI / m_pointPerPeriod) + offset;
                break;
            case WaveformStyle.triangle:
                if (index < (m_pointPerPeriod / 4.0))
                {
                    data = amplitude * (index / (m_pointPerPeriod / 4.0)) + offset;
                }
                else if (index < 3 * (m_pointPerPeriod / 4.0))
                {
                    data = amplitude * ((2.0 * (m_pointPerPeriod / 4.0) - index) / (m_pointPerPeriod / 4.0)) + offset;
                }
                else
                {
                    data = amplitude * ((index - m_pointPerPeriod) / (m_pointPerPeriod / 4.0)) + offset;
                }
                break;
            case WaveformStyle.square:
                if ((index >= 0) && (index < (m_pointPerPeriod / 2)))
                {
                    data = amplitude * 1 + offset;
                }
                else
                {
                    data = amplitude * (-1) + offset;
                }
                break;
             default:
                 break;
            }
            return data;
        }

        public void GetOnePeriod(Double[] waveformBuffer,WaveformStyle style, Double highLevel, Double lowLevel)
        {
            for (int i = 0; i < m_pointPerPeriod; i++ )
            {
                waveformBuffer[i] = GetOnePoint(style, i, highLevel, lowLevel);
            }
        }

        public void GetMultipleWaveform(Double[] waveform,int waveCount, WaveformStyle[] styles,Double[] highLevel, Double[] lowLevel)
        {
            for (int i = 0; i < m_pointPerPeriod;i++ )
            {
                for (int j = 0; j < waveCount; j++)
                {
                    waveform[j + i * waveCount] = GetOnePoint(styles[j], i, highLevel[j], lowLevel[j]);
                }
            }
        }
        #endregion
    }

