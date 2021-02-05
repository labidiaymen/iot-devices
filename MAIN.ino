/**
 * Author Labidi Aymen <labidi@aymen.co>
 * Vaulab iot sensor project 
 * 2021
 */

//#define POWER_CONSUMPTION_SENSORss
#define TEMPERATURE_HUMIDITY_SENSOR
#define DEBUG
#define ENABLE_WIFI
#define ENAbLE_MQTT


bool autoConfig();
void smartConfig();
void printWifiStatus();

void setup()
{
pinMode(D2, INPUT_PULLUP);

  Serial.begin(115200);
  pushEventSetup();
  Serial.printf("\t Main -- \n");

  #if defined(ENABLE_WIFI)
      setupWIFI();
  #endif
  #if defined(ENAbLE_MQTT)
      MQTTSetup();
  #endif
  
  #if defined(POWER_CONSUMPTION_SENSOR)
      powerConsumptionSetup();
  #endif
  
  #if defined(TEMPERATURE_HUMIDITY_SENSOR)
      temperatureHumiditySetup();
  #endif
}

void loop()
{

  #if defined(ENABLE_WIFI)
      wifiLoop();
  #endif
  #if defined(ENAbLE_MQTT)
      MQTTLoop();
  #endif
  
  #if defined(TEMPERATURE_HUMIDITY_SENSOR)
      temperatureHumidityLoop();
  #endif
  
  #if defined(POWER_CONSUMPTION_SENSOR)
      PowerConsumptionLoop();
  #endif

  resetButtonConfigLoop();
}
