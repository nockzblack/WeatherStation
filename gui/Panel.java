package gui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Image;
import javax.swing.ImageIcon;
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
	private Image fondo;
	
	
	public Panel() {
		super();
		this.setPreferredSize(new Dimension(600,590));
		this.setBackground(Color.GRAY);
		this.fondo = new ImageIcon("gui/Cielo.jpg").getImage();
		
		//FUENTES
		fuente = new Font("Tahoma", Font.BOLD, 20); 
		fTemp = new Font("Tahoma", Font.CENTER_BASELINE, 60);
		
		//INICIALIZAR EL OBJETO DATA
		datos = new Data(25,25,65,85,32);
		//datos = new Data();
		Actualizar(datos);
		
		//ETIQUETAS
		this.Cal = new JLabel("Calidad del aire");
		this.Cal.setFont(fuente);
		this.Cal.setForeground(Color.WHITE);
		this.Hum = new JLabel("Humedad en el aire");
		this.Hum.setFont(fuente);
		this.Hum.setForeground(Color.WHITE);
		this.Luz = new JLabel("Intensidad de la luz");
		this.Luz.setFont(fuente);
		this.Luz.setForeground(Color.WHITE);
		this.HumS = new JLabel("Humedad en el suelo");
		this.HumS.setFont(fuente);
		this.HumS.setForeground(Color.WHITE);
		
		//Set Bounds
		this.Cal.setBounds(10, 230, 400, 80);
		this.Hum.setBounds(10, 320, 400, 80);
		this.Luz.setBounds(10, 410, 400, 80);
		this.HumS.setBounds(10, 500, 400, 80);
		
		this.jlTemperatura.setBounds(40,70,200,80);
		this.jlCalidad.setBounds(260,230,200,80);
		this.jlHumedad.setBounds(260,320,200,80);
		this.jlLuz.setBounds(260,410,200,80);
		this.jlHumedadSuelo.setBounds(260,500,200,80);
		
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
		//jlTemperatura
		this.jlTemperatura = new JLabel(datos.getTemperatura() + "ºC");
		this.jlTemperatura.setFont(fTemp);
		this.jlTemperatura.setForeground(Color.WHITE);
		//jlCalidad
		this.jlCalidad = new JLabel(datos.getCalidad() + " puntos IMECA");
		this.jlCalidad.setOpaque(true);
		this.jlCalidad.setFont(fuente);
		this.jlCalidad.setForeground(Color.WHITE);
		this.jlCalidad.setBackground(Color.LIGHT_GRAY);
		//jlHumedad
		this.jlHumedad = new JLabel(datos.getHumedad() + " %");
		this.jlHumedad.setOpaque(true);
		this.jlHumedad.setFont(fuente);
		this.jlHumedad.setForeground(Color.WHITE);
		this.jlHumedad.setBackground(Color.LIGHT_GRAY);
		//jlLuz
		this.jlLuz = new JLabel(datos.getLuz() + " puntos luz");
		this.jlLuz.setOpaque(true);
		this.jlLuz.setFont(fuente);
		this.jlLuz.setForeground(Color.WHITE);
		this.jlLuz.setBackground(Color.LIGHT_GRAY);
		//jlHumedadSuelo
		this.jlHumedadSuelo = new JLabel(datos.getHumedadSuelo() + " %");
		this.jlHumedadSuelo.setOpaque(true);
		this.jlHumedadSuelo.setFont(fuente);
		this.jlHumedadSuelo.setForeground(Color.WHITE);
		this.jlHumedadSuelo.setBackground(Color.LIGHT_GRAY);
		
	}
	
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.setColor(Color.WHITE);
		g.drawImage(this.fondo, 0, 0, this.getWidth(), this.getHeight(), this);
		g.fillRect(240, 0, 10, 610);
		g.fillRect(0,200, 620, 10);
		
		
	}
}

