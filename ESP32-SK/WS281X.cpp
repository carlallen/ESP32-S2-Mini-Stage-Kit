#include "WS281X.h"

const char* const WS281X_COLOUR_ORDER_NAMES[ WS281X_ORDER_COUNT ] = { "RGB", "RBG", "GRB", "GBR", "BRG", "BGR" };

// Indexed the same way as WS281XColourOrder / WS281X_COLOUR_ORDER_NAMES.
static const neoPixelType WS281X_COLOUR_ORDER_FLAGS[ WS281X_ORDER_COUNT ] = {
  NEO_RGB + NEO_KHZ800,
  NEO_RBG + NEO_KHZ800,
  NEO_GRB + NEO_KHZ800,
  NEO_GBR + NEO_KHZ800,
  NEO_BRG + NEO_KHZ800,
  NEO_BGR + NEO_KHZ800,
};

WS281X::WS281X() {
}

WS281X::~WS281X() {
  delete m_strip;
}

void WS281X::Init() {
  m_number_leds  = 0;
  m_gpio_pin     = -1;
  m_colour_order = -1;
  m_strip        = NULL;
}

void WS281X::Setup( const int number_leds, const int gpio_pin, const int colour_order ) {

  if( m_number_leds == number_leds && m_gpio_pin == gpio_pin && m_colour_order == colour_order ) {
    return;
  }

  m_number_leds  = number_leds;
  m_gpio_pin     = gpio_pin;
  m_colour_order = colour_order;

  int order_index = ( colour_order >= 0 && colour_order < WS281X_ORDER_COUNT ) ? colour_order : WS281X_ORDER_GRB;

  delete m_strip;
  m_strip = new Adafruit_NeoPixel( m_number_leds, m_gpio_pin, WS281X_COLOUR_ORDER_FLAGS[ order_index ] );

  m_strip->begin();

  this->AllOff();

  this->Update();
}

void WS281X::Update() {
  m_strip->show();
}

void WS281X::SetColour( const int led_number, const uint8_t red, const uint8_t green, const uint8_t blue, uint8_t brightness ) {
  if( led_number > 0 && led_number <= m_number_leds ) {
    this->SetColourNC( led_number, red, green, blue, brightness );
  }
};

// NC - No range check.
// WS281x LEDs have no separate brightness channel, so brightness (0-31) is applied
// by scaling the RGB values directly.
void WS281X::SetColourNC( int led_number, const uint8_t red, const uint8_t green, const uint8_t blue, uint8_t brightness ) {
  if( brightness > 31 ) {
    brightness = 31;
  }
  m_strip->setPixelColor( led_number - 1, m_strip->Color( ( red * brightness ) / 31, ( green * brightness ) / 31, ( blue * brightness ) / 31 ) );
};

// Brightness = 0-31
void WS281X::SetColourAll( const uint8_t red, const uint8_t green, const uint8_t blue, uint8_t brightness ) {
  for( int led_number = 1; led_number <= m_number_leds; led_number++ ) {
    this->SetColourNC( led_number, red, green, blue, brightness );
  }
};

void WS281X::AllOff() {
  this->SetColourAll( 0, 0, 0, 0 );
};

void WS281X::Dump() {
  uint32_t colour;
  for( int led_number = 0; led_number < m_number_leds; led_number++ ) {
    colour = m_strip->getPixelColor( led_number );
    Serial.printf( "( %i, %i, %i )\n", (uint8_t)( colour >> 16 ), (uint8_t)( colour >> 8 ), (uint8_t)colour );
  }
};
