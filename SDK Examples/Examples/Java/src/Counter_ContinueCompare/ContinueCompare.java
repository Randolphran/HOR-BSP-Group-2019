package Counter_ContinueCompare;

import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.JRadioButton;
import javax.swing.Timer;
import javax.swing.UIManager;
import javax.swing.JLabel;

import java.util.regex.*;

import Automation.BDaq.*;
import Common.Global;

public class ContinueCompare extends JFrame implements ActionListener {
	
	private static final long serialVersionUID = 1L;
	private JPanel contentPane;

	private JTextField txtCounterValue;
	private JTextField txtTab1Data0;
	private JTextField txtTab1Data1;
	private JTextField txtTab1Data2;
	private JTextField txtTab2Data0;
	private JTextField txtTab2Data1;
	private JTextField txtTab2Data2;
	private JTextField txtInt1FirstValue;
	private JTextField txtInt1Increment;
	private JTextField txtInt1Count;
	private JTextField txtInt2FirstValue;
	private JTextField txtInt2Increment;
	private JTextField txtInt2Count;
	private JTextField txtPMCount;
	private JTextField txtEndCount;
	private JButton btnConfig;
	private JButton btnStart;
	private JButton btnStop;
	private JRadioButton radTable;
	private JRadioButton radInterval;
	private ButtonGroup buttonGroup = new ButtonGroup();
	
	ConfigureParameter configure = new ConfigureParameter();
	private ConfigureDialog configureDialog;
	
	private UdCounterCtrl udCounterCtrl = new UdCounterCtrl();
	CounterContCompHandler m_eventHandler = new CounterContCompHandler();
	
	private Timer timer;
	
	public int  m_tabIndex = 0;
	public TabSel m_contCompTabSel;
	
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					ContinueCompare frame = new ContinueCompare();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 * @throws IOException 
	 */
	public ContinueCompare() throws IOException {
		setTitle("Counter_ContinueCompare");
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 530, 354);
		addWindowListener(new WindowCloseActionListener());
		
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		// Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("Background.png", "Background Image");
		panel.setBounds(0, 0, 524, 322);
		contentPane.add(panel);
		panel.setLayout(null);
		
		JPanel panelTable = new JPanel();
		panelTable.setBorder(new TitledBorder(null, "", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panelTable.setBounds(20, 46, 178, 217);
		panel.add(panelTable);
		panelTable.setLayout(null);
		
		JPanel panelTab1 = new JPanel();
		panelTab1.setBorder(new TitledBorder(UIManager.getBorder("TitledBorder.border"), "Table 1", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panelTab1.setBounds(10, 11, 160, 96);
		panelTable.add(panelTab1);
		panelTab1.setLayout(null);
		
		JLabel lblNewLabel = new JLabel("CompareData0:");
		lblNewLabel.setBounds(10, 21, 76, 14);
		panelTab1.add(lblNewLabel);
		
		JLabel lblComparedata = new JLabel("CompareData1:");
		lblComparedata.setBounds(10, 46, 76, 14);
		panelTab1.add(lblComparedata);
		
		JLabel lblComparedata_1 = new JLabel("CompareData2:");
		lblComparedata_1.setBounds(10, 71, 76, 14);
		panelTab1.add(lblComparedata_1);
		
		txtTab1Data0 = new JTextField();
		txtTab1Data0.setHorizontalAlignment(SwingConstants.RIGHT);
		txtTab1Data0.setBounds(88, 18, 62, 20);
		panelTab1.add(txtTab1Data0);
		txtTab1Data0.setColumns(10);
		
		txtTab1Data1 = new JTextField();
		txtTab1Data1.setHorizontalAlignment(SwingConstants.RIGHT);
		txtTab1Data1.setColumns(10);
		txtTab1Data1.setBounds(88, 43, 62, 20);
		panelTab1.add(txtTab1Data1);
		
		txtTab1Data2 = new JTextField();
		txtTab1Data2.setHorizontalAlignment(SwingConstants.RIGHT);
		txtTab1Data2.setColumns(10);
		txtTab1Data2.setBounds(88, 68, 62, 20);
		panelTab1.add(txtTab1Data2);
		
		JPanel panelTab2 = new JPanel();
		panelTab2.setLayout(null);
		panelTab2.setBorder(new TitledBorder(UIManager.getBorder("TitledBorder.border"), "Table 2", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panelTab2.setBounds(10, 110, 160, 96);
		panelTable.add(panelTab2);
		
		JLabel label = new JLabel("CompareData0:");
		label.setBounds(10, 21, 76, 14);
		panelTab2.add(label);
		
		JLabel label_1 = new JLabel("CompareData1:");
		label_1.setBounds(10, 46, 76, 14);
		panelTab2.add(label_1);
		
		JLabel label_2 = new JLabel("CompareData2:");
		label_2.setBounds(10, 71, 76, 14);
		panelTab2.add(label_2);
		
		txtTab2Data0 = new JTextField();
		txtTab2Data0.setHorizontalAlignment(SwingConstants.RIGHT);
		txtTab2Data0.setColumns(10);
		txtTab2Data0.setBounds(88, 18, 62, 20);
		panelTab2.add(txtTab2Data0);
		
		txtTab2Data1 = new JTextField();
		txtTab2Data1.setHorizontalAlignment(SwingConstants.RIGHT);
		txtTab2Data1.setColumns(10);
		txtTab2Data1.setBounds(88, 43, 62, 20);
		panelTab2.add(txtTab2Data1);
		
		txtTab2Data2 = new JTextField();
		txtTab2Data2.setHorizontalAlignment(SwingConstants.RIGHT);
		txtTab2Data2.setColumns(10);
		txtTab2Data2.setBounds(88, 68, 62, 20);
		panelTab2.add(txtTab2Data2);
		
		JPanel panelInterval = new JPanel();
		panelInterval.setBorder(new TitledBorder(null, "", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panelInterval.setBounds(208, 46, 159, 217);
		panel.add(panelInterval);
		panelInterval.setLayout(null);
		
		JPanel panel_1 = new JPanel();
		panel_1.setBorder(new TitledBorder(null, "Interval 1", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panel_1.setBounds(10, 11, 139, 95);
		panelInterval.add(panel_1);
		panel_1.setLayout(null);
		
		JLabel lblNewLabel_1 = new JLabel("FirstValue:");
		lblNewLabel_1.setBounds(10, 21, 51, 14);
		panel_1.add(lblNewLabel_1);
		
		JLabel lblNewLabel_2 = new JLabel("Increment:");
		lblNewLabel_2.setBounds(10, 45, 58, 14);
		panel_1.add(lblNewLabel_2);
		
		JLabel lblNewLabel_3 = new JLabel("Count:");
		lblNewLabel_3.setBounds(10, 70, 38, 14);
		panel_1.add(lblNewLabel_3);
		
		txtInt1FirstValue = new JTextField();
		txtInt1FirstValue.setHorizontalAlignment(SwingConstants.RIGHT);
		txtInt1FirstValue.setColumns(10);
		txtInt1FirstValue.setBounds(67, 18, 62, 20);
		panel_1.add(txtInt1FirstValue);
		
		txtInt1Increment = new JTextField();
		txtInt1Increment.setHorizontalAlignment(SwingConstants.RIGHT);
		txtInt1Increment.setColumns(10);
		txtInt1Increment.setBounds(67, 42, 62, 20);
		panel_1.add(txtInt1Increment);
		
		txtInt1Count = new JTextField();
		txtInt1Count.setHorizontalAlignment(SwingConstants.RIGHT);
		txtInt1Count.setColumns(10);
		txtInt1Count.setBounds(67, 67, 62, 20);
		panel_1.add(txtInt1Count);
		
		JPanel panel_2 = new JPanel();
		panel_2.setLayout(null);
		panel_2.setBorder(new TitledBorder(UIManager.getBorder("TitledBorder.border"), "Interval 2", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panel_2.setBounds(10, 111, 139, 95);
		panelInterval.add(panel_2);
		
		JLabel label_3 = new JLabel("FirstValue:");
		label_3.setBounds(10, 21, 51, 14);
		panel_2.add(label_3);
		
		JLabel label_4 = new JLabel("Increment:");
		label_4.setBounds(10, 45, 58, 14);
		panel_2.add(label_4);
		
		JLabel label_5 = new JLabel("Count:");
		label_5.setBounds(10, 70, 38, 14);
		panel_2.add(label_5);
		
		txtInt2FirstValue = new JTextField();
		txtInt2FirstValue.setHorizontalAlignment(SwingConstants.RIGHT);
		txtInt2FirstValue.setColumns(10);
		txtInt2FirstValue.setBounds(67, 18, 62, 20);
		panel_2.add(txtInt2FirstValue);
		
		txtInt2Increment = new JTextField();
		txtInt2Increment.setHorizontalAlignment(SwingConstants.RIGHT);
		txtInt2Increment.setColumns(10);
		txtInt2Increment.setBounds(67, 42, 62, 20);
		panel_2.add(txtInt2Increment);
		
		txtInt2Count = new JTextField();
		txtInt2Count.setHorizontalAlignment(SwingConstants.RIGHT);
		txtInt2Count.setColumns(10);
		txtInt2Count.setBounds(67, 67, 62, 20);
		panel_2.add(txtInt2Count);
		
		JPanel panelButtons = new JPanel();
		panelButtons.setBorder(new TitledBorder(null, "", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panelButtons.setBounds(377, 46, 123, 217);
		panel.add(panelButtons);
		panelButtons.setLayout(null);
		
		btnConfig = new JButton("Configure");
		btnConfig.addActionListener(new ButtonConfigureActionListener());
		btnConfig.setBounds(29, 168, 79, 23);
		panelButtons.add(btnConfig);
		
		btnStart = new JButton("Start");
		btnStart.addActionListener(new ButtonStartActionListener());
		btnStart.setBounds(29, 69, 79, 23);
		panelButtons.add(btnStart);
		
		btnStop = new JButton("Stop");
		btnStop.addActionListener(new ButtonStopActionListener());
		btnStop.setBounds(29, 114, 79, 23);
		panelButtons.add(btnStop);
		
		txtCounterValue = new JTextField();
		txtCounterValue.setHorizontalAlignment(SwingConstants.RIGHT);
		txtCounterValue.setBounds(10, 21, 98, 24);
		panelButtons.add(txtCounterValue);
		txtCounterValue.setColumns(10);
		
		radTable = new JRadioButton("Compare table");
		radTable.setSelected(true);
		radTable.setBounds(20, 16, 109, 23);
		panel.add(radTable);
		
		radInterval = new JRadioButton("Compare interval");
		radInterval.setBounds(208, 16, 131, 23);
		panel.add(radInterval);
		
		buttonGroup.add(radTable);
		buttonGroup.add(radInterval);
		
		JLabel lblNewLabel_4 = new JLabel("Counter pattern match count:");
		lblNewLabel_4.setBounds(20, 284, 144, 14);
		panel.add(lblNewLabel_4);
		
		txtPMCount = new JTextField();
		txtPMCount.setEditable(false);
		txtPMCount.setHorizontalAlignment(SwingConstants.RIGHT);
		txtPMCount.setColumns(10);
		txtPMCount.setBounds(166, 281, 77, 24);
		panel.add(txtPMCount);
		
		JLabel lblNewLabel_5 = new JLabel("Compare table end count:");
		lblNewLabel_5.setBounds(260, 284, 125, 14);
		panel.add(lblNewLabel_5);
		
		txtEndCount = new JTextField();
		txtEndCount.setEditable(false);
		txtEndCount.setHorizontalAlignment(SwingConstants.RIGHT);
		txtEndCount.setColumns(10);
		txtEndCount.setBounds(387, 281, 77, 24);
		panel.add(txtEndCount);
		
		//initialize the compare table
		txtTab1Data0.setText("100");
		txtTab1Data1.setText("340");
		txtTab1Data2.setText("720");
		txtTab2Data0.setText("1000");
		txtTab2Data1.setText("1980");
		txtTab2Data2.setText("2510");

		txtInt1FirstValue.setText("150");
		txtInt1Increment.setText("3");
		txtInt1Count.setText("3");
		txtInt2FirstValue.setText("210");
		txtInt2Increment.setText("3");
		txtInt2Count.setText("3");
		
		//Add the Udcntr event listener to the control.
		udCounterCtrl.addUdCntrEventListener(m_eventHandler);
		
		configureDialog = new ConfigureDialog(this);
		configureDialog.setModal(true);
		configureDialog.setVisible(true);
	}
	
	public void Initialization() {
		//set the main frame's title.
		this.setTitle("Continue Compare - Run(" + configure.deviceName.substring(0, configure.deviceName.length() - 1) + ")");
		
		ConfigureDevice();
		
		btnStart.setEnabled(true);
		btnStop.setEnabled(false);
		btnConfig.setEnabled(true);
	}
	
	private void ConfigureDevice() {
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
	
	//the timer handler
	public void actionPerformed(ActionEvent e) {
		try {
			udCounterCtrl.setEnabled(true);
		} catch (Exception ex) {
			ShowMessage("Sorry, there're some errors occured: " + ex.toString());
		}
		int[] x = {0};
		udCounterCtrl.Read(1, x);
		int value = x[0];
		txtCounterValue.setText("0x" + Integer.toHexString(value));
	}
	
	private void Start() {
		if (timer == null) {
			timer = new Timer(50, this);
		}
		timer.start();
	}
	
	protected void ShowMessage(String message) {
		JOptionPane.showMessageDialog(this, message, "Warning MessageBox", JOptionPane.WARNING_MESSAGE);
	}
	
	void EnableCompareTable(Boolean enabled) {
		radTable.setEnabled(enabled);
		txtTab1Data0.setEnabled(enabled);
		txtTab1Data1.setEnabled(enabled);
		txtTab1Data2.setEnabled(enabled);
		txtTab2Data0.setEnabled(enabled);
		txtTab2Data1.setEnabled(enabled);
		txtTab2Data2.setEnabled(enabled);
		
		radInterval.setEnabled(enabled);
		txtInt1FirstValue.setEnabled(enabled);
		txtInt1Increment.setEnabled(enabled);
		txtInt1Count.setEnabled(enabled);
		txtInt2FirstValue.setEnabled(enabled);
		txtInt2Increment.setEnabled(enabled);
		txtInt2Count.setEnabled(enabled);
	}
	
	public void CreateDisperseTable(int tabIndex, int CompTab[]) {
		if (tabIndex == 0) {
			CompTab[0] = Integer.parseInt(txtTab1Data0.getText());
			CompTab[1] = Integer.parseInt(txtTab1Data1.getText());
			CompTab[2] = Integer.parseInt(txtTab1Data2.getText());
		} else {
			CompTab[0] = Integer.parseInt(txtTab2Data0.getText());
			CompTab[1] = Integer.parseInt(txtTab2Data1.getText());
			CompTab[2] = Integer.parseInt(txtTab2Data2.getText());
		}
	}
	
	public void CreateLineTable(int tabIndex, LineTabParam param) {
		if (tabIndex == 0) {
			param.firstValue = Integer.parseInt(txtInt1FirstValue.getText());
			param.increment = Integer.parseInt(txtInt1Increment.getText());
			param.count = Integer.parseInt(txtInt1Count.getText());
		} else {
			param.firstValue = Integer.parseInt(txtInt2FirstValue.getText());
			param.increment = Integer.parseInt(txtInt2Increment.getText());
			param.count = Integer.parseInt(txtInt2Count.getText());
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
			//Set compare table
			int ComTable[] = new int[3];
			for (int i = 0; i < ComTable.length; i++) {
				ComTable[i] = 0;
			}
			
			LineTabParam param = new LineTabParam();
			
			if (radTable.isSelected()) {
				m_contCompTabSel = TabSel.dispersed;
			} else {
				m_contCompTabSel = TabSel.lined;
			}
			
			try
			{
				if (TabSel.dispersed == m_contCompTabSel) {
					CreateDisperseTable(0,ComTable);
					udCounterCtrl.CompareSetTable(udCounterCtrl.getChannelStart(), 3, ComTable);
					
					//check the table2
					int ComTable2[] = new int[3];
					for (int i = 0; i < ComTable.length; i++) {
						ComTable[i] = 0;
					}
					CreateDisperseTable(1,ComTable2);	
				} else {
					CreateLineTable(0, param);
					udCounterCtrl.CompareSetInterval(udCounterCtrl.getChannelStart(), param.firstValue, param.increment, param.count);
					
					//check the interval2.
					LineTabParam param2 = new LineTabParam();
					CreateLineTable(1, param2);
				}
			} catch (Exception ex) {
				ShowMessage("Sorry, there're some errors occured: " + ex.toString());
				
				if(!isNum(txtTab1Data0.getText())) txtTab1Data0.setText("");
				if(!isNum(txtTab1Data1.getText())) txtTab1Data1.setText("");
				if(!isNum(txtTab1Data2.getText())) txtTab1Data2.setText("");
				if(!isNum(txtTab2Data0.getText())) txtTab2Data0.setText("");
				if(!isNum(txtTab2Data1.getText())) txtTab2Data1.setText("");
				if(!isNum(txtTab2Data2.getText())) txtTab2Data2.setText("");
				
				if(!isNum(txtInt1FirstValue.getText())) txtInt1FirstValue.setText("");
				if(!isNum(txtInt1Increment.getText())) txtInt1Increment.setText("");
				if(!isNum(txtInt1Count.getText())) txtInt1Count.setText("");
				if(!isNum(txtInt2FirstValue.getText())) txtInt2FirstValue.setText("");
				if(!isNum(txtInt2Increment.getText())) txtInt2Increment.setText("");
				if(!isNum(txtInt2Count.getText())) txtInt2Count.setText("");
				
				return;
			} finally {
				if(!isNum(txtTab1Data0.getText())) txtTab1Data0.setText("");
				if(!isNum(txtTab1Data1.getText())) txtTab1Data1.setText("");
				if(!isNum(txtTab1Data2.getText())) txtTab1Data2.setText("");
				if(!isNum(txtTab2Data0.getText())) txtTab2Data0.setText("");
				if(!isNum(txtTab2Data1.getText())) txtTab2Data1.setText("");
				if(!isNum(txtTab2Data2.getText())) txtTab2Data2.setText("");
				
				if(!isNum(txtInt1FirstValue.getText())) txtInt1FirstValue.setText("");
				if(!isNum(txtInt1Increment.getText())) txtInt1Increment.setText("");
				if(!isNum(txtInt1Count.getText())) txtInt1Count.setText("");
				if(!isNum(txtInt2FirstValue.getText())) txtInt2FirstValue.setText("");
				if(!isNum(txtInt2Increment.getText())) txtInt2Increment.setText("");
				if(!isNum(txtInt2Count.getText())) txtInt2Count.setText("");
			}
			
			m_eventHandler.matchCount = 0;
			m_eventHandler.endCount = 0;
			m_tabIndex = 0;
			
			//Start Snap Counter function.
			try {
				udCounterCtrl.setEnabled(true);
				Start();
				
			} catch (Exception ex) {
				ShowMessage("Sorry, there're some errors occured: " + ex.toString());
			}
			
			btnStart.setEnabled(false);
			btnStop.setEnabled(true);
			btnConfig.setEnabled(false);
			
			EnableCompareTable(false);
			
			txtPMCount.setText("0");
			txtEndCount.setText("0");
		}
	}
	
	class ButtonStopActionListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			//Stop the user Timer
			timer.stop();
			
			btnStart.setEnabled(true);
			btnStop.setEnabled(false);
			btnConfig.setEnabled(true);
			
			EnableCompareTable(true);
			
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
	
	class CounterContCompHandler implements UdCntrEventListener  {
		public int matchCount;
		public int endCount;
		public int comTable[];
		public LineTabParam lineTabparam;
		public EventId evntEndId[];
		public EventId evntMatchId[];
		public boolean matched;
		
		public CounterContCompHandler() {
			matchCount = 0;
			endCount = 0;
			comTable = new int[3];
			lineTabparam = new LineTabParam();
			matched = false;
					
			evntEndId = new EventId[]{EventId.EvtCntCompareTableEnd0, EventId.EvtCntCompareTableEnd1, EventId.EvtCntCompareTableEnd2, EventId.EvtCntCompareTableEnd3,
									  EventId.EvtCntCompareTableEnd4, EventId.EvtCntCompareTableEnd5, EventId.EvtCntCompareTableEnd6, EventId.EvtCntCompareTableEnd7};
			evntMatchId = new EventId[]{EventId.EvtCntPatternMatch0, EventId.EvtCntPatternMatch1, EventId.EvtCntPatternMatch2, EventId.EvtCntPatternMatch3,
									    EventId.EvtCntPatternMatch4, EventId.EvtCntPatternMatch5,EventId.EvtCntPatternMatch6, EventId.EvtCntPatternMatch7,};
		}
		
		public void UdCntrEvent(Object sender, UdCntrEventArgs args) {
			//refresh the snap value list
			UdCounterCtrl udCounterCtrl = (UdCounterCtrl)sender;
			
			if (evntEndId[udCounterCtrl.getChannelStart()] == args.Id) {
				endCount++;
				m_tabIndex++;
				if (m_contCompTabSel == TabSel.dispersed) {
					CreateDisperseTable(m_tabIndex%2, comTable);
					udCounterCtrl.CompareSetTable(udCounterCtrl.getChannelStart(), 3,  comTable);
				} else {
					CreateLineTable(m_tabIndex%2, lineTabparam);
					udCounterCtrl.CompareSetInterval(udCounterCtrl.getChannelStart(), lineTabparam.firstValue,lineTabparam.increment,lineTabparam.count);
				}
				matched = true;
			} else if (evntMatchId[udCounterCtrl.getChannelStart()] == args.Id) {
				++matchCount;
				matched = true;
			}
			
			if (matched) {
				txtPMCount.setText(Integer.toString(matchCount));
				txtEndCount.setText(Integer.toString(endCount));
				
				matched = false;
			}
		}	
	}
}

class ConfigureParameter {
	public String deviceName;
	public int counterChannel;
	public CountingType cntType;
}

enum TabSel {
	dispersed,
	lined;
	
	public int toInt() {
		return this.ordinal();
	} 
}

class LineTabParam {
	int firstValue;
	int increment;
	int count;
}