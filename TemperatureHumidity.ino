/**
 * Author Labidi Aymen <labidi@aymen.co>
 * Vaulab iot sensor project 
 * 2021
 */
#include "DHT.h"

#define DHT11_PIN 4
#define DHTTYPE DHT11

#define TEMPERATURE_MESUREMENT_INTEVAL 5000
float temperature;
float humidity;
uint8_t DHTPin = D4; 
unsigned long temperatureLastMeasurement = 0;
const char *TEMPERATURE_CONSUMPTION_TOPIC = "temperature/sensors9352874";

DHT dht(DHTPin, DHTTYPE);    

void temperatureHumiditySetup(){
   pinMode(DHTPin, INPUT);
   dht.begin();
}



void temperatureHumidityLoop(){
  unsigned long currentMillis = millis();
                                                                     
  if(currentMillis - temperatureLastMeasurement > TEMPERATURE_MESUREMENT_INTEVAL){
    temperatureLastMeasurement = millis();
    temperature = dht.readTemperature(); 
    humidity = dht.readHumidity(); 

    String jsonMesurements = F("{\"temp\": ");
    jsonMesurements+= String(temperature);
    jsonMesurements+= F(",\"humidity\": ");
    jsonMesurements+= String(humidity);
    jsonMesurements+= F("}");
    
    Serial.println(jsonMesurements);
    MQTT_Publish(TEMPERATURE_CONSUMPTION_TOPIC,String(jsonMesurements).c_str());

  }
  
}
