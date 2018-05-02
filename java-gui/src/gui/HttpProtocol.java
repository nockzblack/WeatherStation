package gui;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpProtocol {
	private final String USER_AGENT = "Mozilla/5.0";
	private String url;
	private String response;
	
	public HttpProtocol(String ipAdress) {
		this.url = ipAdress;
		this.response = "";
	}
	
	public String getData()  throws Exception {
		sendGet();
		return this.response;
	}
	
	// HTTP GET request
		private void sendGet() throws Exception {
			
			URL obj = new URL(this.url);
			HttpURLConnection con = (HttpURLConnection) obj.openConnection();

			// optional default is GET
			con.setRequestMethod("GET");

			//add request header
			con.setRequestProperty("User-Agent", USER_AGENT);

			//int responseCode = con.getResponseCode();
			//System.out.println("\nSending 'GET' request to URL : " + this.url);
			//System.out.println("Response Code : " + responseCode);

			BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
			String inputLine;
			StringBuffer responseBuffer = new StringBuffer();

			while ((inputLine = in.readLine()) != null) {
				responseBuffer.append(inputLine);
			}
			in.close();

			//print result
			//System.out.println(responseBuffer.toString());
			this.response = responseBuffer.toString();
		}
}
