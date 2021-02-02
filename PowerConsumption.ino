/**
 * Author Labidi Aymen <labidi@aymen.co>
 * Vaulab iot sensor project 
 * 2021
 */
#include "EmonLib.h"

EnergyMonitor emon1;
unsigned long lastMeasurement = 0;
unsigned long timeFinishedSetup = 0;
short measurements[30];
short measureIndex = 0;
const char *POWER_CONSUMPTION_TOPIC = "esp32/power/watts";

void PowerConsumptionLoop(){
  unsigned long currentMillis = millis();

                                                                        // If it's been longer then 1000ms since we took a measurement, take one now!
  if(currentMillis - lastMeasurement > 1000){
    double amps = emon1.calcIrms(1480);                                 // Calculate Irms only
    double watt = amps * 220;

    lastMeasurement = millis();

                                                                        // Readings are unstable the first 5 seconds when the device powers on
                                                                        // so ignore them until they stabilise.
    if(millis() - timeFinishedSetup < 10000){

    }else{
      Serial.println(watt);
      measurements[measureIndex] = watt;
      measureIndex++;
    }
  }

                                                                         // When we have 30 measurements, send them to MQTT!
  if (measureIndex == 30) {
  
                                                                         // Construct the JSON to send to AWS
    String msg = "{\"readings\": [";

    for (short i = 0; i <= 28; i++){
      msg += measurements[i];
      msg += ",";
    }

    msg += measurements[29];
    msg += "]}";
    
    MQTT_Publish(POWER_CONSUMPTION_TOPIC,String(msg).c_str());
    measureIndex = 0;
  }
}
