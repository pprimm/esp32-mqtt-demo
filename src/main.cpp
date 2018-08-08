#include <Arduino.h>
#include "MyMQTT.h"

#define LED_ON "ON"
#define LED_OFF "OFF"

void mqttConnected(PubSubClient& client) {
  String hello("Hello from ESP32 ");
  hello.concat(DEVICE_NAME);
  client.publish(GET_ECHO_TOPIC, hello.c_str());
  client.publish(GET_LED_TOPIC, LED_OFF);
  client.subscribe(SUBSCRIBE_TOPIC);
}

void mqttMessage(char* topic, char* value, PubSubClient& client) {
  String topicString(topic);
  String valueString(value);
  if (topicString.equals(SET_ECHO_TOPIC)) {
    client.publish(GET_ECHO_TOPIC,valueString.c_str());
    return;
  }
  if (topicString.equals(SET_LED_TOPIC)) {
    valueString.toUpperCase();
    Serial.println(valueString);
    uint8_t ledValue = valueString.equals(LED_ON) ? HIGH : LOW;
    digitalWrite(LED_BUILTIN, ledValue);
    client.publish(GET_LED_TOPIC,ledValue == HIGH ? LED_ON : LED_OFF);
  }
}


void setup() {
  Serial.begin(115200);
  delay(10);
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  connectToWifi();

  connectToMQTTBroker(mqttConnected,mqttMessage);
}

void loop() {
  serviceMQTTConnection();
}