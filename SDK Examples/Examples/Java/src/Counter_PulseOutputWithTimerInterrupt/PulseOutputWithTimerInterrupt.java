package Counter_PulseOutputWithTimerInterrupt;

import java.awt.EventQueue;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.JButton;

import Automation.BDaq.*;
import Common.Global;

import org.eclipse.wb.swing.FocusTraversalOnArray;

import java.awt.Component;
import java.text.NumberFormat;

public class PulseOutputWithTimerInterrupt extends JFrame {
	/**
	 * define the serialization number.
	 */
	private static final long serialVersionUID = 1L;
	
	private JPanel contentPane;
	private JFormattedTextField txtDesiredFreq;
	private JTextField txtGeneratedFreq;
	private JTextField txtEventCount;
	private JLabel lblStatus;
	private JButton btnConfigure;
	private JButton btnStart;
	private JButton btnStop;
	
	ConfigureParameter configure = new ConfigureParameter();
	private ConfigureDialog configureDialog;
	private TimerPulseCtrl timerPulseCtrl = new TimerPulseCtrl();
	private int eventCount = 0;
	private JLabel lblStatus_1;

	/**
	 * 
	 * Build Date:2011-10-09 
	 * Author:Administrator
	 * Function Description: Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					PulseOutputWithTimerInterrupt frame = new PulseOutputWithTimerInterrupt();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * 
	 * Build Date:2011-10-09 
	 * Author:Administrator
	 * Function Description: Create the frame.
	 */
	public PulseOutputWithTimerInterrupt() {
		setTitle("Timer Pulse");
		//add the window closing action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 404, 355);
		contentPane = new JPanel();
		contentPane.setBackground(SystemColor.control);
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(null);
		setContentPane(contentPane);
		
		JPanel panelValue = new JPanel();
		panelValue.setBackground(SystemColor.control);
		panelValue.setBounds(26, 68, 339, 188);
		panelValue.setBorder(BorderFactory.createTitledBorder("Execution status"));
		contentPane.add(panelValue);
		panelValue.setLayout(null);
		
		JLabel lblDevice = new JLabel("Device generated pulse frequency:");
		lblDevice.setBounds(10, 66, 206, 15);
		panelValue.add(lblDevice);
		
		lblStatus = new JLabel(new BackgroundPanel("TimerPulseStatus.gif", "status").getImageIcon());
		lblStatus.setHorizontalAlignment(SwingConstants.LEFT);
		lblStatus.setBounds(64, 29, 244, 15);
		lblStatus.setDisabledIcon(new BackgroundPanel("ExecutionStatus.png", "stop").getImageIcon());
		lblStatus.setEnabled(false);
		panelValue.add(lblStatus);
		
		JLabel lblDeviceGeneratedEvent = new JLabel("Device generated timer event count:");
		lblDeviceGeneratedEvent.setBounds(10, 127, 244, 15);
		panelValue.add(lblDeviceGeneratedEvent);
		
		txtGeneratedFreq = new JTextField();
		txtGeneratedFreq.setEditable(false);
		txtGeneratedFreq.setHorizontalAlignment(SwingConstants.RIGHT);
		txtGeneratedFreq.setText("0");
		txtGeneratedFreq.setColumns(10);
		txtGeneratedFreq.setBounds(64, 91, 222, 21);
		panelValue.add(txtGeneratedFreq);
		
		JLabel label_3 = new JLabel("Hz");
		label_3.setBounds(288, 94, 20, 15);
		panelValue.add(label_3);
		
		txtEventCount = new JTextField();
		txtEventCount.setEditable(false);
		txtEventCount.setText("0");
		txtEventCount.setHorizontalAlignment(SwingConstants.RIGHT);
		txtEventCount.setColumns(10);
		txtEventCount.setBounds(64, 152, 222, 21);
		panelValue.add(txtEventCount);
		
		lblStatus_1 = new JLabel("Status:");
		lblStatus_1.setBounds(10, 29, 56, 15);
		panelValue.add(lblStatus_1);
		
		JLabel lblNewLabel = new JLabel("Desired frequency:");
		lblNewLabel.setBounds(26, 10, 122, 15);
		contentPane.add(lblNewLabel);
		
		txtDesiredFreq = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtDesiredFreq.setValue(new Double(50));
		txtDesiredFreq.setHorizontalAlignment(SwingConstants.RIGHT);
		txtDesiredFreq.setBounds(36, 31, 200, 21);
		contentPane.add(txtDesiredFreq);
		txtDesiredFreq.setColumns(10);
		
		JLabel lblNewLabel_1 = new JLabel("Hz");
		lblNewLabel_1.setBounds(238, 34, 20, 15);
		contentPane.add(lblNewLabel_1);
		
		btnConfigure = new JButton("Configure");
		btnConfigure.setBounds(36, 279, 115, 23);
		btnConfigure.addActionListener(new ButtonConfigureActionListener());
		contentPane.add(btnConfigure);
		
		btnStart = new JButton("Start");
		btnStart.setBounds(178, 279, 80, 23);
		btnStart.addActionListener(new ButtonStartActionListener());
		contentPane.add(btnStart);
		
		btnStop = new JButton("Stop");
		btnStop.setEnabled(false);
		btnStop.setBounds(285, 279, 80, 23);
		btnStop.addActionListener(new ButtonStopActionListener());
		contentPane.add(btnStop);
		
		//Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("Background.png", "background image!");
		panel.setBounds(263, 0, 136, 52);
		panel.setBackground(SystemColor.control);
		panel.setLayout(null);
		contentPane.add(panel);
		contentPane.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[]{
				txtDesiredFreq, btnConfigure, btnStart, btnStop}));
		
		//Caution: When TimerTick interrupt is too frequent, the operating system may hang.
		//The following is the suggestion:
		//1.If you use the pulse output function only, you don't need to deal with TimerTick event.
		//2.If you want to use timer interrupt function, uncomment the following codes.

		//timerPulseCtrl.addTimerTickListener(new TimerPulseEventListener());
		
		configureDialog = new ConfigureDialog(this);
		configureDialog.setModal(true);
		configureDialog.setVisible(true);
	}
	
	/**
	 * 
	 * Build Date:2011-10-09
	 * Author:Administrator
	 * Function Description: This function is used to initialize the main frame.
	 */
	public void Initialization() {
		//set the main frame's title.
		this.setTitle("Pulse Output With Timer Interrupt - Run(" + configure.deviceName.substring(0, configure.deviceName.length() - 1) + ")");
		
		try{
			DeviceInformation devInformation = new DeviceInformation(configure.deviceName);
			devInformation.ModuleIndex = configure.moduleIndex;
			timerPulseCtrl.setSelectedDevice(devInformation);
			String profilePath = null;
			profilePath = configureDialog.GetProfilePath();
			ErrorCode errorCode = timerPulseCtrl.LoadProfile(profilePath);
			if(Global.BioFaild(errorCode)){
				ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
				}
			timerPulseCtrl.setChannelCount(1);
			timerPulseCtrl.setChannelStart(configure.counterChannel);
		}catch(Exception ex){
			ShowMessage("Sorry, some errors occurred: " + ex.getMessage());
		}
		
		txtGeneratedFreq.setText("0");
		txtEventCount.setText("0");
	}
	
	/**
	 * 
	 * Build Date:2011-10-09
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
	 * @author Administrator
	 * Class Function Description: This class is used to listen the timer pulse event.
	 */
	class TimerPulseEventListener implements CntrEventListener{

		public void CntrEvent(Object sender, CntrEventArgs args) {
			txtEventCount.setText(String.valueOf(eventCount++));
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the start button's action.
	 */
	class ButtonStartActionListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			double frequence = ((Number)txtDesiredFreq.getValue()).doubleValue();
			try{
				timerPulseCtrl.getChannels()[timerPulseCtrl.getChannelStart()].setFrequency(frequence);
				timerPulseCtrl.setEnabled(true);
				txtGeneratedFreq.setText(String.valueOf(timerPulseCtrl.getChannels()[timerPulseCtrl.getChannelStart()].getFrequency()));
			}catch(Exception ex){
				ShowMessage("Sorry, there're some errors occured: " + ex.getMessage());
				return;
			}
			
			lblStatus.setEnabled(true);
			txtDesiredFreq.setEnabled(false);
			btnStart.setEnabled(false);
			btnStop.setEnabled(true);
			btnConfigure.setEnabled(false);
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the stop button 's action.
	 */
	class ButtonStopActionListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			eventCount = 0;
			try {
				timerPulseCtrl.setEnabled(false);
			} catch (Exception ex) {
				ShowMessage("Sorry, there're some errors occured: " + ex.toString());
				return;
			}
		
			lblStatus.setEnabled(false);
			txtDesiredFreq.setEnabled(true);
			btnStart.setEnabled(true);
			btnConfigure.setEnabled(true);
			btnStop.setEnabled(false);
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the configure button 's action.
	 */
	class ButtonConfigureActionListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {

			if(timerPulseCtrl.getEnabled()){
				try {
					timerPulseCtrl.setEnabled(false);
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
	 * Class Function Description: This class is used to listen the main frame's closing event.
	 */
	class WindowCloseActionListener extends WindowAdapter{
		@Override
		public void windowClosing(WindowEvent e) {
			if (timerPulseCtrl.getEnabled()) {
				try {
					timerPulseCtrl.setEnabled(false);
					timerPulseCtrl.Cleanup();
				} catch (Exception ex) {
					// do nothing here!
					// ShowMessage("Sorry, there're some errors occurred: " + ex.toString());
				}
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
	public int moduleIndex;
}
