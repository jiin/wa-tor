// wa-tor.h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

// define cell structure 

typedef struct fish {
  int x;                // Fish position on x axis
  int y;                // Fish position on y axis
  int moved;            // If this variable is true the shark was already moved
  int reproduce_time;   // Time remaining after fish reproduction
} fish;

// define shark structure 

typedef struct shark {
  int x;        // Shark position on x axis
  int y;        // Shark position on y axis
  int moved;    // If this variable is true the shark was already moved
  int energy;   // Shark's Energy
} shark;

// define cell structure 

typedef struct cell {
  char type;            // Cell's type ( look at define values for more info )
  shark s_pointer;      // Pointer to shark struct
  fish f_pointer;       // Pointer to fish struct
} cell;


static cell matrix[6][10]; // Declare cells matrix used for wa-tor world

int chronon = 0; // Chronons number

#define SEA   0   // Value for identify sea in matrix
#define FISH  1   // Value for identify fish in matrix
#define SHARK 2   // Value for identify shark in matrix

#define SEA_COLOR   1
#define FISH_COLOR  3
#define SHARK_COLOR 4

#define FISH_RIPRODUCE_TIME 5        // Numbers of chronons after that the fish reproduces
#define SHARK_LIFE_UNITIES 10        // Shark's life unities
#define SHARK_REPRODUCE_THRESHOLD 15 // Threshold after the shark reproduces

#define HEIGHT 8 // Matrix's height
#define WIDTH 8  // Matrix's width

#define LIFE_EARNED 1 // energy earned by shark after fish eating

#define CHRONON 1 // seconds passed for each chronon

#ifdef _WIN32
  #define CLEAR system("cls");
#else
  #define CLEAR system("clear");
#endif

int get_random_value( int min, int max );
int toroidal_x( int x );
int toroidal_y( int y );

void spawn_fish( int x, int y, int new_x, int new_y, int born );
void spawn_shark( int x, int y, int new_x, int new_y, int born );

void new_fish_borned( int x, int y );
void new_shark_borned( int x, int y, int life );

void move_fish( int x, int y, int born );
void move_shark( int x, int y, int born );

void cell_manage( int x, int y );
void die( char *msg );

cell mat( int x, int y );