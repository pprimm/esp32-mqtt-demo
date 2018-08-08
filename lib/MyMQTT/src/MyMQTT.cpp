#include "MyMQTT.h"
#include <WiFi.h>

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void connectToWifi(void) {
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void (*myCallback)(char*, char*, PubSubClient&) = NULL;

char mqttReceiveBuffer[256];
void mqttSubscribeCb(char* topic, byte *payload, unsigned int length) {
  Serial.println("-------new message from broker-----");
  Serial.print("topic: ");
  Serial.println(topic);
  Serial.print("payload: ");  
  Serial.write(payload, length);
  Serial.println();
  strncpy(mqttReceiveBuffer,(const char *)(payload),length);
  mqttReceiveBuffer[length] = '\0';
  //Serial.println(strlen(mqttReceiveBuffer));
  //mqttClient.publish("get/echo",mqttReceiveBuffer);
  if (myCallback) {
    myCallback(topic,mqttReceiveBuffer,mqttClient);
  }
}

void connectToMQTTBroker(MY_CALLBACK_SIGNATURE) {
  myCallback = callback;
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setCallback(mqttSubscribeCb);
 
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD )) {
 
      Serial.println("connected");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(mqttClient.state());
      delay(2000);
 
    }
  }
  mqttClient.publish("get/echo", "Hello from ESP32");
  mqttClient.subscribe("set/#");
}

void serviceMQTTConnection(void) {
  mqttClient.loop();
}