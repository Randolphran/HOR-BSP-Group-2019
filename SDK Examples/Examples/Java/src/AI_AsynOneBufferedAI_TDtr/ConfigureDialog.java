package AI_AsynOneBufferedAI_TDtr;

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

import Automation.BDaq.*;
import Common.*;

import org.eclipse.wb.swing.FocusTraversalOnArray;

import java.awt.Component;
import java.text.Format;

/**
 *Build Date:2012-3-13
 *Author:Administrator
 *Function Description: Create the dialog.
 */
public class ConfigureDialog extends JDialog {
	// define the serialization number.
	private static final long serialVersionUID = 1L;
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
	
	private JComboBox cmbTrigger1Source;
	private JComboBox cmbTrigger1Edge;
	private JFormattedTextField txtTrigger1Level;
	private JFormattedTextField txtDelayCount1;
	
	private JButton btnOK;
	private JButton btnBrowse;
	private JFormattedTextField txtProfilePath;
	
	private WaveformAiCtrl wfAiCtrl = new WaveformAiCtrl();
	private final JPanel contentPanel = new JPanel();
	public boolean isFirstLoad = true;
	private boolean isTriggerSupported = false;
	private boolean isTrigger1Supported = false;
	/**
	 *Build Date:2012-3-13
	 *Author:Administrator
	 *Function Description: Create the dialog.
	 */
	public ConfigureDialog(AsynOneBufferedAI_TDtr parrent) {
		super(parrent);
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
	
		setTitle("Asynchronous One Buffered AI with Trigger Delay to Start - Configuration");
		setResizable(false);
		setBounds(100, 100, 591, 397);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBackground(SystemColor.control);
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);
	
		JLabel lblNewLabel = new JLabel("Device:");
		lblNewLabel.setBounds(15, 21, 57, 15);
		contentPanel.add(lblNewLabel);	
		
		cmbDevice = new JComboBox();
		cmbDevice.addItemListener(new ComboBoxDeviceItemListener());
		cmbDevice.setBounds(68, 18, 206, 21);
		contentPanel.add(cmbDevice);
		
		JPanel pnlParameter = new JPanel();
		pnlParameter.setBackground(SystemColor.control);
		pnlParameter.setBounds(10, 87, 264, 236);
		pnlParameter.setBorder(BorderFactory.createTitledBorder("Buffered AI general setting"));
		contentPanel.add(pnlParameter);
		pnlParameter.setLayout(null);

		JLabel lblChannelStart = new JLabel("Channel start:");
		lblChannelStart.setBounds(10, 25, 95, 15);
		pnlParameter.add(lblChannelStart);
		
		cmbChannelStart = new JComboBox();
		cmbChannelStart.setBounds(107, 22, 126, 21);
		pnlParameter.add(cmbChannelStart);

		JLabel lblChannelCount = new JLabel("Channel count:");
		lblChannelCount.setBounds(10, 68, 95, 15);
		pnlParameter.add(lblChannelCount);

		cmbChannelCount = new JComboBox();
		cmbChannelCount.setBounds(107, 65, 126, 21);
		pnlParameter.add(cmbChannelCount);
	
		JLabel lblValueRange = new JLabel("Value range:");
		lblValueRange.setBounds(10, 112, 95, 15);
		pnlParameter.add(lblValueRange);
		
		cmbValueRange = new JComboBox();
		cmbValueRange.setBounds(107, 109, 126, 21);
		pnlParameter.add(cmbValueRange);
		
		JLabel lblClockRatePerchannel = new JLabel("Clock rate:");
		lblClockRatePerchannel.setBounds(10, 207, 95, 15);
		pnlParameter.add(lblClockRatePerchannel);
		
		txtClockRatePerChan = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtClockRatePerChan.setBounds(107, 204, 126, 21);
		pnlParameter.add(txtClockRatePerChan);
		txtClockRatePerChan.setValue(new Double(1000));
		txtClockRatePerChan.setColumns(10);

		JLabel lblNewLabel_2 = new JLabel("Hz");
		lblNewLabel_2.setBounds(243, 207, 20, 15);
		pnlParameter.add(lblNewLabel_2);
		
		JLabel lblSectionLength = new JLabel("Section Length:");
		lblSectionLength.setBounds(10, 160, 95, 15);
		pnlParameter.add(lblSectionLength);

		txtSectionLength = new JFormattedTextField(NumberFormat.getIntegerInstance());
		txtSectionLength.setBounds(107, 158, 126, 21);
		pnlParameter.add(txtSectionLength);
		txtSectionLength.setValue(new Integer(1024));
		txtSectionLength.setColumns(10);

		btnOK = new JButton("OK");
		btnOK.addActionListener(new ButtonOKActionListener());
		btnOK.setBounds(393, 335, 75, 23);
		//getRootPane().setDefaultButton(btnOK);
		contentPanel.add(btnOK);

		JButton btnCancel = new JButton("Cancel");
		btnCancel.addActionListener(new ButtonCancelActionListener());
		btnCancel.setBounds(495, 335, 75, 23);
		contentPanel.add(btnCancel);

		JPanel pnlTriggerParameter = new JPanel();
		pnlTriggerParameter.setBackground(SystemColor.control);
		pnlTriggerParameter.setBounds(290, 20, 283, 149);
		pnlTriggerParameter.setBorder(BorderFactory.createTitledBorder("Trigger settings"));
		contentPanel.add(pnlTriggerParameter);
		pnlTriggerParameter.setLayout(null);
		
		JLabel lblSource = new JLabel("Source:");
		lblSource.setBounds(10, 26, 78, 15);
		pnlTriggerParameter.add(lblSource);
		
		cmbTriggerSource = new JComboBox();
		lblSource.setLabelFor(cmbTriggerSource);
		cmbTriggerSource.setBounds(98, 23, 160, 21);
		cmbTriggerSource.addItemListener(new ComboBoxTriggerSourceListener());
		pnlTriggerParameter.add(cmbTriggerSource);
		
		JLabel lblDelayCount = new JLabel("Delay count:");
		lblDelayCount.setBounds(10, 91, 86, 15);
		pnlTriggerParameter.add(lblDelayCount);
		
		txtDelayCount = new JFormattedTextField(NumberFormat.getIntegerInstance());
		txtDelayCount.setValue(new Integer(1000));
		lblDelayCount.setLabelFor(txtDelayCount);
		txtDelayCount.setBounds(98, 88, 160, 21);
		pnlTriggerParameter.add(txtDelayCount);
		
		JLabel lblLevel = new JLabel("Trigger level:");
		lblLevel.setBounds(10, 121, 86, 15);
		pnlTriggerParameter.add(lblLevel);
		
		txtTriggerLevel = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtTriggerLevel.setValue(new Double(3.0));
		txtTriggerLevel.addPropertyChangeListener(new TriggerLevelListener());
		lblLevel.setLabelFor(txtTriggerLevel);
		txtTriggerLevel.setBounds(98, 118, 160, 21);
		pnlTriggerParameter.add(txtTriggerLevel);
		
		JLabel lblEdge = new JLabel("Edge:");
		lblEdge.setBounds(10, 58, 78, 15);
		pnlTriggerParameter.add(lblEdge);
		
		cmbTriggerEdge = new JComboBox();
		lblEdge.setLabelFor(cmbTriggerEdge);
		cmbTriggerEdge.setBounds(98, 54, 160, 21);
		pnlTriggerParameter.add(cmbTriggerEdge);
		
		JLabel lblV = new JLabel("V");
		lblV.setBounds(262, 121, 15, 15);
		pnlTriggerParameter.add(lblV);
		//pnlTriggerParameter.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[]{cmbTriggerSource, txtDelayCount, txtTriggerLevel, cmbTriggerEdge}));
		
		JPanel pnlTrigger1Parameter = new JPanel();
		pnlTrigger1Parameter.setLayout(null);
		pnlTrigger1Parameter.setBorder(BorderFactory.createTitledBorder("Trigger1 settings"));
		pnlTrigger1Parameter.setBackground(SystemColor.control);
		pnlTrigger1Parameter.setBounds(290, 175, 283, 149);
		contentPanel.add(pnlTrigger1Parameter);
		
		JLabel label = new JLabel("Source:");
		label.setBounds(10, 26, 78, 15);
		pnlTrigger1Parameter.add(label);
		
		cmbTrigger1Source = new JComboBox();
		cmbTrigger1Source.setBounds(98, 23, 160, 21);
		cmbTrigger1Source.addItemListener(new ComboBoxTriggerSourceListener());
		pnlTrigger1Parameter.add(cmbTrigger1Source);
		
		JLabel label_1 = new JLabel("Delay count:");
		label_1.setBounds(10, 91, 86, 15);
		pnlTrigger1Parameter.add(label_1);
		
		txtDelayCount1 = new JFormattedTextField((Format) null);
		txtDelayCount1.setValue(new Integer(1000));
		txtDelayCount1.setBounds(98, 88, 160, 21);
		pnlTrigger1Parameter.add(txtDelayCount1);
		
		JLabel label_2 = new JLabel("Trigger level:");
		label_2.setBounds(10, 121, 86, 15);
		pnlTrigger1Parameter.add(label_2);
		
		txtTrigger1Level = new JFormattedTextField((Format) null);
		txtTrigger1Level.setValue(new Double(3.0));
		txtTrigger1Level.setBounds(98, 118, 160, 21);
		txtTrigger1Level.addPropertyChangeListener(new Trigger1LevelListener());
		pnlTrigger1Parameter.add(txtTrigger1Level);
		
		JLabel label_3 = new JLabel("Edge:");
		label_3.setBounds(10, 58, 78, 15);
		pnlTrigger1Parameter.add(label_3);
		
		cmbTrigger1Edge = new JComboBox();
		cmbTrigger1Edge.setBounds(98, 54, 160, 21);
		pnlTrigger1Parameter.add(cmbTrigger1Edge);
		
		JLabel label_4 = new JLabel("V");
		label_4.setBounds(262, 121, 15, 15);
		pnlTrigger1Parameter.add(label_4);
		
		JLabel lblProfile = new JLabel("Profile:");
		lblProfile.setBounds(15, 51, 43, 15);
		contentPanel.add(lblProfile);
		
		txtProfilePath = new JFormattedTextField();
		txtProfilePath.setBounds(68, 50, 110, 22);
		contentPanel.add(txtProfilePath);
		
		btnBrowse = new JButton("Browse");
		btnBrowse.setBounds(184, 50, 90, 23);
		contentPanel.add(btnBrowse);
		btnBrowse.addActionListener(new ButtonBrowseActionListener());
		
		contentPanel.setFocusTraversalPolicy(new FocusTraversalOnArray(
				new Component[]{cmbDevice, btnOK, btnCancel,
						cmbChannelStart, cmbChannelCount, cmbValueRange, txtSectionLength,txtClockRatePerChan,
						cmbTriggerSource, txtDelayCount, txtTriggerLevel, cmbTriggerEdge,
						cmbTrigger1Source, txtDelayCount1, txtTrigger1Level, cmbTrigger1Edge}));
		
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
	 * 						 	   selecting changed action
	 */
	class ComboBoxDeviceItemListener implements ItemListener{
		public void itemStateChanged(ItemEvent e) {
			String selected = ((JComboBox) e.getSource()).getSelectedItem().toString();
			if (e.getStateChange() == ItemEvent.SELECTED) {
				btnOK.setEnabled(true);
				try {
					wfAiCtrl.setSelectedDevice(new DeviceInformation(selected));
					AiFeatures feature = wfAiCtrl.getFeatures();

					/**
					 * Note that: as a demo, We needn't draw to much channels in one graph, 
					 * So we define the channel count as an integer less than 16.
					 */
					int channelCount = wfAiCtrl.getChannelCount();
					if (channelCount > 16) {
						channelCount = 16;
					}
					for(int i = 0; i < feature.getChannelCountMax(); i++){
						cmbChannelStart.addItem(i);
					}
					
					for (int i = 1; i <= channelCount; i++) {
						cmbChannelCount.addItem(i);
					}
					
					ValueRange[] value = feature.getValueRanges();
					StringBuffer description = new StringBuffer(BDaqApi.VALUE_RANGE_DESC_MAX_LEN);
					MathInterval range = new MathInterval();
					IntByRef unitIndex = new IntByRef();
					
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
					
					if (isTriggerSupported) {
						// Initialize trigger parameter: trigger source.
						SignalDrop[] source = wfAiCtrl.getFeatures().getTriggerSources();
						if (source != null) {
							for (int i = 0; i < source.length; i++) {
								cmbTriggerSource.addItem(source[i]);
							}
						}

						// Initialize trigger parameter: trigger edge.
						cmbTriggerEdge.addItem(ActiveSignal.RisingEdge);
						cmbTriggerEdge.addItem(ActiveSignal.FallingEdge);

						// set the initialized position of the comboBox;
						cmbTriggerSource.setSelectedIndex(0);
						cmbTriggerEdge.setSelectedIndex(0);
					}
					
					isTrigger1Supported = (wfAiCtrl.getFeatures().getTriggerCount() > 1) ? true : false;
					cmbTrigger1Source.setEnabled(isTrigger1Supported);
					txtDelayCount1.setEnabled(isTrigger1Supported);
					txtTrigger1Level.setEnabled(isTrigger1Supported);
					cmbTrigger1Edge.setEnabled(isTrigger1Supported);
					
					if (isTrigger1Supported) {
						// Initialize trigger parameter: trigger source.
						SignalDrop[] source = wfAiCtrl.getFeatures().getTrigger1Sources();
						if (source != null) {
							for (int i = 0; i < source.length; i++) {
								cmbTrigger1Source.addItem(source[i]);
							}
						}

						// Initialize trigger parameter: trigger edge.
						cmbTrigger1Edge.addItem(ActiveSignal.RisingEdge);
						cmbTrigger1Edge.addItem(ActiveSignal.FallingEdge);

						// set the initialized position of the comboBox;
						cmbTrigger1Source.setSelectedIndex(0);
						cmbTrigger1Edge.setSelectedIndex(0);
					}
					
					cmbChannelStart.setSelectedIndex(0);
					cmbChannelCount.setSelectedIndex(1);
					cmbValueRange.setSelectedIndex(0);
				} catch (Exception except) {
					ShowMessage("Sorry, there'r some errors occured: " + except.toString());
					btnOK.setEnabled(false);
					return;
				}
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
			SignalDrop selectedItem = (SignalDrop)cmbTriggerSource.getSelectedItem();
			if(e.getStateChange() == ItemEvent.SELECTED){
				switch(selectedItem){
					case SignalNone:{
						txtTriggerLevel.setEnabled(false);
						txtDelayCount.setEnabled(false);
						cmbTriggerEdge.setEnabled(false);
					}break;
					case SigExtDigClock:
					//case SigExtAnaTrigger0:
					//case SigExtAnaTrigger1:
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
			
			// for trigger1 
			SignalDrop selectedItem1 = (SignalDrop)cmbTrigger1Source.getSelectedItem();
			if(e.getStateChange() == ItemEvent.SELECTED && selectedItem1 != null){
				switch(selectedItem1){
					case SignalNone:{
						txtTrigger1Level.setEnabled(false);
						txtDelayCount1.setEnabled(false);
						cmbTrigger1Edge.setEnabled(false);
					}break;
					case SigExtDigClock:
					/*case SigExtAnaTrigger0:
					case SigExtAnaTrigger1:*/
					case SigExtDigTrigger0:
					case SigExtDigTrigger1:
					case SigExtDigTrigger2:
					case SigExtDigTrigger3:{
						txtTrigger1Level.setEnabled(false);
						txtDelayCount1.setEnabled(true);
						cmbTrigger1Edge.setEnabled(true);
					}break;
					default:{
						txtTrigger1Level.setEnabled(true);
						txtDelayCount1.setEnabled(true);
						cmbTrigger1Edge.setEnabled(true);					
					}break;
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
			AsynOneBufferedAI_TDtr parrent = (AsynOneBufferedAI_TDtr)getParent();
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
			
			parrent.configure.deviceName = cmbDevice.getSelectedItem().toString();
			parrent.configure.channelStart = cmbChannelStart.getSelectedIndex();
			// We plus 1 because the index of comboBox's selected item is start with 0.
			parrent.configure.channelCount = cmbChannelCount.getSelectedIndex() + 1;
			parrent.configure.valueRange = (ValueRange) cmbValueRange.getSelectedItem();
			parrent.configure.sectionLength = sectionLength;
			parrent.configure.clockRatePerChan = clockRatePerChan;

			if (isTriggerSupported) {
				int delayCount = ((Number) txtDelayCount.getValue()).intValue();
				
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
				
				parrent.configure.triggerAction = TriggerAction.DelayToStart;
				parrent.configure.triggerSource = (SignalDrop) cmbTriggerSource.getSelectedItem();
				parrent.configure.delayCount = ((Number) txtDelayCount.getValue()).intValue();
				parrent.configure.triggerLevel = ((Number) txtTriggerLevel.getValue())
						.doubleValue();
				parrent.configure.triggerEdge = (ActiveSignal) cmbTriggerEdge.getSelectedItem();
			}
			
			if (isTrigger1Supported) {
				int delayCount = ((Number) txtDelayCount1.getValue()).intValue();
				
				MathInterval delayCountRange = wfAiCtrl.getFeatures().getTrigger1DelayRange();
				SamplingMethod method =wfAiCtrl.getFeatures().getSamplingMethod();
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
				
				parrent.configure.trigger1Action = TriggerAction.DelayToStart;
				parrent.configure.trigger1Source = (SignalDrop) cmbTrigger1Source.getSelectedItem();
				parrent.configure.delayCount1 = ((Number) txtDelayCount1.getValue()).intValue();
				parrent.configure.trigger1Level = ((Number) txtTrigger1Level.getValue())
						.doubleValue();
				parrent.configure.trigger1Edge = (ActiveSignal) cmbTrigger1Edge.getSelectedItem();
			}
			

			parrent.Initialization();
			parrent.setVisible(true);

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
	
	public class ButtonBrowseActionListener implements ActionListener{
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
				ShowMessage("The trigger level is invalid");
				txtTriggerLevel.setValue(new Double(5.0));
			}
		}
	}
	
	/**
	 * * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the trigger level's text changing action.
	 */
	class Trigger1LevelListener implements PropertyChangeListener{
		@Override
		public void propertyChange(PropertyChangeEvent evt) {
			double triggerLevel = ((Number)txtTrigger1Level.getValue()).doubleValue();
			
			// we set the valid value of trigger level between -10.0 and 10.0 
			if(triggerLevel < -10 || triggerLevel > 10){
				ShowMessage("The trigger1 level is invalid");
				txtTrigger1Level.setValue(new Double(5.0));
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
