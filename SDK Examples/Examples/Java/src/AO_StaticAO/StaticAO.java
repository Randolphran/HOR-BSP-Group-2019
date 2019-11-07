package AO_StaticAO;

import java.awt.*;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.text.NumberFormat;

import Automation.BDaq.*;
import Common.*;

import org.eclipse.wb.swing.FocusTraversalOnArray;

public class StaticAO extends JFrame implements ActionListener{

	/**
	 * define the serialization number.
	 */
	private static final long serialVersionUID = 1L;
	
	private JPanel contentPane;
	private JFormattedTextField txtHighLevelA;
	private JFormattedTextField txtLowLevelA;
	private JFormattedTextField txtValueA;
	private JFormattedTextField txtHighLevelB;
	private JFormattedTextField txtLowLevelB;
	private JFormattedTextField txtValueB;
	private JButton btnSineA;
	private JButton btnSquareA;
	private JButton btnTriangleA;
	private JButton btnManualA;
	private JButton btnSineB;
	private JButton btnSquareB;
	private JButton btnTriangleB;
	private JButton btnManualB;
	private JSlider sliderTime;
	private JLabel lblTime;
	private JButton btnConfigure;
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
	
	private InstantAoCtrl instantAoCtrl = new InstantAoCtrl();
	private ConfigureDialog configureDialog;
	ConfigureParameter configure = new ConfigureParameter();
	private double[] dataScaled = new double[2];  //we handle two channels in this demo at most.
	private WaveformGenerator waveformGenerator;
	
	private double highLevelA = 0;
	private double lowLevelA = 0;
	private double highLevelB = 0;
	private double lowLevelB = 0;
	
	private WaveformStyle waveStyleA; 
	private int pointIndexA = 0;
	private WaveformStyle waveStyleB;
	private int pointIndexB = 0;
	
	private int[][] buttonState = {{0, 0, 0},{0, 0, 0}};
	private boolean isChannelAChecked = false;
	private boolean isChannelBChecked = false;
	
	private Timer timer;
	
	/**
	*
	* Build Date:2011-9-1 
	* Author:Administrator
	* Function Description: Launch the application.
	*/
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					StaticAO frame = new StaticAO();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * 
	 * Build Date:2011-9-1 
	 * Author:Administrator
	 * Function Description: Create the frame.
	 */
	public StaticAO() {
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 397, 483);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);

		// Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("AO.png", "background image!");
		panel.setBounds(0, 0, 391, 451);
		contentPane.add(panel);
		panel.setLayout(null);

		txtHighLevelA = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtHighLevelA.setValue(new Double(5));
		txtHighLevelA.setHorizontalAlignment(SwingConstants.RIGHT);
		txtHighLevelA.setBounds(72, 89, 75, 22);
		panel.add(txtHighLevelA);
		txtHighLevelA.setColumns(10);

		txtLowLevelA = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtLowLevelA.setValue(new Double(-5));
		txtLowLevelA.setHorizontalAlignment(SwingConstants.RIGHT);
		txtLowLevelA.setColumns(10);
		txtLowLevelA.setBounds(163, 88, 75, 22);
		panel.add(txtLowLevelA);

		txtValueA = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtValueA.setValue(new Double(2.5));
		txtValueA.setHorizontalAlignment(SwingConstants.RIGHT);
		txtValueA.setColumns(10);
		txtValueA.setBounds(278, 88, 66, 22);
		panel.add(txtValueA);

		btnSineA = new JButton(imageIcon[0][0]);
		btnSineA.addActionListener(new WaveButtonActionListener());
		btnSineA.setBounds(62, 120, 53, 50);
		panel.add(btnSineA);

		btnSquareA = new JButton(imageIcon[0][1]);
		btnSquareA.addActionListener(new WaveButtonActionListener());
		btnSquareA.setBounds(130, 121, 53, 50);
		panel.add(btnSquareA);

		btnTriangleA = new JButton(imageIcon[0][2]);
		btnTriangleA.addActionListener(new WaveButtonActionListener());
		btnTriangleA.setBounds(198, 120, 53, 50);
		panel.add(btnTriangleA);

		BackgroundPanel manualImage = new BackgroundPanel("manual.png", "manual");
		btnManualA = new JButton(manualImage.getImageIcon());
		btnManualA.addActionListener(new ManualButtonActionListener());
		btnManualA.setBounds(283, 120, 53, 50);
		panel.add(btnManualA);

		btnSineB = new JButton(imageIcon[0][0]);
		btnSineB.addActionListener(new WaveButtonActionListener());
		btnSineB.setBounds(62, 298, 53, 50);
		panel.add(btnSineB);

		btnSquareB = new JButton(imageIcon[0][1]);
		btnSquareB.addActionListener(new WaveButtonActionListener());
		btnSquareB.setBounds(130, 298, 53, 50);
		panel.add(btnSquareB);

		btnTriangleB = new JButton(imageIcon[0][2]);
		btnTriangleB.addActionListener(new WaveButtonActionListener());
		btnTriangleB.setBounds(198, 298, 53, 50);
		panel.add(btnTriangleB);

		btnManualB = new JButton(manualImage.getImageIcon());
		btnManualB.addActionListener(new ManualButtonActionListener());
		btnManualB.setBounds(283, 298, 53, 50);
		panel.add(btnManualB);

		txtHighLevelB = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtHighLevelB.setValue(new Double(5));
		txtHighLevelB.setHorizontalAlignment(SwingConstants.RIGHT);
		txtHighLevelB.setColumns(10);
		txtHighLevelB.setBounds(72, 267, 75, 22);
		panel.add(txtHighLevelB);

		txtLowLevelB = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtLowLevelB.setValue(new Double(-5));
		txtLowLevelB.setHorizontalAlignment(SwingConstants.RIGHT);
		txtLowLevelB.setColumns(10);
		txtLowLevelB.setBounds(163, 266, 75, 22);
		panel.add(txtLowLevelB);

		txtValueB = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtValueB.setValue(new Double(2.5));
		txtValueB.setHorizontalAlignment(SwingConstants.RIGHT);
		txtValueB.setColumns(10);
		txtValueB.setBounds(278, 266, 66, 22);
		panel.add(txtValueB);

		sliderTime = new JSlider();
		sliderTime.setMinimum(10);
		sliderTime.setMaximum(1000);
		sliderTime.setBackground(SystemColor.control);
		sliderTime.addChangeListener(new SliderTimeChangeListener());
		sliderTime.setBounds(138, 400, 103, 25);
		panel.add(sliderTime);

		lblTime = new JLabel("50ms");
		lblTime.setBounds(240, 406, 50, 15);
		panel.add(lblTime);

		btnConfigure = new JButton("Configure");
		btnConfigure.setBounds(283, 402, 98, 23);
		btnConfigure.addActionListener(new ConfigureButtonActionListener());
		panel.add(btnConfigure);
		
		lblChannelA = new JLabel("0");
		lblChannelA.setForeground(new Color(188, 143, 143));
		lblChannelA.setFont(UIManager.getFont("InternalFrame.titleFont"));
		lblChannelA.setBounds(275, 34, 26, 15);
		panel.add(lblChannelA);
		
		lblChannelB = new JLabel("1");
		lblChannelB.setForeground(new Color(188, 143, 143));
		lblChannelB.setFont(UIManager.getFont("InternalFrame.titleFont"));
		lblChannelB.setBounds(275, 212, 26, 15);
		panel.add(lblChannelB);
		panel.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[]{
				txtHighLevelA, txtLowLevelA, txtValueA, btnSineA, btnSquareA, 
				btnTriangleA, btnManualA, txtHighLevelB, txtLowLevelB, txtValueB, 
				btnSineB, btnSquareB, btnTriangleB, btnManualB, sliderTime, btnConfigure}));
		
		configureDialog = new ConfigureDialog(this);
		configureDialog.setModal(true);
		configureDialog.setVisible(true);
	}

	
	/**
	 * 
	 * Build Date:2011-9-1 
	 * Author:Administrator
	 * Function Description: This function is used to set value range of each Instant-Ai's channels
	 */
	protected void ConfigureDevice() {
		try {
			instantAoCtrl.setSelectedDevice(new DeviceInformation(configure.deviceName));
			AnalogChannel[] channels = instantAoCtrl.getChannels();
			for (int i = 0; i < channels.length; i++) {
				channels[i].setValueRange(configure.valueRange);
			}
		} catch (Exception e) {
			ShowMessage("Sorry, there're some errors occred: " + e.getMessage());
		}
		
		String profilePath = null;
		profilePath = configureDialog.GetProfilePath();
		ErrorCode errorCode = instantAoCtrl.LoadProfile(profilePath);
		if(Global.BioFaild(errorCode)){
			ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
			}
	}
	
	/**
	 * 
	 * Build Date:2011-9-1 
	 * Author:Administrator
	 * Function Description: This function is used to initialize the main frame.
	 */
	public void Initialization() {
		ConfigureDevice();
		
		AoFeatures feature = instantAoCtrl.getFeatures();
		waveformGenerator = new WaveformGenerator(configure.pointCountPerWave);
		
		this.setTitle("Static AO - Run(" + configure.deviceName.substring(0, configure.deviceName.length() - 1) + ")");
		lblChannelA.setText(String.valueOf(configure.channelStart));
		
		if(configure.channelCount == 1){
			lblChannelB.setText("");
			btnSineB.setEnabled(false);
			btnSquareB.setEnabled(false);
			btnTriangleB.setEnabled(false);
			btnManualB.setEnabled(false);
			txtHighLevelB.setEnabled(false);
			txtLowLevelB.setEnabled(false);
			txtValueB.setEnabled(false);
		}else{
			int chanNumberB = configure.channelStart + 1;
			if(chanNumberB == feature.getChannelCountMax()){
				chanNumberB = 0;
			}
			lblChannelB.setText(String.valueOf(chanNumberB));
			btnSineB.setEnabled(true);
			btnSquareB.setEnabled(true);
			btnTriangleB.setEnabled(true);
			btnManualB.setEnabled(true);
			txtHighLevelB.setEnabled(true);
			txtLowLevelB.setEnabled(true);
			txtValueB.setEnabled(true);
		}
	}
	
	/**
	 * 
	 * Build Date:2011-9-1 
	 * Author:Administrator
	 * Function Description: This function is overload the interface ActionListener,and 
	 * 						 is implementation need this function!
	 */
	public void actionPerformed(ActionEvent e) {
		if(isChannelAChecked){
			highLevelA = ((Number)txtHighLevelA.getValue()).doubleValue(); 
			lowLevelA = ((Number)txtLowLevelA.getValue()).doubleValue(); 

			dataScaled[0] = waveformGenerator.GetOnePoint(waveStyleA, pointIndexA++, highLevelA, lowLevelA);
			
			if(pointIndexA == configure.pointCountPerWave){
				pointIndexA = 0;
			}
		}
		
		if(isChannelBChecked){
			highLevelB = ((Number) txtHighLevelB.getValue()).doubleValue();
			lowLevelB = ((Number) txtLowLevelB.getValue()).doubleValue();
			
			dataScaled[1] = waveformGenerator.GetOnePoint(waveStyleB, pointIndexB++, highLevelB, lowLevelB);
			
			if(pointIndexB == configure.pointCountPerWave){
				pointIndexB = 0;
			}
		}
		
		ErrorCode errorCode = instantAoCtrl.Write(configure.channelStart, configure.channelCount, dataScaled);
		if (Global.BioFaild(errorCode)) {
			ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
		}
	}
	
	/**
	 * 
	 * Build Date:2011-9-1 
	 * Author:Administrator
	 * Function Description: This function is used to start the timer!
	 */
	private void Start() {
		if (timer == null) {
			timer = new Timer(200, this);
		}
		timer.start();
	}
	
	/**
	 * 
	 * Build Date:2011-9-1
	 * Author:Administrator
	 * Function Description: This function is used to show the error massage to user!
	 * 
	 * @param message: the message shown to users!
	 */
	protected void ShowMessage(String message) {
		JOptionPane.showMessageDialog(this, message, "Warning MessageBox", JOptionPane.WARNING_MESSAGE);
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
					timer.stop();
				}else{
					buttonState[0][0] = 1;
					waveStyleA = WaveformStyle.sine;
					isChannelAChecked = true;
					Start();
				}
				buttonState[0][1] = 0;
				buttonState[0][2] = 0;
			}else if(source == btnSquareA){
				if(buttonState[0][1] == 1){
					buttonState[0][1] = 0;
					isChannelAChecked = false;
					timer.stop();
				}else{
					buttonState[0][1] = 1;
					waveStyleA = WaveformStyle.square;
					isChannelAChecked = true;
					Start();
				}
				buttonState[0][0] = 0;
				buttonState[0][2] = 0;
			}else if(source == btnTriangleA){
				if(buttonState[0][2] == 1){
					buttonState[0][2] = 0;
					isChannelAChecked = false;
					timer.stop();
				}else{
					buttonState[0][2] = 1;
					waveStyleA = WaveformStyle.triangle;
					isChannelAChecked = true;
					Start();
				}
				buttonState[0][0] = 0;
				buttonState[0][1] = 0;
			}else if(source == btnSineB){
				if(buttonState[1][0] == 1){
					buttonState[1][0] = 0;
					isChannelBChecked = false;
					timer.stop();
				}else{
					buttonState[1][0] = 1;
					waveStyleB = WaveformStyle.sine;
					isChannelBChecked = true;
					Start();
				}
				buttonState[1][1] = 0;
				buttonState[1][2] = 0;
			}else if(source == btnSquareB){
				if(buttonState[1][1] == 1){
					buttonState[1][1] = 0;
					isChannelBChecked = false;
					timer.stop();
				}else{
					buttonState[1][1] = 1;
					waveStyleB = WaveformStyle.square;
					isChannelBChecked = true;
					Start();
				}
				buttonState[1][0] = 0;
				buttonState[1][2] = 0;
			}else if(source == btnTriangleB){
				if(buttonState[1][2] == 1){
					buttonState[1][2] = 0;
					isChannelBChecked = false;
					timer.stop();
				}else{
					buttonState[1][2] = 1;
					waveStyleB = WaveformStyle.triangle;
					isChannelBChecked = true;
					Start();
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
	 * Class Function Description: This class is used to listen the time slider's change.
	 */
	class SliderTimeChangeListener implements ChangeListener{
		public void stateChanged(ChangeEvent arg0) {
			if(timer == null){
				Start();
			}
			timer.setDelay(sliderTime.getValue());
			lblTime.setText(String.valueOf(sliderTime.getValue()) + "ms");
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
	 * Class Function Description: This class is used to listen the manual button 's action.
	 */
	class ManualButtonActionListener implements ActionListener{
		public void actionPerformed(ActionEvent e){
			if(timer != null){
				timer.stop();
			}
			JButton source = (JButton)e.getSource();
			if(source == btnManualA){
				for(int i = 0; i < 3; i++){
					buttonState[0][i] = 0;
					btnSineA.setIcon(imageIcon[0][0]);
					btnSquareA.setIcon(imageIcon[0][1]);
					btnTriangleA.setIcon(imageIcon[0][2]);
				}
				isChannelAChecked = false;
				
				double value = ((Number)txtValueA.getValue()).doubleValue();
				dataScaled[0] = value;
			}else{
				for(int i = 0; i < 3; i++){
					buttonState[1][i] = 0;
					btnSineB.setIcon(imageIcon[0][0]);
					btnSquareB.setIcon(imageIcon[0][1]);
					btnTriangleB.setIcon(imageIcon[0][2]);
				}
				isChannelBChecked = false;
				
				double value = ((Number)txtValueB.getValue()).doubleValue();
				dataScaled[1] = value;
			}
			
			ErrorCode errorCode = instantAoCtrl.Write(configure.channelStart, configure.channelCount, dataScaled);
			if(Global.BioFaild(errorCode)){
				ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
			}
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
			if (instantAoCtrl != null) {
				instantAoCtrl.Cleanup();
			}
			if(timer != null){
				timer.stop();
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
}
