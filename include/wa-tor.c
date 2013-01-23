// wa-tor.c

#include "wa-tor.h"

void die( char *msg ) {
  printf("%s\n", msg);
  exit(0);
}

int get_random_value( int min, int max ) {
  return(( rand() % max ) + min );
}

int toroidal( int i, int max ) {
  return(
    ( i >= max ) ? i % max :
    ( i <  0   ) ? max - 1 : i
  );
}

int toroidal_x( int x ) {
  return toroidal( x, HEIGHT );
}

int toroidal_y( int y ) {
  return toroidal( y, WIDTH );
}

cell mat( int x, int y ) {
  return matrix[ toroidal_x(x) ][ toroidal_y(y) ];
}

void cell_manage( int x, int y ) {
  switch( matrix[x][y].type ) {
    case FISH:
      if( !matrix[x][y].f_pointer.moved )
        move_fish( x, y, 0 );
      break;
    case SHARK:
      if( !matrix[x][y].s_pointer.moved )
        move_shark( x, y, 0 );
      break;
    case SEA:
      break;
    default:
      die("Matrix bad format.");
      break;
  }
}

void spawn_shark( int x, int y, int new_x, int new_y, int born ) {
  shark tmp;

  tmp.x = new_y;
  tmp.y = new_x;

  if( !matrix[x][y].s_pointer.moved ) {
    if( matrix[x][y].s_pointer.energy <= 0 ) {
      matrix[x][y].type = SEA;
    } else if( matrix[x][y].s_pointer.energy > SHARK_REPRODUCE_THRESHOLD ) {
      matrix[x][y].s_pointer.energy /= 2;
      matrix[x][y].s_pointer.moved = TRUE;

      new_shark_borned( new_x, new_y, matrix[x][y].s_pointer.energy );
    } else {
      if( !born )
        matrix[x][y].s_pointer.energy -= 1;

      if( matrix[new_x][new_y].type == FISH )
        matrix[x][y].s_pointer.energy += LIFE_EARNED;

      tmp.energy = matrix[x][y].s_pointer.energy;
      tmp.moved  = TRUE;

      matrix[new_x][new_y].type = SHARK;
      matrix[new_x][new_y].s_pointer = tmp;

      matrix[x][y].type = SEA;
    }
  }
}

void new_shark_borned( int x, int y, int life ) {
  shark new;

  new.x = y;
  new.y = x;

  new.energy = life;
  new.moved  = FALSE;

  matrix[ toroidal_x(x) ][ toroidal_y(y) ].type = SHARK;
  matrix[ toroidal_x(x) ][ toroidal_y(y) ].s_pointer = new;  
}

void new_fish_borned( int x, int y ) {
  fish new;

  new.x = y;
  new.y = x;

  new.reproduce_time = 10;
  new.moved = FALSE;

  matrix[ toroidal_x(x) ][ toroidal_y(y) ].type = FISH;
  matrix[ toroidal_x(x) ][ toroidal_y(y) ].f_pointer = new;
}

void spawn_fish( int x, int y, int new_x, int new_y, int born ) {
  fish tmp;

  tmp.x = new_y;
  tmp.y = new_x;

  if( !born )
    matrix[x][y].f_pointer.reproduce_time -= 1;

  tmp.reproduce_time = matrix[x][y].f_pointer.reproduce_time;
  tmp.moved = TRUE;

  if( matrix[x][y].f_pointer.reproduce_time > 0 ) {
    matrix[new_x][new_y].type = FISH;
    matrix[new_x][new_y].f_pointer = tmp;

    matrix[ toroidal_x(x) ][ toroidal_y(y) ].type = SEA;
  } else {
    new_fish_borned( x, y );
    move_fish( x, y, 1 );

    if( mat(x,y).type == SEA )
      new_fish_borned(x,y);
  }
}

void move_fish( int x, int y, int born ) {
  int random_index;
  int count = 0;
  int possible_position[4][2];

  if( mat(x + 1, y).type == SEA ) {
    possible_position[count][0] = toroidal_x(x + 1);
    possible_position[count][1] = toroidal_y(y);
    count++;
  }

  if( mat(x, y - 1).type == SEA ) {
    possible_position[count][0] = toroidal_x(x);
    possible_position[count][1] = toroidal_y(y - 1);
    count++;
  }

  if( mat(x, y + 1).type == SEA ) {
    possible_position[count][0] = toroidal_x(x);
    possible_position[count][1] = toroidal_y(y + 1);
    count++;
  }

  if( mat(x - 1, y).type == SEA ) {
    possible_position[count][0] = toroidal_x(x - 1);
    possible_position[count][1] = toroidal_y(y);
    count++;
  }

  if( count > 0 ) {
    random_index = get_random_value( 0, count );
    spawn_fish( x, y, possible_position[random_index][0], possible_position[random_index][1], born );
  }
}

void move_shark( int x, int y, int born ) {
  int random_index;
  int count = 0;
  int possible_position[4][2];

  if( mat(x + 1, y).type == SEA || mat(x + 1, y).type == FISH ) {
    possible_position[count][0] = toroidal_x(x + 1);
    possible_position[count][1] = toroidal_y(y);
    count++;
  }

  if( mat(x, y - 1).type == SEA || mat(x, y - 1).type == FISH ) {
    possible_position[count][0] = toroidal_x(x);
    possible_position[count][1] = toroidal_y(y - 1);
    count++;
  }

  if( mat(x, y + 1).type == SEA || mat(x, y + 1).type == FISH ) {
    possible_position[count][0] = toroidal_x(x);
    possible_position[count][1] = toroidal_y(y + 1);
    count++;
  }

  if( mat(x - 1, y).type == SEA || mat(x - 1, y).type == FISH ) {
    possible_position[count][0] = toroidal_x(x - 1);
    possible_position[count][1] = toroidal_y(y);
    count++;
  }

  if( count > 0 ) {
    random_index = get_random_value( 0, count );
    spawn_shark( x, y, possible_position[random_index][0], possible_position[random_index][1], born );
  }
}
