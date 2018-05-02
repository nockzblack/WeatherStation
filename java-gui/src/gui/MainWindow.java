package gui;

import java.awt.Dimension;
import javax.swing.JFrame;
import javax.swing.JOptionPane;

public class MainWindow extends JFrame {
	
	private HttpProtocol serverConnection;
	private WeatherView auxView;
	private Data weatherData;
	private String ipAddress;
	
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
		this.auxView = new WeatherView(this.weatherData, this);
		this.add(auxView);
	}
	
	public void initData(double temp, double airQuality, int groundHumidity,  int airHumidty) {
		this.weatherData = new Data(temp, airQuality, groundHumidity, airHumidty);
	}
	
	public void getIp() {
		this.ipAddress = "http://";
		this.ipAddress += JOptionPane.showInputDialog(this,"Ingresa la dirección IP:");
	}
	
	public void showWeatherView() {
		String strData = "";
		
		try {
			strData = this.initServerConnection(this.ipAddress);
			
			String htmlCode = strData.substring(46);
			String strTemp = htmlCode.substring(47,49);
			String strAirQuality = htmlCode.substring(79,83);
			String strGroundHumidity = htmlCode.substring(115,119);
			String strAirHumidity = htmlCode.substring(152,154);
			/*
			System.out.println(htmlCode);
			System.out.println(strTemp);
			System.out.println(strAirQuality);
			System.out.println(strGroundHumidity);
			System.out.println(strAirHumidity);
			*/

			double temp = Double.parseDouble(strTemp);
			double airQuality = Double.parseDouble(strAirQuality);
			int groundHumidity = Integer.parseInt(strGroundHumidity);
			int airHumidity = Integer.parseInt(strAirHumidity);
			
			this.initData(temp, airQuality, groundHumidity, airHumidity);
			this.initWeatherView();
			this.revalidate();
			this.repaint();
			
		} catch (Exception ex) {
			JOptionPane.showMessageDialog(this,"Error en la IP:\n" +  ex.getMessage());
		}
	}
	
	
	
	public static void main (String[] args) {
		MainWindow app = new MainWindow();
		app.getIp();
		app.showWeatherView();
		
	}
}
