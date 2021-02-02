/**
 * Author Labidi Aymen <labidi@aymen.co>
 * Vaulab iot sensor project 
 * 2021
 */

void setup(){
    Serial.begin(115200);
    Serial.printf("\t Main -- \n");
    setupWIFI();
    MQTTSetup();
}


void loop(){
  wifiLoop();
  MQTTLoop();
}
