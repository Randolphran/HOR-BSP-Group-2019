package Counter_PWMOutput;

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
import javax.swing.JButton;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.SwingConstants;

import Automation.BDaq.*;
import Common.Global;

import org.eclipse.wb.swing.FocusTraversalOnArray;

import java.awt.Component;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.text.NumberFormat;

public class PWMOutput extends JFrame {

	/**
	 * define the serialization number.
	 */
	private static final long serialVersionUID = 1L;
	
	private JPanel contentPane;
	private JFormattedTextField txtHighDesired;
	private JFormattedTextField txtLowDesired;
	private JLabel lblStatus;
	private JTextField txtHighGenerated;
	private JTextField txtLowGenerated;
	private JButton btnConfigure;
	private JButton btnStart;
	private JButton btnStop;
	
	ConfigureParameter configure = new ConfigureParameter();
	private ConfigureDialog configureDialog;
	private PwModulatorCtrl pwModulatorCtrl = new PwModulatorCtrl();

	/**
	 * 
	 * Build Date:2011-10-12
	 * Author:Administrator
	 * Function Description: Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					PWMOutput frame = new PWMOutput();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * 
	 * Build Date:2011-10-12
	 * Author:Administrator
	 * Function Description:  Create the frame.
	 */
	public PWMOutput() {
		//add window close event listener.
		addWindowListener(new WindowCloseActionListener());
		
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 381, 444);
		
		contentPane = new JPanel();
		contentPane.setBackground(SystemColor.control);
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(null);
		setContentPane(contentPane);
		
		JPanel panelDesired = new JPanel();
		panelDesired.setBackground(SystemColor.control);
		panelDesired.setBounds(25, 53, 318, 98);
		panelDesired.setBorder(BorderFactory.createTitledBorder("Desired Pulse Width"));
		panelDesired.setLayout(null);
		contentPane.add(panelDesired);
		
		JLabel lblHighPeriod = new JLabel("High Period:");
		lblHighPeriod.setBounds(29, 30, 80, 15);
		panelDesired.add(lblHighPeriod);
		
		txtHighDesired = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtHighDesired.setValue(new Double(0.08));
		txtHighDesired.setHorizontalAlignment(SwingConstants.RIGHT);
		txtHighDesired.setBounds(114, 27, 165, 21);
		txtHighDesired.addPropertyChangeListener(new DesiredPeriodListener(txtHighDesired));
		panelDesired.add(txtHighDesired);
		txtHighDesired.setColumns(10);
		
		JLabel lblNewLabel = new JLabel("S");
		lblNewLabel.setBounds(286, 30, 21, 15);
		panelDesired.add(lblNewLabel);
		
		JLabel lblLowPeriod = new JLabel("Low Period:");
		lblLowPeriod.setBounds(29, 61, 80, 15);
		panelDesired.add(lblLowPeriod);
		
		txtLowDesired = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtLowDesired.setValue(new Double(0.02));
		txtLowDesired.setHorizontalAlignment(SwingConstants.RIGHT);
		txtLowDesired.setColumns(10);
		txtLowDesired.setBounds(114, 58, 165, 21);
		txtLowDesired.addPropertyChangeListener(new DesiredPeriodListener(txtLowDesired));
		panelDesired.add(txtLowDesired);
		
		JLabel label_1 = new JLabel("S");
		label_1.setBounds(286, 61, 21, 15);
		panelDesired.add(label_1);
		
		JPanel panelValue = new JPanel();
		panelValue.setBackground(SystemColor.control);
		panelValue.setBounds(25, 164, 318, 167);
		panelValue.setBorder(BorderFactory.createTitledBorder("Execution Status"));
		panelValue.setLayout(null);
		contentPane.add(panelValue);
		
		JLabel lbl = new JLabel("High Period:");
		lbl.setBounds(29, 100, 80, 15);
		panelValue.add(lbl);
		
		txtHighGenerated = new JTextField();
		txtHighGenerated.setEnabled(false);
		txtHighGenerated.setHorizontalAlignment(SwingConstants.RIGHT);
		txtHighGenerated.setColumns(10);
		txtHighGenerated.setBounds(114, 97, 165, 21);
		panelValue.add(txtHighGenerated);
		
		JLabel label_2 = new JLabel("S");
		label_2.setBounds(286, 100, 21, 15);
		panelValue.add(label_2);
		
		JLabel label_3 = new JLabel("S");
		label_3.setBounds(286, 131, 21, 15);
		panelValue.add(label_3);
		
		txtLowGenerated = new JTextField();
		txtLowGenerated.setEnabled(false);
		txtLowGenerated.setHorizontalAlignment(SwingConstants.RIGHT);
		txtLowGenerated.setColumns(10);
		txtLowGenerated.setBounds(114, 128, 165, 21);
		panelValue.add(txtLowGenerated);
		
		JLabel label_4 = new JLabel("Low Period:");
		label_4.setBounds(29, 131, 80, 15);
		panelValue.add(label_4);
		
		lblStatus = new JLabel(new BackgroundPanel("PwModulatorStatus.gif", "status").getImageIcon());
		lblStatus.setEnabled(false);
		lblStatus.setBounds(36, 32, 241, 15);
		lblStatus.setDisabledIcon(new BackgroundPanel("ExecutionStatus.png", "disable").getImageIcon());
		panelValue.add(lblStatus);
		
		JLabel lblDeviceGeneratedPulse = new JLabel("Device generated pulse period:");
		lblDeviceGeneratedPulse.setBounds(29, 72, 278, 15);
		panelValue.add(lblDeviceGeneratedPulse);
		
		// Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("Background.png", "background image!");
		panel.setBounds(216, 0, 160, 50);
		panel.setBackground(SystemColor.control);
		panel.setLayout(null);
		contentPane.add(panel);
		
		btnConfigure = new JButton("Configure");
		btnConfigure.setBounds(25, 367, 115, 23);
		btnConfigure.addActionListener(new ButtonConfigureActionListener());
		contentPane.add(btnConfigure);
		
		btnStart = new JButton("Start");
		btnStart.setBounds(163, 367, 80, 23);
		btnStart.addActionListener(new ButtonStartActionListener());
		contentPane.add(btnStart);
		
		btnStop = new JButton("Stop");
		btnStop.setEnabled(false);
		btnStop.setBounds(263, 367, 80, 23);
		btnStop.addActionListener(new ButtonStopActionListener());
		contentPane.add(btnStop);
		contentPane.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[]{
				txtHighDesired, txtLowDesired, btnConfigure, btnStart, btnStop}));
		
		configureDialog = new ConfigureDialog(this);
		configureDialog.setModal(true);
		configureDialog.setVisible(true);

	}
	
	/**
	 * 
	 * Build Date:2011-10-12
	 * Author:Administrator
	 * Function Description: This function is used to initialize the main frame.
	 */
	public void Initialization() {
		//set the main frame's title.
		setTitle("PWM Output - Run(" + configure.deviceName.substring(0, configure.deviceName.length() - 1) + ")");
		
		txtHighDesired.setValue(new Double(0.08));
		txtLowDesired.setValue(new Double(0.02));
		txtHighGenerated.setText("");
		txtLowGenerated.setText("");
		
		try{
			pwModulatorCtrl.setSelectedDevice(new DeviceInformation(configure.deviceName));
			String profilePath = null;
			profilePath = configureDialog.GetProfilePath();
			ErrorCode errorCode = pwModulatorCtrl.LoadProfile(profilePath);
			if(Global.BioFaild(errorCode)){
				ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
				}
			pwModulatorCtrl.setChannelCount(1);
			pwModulatorCtrl.setChannelStart(configure.counterChannel);
		}catch(Exception ex){
			ShowMessage("Sorry, there're some errors occurred: " + ex.getMessage());
		}
	}
	
	/**
	 * 
	 * Build Date:2011-10-12
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
	 * Class Function Description: This class is used to listen the clock count  
	 * 							   textField's text changing action.
	 */
	class DesiredPeriodListener implements PropertyChangeListener{
		JFormattedTextField source;
		
		public DesiredPeriodListener(JFormattedTextField source){
			this.source = source;
		}

		@Override
		public void propertyChange(PropertyChangeEvent evt) {
			double highPeriod, lowPeriod;
			if(source == txtHighDesired){
				highPeriod = ((Number)txtHighDesired.getValue()).doubleValue();
				if(highPeriod < 0){
					txtHighDesired.setValue(new Double(0.08));
				}
			}else if(source == txtLowDesired){
				lowPeriod = ((Number)txtLowDesired.getValue()).doubleValue();
				if(lowPeriod < 0){
					txtLowDesired.setValue(new Double(0.02));
				}
			}
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the configure button 's action.
	 */
	class ButtonConfigureActionListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			if(pwModulatorCtrl.getEnabled()){
				try {
					pwModulatorCtrl.setEnabled(false);
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
			double highPeriod = ((Number)txtHighDesired.getValue()).doubleValue();
			double lowPeriod = ((Number)txtLowDesired.getValue()).doubleValue();
			
			try {
				PulseWidth pulseWidth = new PulseWidth(highPeriod, lowPeriod);
				pwModulatorCtrl.getChannels()[pwModulatorCtrl.getChannelStart()].setPulseWidth(pulseWidth);
				pwModulatorCtrl.setEnabled(true);
			} catch (Exception ex) {
				ShowMessage("Sorry, there're some errors occured: " + ex.toString());
				return;
			}
			
			lblStatus.setEnabled(true);
			txtHighDesired.setEnabled(false);
			txtLowDesired.setEnabled(false);
			
			PulseWidth pulseWidth = pwModulatorCtrl.getChannels()[pwModulatorCtrl.getChannelStart()].getPulseWidth();
			txtHighGenerated.setText(String.valueOf(pulseWidth.HiPeriod));
			txtLowGenerated.setText(String.valueOf(pulseWidth.LoPeriod));
			
			btnStart.setEnabled(false);
			btnConfigure.setEnabled(false);
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
			try {
				pwModulatorCtrl.setEnabled(false);
			} catch (Exception ex) {
				ShowMessage("Sorry, there're some errors occured: " + ex.toString());
				return;
			}
			
			lblStatus.setEnabled(false);
			txtHighDesired.setEnabled(true);
			txtLowDesired.setEnabled(true);
			
			btnConfigure.setEnabled(true);
			btnStart.setEnabled(true);
			btnStop.setEnabled(false);
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
			if (pwModulatorCtrl.getEnabled()) {
				try {
					pwModulatorCtrl.setEnabled(false);
					pwModulatorCtrl.Cleanup();
				} catch (Exception ex) {
					// do nothing here!
					// ShowMessage("Sorry, there're some errors occured: " + ex.toString());
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
}