package Counter_SnapCounter;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import Automation.BDaq.*;
import Common.Global;

import javax.swing.border.LineBorder;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.swing.border.TitledBorder;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.DefaultListModel;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.ListSelectionModel;
import javax.swing.JButton;
import javax.swing.JScrollPane;
import javax.swing.Timer;

public class SnapCounter extends JFrame implements ActionListener {

	/**
	 * define the serialization number.
	 */
	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	
	private JTextField txtTimeInterval;
	private JTextField txtSnapCount;
	private JTextField txtCounterValue;
	private JList listSnapSource;
	private JList CounterValueList;
	private JButton btnStart;
	private JButton btnStop;
	private JButton btnConfig;
	private DefaultListModel model1 = new DefaultListModel();
	private DefaultListModel model2 = new DefaultListModel();
	
	ConfigureParameter configure = new ConfigureParameter();
	private ConfigureDialog configureDialog;
	
	private UdCounterCtrl udCounterCtrl = new UdCounterCtrl();
	private TimerPulseCtrl m_timerPulseCtrl = new TimerPulseCtrl();
	
	private boolean m_isTimerUsing;
	private int timerChan;
	private Timer timer;

	CounterSnapHandler  m_eventHandler = new CounterSnapHandler();

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					SnapCounter frame = new SnapCounter();
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
	public SnapCounter() {
		setTitle("Counter_SnapCounter");
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 537, 342);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		addWindowListener(new WindowCloseActionListener());
		
		// Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("Background.png", "Background Image");
		panel.setBounds(0, 0, 531, 310);
		contentPane.add(panel);
		panel.setLayout(null);
		
		JPanel panel_1 = new JPanel();
		panel_1.setBorder(new TitledBorder(null, "", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panel_1.setBounds(10, 42, 180, 218);
		panel.add(panel_1);
		panel_1.setLayout(null);
		
		JLabel lblNewLabel = new JLabel("Snap source:");
		lblNewLabel.setBounds(10, 11, 96, 14);
		panel_1.add(lblNewLabel);
		
		JLabel lblNewLabel_1 = new JLabel("Time interval:");
		lblNewLabel_1.setBounds(10, 166, 68, 14);
		panel_1.add(lblNewLabel_1);
		
		txtTimeInterval = new JTextField();
		txtTimeInterval.setHorizontalAlignment(SwingConstants.RIGHT);
		txtTimeInterval.setEnabled(false);
		txtTimeInterval.setBounds(84, 160, 86, 27);
		panel_1.add(txtTimeInterval);
		txtTimeInterval.setColumns(10);
		
		JLabel lblNewLabel_2 = new JLabel("(From 0.02Hz to 50kHz)");
		lblNewLabel_2.setBounds(41, 193, 114, 14);
		panel_1.add(lblNewLabel_2);
		
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBounds(10, 36, 160, 113);
		panel_1.add(scrollPane);
		
		listSnapSource = new JList();
		listSnapSource.setBorder(new LineBorder(new Color(0, 0, 0)));
		listSnapSource.addListSelectionListener(new SnapSrcSelChangedListener());
		scrollPane.setViewportView(listSnapSource);
		listSnapSource.setModel(model1);
		
		JPanel panel_2 = new JPanel();
		panel_2.setBorder(new TitledBorder(null, "", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panel_2.setBounds(200, 41, 310, 257);
		panel.add(panel_2);
		panel_2.setLayout(null);
		
		txtCounterValue = new JTextField();
		txtCounterValue.setEditable(false);
		txtCounterValue.setBounds(10, 11, 169, 27);
		txtCounterValue.setHorizontalAlignment(SwingConstants.RIGHT);
		txtCounterValue.setColumns(10);
		panel_2.add(txtCounterValue);
		
		btnStart = new JButton("Start");
		btnStart.setBounds(204, 68, 79, 23);
		btnStart.addActionListener(new ButtonStartActionListener());
		panel_2.add(btnStart);
		
		btnStop = new JButton("Stop");
		btnStop.setBounds(204, 113, 79, 23);
		btnStop.addActionListener(new ButtonStopActionListener());
		panel_2.add(btnStop);
		
		btnConfig = new JButton("Configure");
		btnConfig.setBounds(204, 167, 79, 23);
		btnConfig.addActionListener(new ButtonConfigureActionListener());
		panel_2.add(btnConfig);
		
		JScrollPane scrollPane2 = new JScrollPane();
		scrollPane2.setBounds(10, 49, 169, 197);
		panel_2.add(scrollPane2);
		
		CounterValueList = new JList();
		CounterValueList.setDoubleBuffered(true);
		CounterValueList.setVisibleRowCount(10);
		scrollPane2.setViewportView(CounterValueList);
		CounterValueList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		CounterValueList.setBorder(new LineBorder(new Color(0, 0, 0)));
		CounterValueList.setModel(model2);
		
		JLabel lblSnapCount = new JLabel("Snap count:");
		lblSnapCount.setBounds(20, 277, 68, 14);
		panel.add(lblSnapCount);
		
		txtSnapCount = new JTextField();
		txtSnapCount.setEditable(false);
		txtSnapCount.setHorizontalAlignment(SwingConstants.RIGHT);
		txtSnapCount.setColumns(10);
		txtSnapCount.setBounds(94, 271, 86, 27);
		panel.add(txtSnapCount);
		
		//Add the Udcntr event listener to the control.
		udCounterCtrl.addUdCntrEventListener(m_eventHandler);
		
		//IntToEventId();
		
		configureDialog = new ConfigureDialog(this);
		configureDialog.setModal(true);
		configureDialog.setVisible(true);
	}
	
	public void Initialization() {
		//set the main frame's title.
		this.setTitle("Snap Counter - Run(" + configure.deviceName.substring(0, configure.deviceName.length() - 1) + ")");
		
		txtTimeInterval.setText("5");
		model2.clear();
		m_isTimerUsing = false;
		timerChan = 0;
		
		ConfigureDevice();
		ConfiguratePanel();
		
		btnStart.setEnabled(true);
		btnStop.setEnabled(false);
		btnConfig.setEnabled(true);
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
		//for reset value
		EventId[] snapSrcs = udCounterCtrl.getFeatures().getUdSnapEventSources();
		int srcCount = snapSrcs.length;
		String srcSrc = new String();
		
		model1.removeAllElements();
		
		for (int i = 0; i < srcCount; i++) {
			EventId id= snapSrcs[i];
			srcSrc = EventIDtoString(id);
			model1.add(i, srcSrc);
		}
	}
	
	public String EventIDtoString(EventId id) {
		String str;
		switch (id)
		{
		case EvtUdIndex0:
			str = "Index0";
			break;
		case EvtUdIndex1:
			str = "Index1";
			break;
		case EvtUdIndex2:
			str = "Index2";
			break;
		case EvtUdIndex3:
			str = "Index3";
			break;
		case EvtUdIndex4:
			str = "Index4";
			break;
		case EvtUdIndex5:
			str = "Index5";
			break;
		case EvtUdIndex6:
			str = "Index6";
			break;
		case EvtUdIndex7:
			str = "Index7";
			break;
		case EvtCntTimer0:
			str = "Timer0";
			break;
		case EvtCntTimer1:
			str = "Timer1";
			break;
		case EvtCntTimer2:
			str = "Timer2";
			break;
		case EvtCntTimer3:
			str = "Timer3";
			break;
		case EvtCntTimer4:
			str = "Timer4";
			break;
		case EvtCntTimer5:
			str = "Timer5";
			break;
		case EvtCntTimer6:
			str = "Timer6";
			break;
		case EvtCntTimer7:
			str = "Timer7";
			break;
		case EvtDiintChannel000:
			str = "DiintChannel0";
			break;
		case EvtDiintChannel001:
			str = "DiintChannel1";
			break;
		case EvtDiintChannel002:
			str = "DiintChannel2";
			break;
		case EvtDiintChannel003:
			str = "DiintChannel3";
			break;
		case EvtDiintChannel004:
			str = "DiintChannel4";
			break;
		case EvtDiintChannel005:
			str = "DiintChannel5";
			break;
		case EvtDiintChannel006:
			str = "DiintChannel6";
			break;
		case EvtDiintChannel007:
			str = "DiintChannel7";
			break;
		default:
			str = "";
		}
		
		return str;
	}
	
	public void CheckTimerUsingParam(int id) {
		if (id >= EventId.EvtCntTimer0.toInt() && id <=  EventId.EvtCntTimer7.toInt()) {
			timerChan = id - EventId.EvtCntTimer0.toInt();
		}

		if (timerChan != -1) {
			m_isTimerUsing = true;
		}
	}
	
	protected void ShowMessage(String message) {
		JOptionPane.showMessageDialog(this, message, "Warning MessageBox", JOptionPane.WARNING_MESSAGE);
	}
	
	//the timer handler
	public void actionPerformed(ActionEvent e) {
		try {
			udCounterCtrl.setEnabled(true);
			int x[] = {0};
			udCounterCtrl.Read(1, x);
			int cntrValue = x[0];
			
			txtCounterValue.setText("0x" + Integer.toHexString(cntrValue));
		} catch (Exception ex) {
			ShowMessage("Sorry, there're some errors occured: " + ex.toString());
		}
	}
	
	private void Start() {
		if (timer == null) {
			timer = new Timer(50, this);
		}
		timer.start();
	}
	
	class CounterSnapHandler implements UdCntrEventListener {
		public int snapCount;
		
		public CounterSnapHandler() {
			snapCount = 0;
		}
		
		@Override
		public void UdCntrEvent(Object sender, UdCntrEventArgs args) {
			final UdCntrEventArgs param = args;
			EventQueue.invokeLater(new Runnable() {
				public void run() {
					try {
						if (model2.size() > 10) {
							model2.remove(0);
						}
						
						snapCount++;
						
						String snapValue = new String("");
						String srcID = new String("");
						String source = new String("");
						StringBuilder builder = new StringBuilder("");
						
						txtSnapCount.setText(String.valueOf(snapCount));
						
						srcID = EventIDtoString(param.Id);
						builder.append("CntrValue: ");
						for (int i = 0; i < param.Length; i++) {
							builder.append(Integer.toHexString(param.Data[i]));
							builder.append(" ");
						}
						snapValue = builder.toString();
						model2.addElement(snapValue);
						
						source = "SrcID: " + srcID;
						model2.addElement(source);
						
						if (model2.size() > 10) {
							model2.remove(0);
						}	
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}); 
		}
	}
	
	class SnapSrcSelChangedListener implements ListSelectionListener {
		
		@Override
		public void valueChanged(ListSelectionEvent e) {
			int selectedIndexs[] = listSnapSource.getSelectedIndices();
			EventId[] snapSrcs = udCounterCtrl.getFeatures().getUdSnapEventSources();
			int cnt = selectedIndexs.length;
			
			int i = 0;
			Integer timerChan = -1;
			Boolean isTimerUsing = false;
			for (; i < cnt; i++) {				
				//CheckTimerUsingParam
				timerChan = -1;
				if (snapSrcs[selectedIndexs[i]].toInt() >= EventId.EvtCntTimer0.toInt() && snapSrcs[selectedIndexs[i]].toInt() <=  EventId.EvtCntTimer7.toInt()) {
					timerChan = snapSrcs[selectedIndexs[i]].toInt() - EventId.EvtCntTimer0.toInt();
				}

				if (timerChan != -1) {
					isTimerUsing = true;
				}
				
				if (isTimerUsing) {
					txtTimeInterval.setEnabled(true);
					break;
				}
			}
			if (i == cnt) {
				txtTimeInterval.setEnabled(false);
			}
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
			try {
				model2.removeAllElements();
				
				txtCounterValue.setText("0");
				txtSnapCount.setText("0");
				
				m_eventHandler.snapCount = 0;
				
				m_isTimerUsing = false;
				timerChan = -1;
				
				int selectedIndexs[] = listSnapSource.getSelectedIndices();
				int snapSrcCount = selectedIndexs.length;
				EventId[] snapSrcs = udCounterCtrl.getFeatures().getUdSnapEventSources();
				for (int i = 0; i < snapSrcCount; i++) {
					CheckTimerUsingParam(snapSrcs[selectedIndexs[i]].toInt());
					udCounterCtrl.SnapStart(snapSrcs[selectedIndexs[i]]);
				}
				
				if (m_isTimerUsing) {
					m_timerPulseCtrl.setSelectedDevice(new DeviceInformation(configure.deviceName));
					double frequency = Double.valueOf(txtTimeInterval.getText());
					
					m_timerPulseCtrl.setChannelCount(1);
					m_timerPulseCtrl.setChannelStart(timerChan);
					m_timerPulseCtrl.getChannels()[m_timerPulseCtrl.getChannelStart()].setFrequency(frequency);
					m_timerPulseCtrl.setEnabled(true);
				}
				
				//Start Snap Counter function.
				udCounterCtrl.setEnabled(true);
				
			} catch (Exception ex) {
				if (!isNum(txtTimeInterval.getText())) txtTimeInterval.setText("");
				
				//stop snap function
				int selectedIndexs[] = listSnapSource.getSelectedIndices();
				int snapSrcCount = selectedIndexs.length;
				EventId[] snapSrcs = udCounterCtrl.getFeatures().getUdSnapEventSources();
				for (int i = 0; i < snapSrcCount; i++) {
					udCounterCtrl.SnapStop(snapSrcs[selectedIndexs[i]]);
				}
				
				ShowMessage("Sorry, there're some errors occured: " + ex.toString());
				
				return;
			}
			
			Start();
			
			btnStart.setEnabled(false);
			btnConfig.setEnabled(false);
			btnStop.setEnabled(true);
			listSnapSource.setEnabled(false);
		}
	}
	
	class ButtonStopActionListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			//Stop the user Timer
			timer.stop();
			
			btnStart.setEnabled(true);
			btnStop.setEnabled(false);
			btnConfig.setEnabled(true);
			listSnapSource.setEnabled(true);
			
			try {
				//stop timer pulse
				if (m_isTimerUsing) {
					m_timerPulseCtrl.setEnabled(false);
					m_timerPulseCtrl.Cleanup();
				} 
				
				//stop snap function
				int selectedIndexs[] = listSnapSource.getSelectedIndices();
				int snapSrcCount = selectedIndexs.length;
				EventId[] snapSrcs = udCounterCtrl.getFeatures().getUdSnapEventSources();
				for (int i = 0; i < snapSrcCount; i++) {
					udCounterCtrl.SnapStop(snapSrcs[selectedIndexs[i]]);
				}
				
				//stop updown counter
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
	
	class WindowCloseActionListener extends WindowAdapter {
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
}

class ConfigureParameter {
	public String deviceName;
	public int counterChannel;
	public CountingType cntType;
}