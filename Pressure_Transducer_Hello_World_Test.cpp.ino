#include <Wire.h>
#include <HardwareSerial.h>
const int pressureInput = A4; //tells you where the input of the pressure readings on the arduino
const float pressureZero =  99.0; //this is a digital number that represents the value of pressure read at 0psi based on the minimum voltage the transducer is running on(0.5V)
const float pressureMax = 925.0; // this is a digital number that represents the value of pressure read at 500psi based on the max volts the transducer is running on(4.5V)
const int pressureTransducerMaxPSI = 500; // max psi the transducer can read
const int baudRate = 9600; //int value to set the baud rate for reading stuff on the serial monitor
const int sensorReadDelay = 100; //the delay at which the sensor reads and shows you the data at, in millisecs,
//int timer = 0;

float pressureValue = 0; //this variable stores the value coming from the pressure transducer
float avgPressureValue = 0; //stores the average pressure read from the transducer, calculated from vaules
float maxPSIRead = 0;
//float slope = 0;
//float prevPV = 0;




void setup() {
  Serial.begin(baudRate); //this starts the serial communication at the set rate in bits per seconds

}

//float determineSlope(){
//  slope = (avgPressureValue - prevPV)/(timer - (timer -1));
//  return slope;
//}

void findMaxPSIRead(){
  if(maxPSIRead < pressureValue){
      maxPSIRead = pressureValue;
    }
}

void loop() {
  
  avgPressureValue = 0;
  
  //for (int i  = 0; i<10 ; i++ ){
    pressureValue = analogRead(pressureInput); //reads the value of pressure from pins and assings it to the pressureValue variable
    pressureValue = ((pressureValue - pressureZero)*pressureTransducerMaxPSI)/(pressureMax-pressureZero); //this conversts the analog reading from the pressure transducer to psi
    findMaxPSIRead();
  
    Serial.println(pressureValue); //prints the pressure value on the serial monitor
    //Serial.println(" psi"); //just tells the reader what unit pressureValue is in

    //avgPressureValue = avgPressureValue + pressureValue; //gets the sum of the pressure recorded in the last 1000ms
    delay(sensorReadDelay); //delay between read values, this tells the arduino to only run this loop once every 250ms
    
  //}
  //avgPressureValue = (avgPressureValue)/10; //divides the sum of the pressure recored by 10 to get the average pressure 
  
  //Serial.print(avgPressureValue);
  //Serial.println(" psi avg in the last second");
  
  //Serial.print("Highest psi recorded in the last second: ");
  //Serial.println(maxPSIRead);

  //Serial.print("The Current increase in pressure in the last second is: ");
  //Serial.println(determineSlope());
}
