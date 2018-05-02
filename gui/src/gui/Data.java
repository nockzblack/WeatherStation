package gui;

public class Data {
	private int humedadAmbiental,
				humedadSuelo,
				intensidadLuminosa;
	
	private double temperatura,
				   calidadlDelAire;
				
	public Data(String strData) {
		this.temperatura = 24.0;
		this.calidadlDelAire = 33;
		this.humedadAmbiental = 50;
		this.intensidadLuminosa = 500;
		this.humedadSuelo = 50;
		
	}
	
	public Data(double temperatura, double calidadlDelAire, int humedad, int humedadSuelo) {
		this.temperatura = temperatura;
		this.calidadlDelAire = calidadlDelAire;
		this.humedadAmbiental = humedad;
		this.intensidadLuminosa = 100;
		this.humedadSuelo = humedadSuelo;
		
	}
	
	//SETTERS
	public void setTemperatura(double temperatura) {
		this.temperatura = temperatura;
	}
	
	public void setCalidad(double airQuality) {
		this.calidadlDelAire = airQuality;
	}
	
	public void setHumedad(int humedad) {
		this.humedadAmbiental = humedad;
	}
	
	public void setLuz(int luz) {
		this.intensidadLuminosa = luz;
	}
	
	public void setHumedadSuelo(int humedadSuelo) {
		this.humedadSuelo = humedadSuelo;
	}
	
	//GETTERS
	public double getTemperatura() {
		return this.temperatura;
	}
	
	public double getCalidad() {
		return this.calidadlDelAire;
	}
	
	public int getHumedad() {
		return this.humedadAmbiental;
	}
	
	public int getLuz() {
		return this.intensidadLuminosa;
	}
	
	public int getHumedadSuelo() {
		return this.humedadSuelo;
	}
}
