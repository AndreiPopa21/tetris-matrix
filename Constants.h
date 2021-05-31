#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 6
#define WIDTH 6

#define DOWN 0
#define UP 1
#define RIGHT_DOWN 2
#define LEFT_UP 3
#define LEFT_DOWN 4
#define RIGHT_UP 5

#define RED_CHAR    'R'
#define GREEN_CHAR  'G'
#define BLUE_CHAR   'B'
#define YELLOW_CHAR 'Y'
#define PURPLE_CHAR 'P'
#define EMPTY_CHAR  'O'

#define SQ_TETRO 10
#define I_HOR_TETRO 20
#define I_VERT_TETRO 30
#define T_TETRO 40
#define T_LEFT_TETRO 50

const int RED[3] = {255, 0, 0};
const int GREEN[3] = {0, 255, 0};
const int BLUE[3] = {0, 0, 255};
const int YELLOW[3] = {255, 255, 0};
const int PURPLE[3] = {128, 0, 128};
const int EMPTY[3] = {0, 0, 0};

//DOWN | UP | RIGHT_DOWN | LEFT_UP | LEFT_DOWN | RIGHT_UP
int dir_x[6] = {1, -1, 1, -1, 1, -1};
int dir_y[6] = {0, 0, 1, -1, -1, 1};


//int SQ_Tetro_Cells = 4;
//int SQ_Tetro[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};

typedef struct SQ_Tetro {
  int cells = 4;
  int tetro[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
} SQ_Tetro;

typedef struct Tetromino {
  int origin_x;
  int origin_y;
  char color;
  char type;
} Tetro;



/*int S_tetro[3][3] = {{0, 1, 1}, {1, 1, 0}, {0, 0, 0}};
  int Z_tetro[3][3] = {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}};
  int L_right[3][3] = {{0, 0, 1}, {1, 1, 1}, {0, 0, 0}};
  int L_left[3][3] = {{1, 0, 0}, {1, 1, 1}, {0, 0, 0}};
  int T_tetro[3][3] = {{1, 1, 1}, {0, 1, 0}, {0, 0, 0}};
  int SQ_tetro[2][2] = {{1, 1}, {1, 1}};*/
