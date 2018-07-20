//: Playground - noun: a place where people can play

import UIKit


// Example of data received from server
/* <meta http-equiv='refresh' content='1'/><body><html><h1>Whether Station</h1><h3>Temp: 27.68 C </h3><h3>Calidad del Aire: 163 ppm </h3><h3>Humedad del Suelo: 968 </h3><h3>Humedad del Ambiemte: 63.0 %</h3></body></html> */

var data = "<meta http-equiv='refresh' content='1'/><body><html><h1>Whether Station</h1><h3>Temp: 27.68 C </h3><h3>Calidad del Aire: 163 ppm </h3><h3>Humedad del Suelo: 968 </h3><h3>Humedad del Ambiemte: 63.0 %</h3></body></html>"

let tempRange = data.range(of: "Temp:")
//let startTempIndex = tempRange!.upperBound
let startTempIndex = data.index(tempRange!.upperBound, offsetBy: 1)
let endTempIndex = data.index(tempRange!.upperBound, offsetBy: 6)
let newRange = startTempIndex..<endTempIndex
let tempStr = data[newRange]
let tempDouble = Double(tempStr)


