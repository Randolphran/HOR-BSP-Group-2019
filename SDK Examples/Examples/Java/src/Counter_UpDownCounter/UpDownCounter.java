package Counter_UpDownCounter;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import Automation.BDaq.*;
import Common.ClassLoaderUtil;
import Common.Global;

import javax.swing.border.TitledBorder;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.JList;
import javax.swing.border.LineBorder;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.ButtonGroup;
import javax.swing.DefaultListModel;
import javax.swing.JOptionPane;
import javax.swing.ListSelectionModel;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JComboBox;
import javax.swing.JRadioButton;
import javax.swing.Timer;

import java.awt.Component;
import java.net.MalformedURLException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

@SuppressWarnings("unused")
public class UpDownCounter extends JFrame implements ActionListener {

	/**
	 * define the serialization number.
	 */
	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	
	private JTextField txtCounterValue;
	private JTextField txtResetValue;
	private JTextField txtResetTimes;
	private JList CounterValueList;
	private JButton btnStart;
	private JButton btnStop;
	private JButton btnConfig;
	private JButton btnValReset;
	private JComboBox cmbResetValue;
	private JRadioButton radDisable;
	private JRadioButton raInfinite;
	private JRadioButton radFinite;
	private ButtonGroup buttonGroup = new ButtonGroup();
	private DefaultListModel model = new DefaultListModel();
	
	ConfigureParameter configure = new ConfigureParameter();
	private ConfigureDialog configureDialog;
	
	private UdCounterCtrl udCounterCtrl = new UdCounterCtrl();
	
	private CmbResetValueChangedListener cmbRstValueListener = new CmbResetValueChangedListener();
	
	private Timer timer;
	int cntrValue;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					UpDownCounter frame = new UpDownCounter();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public UpDownCounter() {
		setTitle("Counter_UpDownCounter");
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 533, 342);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		addWindowListener(new WindowCloseActionListener());
		
		// Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("Background.png", "Background Image");
		panel.setBounds(0, 0, 527, 310);
		contentPane.add(panel);
		panel.setLayout(null);
		
		JPanel panel_1 = new JPanel();
		panel_1.setLayout(null);
		panel_1.setBorder(new TitledBorder(null, "", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panel_1.setBounds(207, 42, 310, 245);
		panel.add(panel_1);
		
		txtCounterValue = new JTextField();
		txtCounterValue.setHorizontalAlignment(SwingConstants.LEFT);
		txtCounterValue.setColumns(10);
		txtCounterValue.setBounds(10, 11, 169, 27);
		panel_1.add(txtCounterValue);
		
		CounterValueList = new JList();
		CounterValueList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		CounterValueList.setBorder(new LineBorder(new Color(0, 0, 0)));
		CounterValueList.setBounds(10, 49, 169, 183);
		CounterValueList.setModel(model);
		panel_1.add(CounterValueList);
		
		btnStart = new JButton("Start");
		btnStart.setBounds(204, 28, 79, 23);
		btnStart.addActionListener(new ButtonStartActionListener());
		panel_1.add(btnStart);
		
		btnStop = new JButton("Stop");
		btnStop.setBounds(204, 62, 79, 23);
		btnStop.addActionListener(new ButtonStopActionListener());
		panel_1.add(btnStop);
		
		btnConfig = new JButton("Configure");
		btnConfig.setBounds(204, 177, 79, 23);
		btnConfig.addActionListener(new ButtonConfigureActionListener());
		panel_1.add(btnConfig);
		
		btnValReset = new JButton("ValueReset");
		btnValReset.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				udCounterCtrl.ValueReset();
			}
		});
		btnValReset.setBounds(204, 112, 87, 23);
		panel_1.add(btnValReset);
		
		JPanel panel_2 = new JPanel();
		panel_2.setBorder(new TitledBorder(null, "Reset Value", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panel_2.setBounds(10, 36, 187, 85);
		panel.add(panel_2);
		panel_2.setLayout(null);
		
		JLabel lblNewLabel = new JLabel("Reset Value:");
		lblNewLabel.setBounds(10, 23, 61, 14);
		panel_2.add(lblNewLabel);
		
		cmbResetValue = new JComboBox();
		cmbResetValue.setBounds(79, 18, 98, 24);
		cmbResetValue.addItemListener(cmbRstValueListener);
		panel_2.add(cmbResetValue);
		
		txtResetValue = new JTextField();
		txtResetValue.setHorizontalAlignment(SwingConstants.RIGHT);
		txtResetValue.setEnabled(false);
		txtResetValue.setBounds(79, 50, 98, 24);
		panel_2.add(txtResetValue);
		txtResetValue.setColumns(10);
		
		JPanel panel_3 = new JPanel();
		panel_3.setBorder(new TitledBorder(null, "Index Reset", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panel_3.setBounds(10, 132, 187, 155);
		panel.add(panel_3);
		panel_3.setLayout(null);
		
		radDisable = new JRadioButton("Disable");
		radDisable.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
				if (radDisable.isSelected()) {
					txtResetTimes.setEnabled(false);
				}
			}
		});
		radDisable.setBounds(16, 23, 109, 23);
		panel_3.add(radDisable);
		
		raInfinite = new JRadioButton("Infinite");
		raInfinite.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
				if (raInfinite.isSelected()) {
					txtResetTimes.setEnabled(false);
				}
			}
		});
		raInfinite.setBounds(16, 49, 109, 23);
		panel_3.add(raInfinite);
		
		radFinite = new JRadioButton("Finite");
		radFinite.setFocusCycleRoot(true);
		radFinite.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
				if (radFinite.isSelected()) {
					txtResetTimes.setEnabled(true);
					txtResetTimes.setText("1");
					
					try {
						udCounterCtrl.getChannels()[udCounterCtrl.getChannelStart()].setResetTimesByIndex(1);
					} catch (Exception ex) {
						ShowMessage("Sorry, there're some errors occured: " + ex.toString());
					}
				}
			}
		});
		radFinite.setBounds(16, 75, 109, 23);
		panel_3.add(radFinite);
		
		JLabel lblNewLabel_1 = new JLabel("Reset Times:");
		lblNewLabel_1.setBounds(23, 115, 62, 14);
		panel_3.add(lblNewLabel_1);
		
		txtResetTimes = new JTextField();
		txtResetTimes.setEnabled(false);
		txtResetTimes.setHorizontalAlignment(SwingConstants.RIGHT);
		txtResetTimes.setBounds(91, 112, 86, 26);
		panel_3.add(txtResetTimes);
		txtResetTimes.setColumns(10);
		
		buttonGroup.add(radDisable);
		buttonGroup.add(raInfinite);
		buttonGroup.add(radFinite);
		
		configureDialog = new ConfigureDialog(this);
		configureDialog.setModal(true);
		configureDialog.setVisible(true);
	}
	
	public void Initialization() {
		//set the main frame's title.
		this.setTitle("UpDown Counter - Run(" + configure.deviceName.substring(0, configure.deviceName.length() - 1) + ")");
		
		ConfigureDevice();
		
		model.removeAllElements();
		
		cmbResetValue.removeItemListener(cmbRstValueListener);
		ConfiguratePanel();
		cmbResetValue.addItemListener(cmbRstValueListener);
		
		btnStart.setEnabled(true);
		btnStop.setEnabled(false);
		btnConfig.setEnabled(true);
		btnValReset.setEnabled(false);	
	}
	
	public void ConfigureDevice() {
		try {
			udCounterCtrl.setSelectedDevice(new DeviceInformation(configure.deviceName));
			String profilePath = null;
			profilePath = configureDialog.GetProfilePath();
			ErrorCode errorCode = udCounterCtrl.LoadProfile(profilePath);
			if(Global.BioFaild(errorCode)){
				ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
				}
			udCounterCtrl.setChannelCount(1);
			udCounterCtrl.setChannelStart(configure.counterChannel);
			udCounterCtrl.getChannels()[udCounterCtrl.getChannelStart()].setCountingType(configure.cntType);
		} catch(Exception ex) {
			ShowMessage("Sorry, there're some errors occured: " + ex.toString());
		}
	}
	
	public void ConfiguratePanel() {
		cmbResetValue.removeAllItems();
		
		//for reset value
		int[] resetValues = udCounterCtrl.getFeatures().getUdInitialValues();
		int valueCount = resetValues.length;
		
		int i = 0;
		for (; i < valueCount; i++) {
			if (resetValues[i] != -1) {
				int strLength = Integer.toHexString(resetValues[i]).length();
				if (strLength >= 9) {
					cmbResetValue.addItem("0x" + Integer.toHexString(resetValues[i]).substring(strLength - 9, strLength - 1));
				} else {
					cmbResetValue.addItem("0x" + Integer.toHexString(resetValues[i]));
				}
			} else {
				cmbResetValue.addItem(String.valueOf(-1));
			}
		}
		if (i == 0) {
			cmbResetValue.setSelectedIndex(0);
		}
		
		//for using edit text as reset value
		txtResetValue.setText(Integer.toHexString(0));
		
		//radio button for reset value.
		radDisable.setSelected(true);
		raInfinite.setSelected(false);
		radFinite.setSelected(false);
		
		//reset times
		txtResetTimes.setText("0");
		txtResetTimes.setEnabled(false); 
	}
	
	protected void ShowMessage(String message) {
		JOptionPane.showMessageDialog(this, message, "Warning MessageBox", JOptionPane.WARNING_MESSAGE);
	}
	
	private void Start() {
		if (timer == null) {
			timer = new Timer(50, this);
		}
		timer.start();
	}
	
	//the timer handler
	public void actionPerformed(ActionEvent e) {
		try {
			udCounterCtrl.setEnabled(true);
			int[] x = {0};
			udCounterCtrl.Read(1, x);
			cntrValue = x[0];
			txtCounterValue.setText("0x" + Integer.toHexString(cntrValue));
		} catch (Exception ex) {
			ShowMessage("Sorry, there're some errors occured: " + ex.toString());
		}
	}
	
	public boolean isNum(String str) {
		Pattern pattern = Pattern.compile("[0-9]*"); 
		Matcher num = pattern.matcher(str);

		if (num.matches()) {
			return true;
		}
		return false;
	}
	
	class ButtonStartActionListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			txtCounterValue.setText("0");
			
			try {
				if (btnStart.getText().equals("Start")) {
					model.removeAllElements();
					
					//Set reset times for counter value
					int resetTimes = 0;
					
					if (radFinite.isSelected()) {
						try {
							resetTimes = Integer.valueOf(txtResetTimes.getText());
						} catch (Exception ex) {
							ShowMessage("Sorry, there're some errors occured: " + ex.toString());
							txtResetValue.setText("");
							return;
						}	
					} else if (raInfinite.isSelected()) {
						resetTimes = -1;
					} else if (radDisable.isSelected()) {
						resetTimes = 0;
					}
					
					udCounterCtrl.getChannels()[udCounterCtrl.getChannelStart()].setResetTimesByIndex(resetTimes);
					
					//set reset value
					int[] resetValues = udCounterCtrl.getFeatures().getUdInitialValues();
					int resetValue = resetValues[cmbResetValue.getSelectedIndex()];
					if (resetValue == -1) {
						try {
							resetValue = Integer.valueOf(txtResetValue.getText());
						} catch (Exception ex) {
							ShowMessage("Sorry, there're some errors occured: " + ex.toString());
							txtResetValue.setText("");
							return;
						}
					}
					
					udCounterCtrl.getChannels()[udCounterCtrl.getChannelStart()].setInitialValue(resetValue);
					
					//Start UpDown Counter function.
					udCounterCtrl.setEnabled(true);
					
					Start();
					
					btnStop.setEnabled(true);
					btnConfig.setEnabled(false);
					btnValReset.setEnabled(true);

					cmbResetValue.setEnabled(false);
					radDisable.setEnabled(false);
					radFinite.setEnabled(false);
					raInfinite.setEnabled(false);
					
					btnStart.setText("Latch");
				} else {
					if (model.size() > 8) {
						model.remove(0);
					}
					model.addElement("0x" + Integer.toHexString(cntrValue));
				}
				
			} catch (Exception ex) {
				ShowMessage("Sorry, there're some errors occured: " + ex.toString());
			}
		}
	}
	
	class ButtonStopActionListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			//Stop the user Timer
			timer.stop();
			
			btnStart.setText("Start");
			btnStop.setEnabled(false);
			btnConfig.setEnabled(true);
			btnValReset.setEnabled(false);

			cmbResetValue.setEnabled(true);
			radDisable.setEnabled(true);
			radFinite.setEnabled(true);
			raInfinite.setEnabled(true);
			
			try {
				udCounterCtrl.setEnabled(false);
			} catch (Exception ex) {
				ShowMessage("Sorry, there're some errors occured: " + ex.toString());
			}
		}
	}
	
	class ButtonConfigureActionListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			configureDialog.isFirstLoad = false;
			configureDialog.setVisible(true);
		}
	}
	
	class WindowCloseActionListener extends WindowAdapter{
		@Override
		public void windowClosing(WindowEvent e) {
			if (udCounterCtrl.getEnabled()) {
				try {
					udCounterCtrl.setEnabled(false);
					udCounterCtrl.Cleanup();
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
	
	class CmbResetValueChangedListener implements ItemListener {

		@Override
		public void itemStateChanged(ItemEvent e) {
			int[] resetValues = udCounterCtrl.getFeatures().getUdInitialValues();
			int resetValue = resetValues[cmbResetValue.getSelectedIndex()];
			if (resetValue == -1) {
				txtResetValue.setEnabled(true);
			} else {
				txtResetValue.setEnabled(false);
			}
		}
	}
}

class ConfigureParameter {
	public String deviceName;
	public int counterChannel;
	public CountingType cntType;
}
