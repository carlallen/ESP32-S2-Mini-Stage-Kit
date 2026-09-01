#ifndef _WS281X_H_
#define _WS281X_H_

#include "Arduino.h"

#include <Adafruit_NeoPixel.h>

// The order the colour bytes need to be sent in varies between WS281x LED batches/chipsets.
enum WS281XColourOrder {
  WS281X_ORDER_RGB = 0,
  WS281X_ORDER_RBG = 1,
  WS281X_ORDER_GRB = 2,
  WS281X_ORDER_GBR = 3,
  WS281X_ORDER_BRG = 4,
  WS281X_ORDER_BGR = 5,
};

#define WS281X_ORDER_COUNT 6

// Display names for each WS281XColourOrder value, indexed the same way. Also used to populate the config web UI.
extern const char* const WS281X_COLOUR_ORDER_NAMES[ WS281X_ORDER_COUNT ];

class WS281X {
public:
  WS281X();

  ~WS281X();

  void Init();

  void Setup( const int number_leds, const int gpio_pin, const int colour_order );

  void Update();

  void SetColourAll( const uint8_t red, const uint8_t green, const uint8_t blue, uint8_t brightness );

  void SetColour( const int led_number, const uint8_t red, const uint8_t green, const uint8_t blue, uint8_t brightness );

  void AllOff();

  void Dump();

private:
  void SetColourNC( int led_number, const uint8_t red, const uint8_t green, const uint8_t blue, uint8_t brightness );

  int                m_number_leds;
  int                m_gpio_pin;
  int                m_colour_order;
  Adafruit_NeoPixel* m_strip;
};

#endif
