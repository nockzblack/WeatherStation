package gui;
import java.awt.Dimension;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

public class MainWindow extends JFrame {
	
	private HttpProtocol serverConnection;
	private WeatherView auxView;
	private Data weatherData;
	
	public MainWindow() {
		super("Arduino Weather Station GUI");
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setPreferredSize(new Dimension(600,650));
		this.pack();
		this.setVisible(true);
		this.setResizable(false);
	}
	
	public String initServerConnection(String ipAddress) throws Exception {
		this.serverConnection = new HttpProtocol(ipAddress);
		return this.serverConnection.getData();
	}
	
	public void initWeatherView() {
		this.auxView = new WeatherView(this.weatherData);
		this.add(auxView);
	}
	
	public void initData(double temp, double airQuality, int groundHumidity,  int airHumidty) {
		this.weatherData = new Data(temp, airQuality, groundHumidity, airHumidty);
	}
	
	
	
	public static void main (String[] args) {
		MainWindow app = new MainWindow();
		
		String ipAddress = "http://";
		ipAddress += JOptionPane.showInputDialog(app,"Ingresa la dirección IP:");
		String strData = "";
		
		try {
			strData = app.initServerConnection(ipAddress);
			
			String htmlCode = strData.substring(46);
			String strTemp = htmlCode.substring(47,49);
			String strAirQuality = htmlCode.substring(79,83);
			String strGroundHumidity = htmlCode.substring(115,118);
			String strAirHumidity = htmlCode.substring(152,154);
			
			double temp = Double.parseDouble(strTemp);
			double airQuality = Double.parseDouble(strAirQuality);
			int groundHumidity = Integer.parseInt(strGroundHumidity);
			int airHumidity = Integer.parseInt(strAirHumidity);
			
			app.initData(temp, airQuality, airHumidity, groundHumidity);
			app.initWeatherView();
			app.revalidate();
			app.repaint();
			
		} catch (Exception ex) {
			JOptionPane.showMessageDialog(app,"Error en la IP:\n" +  ex.getMessage());
		}
		
		
	}
}
