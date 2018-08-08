#include <Arduino.h>
#include "MyMQTT.h"

#define GET_ECHO_TOPIC "get/echo"
#define GET_LED_TOPIC "get/led"
#define SET_ECHO_TOPIC "set/echo"
#define SET_LED_TOPIC "set/led"
#define LED_ON "ON"
#define LED_OFF "OFF"

void myMQTTCallback(char* topic, char* value, PubSubClient& client) {
  String topicString(topic);
  String valueString(value);
  if (topicString.equals(SET_ECHO_TOPIC)) {
    client.publish(GET_ECHO_TOPIC,valueString.c_str());
    return;
  }
  if (topicString.equals(SET_LED_TOPIC)) {
    valueString.toUpperCase();
    Serial.println(valueString);
    uint8_t ledValue = valueString.equals("ON") ? HIGH : LOW;
    digitalWrite(LED_BUILTIN, ledValue);
    client.publish(GET_ECHO_TOPIC,ledValue == HIGH ? LED_ON : LED_OFF);
  }
}


void setup() {
  Serial.begin(115200);
  delay(10);
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  connectToWifi();

  connectToMQTTBroker(myMQTTCallback);
}

void loop() {
  serviceMQTTConnection();
}