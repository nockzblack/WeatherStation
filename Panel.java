import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;

//import java.awt.Graphics;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class Panel extends JPanel{
	
	private JLabel jlTemperatura,
					jlCalidad,
					jlHumedad,
					jlLuz,
					jlHumedadSuelo,
					Cal,
					Hum,
					Luz,
					HumS;
	private Data datos;
	private Font fuente,
					fTemp;
	
	
	public Panel() {
		super();
		this.setPreferredSize(new Dimension(600,590));
		this.setBackground(Color.CYAN);
		
		//FUENTES
		fuente = new Font("TimesRoman", Font.BOLD, 20); 
		fTemp = new Font("TimesRoman", Font.BOLD, 72);
		
		//INICIALIZAR EL OBJETO DATA
		datos = new Data(30,25,65,85,32);
		//datos = new Data();
		Actualizar(datos);
		
		//ETIQUETAS
		this.Cal = new JLabel("Calidad del aire");
		this.Cal.setFont(fuente);
		this.Hum = new JLabel("Humedad en el aire");
		this.Hum.setFont(fuente);
		this.Luz = new JLabel("Intensidad de la luz");
		this.Luz.setFont(fuente);
		this.HumS = new JLabel("Humedad en el suelo");
		this.HumS.setFont(fuente);
		
		this.Cal.setBounds(10, 230, 200, 80);
		this.Hum.setBounds(10, 320, 200, 80);
		this.Luz.setBounds(10, 410, 200, 80);
		this.HumS.setBounds(10, 500, 200, 80);
		
		this.jlTemperatura.setBounds(60,70,450,80);
		this.jlCalidad.setBounds(240,230,450,80);
		this.jlHumedad.setBounds(240,320,100,80);
		this.jlLuz.setBounds(240,410,250,80);
		this.jlHumedadSuelo.setBounds(240,500,300,80);
		
		this.setLayout(null);
		
		this.add(this.Cal);
		this.add(this.Hum);
		this.add(this.Luz);
		this.add(this.HumS);
		this.add(this.jlTemperatura);
		this.add(this.jlCalidad);
		this.add(this.jlHumedad);
		this.add(this.jlLuz);
		this.add(this.jlHumedadSuelo);
		 
		
	}
	
	public void Actualizar(Data datos) {
		this.jlTemperatura = new JLabel(datos.getTemperatura() + "°");
		this.jlTemperatura.setFont(fTemp);
		this.jlCalidad = new JLabel(datos.getCalidad() + "puntos IMECA");
		this.jlCalidad.setFont(fuente);
		this.jlHumedad = new JLabel(datos.getHumedad() + "%");
		this.jlHumedad.setFont(fuente);
		this.jlLuz = new JLabel(datos.getLuz() + "puntos luz");
		this.jlLuz.setFont(fuente);
		this.jlHumedadSuelo = new JLabel(datos.getHumedadSuelo() + "%");
		this.jlHumedadSuelo.setFont(fuente);
		
	}
	
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.setColor(Color.BLUE);
		g.fillRect(200, 0, 20, 610);
		g.fillRect(0,200, 620, 20);
		g.fillRect(20, 20, 1000, 0);
		g.fillRect(0, 0, 0, 590);
		
	}
}

