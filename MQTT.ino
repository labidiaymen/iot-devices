/**
 * Author Labidi Aymen <labidi@aymen.co>
 * Vaulab iot sensor project 
 * 2021
 * This file contain the setup of the MQTT server along with the reconnect and publish funtions
 */
 
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32)
  #include <WiFi.h>
#endif
#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);
long lastReconnectAttempt = 0;
const char* mqtt_server = "192.168.1.186";
const char* topic = "esp32/power/watts";

void MQTTSetup(){
   client.setServer(mqtt_server, 1883);
   Serial.println("MQTT server setup ");
   Serial.println("MQTT server IP ");
   Serial.print(mqtt_server);
   
}

boolean reconnect() {
  if (client.connect("arduinoClient")) {
    //client.subscribe("inTopic");
  }
  return client.connected();
}

void MQTTLoop(){
   if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected

    client.loop();
  }
}

void MQTT_Publish(char* message){
   client.publish(topic,String(message).c_str());
}
