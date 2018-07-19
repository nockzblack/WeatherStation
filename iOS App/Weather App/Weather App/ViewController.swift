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
    @IBOutlet weak var updateDataValues: UIButton!
    
    
    // Funcs
    
    func requestDataFromServer(urlToRequestStr:String) {
        
        let auxURL = URL(string: urlToRequestStr)
        
        let task = URLSession.shared.dataTask(with: auxURL!) { (dataReceived, answer, possibleError) in
            
            if possibleError != nil {
                print(possibleError!)
            } else {
                let dataStr = NSString(data: dataReceived!, encoding: String.Encoding.utf8.rawValue)
                
                print(dataStr!)
                
                
                
            }
        }
        
        task.resume()
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

