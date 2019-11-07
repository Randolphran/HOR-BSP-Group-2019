package Common;

import java.awt.Color;
import java.awt.Point;
import java.awt.SystemColor;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;

public class DioPortUI extends JPanel{
	// define the serialization number.
	private static final long serialVersionUID = 1L;
	
	private JPanel highBytes = new JPanel();
	private JPanel lowBytes = new JPanel();
	private JLabel[] bytesLevel = new JLabel[8];
	private JLabel lblPortIndex = new JLabel();
	private JLabel lblHexValue = new JLabel("00");
	private ImageIcon[] imageIcon ;

	private int  key;
	private byte mask = 0;
	private byte state = 0;
	private StateChangeListener listener = null;
	private boolean isEditable = false;
	
	public interface StateChangeListener{
		public void StateChangeAction(Object sender);
	}
	
	public DioPortUI(int index, JPanel parrent, Point location, ImageIcon[] image, byte state) {
		key = index;
		this.state = state;
		imageIcon = image;

		lblPortIndex.setBounds(location.x, location.y + 6, 25, 23);
		lblPortIndex.setHorizontalAlignment(SwingConstants.CENTER);
		lblPortIndex.setBorder(BorderFactory.createLineBorder(Color.GRAY));
		lblPortIndex.setText(String.valueOf(key));
		parrent.add(lblPortIndex);

		highBytes.setBounds(location.x + 35, location.y, 125, 35);
		highBytes.setLayout(null);
		highBytes.setBackground(SystemColor.control);
		highBytes.setBorder(BorderFactory.createLineBorder(Color.gray));
		parrent.add(highBytes);

		lowBytes.setBounds(location.x + 170, location.y, 125, 35);
		lowBytes.setLayout(null);
		lowBytes.setBackground(SystemColor.control);
		lowBytes.setBorder(BorderFactory.createLineBorder(Color.gray));
		parrent.add(lowBytes);

		lblHexValue.setBounds(location.x + 305, location.y + 6, 35, 23);
		lblHexValue.setHorizontalAlignment(SwingConstants.CENTER);
		lblHexValue.setBorder(BorderFactory.createLineBorder(Color.gray));
		parrent.add(lblHexValue);

		for (int i = 0; i < 4; i++) {
			bytesLevel[i] = new JLabel(imageIcon[(state >> 7 - i) & 0x1]);
			bytesLevel[i].setBounds(5 + i * 25, 3, 26, 26);
			bytesLevel[i].addMouseListener(new MouseClickListener());
			highBytes.add(bytesLevel[i]);

			bytesLevel[i + 4] = new JLabel(imageIcon[(state >> 3 - i) & 0x1]);
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
		lblPortIndex.setText(String.valueOf(key));

		int bitValue = 0;
		for (int i = 7; i >= 0; i--) {
			bitValue = (state >> (7 - i)) & 0x1;
			bytesLevel[i].setIcon(imageIcon[bitValue]); 
		}

		lblHexValue.setText(Integer.toHexString(state | 0xFFFFFF00).toUpperCase().substring(6));
	}
	
	public void JudgeDirection(byte portDirection){
		int bitValue = 0;
		mask = portDirection;
		for(int i = 7; i >= 0; i--){
			bitValue = (portDirection >> 7 - i) & 0x1;
			if(bitValue == 0){
				bytesLevel[i].setIcon(imageIcon[2]);
				bytesLevel[i].setEnabled(false);
			}else{
				bytesLevel[i].setEnabled(true);
			}
		}
		lblHexValue.setText(Integer.toHexString((byte)(state & mask) | 0xFFFFFF00).toUpperCase().substring(6));
	}
	
	public void AddStateChangeListener(StateChangeListener listener){
		this.listener = listener;
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
				//invoke the listener here
				if(listener != null){
					listener.StateChangeAction(DioPortUI.this);
				}
			}
		}
	}
}
