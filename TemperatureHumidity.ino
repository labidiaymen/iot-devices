/**
 * Author Labidi Aymen <labidi@aymen.co>
 * Vaulab iot sensor project 
 * 2021
 */
#include "DHT.h"

#define DHT11_PIN 2
#define DHTTYPE DHT11

#define TEMPERATURE_MESUREMENT_INTEVAL 60000
float temperature;
float humidity;
unsigned long temperatureLastMeasurement = 0;
const char *TEMPERATURE_CONSUMPTION_TOPIC = "temperature/sensors9352874";

DHT dht(DHT11_PIN, DHTTYPE);    

void temperatureHumiditySetup(){
  Serial.println(D4);

   pinMode(DHT11_PIN, INPUT);
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
