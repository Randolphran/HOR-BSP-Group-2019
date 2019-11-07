package DI_DIInterrupt;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
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
import javax.swing.border.LineBorder;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.JScrollPane;

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
	private JPanel portPanel ;
	private JScrollPane scrollPanel;
	private DiPortUI[] diPortUI;
	private JButton btnOK;
	
	private ImageIcon[] imageIcon = { 
			new BackgroundPanel("ButtonUp.png", "Up").getImageIcon(),
			new BackgroundPanel("ButtonDown.png", "Down").getImageIcon(),
			new BackgroundPanel("ButtonDisabled.png", "Disable").getImageIcon()
			};
	
	public boolean isFirstLoad = true;
	public ConfigureParameter configure = new ConfigureParameter();
	private JButton btnBrowse;
	private JFormattedTextField txtProfilePath;

	/**
	 * 
	 *Build Date:2011-9-27
	 *Author:Administrator
	 *Function Description: Create the dialog.
	 */
	public ConfigureDialog(DIInterrupt parrent ) {
		super(parrent);
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setResizable(false);
		setTitle("DI Interrupt - Configuration");
		setBounds(100, 100, 375, 345);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBackground(SystemColor.control);
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPanel.setLayout(null);
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		
		scrollPanel = new JScrollPane();
		scrollPanel.setBorder(new LineBorder(new Color(0, 0, 0)));
		scrollPanel.setBounds(20, 146, 325, 122);
		contentPanel.add(scrollPanel);
		
		portPanel = new JPanel();
		scrollPanel.setViewportView(portPanel);
		portPanel.setPreferredSize(new Dimension(310, 100));
		portPanel.setBackground(SystemColor.control);
		portPanel.setLayout(null);
		
		btnOK = new JButton("OK");
		btnOK.setBounds(146, 279, 69, 23);
		btnOK.addActionListener(new ButtonOKActionListener());
		contentPanel.add(btnOK);
		
		JButton btnCancel = new JButton("Cancel");
		btnCancel.setBounds(249, 279, 75, 23);
		btnCancel.addActionListener(new ButtonCancelActionListener());
		contentPanel.add(btnCancel);
		
		JLabel lblDevice = new JLabel("Device:");
		lblDevice.setBounds(20, 25, 54, 15);
		contentPanel.add(lblDevice);
		
		cmbDevice = new JComboBox();
		cmbDevice.setBounds(79, 22, 266, 21);
		cmbDevice.addItemListener(new ComboBoxDiveceItemListener());
		contentPanel.add(cmbDevice);
		
		JLabel lblNewLabel = new JLabel("Channel selection:");
		lblNewLabel.setBounds(20, 108, 128, 15);
		contentPanel.add(lblNewLabel);
		
		JLabel lblNewLabel_1 = new JLabel("CH#7");
		lblNewLabel_1.setBounds(79, 129, 41, 15);
		contentPanel.add(lblNewLabel_1);
		
		JLabel label = new JLabel("#0");
		label.setBounds(315, 129, 30, 15);
		contentPanel.add(label);
		
		JLabel lblProfilePath = new JLabel("Profile:");
		lblProfilePath.setBounds(20, 61, 54, 23);
		contentPanel.add(lblProfilePath);
		
		txtProfilePath = new JFormattedTextField();
		txtProfilePath.setBounds(79, 59, 172, 23);
		contentPanel.add(txtProfilePath);
		
		btnBrowse = new JButton("Browser");
		btnBrowse.setBounds(261, 59, 84, 23);
		contentPanel.add(btnBrowse);
		contentPanel.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[]{cmbDevice, btnOK, btnCancel}));
		btnBrowse.addActionListener(new ButtonBrowseActionListener());
		
		Initialization();
		
	}
	
	/**
	 * 
	 *Build Date:2011-9-27
	 *Author:Administrator
	 *Function Description: this function is used to initialize the configure dialog.
	 */
	private void Initialization(){
		InstantDiCtrl instantDiCtrl = new InstantDiCtrl();
		ArrayList<DeviceTreeNode> installedDevice = instantDiCtrl.getSupportedDevices();
		
		if(installedDevice.size() <= 0){
			ShowMessage("No device to support the currently demonstrated function!");
			System.exit(0);
		}else{
			for(int i = 0; i < installedDevice.size(); i++){
				DeviceTreeNode node = installedDevice.get(i);
				try{
					DeviceInformation devInfo = new DeviceInformation(node.Description);
					devInfo.DeviceMode = AccessMode.ModeRead;
					instantDiCtrl.setSelectedDevice(devInfo);
					DiintChannel[] intChannels = instantDiCtrl.getDiintChannels();
					if(intChannels == null){
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
	 * Build Date:2011-9-27
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
				InstantDiCtrl instantDiCtrl = new InstantDiCtrl();
				btnOK.setEnabled(true);
				try {
					instantDiCtrl.setSelectedDevice(new DeviceInformation(selected));			
				} catch (Exception except) {
					ShowMessage("Sorry, there're some errors occured: " + except.toString());
					btnOK.setEnabled(false);
					return;
				}
				
				DiintChannel[] intChannels = instantDiCtrl.getDiintChannels();
				byte[] ports = new byte[instantDiCtrl.getFeatures().getPortCount()];
				int enablePortCount = 0;
				
				for(int i = 0; i < intChannels.length; i++){
					int portIndex = intChannels[i].getChannel() / 8;
					int chIndex = intChannels[i].getChannel() % 8;
					ports[portIndex] |= 0x1 << chIndex; 
				}
				
				for(int i = 0; i < ports.length; i++){
					if(ports[i] != 0){
						enablePortCount++;
					}
				}
				
				int[] portIndexes = new int[enablePortCount];
				int j = 0;
				for(int i = 0; i < ports.length; i++){
					if(ports[i] != 0){
						portIndexes[j++] = i;
					}
				}
				
				diPortUI = new DiPortUI[enablePortCount];
				if(enablePortCount > 3){
					portPanel.setPreferredSize(new Dimension(310, enablePortCount * 40));
				}else{
					portPanel.setPreferredSize(new Dimension(310, 100));
				}
				scrollPanel.updateUI();
				portPanel.removeAll();
				portPanel.repaint();
				Point location = new Point(0, 0);
				for(int i = 0; i < enablePortCount; i++){
					diPortUI[i] = new DiPortUI(portIndexes[i], portPanel, location, imageIcon, 
							ports[portIndexes[i]]);
					location.y += 35;
					diPortUI[i].setIsEditable(true);
					diPortUI[i].setMask(ports[portIndexes[i]]);
					diPortUI[i].setState((byte)1);
				}
				
				instantDiCtrl.Cleanup();
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
			boolean selectChannel = false;
			for(int i = 0; i < diPortUI.length; i++){
				if(diPortUI[i].getState() != 0){
					selectChannel = true;
					break;
				}
			}
			if(!selectChannel){
				ShowMessage("Please enable one bit at lest!");
				return;
			}
			
			DIInterrupt parrent = (DIInterrupt) getParent();
			configure.deviceName = cmbDevice.getSelectedItem().toString();
			configure.selectedPortIndex = new int[diPortUI.length];
			configure.enableChannel = new byte[diPortUI.length];
			for(int i = 0; i < diPortUI.length; i++){
				configure.selectedPortIndex[i] = diPortUI[i].getKey();
				configure.enableChannel[i] = diPortUI[i].getState();
			}
			
			parrent.configure = configure;
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
				DIInterrupt parrent = (DIInterrupt) getParent();
				parrent.Initialization();
				parrent.setVisible(true);
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
	
}

/**
 * 
 * @author Administrator
 * Class Function Description: This class is used to create one DI port's UI.
 */
class DiPortUI extends JPanel {
	/**
	 * define the serialization number.
	 */
	private static final long serialVersionUID = 1L;
	
	private JLabel portIndex;
	private JPanel highBytes = new JPanel();
	private JPanel lowBytes = new JPanel();
	private JLabel[] bytesLevel = new JLabel[8];
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

		portIndex = new JLabel("Port" +index +": ");
		portIndex.setBounds(location.x, location.y + 4, 50, 23);
		portIndex.setHorizontalAlignment(SwingConstants.CENTER);
		portIndex.setBorder(BorderFactory.createLineBorder(Color.gray));
		parrent.add(portIndex);
		
		highBytes.setBounds(location.x + 55, location.y, 115, 30);
		highBytes.setLayout(null);
		highBytes.setBackground(SystemColor.control);
		highBytes.setBorder(BorderFactory.createLineBorder(Color.gray));
		parrent.add(highBytes);

		lowBytes.setBounds(location.x + 180, location.y, 115, 30);
		lowBytes.setLayout(null);
		lowBytes.setBackground(SystemColor.control);
		lowBytes.setBorder(BorderFactory.createLineBorder(Color.gray));
		parrent.add(lowBytes);

		for (int i = 0; i < 4; i++) {
			if((mask >> i) == 0 ){
				bytesLevel[i] = new JLabel(imageIcon[2]);
				bytesLevel[i + 4] = new JLabel(imageIcon[2]);
			}else{
				bytesLevel[i] = new JLabel(imageIcon[0]);
				bytesLevel[i + 4] = new JLabel(imageIcon[0]);
			}
			//bytesLevel[i] = new JLabel(imageIcon[(state >> i) & 0x1]);
			bytesLevel[i].setBounds(5 + i * 25, 3, 26, 26);
			bytesLevel[i].addMouseListener(new MouseClickListener());
			highBytes.add(bytesLevel[i]);

			
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
			if(((mask >> (7 - i)) & 0x1) == 1 ){
				bytesLevel[i].setIcon(imageIcon[bitValue]); 
			}
			
		}
	}
	public void EnableChannel(byte value){
		int bitValue = 0;
		for (int i = 7; i >= 0; i--) {
			bitValue = (mask >> (7 - i)) & 0x1;
			if(bitValue == 1){
				bytesLevel[i].setIcon(imageIcon[bitValue]); 
			}else{
				bytesLevel[i].setIcon(imageIcon[2]);
			}
			
		}
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
				}
			}
		}
	}
	
}

