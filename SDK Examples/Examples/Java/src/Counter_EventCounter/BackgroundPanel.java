package Counter_EventCounter;

import java.awt.Dimension;
import java.awt.Graphics;

import javax.swing.ImageIcon;
import javax.swing.JPanel;

public class BackgroundPanel extends JPanel {
	// define the serialization number.
	private static final long serialVersionUID = 1L;
	
	private ImageIcon imageicon;

	public BackgroundPanel(String relativePath, String tips) {
		super();
		imageicon = createImageIcon(relativePath, tips);
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		imageicon.paintIcon(this, g, 0, 0);
	}

	public Dimension getPreferredSize() {
		return new Dimension(imageicon.getIconWidth(), imageicon.getIconHeight());
	}
	///create an image in relate path
	protected ImageIcon createImageIcon(String path, String description) {
		java.net.URL imgURL = getClass().getResource(path);
		if (imgURL != null) {
			return new ImageIcon(imgURL, description);
		} else {
			System.err.println("Couldn't find file: " + path);
			return null;
		}
	}
	public ImageIcon getImageIcon(){
		return imageicon;
	}
}
