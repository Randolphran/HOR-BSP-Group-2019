package Counter_EventCounter;

import java.awt.Component;
import java.awt.EventQueue;
import java.awt.SystemColor;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.BorderFactory;
import javax.swing.DefaultListModel;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.JList;
import javax.swing.ListCellRenderer;
import javax.swing.ListSelectionModel;
import javax.swing.Timer;
import javax.swing.border.Border;
import javax.swing.border.LineBorder;
import javax.swing.SwingConstants;
import javax.swing.JButton;

import Automation.BDaq.*;
import Common.Global;

import org.eclipse.wb.swing.FocusTraversalOnArray;
import javax.swing.JTable;
import javax.swing.JTextArea;

public class EventCounter extends JFrame implements ActionListener{
	// define the serialization number.
	private static final long serialVersionUID = 1L;
	
	private JPanel contentPane;
	private JTextField txtCounterValue;
	private JList lstCounterValue;
	private DefaultListModel model = new DefaultListModel();
	private JButton btnStart;
	private JButton btnStop;
	private JButton btnConfigure;
	
	private final int MAX_ROW_COUNT = 8;
	
	ConfigureParameter configure = new ConfigureParameter();
	private ConfigureDialog configureDialog;
	private EventCounterCtrl eventCounterCtrl = new EventCounterCtrl();
	private Timer timer;
	private int countOfValue = 0;	
	private int currentCounterValue = 0;
	
	/**
	 * 
	 * Build Date:2011-9-29 
	 * Author:Administrator
	 * Function Description: Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					EventCounter frame = new EventCounter();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * 
	 * Build Date:2011-9-29 
	 * Author:Administrator
	 * Function Description: Create the frame.
	 */
	public EventCounter() {
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 396, 377);
		addWindowListener(new WindowCloseActionListener());
		
		contentPane = new JPanel();
		contentPane.setBackground(SystemColor.control);
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		txtCounterValue = new JTextField();
		txtCounterValue.setText("0");
		txtCounterValue.setHorizontalAlignment(SwingConstants.RIGHT);
		txtCounterValue.setEditable(false);
		txtCounterValue.setBounds(25, 43, 229, 21);
		contentPane.add(txtCounterValue);
		txtCounterValue.setColumns(10);
		
		lstCounterValue = new JList();
		lstCounterValue.setBackground(SystemColor.controlHighlight);
		lstCounterValue.setBorder(new LineBorder(new Color(0, 0, 0)));
		lstCounterValue.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		lstCounterValue.setBounds(25, 94, 230, 226);
		lstCounterValue.setAlignmentX(Component.RIGHT_ALIGNMENT);
		lstCounterValue.setFixedCellHeight(28);
		contentPane.add(lstCounterValue);
		
		btnStart = new JButton("Start");
		btnStart.setBounds(277, 165, 90, 23);
		btnStart.addActionListener(new ButtonStartActionListener());
		contentPane.add(btnStart);
		
		btnStop = new JButton("Stop");
		btnStop.setBounds(277, 205, 90, 23);
		btnStop.addActionListener(new ButtonStopActionListener());
		btnStop.setEnabled(false);
		contentPane.add(btnStop);
		
		btnConfigure = new JButton("Configure");
		btnConfigure.setBounds(265, 268, 115, 23);
		btnConfigure.addActionListener(new ButtonConfigureActionListener());
		contentPane.add(btnConfigure);
		
		// Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("Background.png", "background image!");
		panel.setBounds(215, 0, 175, 64);
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
	 * Build Date:2011-9-29 
	 * Author:Administrator
	 * Function Description: This function is used to initialize the main frame.
	 */
	public void Initialization() {

		//String array channelValues contents of the current channels' data in each channel.
		String[] channelValues = new String[8];

		//set the main frame's title.
		this.setTitle("Event Counter - Run(" + configure.deviceName.substring(0, configure.deviceName.length() - 1) + ")");
		
		model.removeAllElements();
		for (int i = 0; i < channelValues.length; i++) {
			channelValues[i] = "";
			model.addElement(channelValues[i]);
		}
		lstCounterValue.setModel(model);
		lstCounterValue.setBorder(new LineBorder(new Color(0, 0, 0)));
		lstCounterValue.setCellRenderer(new ListViewCellRenderer());
		lstCounterValue.setVisible(true);
		
		ConfigureDevice();
	}
	
	/**
	 * 
	 *Build Date:2011-9-29
	 *Author:Administrator
	 *Function Description: This function is used to configure the event counter device.
	 */
	private void ConfigureDevice(){
		try{
			eventCounterCtrl.setSelectedDevice(new DeviceInformation(configure.deviceName));
			String profilePath = null;
			profilePath = configureDialog.GetProfilePath();
			ErrorCode errorCode = eventCounterCtrl.LoadProfile(profilePath);
			if(Global.BioFaild(errorCode)){
				ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
				}
			eventCounterCtrl.setChannelCount(1);
			eventCounterCtrl.setChannelStart(configure.counterChannel);
			eventCounterCtrl.setEnabled(true);
		}catch(Exception ex){
			ShowMessage("Sorry, there're some errors occured: " + ex.toString());
		}
	}
	
	/**
	 * 
	 * Build Date:2011-9-29 
	 * Author:Administrator
	 * Function Description: This function is used to start the timer.
	 */
	private void Start() {
		if (timer == null) {
			timer = new Timer(50, this);
		}
		timer.start();
	}
	
	/**
	 * 
	 * Build Date:2011-9-29 
	 * Author:Administrator
	 * Function Description: This function is overload the interface ActionListener,and 
	 * 						 is implementation need this function!
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		int[] x = {0}; 
		eventCounterCtrl.Read(1, x);
		currentCounterValue = x[0];
		txtCounterValue.setText(String.valueOf(currentCounterValue));
	}
	
	/**
	 * 
	 * Build Date:2011-9-29 
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

				setHorizontalAlignment(SwingConstants.RIGHT);
				setBackground(SystemColor.controlHighlight);
				setOpaque(true);
			}
			return this;
		}
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
					eventCounterCtrl.setEnabled(true);
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
					model.set(countOfValue, String.valueOf(currentCounterValue));
					countOfValue++;
				}else{
					model.remove(0);
					model.addElement(String.valueOf(currentCounterValue));
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
				eventCounterCtrl.setEnabled(false);
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
			
			if(eventCounterCtrl.getEnabled()){
				try {
					eventCounterCtrl.setEnabled(false);
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
			if (eventCounterCtrl.getEnabled()) {
				try {
					eventCounterCtrl.setEnabled(false);
					eventCounterCtrl.Cleanup();
				} catch (Exception ex) {
					// do nothing here.
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
