

void setup()
{

  Serial.begin(115200);

#if defined(I2C_SDA) && defined(I2C_SCL)
  Wire.begin(I2C_SDA, I2C_SCL);
#endif



  bool status;
  status = setupDisplay();
  Serial.print("setupDisplay status "); Serial.println(status);
  
  setupNetwork();

  init_ota(gv_clientname);
  
  status = setupCamera();
  Serial.print("setupCamera status "); Serial.println(status);
  if (!status) {
    delay(10000); esp_restart();
  }

  setupButton();



  startCameraServer();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
  status = setupSensor();
  Serial.print("setupSensor status "); Serial.println(status);
  
  Serial.print("Camera Ready! Use 'http://");
  Serial.print(ipAddress);
  Serial.println("' to connect");
}


void loop()
{

  check_ota();

  check_Sensor();
  
  loopDisplay();

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
