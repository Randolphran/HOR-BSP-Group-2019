package DI_DIPatternMatchInterrupt;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.SystemColor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.DefaultTableCellRenderer;

import Automation.BDaq.*;
import Common.*;

import org.eclipse.wb.swing.FocusTraversalOnArray;

import java.awt.Component;

public class DIPatternMatchInterrupt extends JFrame {

	/**
	 * define the serialization number.
	 */
	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	private JButton btnStart;
	private JButton btnStop;
	private JButton btnConfigure;
	private JTable table;
	
	private final int MAX_ROW_COUNT = 10;
	private final int MAX_COLUMN_COUNT = 2;
	
	private TableDataModel model;
	private String [][] tableData = new String[MAX_ROW_COUNT][MAX_COLUMN_COUNT];
	private int tableRowIndex = 0;
	private int changeIndex = 0;
	
	ConfigureParameter configure = new ConfigureParameter(); 
	ConfigureDialog configureDialog;
	
	private InstantDiCtrl instantDiCtrl = new InstantDiCtrl();
	private int portCount;
	private byte[] portData;
	/**
	 * 
	 * Build Date:2011-9-23
	 * Author:Administrator
	 * Function Description: Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					DIPatternMatchInterrupt frame = new DIPatternMatchInterrupt();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * 
	 * Build Date:2011-9-22
	 * Author:Administrator
	 * Function Description: Create the frame.
	 */
	public DIPatternMatchInterrupt() {
		// Add window close action listener.
		addWindowListener(new WindowCloseActionListener());
		
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 503, 359);
		contentPane = new JPanel();
		contentPane.setBackground(SystemColor.control);
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		model = new TableDataModel(tableData, MAX_ROW_COUNT, MAX_COLUMN_COUNT);
		
		// Add background image for the main Frame
		BackgroundPanel panel = new BackgroundPanel("DiBackground.png", "background image!");
		panel.setBounds(0, 0, 500, 327);
		panel.setBackground(SystemColor.control);
		panel.setLayout(null);
		contentPane.add(panel);
		
		table = new JTable(model);
		table.setBorder(new LineBorder(new Color(0, 0, 0)));
		table.getTableHeader().setReorderingAllowed(false); 
		table.getTableHeader().setBackground(Color.LIGHT_GRAY);
		table.setBounds(25, 35, 365, 271);
		table.setRowHeight(25);
		
		DefaultTableCellRenderer render = new DefaultTableCellRenderer();   
		render.setHorizontalAlignment(JLabel.CENTER); 
		table.setDefaultRenderer(Object.class,render);
		
		JScrollPane scrollPanel = new JScrollPane(table);
		scrollPanel.setBounds(23, 29, 370, 271);
		panel.add(scrollPanel);
		
		btnStart = new JButton("Start");
		btnStart.setBounds(408, 156, 75, 23);
		btnStart.addActionListener(new ButtonStartActionListener());
		panel.add(btnStart);
		
		btnStop = new JButton("Stop");
		btnStop.setBounds(408, 189, 75, 23);
		panel.add(btnStop);
		btnStop.addActionListener(new ButtonStopActionListener());
		btnStop.setEnabled(false);
		
		btnConfigure = new JButton("Configure");
		btnConfigure.setBounds(395, 249, 98, 23);
		btnConfigure.addActionListener(new ButtonConfigureActionListener());
		panel.add(btnConfigure);
		panel.setFocusTraversalPolicy(new FocusTraversalOnArray(new Component[]{
				btnStart, btnStop, btnConfigure}));
		
		// Add pattern match event listener to the control.
		instantDiCtrl.addPatternMatchListener(new PatternMatchListener());
		
		configureDialog = new ConfigureDialog(this);
		configureDialog.setModal(true);
		configureDialog.setVisible(true);
	}
	
	/**
	 * 
	 * Build Date:2011-9-22
	 * Author:Administrator
	 * Function Description: This function is used to initialize the main frame.
	 */
	public void Initialization() {
		setTitle("DI Pattern Match Interrupt - Run(" + configure.deviceName.substring(0, configure.deviceName.length() - 1) + ")");

		try {
			instantDiCtrl.setSelectedDevice(new DeviceInformation(configure.deviceName));
			DiPmintPort[] port = instantDiCtrl.getDiPmintPorts();
			port[configure.selectedPortIndex].setMask(configure.enablePort);
			port[configure.selectedPortIndex].setPattern(configure.pattern);
		} catch (Exception ex) {
			ShowMessage("Sorry,some errors occured: " + ex.getMessage());
		}
		String profilePath = null;
		profilePath = configureDialog.GetProfilePath();
		ErrorCode errorCode = instantDiCtrl.LoadProfile(profilePath);
		if(Global.BioFaild(errorCode)){
			ShowMessage("Sorry, there're some errors occred, ErrorCode: " + errorCode.toString());
			}
		
		portCount = instantDiCtrl.getPortCount();
		model.columnName[1] = "Port Value(0~" + String.valueOf(portCount - 1) + ")";
		
		table.createDefaultColumnsFromModel();
		table.getColumnModel().getColumn(0).setPreferredWidth(100);
		table.getColumnModel().getColumn(1).setPreferredWidth(260);
		table.setPreferredSize(new Dimension(370 , table.getSize().height));
		
		//note here !!!!!
		
		if(portCount > 10){
			int increase = portCount - 10;
			
			table.setPreferredSize(new Dimension(370 + increase * 20, table.getSize().height));
			table.getColumnModel().getColumn(0).setPreferredWidth(100);
			table.getColumnModel().getColumn(1).setPreferredWidth(260 + increase * 20);
		}
		
		for(int i =0; i < tableRowIndex; i++){
			model.data[i][0] = "";
			model.data[i][1] = "";
		}
		
		btnConfigure.setEnabled(true);
		btnStart.setEnabled(true);
		btnStop.setEnabled(false);
		
		table.updateUI();
		
		tableRowIndex = 0;
		changeIndex = 0;
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
	 *Build Date:2011-9-22
	 *Author:Administrator
	 *Function Description: This function is used to refresh the table.
	 * @param data
	 */
	private void RefreshTable(byte[] data){
		String allPortValue = "";
		for(int i = 0; i < portCount; i++){
			allPortValue += Integer.toHexString(data[i] | 0xFFFFFF00).toUpperCase().substring(6);
			if(i < portCount - 1){
				allPortValue += ",";
			}
		}
		if (tableRowIndex < MAX_ROW_COUNT) {
			tableData[tableRowIndex][0] = String.valueOf(changeIndex++);
			tableData[tableRowIndex][1] = allPortValue;
			tableRowIndex++;
		} else {
			int Index = tableRowIndex - 1;
			for (int i = 0; i < Index; i++) {
				tableData[i][0] = tableData[i + 1][0];
				tableData[i][1] = tableData[i + 1][1];
			}
			tableData[Index][0] = String.valueOf(changeIndex++);
			tableData[Index][1] = allPortValue;
		}
		table.repaint();
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to control the table's value changing.
	 */
	class TableDataModel extends AbstractTableModel {
		
		private static final long serialVersionUID = 1L;
		int rowCount;
		int columnCount;
		String[][] data;
		String[] columnName = { "Matched NO.#", "Port Value(0~2)" };

		public TableDataModel(String[][] pdata, int row, int column) {
			data = pdata;
			rowCount = row;
			columnCount = column;
		}

		@Override
		public int getRowCount() {
			if (data == null) {
				return 0;
			} else {
				return rowCount;
			}
		}

		@Override
		public int getColumnCount() {
			if (data == null) {
				return 0;
			} else {
				return columnCount;
			}
		}

		@Override
		public Object getValueAt(int rowIndex, int columnIndex) {
			if (data == null) {
				return null;
			} else {
				return data[rowIndex][columnIndex];
			}
		}

		public String getColumnName(int column) {
			return columnName[column];
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the pattern match event.
	 */
	class PatternMatchListener implements DiSnapEventListener{

		@Override
		public void DiSnapEvent(Object sender, DiSnapEventArgs args) {
			if(portData == null || portData.length < portCount){
				portData = new byte[portCount];
			}
			
			for(int i = 0; i < portCount; i++){
				portData[i] = args.PortData[i];
			}
			RefreshTable(portData);
		}
	}
	
	/**
	 * 
	 * @author Administrator
	 * Class Function Description: This class is used to listen the start button 's action.
	 */
	class ButtonStartActionListener implements ActionListener{
		public void actionPerformed(ActionEvent e) {
			
			ErrorCode errorCode = instantDiCtrl.SnapStart();
			if (Global.BioFaild(errorCode)) {
				ShowMessage("Sorry, there're some errors occred, ErrorCode: "
						+ errorCode.toString());
				return;
			}
			
			btnStart.setEnabled(false);
			btnStop.setEnabled(true);
			btnConfigure.setEnabled(false);
			
			for(int i =0; i < tableRowIndex; i++){
				model.data[i][0] = "";
				model.data[i][1] = "";
			}
			table.repaint();
			
			tableRowIndex = 0;
			changeIndex = 0;
		}
	}
	
	/**
	 * 
	 * @author Administrator 
	 * Class Function Description: This class is used to listen the stop button 's action.
	 */
	class ButtonStopActionListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			ErrorCode errorCode = instantDiCtrl.SnapStop();
			if (Global.BioFaild(errorCode)) {
				ShowMessage("Sorry, there're some errors occred, ErrorCode: "
						+ errorCode.toString());
				return;
			}
			
			btnStart.setEnabled(true);
			btnStop.setEnabled(false);
			btnConfigure.setEnabled(true);
		}
	}
	
	/**
	 * 
	 * @author Administrator 
	 * Class Function Description: This class is used to listen the configure button 's action.
	 */
	class ButtonConfigureActionListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			ErrorCode errorCode = instantDiCtrl.SnapStop();
			if (Global.BioFaild(errorCode)) {
				ShowMessage("Sorry, there're some errors occred, ErrorCode: "
						+ errorCode.toString());
				return;
			}
			
			btnStart.setEnabled(true);
			btnStop.setEnabled(false);
			btnConfigure.setEnabled(false);
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
		}
	}
}

/**
 * 
 * @author Administrator 
 * Class Description: this class is use to transfer parameter to the main frame.
 */
class ConfigureParameter{
	public String deviceName;
	public int selectedPortIndex;
	public byte enablePort;
	public byte pattern;
}

