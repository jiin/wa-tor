/*
 *
 *  WA-TOR ~ A cellular automaton to simulate predator-prey.
 *
 *  Copyright (C) 2013 jiin<lotus@paranoici.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#include "wa-tor.c"

int main( int argc, char **argv ) {
  int row, column, bytes_to_read;
  char line[80];

  FILE *fp;

  if( argc < 2 )
    die("- Usage: ./wa-tor [configuration_file]\n");

  srand(time(NULL));

  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

  if(( fp = fopen( argv[1], "r" ) ) == NULL ) {
    die("[Error] An error are occurred in file opening!");
  }
  
  bytes_to_read = ( WIDTH * 2 - 1 );
  row = 0;

  while( fgets(line, 80, fp ) != NULL ) {
    for( column = 0; column < bytes_to_read / 2; column++ ) {
      matrix[row][column].type = line[column * 2] - 48;

      switch( matrix[row][column].type ) {
        case SEA:
          break;
        case FISH:
          matrix[row][column].f_pointer.reproduce_time = FISH_RIPRODUCE_TIME;
          break;
        case SHARK:
          matrix[row][column].s_pointer.energy = SHARK_LIFE_UNITIES;
          break;
      }
    }

    row++;
  }

  fclose(fp);
 
  while(1) {
    for( row = 0; row < WIDTH; row++ ) {
      for( column = 0; column < HEIGHT; column++ ) {
        switch( matrix[row][column].type ) {
          case FISH:
            matrix[row][column].f_pointer.moved = FALSE;
            break;
          case SHARK:
            matrix[row][column].s_pointer.moved = FALSE;
            break;
        }
      }
    }

    for( row = 0; row < WIDTH; row++ ) {
      for( column = 0; column < HEIGHT; column++ ) {
        cell_manage( row, column );
      }
    }

    printf("Chronon: %d\n\n", chronon);

    for( row = 0; row < WIDTH; row++ ) {
      for( column = 0; column < HEIGHT; column++ ) {

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
          ( matrix[row][column].type == SEA  ) ? SEA_COLOR  :
          ( matrix[row][column].type == FISH ) ? FISH_COLOR : SHARK_COLOR );

        printf("%d ", matrix[row][column].type);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
      }
      printf("\n");
    }

    Sleep( CHRONON * 1000 );
    chronon += 1;
    CLEAR;
  }

  return 1;
}
