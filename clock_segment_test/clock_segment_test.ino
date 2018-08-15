#include <FastLED.h>

#define LED_PIN     1
#define NUM_LEDS    7
#define BRIGHTNESS  255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

void setup() {
  delay( 3000 );
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
}

int number = 0;
boolean revert = false;
CRGB color = CRGB::Green;

void loop() {
  if (number == 9) {
    revert = true;
  }

  if (number == 0) {
    revert = false;
  }
  
  showNumber(number);
  delay(500);
  
  if (revert) {
    number--;
  }else{
    number++;
  }
}

void showNumber(int number){
  switch (number) {
  case 0:
    showNumberZero(0,color);
    break;
  case 1:
    showNumberOne(0,color);
    break;
  case 2:
    showNumberTwo(0,color);
    break;
  case 3:
    showNumberThree(0,color);
    break;
  case 4:
    showNumberFour(0,color);
    break;
  case 5:
    showNumberFive(0,color);
    break;
  case 6:
    showNumberSix(0,color);
    break;
  case 7:
    showNumberSeven(0,color);
    break;
  case 8:
    showNumberEight(0,color);
    break;
  case 9:
    showNumberNine(0,color);
    break;
  }
  FastLED.show();
}

void showNumberZero(int startLed,CRGB color){
  leds[startLed] = color;
  leds[startLed + 1] = color;
  leds[startLed + 2] = color;
  leds[startLed + 3] = CRGB::Black;
  leds[startLed + 4] = color;
  leds[startLed + 5] = color;
  leds[startLed + 6] = color;
}

void showNumberOne(int startLed,CRGB color){
  leds[startLed] = CRGB::Black;
  leds[startLed + 1] = CRGB::Black;
  leds[startLed + 2] = color;
  leds[startLed + 3] = CRGB::Black;
  leds[startLed + 4] = CRGB::Black;
  leds[startLed + 5] = CRGB::Black;
  leds[startLed + 6] = color;
}

void showNumberTwo(int startLed,CRGB color){
  leds[startLed] = color;
  leds[startLed + 1] = color;
  leds[startLed + 2] = CRGB::Black;
  leds[startLed + 3] = color;
  leds[startLed + 4] = CRGB::Black;
  leds[startLed + 5] = color;
  leds[startLed + 6] = color;
}

void showNumberThree(int startLed,CRGB color){
  leds[startLed] = CRGB::Black;
  leds[startLed + 1] = color;
  leds[startLed + 2] = color;
  leds[startLed + 3] = color;
  leds[startLed + 4] = CRGB::Black;
  leds[startLed + 5] = color;
  leds[startLed + 6] = color;
}

void showNumberFour(int startLed,CRGB color){
  leds[startLed] = CRGB::Black;
  leds[startLed + 1] = CRGB::Black;
  leds[startLed + 2] = color;
  leds[startLed + 3] = color;
  leds[startLed + 4] = color;
  leds[startLed + 5] = CRGB::Black;
  leds[startLed + 6] = color;
}

void showNumberFive(int startLed,CRGB color){
  leds[startLed] = CRGB::Black;
  leds[startLed + 1] = color;
  leds[startLed + 2] = color;
  leds[startLed + 3] = color;
  leds[startLed + 4] = color;
  leds[startLed + 5] = color;
  leds[startLed + 6] = CRGB::Black;
}

void showNumberSix(int startLed,CRGB color){
  leds[startLed] = color;
  leds[startLed + 1] = color;
  leds[startLed + 2] = color;
  leds[startLed + 3] = color;
  leds[startLed + 4] = color;
  leds[startLed + 5] = color;
  leds[startLed + 6] = CRGB::Black;
}

void showNumberSeven(int startLed,CRGB color){
  leds[startLed] = CRGB::Black;
  leds[startLed + 1] = CRGB::Black;
  leds[startLed + 2] = color;
  leds[startLed + 3] = CRGB::Black;
  leds[startLed + 4] = CRGB::Black;
  leds[startLed + 5] = color;
  leds[startLed + 6] = color;
}

void showNumberEight(int startLed,CRGB color){
  leds[startLed] = color;
  leds[startLed + 1] = color;
  leds[startLed + 2] = color;
  leds[startLed + 3] = color;
  leds[startLed + 4] = color;
  leds[startLed + 5] = color;
  leds[startLed + 6] = color;
}

void showNumberNine(int startLed,CRGB color){
  leds[startLed] = CRGB::Black;
  leds[startLed + 1] = color;
  leds[startLed + 2] = color;
  leds[startLed + 3] = color;
  leds[startLed + 4] = color;
  leds[startLed + 5] = color;
  leds[startLed + 6] = color;
}

