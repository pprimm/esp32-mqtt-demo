#ifndef MyMQTT_h
#define MyMQTT_h
#include <PubSubClient.h>

#define MQTT_MSG_CALLBACK void (*mqttMsgCallback)(char*, char*, PubSubClient&)
#define MQTT_CONNECT_CALLBACK void (*mqttConnectCallback)(PubSubClient&)

void connectToWifi(void);
void connectToMQTTBroker(MQTT_CONNECT_CALLBACK, MQTT_MSG_CALLBACK);
void serviceMQTTConnection(void);

#endif // MyMQTT_h