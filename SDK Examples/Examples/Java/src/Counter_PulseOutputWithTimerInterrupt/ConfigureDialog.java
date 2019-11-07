package Counter_PulseOutputWithTimerInterrupt;

import java.awt.BorderLayout;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.net.MalformedURLException;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.filechooser.FileNameExtensionFilter;

import Automation.BDaq.*;
import Common.ClassLoaderUtil;

import org.eclipse.wb.swing.FocusTraversalOnArray;

import java.awt.Component;

import javax.swing.JFormattedTextField;

public class ConfigureDialog extends JDialog {
	// define the serialization number.
	private static final long serialVersionUID = 1L;
	
	private final JPanel contentPanel = new JPanel();
	private JComboBox cmbDevice;
	private JComboBox cmbChannel;
	private JComboBox cmbModuleIndex;
	private JButton btnOK;
	private JButton btnBrowse;
	private JFormattedTextField txtProfilePath;
	public boolean isFirstLoad = true;
	

	/**
	 * 
	 * Build Date:2011-10-09 
	 * Author:Administrator
	 * Function Description: Create the dialog.
	 */
	public ConfigureDialog(PulseOutputWithTimerInterrupt parrent) {
		super(parrent);
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setTitle("Pulse Output With Timer Interrupt - Configuration");
		setResizable(false);
		setBounds(100, 100, 346, 230);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBackground(SystemColor.control);
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);		

		JLabel lblNewLabel = new JLabel("Device:");
		lblNewLabel.setBounds(20, 20, 36, 15);
		contentPanel.add(lblNewLabel);

		JLabel lblChannel = new JLabel("<html><body>Counter<br>Channel:</body></html>");
		lblChannel.setBounds(20, 89, 49, 28);
		contentPanel.add(lblChannel);
		
		cmbDevice = new JComboBox();
		cmbDevice.addItemListener(new ComboBoxDiveceItemListener());
		cmbDevice.setBounds(69, 17, 251, 21);
		contentPanel.add(cmbDevice);
		
		cmbChannel = new JComboBox();
		cmbChannel.setBounds(69, 89, 251, 21);
		contentPanel.add(cmbChannel);
		
		btnOK = new JButton("OK");
		btnOK.addActionListener(new ButtonOKActionListener());
		btnOK.setBounds(142, 167, 75, 23);
		getRootPane().setDefaultButton(btnOK);
		contentPanel.add(btnOK);

		JButton btnCancel = new JButton("Cancel");
		btnCancel.addActionListener(new ButtonCancelActionListener());
		btnCancel.setBounds(245, 167, 75, 23);
		contentPanel.add(btnCancel);
		
		JLabel lblModuleIndex = new JLabel("<html><body>Module<br> Index:</body></html>");
		lblModuleIndex.setBounds(20, 121, 49, 36);
		contentPanel.add(lblModuleIndex);
		
		cmbModuleIndex = new JComboBox();
		cmbModuleIndex.setBounds(69, 125, 251, 21);
		contentPanel.add(cmbModuleIndex);
		
		JLabel lblProfile = new JLabel("Profile:");
		lblProfile.setBounds(20, 58, 42, 15);
		contentPanel.add(lblProfile);
		
		txtProfilePath = new JFormattedTextField();
		txtProfilePath.setBounds(68, 55, 149, 20);
		contentPanel.add(txtProfilePath);
		
		btnBrowse = new JButton("Browse");
		btnBrowse.setBounds(231, 54, 89, 23);
		contentPanel.add(btnBrowse);
		btnBrowse.addActionListener(new ButtonBrowseActionListener());
		
		contentPanel.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[]{
				cmbDevice, cmbChannel, btnOK, btnCancel}));
		
		Initialization();
	}
	/**
	 * 
	 * Build Date:2011-10-09 
	 * Author:Administrator
	 * Function Description: This function is used to initialize the Configuration dialog.
	 */
	protected void Initialization() {
		TimerPulseCtrl timerPulseCtrl = new TimerPulseCtrl();
		ArrayList<DeviceTreeNode> installedDevice = timerPulseCtrl.getSupportedDevices();

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
	 * Build Date:2011-10-09
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
				TimerPulseCtrl timerPulseCtrl = new TimerPulseCtrl();
				btnOK.setEnabled(true);
				try {
					timerPulseCtrl.setSelectedDevice(new DeviceInformation(selected));
					CntrFeatures feature = timerPulseCtrl.getFeatures();
					int channelCountMax = feature.getChannelCountMax();
					CounterCapabilityIndexer capabilityIndexer = feature.getCapabilities();
					
					for(int i = 0; i < channelCountMax; i++){
						CounterCapability[] capability = capabilityIndexer.getItem(i);
						for(CounterCapability cap : capability){
							if(cap == CounterCapability.TimerPulse){
								cmbChannel.addItem(String.valueOf(i));
								break;
							}
						}
					}
					
					ArrayList<DeviceTreeNode> supportDevice = timerPulseCtrl.getSupportedDevices();
					for (int i = 0; i < supportDevice.size(); i++) {
						DeviceTreeNode devNode = supportDevice.get(i);
						if (devNode.DeviceNumber == timerPulseCtrl.getDevice().getDeviceNumber()) {
							for (int j = 0; j < devNode.ModulesIndex.length; j++) {
								if(devNode.ModulesIndex[j] != -1)
								cmbModuleIndex.addItem(String.valueOf(devNode.ModulesIndex[j]));
							}
						}
					}
					
					timerPulseCtrl.Cleanup();
				}catch (Exception except) {
					ShowMessage("Sorry, Some errors occured: " + except.toString());
					btnOK.setEnabled(false);
					return;
				}
				cmbChannel.setSelectedIndex(0);
				cmbModuleIndex.setSelectedIndex(0);
			}else{
				cmbChannel.removeAllItems();
				cmbModuleIndex.removeAllItems();
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
			PulseOutputWithTimerInterrupt parrent = (PulseOutputWithTimerInterrupt)getParent();
			parrent.configure.deviceName = cmbDevice.getSelectedItem().toString();
			parrent.configure.counterChannel = Integer.parseInt(cmbChannel.getSelectedItem().toString());
			parrent.configure.moduleIndex = Integer.parseInt(cmbModuleIndex.getSelectedItem().toString());
			
			parrent.Initialization();
			parrent.setVisible(true);
			setVisible(false);
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
