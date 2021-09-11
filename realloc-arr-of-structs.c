#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* One of the issues with a program that reads a file
   into an array in memory is that you don't know how big the
   file is, so you don't know how big to make the array.

   In C, you can use realloc to resize the memory allocated
   to what is in effect an array on the heap */

/* Sample data lines
   #%% Read file into array of structs
   5 0 Wednesday Sunny
   6 2 Thursday Wet
*/

int main() {
  /* Define a daydata structure */
  typedef struct {
    float n_adults; float n_kids;
    char day[10]; char weather[10];
  } daydata ;
  daydata * db;
  daydata * current;

  FILE * filehandle;
  char line[121];

  char *item;
  int reccount = 0;
  int k;

  /* Here comes the actions! */
  /* open file */

  filehandle = fopen("daydata.txt","r");

  /* Read file line by line */
  db = calloc(0, sizeof(daydata));

  while (fgets(line, 120, filehandle)) {
    printf(" We just read a line with contents = %s",line);
    printf("Our db will be len = %d, and bytes = %lu\n", reccount+1, (reccount+1)*sizeof(daydata));

    db = realloc(db, (reccount+1)*sizeof(daydata));
    current = (db+reccount);

    item = strtok(line, " ");
    current->n_adults = atof(item);
    item = strtok(NULL, " ");
    current->n_kids = atof(item);
    item = strtok(NULL, " ");
    strcpy(current->day, item);
    item = strtok(NULL, "\n");
    strcpy(current->weather, item);
    printf("%s\n", current->day);

    reccount++;
  }

  /* Close file */

  fclose(filehandle);

  /* Loop through and report on data */

  printf("\n\nWeather Record\n");
  current = db;
  for (k=0; k<reccount; k++) {
    printf("It is %s\n", current->weather);
    printf("Adults: %f\n", current->n_adults);
    current++;
  }

}
