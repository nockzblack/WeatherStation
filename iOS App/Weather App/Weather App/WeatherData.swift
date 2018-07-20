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
    
    
    
    
}
