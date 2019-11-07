package AI_InstantAI;

import java.awt.*;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.net.MalformedURLException;
import java.util.ArrayList;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;

import Automation.BDaq.*;
import Common.ClassLoaderUtil;

public class ConfigureDialog extends JDialog {
	// define the serialization number.
	private static final long serialVersionUID = 1L;
	
	private JComboBox cmbDevice;
	private JComboBox cmbChannelStart;
	private JComboBox cmbChannelCount;
	private JComboBox cmbValueRange;
	private JButton btnOK;
	private JButton btnBrowse;
	private JFormattedTextField txtProfilePath;
	
	private InstantAiCtrl instantAi = new InstantAiCtrl();
	
	public boolean isFirstLoad = true;

	/**
	 * 
	 *Build Date:2011-8-6
	 *Author:Administrator
	 *Function Description: Create the dialog.
	 */
	public ConfigureDialog(InstantAI parrent) {
		super(parrent);
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());

		getContentPane().setBackground(SystemColor.control);
		setTitle("Instant AI - Configuration");
		setResizable(false);
		setBounds(100, 100, 384, 271);
		getContentPane().setLayout(null);

		JLabel lblNewLabel = new JLabel("Device:");
		lblNewLabel.setBounds(22, 13, 64, 15);
		getContentPane().add(lblNewLabel);
		
		JPanel panel = new JPanel();
		panel.setBackground(SystemColor.control);
		panel.setBounds(10, 71, 358, 129);
		panel.setBorder(BorderFactory.createTitledBorder("Instant AI settings"));
		getContentPane().add(panel);
		panel.setLayout(null);

		JLabel lblValueRange = new JLabel("Value range:");
		lblValueRange.setBounds(22, 90, 95, 15);
		panel.add(lblValueRange);

		cmbValueRange = new JComboBox();
		cmbValueRange.setBounds(119, 87, 210, 21);
		panel.add(cmbValueRange);

		JLabel lblChannelCount = new JLabel("Channel count:");
		lblChannelCount.setBounds(22, 60, 95, 15);
		panel.add(lblChannelCount);

		cmbChannelCount = new JComboBox();
		cmbChannelCount.setBounds(119, 57, 210, 21);
		panel.add(cmbChannelCount);

		JLabel lblChannelStart = new JLabel("Channel start:");
		lblChannelStart.setBounds(22, 30, 95, 15);
		panel.add(lblChannelStart);

		cmbChannelStart = new JComboBox();
		cmbChannelStart.setBounds(119, 27, 210, 21);
		panel.add(cmbChannelStart);

		cmbDevice = new JComboBox();
		cmbDevice.addItemListener(new ComboBoxDiveceItemListener());
		cmbDevice.setBounds(91, 10, 257, 21);
		getContentPane().add(cmbDevice);

		btnOK = new JButton("OK");
		btnOK.addActionListener(new ButtonOKActionListener());
		btnOK.setBounds(145, 211, 75, 23);
		getRootPane().setDefaultButton(btnOK);
		getContentPane().add(btnOK);

		JButton btnCancel = new JButton("Cancel");
		btnCancel.addActionListener(new ButtonCancelActionListener());
		btnCancel.setBounds(273, 211, 75, 23);
		getContentPane().add(btnCancel);
		
		JLabel lblProfile = new JLabel("Profile:");
		lblProfile.setBounds(22, 45, 46, 15);
		getContentPane().add(lblProfile);
		
		txtProfilePath = new JFormattedTextField();
		txtProfilePath.setBounds(91, 42, 158, 20);
		getContentPane().add(txtProfilePath);
		
		btnBrowse = new JButton("Browse");
		btnBrowse.setBounds(259, 42, 89, 23);
		getContentPane().add(btnBrowse);
		btnBrowse.addActionListener(new ButtonBrowseActionListener());
		Initialization();
	}

	/**
	 * 
	 * Build Date:2011-8-6 
	 * Author:Administrator
	 * Function Description: This function is used to initialize the Configure dialog
	 */
	protected void Initialization() {
		ArrayList<DeviceTreeNode> installedDevice = instantAi.getSupportedDevices();

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
	 * Build Date:2011-8-6 
	 * Author:Administrator
	 * Function Description: This function is used to show the error massage to user!
	 * 
	 * @param message: the message shown to users!
	 */
	protected void ShowMessage(String message) {
		JOptionPane.showMessageDialog(this, message, "Warning MessageBox", JOptionPane.WARNING_MESSAGE);
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
	 * 							   item selected changing action! 
	 */
	class ComboBoxDiveceItemListener implements ItemListener{
		public void itemStateChanged(ItemEvent e) {
			String selected = ((JComboBox) e.getSource()).getSelectedItem().toString();
			if (e.getStateChange() == ItemEvent.SELECTED) {
				btnOK.setEnabled(true);
				try {
					instantAi.setSelectedDevice(new DeviceInformation(selected));
					AiFeatures feature = instantAi.getFeatures();

					/**
					 * Note that: as a demo, We needn't draw to much channels in one graph, 
					 * So we define the channel count as an integer less than 16.
					 */
					int channelCount = instantAi.getChannelCount();
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
					for (ValueRange i : value) {
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
			}else{
				cmbChannelStart.removeAllItems();
				cmbChannelCount.removeAllItems();
				cmbValueRange.removeAllItems();
				return;
			}
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the OK button's action! 
	 */
	class ButtonOKActionListener implements ActionListener{
		public void actionPerformed(ActionEvent arg0) {
			/**
			 * get the array of the selected device's value range,and then use the ComboBox's 
			 * selected index as the index of value range array. so we can get the value range 
			 * which users have selected.
			 */
			InstantAI parrent = (InstantAI) getParent();
			
			parrent.configure.deviceName = cmbDevice.getSelectedItem().toString();
			parrent.configure.channelStart = cmbChannelStart.getSelectedIndex();
			//We plus 1 because the index of comboBox's selected item is start with 0.
			parrent.configure.channelCount = cmbChannelCount.getSelectedIndex() + 1;
			parrent.configure.valueRange = (ValueRange)cmbValueRange.getSelectedItem();

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
