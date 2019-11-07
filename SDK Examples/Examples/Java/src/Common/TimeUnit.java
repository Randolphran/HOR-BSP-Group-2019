package Common;

public enum TimeUnit {
	 Nanosecond,
	 Microsecond,
	 Millisecond, 
	 Second;
	 public int toInt(){
		 return this.ordinal();
	 }
}