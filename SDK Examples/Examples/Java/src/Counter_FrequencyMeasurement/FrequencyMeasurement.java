package Counter_FrequencyMeasurement;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.SwingConstants;
import javax.swing.JTextField;
import javax.swing.JSlider;
import javax.swing.JButton;
import javax.swing.Timer;

import Common.*;
import Automation.BDaq.*;

import org.eclipse.wb.swing.FocusTraversalOnArray;

import java.awt.Component;

public class FrequencyMeasurement extends JFrame implements ActionListener{
	/**
	 * define the serialization number.
	 */
	private static final long serialVersionUID = 1L;
	
	private JPanel contentPane;
	private JTextField txtChannel;
	private JTextField txtFrequency;
	private JTextField txtInterval;
	private JLabel lblYCoordinateMax;
	private JLabel lblYCoordinateMid;
	private JLabel lblYCoordinateMin;
	private JLabel lblFreqencyUnit;
	private JSlider sldTimer;
	private JButton btnZoomIn;
	private JButton btnZoomOut;
	private JButton btnConfigure;
	private JButton btnStart;
	private JButton btnPause;
	private JButton btnStop;
	
	private SimpleGraph graph;
	ConfigureParameter configure = new ConfigureParameter();
	private ConfigureDialog configureDialog;
	private FreqMeterCtrl freqMeterCtrl = new FreqMeterCtrl();
	private Timer timer;
	
	private ArrayList<RangeYType> rangeYList = new ArrayList<RangeYType>();
	private int unitIndex = 1;
	private double[] frequency = new double[1];

	/**
	 * 
	 *Build Date:2011-10-13
	 *Author:Administrator
	 *Function Description: Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					FrequencyMeasurement frame = new FrequencyMeasurement();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * 
	 *Build Date:2011-10-13
	 *Author:Administrator
	 *Function Description: Create the frame.
	 */
	public FrequencyMeasurement() {
		// Add the window close event action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 733, 525);
		contentPane = new JPanel();
		contentPane.setBackground(SystemColor.control);
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		graph = new SimpleGraph();
		graph.setBounds(91, 32, 540, 310);
		graph.setBackground(Color.black);
		graph.size = new Dimension(graph.getSize());
		contentPane.add(graph);
		
		// Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("Background.png", "Background Image");
		panel.setBounds(567, 0, 160, 50);
		panel.setLayout(null);
		contentPane.add(panel);

		lblYCoordinateMax = new JLabel("1MHz");
		lblYCoordinateMax.setHorizontalAlignment(SwingConstants.RIGHT);
		lblYCoordinateMax.setBounds(33, 35, 54, 15);
		contentPane.add(lblYCoordinateMax);

		lblYCoordinateMid = new JLabel("");
		lblYCoordinateMid.setHorizontalAlignment(SwingConstants.RIGHT);
		lblYCoordinateMid.setBounds(33, 190, 54, 15);
		contentPane.add(lblYCoordinateMid);

		lblYCoordinateMin = new JLabel("0MHz");
		lblYCoordinateMin.setHorizontalAlignment(SwingConstants.RIGHT);
		lblYCoordinateMin.setBounds(33, 327, 54, 15);
		contentPane.add(lblYCoordinateMin);

		JLabel lblXCoordinateMin = new JLabel("0");
		lblXCoordinateMin.setBounds(91, 344, 54, 15);
		contentPane.add(lblXCoordinateMin);

		JLabel lblXCoordinateMax = new JLabel("10Sec");
		lblXCoordinateMax.setHorizontalAlignment(SwingConstants.RIGHT);
		lblXCoordinateMax.setBounds(577, 344, 54, 15);
		contentPane.add(lblXCoordinateMax);

		JLabel lblCounterChannel = new JLabel("Counter Channel:");
		lblCounterChannel.setBounds(91, 369, 108, 15);
		contentPane.add(lblCounterChannel);

		txtChannel = new JTextField();
		txtChannel.setEditable(false);
		txtChannel.setText("0");
		txtChannel.setHorizontalAlignment(SwingConstants.RIGHT);
		txtChannel.setBounds(200, 366, 133, 21);
		contentPane.add(txtChannel);
		txtChannel.setColumns(10);

		txtFrequency = new JTextField();
		txtFrequency.setText("1");
		txtFrequency.setHorizontalAlignment(SwingConstants.RIGHT);
		txtFrequency.setEditable(false);
		txtFrequency.setColumns(10);
		txtFrequency.setBounds(466, 366, 133, 21);
		contentPane.add(txtFrequency);

		JLabel lblFrenquency = new JLabel("Frenquency:");
		lblFrenquency.setBounds(393, 369, 73, 15);
		contentPane.add(lblFrenquency);

		lblFreqencyUnit = new JLabel("Hz");
		lblFreqencyUnit.setBounds(607, 369, 24, 15);
		contentPane.add(lblFreqencyUnit);

		JLabel lblSample = new JLabel("Sample interval:");
		lblSample.setBounds(91, 406, 108, 15);
		contentPane.add(lblSample);

		txtInterval = new JTextField();
		txtInterval.setText("50");
		txtInterval.setHorizontalAlignment(SwingConstants.RIGHT);
		txtInterval.setEditable(false);
		txtInterval.setColumns(10);
		txtInterval.setBounds(533, 400, 66, 21);
		contentPane.add(txtInterval);

		JLabel lblTimeUnit = new JLabel("ms");
		lblTimeUnit.setBounds(607, 403, 24, 15);
		contentPane.add(lblTimeUnit);

		sldTimer = new JSlider();
		sldTimer.setMinimum(10);
		sldTimer.setMaximum(1000);
		sldTimer.setBackground(SystemColor.control);
		sldTimer.setBounds(199, 400, 332, 25);
		sldTimer.addChangeListener(new SliderTimeChangeListener());
		contentPane.add(sldTimer);

		btnZoomIn = new JButton(new BackgroundPanel("Enlarge.png", "Enlarge").getImageIcon());
		btnZoomIn.setBounds(641, 268, 28, 28);
		btnZoomIn.addActionListener(new ButtonZoomActionListener(btnZoomIn));
		contentPane.add(btnZoomIn);

		btnZoomOut = new JButton(new BackgroundPanel("Shorten.png", "Shorten").getImageIcon());
		btnZoomOut.setBounds(641, 314, 28, 28);
		btnZoomOut.addActionListener(new ButtonZoomActionListener(btnZoomOut));
		contentPane.add(btnZoomOut);

		btnConfigure = new JButton("Configure");
		btnConfigure.setBounds(200, 448, 115, 23);
		btnConfigure.addActionListener(new ButtonConfigureActionListener());
		contentPane.add(btnConfigure);

		btnStart = new JButton("Start");
		btnStart.setBounds(356, 448, 75, 23);
		btnStart.addActionListener(new ButtonStartActionListener());
		contentPane.add(btnStart);
		
		btnPause = new JButton("Pause");
		btnPause.setEnabled(false);
		btnPause.setBounds(456, 448, 75, 23);
		btnPause.addActionListener(new ButtonPauseActionListener());
		contentPane.add(btnPause);

		btnStop = new JButton("Stop");
		btnStop.setEnabled(false);
		btnStop.setBounds(556, 448, 75, 23);
		btnStop.addActionListener(new ButtonStopActionListener());
		contentPane.add(btnStop);
		contentPane.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[]{
				btnZoomIn, btnZoomOut, sldTimer, btnConfigure, btnStart, btnPause, btnStop}));
		
		ConstructRangeYList();

		configureDialog = new ConfigureDialog(this);
		configureDialog.setModal(true);
		configureDialog.setVisible(true);
	}
	
	/**
	 * 
	 *Build Date:2011-10-13
	 *Author:Administrator
	 *Function Description: This function is used to construct the Y coordinate list.
	 */
	private void ConstructRangeYList(){
		int index = 0;
		
		for(int i = 10000000; i >= 1; i /= 10){
			if(i >= 1000000){    
				//the Y coordinate unit is MHz.
				RangeYType rangeYType = new RangeYType();
				rangeYType.rangeY = new MathInterval();
				rangeYType.rangeY.Max = i / 1000000;
				rangeYType.rangeY.Min = 0;
				rangeYType.unit = FrequencyUnit.MHz;
				rangeYList.add(index++, rangeYType);
				continue;
			}else if(i >= 1000){   
				//the Y coordinate unit is KHz.
				RangeYType rangeYType = new RangeYType();
				rangeYType.rangeY = new MathInterval();
				rangeYType.rangeY.Max = i / 1000;
				rangeYType.rangeY.Min = 0;
				rangeYType.unit = FrequencyUnit.KHz;
				rangeYList.add(index++, rangeYType);
				continue;
			}
			
			//the Y coordinate unit is Hz.
			RangeYType rangeYType = new RangeYType();
			rangeYType.rangeY = new MathInterval();
			rangeYType.rangeY.Max = i;
			rangeYType.rangeY.Min = 0;
			rangeYType.unit = FrequencyUnit.Hz;
			rangeYList.add(index++, rangeYType);
		}
	}
	
	/**
	 * 
	 *Build Date:2011-10-13
	 *Author:Administrator
	 *Function Description: This function is used to set Y coordinate of the graph.
	 * @param index : the index of current Y coordinate in the array list.
	 */
	private void SetYCord(int index){
		RangeYType rangeYType = (RangeYType)rangeYList.get(index);
		String[] y_Ranges = new String[3];
		String unit = new String();
		int rate = 1;
		
		y_Ranges[0] = String.valueOf(rangeYType.rangeY.Min);
		y_Ranges[1] = (rangeYType.rangeY.Max == -rangeYType.rangeY.Min) ? "0" : "";
		y_Ranges[2] = String.valueOf(rangeYType.rangeY.Max);
		
		switch(rangeYType.unit){
		case MHz:
			unit = "MHz";
			rate = 1000 * 1000;
			break;
		case KHz:
			unit = "KHz";
			rate = 1000;
			break;
		case Hz:
			unit = "Hz";
			break;
		}
		
		y_Ranges[0] += unit;
		y_Ranges[2] += unit;
		lblYCoordinateMax.setText(y_Ranges[2]);
		lblYCoordinateMid.setText(y_Ranges[1]);
		lblYCoordinateMin.setText(y_Ranges[0]);
		
		graph.setyCordRangeMax(rangeYType.rangeY.Max * rate);
		graph.setyCordRangeMin(rangeYType.rangeY.Min * rate);

	}
	
	/**
	 * 
	 * Build Date:2011-10-13
	 * Author:Administrator
	 * Function Description: This function is used to initialize the main frame.
	 */
	public void Initialization() {
		//set the main frame's title.
		setTitle("Frequency Measurement - Run(" + configure.deviceName.substring(0, configure.deviceName.length() - 1) + ")");
		
		if(timer == null){
			timer = new Timer(50, this);
		}
		SetYCord(unitIndex);
		graph.setXCordTimeDiv(1000);
		graph.Clear();
		
		btnConfigure.setEnabled(true);
		btnStart.setEnabled(true);
		btnPause.setEnabled(false);
		btnStop.setEnabled(false);
		
		try{
			freqMeterCtrl.setSelectedDevice(new DeviceInformation(configure.deviceName));
			String profilePath = null;
			profilePath = configureDialog.GetProfilePath();
			ErrorCode errorCode = freqMeterCtrl.LoadProfile(profilePath);
			if(Global.BioFaild(errorCode)){
				ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
				}
			freqMeterCtrl.setChannelCount(1);
			freqMeterCtrl.setChannelStart(configure.counterChannel);
			txtChannel.setText(String.valueOf(configure.counterChannel));
		}catch(Exception ex){
			ShowMessage("Sorry, there're some errors occurred: " + ex.getMessage());
		}
	}
	
	/**
	 * 
	 * Build Date:2011-10-13
	 * Author:Administrator
	 * Function Description: This function is used to start the timer.
	 */
	private void Start() {
		if (timer == null) {
			timer = new Timer(500, this);
		}
		timer.start();
	}
	
	/**
	 * 
	 * Build Date:2011-10-13
	 * Author:Administrator
	 * Function Description: If some errors occurred, Show the error code to the users.
	 * 
	 * @param message:the message shown to users!
	 */
	protected void ShowMessage(String message) {
		JOptionPane.showMessageDialog(this, message, "Warning MessageBox",
				JOptionPane.WARNING_MESSAGE);
	}

	/**
	 * 
	 * Build Date:2011-10-13
	 * Author:Administrator
	 * Function Description: This function is overload the interface ActionListener,and 
	 * 						 is implementation need this function.
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		double[] x = {0};
		freqMeterCtrl.Read(1, x);
		frequency[0] = x[0];
		graph.Chart(frequency, 1, 1, 1.0 * timer.getDelay() / 1000);
		txtFrequency.setText(String.format("%10.6f",frequency[0]));
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the configure button 's action.
	 */
	class ButtonConfigureActionListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			if(timer == null){
				Start();
			}
			timer.stop();
			
			if(freqMeterCtrl.getEnabled()){
				try {
					freqMeterCtrl.setEnabled(false);
				} catch (Exception ex) {
					ShowMessage("Sorry, there're some errors occured: " + ex.toString());
					return;
				}
			}
			
			configureDialog.isFirstLoad = false;
			configureDialog.setVisible(true);
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the start button 's action.
	 */
	class ButtonStartActionListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			Start();
			try {
				freqMeterCtrl.setEnabled(true);
			} catch (Exception ex) {
				ShowMessage("Sorry, there're some errors occured: " + ex.toString());
				return;
			}

			btnStart.setEnabled(false);
			btnConfigure.setEnabled(false);
			btnPause.setEnabled(true);
			btnStop.setEnabled(true);
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the pause button 's action.
	 */
	class ButtonPauseActionListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			timer.stop();

			btnStart.setEnabled(true);
			btnConfigure.setEnabled(false);
			btnPause.setEnabled(false);
			btnStop.setEnabled(true);
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the stop button 's action.
	 */
	class ButtonStopActionListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			timer.stop();
			try {
				freqMeterCtrl.setEnabled(false);
			} catch (Exception ex) {
				ShowMessage("Sorry, there're some errors occured: " + ex.toString());
				return;
			}
			
			btnStart.setEnabled(true);
			btnPause.setEnabled(false);
			btnConfigure.setEnabled(true);
			btnStop.setEnabled(false);
			
			graph.Clear();
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the zoom in/out button 's action.
	 */
	class ButtonZoomActionListener implements ActionListener{
		private JButton source;
		
		public ButtonZoomActionListener(JButton source){
			this.source = source;
		}
		public void actionPerformed(ActionEvent e) {
			if(source == btnZoomIn){
				if(unitIndex <= 0){
					return;
				}
				unitIndex--;
				SetYCord(unitIndex);
			}else if(source == btnZoomOut){
				if(unitIndex >= 7){
					return;
				}
				unitIndex++;
				SetYCord(unitIndex);
			}
			
			graph.Clear();
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the time slider's change.
	 */
	class SliderTimeChangeListener implements ChangeListener{
		public void stateChanged(ChangeEvent arg0) {
			if (timer == null) {
				Start();
			}
			if (btnStart.getModel().isEnabled() == false) {
				timer.start();
			}else{
				timer.stop();
			}
			
			graph.Clear();
			txtInterval.setText(String.valueOf(sldTimer.getValue()));
			timer.setDelay(sldTimer.getValue());
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
			if (freqMeterCtrl.getEnabled()) {
				try {
					freqMeterCtrl.setEnabled(false);
					freqMeterCtrl.Cleanup();
				} catch (Exception ex) {
					// do nothing here!
					// ShowMessage("Sorry, there're some errors occurred: " + ex.toString());
				}
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
 * Class Description: this class is use to transfer parameter to the main frame !
 */
class ConfigureParameter {
	public String deviceName;
	public int counterChannel;
}

/**
 * 
 * @author Administrator 
 * Class Description: this class is use to define Y coordinate of the graph.
 */
class RangeYType{
	public MathInterval rangeY;
	public FrequencyUnit unit;
}
