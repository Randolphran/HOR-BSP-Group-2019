package Common;

public class WaveformGenerator {
	public int pointCountPeriod;
	
	public WaveformGenerator(int pointCount){
		pointCountPeriod = pointCount;
	}
	
	public double GetOnePoint(WaveformStyle style, int index, double highLevel, double lowLevel){
		double amplitude = (highLevel - lowLevel) / 2;
		double offset = (highLevel + lowLevel) / 2;
		double data = 0;
		switch (style) {
		case sine:
			data = amplitude * Math.sin(index * 2.0 * Math.PI / pointCountPeriod) + offset;
			break;
		case square:
			if(index < pointCountPeriod / 2){
				data = amplitude * 1.0 + offset;
			}else{
				data = amplitude *(-1.0) + offset;
			}
			break;
		case triangle:
			if(index < pointCountPeriod / 4){
				data = amplitude * (index / (pointCountPeriod / 4.0)) + offset;
			}else if(index < 3 * (pointCountPeriod / 4)){
				data = amplitude * ((2.0 * (pointCountPeriod / 4.0) - index) / (pointCountPeriod / 4.0)) + offset;
			}else{
				data = amplitude * ((index - pointCountPeriod) / (pointCountPeriod / 4.0)) + offset;
			}
			break;
		default:
			break;
		}
		return data;
	}
	
	public void GetOnePeriod(double[] waveformBuffer, WaveformStyle style, double highLevel, double lowLevel){
		for(int i = 0; i < pointCountPeriod; i++){
			waveformBuffer[i] = GetOnePoint(style, i, highLevel, lowLevel);
		}
	}
	
	public void GetMultipleWaveform(double[] waveform, int waveCount, WaveformStyle[] styles, double[] highLevel, double[] lowLevel){
		for(int i = 0; i < pointCountPeriod; i++){
			for(int j = 0; j < waveCount; j++){
				waveform[j + i * waveCount] = GetOnePoint(styles[j], i, highLevel[j], lowLevel[j]);
			}
		}
	}
}