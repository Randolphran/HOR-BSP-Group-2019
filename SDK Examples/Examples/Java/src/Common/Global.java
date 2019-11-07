package Common;

import java.text.NumberFormat;

import Automation.BDaq.ErrorCode;
import Automation.BDaq.MathInterval;
import Automation.BDaq.ValueUnit;

public final class Global {
	public static ValueUnit toValueUnit(int index){
		for(ValueUnit x : ValueUnit.values())
	      {
	         if (x.toInt() == index)
	         {
	            return x;
	         }
	      }
		return null;
	}
	
	public static void GetXCordRange(String[] ranges, double rangeMax, double rangeMin, TimeUnit unit){
		String[] tUnit = {"ns", "us", "ms", "Sec"};
		int i;
		for(i = unit.toInt(); i < TimeUnit.Second.toInt() && rangeMax > 1000.0; ++i){
			rangeMin /= 1000;
			rangeMax /= 1000;
		}
		NumberFormat format = NumberFormat.getInstance();
		ranges[0] = format.format(rangeMin) + tUnit[i];
		ranges[1] = format.format(rangeMax) + tUnit[i];
	}

	public static void GetYCordRange(String[] ranges, MathInterval range, ValueUnit unit){
		String unitString = new String();
		NumberFormat format = NumberFormat.getInstance();
		ranges[0] = format.format(range.Min);
		ranges[1] = (range.Max == -range.Min) ? "0" : "";
		ranges[2] = format.format(range.Max);
		
		switch(unit){
		case Kilovolt:
			unitString = "KV";
			break;
		case Volt:
			unitString = "V";
			break;
		case Millivolt:
			unitString = "mV";
			break;
		case Microvolt:
			unitString = "uV";
			break;
		case Kiloampere:
			unitString = "KA";
			break;
		case Ampere:
			unitString = "A";
			break;
		case Milliampere:
			unitString = "mA";
			break;
		case Microampere:
			unitString = "uA";
			break;
		case CelsiusUnit:
			unitString = "C";
			break;
		}
		ranges[0] += unitString;
		ranges[2] += unitString;
	}
	
	public static boolean BioFaild(ErrorCode errorCode){
		return (errorCode.compareTo(ErrorCode.ErrorHandleNotValid) >= 0);
	}
}
