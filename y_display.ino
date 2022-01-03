bool setupDisplay()
{

  static FrameCallback frames[] = {
    [](OLEDDisplay * display, OLEDDisplayUiState * state, int16_t x, int16_t y)
    {
      display->setTextAlignment(TEXT_ALIGN_CENTER);
      display->setFont(ArialMT_Plain_10);
      //#if (SSD130_MODLE_TYPE)
      //      display->drawString(64 + x, 0 + y, macAddress);
      //      display->drawString(64 + x, 10 + y, ipAddress);
      //#else
      //      display->drawString(64 + x, 9 + y, macAddress);
      //      display->drawString(64 + x, 25 + y, ipAddress);
      //#endif

#if defined(AS312_PIN)
      if (gv_PIR) {
        display->drawString(64 + x, 40 + y, "AS312 Trigger");
      }
      //      if (digitalRead(AS312_PIN)) {
      //        if (String(gv_as312_trigger).equalsIgnoreCase(F("OFF"))) {
      //
      //          gv_as312_trigger = "ON";
      //
      //          pub_sens( );
      //        }
      //        display->drawString(64 + x, 40 + y, "AS312 Trigger");
      //      } else {
      //        if (String(gv_as312_trigger).equalsIgnoreCase(F("ON"))) {
      //          gv_as312_trigger = "OFF";
      //
      //          pub_sens( );
      //        }
      //      }
#endif
    },


    [](OLEDDisplay * display, OLEDDisplayUiState * state, int16_t x, int16_t y)
    {
      display->setTextAlignment(TEXT_ALIGN_CENTER);
      display->setFont(ArialMT_Plain_10);


      //      display->drawString( 64 + x, 0 + y, "Camera Ready! Use");
      //      display->drawString(64 + x, 10 + y, "http://" + ipAddress );
      //      display->drawString(64 + x, 16 + y, "to connect");

    }


  };

  if (!deviceProbe(SSD1306_ADDRESS))
    return false;

  oled.init();
  // Wire.setClock(100000);  //! Reduce the speed and prevent the speed from being too high, causing the screen
  oled.setFont(ArialMT_Plain_16);
  oled.setTextAlignment(TEXT_ALIGN_CENTER);
  // delay(50);
  oled.drawString( oled.getWidth() / 2, oled.getHeight() / 2 - 10, "LilyGo CAM");
  oled.display();

  ui.setTargetFPS(30);
  ui.setIndicatorPosition(BOTTOM);
  ui.setIndicatorDirection(LEFT_RIGHT);

  ui.setFrameAnimation(SLIDE_LEFT);
  ui.setFrames(frames, sizeof(frames) / sizeof(frames[0]));
  //ui.setTimePerFrame(6000);
  ui.setTimePerFrame(2000);
  //ui.disableIndicator();

  ui.disableAllIndicators();
  ui.disableAutoTransition();
  //#endif
  return true;
}


void loopDisplay()
{

  if (ui.update()) {


#if defined(BUTTON_1)
    button.tick();
#endif  /*BUTTON_1*/


  }

}
