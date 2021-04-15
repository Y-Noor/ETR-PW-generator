#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utime.h>
#include <sys/timeb.h>  /* ftime, timeb (for timestamp in millisecond) */
#include <sys/time.h>   /* gettimeofday, timeval (for timestamp in microsecond) */

/*
readFile(char path[49], int wordLength, int rLine) returns a line rLine from a dictionary
that is stored at path and is called int wordLength value

USAGE:    assign readFile(char path[49], int wordLength, int rLine) to a variable to get a word from dictionary at given line number
          print randNumber(int limit) to display a word from dictionary at given line number

EXAMPLE:  char word[500] = readFile("/Users/Igor/Programs/bin", 5, 200);
          above line will assign word from line "200" from a dictionary called "5" that is stored at "/Users/Igor/Programs/bin"
          to the variable called "word" of type char[500]

          char word[500] = readFile("C:\Users\Igor\bin", 7, 101);
          above line will assign word from line "101" from a dictionary called "7" that is stored at "C:\Users\Igor\bin"
          to the variable called "word" of type char[500]

          printf("%s\n", readFile("C:\Users\Igor\bin", 7, 101));
          above line will print a word from line "101" from a dictionary called "7" that is stored at "C:\Users\Igor\bin"
*/

char *readFile(char path[49], int wordLength, int rLine) {
  static char lineTrimmed[500];
  char str[50];
  sprintf(str, "%s/%d", path, wordLength);
  FILE *file = fopen(str, "r");

  if ( file != NULL ) {
    char line[500]; /* or other suitable maximum line size */
    int x = 0;
    while (fgets(line, sizeof(line), file)) {
      x++;
      if(x == rLine ) {
        memset(&lineTrimmed[0], 0, sizeof(lineTrimmed));
        strncpy(lineTrimmed,line,strlen(line)-1);
        return lineTrimmed;
      }
    }

    fclose(file);
  } else {
    printf("File does not exist \n");
  }

  return lineTrimmed;
}


/*
randNumber(int limit) returns an integer number between 0 and limit

USAGE:  assign randNumber(int limit) to a variable to get the random number
        print randNumber(int limit) to display a random number

Program will sleep for 98765 microseconds to allow random number generation as they are based on time
*/
int randNumber(int limit) {
  struct timeb timer_msec;
  int result;
  long long int timestamp_msec; /* timestamp in millisecond. */
  if (!ftime(&timer_msec)) {
    timestamp_msec = ((long long int) timer_msec.time) * 1000ll +
                        (long long int) timer_msec.millitm;
  } else {
    timestamp_msec = -1;
  }
	srand ( timestamp_msec );
	result = rand() % limit;
  usleep(98765);

  return result;
}

int main(void) {
  /* YOUR CODE HERE */
}
