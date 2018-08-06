#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient mqttClient(espClient);
char mqttReceiveBuffer[256];

void mqttSubscribeCb(char* topic, byte *payload, unsigned int length) {
  Serial.println("-------new message from broker-----");
  Serial.print("topic: ");
  Serial.println(topic);
  Serial.print("ayload: ");  
  Serial.write(payload, length);
  Serial.println();
  strncpy(mqttReceiveBuffer,(const char *)(payload),length);
  //mqttReceiveBuffer[length] = '\0';
  //Serial.println(strlen(mqttReceiveBuffer));
  mqttClient.publish("get/echo",mqttReceiveBuffer);
}

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

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

  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setCallback(mqttSubscribeCb);
 
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (mqttClient.connect("ESP32Client-19834766", MQTT_USERNAME, MQTT_PASSWORD )) {
 
      Serial.println("connected");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(mqttClient.state());
      delay(2000);
 
    }
  }
 
  mqttClient.publish("get/echo", "Hello from ESP32");
  mqttClient.subscribe("set/echo");
}

void loop() {
  mqttClient.loop();
}