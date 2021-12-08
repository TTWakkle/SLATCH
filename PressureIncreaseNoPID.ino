/*=========================================================================
File Name: PressureIncreaseNoPID.ino
Description: 
  This program's funtion is to pump vinegar at certain intervals
in order to reach a linear increase in pressure as close as possible.
This program does not utilize the data from pressure transducer and 
therefore has no information feedback loop running, it is a simple 
procedure the Arduino follows for a duration of 3 minutes and returns
a set of data.
Author: Taha Twakkal
Date: 2021/11/15 -- Present.
=========================================================================*/

//Declaring variables
  #include <Wire.h>
  #include <HardwareSerial.h>
  
  //pressure transducer variables
    const int pressureInput = A4;                     // tells you where the input of the pressure readings on the arduino
    const float pressureZero =  99.0;                 // this is an analog number that represents the value of pressure read at 0psi based on the minimum voltage the transducer is running on(~0.5V)
    const float pressureMax = (1024 - pressureZero);  // this is an analog number that represents the value of pressure read at 500psi based on the maximum volts the transducer is running on(~4.5V)
    const int pressureTransducerMaxPSI = 500;         // max psi the transducer can read.
    const int sensorReadDelay = 100;                  // the delay at which the sensor reads and shows you the data at, in milliseconds.
    double maxPSIRead = 0;                            // this records the highest PSI read so far
    double pressureValue = 0;                         // this variable records the value of psi read from the arduinio's analog pin, pressureInput
  
  //Pump and operation of system variables
    const int baudRate = 9600;                        // int value to set the baud rate for reading stuff on the serial monitor
    int timer = 0;                                    // This variable is only used to allow t inside the for-loop to be used by operations outside of the for loop
    int timePoweredOff = 600;                         // the time in which the pump is inactive or idle
    int timePoweredOn = 400;                          // the time in which the pump is active 
    const int waterPump = 10;                         // declares which digital pin will control the transistor that is running the water pump
    int pumpPowerRate = 0;                            // a range from 0-255, this variable relates to the percentage of power the pump is operating (0-255 = 0%-100%)
    
  
//initializing program
  void setup() {
    Serial.begin(baudRate);                           // initializes the serial monitor
    pinMode(waterPump, OUTPUT);                       // initializes the water pump motor (we tell the code which pin is controlling the pump's motor)

  }

//function that finds and stores the maximum PSI the Transducer has recorded
  void findMaxPSIRead() {
  if(maxPSIRead < pressureValue){
      maxPSIRead = pressureValue;
    }
}

//an operation that alternates the rate and power at which the water pump is operating at
  void pumpOperation() {
    //this if statement changes the rate at which the motor is pumping to counteract the effect of pressure build up, which slows the system down
    //TODO: rewrite this if function so that it's only changing the pumpPowerRate, then executing the analogWrite & delay functions.
      if( (timer >= 36) && (timer < 72) ) {
        pumpPowerRate = 91;
        analogWrite(waterPump, pumpPowerRate);
        delay(timePoweredOn);
      }
      else if( (timer >= 72) && (timer < 108) ) {
        pumpPowerRate = 99;
        analogWrite(waterPump, pumpPowerRate);
        delay(timePoweredOn);
      }
      else if( (timer >= 108) && (timer < 144)) {
        pumpPowerRate = 107;
        analogWrite(waterPump, pumpPowerRate);
        delay(timePoweredOn);
      }
      else if (timer >= 144) {
        pumpPowerRate = 115;
        analogWrite(waterPump, pumpPowerRate);
        delay(timePoweredOn);
      }
      else {
        pumpPowerRate = 87;
        analogWrite(waterPump, pumpPowerRate);
        delay(timePoweredOn);
      }
    // returns the pump to its idle state  
      pumpPowerRate = 79;                                 // this rate causes the pump to remain on but idle without pumping into the reaction chamber (Pump was damaged due to vinegar, less efficient)
      analogWrite(waterPump, pumpPowerRate); 
      delay(timePoweredOff);
    
  }

//This function collects & converts the analog value the arduino is reccieving from an integer to a PSI value
  
//looped function that runs 180 times before halting the arduino
  void loop() {
    for (int t = 0; t <= 180; t++) {
      //Collecting pressure data
        pressureValue = analogRead(pressureInput);
        pressureValue = ((pressureValue - pressureZero)*pressureTransducerMaxPSI)/(pressureMax-pressureZero); 
        findMaxPSIRead();
        timer = t;
      //operating system and dispaying values on the serial monitor        
        //Serial.print(timer);
        //Serial.println(" seconds have passed");
        Serial.println(pressureValue);
        //Serial.println(" PSI");   
        //Serial.print(maxPSIRead);
        //Serial.println(" max PSI recorded so far");
        pumpOperation();
    }
    exit(0);


  }
