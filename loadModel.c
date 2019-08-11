#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
  FILE *objectFile;
  FILE *f2;
  int numbers[2048]; 
  /* make sure it is large enough to hold all the data! */
  int i,j;

  f2 = fopen ("out.txt", "wt");
  objectFile = fopen("test.txt", "rt");

  if(objectFile==NULL) {
    printf("Error: can't open file.\n");
    return 1;
  }
  else {
    printf("File opened successfully.\n");

    i = 0 ;    

    while(!feof(objectFile)) { 
      /* loop through and store the numbers into the array */
      fscanf(objectFile, "%d", &numbers[i]);
      i++;
    }

    fprintf(f2, "Number of numbers read: %d\n\n", i);
    fprintf(f2, "The numbers are:\n");

    for(j=0 ; j<i ; j++) { /* now print them out 1 by 1 */
      fprintf( f2, "%d\n", numbers[j]);
    }

    fclose(objectFile);
    fclose(f2);
    return 0;
  }
}
