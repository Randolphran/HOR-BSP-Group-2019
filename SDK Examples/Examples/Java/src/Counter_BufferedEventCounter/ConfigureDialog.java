package Counter_BufferedEventCounter;

import java.awt.BorderLayout;
import java.awt.Checkbox;
import java.awt.CheckboxGroup;
import java.awt.GridLayout;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;

import javax.swing.AbstractButton;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.filechooser.FileNameExtensionFilter;

import Automation.BDaq.*;
import Common.ClassLoaderUtil;

import org.eclipse.wb.swing.FocusTraversalOnArray;

import java.awt.Component;
import java.io.File;
import java.net.MalformedURLException;

import javax.swing.JFormattedTextField;
import javax.swing.JTextField;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;
import javax.swing.UIManager;

import java.awt.Color;

import javax.swing.JScrollPane;
import javax.swing.SwingConstants;
import javax.swing.JRadioButton;

public class ConfigureDialog extends JDialog {
	// define the serialization number.
	private static final long serialVersionUID = 1L;
	
	private final JPanel contentPanel = new JPanel();
	private JComboBox cmbDevice;
	private JFormattedTextField txtProfilePath;
	private JComboBox cbxSampleClkSrc;
	private JFormattedTextField txtSectionLength;
	private JFormattedTextField txtSectionCount;
	
	private JComboBox cbxTrgSource;
	private JComboBox cbxTrgAction;
	private JComboBox cbxTrgEdge;
	private JFormattedTextField txtTrgLevel;
	
	private JRadioButton rdbtn_LoadProfile;
	private JRadioButton rdbtn_ManualConfigure;
	
	private JButton btnOK;
	private JButton btnBrowse;
	private JButton btnCancel;
    
	private JPanel panel_profile;
	private JPanel panel_manual;
	
	private JScrollPane scrollPane_1;
	private JPanel chkboxPanel; 
	
	private boolean[] channelEnabled;
	private int configureMode;
	
	private final int Profile_Configure = 1;
	private final int Manual_Configure = 0;
	
	public boolean isFirstLoad = true;
	
	BufferedEventCounterCtrl bfdEventCounterCtrl = new BufferedEventCounterCtrl();
	
	public void TriggerSourceChanged()
	{
		if(cbxTrgSource.getItemCount() > 0){
			SignalDrop trgSrc = (SignalDrop)cbxTrgSource.getSelectedItem();
			switch(trgSrc)
			{
			case SignalNone:
				txtTrgLevel.setEnabled(false);
				cbxTrgAction.setEnabled(false);
				cbxTrgEdge.setEnabled(false);
				break;
			case SigDiPatternMatch:
		    case SigDiStatusChange:
		    	txtTrgLevel.setEnabled(false);
				cbxTrgAction.setEnabled(true);
				cbxTrgEdge.setEnabled(false);
				break;
			default :
				txtTrgLevel.setEnabled(true);
				cbxTrgAction.setEnabled(true);
				cbxTrgEdge.setEnabled(true);
				break;
			}
		}
	}
	
	public void ComponentEnabled(int mode)
	{
		//load profile --> 1  /  manual configure --> 0
		if(mode == 1){
			txtSectionLength.setEnabled(false);
			txtSectionCount.setEnabled(false);
			cbxSampleClkSrc.setEnabled(false);
			cbxTrgSource.setEnabled(false);
			TriggerSourceChanged();
			txtProfilePath.setEnabled(true);
			btnBrowse.setEnabled(true);
			
			int count1 = chkboxPanel.getComponentCount();
			for(int i = 0; i < count1; i++){
				Component comp1 = chkboxPanel.getComponent(i);
				if(comp1 instanceof JCheckBox){
					JCheckBox chkbox = (JCheckBox)comp1;
					chkbox.setEnabled(false);
				}			
			}
		}else{
			txtSectionLength.setEnabled(true);
			txtSectionCount.setEnabled(true);
			cbxSampleClkSrc.setEnabled(true);
			cbxTrgSource.setEnabled(true);
			TriggerSourceChanged();
			txtProfilePath.setEnabled(false);
			btnBrowse.setEnabled(false);
			
			int count1 = chkboxPanel.getComponentCount();
			for(int i = 0; i < count1; i++){
				Component comp1 = chkboxPanel.getComponent(i);
				if(comp1 instanceof JCheckBox){
					JCheckBox chkbox = (JCheckBox)comp1;
					chkbox.setEnabled(true);
				}			
			}
		}
	}
	
	
	/**
	 * 
	 * Build Date:2011-9-29 
	 * Author:Administrator
	 * Function Description: Create the dialog.
	 */
	@SuppressWarnings("rawtypes")
	public ConfigureDialog(BufferedEventCounter parrent) {
		super(parrent);
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setTitle("Buffered Event Counter - Configuration");
		setResizable(false);
		setBounds(100, 100, 641, 506);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBackground(SystemColor.control);
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);		

		JLabel lblNewLabel = new JLabel("Device:");
		lblNewLabel.setBounds(23, 25, 52, 15);
		contentPanel.add(lblNewLabel);
		
		cmbDevice = new JComboBox();
		cmbDevice.addItemListener(new ComboBoxDiveceItemListener());
		cmbDevice.setBounds(76, 22, 215, 21);
		contentPanel.add(cmbDevice);
		
		btnOK = new JButton("OK");
		btnOK.addActionListener(new ButtonOKActionListener());
		btnOK.setBounds(340, 431, 75, 28);
		getRootPane().setDefaultButton(btnOK);
		contentPanel.add(btnOK);

	    btnCancel = new JButton("Cancel");
		btnCancel.addActionListener(new ButtonCancelActionListener());
		btnCancel.setBounds(493, 431, 75, 28);
		contentPanel.add(btnCancel);
		
		rdbtn_LoadProfile = new JRadioButton("Load Profile");
		rdbtn_LoadProfile.setBounds(23, 54, 121, 23);
		contentPanel.add(rdbtn_LoadProfile);
		
		rdbtn_ManualConfigure = new JRadioButton("Manual Configure");
		rdbtn_ManualConfigure.setBounds(146, 54, 145, 23);
		contentPanel.add(rdbtn_ManualConfigure);
		
		panel_profile = new JPanel();
		panel_profile.setBorder(new TitledBorder(null, "Using profile to configure the parameters", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panel_profile.setBounds(23, 83, 392, 72);
		contentPanel.add(panel_profile);
		panel_profile.setLayout(null);
		
		JLabel lblProfile = new JLabel("Profile:");
		lblProfile.setBounds(10, 33, 48, 15);
		panel_profile.add(lblProfile);
		
		txtProfilePath = new JFormattedTextField();
		txtProfilePath.setBounds(65, 30, 223, 20);
		panel_profile.add(txtProfilePath);
		
		btnBrowse = new JButton("Browse");
		btnBrowse.setBounds(298, 29, 84, 23);
		panel_profile.add(btnBrowse);
		
		panel_manual = new JPanel();
		panel_manual.setBorder(new TitledBorder(null, "Manual configure the parameters", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		panel_manual.setBounds(23, 165, 602, 256);
		contentPanel.add(panel_manual);
		panel_manual.setLayout(null);
		
		JPanel panel = new JPanel();
		panel.setBounds(10, 30, 272, 216);
		panel_manual.add(panel);
		panel.setBorder(new TitledBorder(UIManager.getBorder("TitledBorder.border"), "General Settings", TitledBorder.LEADING, TitledBorder.TOP, null, new Color(0, 0, 0)));
		panel.setLayout(null);
		
		JLabel lblsectionlength = new JLabel("Section Length:");
		lblsectionlength.setBounds(23, 99, 101, 21);
		panel.add(lblsectionlength);
		
		txtSectionLength = new JFormattedTextField();
		txtSectionLength.setBounds(122, 99, 120, 21);
		txtSectionLength.setValue(new Integer(1024));
		panel.add(txtSectionLength);
		txtSectionLength.setColumns(10);
		
		JLabel lblsectioncount = new JLabel("Section Count:");
		lblsectioncount.setBounds(23, 130, 84, 21);
		panel.add(lblsectioncount);
		
		txtSectionCount = new JFormattedTextField();
		txtSectionCount.setColumns(10);
		txtSectionCount.setBounds(122, 130, 120, 21);
		txtSectionCount.setValue(new Integer(0));
		panel.add(txtSectionCount);
		
		JLabel lblChannelCount = new JLabel("Sample Clock Source:");
		lblChannelCount.setBounds(23, 161, 132, 21);
		panel.add(lblChannelCount);
		
		cbxSampleClkSrc = new JComboBox();
		cbxSampleClkSrc.setBounds(23, 182, 219, 21);
		panel.add(cbxSampleClkSrc);
		
		scrollPane_1 = new JScrollPane();
		scrollPane_1.setBorder(null);
		scrollPane_1.setBounds(23, 25, 219, 64);
		panel.add(scrollPane_1);
		
		chkboxPanel = new JPanel();
		chkboxPanel.setBorder(new TitledBorder(UIManager.getBorder("TitledBorder.border"), "Enabled Channel", TitledBorder.LEADING, TitledBorder.TOP, null, new Color(0, 0, 0)));
		scrollPane_1.setViewportView(chkboxPanel);
		chkboxPanel.setLayout(new GridLayout(1, 0, 0, 0));
		
		JPanel panel_1 = new JPanel();
		panel_1.setBounds(294, 30, 298, 216);
		panel_manual.add(panel_1);
		panel_1.setBorder(new TitledBorder(UIManager.getBorder("TitledBorder.border"), "Trigger Settings", TitledBorder.LEADING, TitledBorder.TOP, null, new Color(0, 0, 0)));
		panel_1.setLayout(null);
		
		JLabel lblTriggerSource = new JLabel("Trigger Source:");
		lblTriggerSource.setBounds(17, 19, 90, 30);
		panel_1.add(lblTriggerSource);
		
		cbxTrgSource = new JComboBox();
		cbxTrgSource.setBounds(121, 26, 167, 21);
		cbxTrgSource.addItemListener(new ComboBoxTrgSrcItemListener());
		panel_1.add(cbxTrgSource);
		
		JLabel lblTriggerAction = new JLabel("Trigger Action:");
		lblTriggerAction.setBounds(17, 68, 90, 30);
		panel_1.add(lblTriggerAction);
		
		cbxTrgAction = new JComboBox();
		cbxTrgAction.setBounds(121, 73, 167, 21);
		panel_1.add(cbxTrgAction);
		
		JLabel lblTriggerEdge = new JLabel("Trigger Edge:");
		lblTriggerEdge.setBounds(17, 115, 90, 30);
		panel_1.add(lblTriggerEdge);
		
		cbxTrgEdge = new JComboBox();
		cbxTrgEdge.setBounds(121, 120, 167, 21);
		panel_1.add(cbxTrgEdge);
		
		JLabel lblTriggerLevel = new JLabel("Trigger Level:");
		lblTriggerLevel.setBounds(17, 162, 90, 30);
		panel_1.add(lblTriggerLevel);
		
		txtTrgLevel = new JFormattedTextField();
		txtTrgLevel.setBounds(121, 167, 134, 21);
		txtTrgLevel.setValue(new Double(3.0));
		panel_1.add(txtTrgLevel);
		txtTrgLevel.setColumns(10);
		
		JLabel lblV = new JLabel("V");
		lblV.setBounds(265, 163, 11, 30);
		panel_1.add(lblV);
		contentPanel.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[]{cmbDevice, btnOK, btnCancel, txtSectionLength, txtSectionCount, cbxSampleClkSrc, cbxTrgSource, cbxTrgAction, cbxTrgEdge, txtTrgLevel}));
		btnBrowse.addActionListener(new ButtonBrowseActionListener());
		rdbtn_LoadProfile.addActionListener(new rdbtnLoadProfileActionListener());
		rdbtn_ManualConfigure.addActionListener(new rdbtnManualConfigureActionListener());
		Initialization();
	}
	
	/**
	 * 
	 * Build Date:2011-9-29 
	 * Author:Administrator
	 * Function Description: This function is used to initialize the Configuration dialog.
	 */
	protected void Initialization() {
		ArrayList<DeviceTreeNode> installedDevice = bfdEventCounterCtrl.getSupportedDevices();

		if (installedDevice.size() <= 0) {
			ShowMessage("No device to support the currently demonstrated function!");
			System.exit(0);
		} else {
			for (DeviceTreeNode installed : installedDevice) {
				cmbDevice.addItem(installed.toString());
			}
			cmbDevice.setSelectedIndex(0);
		}
		
		ButtonGroup btnGroup = new ButtonGroup();
		btnGroup.add(rdbtn_LoadProfile);
		btnGroup.add(rdbtn_ManualConfigure);
		rdbtn_ManualConfigure.setSelected(true); // default selecte Manual configure parameters.
		panel_profile.setEnabled(false);
	}
	
	/**
	 *Build Date:2011-9-29 
	 *Author:Administrator
	 *Function Description: load the configuration parameters. 
	 */
	public void LoadConfiguration(ConfigureParameter configure){
		if(configure.configureMode == Manual_Configure){
			txtSectionLength.setValue(configure.sectionLength);   
			txtSectionCount.setValue(configure.sectionCount);
			cbxSampleClkSrc.setSelectedItem(configure.sampleClkSrc);
			cbxTrgSource.setSelectedItem(configure.triggerSource);
			cbxTrgAction.setSelectedItem(configure.triggerAction);
			cbxTrgEdge.setSelectedItem(configure.triggerEdge);
			txtTrgLevel.setValue(configure.triggerLevel);
				
			int count = chkboxPanel.getComponentCount();
			Component[] comp = chkboxPanel.getComponents();
			for (int i = 0; i < count; i++) {
				if(configure.channelEnabled[i]){
					((JCheckBox)comp[i]).setSelected(true);
				}else{
					((JCheckBox)comp[i]).setSelected(false);
				}
			}
		}
	}
	
	
	/**
	 * 
	 * Build Date:2011-9-29 
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
				btnOK.setEnabled(true);
				
				try {
					bfdEventCounterCtrl.setSelectedDevice(new DeviceInformation(selected));
					CntrFeatures feature = bfdEventCounterCtrl.getFeatures();
					final int channelCountMax = feature.getChannelCountMax();
					
					//Get configure mode
					if(rdbtn_LoadProfile.isSelected()){
						configureMode = Profile_Configure;  //load profile --> 1  /  manual configure --> 0	
					}else{
						configureMode = Manual_Configure;
					}
					ComponentEnabled(configureMode);
					
					//initial channelEnabled
					channelEnabled = new boolean[channelCountMax];
					
					//configure CheckBox for ChannelMap
					chkboxPanel.removeAll();
					for(int i = 0; i < channelCountMax; i++){
						String str = "CH";
						str = str + String.valueOf(i);
						JCheckBox ch_chkbox = new JCheckBox(str);
						chkboxPanel.add(ch_chkbox);					
						ch_chkbox.addItemListener(new ItemListener() {
				            @Override
				            public void itemStateChanged(ItemEvent e) {
				                JCheckBox cb = (JCheckBox)e.getSource();
				                String subStr = cb.getText().substring(2);
				                int channelIndex = Integer.parseInt(subStr);
				                //System.out.println("Checkbox "+ cb.getText() + "status£º" + cb.isSelected() + "sbuString is " + subStr);
				                
				                for(int i = 0; i <channelCountMax; i++){
				                	if(cb.isSelected()){
					                	channelEnabled[channelIndex] = true;
					                }else{
					                	channelEnabled[channelIndex] = false;
					                }
				                	//System.out.println(" channelEnabled["+ i + "]: " + channelEnabled[i] );
				                }				                				                
				            }
				        });
					}
					
					// Set Sample Clock Source Combo box
					cbxSampleClkSrc.removeAllItems();
					CounterClockSourceIndexer indexer =  feature.getEcSampleClockSources();
					SignalDrop[] clkSrc = indexer.getItem(0);
					if(indexer != null){
						for(int i = 0; i < clkSrc.length; i++)
						{
							cbxSampleClkSrc.addItem(clkSrc[i]);
							
						}
					}
					cbxSampleClkSrc.setSelectedIndex(0);
					
					// Set Trigger Source
					cbxTrgSource.removeAllItems();
					SignalDrop[] trgSrc = bfdEventCounterCtrl.getFeatures().getTriggerSources();
					if(trgSrc != null){
						for(int i = 0; i < trgSrc.length; i++)
						{
							cbxTrgSource.addItem(trgSrc[i]);
						}
					}
					cbxTrgSource.setSelectedIndex(0);
					
					// Set Trigger Action
					cbxTrgAction.removeAllItems();
					TriggerAction[] trgAct = bfdEventCounterCtrl.getFeatures().getTriggerActions();
					if(trgAct != null){
						for(int i = 0; i < trgAct.length; i++){
							cbxTrgAction.addItem(trgAct[i]);
						}
					}
					cbxTrgAction.setSelectedIndex(0);
					
					//Set trigger edge
					cbxTrgEdge.removeAllItems();
					cbxTrgEdge.addItem(ActiveSignal.RisingEdge);
					cbxTrgEdge.addItem(ActiveSignal.FallingEdge);
					cbxTrgEdge.setSelectedIndex(0);
				}catch (Exception except) {
					ShowMessage("Sorry, there're some errors occured: " + except.toString());
					btnOK.setEnabled(false);
					return;
				}	
			}else{
				btnOK.setEnabled(false);
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
			BufferedEventCounter parrent = (BufferedEventCounter)getParent();
			
			if(rdbtn_LoadProfile.isSelected()){
				//choose LoadProfile
				if( (txtProfilePath.getText() == null)|| (txtProfilePath.getText().length() < 1)){
					ShowMessage("Sorry, profile path is null, please select the device's profile");
				}else{
					parrent.configure.configureMode = Profile_Configure;
					parrent.configure.deviceName = cmbDevice.getSelectedItem().toString();
					parrent.Initialization();
					parrent.setVisible(true);
					setVisible(false);
				}
			}else{
				parrent.configure.deviceName = cmbDevice.getSelectedItem().toString();
				parrent.configure.sectionLength = ((Number)txtSectionLength.getValue()).intValue();
				parrent.configure.sectionCount = ((Number)txtSectionCount.getValue()).intValue();
				parrent.configure.sampleClkSrc = (SignalDrop)cbxSampleClkSrc.getSelectedItem();
				
				parrent.configure.triggerSource = (SignalDrop)cbxTrgSource.getSelectedItem();
				parrent.configure.triggerAction = TriggerAction.DelayToStart;
				parrent.configure.triggerEdge = (ActiveSignal)cbxTrgEdge.getSelectedItem();
				parrent.configure.triggerLevel = ((Number) txtTrgLevel.getValue()).doubleValue();
				
				parrent.configure.channelEnabled = new boolean [channelEnabled.length];
				System.arraycopy(channelEnabled, 0, parrent.configure.channelEnabled, 0, channelEnabled.length);
				
				parrent.configure.configureMode = Manual_Configure;
				
				//check enabled channel
				boolean flag = false;
		        for(int i = 0; i < channelEnabled.length; i++){
		            flag |= channelEnabled[i];
		        }
				
				if(flag){
					parrent.Initialization();
					parrent.setVisible(true);
					setVisible(false);
				}else{
					ShowMessage("Please enable at least one channel!");
				}			
			}
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
	
	class rdbtnLoadProfileActionListener implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			// TODO Auto-generated method stub
			if(rdbtn_LoadProfile.isSelected()){
				configureMode = Profile_Configure; // loadprofile mode --> (configureMode == true) 
				ComponentEnabled(configureMode);
			}else{
				configureMode = Manual_Configure;
				ComponentEnabled(configureMode);
			}
		}
	}
	
	class rdbtnManualConfigureActionListener implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			// TODO Auto-generated method stub
			if(rdbtn_ManualConfigure.isSelected()){
				configureMode = Manual_Configure;
				ComponentEnabled(configureMode);
			}else{
				configureMode = Profile_Configure;
				ComponentEnabled(configureMode);
			}
		}
	}
	
	public class ComboBoxTrgSrcItemListener implements ItemListener {

		@Override
		public void itemStateChanged(ItemEvent e) {
			// TODO Auto-generated method stub
			if(e.getStateChange() == ItemEvent.SELECTED){
				TriggerSourceChanged();
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
