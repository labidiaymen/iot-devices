/**
 * Author Labidi Aymen <labidi@aymen.co>
 * Vaulab iot sensor project 
 * 2021
 */

#define PUSH_EVENT_PIN 2
#define PSUH_EVENT_DELAY 1000

void pushEventSetup(){
    pinMode(PUSH_EVENT_PIN, OUTPUT); 
}

void executePushEvent(){
  Serial.println("executePushEvent");
  digitalWrite(PUSH_EVENT_PIN, HIGH);
  delay(PSUH_EVENT_DELAY);
  digitalWrite(PUSH_EVENT_PIN, LOW);
}

 void subscribeToPushEvent(){
    Serial.println("subscribeToPushEvent");
    client.setCallback(callback);
 }

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.println(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "pushEvent/822141") {
    executePushEvent();
    Serial.println("Message ");
    Serial.print(messageTemp);
  }
}
