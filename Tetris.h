#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <FastLED.h>
#include "Paint.h"

Tetro* currentTetro;
int spawnNextTetro = 1;
int gameScore = 0;

void move_tetro(int direction);
int reverse_dir(int direction);

int getScore();
int checkCollision(char** Board);
int deleteLinesAndShift(char** Board);
int get_random_tetro();
char get_random_color();
void addScore(int newScore);
void reset_board(char color, char** Board);
void every_frame(int direction, char** Board);
void display_board(char** Board);
void display_shape(Tetro* tetro);
void spawn_new_tetro();
void paint_tetro_in_board(char** Board, char color);

int get_random_tetro() {
    int r = rand() % 5;
    switch (r) {
        case 0:
          return SQ_TETRO;
        case 1:
          return I_HOR_TETRO;
        case 2:
          return T_TETRO;
        case 3:
          return T_LEFT_TETRO;
        default:
          return I_VERT_TETRO;
    }
}

char get_random_color() {
    int r = rand() % 6;
    switch (r) {
        case 0:
          return RED_CHAR;
        case 1:
          return BLUE_CHAR;
        case 2:
          return GREEN_CHAR;
        case 3:
          return YELLOW_CHAR;
        case 4:
          return PURPLE_CHAR;
        default:
          return RED_CHAR;
    }
}

void spawn_new_tetro() {
   currentTetro->origin_x = 0;
   currentTetro->origin_y = WIDTH/2 - 1;
   currentTetro->color = get_random_color();
   currentTetro->type = get_random_tetro();
}

void every_frame(int direction, char** Board) {

  if (currentTetro == NULL) {
      currentTetro = (Tetro*) malloc(sizeof(Tetro));
      if (currentTetro == NULL) {
          Serial.write("\nError could not spawn new tetro\n");
          return; 
      }

      spawn_new_tetro();
      int cannotSpawn = checkCollision(Board);
      if (cannotSpawn == 1) {
          Serial.write("\nCannot spawn. Game is lost\n");
          reset_board(EMPTY_CHAR, Board);
          display_board(Board);
          free(currentTetro);
          currentTetro = NULL;
          return; 
      }
      
      paint_tetro_in_board(Board, currentTetro->color);
      display_board(Board);
      return;
  }
  
  paint_tetro_in_board(Board, EMPTY_CHAR);
  move_tetro(direction);
  int collision = checkCollision(Board);
  if (collision == 1) {
      Serial.write("\nWe have a collision\n");
      move_tetro(reverse_dir(direction));
      paint_tetro_in_board(Board, currentTetro->color);
      int foundLines = deleteLinesAndShift(Board);
      Serial.write("\nS-a sters: ");
      Serial.print(foundLines);Serial.print('\n');
      free(currentTetro);
      currentTetro = NULL;
  }
  else 
    paint_tetro_in_board(Board, currentTetro->color);
  
  display_board(Board);
}

int reverse_dir(int direction) {
    switch(direction) {
        case DOWN:
          return UP;
        case UP:
          return DOWN;
        case RIGHT_DOWN:
          return LEFT_UP;
        case LEFT_UP:
          return RIGHT_DOWN;
        case LEFT_DOWN:
          return RIGHT_UP;
        case RIGHT_UP:
          return LEFT_DOWN;
    }
}

void move_tetro(int direction) {
    switch(direction) {
        case DOWN:
            currentTetro->origin_x += 1;
            break;
        case UP:
            currentTetro->origin_x -= 1;
            break;
        case RIGHT_DOWN:
            currentTetro->origin_x += 1;
            currentTetro->origin_y += 1;
            break;
        case LEFT_UP:
            currentTetro->origin_x -= 1;
            currentTetro->origin_y -= 1;
            break;
        case LEFT_DOWN:
            currentTetro->origin_x += 1;
            currentTetro->origin_y -= 1;
            break;
        case RIGHT_UP:
            currentTetro->origin_x -= 1;
            currentTetro->origin_y += 1;
            break;
    }
}

int checkCollision(char** Board) {
    if (currentTetro == NULL) {
        Serial.write("\nCurrent Tetro is null, cannot check collision on it\n");
        return 0;
    }

    if (currentTetro->type == SQ_TETRO) {
        int lowerLeft_x = currentTetro->origin_x + 1;
        int lowerLeft_y = currentTetro->origin_y;
        int lowerRight_x = currentTetro->origin_x + 1;
        int lowerRight_y = currentTetro->origin_y + 1;

        if (lowerLeft_x >= HEIGHT) return 1;
        if (lowerLeft_y < 0 || lowerLeft_y >= WIDTH) return 1;
        if (Board[lowerLeft_x][lowerLeft_y] != EMPTY_CHAR) return 1;
        if (Board[lowerRight_x][lowerRight_y] != EMPTY_CHAR) return 1;
    }

    if (currentTetro->type == I_HOR_TETRO) {
        int or_x = currentTetro->origin_x;
        int or_y = currentTetro->origin_y;

        for (int i = 0; i < 2; i++) {
            int curr_x = or_x;
            int curr_y = or_y + i;

            if (curr_x >= HEIGHT) return 1;
            if (curr_y < 0 || curr_y >= WIDTH) return 1;
            if (Board[curr_x][curr_y] != EMPTY_CHAR) return 1;
        }
    }

    if (currentTetro->type == I_VERT_TETRO) {
        int or_x = currentTetro->origin_x;
        int or_y = currentTetro->origin_y;

        int bottom_x = or_x + 1;
        int bottom_y = or_y;

        if (bottom_y < 0 || bottom_y >= WIDTH) return 1;
        if (bottom_x >= HEIGHT) return 1;
        if (Board[or_x][or_y] != EMPTY_CHAR) return 1;
        if (Board[or_x + 1][or_y] != EMPTY_CHAR) return 1;
    }

    if (currentTetro->type == T_TETRO) {
        int or_x = currentTetro->origin_x;
        int or_y = currentTetro->origin_y;

        if (Board[or_x][or_y] != EMPTY_CHAR || or_y < 0 || or_y >= WIDTH) return 1;
        if (Board[or_x][or_y + 2] != EMPTY_CHAR || or_y + 2 >= WIDTH) return 1;
        if (Board[or_x + 1][or_y + 1] != EMPTY_CHAR || or_x >= HEIGHT) return 1;
    }

    if (currentTetro->type == T_LEFT_TETRO) {
        int or_x = currentTetro->origin_x;
        int or_y = currentTetro->origin_y;

        if (Board[or_x + 1][or_y] != EMPTY_CHAR || or_y < 0 || or_y >= WIDTH) return 1;
        if (Board[or_x + 2][or_y + 1] != EMPTY_CHAR || or_x + 2 >= HEIGHT || or_y + 1 >= WIDTH) return 1;
        if (Board[or_x + 1][or_y + 1] != EMPTY_CHAR) return 1;
    }
    return 0;
}

void paint_tetro_in_board(char** Board, char color) {
    if (currentTetro == NULL) {
        Serial.write("\nCurrent Tetro is null, cannot paint it\n");
        return;
    }

    if (currentTetro->type == SQ_TETRO) {
        int or_x = currentTetro->origin_x;
        int or_y = currentTetro->origin_y;
        Board[or_x][or_y] = color;
        Board[or_x][or_y+1] = color;
        Board[or_x+1][or_y] = color;
        Board[or_x+1][or_y+1] = color;
    }

    if (currentTetro->type == I_HOR_TETRO) {
        int or_x = currentTetro->origin_x;
        int or_y = currentTetro->origin_y;
        Board[or_x][or_y] = color;
        Board[or_x][or_y + 1] = color;
    }

    if (currentTetro->type == I_VERT_TETRO) {
        int or_x = currentTetro->origin_x;
        int or_y = currentTetro->origin_y;
        Board[or_x][or_y] = color;
        Board[or_x + 1][or_y] = color;
    }

    if (currentTetro->type == T_TETRO) {
        int or_x = currentTetro->origin_x;
        int or_y = currentTetro->origin_y;
        Board[or_x][or_y] = color;
        Board[or_x][or_y+1] = color;
        Board[or_x][or_y+2] = color;
        Board[or_x + 1][or_y + 1] = color;
    }

    if (currentTetro->type == T_LEFT_TETRO) {
        int or_x = currentTetro->origin_x;
        int or_y = currentTetro->origin_y;
        Board[or_x][or_y + 1] = color;
        Board[or_x+1][or_y] = color;
        Board[or_x+1][or_y+1] = color;
        Board[or_x+2][or_y+1] = color;
    }
}

int deleteLinesAndShift(char** Board) {
  int deletedLines = 0;
  for (int i = HEIGHT - 1; i >= 0; i--) {
    int isLineComplete = 1;
    for (int j = 0; j < WIDTH; j++)
      if (Board[i][j] == EMPTY_CHAR) {
        isLineComplete = 0;
        break;
      }

    if (isLineComplete) {
      deletedLines++;
      for (int k = i; k > 0; k--)
        for (int j = 0; j < WIDTH; j++)
          Board[k][j] = Board[k - 1][j];

      for (int j = 0; j < WIDTH; j++)
        Board[0][j] = EMPTY_CHAR;
      
      i = i + 1;
    }
  }
  return deletedLines;
}


void display_board(char** Board) {
  Serial.print('\n');
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      Serial.print(Board[i][j]);
      Serial.print('\t');
    }
    Serial.print('\n');
  }
  Serial.print('\n');
}

void reset_board(char color, char** Board) {
  for (int i = 0; i < HEIGHT; i++)
    for (int j = 0; j < WIDTH; j++)
      Board[i][j] = color;
}

int getScore() {
  return gameScore;
}

void addScore(int newScore) {
  gameScore += newScore;
}
