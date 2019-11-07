package AI_StreamingAI_Retrigger;

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

public class ConfigureDialog extends JDialog {
	// define the serialization number.
	private static final long serialVersionUID = 1L;
	
	private JComboBox cmbDevice;
	private JComboBox cmbChannelStart;
	private JComboBox cmbChannelCount;
	private JComboBox cmbValueRange;
	private JComboBox cmbTriggerSource;
	private JComboBox cmbTriggerEdge;
	private JFormattedTextField txtClockRatePerChan;
	private JFormattedTextField txtTriggerLevel;
	private JFormattedTextField txtDelayCount;
	
	private JFormattedTextField txtSectionLength;
	private JFormattedTextField txtCycles;
	
	private JComboBox cmbTrigger1Source;
	private JComboBox cmbTrigger1Edge;
	private JFormattedTextField txtTrigger1Level;
	private JFormattedTextField txtDelayCount1;
	
	private JButton btnOK;
	private JButton btnCancel;
	
	private JButton btnBrowse;
	private JFormattedTextField txtProfileName;
	
	private final JPanel contentPanel = new JPanel();
		
	private WaveformAiCtrl wfAiCtrl = new WaveformAiCtrl();
	
	public boolean isFirstLoad = true;
	private boolean isTriggerSupported = false;
	private boolean isTrigger1Supported = false;
	
	/**
	 *Build Date:2012-3-14
	 *Author:Administrator
	 *Function Description: Create the dialog.
	 */
	public ConfigureDialog(StreamingAI_Retrigger parrent) {
		super(parrent);
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());

		setTitle("Streaming AI with Retrigger - Configuration");
		setResizable(false);
		setBounds(100, 100, 612, 493);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBackground(SystemColor.control);
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);

		JLabel lblNewLabel = new JLabel("Device:");
		lblNewLabel.setBounds(22, 29, 58, 15);
		contentPanel.add(lblNewLabel);

		cmbDevice = new JComboBox();
		cmbDevice.addItemListener(new ComboBoxDeviceItemListener());
		cmbDevice.setBounds(73, 26, 171, 21);
		contentPanel.add(cmbDevice);

		JPanel panel1 = new JPanel();
		panel1.setBackground(SystemColor.control);
		panel1.setBounds(10, 68, 266, 340);
		panel1.setBorder(BorderFactory.createTitledBorder("Streaming AI general setting"));
		contentPanel.add(panel1);
		panel1.setLayout(null);

		JLabel lblNewLabel_2 = new JLabel("Hz");
		lblNewLabel_2.setBounds(245, 192, 21, 15);
		panel1.add(lblNewLabel_2);

		txtClockRatePerChan = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtClockRatePerChan.setBounds(106, 189, 129, 21);
		panel1.add(txtClockRatePerChan);
		txtClockRatePerChan.setValue(new Double(10000));
		txtClockRatePerChan.setColumns(10);

		JLabel lblClockRatePerchannel = new JLabel("Clock rate:");
		lblClockRatePerchannel.setBounds(10, 192, 84, 15);
		panel1.add(lblClockRatePerchannel);

		JLabel lblChannelStart = new JLabel("Channel start:");
		lblChannelStart.setBounds(10, 41, 87, 15);
		panel1.add(lblChannelStart);

		cmbChannelStart = new JComboBox();
		cmbChannelStart.setBounds(104, 38, 129, 21);
		panel1.add(cmbChannelStart);

		JLabel lblChannelCount = new JLabel("Channel count:");
		lblChannelCount.setBounds(10, 91, 87, 15);
		panel1.add(lblChannelCount);

		cmbChannelCount = new JComboBox();
		cmbChannelCount.setBounds(104, 88, 129, 21);
		panel1.add(cmbChannelCount);

		JLabel lblValueRange = new JLabel("Value range:");
		lblValueRange.setBounds(10, 142, 105, 15);
		panel1.add(lblValueRange);

		cmbValueRange = new JComboBox();
		cmbValueRange.setBounds(104, 139, 129, 21);
		panel1.add(cmbValueRange);
		
		JLabel lblSectionLength = new JLabel("Section Length:");
		lblSectionLength.setBounds(13, 243, 120, 15);
		panel1.add(lblSectionLength);
		
		txtSectionLength = new JFormattedTextField((Format) null);
		txtSectionLength.setColumns(10);
		txtSectionLength.setBounds(106, 240, 129, 21);
		txtSectionLength.setValue(new Integer(10240));
		panel1.add(txtSectionLength);
		
		JLabel lblCycles = new JLabel("Cycles:");
		lblCycles.setBounds(13, 294, 76, 15);
		panel1.add(lblCycles);
		
		txtCycles = new JFormattedTextField((Format) null);
		txtCycles.setColumns(10);
		txtCycles.setBounds(106, 291, 129, 21);
		txtCycles.setValue(new Integer(2));
		panel1.add(txtCycles);

		JPanel panel = new JPanel();
		panel.setBackground(SystemColor.control);
		panel.setBounds(283, 68, 311, 164);
		panel.setBorder(BorderFactory.createTitledBorder("Trigger settings"));
		contentPanel.add(panel);
		panel.setLayout(null);
		
		JLabel lblSource = new JLabel("Source:");
		lblSource.setBounds(20, 28, 61, 15);
		panel.add(lblSource);
		
		cmbTriggerSource = new JComboBox();
		lblSource.setLabelFor(cmbTriggerSource);
		cmbTriggerSource.setBounds(110, 25, 172, 21);
		cmbTriggerSource.addItemListener(new ComboBoxTriggerSourceListener());
		panel.add(cmbTriggerSource);
		
		JLabel lblDelayCount = new JLabel("Delay count:");
		lblDelayCount.setBounds(20, 91, 90, 15);
		panel.add(lblDelayCount);
		
		txtDelayCount = new JFormattedTextField(NumberFormat.getIntegerInstance());
		txtDelayCount.setValue(new Integer(1000));
		lblDelayCount.setLabelFor(txtDelayCount);
		txtDelayCount.setBounds(110, 88, 172, 21);
		panel.add(txtDelayCount);
		
		JLabel lblLevel = new JLabel("Trigger level:");
		lblLevel.setBounds(20, 121, 90, 15);
		panel.add(lblLevel);
		
		txtTriggerLevel = new JFormattedTextField((Format) null);
		txtTriggerLevel.setValue(new Double(3.0));
		txtTriggerLevel.addPropertyChangeListener(new TriggerLevelListener());
		lblLevel.setLabelFor(txtTriggerLevel);
		txtTriggerLevel.setBounds(110, 118, 172, 21);
		panel.add(txtTriggerLevel);
		
		JLabel lblEdge = new JLabel("Edge:");
		lblEdge.setBounds(20, 60, 61, 15);
		panel.add(lblEdge);
		
		cmbTriggerEdge = new JComboBox();
		lblEdge.setLabelFor(cmbTriggerEdge);
		cmbTriggerEdge.setBounds(110, 57, 172, 21);
		panel.add(cmbTriggerEdge);
		
		JLabel lblV = new JLabel("V");
		lblV.setBounds(286, 121, 15, 15);
		panel.add(lblV);
		
		btnOK = new JButton("OK");
		btnOK.addActionListener(new ButtonOKActionListener());
		btnOK.setBounds(327, 422, 73, 23);
		//getRootPane().setDefaultButton(btnOK);
		contentPanel.add(btnOK);

		btnCancel = new JButton("Cancel");
		btnCancel.addActionListener(new ButtonCancelActionListener());
		btnCancel.setBounds(482, 422, 73, 23);
		contentPanel.add(btnCancel);
		
		JPanel panel_1 = new JPanel();
		panel_1.setLayout(null);
		panel_1.setBorder(BorderFactory.createTitledBorder("Trigger1 settings"));
		panel_1.setBackground(SystemColor.control);
		panel_1.setBounds(283, 243, 311, 165);
		contentPanel.add(panel_1);
		
		JLabel label = new JLabel("Source:");
		label.setBounds(20, 28, 61, 15);
		panel_1.add(label);
		
		cmbTrigger1Source = new JComboBox();
		cmbTrigger1Source.setBounds(110, 25, 172, 21);
		cmbTrigger1Source.addItemListener(new ComboBoxTriggerSourceListener());
		panel_1.add(cmbTrigger1Source);
		
		JLabel label_1 = new JLabel("Delay count:");
		label_1.setBounds(20, 91, 90, 15);
		panel_1.add(label_1);
		
		txtDelayCount1 = new JFormattedTextField((Format) null);
		txtDelayCount1.setValue(new Integer(1000));
		txtDelayCount1.setBounds(110, 88, 172, 21);
		panel_1.add(txtDelayCount1);
		
		JLabel label_2 = new JLabel("Trigger level:");
		label_2.setBounds(20, 121, 90, 15);
		panel_1.add(label_2);
		
		txtTrigger1Level = new JFormattedTextField((Format) null);
		txtTrigger1Level.setValue(new Double(3.0));
		txtTrigger1Level.setBounds(110, 118, 172, 21);
		txtTrigger1Level.addPropertyChangeListener(new Trigger1LevelListener());
		panel_1.add(txtTrigger1Level);
		
		JLabel label_3 = new JLabel("Edge:");
		label_3.setBounds(20, 60, 61, 15);
		panel_1.add(label_3);
		
		cmbTrigger1Edge = new JComboBox();
		cmbTrigger1Edge.setBounds(110, 57, 172, 21);
		panel_1.add(cmbTrigger1Edge);
		
		JLabel label_4 = new JLabel("V");
		label_4.setBounds(286, 121, 15, 15);
		panel_1.add(label_4);
		
		JLabel lblProfileName = new JLabel("Proflie:");
		lblProfileName.setBounds(276, 29, 50, 15);
		contentPanel.add(lblProfileName);
		
		btnBrowse = new JButton("Browse");
		btnBrowse.setBounds(518, 25, 78, 23);
		contentPanel.add(btnBrowse);
		
		txtProfileName = new JFormattedTextField((Format) null);
		txtProfileName.setColumns(10);
		txtProfileName.setBounds(336, 26, 175, 21);
		contentPanel.add(txtProfileName);
		contentPanel.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[]{cmbDevice, btnOK, btnCancel, cmbChannelStart, cmbChannelCount, cmbValueRange, txtClockRatePerChan, txtSectionLength, txtCycles, cmbTriggerSource, txtDelayCount, txtTriggerLevel, cmbTriggerEdge, cmbTrigger1Source, txtDelayCount1, txtTrigger1Level, cmbTrigger1Edge}));
		btnBrowse.addActionListener(new ButtonBrowseActionListener());
		
		Initialization();

	}
	/**
	 * 
	 *Build Date:2012-3-14
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
				//cmbDevice.addItem(installed.toString());
				try{
					wfAiCtrl.setSelectedDevice(new DeviceInformation(installed.Description));
					if(wfAiCtrl.getFeatures().getRetriggerable())
					{
						cmbDevice.addItem(installed.toString());
					}
					} catch (Exception except) {
						ShowMessage("Sorry, there'r some errors occured: " + except.toString());
						btnOK.setEnabled(false);
						return;
					}
			}
		}
		if (cmbDevice.getItemCount() == 0)
	    {
			btnOK.setEnabled(false);
			btnCancel.setEnabled(false);
			ShowMessage("No device to support the delay to start and delay to stop Demo!");
	        return ;
	    }
		cmbDevice.setSelectedIndex(0);
	}
	
	/**
	 *Build Date:2012-3-14
	 *Author:Administrator
	 *Function Description: load the configuration parameters. 
	 */
	public void LoadConfiguration(ConfigureParameter config){
		cmbChannelStart.setSelectedItem(config.channelStart);
		cmbChannelCount.setSelectedItem(config.channelCount);
		cmbValueRange.setSelectedItem(config.valueRange);
		txtClockRatePerChan.setValue(config.clockRatePerChan);
	}
	
	/**
	 * 
	 *Build Date:2012-3-14
	 *Author:Administrator
	 *Function Description: Show the message for users
	 * @param message: the text message
	 */
	protected void ShowMessage(String message) {
		JOptionPane.showMessageDialog(this, message, "Warning MessageBox",
				JOptionPane.WARNING_MESSAGE);
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the comboBox 
	 * 							   device's items selecting changed action.
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
					
					//for trigger0
					isTriggerSupported = (wfAiCtrl.getFeatures().getTriggerCount() > 0) ? true : false;
					cmbTriggerSource.setEnabled(isTriggerSupported);
					txtDelayCount.setEnabled(isTriggerSupported);
					txtTriggerLevel.setEnabled(isTriggerSupported);
					cmbTriggerEdge.setEnabled(isTriggerSupported);
					if(isTriggerSupported){
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
						
						cmbTriggerSource.setSelectedIndex(0);
						cmbTriggerEdge.setSelectedIndex(0);
					}
					
					//for trigger1
					isTrigger1Supported = (wfAiCtrl.getFeatures().getTriggerCount() > 1) ? true : false;
					cmbTrigger1Source.setEnabled(isTrigger1Supported);
					txtDelayCount1.setEnabled(isTrigger1Supported);
					txtTrigger1Level.setEnabled(isTrigger1Supported);
					cmbTrigger1Edge.setEnabled(isTrigger1Supported);
					if(isTrigger1Supported){
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
						
						cmbTrigger1Source.setSelectedIndex(0);
						cmbTrigger1Edge.setSelectedIndex(0);
					}
					
					//set the initialized position of the comboBox;
					cmbChannelStart.setSelectedIndex(0);
					cmbChannelCount.setSelectedIndex(0);
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
			//btnOK.setEnabled(true);
			SignalDrop selectedItem = (SignalDrop)cmbTriggerSource.getSelectedItem();
			if(e.getStateChange() == ItemEvent.SELECTED){
				switch(selectedItem){
					case SignalNone:{
						txtTriggerLevel.setEnabled(false);
						txtDelayCount.setEnabled(false);
						cmbTriggerEdge.setEnabled(false);
					}break;
					case SigExtDigClock:
					case SigExtDigTrigger0:{
						txtTriggerLevel.setEnabled(false);
						txtDelayCount.setEnabled(true);
						cmbTriggerEdge.setEnabled(true);
					}break;
					case SigExtDigTrigger1:
					case SigExtDigTrigger2:
					case SigExtDigTrigger3:
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
					case SigExtDigTrigger0:
					case SigExtDigTrigger1:{
						txtTrigger1Level.setEnabled(false);
						txtDelayCount1.setEnabled(true);
						cmbTrigger1Edge.setEnabled(true);
					}break;
					case SigExtDigTrigger2:
					case SigExtDigTrigger3:
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
				txtTrigger1Level.setValue(new Double(5.0));
				ShowMessage("The trigger1 level is invalid");
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
			
			StreamingAI_Retrigger parrent = (StreamingAI_Retrigger)getParent();
			double clockRatePerChan = ((Number) txtClockRatePerChan.getValue()).doubleValue();

			// we set the valid value of clock rate per channel between 1 and 30,000,000.
			if(clockRatePerChan <= 0 || clockRatePerChan > 500000000){
				ShowMessage("The clock rate per channel is invalid");
				return;
			}
			
			parrent.configure.deviceName = cmbDevice.getSelectedItem().toString();
			parrent.configure.channelStart = cmbChannelStart.getSelectedIndex();
			// We plus 1 because the index of comboBox's selected item is start with 0.
			parrent.configure.channelCount = cmbChannelCount.getSelectedIndex() + 1;
			parrent.configure.valueRange = (ValueRange) cmbValueRange.getSelectedItem();
			parrent.configure.clockRatePerChan = ((Number)txtClockRatePerChan.getValue()).intValue();
			parrent.configure.sectionLength = ((Number)txtSectionLength.getValue()).intValue();
			parrent.configure.cycles = ((Number)txtCycles.getValue()).intValue();
			parrent.configure.profileName = txtProfileName.getText();
			 System.out.println(txtProfileName.getText());
			
			// for trigger0
			if(isTriggerSupported){
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
				parrent.configure.triggerLevel = ((Number) txtTriggerLevel.getValue()).doubleValue();
				parrent.configure.triggerEdge = (ActiveSignal) cmbTriggerEdge.getSelectedItem();
			}
			
			//for trigger1
			if (isTrigger1Supported) {
				int delayCount = ((Number) txtDelayCount1.getValue()).intValue();
				
				MathInterval delayCountRange = wfAiCtrl.getFeatures().getTrigger1DelayRange();
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
				
				parrent.configure.trigger1Action = TriggerAction.DelayToStop;
				parrent.configure.trigger1Source = (SignalDrop) cmbTrigger1Source.getSelectedItem();
				parrent.configure.delayCount1 = ((Number) txtDelayCount1.getValue()).intValue();
				parrent.configure.trigger1Level = ((Number) txtTrigger1Level.getValue()).doubleValue();
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
			chooser.showDialog(new JLabel(), "Profile");
			File file=chooser.getSelectedFile();
			txtProfileName.setText(file.getAbsolutePath());
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
