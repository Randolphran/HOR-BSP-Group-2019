package AO_StaticAO;

import java.awt.SystemColor;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
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

import Automation.BDaq.*;
import Common.ClassLoaderUtil;

import org.eclipse.wb.swing.FocusTraversalOnArray;

import java.awt.Component;

import javax.swing.SwingConstants;
import javax.swing.filechooser.FileNameExtensionFilter;

public class ConfigureDialog extends JDialog {
	// define the serialization number.
	private static final long serialVersionUID = 1L;
	
	private JComboBox cmbDevice;
	private JComboBox cmbChannelStart;
	private JComboBox cmbChannelCount;
	private JComboBox cmbValueRange;
	private JFormattedTextField txtPointCount;
	private JButton btnOK;
	private JButton btnBrowse;
	private JFormattedTextField txtProfilePath;
	public boolean isFirstLoad = true;
	
	/**
	 * Build Date:2011-8-30
	 * Author:Administrator
	 * Function Description: Create the dialog.
	 */
	public ConfigureDialog(StaticAO parrent) {
		super(parrent);
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
		
		getContentPane().setBackground(SystemColor.control);
		setTitle("Static AO - Configuration");
		setResizable(false);
		setBounds(100, 100, 471, 245);
		getContentPane().setLayout(null);

		JLabel lblDevice = new JLabel("Device:");
		lblDevice.setBounds(15, 20, 53, 15);
		getContentPane().add(lblDevice);

		cmbDevice = new JComboBox();
		cmbDevice.addItemListener(new ComboBoxDiveceItemListener());
		cmbDevice.setBounds(61, 17, 146, 21);
		getContentPane().add(cmbDevice);

		btnOK = new JButton("OK");
		btnOK.addActionListener(new ButtonOKActionListener());
		btnOK.setBounds(275, 180, 75, 23);
		getRootPane().setDefaultButton(btnOK);
		getContentPane().add(btnOK);

		JButton btnCancel = new JButton("Cancel");
		btnCancel.addActionListener(new ButtonCancelActionListener());
		btnCancel.setBounds(368, 180, 75, 23);
		getContentPane().add(btnCancel);
		
		JPanel panel = new JPanel();
		panel.setBackground(SystemColor.control);
		panel.setBorder(BorderFactory.createTitledBorder("Output wave settings"));
		panel.setBounds(265, 45, 191, 121);
		getContentPane().add(panel);
		panel.setLayout(null);
		
		JLabel lblNewLabel_1 = new JLabel("Points for each waveform");
		lblNewLabel_1.setBounds(10, 23, 161, 15);
		panel.add(lblNewLabel_1);
		
		JLabel lblTheDataCount = new JLabel(
				"<html><body>The data count of AO to form<br> a waveform</body></html>");
		lblTheDataCount.setVerticalAlignment(SwingConstants.TOP);
		lblTheDataCount.setHorizontalAlignment(SwingConstants.LEFT);
		lblTheDataCount.setBounds(10, 76, 171, 42);
		panel.add(lblTheDataCount);
		
		txtPointCount = new JFormattedTextField(NumberFormat.getIntegerInstance());
		txtPointCount.setValue(new Integer(400));
		txtPointCount.setBounds(20, 45, 135, 21);
		txtPointCount.addPropertyChangeListener(new PointCountListener());
		panel.add(txtPointCount);
		txtPointCount.setColumns(10);
		
		JPanel panel_1 = new JPanel();
		panel_1.setLayout(null);
		panel_1.setBackground(SystemColor.control);
		panel_1.setBorder(BorderFactory.createTitledBorder("Static AO settings"));
		panel_1.setBounds(10, 45, 243, 121);
		getContentPane().add(panel_1);

		cmbValueRange = new JComboBox();
		cmbValueRange.setBounds(100, 85, 128, 21);
		panel_1.add(cmbValueRange);

		JLabel lblValueRange = new JLabel("Value range:");
		lblValueRange.setBounds(10, 88, 90, 15);
		panel_1.add(lblValueRange);

		JLabel lblChannelCount = new JLabel("Channel count:");
		lblChannelCount.setBounds(10, 58, 90, 15);
		panel_1.add(lblChannelCount);

		cmbChannelCount = new JComboBox();
		cmbChannelCount.setBounds(100, 55, 128, 21);
		panel_1.add(cmbChannelCount);

		cmbChannelStart = new JComboBox();
		cmbChannelStart.setBounds(100, 25, 128, 21);
		panel_1.add(cmbChannelStart);

		JLabel lblChannelStart = new JLabel("Channel start:");
		lblChannelStart.setBounds(10, 28, 90, 15);
		panel_1.add(lblChannelStart);
		
		JLabel lblProfile = new JLabel("Profile:");
		lblProfile.setBounds(217, 20, 53, 15);
		getContentPane().add(lblProfile);
		
		txtProfilePath = new JFormattedTextField();
		txtProfilePath.setBounds(265, 17, 93, 20);
		getContentPane().add(txtProfilePath);
		
		btnBrowse = new JButton("Browse");
		btnBrowse.setBounds(368, 16, 87, 23);
		getContentPane().add(btnBrowse);
		btnBrowse.addActionListener(new ButtonBrowseActionListener());
		
		getContentPane().setFocusTraversalPolicy(
				new FocusTraversalOnArray(new Component[] { cmbDevice, cmbChannelStart,
						cmbChannelCount, cmbValueRange, btnOK, btnCancel }));

		Initialization();
	}

	/**
	 * 
	 * Build Date:2011-9-1
	 * Author:Administrator
	 * Function Description: This function is used to initialize the Configure dialog
	 */
	protected void Initialization() {
		InstantAoCtrl instantAo = new InstantAoCtrl();
		ArrayList<DeviceTreeNode> installedDevice = instantAo.getSupportedDevices();

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
	 * Build Date:2011-9-1
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
					InstantAoCtrl instantAo = new InstantAoCtrl();
					instantAo.setSelectedDevice(new DeviceInformation(selected));
					AoFeatures feature = instantAo.getFeatures();

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
					
					instantAo.Cleanup();
					
					//set the initialized position of the comboBox.
					cmbChannelStart.setSelectedIndex(0);
					cmbChannelCount.setSelectedIndex(1);
					cmbValueRange.setSelectedIndex(0);
				} catch (Exception except) {
					ShowMessage("Sorry, there''re some errors occured:" + except.toString());
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
	 * Class Function Description: This class is used to listen the data count per channel 
	 * 							   textField's text changing action.
	 */
	class PointCountListener implements PropertyChangeListener{
		@Override
		public void propertyChange(PropertyChangeEvent evt) {
			int pointCount = ((Number)txtPointCount.getValue()).intValue();
			if(pointCount <1){
				txtPointCount.setValue(new Integer(400));
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
			StaticAO parrent = (StaticAO) getParent();
			
			parrent.configure.deviceName = cmbDevice.getSelectedItem().toString();
			parrent.configure.channelStart = cmbChannelStart.getSelectedIndex();
			//We plus 1 because the index of comboBox's selected item is start with 0.
			parrent.configure.channelCount = cmbChannelCount.getSelectedIndex() + 1;
			parrent.configure.valueRange = (ValueRange)cmbValueRange.getSelectedItem();
			parrent.configure.pointCountPerWave = ((Number)txtPointCount.getValue()).intValue();

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
