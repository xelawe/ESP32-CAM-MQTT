/***************************************
    MQTT
 **************************************/
#include <PubSubClient.h>
#include <ArduinoJson.h> //ArduinoJSON6
DynamicJsonDocument CONFIG(2048);


#include "cy_mqtt_v1.h"

const char* topic_PHOTO = "TakeAPicture";
const char* topic_CONFIG = "JSONConfig";
const char* topic_UP = "PICTURE";

const char* gv_as312_trigger = "OFF";

char gv_ptopic[MQTT_TOPSZ];
