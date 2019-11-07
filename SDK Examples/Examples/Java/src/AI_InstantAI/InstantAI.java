package AI_InstantAI;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.ChangeListener;
import javax.swing.event.ChangeEvent;

import Automation.BDaq.*;
import Common.*;

import org.eclipse.wb.swing.FocusTraversalOnArray;

public class InstantAI extends JFrame implements ActionListener {

	/**
	 * define the serialization number.
	 */
	private static final long serialVersionUID = 1L;
	
	private JPanel contentPane;
	private JTextField txtTrackValue;
	private JLabel label_YCoordinateMax;
	private JLabel label_YCoordinateMid;
	private JLabel label_YCoordinateMin;
	private JLabel label_XCoordinateMin;
	private JLabel label_XCoordinateMax;
	private JSlider sliderTime;
	private JButton btnConfig;
	private JButton btnStart;
	private JButton btnPause;
	private JButton btnStop;
	private JList listView;
	private DefaultListModel model = new DefaultListModel();
	private Timer timer;

	private SimpleGraph graph;
	private InstantAiCtrl instantAiCtrl = new InstantAiCtrl();
	
	/**
	 * Note that: as a demo, We needn't draw to much channels in one graph, and in instantAI ,one 
	 * channel one sample, channel count is equal to data count, and we define the channel count
	 * as an integer less than 16, so we allocate a buffer length of 16 to store the scaled data
	 * from the device.
	 */
	private double[] scaledData = new double[16];
	private ConfigureDialog configureDialog;
	ConfigureParameter configure = new ConfigureParameter();
	
	/**
	 * 
	 * Build Date:2011-8-8 
	 * Author:Administrator 
	 * Function Description: Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					InstantAI frame = new InstantAI();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * 
	 * Build Date:2011-8-8 
	 * Author:Administrator
	 * Function Description: Create the frame.
	 */
	public InstantAI() {
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setResizable(false);
		setTitle("AI-Instant Run");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 766, 539);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);

		// Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("Background.png", "Background Image");
		panel.setBounds(0, 0, 760, 507);
		contentPane.add(panel);
		panel.setLayout(null);

		graph = new SimpleGraph();
		graph.setBackground(Color.BLACK);
		graph.setBounds(49, 39, 660, 340);
		graph.size = new Dimension(graph.getSize());
		panel.add(graph);

		label_YCoordinateMax = new JLabel("5V");
		label_YCoordinateMax.setHorizontalAlignment(SwingConstants.RIGHT);
		label_YCoordinateMax.setBounds(0, 39, 46, 15);
		panel.add(label_YCoordinateMax);

		label_YCoordinateMid = new JLabel("0");
		label_YCoordinateMid.setHorizontalAlignment(SwingConstants.RIGHT);
		label_YCoordinateMid.setBounds(0, 198, 46, 15);
		panel.add(label_YCoordinateMid);

		label_YCoordinateMin = new JLabel("-5V");
		label_YCoordinateMin.setHorizontalAlignment(SwingConstants.RIGHT);
		label_YCoordinateMin.setBounds(0, 364, 46, 15);
		panel.add(label_YCoordinateMin);

		label_XCoordinateMin = new JLabel("0Sec");
		label_XCoordinateMin.setHorizontalAlignment(SwingConstants.LEFT);
		label_XCoordinateMin.setBounds(49, 383, 70, 15);
		panel.add(label_XCoordinateMin);

		label_XCoordinateMax = new JLabel("10Sec");
		label_XCoordinateMax.setHorizontalAlignment(SwingConstants.RIGHT);
		label_XCoordinateMax.setBounds(629, 383, 80, 15);
		panel.add(label_XCoordinateMax);

		listView = new JList();
		listView.setBounds(49, 404, 498, 50);
		listView.setLayoutOrientation(JList.HORIZONTAL_WRAP);
		listView.setDoubleBuffered(true);
		listView.setAlignmentX(Component.RIGHT_ALIGNMENT);
		listView.setFixedCellWidth(62);
		listView.setFixedCellHeight(25);
		panel.add(listView);

		sliderTime = new JSlider();
		sliderTime.setEnabled(false);
		sliderTime.setValue(200);
		sliderTime.setMinimum(10);
		sliderTime.setMaximum(1000);
		sliderTime.setBackground(SystemColor.control);
		sliderTime.setBounds(553, 430, 156, 25);
		sliderTime.addChangeListener(new SliderTimeChangeListener());
		panel.add(sliderTime);

		txtTrackValue = new JTextField();
		txtTrackValue.setEditable(false);
		txtTrackValue.setHorizontalAlignment(SwingConstants.RIGHT);
		txtTrackValue.setText("200");
		txtTrackValue.setBounds(653, 401, 36, 21);
		panel.add(txtTrackValue);
		txtTrackValue.setColumns(10);

		JLabel lblNewLabel = new JLabel("ms");
		lblNewLabel.setHorizontalAlignment(SwingConstants.RIGHT);
		lblNewLabel.setBounds(689, 405, 20, 15);
		panel.add(lblNewLabel);

		btnConfig = new JButton("Configure");
		btnConfig.addActionListener(new ButtonConfigureActionListener());

		btnConfig.setBounds(287, 474, 115, 23);
		panel.add(btnConfig);

		btnStart = new JButton("Start");
		btnStart.addActionListener(new ButtonStartActionListener());
		btnStart.setBounds(449, 474, 75, 23);
		panel.add(btnStart);

		btnPause = new JButton("Pause");
		btnPause.addActionListener(new ButtonPauseActionListener());
		btnPause.setBounds(543, 474, 75, 23);
		btnPause.setEnabled(false);
		panel.add(btnPause);

		btnStop = new JButton("Stop");
		btnStop.addActionListener(new ButtonStopActionListener());
		btnStop.setBounds(634, 474, 75, 23);
		btnStop.setEnabled(false);
		panel.add(btnStop);

		JLabel lblNewLabel_1 = new JLabel("Sample Interval:");
		lblNewLabel_1.setBounds(553, 404, 96, 15);
		panel.add(lblNewLabel_1);
		panel.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[]{
				sliderTime, btnConfig, btnStart, btnPause, btnStop}));

		configureDialog = new ConfigureDialog(this);
		configureDialog.setModal(true);
		configureDialog.setVisible(true);

	}

	/**
	 * 
	 * Build Date:2011-8-8 
	 * Author:Administrator
	 * Function Description: This function is used to configure parameter for the device.
	 */
	protected void ConfigureDevice() {
		try {
			instantAiCtrl.setSelectedDevice(new DeviceInformation(configure.deviceName));
			AnalogInputChannel[] channels = instantAiCtrl.getChannels();
			int count = instantAiCtrl.getFeatures().getChannelCountMax();
			int channel = configure.channelStart;
			
			for (int i = 0; i < configure.channelCount; ++i)
		    {
		      if (channel >= count){
		         channel = 0;}
		      if (channels[channel].getSignalType() == AiSignalType.Differential)
		      {
		         if (channel%2 == 1){
		            channel -= 1;}
		         channels[channel%count].setValueRange((ValueRange)(configure.valueRange));
		         channel += 1;
		      }
		      channels[channel%count].setValueRange((ValueRange)(configure.valueRange));
		      channel += 1;
		    }
		} catch (Exception e) {
			ShowMessage("Sorry, there're some errors occred:  " + e.getMessage());
		}
		String profilePath = null;
		profilePath = configureDialog.GetProfilePath();
		ErrorCode errorCode = instantAiCtrl.LoadProfile(profilePath);
		if(Global.BioFaild(errorCode)){
			ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
			}
	}

	/**
	 * 
	 * Build Date:2011-8-9 
	 * Author:Administrator
	 * Function Description: This function is used to configure the graph!
	 */
	protected void ConfigureGraph() {
		StringBuffer description = new StringBuffer(BDaqApi.VALUE_RANGE_DESC_MAX_LEN);
		MathInterval range = new MathInterval();
		IntByRef unitIndex = new IntByRef();

		/**
		 * String array X ranges contents of two elements, They are the Maximum
		 * value of X coordinate, and the Minimum value of X coordinate!
		 */
		String[] Xranges = new String[2];

		/**
		 * String array Y ranges contents of three elements, They are the
		 * Maximum value of Y coordinate, the Middle value of Y coordinate and
		 * the Minimum value of Y coordinate!
		 */
		String[] Yranges = new String[3];

		Global.GetXCordRange(Xranges, 10, 0, TimeUnit.Second);
		BDaqApi.AdxGetValueRangeInformation(configure.valueRange.toInt(), description, range, unitIndex);
		Global.GetYCordRange(Yranges, range, Global.toValueUnit(unitIndex.value));

		label_YCoordinateMax.setText(Yranges[2]);
		label_YCoordinateMid.setText(Yranges[1]);
		label_YCoordinateMin.setText(Yranges[0]);
		
		if(ValueUnit.values()[unitIndex.value] == ValueUnit.Millivolt){
			range.Max /= 1000;
			range.Min /= 1000;
		}

		//configure the simple graph
		graph.setXCordTimeDiv(1000);
		graph.setyCordRangeMax(range.Max);
		graph.setyCordRangeMin(range.Min);
		graph.Clear();
	}

	/**
	 * 
	 * Build Date:2011-8-8 
	 * Author:Administrator
	 * Function Description: This function is used to initialize the main frame's title, X 
	 * 						 coordinate and Y coordinate
	 */
	public void Initialization() {

		//String array channelValues contents of the current channels' data in each channel.
		String[] channelValues = new String[configure.channelCount];

		//set the main frame's title.
		this.setTitle("Instant AI - Run(" + configure.deviceName.substring(0, configure.deviceName.length() - 1) + ")");
		
		model.removeAllElements();
		for (int i = 0; i < channelValues.length; i++) {
			channelValues[i] = "0.0000";
			model.addElement(channelValues[i]);
		}
		listView.setModel(model);
		listView.setBorder(new LineBorder(new Color(0, 0, 0)));
		listView.setVisibleRowCount(-1);
		listView.setCellRenderer(new ListViewCellRenderer());
		listView.setVisible(true);
		
		ConfigureDevice();
		ConfigureGraph();
		
		btnConfig.setEnabled(true);
		btnStart.setEnabled(true);
		btnPause.setEnabled(false);
		btnStop.setEnabled(false);
	}

	/**
	 * 
	 * Build Date:2011-8-10 
	 * Author:Administrator
	 * Function Description: This function is used to start the timer!
	 */
	private void Start() {
		if (timer == null) {
			timer = new Timer(200, this);
		}
		timer.start();
	}

	/**
	 * 
	 * Build Date:2011-8-10 
	 * Author:Administrator
	 * Function Description: This function is used to update the list' values!
	 */
	private void FreshList() {
		model.removeAllElements();
		String str = "0.0000";
		String strNumber = "";
		for (int i = 0; i < configure.channelCount; i++) {
			model.addElement("0.0000");
			str = String.format("%.4f", scaledData[i]);
			strNumber = str;
			if(str.length() > 7){
				strNumber = str.substring(0, 7);
			}
			model.set(i, strNumber);
		}
	}

	/**
	 * 
	 * Build Date:2011-8-10 
	 * Author:Administrator
	 * Function Description: This function is overload the interface ActionListener,and 
	 * 						 is implementation need this function!
	 */
	public void actionPerformed(ActionEvent e) {
		ErrorCode errorCode = instantAiCtrl.Read(configure.channelStart, configure.channelCount, scaledData);
		if (Global.BioFaild(errorCode)) {
			timer.stop();
			
			btnStart.setEnabled(false);
			btnConfig.setEnabled(true);
			btnPause.setEnabled(false);
			btnStop.setEnabled(false);
			
			ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
			return;
		}

		graph.Chart(scaledData, configure.channelCount, 1, 1.0 * sliderTime.getValue() / 1000);
		FreshList();
	}

	/**
	 * 
	 * Build Date:2011-8-8 
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
	 * Class Function Description: This class is used to listen the time slider's change.
	 */
	class SliderTimeChangeListener implements ChangeListener{
		public void stateChanged(ChangeEvent arg0) {
			if (timer == null) {
				Start();
			}
			graph.Clear();
			txtTrackValue.setText(String.valueOf(sliderTime.getValue()));
			timer.setDelay(sliderTime.getValue());
			if (btnStart.getModel().isEnabled() == false) {
				timer.start();
			}else{
				timer.stop();
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
			graph.Clear();
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
			btnStart.setEnabled(false);
			btnConfig.setEnabled(false);
			btnPause.setEnabled(true);
			btnStop.setEnabled(true);
			sliderTime.setEnabled(true);
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
			btnPause.setEnabled(false);
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
			for (int i = 0; i < configure.channelCount; i++) {
				scaledData[i] = 0;
			}
			graph.Clear();
			FreshList();
			btnStart.setEnabled(true);
			btnConfig.setEnabled(true);
			btnPause.setEnabled(false);
			btnStop.setEnabled(false);
		}
	}
	
	/**
	 * 
	 * @author Administrator 
	 * Class Function Description: this class is use to draw each cell of the JList object
	 */
	class ListViewCellRenderer extends JLabel implements ListCellRenderer {
		
		private static final long serialVersionUID = 1L;

		public Component getListCellRendererComponent(JList list, Object value, int index,
				boolean isSelected, boolean cellHasFocus) {

			if (value != null) {
				String text = value.toString();
				setText(text);
				Border etch = BorderFactory.createEtchedBorder();
				this.setBorder(BorderFactory.createTitledBorder(etch));

				setHorizontalAlignment(SwingConstants.RIGHT);
				setOpaque(true);
				setBackground(SimpleGraph.color[index]);
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
			if (instantAiCtrl != null) {
				instantAiCtrl.Cleanup();
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
 * Class Description: this class is use to transfer parameter to the main frame dialog!
 */
class ConfigureParameter {
	public String deviceName;
	public int channelStart;
	public int channelCount;
	public ValueRange valueRange;
}