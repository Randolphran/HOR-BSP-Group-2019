package DI_DIPatternMatchInterrupt;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Point;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.net.MalformedURLException;
import java.util.ArrayList;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;
import javax.swing.filechooser.FileNameExtensionFilter;

import Automation.BDaq.*;
import Common.ClassLoaderUtil;

import javax.swing.JFormattedTextField;

public class ConfigureDialog extends JDialog {
	// define the serialization number.
	private static final long serialVersionUID = 1L;
	private final JPanel contentPanel = new JPanel();
	private final JPanel panel = new JPanel();
	private JComboBox cmbDevice;
	private JComboBox cmbPort;
	private DiPortUI enablePort;
	private DiPortUI pattern;
	private ImageIcon[] imageIcon = { 
			new BackgroundPanel("ButtonUp.png", "Up").getImageIcon(),
			new BackgroundPanel("ButtonDown.png", "Down").getImageIcon() 
			};
	private JButton btnOK;
	private JButton btnBrowse;
	private JFormattedTextField txtProfilePath;
	
	private InstantDiCtrl instantDiCtrl;
	public boolean isFirstLoad = true;
	
	/**
	 * 
	 * Build Date:2011-9-22
	 * Author:Administrator
	 * Function Description: Create the dialog.
	 */
	public ConfigureDialog(DIPatternMatchInterrupt parrent) {
		super(parrent);
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setResizable(false);
		setTitle("DI Pattern Match Interupt-Configuration");
		setBounds(100, 100, 358, 345);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBackground(SystemColor.control);
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);
		
		panel.setBackground(SystemColor.control);
		panel.setBorder(new TitledBorder(null, "", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panel.setBounds(22, 15, 305, 257);
		panel.setLayout(null);
		contentPanel.add(panel);
		
		cmbDevice = new JComboBox();
		cmbDevice.setBounds(69, 10, 214, 21);
		cmbDevice.addItemListener(new ComboBoxDiveceItemListener());
		panel.add(cmbDevice);
		
		JLabel lblDevice = new JLabel("Device:");
		lblDevice.setBounds(10, 13, 54, 15);
		panel.add(lblDevice);
		
		cmbPort = new JComboBox();
		cmbPort.setBounds(69, 81, 214, 21);
		cmbPort.addItemListener(new ComboBoxPortItemListener());
		panel.add(cmbPort);
		
		JLabel lblDiPort = new JLabel("DI port:");
		lblDiPort.setBounds(10, 84, 54, 15);
		panel.add(lblDiPort);
		
		JLabel lblNewLabel = new JLabel("Enabled channels:");
		lblNewLabel.setBounds(10, 123, 128, 15);
		panel.add(lblNewLabel);
		
		JLabel lblMatchedValue = new JLabel("Matched value:");
		lblMatchedValue.setBounds(10, 182, 128, 29);
		panel.add(lblMatchedValue);
		
		JLabel lblProfile = new JLabel("Profile:");
		lblProfile.setBounds(10, 52, 54, 21);
		panel.add(lblProfile);
		
		txtProfilePath = new JFormattedTextField();
		txtProfilePath.setBounds(69, 50, 120, 20);
		panel.add(txtProfilePath);
		
		btnBrowse = new JButton("Browse");
		btnBrowse.setBounds(199, 47, 84, 23);
		panel.add(btnBrowse);
		btnBrowse.addActionListener(new ButtonBrowseActionListener());
		
		btnOK = new JButton("OK");
		btnOK.setBounds(120, 283, 69, 23);
		btnOK.addActionListener(new ButtonOKActionListener());
		contentPanel.add(btnOK);
		
		JButton btnCancel = new JButton("Cancel");
		btnCancel.setBounds(228, 283, 75, 23);
		btnCancel.addActionListener(new ButtonCancelActionListener());
		contentPanel.add(btnCancel);
		
		Initialization();
	}
	
	/**
	 * 
	 * Build Date:2011-9-22
	 * Author:Administrator
	 * Function Description: This function is used to initialize the Configure dialog
	 */
	protected void Initialization() {
		instantDiCtrl = new InstantDiCtrl();
		ArrayList<DeviceTreeNode> installedDevice = instantDiCtrl.getSupportedDevices();

		if (installedDevice.size() <= 0) {
			ShowMessage("No device to support the currently demonstrated function!");
			System.exit(0);
		}else{
			for(int i = 0; i < installedDevice.size(); i++){
				DeviceTreeNode node = installedDevice.get(i);
				try{
					DeviceInformation devInfo = new DeviceInformation(node.Description);
					devInfo.DeviceMode = AccessMode.ModeRead;
					instantDiCtrl.setSelectedDevice(devInfo);
					DiPmintPort[] diPmintPorts = instantDiCtrl.getDiPmintPorts();
					if(diPmintPorts == null){
						continue;
					}
				}catch(Exception e){
					continue;
				}
				cmbDevice.addItem(node.Description);
			}
			instantDiCtrl.Cleanup();
			cmbDevice.setSelectedIndex(0);
		}
	}
	
	/**
	 * 
	 * Build Date:2011-9-22
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
					instantDiCtrl.setSelectedDevice(new DeviceInformation(selected));

					DiPmintPort[] diPminPort = instantDiCtrl.getDiPmintPorts();				
					for(DiPmintPort port : diPminPort){
						cmbPort.addItem(String.valueOf(port.getPort()));
					}
					cmbPort.setSelectedIndex(0);
						
				} catch (Exception except) {
					ShowMessage("Sorry, Errors occured: " + except.toString());
					btnOK.setEnabled(false);
					return;
				}
			}else{
				cmbPort.removeAllItems();
				return;
			}
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the port comboBox's
	 * 							   item selected changing action! 
	 */
	class ComboBoxPortItemListener implements ItemListener{
		public void itemStateChanged(ItemEvent e) {

			if (e.getStateChange() == ItemEvent.SELECTED) {
				DiPmintPort[] diPminPort = instantDiCtrl.getDiPmintPorts();

				if (enablePort == null && pattern == null) {
					enablePort = new DiPortUI(0, panel, new Point(10, 95), imageIcon,
							diPminPort[cmbPort.getSelectedIndex()].getMask());

					pattern = new DiPortUI(1, panel, new Point(10, 158), imageIcon,
							diPminPort[cmbPort.getSelectedIndex()].getPattern());

					enablePort.setIsEditable(true);
					enablePort.setMask((byte) 0xFF);
					enablePort.setState((byte)0x01);
					
					pattern.setIsEditable(true);
					pattern.setMask((byte) 0xFF);
					pattern.setState((byte)0xFF);
				} else {
					enablePort.setState(diPminPort[cmbPort.getSelectedIndex()].getMask());
					pattern.setState(diPminPort[cmbPort.getSelectedIndex()].getPattern());
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
			if(enablePort.getState() == 0){
				ShowMessage("Please enable one bit at lest!");
				return;
			}
			
			DIPatternMatchInterrupt parrent = (DIPatternMatchInterrupt) getParent();
			parrent.configure.deviceName = cmbDevice.getSelectedItem().toString();
			parrent.configure.selectedPortIndex = cmbPort.getSelectedIndex();
			parrent.configure.enablePort = enablePort.getState();
			parrent.configure.pattern = pattern.getState();

			parrent.Initialization();
			parrent.setVisible(true);
			setVisible(false);
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the Cancel button's action.
	 */
	class ButtonCancelActionListener implements ActionListener{
		public void actionPerformed(ActionEvent arg0) {
			if (isFirstLoad) {
				System.exit(0);
			} else {
				DIPatternMatchInterrupt parrent = (DIPatternMatchInterrupt) getParent();
				parrent.Initialization();
				parrent.setVisible(true);
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

/**
 * 
 * @author Administrator
 * Class Function Description: This class is used to define the UI of one port.
 */
class DiPortUI extends JPanel{
	/**
	 * define the serialization number.
	 */
	private static final long serialVersionUID = 1L;
	
	private JPanel highBytes = new JPanel();
	private JPanel lowBytes = new JPanel();
	private JLabel[] bytesLevel = new JLabel[8];
	private JLabel lblHexValue = new JLabel("00");
	private ImageIcon[] imageIcon ;

	private int  key;
	private byte mask = 0;
	private byte state = 0;
	private boolean isEditable = false;
	
	public interface StateChangeListener{
		public void StateChangeAction(Object sender);
	}
	
	public DiPortUI(int index, JPanel parrent, Point location, ImageIcon[] image, byte state) {
		key = index;
		this.state = state;
		imageIcon = image;

		highBytes.setBounds(location.x, location.y + 50, 115, 30);
		highBytes.setLayout(null);
		highBytes.setBackground(SystemColor.control);
		highBytes.setBorder(BorderFactory.createLineBorder(Color.gray));
		parrent.add(highBytes);

		lowBytes.setBounds(location.x + 125, location.y + 50, 115, 30);
		lowBytes.setLayout(null);
		lowBytes.setBackground(SystemColor.control);
		lowBytes.setBorder(BorderFactory.createLineBorder(Color.gray));
		parrent.add(lowBytes);

		lblHexValue.setBounds(location.x + 250, location.y + 54, 35, 23);
		lblHexValue.setHorizontalAlignment(SwingConstants.CENTER);
		lblHexValue.setBorder(BorderFactory.createLineBorder(Color.gray));
		parrent.add(lblHexValue);

		for (int i = 0; i < 4; i++) {
			
			bytesLevel[i] = new JLabel(imageIcon[(state >> i) & 0x1]);
			bytesLevel[i].setBounds(5 + i * 25, 3, 26, 26);
			bytesLevel[i].addMouseListener(new MouseClickListener());
			highBytes.add(bytesLevel[i]);

			bytesLevel[i + 4] = new JLabel(imageIcon[(state >> i) & 0x1]);
			bytesLevel[i + 4].setBounds(5 + i * 25, 3, 26, 26);
			bytesLevel[i + 4].addMouseListener(new MouseClickListener());
			lowBytes.add(bytesLevel[i + 4]);
		}
	}

	public int getKey(){
		return key;
	}
	
	public byte getMask(){
		return mask;
	}
	
	public void setMask(byte value){
		mask = value;
	}
	
	public byte getState(){
		return state;
	}
	
	public void setState(byte state){
		this.state = state;
		Refresh();
	}
	
	public boolean getIsEditable(){
		return isEditable;
	}
	
	public void setIsEditable(boolean value){
		isEditable = value;
	}
	
	private void Refresh() {

		int bitValue = 0;
		for (int i = 7; i >= 0; i--) {
			bitValue = (state >> (7 - i)) & 0x1;
			bytesLevel[i].setIcon(imageIcon[bitValue]); 
		}

		lblHexValue.setText(Integer.toHexString(state | 0xFFFFFF00).toUpperCase().substring(6));
	}
	
	class MouseClickListener extends MouseAdapter{
		@Override
		public void mouseClicked(MouseEvent e) {
			int bitIndex = 0;
			JLabel source = (JLabel) e.getSource();
			if (isEditable) {
				for (int i = 0; i < 8; i++) {
					if (source == bytesLevel[i]) {
						bitIndex = i;
					}
				}
				if ((mask >> 7 - bitIndex & 0x1) == 1) {
					if ((state >> 7 - bitIndex & 0x1) == 1) {
						state = (byte) (state & ~(0x1 << 7 - bitIndex));
						bytesLevel[bitIndex].setIcon(imageIcon[0]);

					} else {
						state = (byte) (state | (0x1 << 7 - bitIndex));
						bytesLevel[bitIndex].setIcon(imageIcon[1]);
					}
					lblHexValue.setText(Integer.toHexString(state | 0xFFFFFF00).toUpperCase()
							.substring(6));
				}
			}
		}
	}
}
