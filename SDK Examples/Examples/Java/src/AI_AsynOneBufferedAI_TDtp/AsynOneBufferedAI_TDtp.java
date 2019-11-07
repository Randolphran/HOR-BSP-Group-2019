package AI_AsynOneBufferedAI_TDtp;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.Point;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.math.BigDecimal;
import java.text.NumberFormat;

import javax.swing.BorderFactory;
import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.ListCellRenderer;
import javax.swing.SwingConstants;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import Automation.BDaq.*;
import Common.*;

public class AsynOneBufferedAI_TDtp extends JFrame {

	// define the serialization number.
	private static final long serialVersionUID = 1L;

	private JPanel contentPane;
	private JLabel label_YCoordinateMax;
	private JLabel label_YCoordinateMid;
	private JLabel label_YCoordinateMin;
	private JLabel label_XCoordinateMin;
	private JLabel label_XCoordinateMax;
	private JLabel lblTriggerLocation;
	private ImageIcon triggerIcon = new BackgroundPanel("trigger.png", "trigger").getImageIcon();
	private JList listView;
	private JTextField txtShift;
	private JLabel lblShift;
	private JSlider sliderShift;
	private JTextField txtDiv;
	private JLabel lblDiv;
	private JSlider sliderDiv;
	private JButton btnConfigure;
	private JButton btnGetData;
	private DefaultListModel model = new DefaultListModel();

	ConfigureParameter configure = new ConfigureParameter();
	private WaveformAiCtrl wfAiCtrl = new WaveformAiCtrl();
	private SimpleGraph graph;
	private ConfigureDialog configureDialog;
	private TimeUnit timeUnit = TimeUnit.Millisecond;
	private double[] dataScaled;
	private int readyDataCount = 0;
	private boolean isTriggerSupported = false;
	private boolean isSourceNone = true;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					AsynOneBufferedAI_TDtp frame = new AsynOneBufferedAI_TDtp();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public AsynOneBufferedAI_TDtp() {
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());

		setTitle("Asynchronous One Buffered AI with Delay to Stop Trigger - Run");
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 766, 547);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);

		// Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("Background.png", "background image!");
		panel.setBounds(0, 0, 760, 515);
		contentPane.add(panel);
		panel.setLayout(null);

		graph = new SimpleGraph();
		graph.setBackground(Color.BLACK);
		graph.setBounds(49, 39, 660, 324);
		graph.size = new Dimension(graph.getSize());
		panel.add(graph);

		label_YCoordinateMax = new JLabel("5V");
		label_YCoordinateMax.setHorizontalAlignment(SwingConstants.RIGHT);
		label_YCoordinateMax.setBounds(0, 39, 46, 15);
		panel.add(label_YCoordinateMax);

		label_YCoordinateMid = new JLabel("0");
		label_YCoordinateMid.setHorizontalAlignment(SwingConstants.RIGHT);
		label_YCoordinateMid.setBounds(0, 190, 46, 15);
		panel.add(label_YCoordinateMid);

		label_YCoordinateMin = new JLabel("-5V");
		label_YCoordinateMin.setHorizontalAlignment(SwingConstants.RIGHT);
		label_YCoordinateMin.setBounds(0, 348, 46, 15);
		panel.add(label_YCoordinateMin);

		label_XCoordinateMin = new JLabel("0Sec");
		label_XCoordinateMin.setHorizontalAlignment(SwingConstants.LEFT);
		label_XCoordinateMin.setBounds(49, 395, 70, 15);
		panel.add(label_XCoordinateMin);

		label_XCoordinateMax = new JLabel("10Sec");
		label_XCoordinateMax.setHorizontalAlignment(SwingConstants.RIGHT);
		label_XCoordinateMax.setBounds(629, 395, 80, 15);
		panel.add(label_XCoordinateMax);

		JLabel lblColorOfChannels = new JLabel("<html><body>Color of<br>channels:</body></html>");
		lblColorOfChannels.setHorizontalAlignment(SwingConstants.LEFT);
		lblColorOfChannels.setBounds(49, 412, 62, 38);
		panel.add(lblColorOfChannels);

		listView = new JList();
		listView.setBorder(new LineBorder(new Color(0, 0, 0)));
		listView.setBounds(110, 415, 475, 38);
		listView.setLayoutOrientation(JList.HORIZONTAL_WRAP);
		listView.setDoubleBuffered(true);
		listView.setAlignmentX(Component.RIGHT_ALIGNMENT);
		listView.setFixedCellWidth(59);
		listView.setFixedCellHeight(19);
		panel.add(listView);

		JLabel label_1 = new JLabel("Shift:");
		label_1.setBounds(49, 466, 46, 15);
		panel.add(label_1);

		txtShift = new JTextField();
		txtShift.setEditable(false);
		txtShift.setText("0");
		txtShift.setHorizontalAlignment(SwingConstants.RIGHT);
		txtShift.setBounds(94, 463, 70, 21);
		panel.add(txtShift);
		txtShift.setColumns(10);

		sliderShift = new JSlider();
		sliderShift.setEnabled(false);
		sliderShift.setBackground(SystemColor.control);
		sliderShift.setBounds(191, 463, 128, 25);
		sliderShift.addChangeListener(new SliderShiftChangeListener());
		panel.add(sliderShift);

		lblShift = new JLabel("ms");
		lblShift.setBounds(168, 466, 22, 15);
		panel.add(lblShift);

		JLabel label_2 = new JLabel("Div:");
		label_2.setBounds(325, 466, 30, 15);
		panel.add(label_2);

		txtDiv = new JTextField();
		txtDiv.setEditable(false);
		txtDiv.setText("200");
		txtDiv.setHorizontalAlignment(SwingConstants.RIGHT);
		txtDiv.setColumns(10);
		txtDiv.setBounds(355, 463, 70, 21);
		panel.add(txtDiv);

		lblDiv = new JLabel("ms");
		lblDiv.setBounds(430, 466, 22, 15);
		panel.add(lblDiv);

		sliderDiv = new JSlider();
		sliderDiv.setEnabled(false);
		sliderDiv.addChangeListener(new SliderDivChangeListener());
		sliderDiv.setBackground(SystemColor.control);
		sliderDiv.setBounds(455, 463, 128, 25);
		panel.add(sliderDiv);

		btnConfigure = new JButton("Configure");
		btnConfigure.addActionListener(new ButtonConfigureActionListener());
		btnConfigure.setBounds(595, 427, 115, 23);
		panel.add(btnConfigure);

		btnGetData = new JButton("Get Data");
		btnGetData.addActionListener(new ButtonGetDataActionListener());
		btnGetData.setBounds(594, 462, 115, 23);
		panel.add(btnGetData);
		
		lblTriggerLocation = new JLabel("0ms", triggerIcon, SwingConstants.LEFT);
		lblTriggerLocation.setBounds(175, 364, 134, 25);
		panel.add(lblTriggerLocation);

		// Add the data stopped event listener to the control.
		//bufferedAiCtrl.addStoppedListener(new StoppedEventListener());
		wfAiCtrl.addStoppedListener(new StoppedEventListener());
		configureDialog = new ConfigureDialog(this);
		configureDialog.setModal(true);
		configureDialog.setVisible(true);
	}

	/**
	 * 
	 * Build Date:2012-3-14 
	 * Author:Administrator 
	 * Function Description:Initialize the main frame.
	 */
	public void Initialization() {
		ConfigureDevice();
		ConfigureGraph();
		
		// String array channelValues contents of the current channels' data in each channel.
		String[] channelValues = new String[configure.channelCount];

		this.setTitle("Asynchronous One Buffered AI with Trigger Delay to Stop- Run(" + configure.deviceName.substring(0, configure.deviceName.length() - 1) + ")");

		model.removeAllElements();
		for (int i = 0; i < channelValues.length; i++) {
			channelValues[i] = "";
			model.addElement(channelValues[i]);
		}
		listView.setModel(model);
		listView.setBorder(new LineBorder(new Color(0, 0, 0)));
		listView.setVisibleRowCount(-1);
		listView.setCellRenderer(new ListViewCellRenderer());
		listView.setVisible(true);
	}

	/**
	 * 
	 * Build Date:2012-3-14 
	 * Author:Administrator 
	 * Function Description: Configure the Device.
	 */
	protected void ConfigureDevice() {
		try {
			wfAiCtrl.setSelectedDevice(new DeviceInformation(configure.deviceName));
			String profilePath = null;
			profilePath = configureDialog.GetProfilePath();
			ErrorCode errorCode = wfAiCtrl.LoadProfile(profilePath);
			if(Global.BioFaild(errorCode)){
				ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
				}
			
			AnalogInputChannel[] channels = wfAiCtrl.getChannels();
			wfAiCtrl.getConversion().setChannelStart(configure.channelStart);
			wfAiCtrl.getConversion().setChannelCount(configure.channelCount);
			wfAiCtrl.getRecord().setSectionLength(configure.sectionLength);
			wfAiCtrl.getRecord().setSectionCount(1);//The nonzero value means 'one buffered' mode;
			wfAiCtrl.getConversion().setClockRate(configure.clockRatePerChan);

			int count = wfAiCtrl.getFeatures().getChannelCountMax();
			int channel = configure.channelStart;
			
			for (int i = 0; i < configure.channelCount; ++i)
		    {
		      if (channel >= count){
		         channel = 0;}
		      if (channels[channel].getSignalType() == AiSignalType.Differential)
		      {
		         if (channel%2 == 1){
		            channel -= 1;}
		         channels[channel%count].setValueRange((ValueRange)(configure.valueRange));
		         channel += 1;
		      }
		      channels[channel%count].setValueRange((ValueRange)(configure.valueRange));
		      channel += 1;
		    }
			
			isTriggerSupported = (wfAiCtrl.getFeatures().getTriggerCount() > 0) ? true : false;
			if(isTriggerSupported && configure.TriggerIndex == 0){
				
		       // close the trigger1,in order to avoid affect trigger0    
				if (wfAiCtrl.getFeatures().getTriggerCount() > 1)
		       {
		    	  wfAiCtrl.getTrigger1().setSource(SignalDrop.SignalNone);
		       }
			 
				wfAiCtrl.getTrigger().setAction(configure.triggerAction);
				wfAiCtrl.getTrigger().setSource(configure.triggerSource);
				wfAiCtrl.getTrigger().setDelayCount((int)configure.delayCount);
				wfAiCtrl.getTrigger().setLevel(configure.triggerLevel);
				wfAiCtrl.getTrigger().setEdge(configure.triggerEdge);
				
				SignalDrop triggerSource = wfAiCtrl.getTrigger().getSource();
				isSourceNone = (triggerSource != SignalDrop.SignalNone)? false : true;
						
			}
					
			if(wfAiCtrl.getFeatures().getTrigger1Supported() && configure.TriggerIndex == 1){
				
				if (wfAiCtrl.getFeatures().getTriggerSupported())
			    {
			    	wfAiCtrl.getTrigger().setSource(SignalDrop.SignalNone);
			    }
				
				wfAiCtrl.getTrigger1().setAction(configure.triggerAction);
				wfAiCtrl.getTrigger1().setSource(configure.triggerSource);
				wfAiCtrl.getTrigger1().setDelayCount((int)configure.delayCount);
				wfAiCtrl.getTrigger1().setLevel(configure.triggerLevel);
				wfAiCtrl.getTrigger1().setEdge(configure.triggerEdge);
				
				SignalDrop triggerSource1 = wfAiCtrl.getTrigger1().getSource();
				isSourceNone = (triggerSource1 != SignalDrop.SignalNone)? false : true;

			}
		} catch (Exception ex) {
			ShowMessage("Sorry, there're some errors occured: " + ex.getMessage());
			return;
		}
		
		ErrorCode errorCode = wfAiCtrl.Prepare();
		if (Global.BioFaild(errorCode)) {
			ShowMessage("Sorry, there're some errors occured, ErrorCode: " + errorCode.toString());
			return;
		} 
		
		/**
		 * the channel start, channel count and clock rate are not always configured follow the value 
		 * users have selected. Such as 'PCI-1714', its channel start cann't be 1,3, channel
		 * count cann't be 3 and clock rate must bigger than 250000.
		 */
		
		int channelStart = wfAiCtrl.getConversion().getChannelStart();
		int channelCount = wfAiCtrl.getConversion().getChannelCount();
		double clockRate = wfAiCtrl.getConversion().getClockRate();
		if (channelStart != configure.channelStart) {
			ShowMessage("Sorry, the channel start is invalid, driver will change it from "
					+ configure.channelStart + " to " + channelStart);
			configure.channelStart = channelStart;
		}

		if(channelCount != configure.channelCount){
			ShowMessage("Sorry, the channel count is invalid, driver will change it from "
					+ configure.channelCount + " to " + channelCount);
			configure.channelCount = channelCount;
		}
		
		if(clockRate != configure.clockRatePerChan){
			configure.clockRatePerChan = clockRate;
		}
	}

	/**
	 * 
	 * Build Date:2012-3-14 
	 * Author:Administrator 
	 * Function Description: Configure the simple graph.
	 */
	protected void ConfigureGraph() {		
		double clockRate = wfAiCtrl.getConversion().getClockRate();
		int unit = 2;
		double timeInterval = 100.0 * graph.size.width / clockRate;
		double shiftMax = 1000.0 * wfAiCtrl.getRecord().getSectionLength() / clockRate;
		
		while (clockRate >= 10 * 1000) {
			timeInterval *= 1000;
			clockRate /= 1000;
			unit = unit - 1;
			shiftMax *= 1000;
			} 		

		sliderDiv.setMaximum((int)(4 * timeInterval));
		sliderDiv.setMinimum((int)Math.ceil(timeInterval / 10));
		sliderDiv.setValue((int)(timeInterval));
		
		sliderShift.setMaximum((int)shiftMax);

		sliderShift.setMinimum(0);
		sliderShift.setValue(0);
		txtShift.setText(String.valueOf(sliderShift.getValue()));

		TimeUnit[] tUnits = {TimeUnit.Nanosecond, TimeUnit.Microsecond, TimeUnit.Millisecond, TimeUnit.Second};
		timeUnit = tUnits[unit];
		
		String[] timeUnit = {"ns", "us", "ms", "Sec"};
		lblShift.setText(timeUnit[unit]);
		lblDiv.setText(timeUnit[unit]);	
		
		SetXCord();

		StringBuffer description = new StringBuffer(BDaqApi.VALUE_RANGE_DESC_MAX_LEN);
		MathInterval range = new MathInterval();
		IntByRef unitIndex = new IntByRef();

		/**
		 * String array Y ranges contents of three elements, They are the
		 * Maximum value of Y coordinate, the Middle value of Y coordinate and
		 * the Minimum value of Y coordinate!
		 */
		String[] Yranges = new String[3];

		BDaqApi.AdxGetValueRangeInformation(configure.valueRange.toInt(), description, range,
				unitIndex);
		Global.GetYCordRange(Yranges, range, Global.toValueUnit(unitIndex.value));

		label_YCoordinateMax.setText(Yranges[2]);
		label_YCoordinateMid.setText(Yranges[1]);
		label_YCoordinateMin.setText(Yranges[0]);
		if (ValueUnit.values()[unitIndex.value] == ValueUnit.Millivolt) {
			range.Max /= 1000;
			range.Min /= 1000;
		}

		graph.setyCordRangeMax(range.Max);
		graph.setyCordRangeMin(range.Min);
		graph.Clear();
		
		// Set the initialize location of trigger time flag. 
		if(isTriggerSupported && !isSourceNone){
			lblTriggerLocation.setVisible(true);
			lblTriggerLocation.setText("0ms Triggered");
			lblTriggerLocation.setLocation(new Point(graph.getLocation().x, graph.getLocation().y + graph.getHeight()));
		}else{
			lblTriggerLocation.setVisible(false);
		}
	}
	
	/**
	 * 
	 * Build Date:2012-3-14 
	 * Author:Administrator 
	 * Function Description: Configure the simple graph.
	 */
	protected void ConfigureGraph(int samplesCountPerChan) {		
		double clockRate = wfAiCtrl.getConversion().getClockRate();
		int unit = 2;
		double timeInterval = 100.0 * graph.size.width / clockRate;
		double shiftMax = 1000.0 * samplesCountPerChan / clockRate;
		
		while (clockRate >= 10 * 1000) {
			timeInterval *= 1000;
			clockRate /= 1000;
			unit = unit - 1;
			shiftMax *= 1000;
			} 		

		sliderDiv.setMaximum((int)(4 * timeInterval));
		sliderDiv.setMinimum((int)Math.ceil(timeInterval / 10));
		sliderDiv.setValue((int)(timeInterval));
		
		sliderShift.setMaximum((int)shiftMax);
		sliderShift.setMinimum(0);
		sliderShift.setValue(0);
		txtShift.setText(String.valueOf(sliderShift.getValue()));

		TimeUnit[] tUnits = {TimeUnit.Nanosecond, TimeUnit.Microsecond, TimeUnit.Millisecond, TimeUnit.Second};
		timeUnit = tUnits[unit];
		
		String[] timeUnit = {"ns", "us", "ms", "Sec"};
		lblShift.setText(timeUnit[unit]);
		lblDiv.setText(timeUnit[unit]);	
		SetXCord();

		StringBuffer description = new StringBuffer(BDaqApi.VALUE_RANGE_DESC_MAX_LEN);
		MathInterval range = new MathInterval();
		IntByRef unitIndex = new IntByRef();

		/**
		 * String array Y ranges contents of three elements, They are the
		 * Maximum value of Y coordinate, the Middle value of Y coordinate and
		 * the Minimum value of Y coordinate!
		 */
		String[] Yranges = new String[3];

		BDaqApi.AdxGetValueRangeInformation(configure.valueRange.toInt(), description, range,
				unitIndex);
		Global.GetYCordRange(Yranges, range, Global.toValueUnit(unitIndex.value));

		label_YCoordinateMax.setText(Yranges[2]);
		label_YCoordinateMid.setText(Yranges[1]);
		label_YCoordinateMin.setText(Yranges[0]);
		if (ValueUnit.values()[unitIndex.value] == ValueUnit.Millivolt) {
			range.Max /= 1000;
			range.Min /= 1000;
		}

		graph.setyCordRangeMax(range.Max);
		graph.setyCordRangeMin(range.Min);
		graph.Clear();
		
		// Set the initialize location of trigger time flag. 
		if(isTriggerSupported && !isSourceNone){
			lblTriggerLocation.setVisible(true);
			lblTriggerLocation.setText("0ms Triggered");
			lblTriggerLocation.setLocation(new Point(graph.getLocation().x, graph.getLocation().y + graph.getHeight()));
		}else{
			lblTriggerLocation.setVisible(false);
		}
	}

	/**
	 * 
	 *Build Date:2012-3-20
	 *Author:Administrator
	 *Function Description: this function is used to set the location of the trigger. 
	 * @param delayCount: the trigger's delay count.
	 */
	private void SetTriggerPointFlagProperty(int delayCount){
		Point flagInitialLocation = new Point(graph.getLocation().x, graph.getLocation().y + graph.getHeight());
		
		int relativeWidth = GetArrowXCordLocation(readyDataCount, delayCount, graph.getWidth());
		if(relativeWidth < 0){
			lblTriggerLocation.setVisible(false);
		}else{
			lblTriggerLocation.setVisible(true);
			lblTriggerLocation.setLocation(new Point(flagInitialLocation.x + relativeWidth, flagInitialLocation.y));
		}
	}
	
	/**
	 * 
	 *Build Date:2012-3-20
	 *Author:Administrator
	 *Function Description: this function is used to get the location of the delay to stop trigger.
	 * @param delayCount: trigger's delay count.
	 * @param pixelCount: the width of the sample graph.
	 * @return: the relative pixel width of the trigger.
	 */
	private int GetArrowXCordLocation(int dataCount, int delayCount, int pixelCount){
		int relativePixelWidth = 0;
		double rate = wfAiCtrl.getConversion().getClockRate();
		double shift = sliderShift.getValue();
		double divide = sliderDiv.getValue();
		int samplesPerChan = dataCount / wfAiCtrl.getConversion().getChannelCount();
		String unit = "ms";
		double triggerTime = 0;
		double timerFactor = 1000;
		
		if(rate >= 1000 * 1000){
			unit = "us";
			timerFactor = 1000 * 1000;
		}
		triggerTime = timerFactor * (samplesPerChan - delayCount) / rate;
		if(triggerTime > 1000 && unit == "us"){
			triggerTime /= 1000;
			unit = "ms";
		}
		if(triggerTime < 1 && unit == "ms"){
			triggerTime *= 1000;
			unit = "us";
		}
		NumberFormat format = NumberFormat.getInstance();
		String str = format.format(triggerTime);
		lblTriggerLocation.setText(str + unit + " Triggered");
		
		if(rate >= 1000 * 10){
			rate /= 1000;
		}
		int screenCount = (int)(divide * 10 * rate / 1000);
		int shiftCount = (int)(shift * rate / 1000);
		
		if(samplesPerChan - delayCount - shiftCount > 0 &&
				samplesPerChan - delayCount - shiftCount < screenCount){
			relativePixelWidth = pixelCount *  (samplesPerChan - delayCount - shiftCount) / screenCount;
		}else{
			relativePixelWidth = -1;
		}
		
		return relativePixelWidth;
	}
	
	/**
	 * 
	 * Build Date:2012-3-14 
	 * Author:Administrator 
	 * Function Description: This function is used to set the X coordinate of the simple graph
	 */
 	private void SetXCord() {
		graph.setXCordTimeDiv((double) (sliderDiv.getValue()));
		graph.setxCordTimeOffest((double) (sliderShift.getValue()));
		String[] X_rangeLabels = new String[2];
		double shiftMaxValue = round(graph.getXCordTimeDiv() * 10 + sliderShift.getValue(), 3,
				BigDecimal.ROUND_HALF_UP);
		Global.GetXCordRange(X_rangeLabels, shiftMaxValue, sliderShift.getValue(), timeUnit);
		label_XCoordinateMin.setText(X_rangeLabels[0]);
		label_XCoordinateMax.setText(X_rangeLabels[1]);
	}

	/**
	 * Build Date:2012-3-14 
	 * Author:Administrator 
	 * Function Description: This function is used to round a double value in 'scale' precision!
	 * 
	 * @param value
	 *            : The double data
	 * @param scale
	 *            : Precision number
	 * @param roundingMode
	 *            : Rounding mode
	 * @return: the return value
	 */
	private double round(double value, int scale, int roundingMode) {
		BigDecimal bd = new BigDecimal(value);
		bd = bd.setScale(scale, roundingMode);
		double d = bd.doubleValue();
		bd = null;
		return d;
	}

	/**
	 * Build Date:2012-3-14
	 * Author:Administrator 
	 * Function Description: if some errors occurred, Show the error code to the users.
	 * 
	 * @param message
	 *            :the message shown to users!
	 */
	protected void ShowMessage(String message) {
		JOptionPane.showMessageDialog(this, message, "Warning MessageBox",
				JOptionPane.WARNING_MESSAGE);
	}

	/**
	 * 
	 * @author Administrator 
	 * Class Function Description: This class is used to listen the shift slider's changing.
	 */
	class SliderShiftChangeListener implements ChangeListener {
		@Override
		public void stateChanged(ChangeEvent arg0) {
			txtShift.setText(String.valueOf(sliderShift.getValue()));
			graph.Shift(sliderShift.getValue());

			SetXCord();
			
			if(isTriggerSupported && !isSourceNone){
				int delayCount = 0;
				if(configure.TriggerIndex == 0){
					
					delayCount = wfAiCtrl.getTrigger().getDelayCount();
				}else if(configure.TriggerIndex == 1){
	
					delayCount = wfAiCtrl.getTrigger1().getDelayCount();
				}
				SetTriggerPointFlagProperty(delayCount);
			}
		}
	}

	/**
	 * 
	 * @author Administrator 
	 * Class Function Description: This class is used to listen the Div slider's changing
	 */
	class SliderDivChangeListener implements ChangeListener {
		@Override
		public void stateChanged(ChangeEvent e) {

			txtDiv.setText(String.valueOf(sliderDiv.getValue()));
			graph.Div(sliderDiv.getValue());

			SetXCord();
			
			if(isTriggerSupported && !isSourceNone){
				int delayCount = 0;
				if(configure.TriggerIndex == 0){
					delayCount = wfAiCtrl.getTrigger().getDelayCount();
				}else if(configure.TriggerIndex == 1){
					delayCount = wfAiCtrl.getTrigger1().getDelayCount();
				}
				SetTriggerPointFlagProperty(delayCount);
			}
		}
	}

	/**
	 * 
	 * @author Administrator 
	 * Class Function Description: This class is used to listen the configure button's action
	 */
	class ButtonConfigureActionListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent arg0) {
			graph.Clear();
			configureDialog.LoadConfiguration(configure);
			configureDialog.isFirstLoad = false;
			configureDialog.setVisible(true);
		}
	}

	/**
	 * 
	 * @author Administrator 
	 * Class Function Description: This class is used to listen the get data button's action.
	 */
	class ButtonGetDataActionListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			btnConfigure.setEnabled(false);
			btnGetData.setEnabled(false);
			sliderShift.setEnabled(true);
			sliderDiv.setEnabled(true);
			
			ErrorCode errorCode = wfAiCtrl.Start();
			if (Global.BioFaild(errorCode)) {
				ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
				return;
			}
			
			graph.Clear();
		}
	}

	/**
	 * 
	 * @author Administrator 
	 * Class Function Description: This class is used to get data in an asynchronous.
	 */
	class StoppedEventListener implements BfdAiEventListener {
		public void BfdAiEvent(Object sender, BfdAiEventArgs args) {
			/**
			 * 'channelCount * dataCountPerChan' tell driver how many samples the APP's scaled data 
			 * buffer and driver allocate memory for raw data.
			 */
			int rawDataBufferLength = configure.channelCount * configure.sectionLength;
			rawDataBufferLength = Math.min(rawDataBufferLength, args.Count);
			if (dataScaled == null || dataScaled.length < rawDataBufferLength) {
				dataScaled = new double[rawDataBufferLength];
			}

			if(wfAiCtrl.getState() == ControlState.Idle){
				return;
			}
			graph.Clear();
			
			ErrorCode errorCode = wfAiCtrl.GetData(rawDataBufferLength, dataScaled, 0, null, null, null, null);
			if (Global.BioFaild(errorCode)) {
				ShowMessage("Sorry, there're some errors occred, ErrorCode: "
						+ errorCode.toString());
				return;
			}
			
			ConfigureGraph(rawDataBufferLength / configure.channelCount);

			graph.Chart(dataScaled, configure.channelCount, rawDataBufferLength / configure.channelCount,
					1.0 / configure.clockRatePerChan);
			
			if(isTriggerSupported && !isSourceNone){
				lblTriggerLocation.setLocation(new Point(graph.getLocation().x,
						graph.getLocation().y + graph.getHeight()));
				
				// readyDataCount stands for the data count that driver has readied for us.
				readyDataCount = rawDataBufferLength;
				int delayCount = 0;
				if(configure.TriggerIndex == 0){
					delayCount = wfAiCtrl.getTrigger().getDelayCount();
				}else if(configure.TriggerIndex == 1){
					delayCount = wfAiCtrl.getTrigger1().getDelayCount();
				}
				
				SetTriggerPointFlagProperty(delayCount);
			}
			
			btnConfigure.setEnabled(true);
			btnGetData.setEnabled(true);
		}
	}

	/**
	 * 
	 * @author Administrator 
	 * Class Function Description: this class is use to draw each cell of the JList object.
	 */
	class ListViewCellRenderer extends JLabel implements ListCellRenderer {
		/**
		 * define the serialization number.
		 */
		private static final long serialVersionUID = 1L;

		public Component getListCellRendererComponent(JList list, Object value, int index,
				boolean isSelected, boolean cellHasFocus) {

			if (value != null) {
				String text = value.toString();
				setText(text);
				Border etch = BorderFactory.createEtchedBorder();
				this.setBorder(BorderFactory.createTitledBorder(etch));

				setHorizontalAlignment(SwingConstants.RIGHT);
				setOpaque(true);
				setBackground(SimpleGraph.color[index]);
			}
			return this;
		}
	}
	
	/**
	 * 
	 * @author Administrator 
	 * Class Function Description: This class is used to listen the main frame's closing event.
	 */
	class WindowCloseActionListener extends WindowAdapter {
		@Override
		public void windowClosing(WindowEvent e) {
			if (wfAiCtrl != null) {
				wfAiCtrl.Cleanup();
			}
		}
	}
}

/**
 * 
 * @author Administrator 
 * Class Description: this class is use to transfer parameter to the main frame dialog.
 */
class ConfigureParameter {
	public String deviceName;
	public int channelStart;
	public int channelCount;
	public ValueRange valueRange;
	public int sectionLength;
	public double clockRatePerChan;
	public TriggerAction triggerAction;
	public SignalDrop triggerSource;
	public long delayCount;
	public double triggerLevel;
	public ActiveSignal triggerEdge;
	
	public int TriggerIndex;
}