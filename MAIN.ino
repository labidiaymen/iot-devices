/**
 * Author Labidi Aymen <labidi@aymen.co>
 * Vaulab iot sensor project 
 * 2021
 */
#include "DHT.h"

//#define POWER_CONSUMPTION_SENSOR
#define DEBUG
#define DHT11_PIN 4
#define DHTTYPE DHT11

uint8_t DHTPin = D4; 

DHT dht(DHTPin, DHTTYPE);                

float Temperature;
float Humidity;
 

void setup(){
   pinMode(DHTPin, INPUT);
    dht.begin();              

    Serial.begin(115200);
    Serial.printf("\t Main -- \n");
    //setupWIFI();
    //MQTTSetup();
  #if defined(POWER_CONSUMPTION_SENSOR)
    powerConsumptionSetup();
  #endif
    
}


void loop(){
  //wifiLoop();
  //MQTTLoop();
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  Serial.print("Temperature = ");
  Serial.println(Temperature);
  Serial.print("Humidity = ");
  Serial.println(Humidity);
  float h = analogRead(4);
  delay(1000);
  
 // float h = analogRead(0);
  Serial.println(h);
if (!isnan(h))
{
//Serial.println(h/1023*100);

}
  #if defined(POWER_CONSUMPTION_SENSOR)
    PowerConsumptionLoop();
  #endif
}
