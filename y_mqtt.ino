
void pub_sens() {

  char buffer[256];
  //dtostrf(fire.NUMFirePIXELS, 0, 0, buffer);

  // Allocate the JSON document
  //
  // Inside the brackets, 200 is the RAM allocated to this document.
  // Don't forget to change this value to match your requirement.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<200> jsondoc;

  // Add values in the document
  JsonObject lv_ldr = jsondoc.createNestedObject("AS312");
  lv_ldr["Status"] = gv_as312_trigger;

  int n  = serializeJson(jsondoc, buffer);

  client.publish(mqtt_GetTopic_P(gv_ptopic, mqtt_pre_tele, gv_clientname, (PGM_P)F("SENSOR")), buffer, true);
}



void callback(String topic, byte* message, unsigned int length) {
  String messageTemp;
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  if (topic == topic_PHOTO) {
    Serial.println("PING");
    take_picture();
  }
  if (topic == topic_CONFIG) {
    deserializeJson(CONFIG, messageTemp);
    Serial.println(messageTemp);
    sensor_t * s = esp_camera_sensor_get();
    s->set_framesize(s, FRAMESIZE_VGA); //QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA
    s->set_vflip(s, CONFIG["vflip"]); //0 - 1
    s->set_hmirror(s, CONFIG["hmirror"]); //0 - 1
    s->set_colorbar(s, CONFIG["colorbar"]); //0 - 1
    s->set_special_effect(s, CONFIG["special_effect"]); // 0 - 6
    s->set_quality(s, CONFIG["quality"]); // 0 - 63
    s->set_brightness(s, CONFIG["brightness"]); // -2 - 2
    s->set_contrast(s, CONFIG["contrast"]); // -2 - 2
    s->set_saturation(s, CONFIG["saturation"]); // -2 - 2
    s->set_sharpness(s, CONFIG["sharpness"]); // -2 - 2
    s->set_denoise(s, CONFIG["denoise"]); // 0 - 1
    s->set_awb_gain(s, CONFIG["awb_gain"]); // 0 - 1
    s->set_wb_mode(s, CONFIG["wb_mode"]); // 0 - 4
  }
}

String macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i) {
    if (mac[i] < 0x10 ) {
      result += '0';
    }
    result += String(mac[i], 16);
    //if (i < 5)
    //  result += ':';
  }
  return result;
}

void get_clientname(const char *iv_hostname) {
  // Generate hostname based on MAC address

  clientName += iv_hostname;
  uint8_t mac[6];
  WiFi.macAddress(mac);
  clientName += macToStr(mac);

  gv_clientname = (char*) clientName.c_str();
}


void reconnect() {
  String lv_lwt;
  char lv_lwtc[40];

  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    mqtt_clientname = gv_clientname;
    lv_lwt = gv_clientname;
    lv_lwt += "/tele/LWT";
    lv_lwt.toCharArray(lv_lwtc, sizeof(lv_lwtc));
    //Serial.print(lv_lwtc);
    if (client.connect(gv_clientname, mqtt_user, mqtt_pass, lv_lwtc, 0, true, "offline")) {
      client.publish(lv_lwtc, "online", true);

      pub_info2();

      Serial.println("connected");

      //client.subscribe(topic_PHOTO);
      //client.subscribe(topic_CONFIG);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
