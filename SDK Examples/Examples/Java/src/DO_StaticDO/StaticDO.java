package DO_StaticDO;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.Point;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;

import Automation.BDaq.*;
import Common.*;
import Common.DioPortUI.StateChangeListener;

public class StaticDO extends JFrame {

	/**
	 *  define the serialization number.
	 */
	private static final long serialVersionUID = 1L;
	
	private JPanel contentPane;
	private JScrollPane portPanel;
	private JPanel allPanel;
	public ImageIcon[] imageIcon = { 
			new BackgroundPanel("ButtonUp.png", "Low").getImageIcon(),
			new BackgroundPanel("ButtonDown.png", "High").getImageIcon(),
			new BackgroundPanel("ButtonDisabled.png", "Didable").getImageIcon()
			};

	public InstantDoCtrl instantDoCtrl = new InstantDoCtrl();
	private ConfigureDialog configureDialog;
	private int portCount;
	private DioPortUI[] DiPorts;
	
	private StateChangeListener listener = new PortStateChangeListener();

	/**
	 * 
	 *Build Date:2011-9-21
	 *Author:Administrator
	 *Function Description: Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					StaticDO frame = new StaticDO();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * 
	 *Build Date:2011-9-21
	 *Author:Administrator
	 *Function Description: Create the frame.
	 */
	public StaticDO() {
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 461, 544);
		contentPane = new JPanel();
		contentPane.setBackground(SystemColor.control);
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		allPanel = new JPanel();
		// Default size
		allPanel.setPreferredSize(new Dimension(350, 382));
		allPanel.setLayout(null);
		allPanel.setBackground(SystemColor.control);
		portPanel = new JScrollPane(allPanel);
		portPanel.setBorder(new LineBorder(new Color(0, 0, 0)));
		portPanel.setBounds(30, 72, 372, 386);
		contentPane.add(portPanel);

		JLabel lblNewLabel = new JLabel("Port No.");
		lblNewLabel.setBounds(30, 56, 48, 15);
		contentPane.add(lblNewLabel);

		JLabel lblNewLabel_1 = new JLabel("Bit7");
		lblNewLabel_1.setBounds(90, 56, 33, 15);
		contentPane.add(lblNewLabel_1);

		JLabel lblBit = new JLabel("Bit3");
		lblBit.setBounds(220, 56, 33, 15);
		contentPane.add(lblBit);

		JLabel label = new JLabel("4");
		label.setHorizontalAlignment(SwingConstants.RIGHT);
		label.setBounds(172, 56, 20, 15);
		contentPane.add(label);

		JButton btnConfigure = new JButton("Configure");
		btnConfigure.setBounds(265, 468, 115, 23);
		btnConfigure.addActionListener(new ButtonConfigureActionListener());
		contentPane.add(btnConfigure);
		
		// Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("Background.png", "background image!");
		panel.setBounds(263, 0, 192, 92);
		panel.setBackground(SystemColor.control);
		panel.setLayout(null);
		contentPane.add(panel);

		JLabel lblNewLabel_2 = new JLabel("Hex");
		lblNewLabel_2.setBounds(89, 56, 29, 15);
		panel.add(lblNewLabel_2);

		JLabel lblNewLabel_3 = new JLabel("0");
		lblNewLabel_3.setHorizontalAlignment(SwingConstants.RIGHT);
		lblNewLabel_3.setBounds(41, 56, 20, 15);
		panel.add(lblNewLabel_3);
	
		configureDialog = new ConfigureDialog(this);
		configureDialog.setModal(true);
		configureDialog.setVisible(true);						
	}
	
	/**
	 * 
	 * Build Date:2011-9-21
	 * Author:Administrator
	 * Function Description: This function is used to initialize the main frame.
	 */
	public void Initialization() {
		setTitle("Static DO - Run(" + configureDialog.GetDeviceName().substring(0, configureDialog.GetDeviceName().length() - 1) + ")");
		
		try {
			instantDoCtrl.setSelectedDevice(new DeviceInformation(configureDialog.GetDeviceName()));
		} catch (Exception ex) {
			ShowMessage("Sorry,some errors occured: " + ex.getMessage());
		}
		
		String profilePath = null;
		profilePath = configureDialog.GetProfilePath();
		ErrorCode errorCode = instantDoCtrl.LoadProfile(profilePath);
		if(Global.BioFaild(errorCode)){
			ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
			}
		
		portCount = instantDoCtrl.getPortCount();
		DiPorts = new DioPortUI[portCount];
		Point location = new Point(10, 10);
		allPanel.removeAll();
		allPanel.repaint();
		byte[] portMask = instantDoCtrl.getFeatures().getDoDataMask();
		
		byte[] portStates = new byte[portCount];
		try {
			instantDoCtrl.Read(0, portCount, portStates);
		} catch(Exception e) {
			e.printStackTrace();
		}
		
		for (int i = 0; i < portCount; i++) {
			DiPorts[i] = new DioPortUI(i, allPanel, location, imageIcon, (byte)0);
			DiPorts[i].setMask(portMask[i]);
			DiPorts[i].setIsEditable(true);
			DiPorts[i].setState(portStates[i]);
			DiPorts[i].JudgeDirection(portMask[i]);
			DiPorts[i].AddStateChangeListener(listener);
			if (i % 2 == 0) {
				location.y += 40;
			} else {
				location.y += 55;
			}
		}
		allPanel.setPreferredSize(new Dimension(350, 48 * portCount));
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
	 * Class Function Description: This class is used to listen the configure button 's action.
	 */
	class ButtonConfigureActionListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			configureDialog.isFirstLoad = false;
			configureDialog.setVisible(true);
		}
	}
	
	/**
	 * 
	 * @author Administrator 
	 * Class Function Description: This class is used to listen the port's state changed event.
	 */
	class PortStateChangeListener implements StateChangeListener{
		@Override
		public void StateChangeAction(Object sender) {
			DioPortUI port = (DioPortUI)sender;
			ErrorCode errorCode = instantDoCtrl.Write(port.getKey(), port.getState());
			if(Global.BioFaild(errorCode)){
				ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
			}
		}	
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the main frame's closing event.
	 */
	class WindowCloseActionListener extends WindowAdapter{
		@Override
		public void windowClosing(WindowEvent e) {
			if (instantDoCtrl != null) {
				instantDoCtrl.Cleanup();
			}
		}
	}
}
