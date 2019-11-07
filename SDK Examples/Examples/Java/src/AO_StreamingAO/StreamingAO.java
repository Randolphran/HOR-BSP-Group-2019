package AO_StreamingAO;

import java.awt.Color;
import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFormattedTextField;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.UIManager;
import javax.swing.border.EmptyBorder;

import Automation.BDaq.*;
import Common.*;

import org.eclipse.wb.swing.FocusTraversalOnArray;

import java.awt.Component;
import java.text.NumberFormat;

public class StreamingAO extends JFrame {
	// Define the default serialization number.
	private static final long serialVersionUID = 1L;

	private JPanel contentPane;
	
	private JFormattedTextField txtHighLevelA;
	private JFormattedTextField txtLowLevelA;
	private JFormattedTextField txtHighLevelB;
	private JFormattedTextField txtLowLevelB;
	private JButton btnSineA;
	private JButton btnSquareA;
	private JButton btnTriangleA;
	private JButton btnSineB;
	private JButton btnSquareB;
	private JButton btnTriangleB;
	private JButton btnConfigure;
	private JButton btnStart;
	private JLabel lblChannelA;
	private JLabel lblChannelB;
	private ImageIcon[][] imageIcon = {
			{
				new BackgroundPanel("sine.png","sine").getImageIcon(),
				new BackgroundPanel("square.png","square").getImageIcon(),
				new BackgroundPanel("triangle.png","triangle").getImageIcon()
			},
			{
				new BackgroundPanel("sine_down.png","sine").getImageIcon(),
				new BackgroundPanel("square_down.png","square").getImageIcon(),
				new BackgroundPanel("triangle_down.png","triangle").getImageIcon()
			}
	}; 
	
	private BufferedAoCtrl bufferedAoCtrl = new BufferedAoCtrl();
	private ConfigureDialog configureDialog;
	ConfigureParameter configure = new ConfigureParameter();
	private double[] dataScaled ;
	//decide how many sections in the raw data buffer. 
	final private int sectionsCount = 4;
	//decide how many samples in a section each channel
	private int sectionLengthPerChan = 0;
	private int rawDataBufferLength = 0;
	private WaveformGenerator waveformGenerator;
	
	private double highLevelA = 0;
	private double lowLevelA = 0;
	private double highLevelB = 0;
	private double lowLevelB = 0;
	
	private WaveformStyle waveStyleA; 
	private WaveformStyle waveStyleB;
	
	private int[][] buttonState = {{0, 0, 0},{0, 0, 0}};
	private boolean isChannelAChecked = false;
	private boolean isChannelBChecked = false;

	/**
	 * 
	 * Build Date:2011-9-8 
	 * Author:Administrator
	 * Function Description: Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					StreamingAO frame = new StreamingAO();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * 
	 * Build Date:2011-9-7 
	 * Author:Administrator
	 * Function Description: Create the frame.
	 */
	public StreamingAO() {
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setTitle("Streaming AO - Run");
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 355, 470);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);

		// Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("ao1.png", "background image!");
		panel.setBounds(0, 0, 348, 438);
		contentPane.add(panel);
		panel.setLayout(null);

		txtHighLevelA = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtHighLevelA.setValue(new Double(5));
		txtHighLevelA.setHorizontalAlignment(SwingConstants.RIGHT);
		txtHighLevelA.setBounds(82, 89, 75, 22);
		panel.add(txtHighLevelA);
		txtHighLevelA.setColumns(10);

		txtLowLevelA = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtLowLevelA.setValue(new Double(-5));
		txtLowLevelA.setHorizontalAlignment(SwingConstants.RIGHT);
		txtLowLevelA.setColumns(10);
		txtLowLevelA.setBounds(192, 88, 75, 22);
		panel.add(txtLowLevelA);

		btnSineA = new JButton(imageIcon[0][0]);
		btnSineA.addActionListener(new WaveButtonActionListener());
		btnSineA.setBounds(80, 121, 53, 50);
		panel.add(btnSineA);

		btnSquareA = new JButton(imageIcon[0][1]);
		btnSquareA.addActionListener(new WaveButtonActionListener());
		btnSquareA.setBounds(149, 121, 53, 50);
		panel.add(btnSquareA);

		btnTriangleA = new JButton(imageIcon[0][2]);
		btnTriangleA.addActionListener(new WaveButtonActionListener());
		btnTriangleA.setBounds(216, 121, 53, 50);
		panel.add(btnTriangleA);

		btnSineB = new JButton(imageIcon[0][0]);
		btnSineB.addActionListener(new WaveButtonActionListener());
		btnSineB.setBounds(82, 308, 53, 50);
		panel.add(btnSineB);

		btnSquareB = new JButton(imageIcon[0][1]);
		btnSquareB.addActionListener(new WaveButtonActionListener());
		btnSquareB.setBounds(149, 308, 53, 50);
		panel.add(btnSquareB);

		btnTriangleB = new JButton(imageIcon[0][2]);
		btnTriangleB.addActionListener(new WaveButtonActionListener());
		btnTriangleB.setBounds(214, 308, 53, 50);
		panel.add(btnTriangleB);

		txtHighLevelB = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtHighLevelB.setValue(new Double(5));
		txtHighLevelB.setHorizontalAlignment(SwingConstants.RIGHT);
		txtHighLevelB.setColumns(10);
		txtHighLevelB.setBounds(82, 274, 75, 22);
		panel.add(txtHighLevelB);

		txtLowLevelB = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtLowLevelB.setValue(new Double(-5));
		txtLowLevelB.setHorizontalAlignment(SwingConstants.RIGHT);
		txtLowLevelB.setColumns(10);
		txtLowLevelB.setBounds(192, 274, 75, 22);
		panel.add(txtLowLevelB);

		btnConfigure = new JButton("Configure");
		btnConfigure.setBounds(63, 395, 115, 23);
		btnConfigure.addActionListener(new ConfigureButtonActionListener());
		panel.add(btnConfigure);
		
		lblChannelA = new JLabel("0");
		lblChannelA.setForeground(new Color(188, 143, 143));
		lblChannelA.setFont(UIManager.getFont("InternalFrame.titleFont"));
		lblChannelA.setBounds(230, 33, 26, 15);
		panel.add(lblChannelA);
		
		lblChannelB = new JLabel("1");
		lblChannelB.setForeground(new Color(188, 143, 143));
		lblChannelB.setFont(UIManager.getFont("InternalFrame.titleFont"));
		lblChannelB.setBounds(230, 219, 26, 15);
		panel.add(lblChannelB);
		
		btnStart = new JButton("Start");
		btnStart.setBounds(201, 395, 90, 23);
		btnStart.addActionListener(new StartButtonActionListener());
		panel.add(btnStart);
		panel.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[]{
				txtHighLevelA, txtLowLevelA, btnSineA, btnSquareA, btnTriangleA, 
				txtHighLevelB, txtLowLevelB, btnSineB, btnSquareB, btnTriangleB, 
				btnConfigure, btnStart}));
		
		// Add the event listener to the control.
		bufferedAoCtrl.addDataTransmittedListener(new DataTransmittedEventListener());
		bufferedAoCtrl.addTransitStoppedListener(new TransmittedStoppedEventListener());
		bufferedAoCtrl.addUnderrunListener(new UnderrunEventListener());
		bufferedAoCtrl.addStoppedListener(new StoppedEventListener());	
		
		configureDialog  = new ConfigureDialog(this);
		configureDialog.setModal(true);
		configureDialog.setVisible(true);
	}
	
	/**
	 * 
	 * Build Date:2011-9-8 
	 * Author:Administrator
	 * Function Description: This function is used to configure the device of bufferedAoCtrl.
	 */
	protected void ConfigureDevice() {
		/**
		 *  in order to keep output 'sectionsCount' times in a second, we set 'sampleRatePerChan'
		 *   value to buffer length for each channel and divide buffer for each channel by 'sectionsCount'. 
		 *   users can set 'SectionCount' according to demand.
		 */
		sectionLengthPerChan = (int)(configure.pointCountPerWave / sectionsCount);
		try {
			bufferedAoCtrl.setSelectedDevice(new DeviceInformation(configure.deviceName));
			String profilePath = null;
			profilePath = configureDialog.GetProfilePath();
			ErrorCode errorCode = bufferedAoCtrl.LoadProfile(profilePath);
			if(Global.BioFaild(errorCode)){
				ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
				}
			
			AnalogChannel[] channels = bufferedAoCtrl.getChannels();
			bufferedAoCtrl.getScanChannel().setChannelStart(configure.channelStart);
			bufferedAoCtrl.getScanChannel().setChannelCount(configure.channelCount);
			bufferedAoCtrl.getScanChannel().setSamples(configure.pointCountPerWave);
			bufferedAoCtrl.getScanChannel().setIntervalCount(sectionLengthPerChan);
			bufferedAoCtrl.getConvertClock().setRate(configure.clockRate * configure.pointCountPerWave);
			
			// Set the streaming mode.
			bufferedAoCtrl.setStreaming(true);
			
			for (int i = 0; i < channels.length; i++) {
				channels[i].setValueRange(configure.valueRange);
			}
			
		} catch (Exception e) {
			ShowMessage("Sorry, there're some errors occred: " + e.getMessage());
		}
		
		ErrorCode errorCode = bufferedAoCtrl.Prepare();
		if(Global.BioFaild(errorCode)){
			ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
		}
	}
	
	/**
	 * 
	 *Build Date:2011-9-8
	 *Author:Administrator
	 *Function Description: This function is used to initialize the state of the waveform button.
	 */
	private void InatializeWaveButton(){
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 3; j++){
				if(j == 0){
					buttonState[i][j] = 1;
				}else{
					buttonState[i][j] = 0;
				}			
			}
		}
		
		btnSineA.setIcon(imageIcon[1][0]);
		btnSquareA.setIcon(imageIcon[0][1]);
		btnTriangleA.setIcon(imageIcon[0][2]);
		waveStyleA = WaveformStyle.sine;
		isChannelAChecked = true;
		
		btnSineB.setIcon(imageIcon[1][0]);
		btnSquareB.setIcon(imageIcon[0][1]);
		btnTriangleB.setIcon(imageIcon[0][2]);
		waveStyleB = WaveformStyle.sine;
		isChannelBChecked = true;
	}
	
	/**
	 * 
	 *Build Date:2011-9-8
	 *Author:Administrator
	 *Function Description: This function is used to set the initialized state of the main frame.
	 */
	private void ConfigurePanel(){
		AoFeatures feature = bufferedAoCtrl.getFeatures();
		
		InatializeWaveButton();
		lblChannelA.setText(String.valueOf(configure.channelStart));
		
		if(configure.channelCount == 1){
			lblChannelB.setText("");
			btnSineB.setEnabled(false);
			btnSquareB.setEnabled(false);
			btnTriangleB.setEnabled(false);
			txtHighLevelB.setEnabled(false);
			txtLowLevelB.setEnabled(false);
			isChannelBChecked = false;
		}else{
			int chanNumberB = configure.channelStart + 1;
			if(chanNumberB == feature.getChannelCountMax()){
				chanNumberB = 0;
			}
			lblChannelB.setText(String.valueOf(chanNumberB));
			btnSineB.setEnabled(true);
			btnSquareB.setEnabled(true);
			btnTriangleB.setEnabled(true);
			txtHighLevelB.setEnabled(true);
			txtLowLevelB.setEnabled(true);	
		}
	}
	
	/**
	 * 
	 * Build Date:2011-9-8 
	 * Author:Administrator
	 * Function Description: This function is used to initialize the main frame.
	 */
	public void Initialization(){
		ConfigureDevice();
		//'2 * pointCountPerWave' means we handle two channels in this demo at most. 
		rawDataBufferLength = 2 * configure.pointCountPerWave;
		waveformGenerator = new WaveformGenerator(configure.pointCountPerWave);
		if(dataScaled == null || dataScaled.length < rawDataBufferLength){
			dataScaled = new double[rawDataBufferLength];
		}
		
		this.setTitle("Streaming AO - Run(" + configure.deviceName.substring(0, configure.deviceName.length() - 1) + ")");
		
		ConfigurePanel();
	}
	
	/**
	 * 
	 * Build Date:2011-9-8
	 * Author:Administrator
	 * Function Description: This function is used to show the error massage to user!
	 * 
	 * @param message: the message shown to users!
	 */
	protected void ShowMessage(String message) {
		JOptionPane.showMessageDialog(this, message, "Warning MessageBox",
				JOptionPane.WARNING_MESSAGE);
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the waveform button 's action.
	 */
	class WaveButtonActionListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			JButton source = (JButton)e.getSource();
			if(source == btnSineA){
				if(buttonState[0][0] == 1){
					buttonState[0][0] = 0;
					isChannelAChecked = false;
				}else{
					buttonState[0][0] = 1;
					waveStyleA = WaveformStyle.sine;
					isChannelAChecked = true;
				}
				buttonState[0][1] = 0;
				buttonState[0][2] = 0;
			}else if(source == btnSquareA){
				if(buttonState[0][1] == 1){
					buttonState[0][1] = 0;
					isChannelAChecked = false;
				}else{
					buttonState[0][1] = 1;
					waveStyleA = WaveformStyle.square;
					isChannelAChecked = true;
				}
				buttonState[0][0] = 0;
				buttonState[0][2] = 0;
			}else if(source == btnTriangleA){
				if(buttonState[0][2] == 1){
					buttonState[0][2] = 0;
					isChannelAChecked = false;
				}else{
					buttonState[0][2] = 1;
					waveStyleA = WaveformStyle.triangle;
					isChannelAChecked = true;
				}
				buttonState[0][0] = 0;
				buttonState[0][1] = 0;
			}else if(source == btnSineB){
				if(buttonState[1][0] == 1){
					buttonState[1][0] = 0;
					isChannelBChecked = false;
				}else{
					buttonState[1][0] = 1;
					waveStyleB = WaveformStyle.sine;
					isChannelBChecked = true;
				}
				buttonState[1][1] = 0;
				buttonState[1][2] = 0;
			}else if(source == btnSquareB){
				if(buttonState[1][1] == 1){
					buttonState[1][1] = 0;
					isChannelBChecked = false;
				}else{
					buttonState[1][1] = 1;
					waveStyleB = WaveformStyle.square;
					isChannelBChecked = true;
				}
				buttonState[1][0] = 0;
				buttonState[1][2] = 0;
			}else if(source == btnTriangleB){
				if(buttonState[1][2] == 1){
					buttonState[1][2] = 0;
					isChannelBChecked = false;
				}else{
					buttonState[1][2] = 1;
					waveStyleB = WaveformStyle.triangle;
					isChannelBChecked = true;
				}
				buttonState[1][0] = 0;
				buttonState[1][1] = 0;
			}
			
			if(buttonState[0][0] == 1){
				btnSineA.setIcon(imageIcon[1][0]);
			}else{
				btnSineA.setIcon(imageIcon[0][0]);
			}
			
			if(buttonState[0][1] == 1){
				btnSquareA.setIcon(imageIcon[1][1]);
			}else{
				btnSquareA.setIcon(imageIcon[0][1]);
			}
			
			if(buttonState[0][2] == 1){
				btnTriangleA.setIcon(imageIcon[1][2]);
			}else{
				btnTriangleA.setIcon(imageIcon[0][2]);
			}
			
			if(buttonState[1][0] == 1){
				btnSineB.setIcon(imageIcon[1][0]);
			}else{
				btnSineB.setIcon(imageIcon[0][0]);
			}
			
			if(buttonState[1][1] == 1){
				btnSquareB.setIcon(imageIcon[1][1]);
			}else{
				btnSquareB.setIcon(imageIcon[0][1]);
			}
			
			if(buttonState[1][2] == 1){
				btnTriangleB.setIcon(imageIcon[1][2]);
			}else{
				btnTriangleB.setIcon(imageIcon[0][2]);
			}
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the configure button 's action.
	 */
	class ConfigureButtonActionListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {

			configureDialog.isFirstLoad = false;
			configureDialog.setVisible(true);
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the Start button 's action.
	 */
	class StartButtonActionListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			if(btnStart.getText() == "Start"){
				if (!isChannelAChecked && !isChannelBChecked) {
					ShowMessage("Please select a waveform !");
					return;
				}

				highLevelA = ((Number)txtHighLevelA.getValue()).doubleValue();
				lowLevelA = ((Number)txtLowLevelA.getValue()).doubleValue();
				highLevelB = ((Number)txtHighLevelB.getValue()).doubleValue();
				lowLevelB = ((Number)txtLowLevelB.getValue()).doubleValue();
				
				WaveformStyle[] styles = new WaveformStyle[] { waveStyleA, waveStyleB };
				double[] highLevels = new double[] { highLevelA, highLevelB };
				double[] lowLevels = new double[] { lowLevelA, lowLevelB };
				
				if (configure.channelCount <= 1) {
					if (isChannelAChecked) {
						waveformGenerator.GetOnePeriod(dataScaled, waveStyleA, highLevelA, lowLevelA);
					} else {
						ShowMessage("Please select one waveform style!");
						return;
					}
					
					ErrorCode errorCode = bufferedAoCtrl.SetData(configure.pointCountPerWave,
							dataScaled);
					if (Global.BioFaild(errorCode)) {
						ShowMessage("Sorry, there're some errors occred, ErrorCode: "
								+ errorCode.toString());
						return;
					}

				} else {
					if (isChannelAChecked && !isChannelBChecked) {
						styles[0] = waveStyleA;
						highLevels[1] = 0;
						lowLevels[1] = 0;
					} else if (!isChannelAChecked && isChannelBChecked) {
						styles[1] = waveStyleB;
						highLevels[0] = 0;
						lowLevels[0] = 0;
					} else if (!isChannelAChecked && !isChannelBChecked) {
						highLevels[0] = 0;
						highLevels[1] = 0;
						lowLevels[0] = 0;
						lowLevels[1] = 0;
					}
					waveformGenerator.GetMultipleWaveform(dataScaled, 2, styles, highLevels,
							lowLevels);
					
					ErrorCode errorCode = bufferedAoCtrl.SetData(2 * configure.pointCountPerWave, dataScaled);
					if (Global.BioFaild(errorCode)) {
						ShowMessage("Sorry, there're some errors occred, ErrorCode: "
								+ errorCode.toString());
						return;
					}
				}
				
				ErrorCode errorCode = bufferedAoCtrl.Start();
				if (Global.BioFaild(errorCode)) {
					ShowMessage("Sorry, there're some errors occred, ErrorCode: "
							+ errorCode.toString());
					return;
				}
				
				btnStart.setText("Stop");
				
				txtHighLevelA.setEnabled(false);
				txtLowLevelA.setEnabled(false);
				txtHighLevelB.setEnabled(false);
				txtLowLevelB.setEnabled(false);
				
				btnSineA.setEnabled(false);
				btnSquareA.setEnabled(false);
				btnTriangleA.setEnabled(false);
				btnSineB.setEnabled(false);
				btnSquareB.setEnabled(false);
				btnTriangleB.setEnabled(false);
				
				btnConfigure.setEnabled(false);
			}else{
				ErrorCode errorCode = bufferedAoCtrl.Stop(0);
				if(Global.BioFaild(errorCode)){
					ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
					return;
				}
				
				btnStart.setText("Start");
				
				txtHighLevelA.setEnabled(true);
				txtLowLevelA.setEnabled(true);
				btnSineA.setEnabled(true);
				btnSquareA.setEnabled(true);
				btnTriangleA.setEnabled(true);
				
				if(configure.channelCount > 1){
					txtHighLevelB.setEnabled(true);
					txtLowLevelB.setEnabled(true);
					btnSineB.setEnabled(true);
					btnSquareB.setEnabled(true);
					btnTriangleB.setEnabled(true);
				}
				
				btnConfigure.setEnabled(true);
			}
		
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the data transmit 
	 * 							   stop event in streaming buffered AO scenario.
	 */
	class TransmittedStoppedEventListener implements BfdAoEventListener{
		 public void BfdAoEvent(Object sender, BfdAoEventArgs args){
			 
			 /*
			  * You can do something you want here! such as the following.
			  * ShowMessage("The transmit stopped event has happened!");
			 */
		 }
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the under run 
	 * 							   event in streaming buffered AO scenario
	 */
	class UnderrunEventListener implements BfdAoEventListener{
		 public void BfdAoEvent(Object sender, BfdAoEventArgs args){
			 /*
			  * You can do something you want here! such as the following.
			  * ShowMessage("The under run event has happened!");
			 */
		 }
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the data transmit 
	 * 							   event in streaming buffered AO scenario
	 */
	class DataTransmittedEventListener implements BfdAoEventListener{
		 public void BfdAoEvent(Object sender, BfdAoEventArgs args){
			 /*
			  * You can do something you want here! such as the following.
			  * ShowMessage("The data transmitted event has happened!");
			  * 
			  * if you want to change the data in the buffer which is used to put out,
			  * you must update the buffer in this function. 
			  * otherwise, it will be unsafe to you application!
			 */
		 }
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the buffered AO 
	 * 							   stop event in streaming buffered AO scenario
	 */
	class StoppedEventListener implements BfdAoEventListener{
		 public void BfdAoEvent(Object sender, BfdAoEventArgs args){
			 /*
			  * You can do something you want here! such as the following.
			  * ShowMessage("The stop event has happened!");
			 */
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
			if (bufferedAoCtrl != null) {
				bufferedAoCtrl.Stop(0);
				bufferedAoCtrl.Cleanup();
			}
		}
	}
}

/**
 * 
 * @author Administrator 
 * Class Description: this class is use to transfer parameter to the main frame.
 */
class ConfigureParameter{
	public String deviceName;
	public int channelStart;
	public int channelCount;
	public ValueRange valueRange;
	public int pointCountPerWave;
	public double clockRate;
}
