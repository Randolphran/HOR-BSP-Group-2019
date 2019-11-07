package AI_AsynOneBufferedAI_TDtp;

import java.awt.BorderLayout;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.File;
import java.net.MalformedURLException;
import java.text.NumberFormat;
import java.util.ArrayList;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.filechooser.FileNameExtensionFilter;

import Automation.BDaq.ActiveSignal;
import Automation.BDaq.AiFeatures;
import Automation.BDaq.BDaqApi;
import Automation.BDaq.DeviceInformation;
import Automation.BDaq.DeviceTreeNode;
import Automation.BDaq.IntByRef;
import Automation.BDaq.MathInterval;
import Automation.BDaq.SamplingMethod;
import Automation.BDaq.SignalDrop;
import Automation.BDaq.TriggerAction;
import Automation.BDaq.ValueRange;
import Automation.BDaq.ValueUnit;
import Automation.BDaq.WaveformAiCtrl;
import Common.ClassLoaderUtil;
import Common.Global;

public class ConfigureDialog extends JDialog {

	// define the serialization number.
	private static final long serialVersionUID = 1L;

	private final JPanel contentPanel = new JPanel();
	
	private JFormattedTextField txtSectionLength;
	private JFormattedTextField txtClockRatePerChan;
	private JComboBox cmbDevice;
	private JComboBox cmbChannelStart;
	private JComboBox cmbChannelCount;
	private JComboBox cmbValueRange;
	private JComboBox cmbTriggerSource;
	private JComboBox cmbTriggerEdge;
	private JFormattedTextField txtTriggerLevel;
	private JFormattedTextField txtDelayCount;
	private JButton btnBrowse;
	private JFormattedTextField txtProfilePath;
	private JComboBox cmbTriggerIndex;
	private JButton btnOK;
	
	WaveformAiCtrl wfAiCtrl = new WaveformAiCtrl();

	public boolean isFirstLoad = true;
	private boolean isTriggerSupported = false;
	private boolean isTrigger1Supported = false;

	public void DeviceChanged(String deviceDescription)
	{
		try {
			wfAiCtrl.setSelectedDevice(new DeviceInformation(deviceDescription));
			AiFeatures feature = wfAiCtrl.getFeatures();

			/**
			 * Note that: as a demo, We needn't draw to much channels in one graph, 
			 * So we define the channel count as an integer less than 16.
			 */
			int channelCount = wfAiCtrl.getChannelCount();
			if (channelCount > 16) {
				channelCount = 16;
			}
			cmbChannelStart.removeAllItems();
			for(int i = 0; i < feature.getChannelCountMax(); i++){
				cmbChannelStart.addItem(i);
			}
			cmbChannelCount.removeAllItems();
			for (int i = 1; i <= channelCount; i++) {
				cmbChannelCount.addItem(i);
			}
			
			ValueRange[] value = feature.getValueRanges();
			StringBuffer description = new StringBuffer(BDaqApi.VALUE_RANGE_DESC_MAX_LEN);
			MathInterval range = new MathInterval();
			IntByRef unitIndex = new IntByRef();
			cmbValueRange.removeAllItems();
			for (ValueRange i : value) {
				BDaqApi.AdxGetValueRangeInformation(i.toInt(), description, range, unitIndex);
				
				//we filter the celsius degree for the buffered AI cann't support this function.
				if(Global.toValueUnit(unitIndex.value) == ValueUnit.CelsiusUnit){
					continue;
				}
				cmbValueRange.addItem(i);
			}

			isTriggerSupported = (wfAiCtrl.getFeatures().getTriggerCount() > 0) ? true : false;
			cmbTriggerSource.setEnabled(isTriggerSupported);
			txtDelayCount.setEnabled(isTriggerSupported);
			txtTriggerLevel.setEnabled(isTriggerSupported);

			cmbTriggerEdge.setEnabled(isTriggerSupported);
			cmbTriggerIndex.setEnabled(isTriggerSupported);
			
			isTrigger1Supported = (wfAiCtrl.getFeatures().getTriggerCount() > 1) ? true : false;
			
			cmbTriggerIndex.removeAllItems();
		
			if(wfAiCtrl.getFeatures().getTriggerCount() > 0)
			{
				cmbTriggerIndex.addItem(new String("Trigger0"));
				cmbTriggerIndex.setSelectedIndex(0);
			}
			 
			//if(bufferedAiCtrl.getFeatures().getTriggerSupported())
			if(wfAiCtrl.getFeatures().getTriggerCount() > 1)
			{
				cmbTriggerIndex.addItem(new String("Trigger1"));
			}
			
			
			if (isTriggerSupported) {
				// Initialize trigger parameter: trigger source.
			    SignalDrop[] source = wfAiCtrl.getFeatures().getTriggerSources();
			    cmbTriggerSource.removeAllItems();
				if (source != null) {
					for (int i = 0; i < source.length; i++) {
						cmbTriggerSource.addItem(source[i]);
					}
				}

				// Initialize trigger parameter: trigger edge.
				cmbTriggerEdge.removeAllItems();
				cmbTriggerEdge.addItem(ActiveSignal.RisingEdge);
				cmbTriggerEdge.addItem(ActiveSignal.FallingEdge);

				// set the initialized position of the comboBox;
				cmbTriggerSource.setSelectedIndex(0);
				cmbTriggerEdge.setSelectedIndex(0);
			}else{
				cmbTriggerSource.removeAllItems();
				cmbTriggerEdge.removeAllItems();
				txtDelayCount.setValue(new Integer(1000));
				txtTriggerLevel.setValue(new Double(3.0));
			}
			

			
			cmbChannelStart.setSelectedIndex(0);
			cmbChannelCount.setSelectedIndex(1);
			cmbValueRange.setSelectedIndex(0);
		} catch (Exception except) {
			ShowMessage("Sorry, there'r some errors occured: " + except.toString());
			btnOK.setEnabled(false);
			return;
		}
		TriggerSourceChanged();
	}
	
	public void TriggerSourceChanged()
	{
		SignalDrop selectedItem = (SignalDrop)cmbTriggerSource.getSelectedItem();
		switch(selectedItem){
			case SignalNone:{
				txtTriggerLevel.setEnabled(false);
				txtDelayCount.setEnabled(false);
				cmbTriggerEdge.setEnabled(false);
			}break;
			case SigExtDigClock:
			case SigExtDigTrigger0:
			case SigExtDigTrigger1:
			case SigExtDigTrigger2:
			case SigExtDigTrigger3:{
				txtTriggerLevel.setEnabled(false);
				txtDelayCount.setEnabled(true);
				cmbTriggerEdge.setEnabled(true);
			}break;
			default:{
				txtTriggerLevel.setEnabled(true);
				txtDelayCount.setEnabled(true);
				cmbTriggerEdge.setEnabled(true);					
			}break;
		}
	}
	/**
	 * Create the dialog.
	 */
	public ConfigureDialog(AsynOneBufferedAI_TDtp parrent) {
		super(parrent);
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());

		setTitle("Asynchronous One Buffered AI with Trigger Delay to Stop - Configuration");
		
		setResizable(false);
		setBounds(200, 200, 581, 337);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBackground(SystemColor.control);
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);
		
		JLabel lblNewLabel = new JLabel("Device:");
		lblNewLabel.setBounds(23, 37, 57, 15);
		contentPanel.add(lblNewLabel);	
		
		cmbDevice = new JComboBox();
		cmbDevice.addItemListener(new ComboBoxDeviceItemListener());
		cmbDevice.setBounds(67, 34, 190, 21);
		contentPanel.add(cmbDevice);
		
		btnOK = new JButton("OK");
		btnOK.addActionListener(new ButtonOKActionListener());
		btnOK.setBounds(377, 275, 75, 23);
		//getRootPane().setDefaultButton(btnOK);
		contentPanel.add(btnOK);

		JButton btnCancel = new JButton("Cancel");
		btnCancel.addActionListener(new ButtonCancelActionListener());
		btnCancel.setBounds(479, 275, 75, 23);
		contentPanel.add(btnCancel);

		//getContentPane().setFocusTraversalPolicy( new FocusTraversalOnArray(new Component[] { cmbDevice, btnOK, btnCancel }));
		
		JPanel pnlParameter = new JPanel();
		pnlParameter.setBackground(SystemColor.control);
		pnlParameter.setBounds(23, 74, 250, 190);
		pnlParameter.setBorder(BorderFactory.createTitledBorder("Buffered AI general setting"));
		contentPanel.add(pnlParameter);
		pnlParameter.setLayout(null);

		JLabel lblChannelStart = new JLabel("Channel start:");
		lblChannelStart.setBounds(10, 26, 95, 15);
		pnlParameter.add(lblChannelStart);
		
		cmbChannelStart = new JComboBox();
		cmbChannelStart.setBounds(103, 23, 118, 21);
		pnlParameter.add(cmbChannelStart);

		JLabel lblChannelCount = new JLabel("Channel count:");
		lblChannelCount.setBounds(10, 60, 95, 15);
		pnlParameter.add(lblChannelCount);

		cmbChannelCount = new JComboBox();
		cmbChannelCount.setBounds(103, 57, 118, 21);
		pnlParameter.add(cmbChannelCount);
	
		JLabel lblValueRange = new JLabel("Value range:");
		lblValueRange.setBounds(10, 92, 95, 15);
		pnlParameter.add(lblValueRange);
		
		cmbValueRange = new JComboBox();
		cmbValueRange.setBounds(103, 89, 118, 21);
		pnlParameter.add(cmbValueRange);
		
		JLabel lblClockRatePerchannel = new JLabel("Clock rate:");
		lblClockRatePerchannel.setBounds(10, 156, 95, 15);
		pnlParameter.add(lblClockRatePerchannel);
		
		txtClockRatePerChan = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtClockRatePerChan.setBounds(103, 153, 118, 21);
		pnlParameter.add(txtClockRatePerChan);
		txtClockRatePerChan.setValue(new Double(1000));
		txtClockRatePerChan.setColumns(10);

		JLabel lblNewLabel_2 = new JLabel("Hz");
		lblNewLabel_2.setBounds(231, 156, 22, 15);
		pnlParameter.add(lblNewLabel_2);
		
		JLabel lblSectionLength = new JLabel("Section Length:");
		lblSectionLength.setBounds(10, 121, 95, 24);
		pnlParameter.add(lblSectionLength);

		txtSectionLength = new JFormattedTextField(NumberFormat.getIntegerInstance());
		txtSectionLength.setBounds(103, 121, 118, 21);
		pnlParameter.add(txtSectionLength);
		txtSectionLength.setValue(new Integer(1024));
		txtSectionLength.setColumns(10);

		//pnlParameter.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[]{cmbChannelStart, cmbChannelCount, cmbValueRange, txtDataCountPerChan,txtClockRatePerChan}));
		
		JPanel pnlTriggerParameter = new JPanel();
		pnlTriggerParameter.setBackground(SystemColor.control);
		pnlTriggerParameter.setBounds(285, 74, 280, 190);
		pnlTriggerParameter.setBorder(BorderFactory.createTitledBorder("Trigger settings"));
		contentPanel.add(pnlTriggerParameter);
		pnlTriggerParameter.setLayout(null);
		
		JLabel lblSource = new JLabel("Source:");
		lblSource.setBounds(10, 60, 89, 15);
		pnlTriggerParameter.add(lblSource);
		
		cmbTriggerSource = new JComboBox();
		cmbTriggerSource.addItemListener(new ComboBoxTriggerSourceListener());
		lblSource.setLabelFor(cmbTriggerSource);
		cmbTriggerSource.setBounds(98, 57, 150, 21);
		pnlTriggerParameter.add(cmbTriggerSource);
		
		JLabel lblDelayCount = new JLabel("Delay count:");
		lblDelayCount.setBounds(10, 121, 89, 15);
		pnlTriggerParameter.add(lblDelayCount);
		
		txtDelayCount = new JFormattedTextField(NumberFormat.getIntegerInstance());
		txtDelayCount.setValue(new Integer(1000));
		lblDelayCount.setLabelFor(txtDelayCount);
		txtDelayCount.setBounds(98, 121, 150, 21);
		pnlTriggerParameter.add(txtDelayCount);
		
		JLabel lblLevel = new JLabel("Trigger level:");
		lblLevel.setBounds(10, 156, 89, 15);
		pnlTriggerParameter.add(lblLevel);
		
		txtTriggerLevel = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtTriggerLevel.setValue(new Double(3.0));
		txtTriggerLevel.addPropertyChangeListener(new TriggerLevelListener());
		lblLevel.setLabelFor(txtTriggerLevel);
		txtTriggerLevel.setBounds(98, 153, 150, 21);
		pnlTriggerParameter.add(txtTriggerLevel);
		
		JLabel lblEdge = new JLabel("Edge:");
		lblEdge.setBounds(10, 92, 89, 15);
		pnlTriggerParameter.add(lblEdge);
		
		cmbTriggerEdge = new JComboBox();
		lblEdge.setLabelFor(cmbTriggerEdge);
		cmbTriggerEdge.setBounds(98, 89, 150, 21);
		pnlTriggerParameter.add(cmbTriggerEdge);
		
		JLabel lblNewLabel_1 = new JLabel("V");
		lblNewLabel_1.setBounds(253, 156, 17, 15);
		pnlTriggerParameter.add(lblNewLabel_1);
		
		JLabel lblTrigger = new JLabel("Trigger:");
		lblTrigger.setBounds(10, 26, 89, 15);
		pnlTriggerParameter.add(lblTrigger);
		
		cmbTriggerIndex = new JComboBox();
		cmbTriggerIndex.setBounds(98, 23, 150, 21);
		pnlTriggerParameter.add(cmbTriggerIndex);
		
		JLabel lblProfile = new JLabel("Profile:");
		lblProfile.setBounds(275, 37, 47, 15);
		contentPanel.add(lblProfile);
		
		txtProfilePath = new JFormattedTextField();
		txtProfilePath.setBounds(320, 34, 152, 20);
		contentPanel.add(txtProfilePath);
		
		btnBrowse = new JButton("Browse");
		btnBrowse.setBounds(479, 33, 89, 23);
		contentPanel.add(btnBrowse);
		btnBrowse.addActionListener(new ButtonBrowseActionListener());
		cmbTriggerIndex.addItemListener(new ComboBoxTriggerIndexListener());

		Initialization();
	}
	/**
	 * 
	 *Build Date:2012-3-13
	 *Author:Administrator
	 *Function Description: Initialize the configuration dialog.
	 */
	protected void Initialization() {
		ArrayList<DeviceTreeNode> installedDevice = wfAiCtrl.getSupportedDevices();
		if (installedDevice.size() <= 0) {
			ShowMessage("No device to support the currently demonstrated function!");
			System.exit(0);
		} else {
			for (DeviceTreeNode installed : installedDevice) {
				cmbDevice.addItem(installed.toString());
			}
		}
		
		cmbDevice.setSelectedIndex(0);
	}
	
	/**
	 *Build Date:2012-3-13
	 *Author:Administrator
	 *Function Description: load the configuration parameters. 
	 */
	public void LoadConfiguration(ConfigureParameter config){
		cmbChannelStart.setSelectedItem(config.channelStart);
		cmbChannelCount.setSelectedItem(config.channelCount);
		cmbValueRange.setSelectedItem(config.valueRange);
		txtClockRatePerChan.setValue(config.clockRatePerChan);
		txtSectionLength.setValue(config.sectionLength);
	}
	
	/**
	 * 
	 *Build Date:2012-3-13
	 *Author:Administrator
	 *Function Description: Show the message for users.
	 * @param message: the text message
	 */
	protected void ShowMessage(String message) {
		JOptionPane.showMessageDialog(this, message, "Warning MessageBox",
				JOptionPane.WARNING_MESSAGE);
	}
	
	/**
	 * 
	 *Build Date:2016-2-25
	 *Author:Administrator
	 *Function Description: this function is used to get profile path.
	 * @return String device name
	 */
	public String GetProfilePath() {
		return txtProfilePath.getText();
	}
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the comboBox device's items
	 * 						 	   selecting changed action.
	 */
	class ComboBoxDeviceItemListener implements ItemListener{
		public void itemStateChanged(ItemEvent e) {
			String selected = ((JComboBox) e.getSource()).getSelectedItem().toString();
			if (e.getStateChange() == ItemEvent.SELECTED) {
				btnOK.setEnabled(true);
				DeviceChanged(selected);
			} else {
				cmbChannelCount.removeAllItems();
				cmbChannelStart.removeAllItems();
				cmbValueRange.removeAllItems();
				cmbTriggerSource.removeAllItems();
				cmbTriggerEdge.removeAllItems();
			}
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 *Class Function Description: This class is used to listen the comboBox trigger source's items
	 *							  selecting changed action.
	 */
	class ComboBoxTriggerSourceListener implements ItemListener{

		@Override
		public void itemStateChanged(ItemEvent e) {
			if(e.getStateChange() == ItemEvent.SELECTED){
				TriggerSourceChanged();
			}
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 *Class Function Description: This class is used to listen the comboBox trigger source's items
	 *							  selecting changed action.
	 */
	class ComboBoxTriggerIndexListener implements ItemListener{

		@Override
		public void itemStateChanged(ItemEvent e) {
			int  index = cmbTriggerIndex.getSelectedIndex();
			String selected = cmbDevice.getSelectedItem().toString();
			if(e.getStateChange() == ItemEvent.SELECTED){
				try {
					wfAiCtrl.setSelectedDevice(new DeviceInformation(selected));
					AiFeatures feature = wfAiCtrl.getFeatures();
					cmbTriggerSource.removeAllItems();
					if(index == 0)
					{
						// Initialize trigger parameter: trigger source.
						cmbTriggerSource.removeAllItems();
 						SignalDrop[] source = feature.getTriggerSources();
 						
 						if (source != null) {
							for (int i = 0; i < source.length; i++) {
								cmbTriggerSource.addItem(source[i]);
							}
						}
						SignalDrop src = wfAiCtrl.getTrigger().getSource();
						for(int j =0; j < cmbTriggerSource.getItemCount(); ++j)
						{
						   if(src == cmbTriggerSource.getItemAt(j))
						   {
							   cmbTriggerSource.setSelectedIndex(j);
						   }
						}

						// Initialize trigger parameter: trigger edge.
						cmbTriggerEdge.removeAllItems();
						cmbTriggerEdge.addItem(ActiveSignal.RisingEdge);
						cmbTriggerEdge.addItem(ActiveSignal.FallingEdge);
						ActiveSignal edge = wfAiCtrl.getTrigger().getEdge();
						if(edge == ActiveSignal.RisingEdge){
							cmbTriggerEdge.setSelectedIndex(0);
						}else if(edge == ActiveSignal.FallingEdge){
							cmbTriggerEdge.setSelectedIndex(1);
						}
						
						txtDelayCount.setValue(wfAiCtrl.getTrigger().getDelayCount());
						txtTriggerLevel.setValue(wfAiCtrl.getTrigger().getLevel());
						
					}else if(index == 1){
					
						// Initialize trigger parameter: trigger source.
						cmbTriggerSource.removeAllItems();
 						SignalDrop[] source = wfAiCtrl.getFeatures().getTrigger1Sources();
						if (source != null) {
							for (int i = 0; i < source.length; i++) {
								cmbTriggerSource.addItem(source[i]);
							}
						}
						SignalDrop src = wfAiCtrl.getTrigger1().getSource();
						for(int j =0; j < cmbTriggerSource.getItemCount(); ++j)
						{
						   if(src == cmbTriggerSource.getItemAt(j))
						   {
							   cmbTriggerSource.setSelectedIndex(j);
						   }
						}

						// Initialize trigger parameter: trigger edge.
						cmbTriggerEdge.removeAllItems();
						cmbTriggerEdge.addItem(ActiveSignal.RisingEdge);
						cmbTriggerEdge.addItem(ActiveSignal.FallingEdge);
						ActiveSignal edge = wfAiCtrl.getTrigger1().getEdge();
						if(edge == ActiveSignal.RisingEdge){
							cmbTriggerEdge.setSelectedIndex(0);
						}else if(edge == ActiveSignal.FallingEdge){
							cmbTriggerEdge.setSelectedIndex(1);
						}
						
						txtDelayCount.setValue(wfAiCtrl.getTrigger().getDelayCount());
						txtTriggerLevel.setValue(wfAiCtrl.getTrigger().getLevel());
					}
			    } catch (Exception except) {
					ShowMessage("Sorry, there'r some errors occured: " + except.toString());
					btnOK.setEnabled(false);
					return;
			    }
			}
		
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the OK button's action. 
	 */
	class ButtonOKActionListener implements ActionListener{
		public void actionPerformed(ActionEvent arg0) {
			AsynOneBufferedAI_TDtp parent = (AsynOneBufferedAI_TDtp)getParent();
			int sectionLength = ((Number) txtSectionLength.getValue()).intValue();
			double clockRatePerChan = ((Number) txtClockRatePerChan.getValue()).doubleValue();

			if(sectionLength < 1 || sectionLength > 10000000 ){
				ShowMessage("The samples per channel is invalid");
				return;
			}
			
			if(clockRatePerChan <= 0 || clockRatePerChan > 500000000){
				ShowMessage("The clock rate per channel is invalid");
				return;
			}

			parent.configure.deviceName = cmbDevice.getSelectedItem().toString();
			parent.configure.channelStart = cmbChannelStart.getSelectedIndex();
			// We plus 1 because the index of comboBox's selected item is start with 0.
			parent.configure.channelCount = cmbChannelCount.getSelectedIndex() + 1;
			parent.configure.valueRange = (ValueRange) cmbValueRange.getSelectedItem();
			parent.configure.sectionLength = sectionLength;
			parent.configure.clockRatePerChan = clockRatePerChan;

			parent.configure.TriggerIndex = cmbTriggerIndex.getSelectedIndex();
			if (isTriggerSupported && cmbTriggerIndex.getSelectedIndex() == 0) {
				long delayCount = ((Number) txtDelayCount.getValue()).longValue();
				double triggerLevel = ((Number) txtTriggerLevel.getValue()).doubleValue();
				SignalDrop selectedItem = (SignalDrop)cmbTriggerSource.getSelectedItem();
				
				MathInterval delayCountRange = wfAiCtrl.getFeatures().getTriggerDelayRange();
				SamplingMethod method = wfAiCtrl.getFeatures().getSamplingMethod();
				int channelCount = 1;
				if(method == SamplingMethod.EqualTimeSwitch){
					channelCount = cmbChannelCount.getSelectedIndex() + 1;
				}else{
					channelCount = 1;
				}
				if(delayCount < 0 || delayCount > delayCountRange.Max / channelCount){
					ShowMessage("The trigger delay count range from 0 to " + delayCountRange.Max
							/ channelCount);
					return;
				}
				
				if(delayCount >= sectionLength && selectedItem != SignalDrop.SignalNone){
					ShowMessage("Delay count must smaller than samples per channel!");
					return;
				}
				
				parent.configure.triggerAction = TriggerAction.DelayToStop;
				parent.configure.triggerSource = (SignalDrop) cmbTriggerSource.getSelectedItem();
				parent.configure.delayCount = delayCount;
				parent.configure.triggerLevel = triggerLevel;
				parent.configure.triggerEdge = (ActiveSignal) cmbTriggerEdge.getSelectedItem();
			}

			if (isTrigger1Supported && cmbTriggerIndex.getSelectedIndex() == 1) {
				long delayCount = ((Number) txtDelayCount.getValue()).longValue();
				double triggerLevel = ((Number) txtTriggerLevel.getValue()).doubleValue();
				SignalDrop selectedItem = (SignalDrop)cmbTriggerSource.getSelectedItem();
				
				MathInterval delayCountRange = wfAiCtrl.getFeatures().getTrigger1DelayRange();
				SamplingMethod method = wfAiCtrl.getFeatures().getSamplingMethod();
				int channelCount = 1;
				if(method == SamplingMethod.EqualTimeSwitch){
					channelCount = cmbChannelCount.getSelectedIndex() + 1;
				}else{
					channelCount = 1;
				}
				if(delayCount < 0 || delayCount > delayCountRange.Max / channelCount){
					ShowMessage("The trigger1 delay count range from 0 to " + delayCountRange.Max
							/ channelCount);
					return;
				}
				
				if(delayCount >= sectionLength && selectedItem != SignalDrop.SignalNone){
					ShowMessage("Delay count must smaller than samples per channel!");
					return;
				}
				
				parent.configure.triggerAction = TriggerAction.DelayToStop;
				parent.configure.triggerSource = (SignalDrop) cmbTriggerSource.getSelectedItem();
				parent.configure.delayCount = delayCount;
				parent.configure.triggerLevel = triggerLevel;
				parent.configure.triggerEdge = (ActiveSignal) cmbTriggerEdge.getSelectedItem();
			}

			parent.Initialization();
			parent.setVisible(true);

			setVisible(false);
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the Cancel button's action
	 */
	class ButtonCancelActionListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			if(isFirstLoad ){
				System.exit(0);
			}else{
				setVisible(false);
			}
		}
	}
	
	class ButtonBrowseActionListener implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			//
			String str = null;
			try {
				str = ClassLoaderUtil.getExtendResource("../../profile");
			} catch (MalformedURLException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			str = str.substring(6);
			
			//open file dialog to select profile
			JFileChooser chooser = new JFileChooser(new File(str));
			chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
			chooser.setFileFilter(new FileNameExtensionFilter("Licence File(.xml)", "xml"));
			chooser.showOpenDialog(new JLabel());
			File file=chooser.getSelectedFile();
			txtProfilePath.setText(file.getAbsolutePath());
		}	
	}
	
	/**
	 * * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the trigger level's text changing action.
	 */
	class TriggerLevelListener implements PropertyChangeListener{
		@Override
		public void propertyChange(PropertyChangeEvent evt) {
			double triggerLevel = ((Number)txtTriggerLevel.getValue()).doubleValue();
			
			// we set the valid value of trigger level between -10.0 and 10.0 
			if(triggerLevel < -10 || triggerLevel > 10){
				txtTriggerLevel.setValue(new Double(5.0));
				ShowMessage("The trigger level is invalid");
			}

		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the configure dialog's closing event.
	 */
	class WindowCloseActionListener extends WindowAdapter{
		@Override
		public void windowClosing(WindowEvent e) {
			if (isFirstLoad) {
				System.exit(0);
			}
		}
	}
}
