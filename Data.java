
public class Data {
	private int temperatura,
				calidad,
				humedad,
				luz,
				humedadSuelo;
				
	public Data() {
		this.temperatura = 24;
		this.calidad = 33;
		this.humedad = 50;
		this.luz = 500;
		this.humedadSuelo = 50;
		
	}
	
	public Data(int temperatura, int calidad, int humedad, int luz, int humedadSuelo) {
		this.temperatura = temperatura;
		this.calidad = calidad;
		this.humedad = humedad;
		this.luz = luz;
		this.humedadSuelo = humedadSuelo;
		
	}
	
	//SETTERS
	public void setTemperatura(int temperatura) {
		this.temperatura = temperatura;
	}
	
	public void setCalidad(int calidad) {
		this.calidad = calidad;
	}
	
	public void setHumedad(int humedad) {
		this.humedad = humedad;
	}
	
	public void setLuz(int luz) {
		this.luz= luz;
	}
	
	public void setHumedadSuelo(int humedadSuelo) {
		this.humedadSuelo = humedadSuelo;
	}
	
	//GETTERS
	public int getTemperatura() {
		return this.temperatura;
	}
	
	public int getCalidad() {
		return this.calidad;
	}
	
	public int getHumedad() {
		return this.humedad;
	}
	
	public int getLuz() {
		return this.luz;
	}
	
	public int getHumedadSuelo() {
		return this.humedadSuelo;
	}
}
