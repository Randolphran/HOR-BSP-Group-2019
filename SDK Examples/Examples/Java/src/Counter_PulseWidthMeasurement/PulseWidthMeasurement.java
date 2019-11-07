package Counter_PulseWidthMeasurement;

import java.awt.Color;
import java.awt.Component;
import java.awt.EventQueue;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.math.BigDecimal;
import javax.swing.BorderFactory;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.ListCellRenderer;
import javax.swing.ListSelectionModel;
import javax.swing.SwingConstants;
import javax.swing.Timer;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;

import org.eclipse.wb.swing.FocusTraversalOnArray;

import Automation.BDaq.DeviceInformation;
import Automation.BDaq.ErrorCode;
import Automation.BDaq.PulseWidth;
import Automation.BDaq.PwMeterCtrl;
import Common.Global;

public class PulseWidthMeasurement extends JFrame implements ActionListener{

	/**
	 * define the serialization number.
	 */
	private static final long serialVersionUID = 1L;
	
	private JPanel contentPane;
	private JTextField txtHigh;
	private JTextField txtLow;
	private JList lstValue;
	private DefaultListModel model = new DefaultListModel();
	private JButton btnStart;
	private JButton btnStop;
	private JButton btnConfigure;
	
	private final int MAX_ROW_COUNT = 8;
	
	ConfigureParameter configure = new ConfigureParameter();
	private ConfigureDialog configureDialog;
	private PwMeterCtrl pwMeterCtrl = new PwMeterCtrl(); 
	private Timer timer;
	private int countOfValue = 0;

	/**
	 * 
	 * Build Date:2011-10-11
	 * Author:Administrator
	 * Function Description: Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					PulseWidthMeasurement frame = new PulseWidthMeasurement();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * 
	 * Build Date:2011-10-11
	 * Author:Administrator
	 * Function Description: Create the frame.
	 */
	public PulseWidthMeasurement() {
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 441, 391);
		contentPane = new JPanel();
		contentPane.setBackground(SystemColor.control);
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JPanel panelValue = new JPanel();
		panelValue.setBackground(SystemColor.control);
		panelValue.setBounds(21, 45, 267, 299);
		panelValue.setBorder(BorderFactory.createTitledBorder(""));
		contentPane.add(panelValue);
		panelValue.setLayout(null);
		
		JLabel lblHighPeriod = new JLabel("High Period:");
		lblHighPeriod.setBounds(15, 13, 72, 15);
		panelValue.add(lblHighPeriod);
		
		JLabel lblLowPeriod = new JLabel("Low Period:");
		lblLowPeriod.setBounds(15, 50, 72, 15);
		panelValue.add(lblLowPeriod);
		
		lstValue = new JList();
		lstValue.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		lstValue.setBackground(SystemColor.controlHighlight);
		lstValue.setBorder(new LineBorder(new Color(0, 0, 0)));
		lstValue.setAlignmentX(Component.RIGHT_ALIGNMENT);
		lstValue.setFixedCellHeight(25);
		lstValue.setBounds(15, 85, 235, 200);
		panelValue.add(lstValue);
		
		txtHigh = new JTextField();
		txtHigh.setHorizontalAlignment(SwingConstants.RIGHT);
		txtHigh.setEditable(false);
		txtHigh.setBounds(88, 10, 137, 21);
		panelValue.add(txtHigh);
		txtHigh.setColumns(10);
		
		JLabel lblS = new JLabel("S");
		lblS.setBounds(230, 13, 20, 15);
		panelValue.add(lblS);
		
		JLabel label = new JLabel("S");
		label.setBounds(230, 50, 20, 15);
		panelValue.add(label);
		
		txtLow = new JTextField();
		txtLow.setHorizontalAlignment(SwingConstants.RIGHT);
		txtLow.setEditable(false);
		txtLow.setColumns(10);
		txtLow.setBounds(88, 47, 137, 21);
		panelValue.add(txtLow);
		
		btnStart = new JButton("Start");
		btnStart.setBounds(312, 209, 93, 23);
		btnStart.addActionListener(new ButtonStartActionListener());
		contentPane.add(btnStart);
		
		btnStop = new JButton("Stop");
		btnStop.setEnabled(false);
		btnStop.setBounds(312, 253, 93, 23);
		btnStop.addActionListener(new ButtonStopActionListener());
		contentPane.add(btnStop);
		
		btnConfigure = new JButton("Configure");
		btnConfigure.setBounds(298, 299, 127, 23);
		btnConfigure.addActionListener(new ButtonConfigureActionListener());
		contentPane.add(btnConfigure);
		
		//Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("Background.png", "background image!");
		panel.setBounds(265, 0, 170, 59);
		panel.setBackground(SystemColor.control);
		panel.setLayout(null);
		contentPane.add(panel);
		contentPane.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[]{
				btnStart, btnStop, btnConfigure}));
		
		configureDialog = new ConfigureDialog(this);
		configureDialog.setModal(true);
		configureDialog.setVisible(true);
	}
	
	/**
	 * 
	 * Build Date:2011-10-11
	 * Author:Administrator
	 * Function Description: This function is used to initialize the main frame.
	 */
	public void Initialization() {
		//set the main frame's title.
		setTitle("Pulse Width Measurement - Run(" + configure.deviceName.substring(0, configure.deviceName.length() - 1) + ")");
		
		//String array channelValues contents of the current channels' data in each channel.
		String[] channelValues = new String[8];
		model.removeAllElements();
		for (int i = 0; i < channelValues.length; i++) {
			channelValues[i] = "";
			model.addElement(channelValues[i]);
		}
		lstValue.setModel(model);
		lstValue.setBorder(new LineBorder(new Color(0, 0, 0)));
		lstValue.setCellRenderer(new ListViewCellRenderer());
		lstValue.setVisible(true);
		
		try{
			pwMeterCtrl.setSelectedDevice(new DeviceInformation(configure.deviceName));
			String profilePath = null;
			profilePath = configureDialog.GetProfilePath();
			ErrorCode errorCode = pwMeterCtrl.LoadProfile(profilePath);
			if(Global.BioFaild(errorCode)){
				ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
				}
			pwMeterCtrl.setChannelCount(1);
			pwMeterCtrl.setChannelStart(configure.counterChannel);
		}catch(Exception ex){
			ShowMessage("Sorry, there're some errors occurred: " + ex.getMessage());
		}
	}
	
	/**
	 * 
	 * Build Date:2011-10-11 
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
	 * Build Date:2011-10-11
	 * Author:Administrator
	 * Function Description: This function is overload the interface ActionListener,and 
	 * 						 is implementation need this function!
	 */
	public void actionPerformed(ActionEvent e) {
		try{
			PulseWidth currentValue = new PulseWidth(0, 0);
			pwMeterCtrl.Read(currentValue);
			BigDecimal valueHigh = new BigDecimal(currentValue.HiPeriod);
			BigDecimal valueLow = new BigDecimal(currentValue.LoPeriod);
			currentValue.HiPeriod = valueHigh.setScale(6, BigDecimal.ROUND_HALF_UP).doubleValue();
			currentValue.LoPeriod = valueLow.setScale(6, BigDecimal.ROUND_HALF_UP).doubleValue();
			txtHigh.setText(String.valueOf((float)currentValue.HiPeriod));
			txtLow.setText(String.valueOf((float)currentValue.LoPeriod));
		}catch(Exception ex){
			timer.stop();
			ShowMessage("Sorry, there're some errors occured: " + ex.toString());
		}
	}
	
	/**
	 * 
	 * Build Date:2011-10-11 
	 * Author:Administrator
	 * Function Description: This function is used to start the timer.
	 */
	private void Start() {
		if (timer == null) {
			timer = new Timer(100, this);
		}
		timer.start();
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the start button 's action.
	 */
	class ButtonStartActionListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			if(btnStart.getText() == "Start"){
				Start();
				try {
					pwMeterCtrl.setEnabled(true);
				} catch (Exception ex) {
					timer.stop();
					ShowMessage("Sorry, there're some errors occured: " + ex.toString());
					return;
				}
				
				for(int i = 0; i < model.getSize(); i++){
					model.set(i, "");
				}
				countOfValue = 0;
				
				btnStart.setText("Latch");
				btnConfigure.setEnabled(false);
				btnStop.setEnabled(true);
			}else if(btnStart.getText() == "Latch"){
				if(countOfValue < MAX_ROW_COUNT){
					model.set(countOfValue, "High: " + txtHigh.getText() + "   Low: " + txtLow.getText());
					countOfValue++;
				}else{
					model.remove(0);
					model.addElement("High: " + txtHigh.getText() + "   Low: " + txtLow.getText());
				}
			}
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
				pwMeterCtrl.setEnabled(false);
			} catch (Exception ex) {
				ShowMessage("Sorry, there're some errors occured: " + ex.toString());
				return;
			}
			
			btnStart.setText("Start");
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
			if(timer == null){
				Start();
			}
			timer.stop();
			if(pwMeterCtrl.getEnabled()){
				try {
					pwMeterCtrl.setEnabled(false);
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
	 * Class Function Description: this class is use to draw each cell of the JList object
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

				setHorizontalAlignment(SwingConstants.CENTER);
				setBackground(SystemColor.controlHighlight);
				setOpaque(true);
			}
			return this;
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
			if (pwMeterCtrl.getEnabled()) {
				try {
					pwMeterCtrl.setEnabled(false);
					pwMeterCtrl.Cleanup();
				} catch (Exception ex) {
					// do nothing here!
					// ShowMessage("Sorry, there're some errors occured: " + ex.toString());
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
