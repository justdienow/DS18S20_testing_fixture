#include <OneWire.h>
#include <DallasTemperature.h>

/*-----------------------------------------------------------------------------------------------
 * Create object references
 * ----------------------------------------------------------------------------------------------*/

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

// Create an array for DS18B20 sensor addresses
DeviceAddress  DS18B20[3]; 

/*-----------------------------------------------------------------------------------------------
 * Function: INIT_DS18B20
 * Description: Initialize DS18B20 Temperature sensor(s) and print message
 * Ins: none
 * Outs: none
 * ----------------------------------------------------------------------------------------------*/
 
void INIT_DS18B20()
{
  sensors.begin();
  
  if(sensors.getDeviceCount() > 0){
    Serial.print("There are ");
    Serial.print(sensors.getDeviceCount());
    Serial.print(" OneWire devices on the bus of pin 2\n\r");
    delay(1000);
  }else{
    Serial.print("There are no OneWire devices connected!\n\r");
  }
}

/*-----------------------------------------------------------------------------------------------
 * Function: tempInCelsius
 * Description: Get celsius reading from DS18B20 Temperature sensor
 * Arguments: Integer value for sensor address
 * Returns: Float in celsius reading
 * ----------------------------------------------------------------------------------------------*/
float tempInCelsius(int address){
  if (sensors.getAddress(DS18B20[address], address)){
    sensors.requestTemperatures();
    return sensors.getTempC(DS18B20[address]);
  }else{
    return 0;
  }
}

/*-----------------------------------------------------------------------------------------------
 * Function: deviceIsConnected
 * Description: Checking to make sure that the DS18B20 is connected to the Arduino.
 * Arguments: Integer value for sensor address
 * Returns: Returns a boolean value of true or false
 * ----------------------------------------------------------------------------------------------*/
bool deviceIsConnected(int address){
  if (sensors.getAddress(DS18B20[address], address)){
    return true;
  }else{
    return false;
  }
}

/*-----------------------------------------------------------------------------------------------
 * Main routines
 * ----------------------------------------------------------------------------------------------*/
void setup(void){
  Serial.begin(115200);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  // Initialize DS18B20 temperature sensors
  INIT_DS18B20();
}

void loop(void){
  if(deviceIsConnected(0)){  
    float temp_c;
    // Read values from the sensor at address 0
    temp_c = tempInCelsius(0);
    //print the temperature in Celsius
    Serial.print("Temperature: ");
    Serial.print(temp_c);
    Serial.print("°C\n\r");
  }else{
    Serial.print("There are no OneWire devices connected!\n\r");
  }
  
  delay(500);
}