package DO_StaticDO;

import java.awt.BorderLayout;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
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

import Automation.BDaq.DeviceTreeNode;
import Automation.BDaq.InstantDoCtrl;

import javax.swing.JFormattedTextField;

import Common.*;


public class ConfigureDialog extends JDialog {
	// define the serialization number.
	private static final long serialVersionUID = 1L;
	private final JPanel contentPanel = new JPanel();
	private JComboBox cmbDevice;
	
	public boolean isFirstLoad = true;
	public InstantDoCtrl instantDoCtrl = new InstantDoCtrl();
	
	private JButton btnBrowse;
	private JFormattedTextField txtProfilePath;
	
	/**
	 * 
	 *Build Date:2011-9-20
	 *Author:Administrator
	 *Function Description: Create the dialog.
	 */
	public ConfigureDialog(StaticDO parent) {
		super(parent);
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setResizable(false);
		setTitle("Static DO - Configuration");
		setBounds(100, 100, 323, 177);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBackground(SystemColor.control);
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);
		
		cmbDevice = new JComboBox();
		cmbDevice.setBounds(60, 25, 226, 21);
		contentPanel.add(cmbDevice);
		
		JLabel lblDevice = new JLabel("Device:");
		lblDevice.setBounds(17, 28, 44, 15);
		contentPanel.add(lblDevice);
		
		JButton btnOK = new JButton("OK");
		btnOK.setBounds(91, 111, 69, 23);
		btnOK.addActionListener(new ButtonOKActionListener());
		contentPanel.add(btnOK);
		
		JButton btnCancel = new JButton("Cancel");
		btnCancel.setBounds(201, 111, 75, 23);
		btnCancel.addActionListener(new ButtonCancelActionListener());
		contentPanel.add(btnCancel);
		
		JLabel lblProfilePath = new JLabel("Profile:");
		lblProfilePath.setBounds(17, 71, 44, 15);
		contentPanel.add(lblProfilePath);
		
		btnBrowse = new JButton("Browse");
		btnBrowse.setBounds(201, 67, 85, 23);
		btnBrowse.addActionListener(new ButtonBrowseActionListener());
		contentPanel.add(btnBrowse);
		
		txtProfilePath = new JFormattedTextField();
		txtProfilePath.setBounds(60, 68, 131, 20);
		contentPanel.add(txtProfilePath);
		
		Initialization();
	}
	
	/**
	 * 
	 *Build Date:2011-9-20
	 *Author:Administrator
	 *Function Description: this function is used to initialize the configure dialog.
	 */
	private void Initialization(){
		InstantDoCtrl instantDoCtrl = new InstantDoCtrl();
		ArrayList<DeviceTreeNode> installedDevice = instantDoCtrl.getSupportedDevices();
		
		if(installedDevice.size() <= 0){
			ShowMessage("No device to support the currently demonstrated function!");
			System.exit(0);
		}else{
			for(DeviceTreeNode installed : installedDevice){
				cmbDevice.addItem(installed.toString());
			}
			cmbDevice.setSelectedIndex(0);
		}
	}
	
	/**
	 * 
	 *Build Date:2011-9-20
	 *Author:Administrator
	 *Function Description: this function is used to get device name.
	 * @return String device name
	 */
	public String GetDeviceName(){
		return cmbDevice.getSelectedItem().toString();
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
	 * Build Date:2011-9-20
	 * Author:Administrator
	 * Function Description: This function is used to show the error massage to user!
	 * 
	 * @param message: the message shown to users!
	 */
	protected void ShowMessage(String message) {
		JOptionPane.showMessageDialog(this, message, "Warning MessageBox",
				JOptionPane.WARNING_MESSAGE);
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the OK button's action! 
	 */
	class ButtonOKActionListener implements ActionListener{
		public void actionPerformed(ActionEvent arg0) {
			StaticDO parent = (StaticDO) getParent();
			parent.Initialization();
			parent.setVisible(true);
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
