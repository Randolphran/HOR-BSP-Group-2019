package AI_StreamingAI_TDtr;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.BorderFactory;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.ListCellRenderer;
import javax.swing.SwingConstants;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import org.eclipse.wb.swing.FocusTraversalOnArray;


/*
import AI_StreamingAI.StreamingAI.CacheOverFlowEventListener;
import AI_StreamingAI.StreamingAI.DataReadyEventListener;
import AI_StreamingAI.StreamingAI.OverRunEventListener;
*/
import Automation.BDaq.*;
import Common.*;

public class StreamingAI_TDtr extends JFrame {
	// define the serialization number.
	private static final long serialVersionUID = 1L;

	private JPanel contentPane;
	private JLabel label_YCoordinateMax;
	private JLabel label_YCoordinateMid;
	private JLabel label_YCoordinateMin;
	private JLabel label_XCoordinateMin;
	private JLabel label_XCoordinateMax;
	private JSlider sliderDiv;
	private JButton btnConfig;
	private JButton btnStart;
	private JButton btnPause;
	private JButton btnStop;
	private JList listView;
	private DefaultListModel model = new DefaultListModel();

	private SimpleGraph graph;
	ConfigureParameter configure = new ConfigureParameter();
	
	private WaveformAiCtrl wfAiCtrl = new WaveformAiCtrl();
	
	private ConfigureDialog configureDialog;
	private TimeUnit timeUnit = TimeUnit.Millisecond;
	private double[] dataScaled;
	private int rawDataBufferLength = 0;
	private boolean isTriggerSupported = false;
	private boolean isTrigger1Supported = false;
	private double xInc;
	/**
	 * 
	 *Build Date:2012-3-15
	 *Author:Administrator
	 *Function Description: Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					StreamingAI_TDtr frame = new StreamingAI_TDtr();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * 
	 *Build Date:2012-3-15
	 *Author:Administrator
	 *Function Description: Create the frame.
	 */
	public StreamingAI_TDtr() {
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());

		setTitle("Streaming AI with Delay to Start Trigger - Run");
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 766, 543);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);

		// Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("Background.png", "background image!");
		panel.setBounds(0, 0, 760, 511);
		contentPane.add(panel);
		panel.setLayout(null);

		graph = new SimpleGraph();
		graph.setBackground(Color.BLACK);
		graph.setBounds(49, 39, 660, 340);
		graph.size = new Dimension(graph.getSize());
		panel.add(graph);

		label_YCoordinateMax = new JLabel("5V");
		label_YCoordinateMax.setHorizontalAlignment(SwingConstants.RIGHT);
		label_YCoordinateMax.setBounds(0, 39, 46, 15);
		panel.add(label_YCoordinateMax);

		label_YCoordinateMid = new JLabel("0");
		label_YCoordinateMid.setHorizontalAlignment(SwingConstants.RIGHT);
		label_YCoordinateMid.setBounds(0, 200, 46, 15);
		panel.add(label_YCoordinateMid);

		label_YCoordinateMin = new JLabel("-5V");
		label_YCoordinateMin.setHorizontalAlignment(SwingConstants.RIGHT);
		label_YCoordinateMin.setBounds(0, 364, 46, 15);
		panel.add(label_YCoordinateMin);

		label_XCoordinateMin = new JLabel("0Sec");
		label_XCoordinateMin.setHorizontalAlignment(SwingConstants.LEFT);
		label_XCoordinateMin.setBounds(49, 383, 70, 15);
		panel.add(label_XCoordinateMin);

		label_XCoordinateMax = new JLabel("10Sec");
		label_XCoordinateMax.setHorizontalAlignment(SwingConstants.RIGHT);
		label_XCoordinateMax.setBounds(629, 383, 80, 15);
		panel.add(label_XCoordinateMax);

		JLabel lblcolorOfchannels = new JLabel("<html><body>Color of<br>channels:</body><html>");
		lblcolorOfchannels.setHorizontalAlignment(SwingConstants.RIGHT);
		lblcolorOfchannels.setBounds(6, 405, 64, 45);
		panel.add(lblcolorOfchannels);

		listView = new JList();
		listView.setBorder(new LineBorder(new Color(0, 0, 0)));
		listView.setBounds(71, 405, 443, 45);
		listView.setLayoutOrientation(JList.HORIZONTAL_WRAP);
		listView.setDoubleBuffered(true);
		listView.setAlignmentX(Component.RIGHT_ALIGNMENT);
		listView.setFixedCellWidth(55);
		listView.setFixedCellHeight(22);
		panel.add(listView);

		sliderDiv = new JSlider();
		sliderDiv.setValue(200);
		sliderDiv.setMinimum(10);
		sliderDiv.setMaximum(1000);
		sliderDiv.setBackground(SystemColor.control);
		sliderDiv.setBounds(565, 416, 144, 25);
		sliderDiv.addChangeListener(new SliderDivChangeListener());
		panel.add(sliderDiv);

		JLabel lblNewLabel = new JLabel("Div:");
		lblNewLabel.setBounds(535, 420, 30, 15);
		panel.add(lblNewLabel);

		btnConfig = new JButton("Configure");
		btnConfig.addActionListener(new ButtonConfigureActionListener());
		btnConfig.setBounds(268, 468, 115, 23);
		panel.add(btnConfig);

		btnStart = new JButton("Start");
		btnStart.addActionListener(new ButtonStartActionListener());
		btnStart.setBounds(437, 468, 75, 23);
		panel.add(btnStart);

		btnPause = new JButton("Pause");
		btnPause.addActionListener(new ButtonPauseActionListener());
		btnPause.setBounds(537, 468, 75, 23);
		btnPause.setEnabled(false);
		panel.add(btnPause);

		btnStop = new JButton("Stop");
		btnStop.addActionListener(new ButtonStopActionListener());
		btnStop.setBounds(634, 468, 75, 23);
		btnStop.setEnabled(false);
		panel.add(btnStop);
		panel.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[] { sliderDiv,
				btnConfig, btnStart, btnPause, btnStop }));

		// Add the listener to the control.
		
		wfAiCtrl.addCacheOverflowListener(new CacheOverFlowEventListener());
		wfAiCtrl.addOverrunListener(new OverRunEventListener());
		wfAiCtrl.addDataReadyListener(new DataReadyEventListener());

		configureDialog = new ConfigureDialog(this);
		configureDialog.setModal(true);
		configureDialog.setVisible(true);
	}
	/**
	 * 
	 *Build Date:2012-3-15
	 *Author:Administrator
	 *Function Description: Initialize the main frame.
	 */
	public void Initialization(){
		ConfigureDevice();
		ConfigureGraph();
		
		// String array channelValues contents of the current channels' data in each channel.
		String[] channelValues = new String[configure.channelCount];

		this.setTitle("Streaming AI with Delay to Start Trigger - Run(" + configure.deviceName.substring(0, configure.deviceName.length() - 1) + ")");
		
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
		
		btnStart.setEnabled(true);
		btnStop.setEnabled(false);
		btnConfig.setEnabled(true);
		btnPause.setEnabled(false);
		sliderDiv.setEnabled(false);
	}
	
	/**
	 * 
	 *Build Date:2012-3-15
	 *Author:Administrator
	 *Function Description: Configure the Device.
	 */
	protected void ConfigureDevice(){
		try{
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
			wfAiCtrl.getRecord().setSectionCount(0);//0 means Streaming mode;
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
			if(isTriggerSupported){
				wfAiCtrl.getTrigger().setAction(configure.triggerAction);
				wfAiCtrl.getTrigger().setSource(configure.triggerSource);
				wfAiCtrl.getTrigger().setDelayCount(configure.delayCount);
				wfAiCtrl.getTrigger().setLevel(configure.triggerLevel);
				wfAiCtrl.getTrigger().setEdge(configure.triggerEdge);
			}
			
			isTrigger1Supported = (wfAiCtrl.getFeatures().getTriggerCount() > 1) ? true : false;
			if(isTrigger1Supported){
				wfAiCtrl.getTrigger1().setAction(configure.trigger1Action);
				wfAiCtrl.getTrigger1().setSource(configure.trigger1Source);
				wfAiCtrl.getTrigger1().setDelayCount(configure.delayCount1);
				wfAiCtrl.getTrigger1().setLevel(configure.trigger1Level);
				wfAiCtrl.getTrigger1().setEdge(configure.trigger1Edge);
			}
		}catch(Exception ex){
			ShowMessage("Sorry, there're some errors occred: " + ex.getMessage());
		}
		
		ErrorCode errorCode = wfAiCtrl.Prepare();
		if(Global.BioFaild(errorCode)){
			ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
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
	 *Build Date:2012-3-15
	 *Author:Administrator
	 *Function Description: Configure the simple graph.
	 */
	protected void ConfigureGraph(){	
		double clockRate = wfAiCtrl.getConversion().getClockRate();
		
		int unit = 2;
		double timeInterval = 100.0 * graph.size.width / clockRate;
		
		while (clockRate >= 10 * 1000) {
			timeInterval *= 1000;
			clockRate /= 1000;
			unit = unit - 1;
			} 		

		sliderDiv.setMaximum((int)Math.floor(4 * timeInterval));
		sliderDiv.setMinimum((int)Math.ceil(timeInterval / 10));
		sliderDiv.setValue((int)(Math.floor(timeInterval)));

		TimeUnit[] tUnit = {TimeUnit.Nanosecond, TimeUnit.Microsecond, TimeUnit.Millisecond, TimeUnit.Second};
		timeUnit = tUnit[unit];
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

		BDaqApi.AdxGetValueRangeInformation(configure.valueRange.toInt(), description, range, unitIndex);
		Global.GetYCordRange(Yranges, range, Global.toValueUnit(unitIndex.value));

		label_YCoordinateMax.setText(Yranges[2]);
		label_YCoordinateMid.setText(Yranges[1]);
		label_YCoordinateMin.setText(Yranges[0]);
		if(ValueUnit.values()[unitIndex.value] == ValueUnit.Millivolt){
			range.Max /= 1000;
			range.Min /= 1000;
		}
		graph.setyCordRangeMax(range.Max);
		graph.setyCordRangeMin(range.Min);
		graph.Clear();
	}
	
	/**
	 * 
	 *Build Date:2012-3-15
	 *Author:Administrator
	 *Function Description: This function is used to set the X coordinate of the simple graph
	 */
	 private void SetXCord(){
		 graph.setXCordTimeDiv((double)(sliderDiv.getValue()));
		 graph.setxCordTimeOffest(0);
		 String[]X_rangeLabels = new String[2];

		 Global.GetXCordRange(X_rangeLabels, sliderDiv.getValue() * 10, 0, timeUnit);
		 label_XCoordinateMin.setText(X_rangeLabels[0]);
		 label_XCoordinateMax.setText(X_rangeLabels[1]);
	 }

	/**
	 * Build Date:2012-3-15
	 * Author:Administrator
	 * Function Description: if some errors occurred, Show the error code to the users.
	 * 
	 * @param message:the message shown to users!
	 */
	protected void ShowMessage(String message) {
		JOptionPane.showMessageDialog(this, message, "Warning MessageBox",
				JOptionPane.WARNING_MESSAGE);
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the OverRun event in 
	 * 							   streaming buffered AI.
	 */
	class OverRunEventListener implements BfdAiEventListener{
		public void BfdAiEvent(Object sender, BfdAiEventArgs args){
			/**
			 * You can do something you want here! such as the following.
			 *  ShowMessage("Buffered AI over run! ");
			 */
			
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the OverFlow event in 
	 * 							   streaming buffered AI.
	 */
	class CacheOverFlowEventListener implements BfdAiEventListener{
		public void BfdAiEvent(Object sender, BfdAiEventArgs args){
			/**
			 * You can do something you want here! such as the following.
			 * 	ShowMessage("Buffered AI cache over flow! ");
			 */
			
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the DataReady event in 
	 * 							   streaming buffered AI.
	 */
	class DataReadyEventListener implements BfdAiEventListener{
		public void BfdAiEvent(Object sender, BfdAiEventArgs args){
			
			rawDataBufferLength = configure.sectionLength * configure.channelCount;
			rawDataBufferLength = Math.min(rawDataBufferLength, args.Count);
			if (dataScaled == null || dataScaled.length < rawDataBufferLength) {
				dataScaled = new double[rawDataBufferLength];
			}
			
			ErrorCode errorCode = wfAiCtrl.GetData(rawDataBufferLength, dataScaled, 0, null, null, null, null);
			if(Global.BioFaild(errorCode)){
				ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
				return;
			}
			
			graph.Chart(dataScaled, configure.channelCount, rawDataBufferLength / configure.channelCount, xInc);
			
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
	 * Class Function Description: This class is used to listen the Div slider's changing.
	 */
	class SliderDivChangeListener implements ChangeListener{
		@Override
		public void stateChanged(ChangeEvent e) {
			graph.Div(sliderDiv.getValue());
			
			SetXCord();
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the configure button's changing.
	 */
	class ButtonConfigureActionListener implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent arg0){
			ErrorCode errorCode = wfAiCtrl.Stop();
			if (Global.BioFaild(errorCode)) {
				ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
				return;
			}

			btnStart.setEnabled(true);
			btnStop.setEnabled(false);
			btnConfig.setEnabled(true);
			btnPause.setEnabled(false);
			sliderDiv.setEnabled(false);
			
			graph.Clear();
			configureDialog.LoadConfiguration(configure);
			configureDialog.isFirstLoad = false;
			configureDialog.setVisible(true);
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the start button's changing.
	 */
	class ButtonStartActionListener implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent arg0) {
			ErrorCode errorCode = wfAiCtrl.Start();
			if (Global.BioFaild(errorCode)) {
				ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
				return;
			}
			
			xInc = 1.0 / wfAiCtrl.getConversion().getClockRate();
			btnStart.setEnabled(false);
			btnStop.setEnabled(true);
			btnConfig.setEnabled(false);
			btnPause.setEnabled(true);
			sliderDiv.setEnabled(true);
			
			graph.Clear();
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the pause button's changing.
	 */
	class ButtonPauseActionListener implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent arg0){
			ErrorCode errorCode = wfAiCtrl.Stop();
			if(Global.BioFaild(errorCode)){
				ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
				return;
			}
			
			btnStart.setEnabled(true);
			btnStop.setEnabled(true);
			btnConfig.setEnabled(false);
			btnPause.setEnabled(false);
			sliderDiv.setEnabled(true);
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the stop button's changing.
	 */
	class ButtonStopActionListener implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent arg0){
			ErrorCode errorCode = wfAiCtrl.Stop();
			if(errorCode != ErrorCode.Success){
				ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
				return;
			}
			
			btnStart.setEnabled(true);
			btnStop.setEnabled(false);
			btnConfig.setEnabled(true);
			btnPause.setEnabled(false);
			sliderDiv.setEnabled(false);
			
			graph.Clear();
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the main frame's closing event.
	 */
	class WindowCloseActionListener extends WindowAdapter{
		@Override
		public void windowClosing(WindowEvent e) {
			if (wfAiCtrl != null) {
				wfAiCtrl.Stop();
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
	public double clockRatePerChan;
	public int sectionLength;
	public TriggerAction triggerAction;
	public SignalDrop triggerSource;
	public int delayCount;
	public double triggerLevel;
	public ActiveSignal triggerEdge;
	
	public TriggerAction trigger1Action;
	public SignalDrop trigger1Source;
	public int delayCount1;
	public double trigger1Level;
	public ActiveSignal trigger1Edge;
}

