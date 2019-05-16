#ifndef EEPROM_SAVE_H
#define EEPROM_SAVE_H

#include <Arduino.h>
#include "color.h"
#include <Preferences.h>
Preferences prefs;

boolean config_save_switch = false;

void save_settings(CRGB love_color, CRGB happy_color, CRGB sad_color, CRGB fear_color, CRGB anger_color, CRGB lamp_color, uint8_t opmode) {
  prefs.begin("settings", false);
  prefs.putBool("valid", true);
  prefs.putBytes("love_color", &love_color, sizeof(CRGB));
  prefs.putBytes("happy_color", &happy_color, sizeof(CRGB));
  prefs.putBytes("sad_color", &love_color, sizeof(CRGB));
  prefs.putBytes("fear_color", &love_color, sizeof(CRGB));
  prefs.putBytes("anger_color", &love_color, sizeof(CRGB));
  prefs.putBytes("lamp_color", &love_color, sizeof(CRGB));
  uint8_t tmp[1];
  tmp[0] = opmode;
  prefs.putBytes("opmode", tmp, 1);
  prefs.end();
}

CRGB load_color(const char * s) {
  uint8_t tmp[sizeof(CRGB)];
  prefs.getBytes(s, tmp ,sizeof(CRGB));
  return *((CRGB *)tmp);
}

void load_settings() {
  prefs.begin("settings", false);
  bool hasPref = prefs.getBool("valid", false);
  if (hasPref) {
    loveColor = load_color("love_color");
    happyColor = load_color("happy_color");
    sadColor = load_color("sad_color");
    fearColor = load_color("fear_color");
    angerColor = load_color("anger_color");
    lampColor = load_color("lamp_color");
    uint8_t tmp[1];
    prefs.getBytes("opmode", tmp, 1);
    opmode = tmp[0];
  }
  prefs.end();
}

#endif
