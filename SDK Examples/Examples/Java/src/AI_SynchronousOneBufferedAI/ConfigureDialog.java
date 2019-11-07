package AI_SynchronousOneBufferedAI;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;

import java.io.File;
import java.net.MalformedURLException;
import java.text.NumberFormat;
import java.util.ArrayList;

import Automation.BDaq.*;
import Common.*;

import org.eclipse.wb.swing.FocusTraversalOnArray;

public class ConfigureDialog extends JDialog {
	// define the serialization number.
	private static final long serialVersionUID = 1L;
	private JFormattedTextField txtSectionLength;
	private JFormattedTextField txtClockRatePerChan;
	private JComboBox cmbDevice;
	private JComboBox cmbChannelStart;
	private JComboBox cmbChannelCount;
	private JComboBox cmbValueRange;
	private JButton btnOK;
	private JButton btnBrowse;
	private JFormattedTextField txtProfilePath;
	
	private WaveformAiCtrl wfAiCtrl = new WaveformAiCtrl();

	public boolean isFirstLoad = true;

	/**
	 *Build Date:2011-8-15
	 *Author:Administrator
	 *Function Description: Create the dialog.
	 */
	public ConfigureDialog(SynchronousOneBufferedAI parrent) {
		super(parrent);
		// Add window  close action listener.
		addWindowListener(new WindowCloseActionListener());

		getContentPane().setBackground(SystemColor.control);
		setTitle("Synchronous One Buffered AI - Configuration");
		setResizable(false);
		setBounds(100, 100, 385, 352);
		getContentPane().setLayout(null);

		JLabel lblNewLabel = new JLabel("Device:");
		lblNewLabel.setBounds(35, 21, 52, 15);
		getContentPane().add(lblNewLabel);

		cmbDevice = new JComboBox();
		cmbDevice.addItemListener(new ComboBoxDeviceItemListener());
		cmbDevice.setBounds(86, 18, 236, 21);
		getContentPane().add(cmbDevice);

		btnOK = new JButton("OK");
		btnOK.addActionListener(new ButtonOKActionListener());
		btnOK.setBounds(142, 286, 75, 23);
		getRootPane().setDefaultButton(btnOK);
		getContentPane().add(btnOK);

		JButton btnCancel = new JButton("Cancel");
		btnCancel.addActionListener(new ButtonCancelActionListener());
		btnCancel.setBounds(250, 286, 75, 23);
		getContentPane().add(btnCancel);

		JPanel panel = new JPanel();
		panel.setBackground(SystemColor.control);
		panel.setBounds(20, 87, 337, 188);
		panel.setBorder(BorderFactory.createTitledBorder("Buffered AI settings"));
		getContentPane().add(panel);
		panel.setLayout(null);

		JLabel lblClockRatePerchannel = new JLabel("Clock rate:");
		lblClockRatePerchannel.setBounds(15, 155, 95, 15);
		panel.add(lblClockRatePerchannel);

		txtClockRatePerChan = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtClockRatePerChan.setBounds(112, 152, 190, 21);
		panel.add(txtClockRatePerChan);
		txtClockRatePerChan.setValue(new Double(1000));
		txtClockRatePerChan.setColumns(10);

		JLabel lblNewLabel_2 = new JLabel("Hz");
		lblNewLabel_2.setBounds(305, 155, 22, 15);
		panel.add(lblNewLabel_2);

		txtSectionLength = new JFormattedTextField(NumberFormat.getIntegerInstance());
		txtSectionLength.setBounds(112, 123, 190, 21);
		panel.add(txtSectionLength);
		txtSectionLength.setValue(new Integer(1024));
		txtSectionLength.setColumns(10);

		JLabel lblSectionLength = new JLabel("Section Length:");
		lblSectionLength.setBounds(15, 125, 95, 15);
		panel.add(lblSectionLength);

		JLabel lblValueRange = new JLabel("Value range:");
		lblValueRange.setBounds(15, 95, 95, 15);
		panel.add(lblValueRange);

		cmbValueRange = new JComboBox();
		cmbValueRange.setBounds(112, 92, 190, 21);
		panel.add(cmbValueRange);

		JLabel lblChannelCount = new JLabel("Channel count:");
		lblChannelCount.setBounds(15, 65, 95, 15);
		panel.add(lblChannelCount);

		cmbChannelCount = new JComboBox();
		cmbChannelCount.setBounds(112, 62, 190, 21);
		panel.add(cmbChannelCount);

		JLabel lblChannelStart = new JLabel("Channel start:");
		lblChannelStart.setBounds(15, 35, 95, 15);
		panel.add(lblChannelStart);

		cmbChannelStart = new JComboBox();
		cmbChannelStart.setBounds(112, 32, 190, 21);
		panel.add(cmbChannelStart);
		
		JLabel lblProfile = new JLabel("Profile:");
		lblProfile.setBounds(35, 55, 52, 21);
		getContentPane().add(lblProfile);
		
		txtProfilePath = new JFormattedTextField();
		txtProfilePath.setBounds(86, 56, 127, 20);
		getContentPane().add(txtProfilePath);
		
		btnBrowse = new JButton("Browse");
		btnBrowse.setBounds(233, 55, 89, 23);
		getContentPane().add(btnBrowse);
		btnBrowse.addActionListener(new ButtonBrowseActionListener());
		
		getContentPane().setFocusTraversalPolicy(
				new FocusTraversalOnArray(new Component[] { cmbDevice, cmbChannelStart,
						cmbChannelCount, cmbValueRange, panel, txtSectionLength,
						txtClockRatePerChan, btnOK, btnCancel }));

		Initialization();
	}

	/**
	 * 
	 * Build Date:2011-8-15 
	 * Author:Administrator 
	 * Function Description:
	 * Initialize the configuration dialog.
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
	 *Build Date:2011-8-15
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
	 *Build Date:2011-8-15
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
						
						//we filter the Celsius degree for the One Buffered AI cann't support this function.
						if(Global.toValueUnit(unitIndex.value) == ValueUnit.CelsiusUnit){
							continue;
						}
						cmbValueRange.addItem(i);
					}

					//set the initialized position of the comboBox;
					cmbChannelStart.setSelectedIndex(0);
					cmbChannelCount.setSelectedIndex(1);
					cmbValueRange.setSelectedIndex(0);
				} catch (Exception except) {
					ShowMessage("Sorry, there're some errors occured: " + except.toString());
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
			SynchronousOneBufferedAI parrent = (SynchronousOneBufferedAI)getParent();

			int dataCountPerChan = ((Number) txtSectionLength.getValue()).intValue();
			double clockRatePerChan = ((Number) txtClockRatePerChan.getValue()).doubleValue();

			if(dataCountPerChan < 1 || dataCountPerChan > 10000000 ){
				ShowMessage("The samples per channel is invalid");
				return;
			}
			
			if(clockRatePerChan <= 0 || clockRatePerChan > 500000000){
				ShowMessage("The clock rate per channel is invalid");
				return;
			}

			parrent.configure.deviceName = cmbDevice.getSelectedItem().toString();
			parrent.configure.channelStart = cmbChannelStart.getSelectedIndex();
			// We plus 1 because the index of comboBox's selected item is start
			// with 0.
			parrent.configure.channelCount = cmbChannelCount.getSelectedIndex() + 1;
			parrent.configure.valueRange = (ValueRange) cmbValueRange.getSelectedItem();
			parrent.configure.clockRatePerChan = clockRatePerChan;
			parrent.configure.sectionLength = ((Number) txtSectionLength.getValue()).intValue();

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
