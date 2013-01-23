#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define X 5
#define Y 5

int main( int argc, char **argv ) {
  FILE *fp;
  long test;
  int i, row = 0;
  char line[80];

  int matrix[5][5];

  fp = fopen("lol.txt", "r");
  int bytes_to_read = ( X * 2 - 1 ); // Numero di caratteri da leggere * 2 ( dato che ci sono anche spazi ) - 1 ( dato che alla fine non compaiono spazi ).

  while( fgets(line, 80, fp ) != NULL ) {
    for( i = 0; i < bytes_to_read; i += 2 ) {
      matrix[row][i] = line[i] - 48;
      printf("%d ", matrix[row][i]);
    }
    row++;
    printf("\n");
  }

  fclose(fp);
}