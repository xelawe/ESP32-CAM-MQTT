void setupButton()
{
//#if defined(BUTTON_1)
//  button.attachClick([]() {
//    static bool en = false;
//    sensor_t *s = esp_camera_sensor_get();
//    en = en ? 0 : 1;
//    s->set_vflip(s, en);
//#if defined(SSD130_MODLE_TYPE)
//    if (en) {
//      oled.resetOrientation();
//    } else {
//      oled.flipScreenVertically();
//    }
//#endif
//    // delay(200);
//  });
//
//  button.attachDoubleClick([]() {
//    if (PWDN_GPIO_NUM > 0) {
//      pinMode(PWDN_GPIO_NUM, PULLUP);
//      digitalWrite(PWDN_GPIO_NUM, HIGH);
//    }
//
//#if defined(SSD130_MODLE_TYPE)
//    ui.disableAutoTransition();
//    oled.setTextAlignment(TEXT_ALIGN_CENTER);
//    oled.setFont(ArialMT_Plain_10);
//    oled.clear();
//#if defined(AS312_PIN) && defined(PIR_SUPPORT_WAKEUP)
//    oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "Set to wake up from PIR");
//#elif defined(BUTTON_1)
//    oled.drawString(oled.getWidth() / 2 - 5, oled.getHeight() / 2 - 20, "Deepsleep");
//    oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2 - 10, "Set to be awakened by");
//    oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "a key press");
//#else
//    oled.drawString(oled.getWidth() / 2, oled.getHeight() / 2, "Set to wake up by timer");
//#endif
//    oled.display();
//    delay(3000);
//    oled.clear();
//    oled.displayOff();
//#else
//    delay(2000);
//#endif  /*SSD130_MODLE_TYPE*/
//
//
//#if defined(AS312_PIN) && defined(PIR_SUPPORT_WAKEUP)
//    esp_sleep_enable_ext1_wakeup(((uint64_t)(((uint64_t)1) << AS312_PIN)), ESP_EXT1_WAKEUP_ANY_HIGH);
//#elif defined(BUTTON_1)
//    // esp_sleep_enable_ext0_wakeup((gpio_num_t )BUTTON_1, LOW);
//#if defined(T_Camera_MINI_VERSION)
//    esp_sleep_enable_ext1_wakeup(((uint64_t)(((uint64_t)1) << BUTTON_1)), ESP_EXT1_WAKEUP_ANY_HIGH);
//#else
//    esp_sleep_enable_ext1_wakeup(((uint64_t)(((uint64_t)1) << BUTTON_1)), ESP_EXT1_WAKEUP_ALL_LOW);
//#endif
//#else
//    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
//#endif
//    esp_deep_sleep_start();
//  });
//#if defined(T_Camera_MINI_VERSION)
//  button.setClickTicks(200);
//  button.setDebounceTicks(0);
//#endif
//#endif /*BUTTON_1*/
}
