
#include <FastLED.h>
#include "Tetris.h"
#include "Music.h"

#define NUM_LEDS  40
#define LED_PIN   7

char** Board;
CRGB leds[NUM_LEDS];
int onKeyDown = 0;

void test_grid();
void play_music();

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10);
  Serial.begin(9600);

  srand(time(NULL));
  
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
  pinMode(8, INPUT);
  pinMode(2, INPUT);
  
  Board = (char**)malloc( HEIGHT * sizeof(char*));
  for (int i = 0; i < HEIGHT; i++)
    Board[i] = (char*)malloc(WIDTH * sizeof(char));

  for (int i = 0; i < HEIGHT; i++)
    for (int j = 0; j < WIDTH; j++)
      Board[i][j] = EMPTY_CHAR;
}

// 2  - INPUT PIN - DOWN_LEFT
// 8  - INPUT PIN - DOWN
// 12 - INPUT PIN - DOWN_RIGHT

void loop() {
  int down_left = digitalRead(2);
  int down = digitalRead(8);
  int down_right = digitalRead(12);
  
  if (down_left == HIGH) {
    if (onKeyDown) return;
    onKeyDown = 1;
    Serial.write("Apasat LEFT_DOWN\n");
    every_frame(LEFT_DOWN, Board);
    paint_leds(leds, Board);
  }

  if (down == HIGH) {
    if (onKeyDown) return;
    onKeyDown = 1;
    Serial.write("Apasat DOWN\n");
    every_frame(DOWN, Board);
    paint_leds(leds, Board);
  }

  if (down_right == HIGH) {
    if (onKeyDown) return;
    onKeyDown = 1;
    Serial.write("Apasat RIGHT_DOWN\n");
    every_frame(RIGHT_DOWN, Board);
    paint_leds(leds, Board);
  }
  
  if (down_left == LOW && down == LOW && down_right == LOW)
    onKeyDown = 0;

  FastLED.show()

  play_music();
}

void play_music() {
  int note = get_next_note();
  int del = get_next_delay();
  tone(13, note, 100);
  delay(del)
}

void test_grid() {
  leds[0] = CRGB::Red;
  leds[1] = CRGB::Red;
  leds[2] = CRGB::Red;
  leds[3] = CRGB::Purple;
  leds[4] = CRGB::Red;
  leds[5] = CRGB::Red;
  leds[6] = CRGB::Red;
  leds[7] = CRGB::Red;
  leds[8] = CRGB::Red;
  leds[9] = CRGB::Red;
  leds[10] = CRGB::Red;
  leds[11] = CRGB::Red;
  leds[12] = CRGB::Red;
  leds[13] = CRGB::Red;
  leds[14] = CRGB::Red;
  leds[15] = CRGB::Purple;
  leds[16] = CRGB::Purple;
  leds[17] = CRGB::Red;
  leds[18] = CRGB::Red;
  leds[19] = CRGB::Red;
  leds[20] = CRGB::Purple;
  leds[21] = CRGB::Yellow;
  leds[22] = CRGB::Purple;
  leds[23] = CRGB::Purple;
  leds[24] = CRGB::Purple;
  leds[25] = CRGB::Purple;
  leds[26] = CRGB::Purple;
  leds[27] = CRGB::Red;
  leds[28] = CRGB::Red;
  leds[29] = CRGB::Red;
  leds[30] = CRGB::Red;
  leds[31] = CRGB::Red;
  leds[32] = CRGB::Red;
  leds[33] = CRGB::Red;
  leds[34] = CRGB::Purple;
  leds[35] = CRGB::Red;
  FastLED.show();
}
