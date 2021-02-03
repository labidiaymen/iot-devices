/**
 * Author Labidi Aymen <labidi@aymen.co>
 * Vaulab iot sensor project 
 * 2021
 */
#define POWER_CONSUMPTION_SENSOR
#define DEBUG
void setup(){
    Serial.begin(115200);
    Serial.printf("\t Main -- \n");
    setupWIFI();
    MQTTSetup();
  #if defined(POWER_CONSUMPTION_SENSOR)
    powerConsumptionSetup();
  #endif
    
}


void loop(){
  wifiLoop();
  MQTTLoop();
  float h = analogRead(0);
if (!isnan(h))
{
//Serial.println(h/1023*100);

}
  #if defined(POWER_CONSUMPTION_SENSOR)
    PowerConsumptionLoop();
  #endif
}
