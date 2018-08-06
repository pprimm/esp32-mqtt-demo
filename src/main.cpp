#include <Arduino.h>
#include "MyMQTT.h"

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  connectToWifi();

  connectToMQTTBroker();
}

void loop() {
  serviceMQTTConnection();
}