//
//  ViewController.swift
//  Weather App
//
//  Created by Fernando Benavides Rodriguez on 7/16/18.
//  Copyright © 2018 Nockzblack. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    // MARK: Vars
    var data = WeatherData()
    var IPAddress: String? = nil
    
    // MARK: IBOutlets
    @IBOutlet weak var tempDataLabel: UILabel!
    
    @IBOutlet weak var airHumidityDataLabel: UILabel!
    
    @IBOutlet weak var airQualityDataLabel: UILabel!
    
    @IBOutlet weak var humidityDataLabel: UILabel!
    
    
    // MARK: IBActions
    @IBAction func updateDataValues(_ sender: UIButton) {
        
        if let auxIP = self.IPAddress {
            requestDataFromServer(urlToRequestStr: "http://\(auxIP)")
        } else {
            let alert = UIAlertController(title: "There isn't a specific IP", message: "Try to add one", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
            self.present(alert, animated: true)
        }
        
        
    }
    @IBAction func enterIPAddress(_ sender: UIButton) {
        
        let IPAlert = UIAlertController(title: "Enter an IP:", message: "Without http://", preferredStyle: .alert)
        IPAlert.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler: nil))
        IPAlert.addTextField(configurationHandler: { texField in
            texField.placeholder = "Input your IP Address here..."
            
        })
        
        IPAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: { action in
            if let newIP = IPAlert.textFields?.first?.text {
                self.IPAddress = newIP
                sender.setTitle("IP: \(newIP)", for: .normal)
            }
        }))
        
        self.present(IPAlert, animated: true)
        
    }
    
    
    // MARK: Funcs
    
    func requestDataFromServer(urlToRequestStr:String) {
        
        let auxURL = URL(string: urlToRequestStr)
        
        let task = URLSession.shared.dataTask(with: auxURL!) { (dataReceived, answer, possibleError) in
            
            if possibleError != nil {
                
                let alert = UIAlertController(title: "Error", message: "trying to reach the server", preferredStyle: .alert)
                alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
                self.present(alert, animated: true)
                print(possibleError!)
                
                
            } else {
                let dataNSStr = NSString(data: dataReceived!, encoding: String.Encoding.utf8.rawValue)
                
                let dataStr = String(dataNSStr!)
                
                // Example of data received from server
                /* <meta http-equiv='refresh' content='1'/><body><html><h1>Whether Station</h1><h3>Temp: 27.68 C </h3><h3>Calidad del Aire: 163 ppm </h3><h3>Humedad del Suelo: 968 </h3><h3>Humedad del Ambiemte: 63.0 %</h3></body></html> */
                
                let newTemp = self.getNumberAfter(indentifier: "Temp:", in: dataStr, lenOfData: 5)
                let newAirQuality = self.getNumberAfter(indentifier: "Aire:", in: dataStr, lenOfData: 3)
                let newGroundHumidity = self.getNumberAfter(indentifier: "Suelo:", in: dataStr, lenOfData: 3)
                let newEnviromentHumidity = self.getNumberAfter(indentifier: "Ambiemte:", in: dataStr, lenOfData: 4)
                self.data = WeatherData(temp: newTemp, airQuality: Int(newAirQuality), groundHumidity: Int(newGroundHumidity), enviromentHumidity: newEnviromentHumidity)
                
               // print(self.data.toString())
                
                
                // Execute asincronamente
                DispatchQueue.main.sync (execute: {
                    self.updateUIDataLabels()
                })

                
                
            }
        }
        
        task.resume()
    }
    
    
    func getNumberAfter(indentifier:String, in auxString:String, lenOfData:Int) -> Double {
        
        if let tempRange = auxString.range(of: indentifier) {
            
            let startTempIndex = auxString.index(tempRange.upperBound, offsetBy: 1)
            let endTempIndex = auxString.index(tempRange.upperBound, offsetBy: lenOfData + 1)
            let newRange = startTempIndex..<endTempIndex
            let tempStr = auxString[newRange]
            return Double(tempStr)!
        }
        
        return  0.0
        
    }
    
    
    func updateUIDataLabels() {
        self.tempDataLabel.text = String(data.temp) + " ºC"
        self.airQualityDataLabel.text = String(data.airQuality) + " ppm"
        self.airHumidityDataLabel.text = String(data.enviromentHumidity) +  " %"
        self.humidityDataLabel.text = String(data.groundHumidity) + " points"
        
    }
        
        
    // MARK: System funcs

    override func viewDidLoad() {
        super.viewDidLoad()
        //requestDataFromServer(urlToRequestStr: "http://192.168.1.200")
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

