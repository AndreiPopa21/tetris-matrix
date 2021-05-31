#include <FastLED.h>
#include "Constants.h"

void paint_red(CRGB* cell);
void paint_green(CRGB* cell);
void paint_blue(CRGB* cell);
void paint_yellow(CRGB* cell);
void paint_purple(CRGB* cell);
void paint_empty(CRGB* cell);
void paint_leds(CRGB* leds);

void paint_red(CRGB* cell) {
  (*cell) = CRGB(RED[0], RED[1], RED[2]);
}

void paint_green(CRGB* cell) {
  (*cell) = CRGB(GREEN[0], GREEN[1], GREEN[2]);
}

void paint_blue(CRGB* cell) {
  (*cell) = CRGB(BLUE[0], BLUE[1], BLUE[2]);
}

void paint_yellow(CRGB* cell) {
  (*cell) = CRGB(YELLOW[0], YELLOW[1], YELLOW[2]);
}

void paint_purple(CRGB* cell) {
  (*cell) = CRGB(PURPLE[0], PURPLE[1], PURPLE[2]);
}

void paint_empty(CRGB* cell) {
  (*cell) = CRGB(EMPTY[0], EMPTY[1], EMPTY[2]);
}


void paint_leds(CRGB* leds, char** Boards) {
  int index = 0;
  for (int i = 0; i < HEIGHT; i++)
    for (int j = 0; j < WIDTH; j++) {
      switch (Boards[i][j]) {
        case GREEN_CHAR:
          paint_green(&leds[index]);
          break;
        case PURPLE_CHAR:
          paint_purple(&leds[index]);
          break;
        case RED_CHAR:
          paint_red(&leds[index]);
          break;
        case BLUE_CHAR:
          paint_blue(&leds[index]);
          break;
        case YELLOW_CHAR:
          paint_yellow(&leds[index]);
          break;
        default:
          paint_empty(&leds[index]);
          break;
      }
      index += 1;
    }
}
