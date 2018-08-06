### esp32-mqtt

This is a simple Platform.io ESP32-Arduino project showing:
1. How to use the ESP32 WiFi to connect to a wifi network
2. How to use the [platformio build_flags](http://docs.platformio.org/en/latest/projectconf/section_env_build.html) to create named difinitions instead of inline #define(s)
3. How to use install and use the [PubSubClient library](https://github.com/knolleary/pubsubclient) with the ESP32 using ESP8266 examples.  As of this Aug 2018, I have yet to see official ESP32 support for the PubSubClient library.
4. Write your own "library" with three (3) functions (`connectToWifi()`, `connectToMQTTBroker()` and `serviceMQTTConnection()`) to demonstrate where and how to include our code in the platformio `/lib` project folder