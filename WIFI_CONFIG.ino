/**
 * Author Labidi Aymen <labidi@aymen.co>
 * Vaulab iot sensor project 
 * 2021
 * Handling wifi configuration (EspTouch), reconnecting when connexion is lost
 */
 
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32)
  #include <WiFi.h>
#endif
#include <neotimer.h>
#define CONNEXION_LOST_DELAY 5000
#define LED_BUILTIN 2
Neotimer wifiLostTimer = Neotimer(CONNEXION_LOST_DELAY);


bool autoConfig();
void smartConfig();
void printWifiStatus();

void setupWIFI()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    if (!wifiConnect()) {
        smartConfig();
    }
}


bool wifiConnect()
{
    WiFi.begin();
    Serial.print("WiFi Connecting.");
    for (int i = 0; i < 20; i++) {
        if (WiFi.status() == WL_CONNECTED) {
            printWifiStatus();
            digitalWrite(LED_BUILTIN, HIGH);
            return true;
        }
        else {
            Serial.print(".");
            delay(500);
        }
    }
    Serial.println("\nWifi Connect Faild!");
    return false;
    //WiFi.printDiag(Serial);
}

void smartConfig()
{
   
    WiFi.mode(WIFI_STA);
    WiFi.beginSmartConfig();
    Serial.println("Start SmartConfig.");
    Serial.println("Waiting for SmartConfig. Launch Mobile App (ex: ESP-TOUCH ) to progress SmartConfig.");
    while (!WiFi.smartConfigDone()) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("SmartConfig done.");

    Serial.print("WiFi Connecting.");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    printWifiStatus();
    WiFi.setAutoConnect(true);
}

void printWifiStatus()
{
    Serial.println("\nWiFi Connected.");
    Serial.printf("SSID: %s\n", WiFi.SSID().c_str());
    Serial.printf("Password: %s\n", WiFi.psk().c_str());
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void wifiLoop()
{
    if (!WiFi.isConnected()) {
      if(!wifiLostTimer.waiting()){
         wifiLostTimer.start();
      }
      if(wifiLostTimer.done()){
        WiFi.begin();
      }
    }
}
