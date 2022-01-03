/*

  _                      _       _   _
  | |                    (_)     | | | |
  | |      ___ __      __ _  ___ | |_| |  ___
  | |     / _ \\ \ /\ / /| |/ __||  _  | / _ \
  | |____|  __/ \ V  V / | |\__ \| | | ||  __/
  \_____/ \___|  \_/\_/  |_||___/\_| |_/ \___|

  Compatible with all TTGO camera products, written by LewisHe
  03/28/2020

  https://github.com/botabotlab/ESP32CAM-MQTT
*/

#include "esp_camera.h"

/***************************************
    Board select
 **************************************/
/* Select your board here, see the board list in the README for details*/
// #define T_Camera_JORNAL_VERSION
// #define T_Camera_MINI_VERSION
// #define T_Camera_PLUS_VERSION
// #define T_Camera_V05_VERSION
// #define T_Camera_V16_VERSION
// #define T_Camera_V162_VERSION
#define T_Camera_V17_VERSION
// #define ESPRESSIF_ESP_EYE

#include "select_pins.h"

#include <WiFi.h>
#include <Wire.h>

#include "app_httpd.h"


/***************************************
    Function
 **************************************/
//When there is BME280, set the reading time here
#define DEFAULT_MEASUR_MILLIS   3000        /* Get sensor time by default (ms)*/

//When using timed sleep, set the sleep time here
#define uS_TO_S_FACTOR 1000000              /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  5                    /* Time ESP32 will go to sleep (in seconds) */


/***************************************
    WiFi
 **************************************/
#include "cy_wifi_cfg.h"
String clientName;
char *gv_clientname;
#include "cy_ota.h"

String macAddress = "";
String ipAddress = "";

//extern void startCameraServer();

bool deviceProbe(uint8_t addr)
{
  Wire.beginTransmission(addr);
  return Wire.endTransmission() == 0;
}

//bool setupPower()
//{
//#if defined(ENABLE_IP5306)
//#define IP5306_ADDR 0X75
//#define IP5306_REG_SYS_CTL0 0x00
//  if (!deviceProbe(IP5306_ADDR))return false;
//  bool en = true;
//  Wire.beginTransmission(IP5306_ADDR);
//  Wire.write(IP5306_REG_SYS_CTL0);
//  if (en)
//    Wire.write(0x37); // Set bit1: 1 enable 0 disable boost keep on
//  else
//    Wire.write(0x35); // 0x37 is default reg value
//  return Wire.endTransmission() == 0;
//
//#elif defined(ENABLE_AXP192)
//#define AXP192_ADDRESS  0x34
//  if (!deviceProbe(AXP192_ADDRESS))return false;
//  //Turn off no use power channel , Or you can do nothing
//  uint8_t val;
//  Wire.beginTransmission(AXP192_ADDRESS);
//  Wire.write(0x30);
//  Wire.endTransmission();
//  Wire.requestFrom(AXP192_ADDRESS, 1);
//  val = Wire.read();
//
//  Wire.beginTransmission(AXP192_ADDRESS);
//  Wire.write(0x30);
//  Wire.write( val & 0xFC);
//  Wire.endTransmission();
//
//  Wire.beginTransmission(AXP192_ADDRESS);
//  Wire.write(0x12);
//  Wire.endTransmission();
//  Wire.requestFrom(AXP192_ADDRESS, 1);
//  val =  Wire.read();
//
//  Wire.beginTransmission(AXP192_ADDRESS);
//  Wire.write(0x12);
//  Wire.write(val & 0b10100010);
//  Wire.endTransmission();
//#endif
//#if defined(T_Camera_MINI_VERSION)
//  //  There is a pin in the Mini to control the camera power
//  pinMode(POWER_CONTROL_PIN, OUTPUT);
//  digitalWrite(POWER_CONTROL_PIN, HIGH);
//#endif
//
//  return true;
//}

void setupNetwork()
{
  macAddress = "LilyGo-CAM-";
#ifdef SOFTAP_MODE
  WiFi.mode(WIFI_AP);
  macAddress += WiFi.softAPmacAddress().substring(0, 5);
  WiFi.softAP(macAddress.c_str());
  ipAddress = WiFi.softAPIP().toString();
#else
  WiFi.begin(wifi_ssid_i, wifi_pass_i);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  ipAddress = WiFi.localIP().toString();
  macAddress += WiFi.macAddress().substring(0, 5);
#endif
#if defined(ENABLE_TFT)
#if defined(T_Camera_PLUS_VERSION)
  tft.drawString("ipAddress:", tft.width() / 2, tft.height() / 2 + 50);
  tft.drawString(ipAddress, tft.width() / 2, tft.height() / 2 + 72);
#endif
#endif
  get_clientname( "ESP32-CAM" );
  Serial.println(gv_clientname);
}
