//
//  WeatherData.swift
//  Weather App
//
//  Created by Fernando Benavides Rodriguez on 7/20/18.
//  Copyright © 2018 Nockzblack. All rights reserved.
//

import Foundation

class WeatherData {
    var temp: Double
    var airQuality: Int
    var groundHumidity: Int
    var enviromentHumidity: Double
    
    init(temp: Double, airQuality: Int, groundHumidity: Int, enviromentHumidity: Double) {
        self.temp = temp
        self.airQuality = airQuality
        self.groundHumidity = groundHumidity
        self.enviromentHumidity = enviromentHumidity
    }

    init() {
        self.temp = 00.00
        self.airQuality = 0
        self.groundHumidity = 0
        self.enviromentHumidity = 00.00
    }
    
    func toString() -> String {
        var auxString = "The weather Data is\n"
        auxString += "Temp: \(self.temp) ºCº\n"
        auxString += "Air Quality: \(self.airQuality) ppm\n"
        auxString += "Ground Humidity: \(self.groundHumidity) %\n"
        auxString += "Enviroment Humidity: \(self.enviromentHumidity)"
        
        return auxString
    }
    
    
    
    
}
