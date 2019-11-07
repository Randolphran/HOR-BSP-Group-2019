package Counter_BufferedPWMOutput;

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

import javax.swing.border.TitledBorder;
import javax.swing.UIManager;

import java.awt.Color;
import java.text.Format;

public class BufferedPWMOutput extends JFrame {

	/**
	 * define the serialization number.
	 */
	private static final long serialVersionUID = 1L;
	
	private JPanel contentPane;
	private JFormattedTextField data1_txtHigh;
	private JFormattedTextField data1_txtLow;
	private JFormattedTextField data2_txtHigh; 
	private JFormattedTextField data2_txtLow; 
	private JLabel lblStatus;
	private JButton btnConfigure;
	private JButton btnStart;
	private JButton btnStop;
	private boolean [] channelEnable;
	private int intervalCount;
	private int samplesCount;
	private int channelCountMax;
	
	ConfigureParameter configure = new ConfigureParameter();
	private ConfigureDialog configureDialog;
	private BufferedPwModulatorCtrl bfdPwModulatorCtrl = new BufferedPwModulatorCtrl();

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
					BufferedPWMOutput frame = new BufferedPWMOutput();
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
	public BufferedPWMOutput() {
		//add window close event listener.
		addWindowListener(new WindowCloseActionListener());
		
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 427, 474);
		
		contentPane = new JPanel();
		contentPane.setBackground(SystemColor.control);
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(null);
		setContentPane(contentPane);
		
		JPanel panelDesired = new JPanel();
		panelDesired.setBackground(SystemColor.control);
		panelDesired.setBounds(25, 53, 318, 98);
		panelDesired.setBorder(new TitledBorder(null, "Data 1", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panelDesired.setLayout(null);
		contentPane.add(panelDesired);
		
		JLabel lblHighPeriod = new JLabel("High Period:");
		lblHighPeriod.setBounds(29, 30, 80, 15);
		panelDesired.add(lblHighPeriod);
		
		data1_txtHigh = new JFormattedTextField(NumberFormat.getNumberInstance());
		data1_txtHigh.setValue(new Double(0.08));
		data1_txtHigh.setHorizontalAlignment(SwingConstants.RIGHT);
		data1_txtHigh.setBounds(114, 27, 165, 21);
		panelDesired.add(data1_txtHigh);
		data1_txtHigh.setColumns(10);
		
		JLabel lblNewLabel = new JLabel("S");
		lblNewLabel.setBounds(286, 30, 21, 15);
		panelDesired.add(lblNewLabel);
		
		JLabel lblLowPeriod = new JLabel("Low Period:");
		lblLowPeriod.setBounds(29, 61, 80, 15);
		panelDesired.add(lblLowPeriod);
		
		data1_txtLow = new JFormattedTextField(NumberFormat.getNumberInstance());
		data1_txtLow.setValue(new Double(0.02));
		data1_txtLow.setHorizontalAlignment(SwingConstants.RIGHT);
		data1_txtLow.setColumns(10);
		data1_txtLow.setBounds(114, 58, 165, 21);
		panelDesired.add(data1_txtLow);
		
		JLabel label_1 = new JLabel("S");
		label_1.setBounds(286, 61, 21, 15);
		panelDesired.add(label_1);
		
		JPanel panelValue = new JPanel();
		panelValue.setBackground(SystemColor.control);
		panelValue.setBounds(25, 323, 318, 64);
		panelValue.setBorder(BorderFactory.createTitledBorder("Execution Status"));
		panelValue.setLayout(null);
		contentPane.add(panelValue);
		
		lblStatus = new JLabel(new BackgroundPanel("BufferedPwModulatorStatus.gif", "status").getImageIcon());
		lblStatus.setEnabled(false);
		lblStatus.setBounds(36, 32, 241, 15);
		lblStatus.setDisabledIcon(new BackgroundPanel("ExecutionStatus.png", "disable").getImageIcon());
		panelValue.add(lblStatus);
		
		// Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("Background.png", "background image!");
		panel.setBounds(263, 0, 160, 50);
		panel.setBackground(SystemColor.control);
		panel.setLayout(null);
		contentPane.add(panel);
		
		btnConfigure = new JButton("Configure");
		btnConfigure.setBounds(35, 397, 93, 28);
		btnConfigure.addActionListener(new ButtonConfigureActionListener());
		contentPane.add(btnConfigure);
		
		btnStart = new JButton("Start");
		btnStart.setBounds(165, 397, 80, 28);
		btnStart.addActionListener(new ButtonStartActionListener());
		contentPane.add(btnStart);
		
		btnStop = new JButton("Stop");
		btnStop.setEnabled(false);
		btnStop.setBounds(263, 397, 80, 28);
		btnStop.addActionListener(new ButtonStopActionListener());
		contentPane.add(btnStop);
		
		JPanel panel_2 = new JPanel();
		panel_2.setBorder(new TitledBorder(null, "Data 2", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panel_2.setBounds(25, 161, 318, 105);
		contentPane.add(panel_2);
		panel_2.setLayout(null);
		
		JLabel lblNewLabel_1 = new JLabel("High Period:");
		lblNewLabel_1.setBounds(29, 28, 86, 15);
		panel_2.add(lblNewLabel_1);
		
		JLabel lblNewLabel_2 = new JLabel("Low Period:");
		lblNewLabel_2.setBounds(29, 70, 75, 15);
		panel_2.add(lblNewLabel_2);
		
		JLabel lblNewLabel_3 = new JLabel("S");
		lblNewLabel_3.setBounds(291, 28, 17, 15);
		panel_2.add(lblNewLabel_3);
		
		JLabel lblNewLabel_4 = new JLabel("S");
		lblNewLabel_4.setBounds(291, 70, 17, 15);
		panel_2.add(lblNewLabel_4);
		
		data2_txtHigh = new JFormattedTextField((Format) null);
		data2_txtHigh.setText("0.05");
		data2_txtHigh.setHorizontalAlignment(SwingConstants.RIGHT);
		data2_txtHigh.setColumns(10);
		data2_txtHigh.setBounds(116, 25, 165, 21);
		panel_2.add(data2_txtHigh);
		
		data2_txtLow = new JFormattedTextField((Format) null);
		data2_txtLow.setText("0.05");
		data2_txtLow.setHorizontalAlignment(SwingConstants.RIGHT);
		data2_txtLow.setColumns(10);
		data2_txtLow.setBounds(116, 67, 165, 21);
		panel_2.add(data2_txtLow);
		
		JLabel lblNewLabel_5 = new JLabel("<html><body>Note:The buffer will be filled with<br>Data1 and Data2 in turn.</body><html>");
		lblNewLabel_5.setBounds(67, 276, 230, 37);
		contentPane.add(lblNewLabel_5);
		
		contentPane.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[]{data1_txtHigh, data1_txtLow, btnConfigure, btnStart, btnStop}));
	
		configureDialog = new ConfigureDialog(this);
		configureDialog.setModal(true);
		configureDialog.setVisible(true);

	}
	
	public void CheckDataValiable()
	{
		double highPeriod, lowPeriod;
		
		highPeriod = ((Number)data1_txtHigh.getValue()).doubleValue();
		if(highPeriod <= 0){
			data1_txtHigh.setValue(new Double(0.08));
			data1_txtHigh.setText("0.08");
		}
		
		
		lowPeriod = ((Number)data1_txtLow.getValue()).doubleValue();
		if(lowPeriod <= 0){
			data1_txtLow.setValue(new Double(0.02));
			data1_txtLow.setText("0.02");
		}
		
		
		highPeriod = ((Number)data2_txtHigh.getValue()).doubleValue();
		if(highPeriod <= 0){
			data2_txtHigh.setValue(new Double(0.05));
			data2_txtHigh.setText("0.05");
		}
		
		
		lowPeriod = ((Number)data2_txtLow.getValue()).doubleValue();
		if(lowPeriod <= 0){
			data2_txtLow.setValue(new Double(0.05));
			data2_txtLow.setText("0.05");
		}
		
	}
	/**
	 * 
	 * Build Date:2011-10-12
	 * Author:Administrator
	 * Function Description: This function is used to initialize the main frame.
	 * 
	 */
	public void Initialization() {
		//set the main frame's title.
		setTitle("Buffered PWM Output - Run(" + configure.deviceName.substring(0, configure.deviceName.length() - 1) + ")");
		
		data1_txtHigh.setValue(new Double(0.08));
		data1_txtLow.setValue(new Double(0.02));
		data2_txtHigh.setValue(new Double(0.05));
		data2_txtLow.setValue(new Double(0.05));
		
		try{
			bfdPwModulatorCtrl.setSelectedDevice(new DeviceInformation(configure.deviceName));
			channelCountMax = bfdPwModulatorCtrl.getFeatures().getChannelCountMax();
			channelEnable = new boolean [channelCountMax];
			
			// ConfigureMode: ProfileConfigure / ManualConfigure
			if(configure.configureMode == 1){
				String profilePath = null;
				profilePath = configureDialog.GetProfilePath();
				ErrorCode errorCode = bfdPwModulatorCtrl.LoadProfile(profilePath);
				if(Global.BioFaild(errorCode)){
					ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
					}
				channelEnable = bfdPwModulatorCtrl.getChannelMap();
				samplesCount = bfdPwModulatorCtrl.getSamples();
				bfdPwModulatorCtrl.setChannelMap(channelEnable);
			}else{
				System.arraycopy(configure.channelEnabled, 0, channelEnable, 0, configure.channelEnabled.length);
				// Device General Settings
				bfdPwModulatorCtrl.setChannelMap(configure.channelEnabled);
				bfdPwModulatorCtrl.setSampleClkSrc(configure.sampleClkSrc);
				bfdPwModulatorCtrl.setIntervalCount(configure.intervalCount);
				
				samplesCount = configure.intervalCount * 2;
				bfdPwModulatorCtrl.setSamples(samplesCount);
				bfdPwModulatorCtrl.setStreaming(true);
				
				// Trigger Settings
				Trigger trg = bfdPwModulatorCtrl.getTrigger();
				if(trg != null){
					trg.setSource(configure.triggerSource);
					trg.setAction(configure.triggerAction);
					trg.setEdge(configure.triggerEdge);
					trg.setLevel(configure.triggerLevel);
			    }	
			}
			
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
	 * Class Function Description: This class is used to listen the configure button 's action.
	 */
	class ButtonConfigureActionListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			if(bfdPwModulatorCtrl.getEnabled()){
				try {
					bfdPwModulatorCtrl.setEnabled(false);
				} catch (Exception ex) {
					ShowMessage("Sorry, there're some errors occured: " + ex.toString());
					return;
				}
			}
			configureDialog.LoadConfiguration(configure);
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
			CheckDataValiable();
			double data1_hi = ((Number)data1_txtHigh.getValue()).doubleValue();
			double data1_lo = ((Number)data1_txtLow.getValue()).doubleValue();
			double data0_hi = ((Number)data2_txtHigh.getValue()).doubleValue();
			double data0_lo = ((Number)data2_txtLow.getValue()).doubleValue();
			
			PulseWidth[] dataBuf = new PulseWidth[samplesCount];
			for(int i = 0; i < samplesCount; i++){
				dataBuf[i] = new PulseWidth();
				if((i & 1) == 0){
					dataBuf[i].HiPeriod = data1_hi;
					dataBuf[i].LoPeriod = data1_lo;
				}else{
					dataBuf[i].HiPeriod = data0_hi;
					dataBuf[i].LoPeriod = data0_lo;
				}				
			}
			
			for(int i = 0; i < channelCountMax; i++){
				if(channelEnable[i]){
					bfdPwModulatorCtrl.SetData(i, samplesCount, dataBuf);	
				}
			}
			
			try {
				bfdPwModulatorCtrl.Prepare();
				bfdPwModulatorCtrl.setEnabled(true);
			} catch (Exception ex) {
				ShowMessage("Sorry, there're some errors occured: " + ex.toString());
				return;
			}
			
			lblStatus.setEnabled(true);
			data1_txtHigh.setEnabled(false);
			data1_txtLow.setEnabled(false);
			data2_txtHigh.setEnabled(false);
			data2_txtLow.setEnabled(false);
			
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
				bfdPwModulatorCtrl.setEnabled(false);
			} catch (Exception ex) {
				ShowMessage("Sorry, there're some errors occured: " + ex.toString());
				return;
			}
			
			lblStatus.setEnabled(false);
			data1_txtHigh.setEnabled(true);
			data1_txtLow.setEnabled(true);
			data2_txtHigh.setEnabled(true);
			data2_txtLow.setEnabled(true);
			
			btnConfigure.setEnabled(true);
			btnStart.setEnabled(true);
			btnStop.setEnabled(false);
		}
	}
	
	public class DataReadyEventListener implements BfdCntrEventListener{

		@Override
		public void BfdCntrEvent(Object arg0, BfdCntrEventArgs arg1) {
			// TODO Auto-generated method stub
			
			//Do Nothing Here!
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
			if (bfdPwModulatorCtrl.getEnabled()) {
				try {
					bfdPwModulatorCtrl.setEnabled(false);
					bfdPwModulatorCtrl.Cleanup();
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
	public int channelStart;
	public int channelCount;
	public int intervalCount;
	public SignalDrop sampleClkSrc;
	
	public SignalDrop triggerSource;
	public TriggerAction triggerAction;	
	public ActiveSignal triggerEdge;
	public double triggerLevel;
	
	public boolean[] channelEnabled;
	public int configureMode; //load profile --> 1  /  manual configure --> 0
	
}