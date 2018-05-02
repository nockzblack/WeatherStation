package gui;
import javax.swing.JFrame;

public class Frame extends JFrame {
	public Frame(){
		super("Mi nueva ventana");
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		Panel PanelI = new Panel();
		this.add(PanelI);
		this.pack();
		this.setVisible(true);
		this.setResizable(false);
		
	}
	public static void main (String[] args) {
		Frame miVentana = new Frame();
		
	}
}
