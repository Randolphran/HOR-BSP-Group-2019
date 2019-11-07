package Counter_DelayedPulseGeneration;

import java.awt.EventQueue;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.SystemColor;
import java.text.NumberFormat;

import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.JButton;
import javax.swing.SwingConstants;

import Automation.BDaq.*;
import Common.Global;

import org.eclipse.wb.swing.FocusTraversalOnArray;

import java.awt.Component;

public class DelayPulseGeneration extends JFrame {
	// define the serialization number.
	private static final long serialVersionUID = 1L;
	
	private JPanel contentPane;
	private JFormattedTextField txtClockCount;
	private JTextField txtShotCount;
	private JLabel lblStatus;
	private JButton btnConfigure;
	private JButton btnStart;
	private JButton btnStop;
	private JLabel lblExecutionStatus;
	
	ConfigureParameter configure = new ConfigureParameter();
	private ConfigureDialog configureDialog;
	private OneShotCtrl oneShotCtrl = new OneShotCtrl();
	private int countOfValue = 0;	
	private int delayCount = 1000;

	/**
	 * 
	 * Build Date:2011-10-08 
	 * Author:Administrator
	 * Function Description: Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					DelayPulseGeneration frame = new DelayPulseGeneration();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * 
	 * Build Date:2011-10-08 
	 * Author:Administrator
	 * Function Description: Create the frame.
	 */
	public DelayPulseGeneration() {
		//add window closing action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 398, 271);
		contentPane = new JPanel();
		contentPane.setBackground(SystemColor.control);
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JPanel panelValue = new JPanel();
		panelValue.setBackground(SystemColor.control);
		panelValue.setBounds(22, 46, 256, 80);
		panelValue.setBorder(BorderFactory.createTitledBorder(""));
		contentPane.add(panelValue);
		panelValue.setLayout(null);
		
		JLabel lblClockCount = new JLabel("Delay count:");
		lblClockCount.setBounds(10, 15, 123, 15);
		panelValue.add(lblClockCount);
		
		JLabel lblShotCount = new JLabel("DelayedPulse count:");
		lblShotCount.setBounds(10, 50, 123, 15);
		panelValue.add(lblShotCount);
		
		txtClockCount = new JFormattedTextField(NumberFormat.getIntegerInstance());
		txtClockCount.setValue(new Integer(1000));
		txtClockCount.setHorizontalAlignment(SwingConstants.RIGHT);
		txtClockCount.setBounds(133, 12, 104, 21);
		panelValue.add(txtClockCount);
		txtClockCount.setColumns(10);
		
		txtShotCount = new JTextField();
		txtShotCount.setText("0");
		txtShotCount.setHorizontalAlignment(SwingConstants.RIGHT);
		txtShotCount.setEditable(false);
		txtShotCount.setColumns(10);
		txtShotCount.setBounds(133, 47, 104, 21);
		panelValue.add(txtShotCount);

		//Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("Background.png", "background image!");
		panel.setBounds(168, 0, 224, 127);
		panel.setBackground(SystemColor.control);
		panel.setLayout(null);
		contentPane.add(panel);

		btnConfigure = new JButton("Configure...");
		btnConfigure.setBounds(65, 192, 115, 23);
		btnConfigure.addActionListener(new ButtonConfigureActionListener());
		contentPane.add(btnConfigure);

		btnStart = new JButton("Start");
		btnStart.addActionListener(new ButtonStartActionListener());
		btnStart.setBounds(198, 192, 80, 23);
		contentPane.add(btnStart);

		btnStop = new JButton("Stop");
		btnStop.setBounds(292, 192, 80, 23);
		btnStop.setEnabled(false);
		btnStop.addActionListener(new ButtonStopActionListener());
		contentPane.add(btnStop);

		lblExecutionStatus = new JLabel("Execution status:");
		lblExecutionStatus.setBounds(32, 148, 112, 15);
		contentPane.add(lblExecutionStatus);
		
		lblStatus = new JLabel(new BackgroundPanel("OneShotStatus.gif", "status").getImageIcon());
		lblStatus.setBounds(144, 148, 238, 15);
		contentPane.add(lblStatus);
		lblStatus.setDisabledIcon(new BackgroundPanel("ExecutionStatus.png", "stop").getImageIcon());
		lblStatus.setEnabled(false);
		contentPane.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[]{
				txtClockCount, btnConfigure, btnStart, btnStop}));
		
		//Caution: When OneShot interrupt is too frequent, the operating system may hang.
		//The following is the suggestion:
		//1.If you generate delayed pulse only, you don't need to deal with OneShot event.
		//2.If you want to use OneShot interrupt function, uncomment the following codes.
		
		//oneShotCtrl.addOneShotListener(new OneShotEventListener());
		
		configureDialog = new ConfigureDialog(this);
		configureDialog.setModal(true);
		configureDialog.setVisible(true);
	}
	
	/**
	 * 
	 * Build Date:2011-10-08 
	 * Author:Administrator
	 * Function Description: This function is used to initialize the main frame.
	 */
	public void Initialization() {
		//set the main frame's title.
		this.setTitle("Delay Pulse Generation - Run(" + configure.deviceName.substring(0, configure.deviceName.length() - 1) + ")");
		try{
			oneShotCtrl.setSelectedDevice(new DeviceInformation(configure.deviceName));
			String profilePath = null;
			profilePath = configureDialog.GetProfilePath();
			ErrorCode errorCode = oneShotCtrl.LoadProfile(profilePath);
			if(Global.BioFaild(errorCode)){
				ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
				}
			oneShotCtrl.setChannelCount(1);
			oneShotCtrl.setChannelStart(configure.counterChannel);
		}catch(Exception ex){
			ShowMessage("Sorry, there're some errors occurred: " + ex.getMessage());
		}
	}
	
	/**
	 * 
	 * Build Date:2011-10-08 
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
	 * Class Function Description: This class is used to listen the one shot event.
	 */
	class OneShotEventListener implements CntrEventListener{

		public void CntrEvent(Object sender, CntrEventArgs args) {
			txtShotCount.setText(String.valueOf(countOfValue++));
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the start button 's action.
	 */
	class ButtonStartActionListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			long delay = ((Number)txtClockCount.getValue()).intValue();
			MathInterval range = oneShotCtrl.getFeatures().getOsDelayCountRange();
			if(delay < range.Min || delay > range.Max){
				ShowMessage("please input number between " + range.Min + " and " + range.Max
						+ " in delay count");
				return;
			}
			
			delayCount = ((Number)txtClockCount.getValue()).intValue();
			try{
				oneShotCtrl.getChannels()[oneShotCtrl.getChannelStart()].setDelayCount(delayCount);
				oneShotCtrl.setEnabled(true);
			}catch(Exception ex){
				ShowMessage("Sorry, there're some errors occured: " + ex.getMessage());
				return;
			}
			
			lblStatus.setEnabled(true);
			txtClockCount.setEnabled(false);
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
			countOfValue = 0;
			try {
				oneShotCtrl.setEnabled(false);
			} catch (Exception ex) {
				ShowMessage("Sorry, there're some errors occured: " + ex.toString());
				return;
			}
		
			txtShotCount.setText(String.valueOf(countOfValue));
			
			lblStatus.setEnabled(false);
			txtClockCount.setEnabled(true);
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

			if(oneShotCtrl.getEnabled()){
				try {
					oneShotCtrl.setEnabled(false);
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
			if (oneShotCtrl.getEnabled()) {
				try {
					oneShotCtrl.setEnabled(false);
					oneShotCtrl.Cleanup();
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

