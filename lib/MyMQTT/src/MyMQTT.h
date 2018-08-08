#ifndef MyMQTT_h
#define MyMQTT_h
#include <PubSubClient.h>

// topic 
#define MY_CALLBACK_SIGNATURE void (*callback)(char*, char*, PubSubClient&)

void connectToWifi(void);
void connectToMQTTBroker(MY_CALLBACK_SIGNATURE);
void serviceMQTTConnection(void);

#endif // MyMQTT_h