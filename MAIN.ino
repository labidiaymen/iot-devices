/**
 * Author Labidi Aymen <labidi@aymen.co>
 * Vaulab iot sensor project 
 * 2021
 */
// #define POWER_CONSUMPTION_SENSOR

void setup(){
    Serial.begin(115200);
    Serial.printf("\t Main -- \n");
    setupWIFI();
    MQTTSetup();
}


void loop(){
  wifiLoop();
  MQTTLoop();
  #if defined(POWER_CONSUMPTION_SENSOR)
    PowerConsumptionLoop();
  #endif
}
