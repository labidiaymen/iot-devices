/**
 * Author Labidi Aymen <labidi@aymen.co>
 * Vaulab iot sensor project 
 * 2021
 */
#include "EmonLib.h"

// CONSTANTS
#define CURRENT_VOLTAGE 220
#define MESUREMENT_INTEVAL 1000
#define IRMS_VALUE 1480
#define START_UP_DELAY 10000
#define TOTAL_MESUREMENT_TO_SEND 30
#define CT_SENSOR_PIN 34
#define CT_SENSOR_CALIBRATION 16
// END CONSTANTS

EnergyMonitor emon1;
unsigned long lastMeasurement = 0;
unsigned long timeFinishedSetup = 0;
short wattsMeasurements[TOTAL_MESUREMENT_TO_SEND];
short ampsMeasurements[TOTAL_MESUREMENT_TO_SEND];
short measureIndex = 0;
const char *POWER_CONSUMPTION_TOPIC = "esp32/power/watts";


void powerConsumptionSetup(){
  emon1.current(CT_SENSOR_PIN, CT_SENSOR_CALIBRATION); 
}

void PowerConsumptionLoop(){
  
  unsigned long currentMillis = millis();
                                                                       // If it's been longer then 1000ms since we took a measurement, take one now!
  if(currentMillis - lastMeasurement > MESUREMENT_INTEVAL){
    double amps = emon1.calcIrms(IRMS_VALUE);                           // Calculate Irms only
    if(amps <= 0.5){
      amps = amps - 0.2;
     }
     if(amps <= 0.25){
      amps =  0;
     }
     double watt = amps * CURRENT_VOLTAGE;


    lastMeasurement = millis();
                                                                        // Readings are unstable the first 5 seconds when the device powers on
                                                                        // so ignore them until they stabilise.
    if(millis() - timeFinishedSetup < START_UP_DELAY){

    }else{
      #if defined(DEBUG)
        Serial.print("Watts");        
        Serial.println( watt);
        Serial.print("Amps" );
        Serial.println( amps);
      #endif
  
      wattsMeasurements[measureIndex] = watt;
      measureIndex++;
    }
  }

                                                                         // When we have 30 measurements, send them to MQTT!
  if (measureIndex == TOTAL_MESUREMENT_TO_SEND) {
  
                                                                         // Construct the JSON to send to AWS
    String wattsMesurementsReadings = "[";
    String ampsMesurementsReadings = "[";

    for (short i = 0; i <= TOTAL_MESUREMENT_TO_SEND-2; i++){
      wattsMesurementsReadings += wattsMeasurements[i];
      wattsMesurementsReadings += ",";

      ampsMesurementsReadings += ampsMeasurements[i];
      ampsMesurementsReadings += ",";
    }

    wattsMesurementsReadings += wattsMeasurements[TOTAL_MESUREMENT_TO_SEND-1];
    wattsMesurementsReadings += "]";
    
    ampsMesurementsReadings += ampsMeasurements[TOTAL_MESUREMENT_TO_SEND-1];
    ampsMesurementsReadings += "]";
    
    String jsonMesurements = "{\"apms\": " + ampsMesurementsReadings + ",\"watts\": "+wattsMesurementsReadings+ "}";
    // Serial.println(jsonMesurements);
    MQTT_Publish(POWER_CONSUMPTION_TOPIC,String(jsonMesurements).c_str());
    measureIndex = 0;
  }
}
