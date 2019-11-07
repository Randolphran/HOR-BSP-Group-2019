package AO_StreamingAO;

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
import javax.swing.filechooser.FileNameExtensionFilter;

import Automation.BDaq.*;
import Common.ClassLoaderUtil;

import org.eclipse.wb.swing.FocusTraversalOnArray;

import java.awt.Component;

public class ConfigureDialog extends JDialog {
	// Define the serialization number.
	private static final long serialVersionUID = 1L;
	
	private JComboBox cmbDevice;
	private JComboBox cmbChannelStart;
	private JComboBox cmbChannelCount;
	private JComboBox cmbValueRange;
	private JFormattedTextField txtPointCount;
	private JFormattedTextField txtClockRate;
	private JButton btnOK;
	private JButton btnBrowse;
	private JFormattedTextField txtProfilePath;
	public boolean isFirstLoad = true;

	/**
	 * 
	 * Build Date:2011-9-8
	 * Author:Administrator
	 * Function Description: Create the dialog.
	 */
	public ConfigureDialog(StreamingAO parrent) {
		super(parrent);
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
		
		getContentPane().setBackground(SystemColor.control);
		setTitle("Streaming AO - Configuration");
		setResizable(false);
		setBounds(100, 100, 503, 251);
		getContentPane().setLayout(null);

		JLabel lblDevice = new JLabel("Device:");
		lblDevice.setBounds(20, 20, 41, 15);
		getContentPane().add(lblDevice);

		cmbDevice = new JComboBox();
		cmbDevice.addItemListener(new ComboBoxDiveceItemListener());
		cmbDevice.setBounds(60, 17, 180, 21);
		getContentPane().add(cmbDevice);

		btnOK = new JButton("OK");
		btnOK.addActionListener(new ButtonOKActionListener());
		btnOK.setBounds(309, 183, 75, 23);
		getRootPane().setDefaultButton(btnOK);
		getContentPane().add(btnOK);

		JButton btnCancel = new JButton("Cancel");
		btnCancel.addActionListener(new ButtonCancelActionListener());
		btnCancel.setBounds(395, 183, 75, 23);
		getContentPane().add(btnCancel);
		
		JPanel panel = new JPanel();
		panel.setBackground(SystemColor.control);
		panel.setBorder(BorderFactory.createTitledBorder("Output wave settings"));
		panel.setBounds(276, 48, 209, 125);
		getContentPane().add(panel);
		panel.setLayout(null);
		
		JLabel lblNewLabel_1 = new JLabel("Points for each waveform");
		lblNewLabel_1.setBounds(19, 27, 161, 15);
		panel.add(lblNewLabel_1);
		
		JLabel lblTheDataCount = new JLabel("Waveform out frequency:");
		lblTheDataCount.setBounds(19, 72, 161, 15);
		panel.add(lblTheDataCount);
		
		JLabel lblFormAWaveform = new JLabel("Hz");
		lblFormAWaveform.setBounds(162, 97, 25, 15);
		panel.add(lblFormAWaveform);
		
		txtPointCount = new JFormattedTextField(NumberFormat.getIntegerInstance());
		txtPointCount.setValue(new Integer(400));
		txtPointCount.setBounds(19, 47, 141, 21);
		txtPointCount.addPropertyChangeListener(new PointCountListener());
		panel.add(txtPointCount);
		txtPointCount.setColumns(10);
		
		txtClockRate = new JFormattedTextField(NumberFormat.getNumberInstance());
		txtClockRate.setValue(new Double(1000));
		txtClockRate.setColumns(10);
		txtClockRate.setBounds(19, 94, 141, 21);
		txtClockRate.addPropertyChangeListener(new ClockRateListener());
		panel.add(txtClockRate);
		
		JPanel panel_1 = new JPanel();
		panel_1.setLayout(null);
		panel_1.setBackground(SystemColor.control);
		panel_1.setBorder(BorderFactory.createTitledBorder("Streaming AO settings"));
		panel_1.setBounds(10, 48, 256, 125);
		getContentPane().add(panel_1);

		cmbValueRange = new JComboBox();
		cmbValueRange.setBounds(110, 93, 128, 21);
		panel_1.add(cmbValueRange);

		JLabel lblValueRange = new JLabel("Value range:");
		lblValueRange.setBounds(20, 96, 90, 15);
		panel_1.add(lblValueRange);

		JLabel lblChannelCount = new JLabel("Channel count:");
		lblChannelCount.setBounds(20, 66, 90, 15);
		panel_1.add(lblChannelCount);

		cmbChannelCount = new JComboBox();
		cmbChannelCount.setBounds(110, 63, 128, 21);
		panel_1.add(cmbChannelCount);

		cmbChannelStart = new JComboBox();
		cmbChannelStart.setBounds(110, 33, 128, 21);
		panel_1.add(cmbChannelStart);

		JLabel lblChannelStart = new JLabel("Channel start:");
		lblChannelStart.setBounds(20, 36, 90, 15);
		panel_1.add(lblChannelStart);
		
		JLabel lblProfile = new JLabel("Profile:");
		lblProfile.setBounds(250, 20, 41, 15);
		getContentPane().add(lblProfile);
		
		txtProfilePath = new JFormattedTextField();
		txtProfilePath.setBounds(295, 17, 88, 20);
		getContentPane().add(txtProfilePath);
		
		btnBrowse = new JButton("Browse");
		btnBrowse.setBounds(396, 16, 89, 23);
		getContentPane().add(btnBrowse);
		btnBrowse.addActionListener(new ButtonBrowseActionListener());
		
		getContentPane().setFocusTraversalPolicy(
				new FocusTraversalOnArray(new Component[] { cmbDevice, cmbChannelStart,
						cmbChannelCount, cmbValueRange, txtPointCount, txtClockRate, btnOK,
						btnCancel }));

		Initialization();
	}

	/**
	 * 
	 * Build Date:2011-9-8
	 * Author:Administrator
	 * Function Description: This function is used to initialize the Configure dialog.
	 */
	protected void Initialization() {
		BufferedAoCtrl bufferedAoCtrl = new BufferedAoCtrl();
		ArrayList<DeviceTreeNode> installedDevice = bufferedAoCtrl.getSupportedDevices();

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
	 * 
	 * Build Date:2011-9-8
	 * Author:Administrator
	 * Function Description: This function is used to show the error massage to user.
	 * 
	 * @param message: the message shown to users!
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
	 * Class Function Description: This class is used to listen the device comboBox's
	 * 							   item selected changing action.
	 */
	class ComboBoxDiveceItemListener implements ItemListener{
		public void itemStateChanged(ItemEvent e) {
			String selected = ((JComboBox) e.getSource()).getSelectedItem().toString();
			if (e.getStateChange() == ItemEvent.SELECTED) {
				btnOK.setEnabled(true);
				try {
					BufferedAoCtrl bufferedAoCtrl = new BufferedAoCtrl();
					bufferedAoCtrl.setSelectedDevice(new DeviceInformation(selected));
					AoFeatures feature = bufferedAoCtrl.getFeatures();

					for (int i = 1; i < 3; i++) {
						cmbChannelCount.addItem(i);
					}

					for (int i = 0; i < feature.getChannelCountMax(); i++) {
						cmbChannelStart.addItem(i);
					}

					ValueRange[] value = feature.getValueRanges();
					for (ValueRange i : value) {
						if(i == ValueRange.V_ExternalRefBipolar || 
								i == ValueRange.V_ExternalRefUnipolar){
							continue;
						}
						cmbValueRange.addItem(i);
					}
					
					bufferedAoCtrl.Cleanup();
					
					//set the initialized position of the comboBox.
					cmbChannelStart.setSelectedIndex(0);
					cmbChannelCount.setSelectedIndex(1);
					cmbValueRange.setSelectedIndex(0);
				} catch (Exception except) {
					ShowMessage("Sorry, there're some errors occured: " + except.toString());
					btnOK.setEnabled(false);
					return;
				}
			}else{
				cmbChannelStart.removeAllItems();
				cmbChannelCount.removeAllItems();
				cmbValueRange.removeAllItems();
			}
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the data count per channel 
	 * 							   textField's text changing action.
	 */
	class PointCountListener implements PropertyChangeListener{
		@Override
		public void propertyChange(PropertyChangeEvent evt) {
			int pointCount = ((Number)txtPointCount.getValue()).intValue();
			if(pointCount < 1){
				txtPointCount.setValue(new Integer(400));
			}
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the clock rate per channel 
	 * 							   textField's text changing action.
	 */
	class ClockRateListener implements PropertyChangeListener{
		@Override
		public void propertyChange(PropertyChangeEvent evt) {
			double clockRate= ((Number)txtClockRate.getValue()).doubleValue();
			if(clockRate <= 0){
				txtClockRate.setValue(new Integer(1000));
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
			StreamingAO parrent = (StreamingAO) getParent();

			parrent.configure.deviceName = cmbDevice.getSelectedItem().toString();
			parrent.configure.channelStart = cmbChannelStart.getSelectedIndex();
			//We plus 1 because the index of comboBox's selected item is start with 0.
			parrent.configure.channelCount = cmbChannelCount.getSelectedIndex() + 1;
			parrent.configure.valueRange = (ValueRange)cmbValueRange.getSelectedItem();
			parrent.configure.pointCountPerWave = ((Number)txtPointCount.getValue()).intValue();
			parrent.configure.clockRate = ((Number)txtClockRate.getValue()).doubleValue();

			parrent.Initialization();
			parrent.setVisible(true);
			setVisible(false);
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the Cancel button's action! 
	 */
	class ButtonCancelActionListener implements ActionListener{
		public void actionPerformed(ActionEvent arg0) {
			if (isFirstLoad) {
				System.exit(0);
			} else {
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
