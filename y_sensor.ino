void IRAM_ATTR pir_irq(void* arg) {
  pir_flag = true;
}


bool setupSensor()
{
  pinMode(AS312_PIN, INPUT);
  //pinMode(pir_pin, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(pir_pin), pir_irq, RISING);
  // siehe https://github.com/espressif/esp32-camera/issues/256#issuecomment-813628605
  gpio_set_intr_type(AS312_PIN, GPIO_INTR_POSEDGE);
  gpio_isr_handler_add(AS312_PIN, pir_irq, NULL);

  return true;
}

void check_Sensor()
{
  if (pir_flag) {
    gv_PIR = true;
    // Reset after x Seconds
    gv_PIR_res_mil = millis() + 2000;
    gv_as312_trigger = "ON";
    pub_sens( );
    pir_flag = false;

  } else {
    if (!gv_PIR) {
      return;
    }

    if (gv_PIR_res_mil < millis()) {
      gv_PIR = false;
      gv_as312_trigger = "OFF";
      pub_sens( );
    }
  }

}
