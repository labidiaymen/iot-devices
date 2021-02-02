void setup(){
    Serial.begin(115200);
    Serial.printf("\t GAS Sensor -- \n");
    setupWIFI();
}


void loop(){
  wifiLoop();
}
