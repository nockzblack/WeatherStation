//
//  ViewController.swift
//  Weather App
//
//  Created by Fernando Benavides Rodriguez on 7/16/18.
//  Copyright © 2018 Nockzblack. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    // Vars
    
    
    // IBOutlets
    @IBOutlet weak var tempDataLabel: UILabel!
    
    @IBOutlet weak var airHumidityDataLabel: UILabel!
    
    @IBOutlet weak var airQualityDataLabel: UILabel!
    
    @IBOutlet weak var humidityDataLabel: UILabel!
    
    
    // IBActions
    @IBAction func updateDataValues(_ sender: UIButton) {
        requestDataFromServer(urlToRequestStr: "http://192.168.1.200")
    }
    
    
    // Funcs
    
    func requestDataFromServer(urlToRequestStr:String) {
        
        let auxURL = URL(string: urlToRequestStr)
        
        let task = URLSession.shared.dataTask(with: auxURL!) { (dataReceived, answer, possibleError) in
            
            if possibleError != nil {
                print(possibleError!)
            } else {
                let dataNSStr = NSString(data: dataReceived!, encoding: String.Encoding.utf8.rawValue)
                
                let dataStr = String(dataNSStr!)
                
                let temp = self.getNumberAfter(indentifier: "Temp:", in: dataStr, lenOfData: 5)
                //print(temp)
                //dataStr
                
                // Example of data received from server
                /* <meta http-equiv='refresh' content='1'/><body><html><h1>Whether Station</h1><h3>Temp: 27.68 C </h3><h3>Calidad del Aire: 163 ppm </h3><h3>Humedad del Suelo: 968 </h3><h3>Humedad del Ambiemte: 63.0 %</h3></body></html> */
                
                // Execute asincronamente
                DispatchQueue.main.sync (execute: {
                    self.tempDataLabel.text! = String(temp)
                })

                
                
            }
        }
        
        task.resume()
    }
    
    func getNumberAfter(indentifier:String, in auxString:String, lenOfData:Int) -> Double {
        
        let tempRange = auxString.range(of: indentifier)
        //let startTempIndex = tempRange!.upperBound
        let startTempIndex = auxString.index(tempRange!.upperBound, offsetBy: 1)
        let endTempIndex = auxString.index(tempRange!.upperBound, offsetBy: lenOfData + 1)
        let newRange = startTempIndex..<endTempIndex
        let tempStr = auxString[newRange]
        let tempDouble = Double(tempStr)
        return tempDouble!
    }
    
    // System funcs

    override func viewDidLoad() {
        super.viewDidLoad()
        requestDataFromServer(urlToRequestStr: "http://192.168.1.200")
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

