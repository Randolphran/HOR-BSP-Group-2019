package AI_StreamingAI;

import java.awt.BorderLayout;
import java.awt.SystemColor;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.net.MalformedURLException;
import java.text.NumberFormat;
import java.util.ArrayList;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JComboBox;
import javax.swing.JOptionPane;

import Automation.BDaq.*;
import Common.*;

import org.eclipse.wb.swing.FocusTraversalOnArray;

import java.awt.Component;
import java.text.Format;

public class ConfigureDialog extends JDialog {
	//define the serialization number.
	private static final long serialVersionUID = 1L;
	
	private final JPanel contentPanel = new JPanel();
	private JFormattedTextField txtClockRatePerChan;
	private JComboBox cmbDevice;
	private JComboBox cmbChannelStart;
	private JComboBox cmbChannelCount;
	private JComboBox cmbValueRange;
	private JButton btnOK;
	private JButton btnBrowse;
	private JFormattedTextField txtProfilePath;
	private JFormattedTextField txtSectionLength;
	
	private WaveformAiCtrl wfAiCtrl = new WaveformAiCtrl();
	
	public boolean isFirstLoad = true;

	/**
	 *Build Date:2011-8-29
	 *Author:Administrator
	 *Function Description: Create the dialog.
	 */
	public ConfigureDialog(StreamingAI parrent) {
		super(parrent);
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setTitle("Streaming AI - Configuration");
		setResizable(false);
		setBounds(100, 100, 339, 361);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBackground(SystemColor.control);
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);

		JLabel lblNewLabel = new JLabel("Device:");
		lblNewLabel.setBounds(20, 30, 54, 15);
		contentPanel.add(lblNewLabel);

		cmbDevice = new JComboBox();
		cmbDevice.addItemListener(new ComboBoxDeviceItemListener());
		cmbDevice.setBounds(73, 27, 217, 21);
		contentPanel.add(cmbDevice);
		
		btnOK = new JButton("OK");
		btnOK.addActionListener(new ButtonOKActionListener());
		btnOK.setBounds(115, 301, 75, 23);
		contentPanel.add(btnOK);
		
		JButton btnCancel = new JButton("Cancel");
		btnCancel.addActionListener(new ButtonCancelActionListener());
		btnCancel.setBounds(215, 301, 75, 23);
		contentPanel.add(btnCancel);
		
		JPanel panel = new JPanel();
		panel.setBackground(SystemColor.control);
		panel.setBounds(20, 96, 303, 194);
		panel.setBorder(BorderFactory.createTitledBorder("Streaming AI settings"));
		contentPanel.add(panel);
		panel.setLayout(null);
		
		JLabel lblHz = new JLabel("Hz");
		lblHz.setBounds(279, 130, 14, 15);
		panel.add(lblHz);
		
		txtClockRatePerChan = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtClockRatePerChan.setBounds(100, 127, 169, 21);
		panel.add(txtClockRatePerChan);
		txtClockRatePerChan.setValue(new Double(1000));
		txtClockRatePerChan.setColumns(10);
		
		JLabel lblNewLabel_1 = new JLabel("Clock rate: ");
		lblNewLabel_1.setBounds(10, 130, 72, 15);
		panel.add(lblNewLabel_1);

		JLabel lblValueRange = new JLabel("Value range:");
		lblValueRange.setBounds(10, 95, 90, 15);
		panel.add(lblValueRange);

		cmbValueRange = new JComboBox();
		cmbValueRange.setBounds(100, 92, 169, 21);
		panel.add(cmbValueRange);

		cmbChannelCount = new JComboBox();
		cmbChannelCount.setBounds(100, 57, 169, 21);
		panel.add(cmbChannelCount);

		JLabel lblChannelCount = new JLabel("Channel count:");
		lblChannelCount.setBounds(10, 60, 90, 15);
		panel.add(lblChannelCount);

		JLabel lblChannelStart = new JLabel("Channel start:");
		lblChannelStart.setBounds(10, 25, 90, 15);
		panel.add(lblChannelStart);

		cmbChannelStart = new JComboBox();
		cmbChannelStart.setBounds(100, 22, 169, 21);
		panel.add(cmbChannelStart);
		
		JLabel lblSectionLength = new JLabel("Section Length: ");
		lblSectionLength.setBounds(10, 166, 102, 15);
		panel.add(lblSectionLength);
		
		txtSectionLength = new JFormattedTextField((Format) null);
		txtSectionLength.setColumns(10);
		txtSectionLength.setBounds(100, 163, 169, 21);
		txtSectionLength.setValue(new Integer(1024));
		panel.add(txtSectionLength);
		
		JLabel lblProfile = new JLabel("Profile:");
		lblProfile.setBounds(20, 70, 54, 15);
		contentPanel.add(lblProfile);
		
		txtProfilePath = new JFormattedTextField();
		txtProfilePath.setBounds(73, 67, 118, 20);
		contentPanel.add(txtProfilePath);
		
		btnBrowse = new JButton("Browse");
		btnBrowse.setBounds(201, 66, 89, 23);
		contentPanel.add(btnBrowse);
		btnBrowse.addActionListener(new ButtonBrowseActionListener());
		contentPanel.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[]{
				cmbDevice, cmbChannelStart, cmbChannelCount, cmbValueRange, txtClockRatePerChan, 
				btnOK, btnCancel}));
		
		Initialization();
	}
	
	/**
	 * 
	 *Build Date:2011-8-29
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
			cmbDevice.setSelectedIndex(0);
		}
	}
	
	/**
	 *Build Date:2011-8-29
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
	 *Build Date:2011-8-29
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
					
					// set the initialized position of the comboBox;
					cmbChannelStart.setSelectedIndex(0);
					cmbChannelCount.setSelectedIndex(1);
					cmbValueRange.setSelectedIndex(0);

				} catch (Exception except) {
					ShowMessage("Sorry, Some errors occured: " + except.toString());
					btnOK.setEnabled(false);
					return;
				}
			} else {
				cmbChannelCount.removeAllItems();
				cmbChannelStart.removeAllItems();
				cmbValueRange.removeAllItems();
				return;
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
			
			StreamingAI parrent = (StreamingAI)getParent();
			try {
				double clockRatePerChan = ((Number)txtClockRatePerChan.getValue()).doubleValue();
				if( clockRatePerChan <= 0 || clockRatePerChan > 500000000){
					ShowMessage("The clock rate per channel is invalid");
					return;
				}
				parrent.configure.deviceName = cmbDevice.getSelectedItem().toString();
				parrent.configure.channelStart = cmbChannelStart.getSelectedIndex();
				//We plus 1 because the index of comboBox's selected item is start with 0.
				parrent.configure.channelCount = cmbChannelCount.getSelectedIndex() + 1;
				parrent.configure.valueRange = (ValueRange)cmbValueRange.getSelectedItem();
				parrent.configure.clockRatePerChan = clockRatePerChan;
				parrent.configure.sectionLength = ((Number) txtSectionLength.getValue()).intValue();
				parrent.Initialization();				
				parrent.setVisible(true);
				setVisible(false);
			} catch (Exception ex) {
				ShowMessage("Sorry! Error occurred: " + ex.getMessage());
			}
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
