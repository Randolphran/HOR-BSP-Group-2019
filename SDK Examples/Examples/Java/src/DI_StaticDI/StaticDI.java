package DI_StaticDI;

import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.Point;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.Timer;
import javax.swing.border.EmptyBorder;

import java.awt.SystemColor;
import javax.swing.JButton;
import javax.swing.border.LineBorder;
import javax.swing.JScrollPane;
import javax.swing.JLabel;
import javax.swing.SwingConstants;

import Common.*;
import Automation.BDaq.*;

public class StaticDI extends JFrame implements ActionListener {

	/**
	 *  define the serialization number.
	 */
	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	private JScrollPane portPanel;
	private JPanel allPanel;
	public ImageIcon[] imageIcon = { 
			new BackgroundPanel("ledLow.png", "Low").getImageIcon(),
			new BackgroundPanel("ledHigh.png", "High").getImageIcon() 
			};

	private InstantDiCtrl instantDiCtrl = new InstantDiCtrl();
	private ConfigureDialog configureDialog;
	private int portCount;
	private DioPortUI[] DiPorts;
	private byte[] data;

	private Timer timer;

	/**
	 * 
	 * Build Date:2011-9-14 
	 * Author:Administrator
	 * Function Description: Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					StaticDI frame = new StaticDI();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * 
	 * Build Date:2011-9-14 
	 * Author:Administrator
	 * Function Description: Create the frame.
	 */
	public StaticDI() {
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 430, 542);
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
		portPanel.setBounds(20, 60, 372, 386);
		contentPane.add(portPanel);

		JLabel lblNewLabel = new JLabel("Port No.");
		lblNewLabel.setBounds(20, 43, 48, 15);
		contentPane.add(lblNewLabel);

		JLabel lblNewLabel_1 = new JLabel("Bit7");
		lblNewLabel_1.setBounds(80, 43, 33, 15);
		contentPane.add(lblNewLabel_1);

		JLabel lblBit = new JLabel("Bit3");
		lblBit.setBounds(210, 43, 33, 15);
		contentPane.add(lblBit);

		JLabel label = new JLabel("4");
		label.setHorizontalAlignment(SwingConstants.RIGHT);
		label.setBounds(162, 43, 20, 15);
		contentPane.add(label);

		JButton btnConfigure = new JButton("Configure");
		btnConfigure.setBounds(265, 468, 115, 23);
		btnConfigure.addActionListener(new ButtonConfigureActionListener());
		contentPane.add(btnConfigure);
		
		// Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("Background.png", "background image!");
		panel.setBounds(265, 0, 160, 77);
		panel.setBackground(SystemColor.control);
		panel.setLayout(null);
		contentPane.add(panel);
		
		JLabel lblNewLabel_2 = new JLabel("Hex");
		lblNewLabel_2.setBounds(80, 43, 29, 15);
		panel.add(lblNewLabel_2);

		JLabel lblNewLabel_3 = new JLabel("0");
		lblNewLabel_3.setHorizontalAlignment(SwingConstants.RIGHT);
		lblNewLabel_3.setBounds(34, 43, 20, 15);
		panel.add(lblNewLabel_3);

		configureDialog = new ConfigureDialog(this);
		configureDialog.setModal(true);
		configureDialog.setVisible(true);
	}

	/**
	 * 
	 * Build Date:2011-9-14
	 * Author:Administrator
	 * Function Description: This function is used to initialize the main frame.
	 */
	public void Initialization() {
		setTitle("Static DI - Run(" + configureDialog.GetDeviceName().substring(0, configureDialog.GetDeviceName().length() - 1) + ")");

		try {
			instantDiCtrl.setSelectedDevice(new DeviceInformation(configureDialog.GetDeviceName()));
		} catch (Exception ex) {
			ShowMessage("Sorry, there're some errors occured: " + ex.getMessage());
		}
		String profilePath = null;
		profilePath = configureDialog.GetProfilePath();
		ErrorCode errorCode = instantDiCtrl.LoadProfile(profilePath);
		if(Global.BioFaild(errorCode)){
			ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
			}
		portCount = instantDiCtrl.getPortCount();
		DiPorts = new DioPortUI[portCount];
		Point location = new Point(10, 10);
		allPanel.removeAll();
		allPanel.repaint();
		
		for (int i = 0; i < portCount; i++) {
			DiPorts[i] = new DioPortUI(i, allPanel, location, imageIcon, (byte) 0);
			if (i % 2 == 0) {
				location.y += 40;
			} else {
				location.y += 55;
			}
		}
		allPanel.setPreferredSize(new Dimension(350, 48 * portCount));

		if (timer == null) {
			timer = new Timer(100, this);
		}
		timer.start();
	}

	/**
	 * 
	 * Build Date:2011-9-14 
	 * Author:Administrator
	 * Function Description: This function is overload the interface ActionListener,and 
	 * 						 is implementation need this function!
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		if (data == null || data.length < portCount) {
			data = new byte[portCount];
		}

		ErrorCode errorCode = instantDiCtrl.Read(0, portCount, data);
		if (!Global.BioFaild(errorCode)) {
			for (int i = 0; i < portCount; i++) {
				DiPorts[i].setState(data[i]);
			}
		} else {
			ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
			return;
		}

	}

	/**
	 * 
	 * Build Date:2011-9-13
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
			if(timer != null){
				timer.stop();
			}
			configureDialog.isFirstLoad = false;
			configureDialog.setVisible(true);
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
			if (instantDiCtrl != null) {
				instantDiCtrl.Cleanup();
			}
			if(timer != null){
				timer.stop();
			}
		}
	}
}
