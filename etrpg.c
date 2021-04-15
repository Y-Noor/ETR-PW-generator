#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

// function for data validation
int inpt()
{
  int n;
  // boolean value to use as a check
  char flag;
  flag = '0';
  printf("Input the number of words you wish to have in your e-t-r: ");
  scanf("%d", &n);
  while (flag == '0')
  {
    // check if input is within valid range
    if (n > 2 && n < 5)
    {
      flag = '1';
    }
    else
    {
      printf("INVALID INPUT. Please input an integer between 2 and 5 (not inclusive): ");
      scanf("%d", &n);
    }
  }
  // return valid input to main function
  return n;
}

// function to generate a random number in range [lower, upper]
int randNumGen(int lower, int upper)
{
  return (rand() % (upper - lower + 1) + lower);
}

// function to deal with the dictionaries. returns a string
char* fileHandle(int n, int choice, char* word)
{
    // define string variable that will be used to reference the file
    char path[2];
    // switch structure to cater for each possible choice available and 'create' the adequate path
    switch(choice)
    {
        case 4 :
                strcpy(path, "4");
                break;
        case 5 :
                strcpy(path, "5");
                break;
        case 6 :
                strcpy(path, "6");
                break;
        case 7 :
                strcpy(path, "7");
                break;
    }
    // storing the string on the heap
    char *line = (char *)malloc(sizeof(char)*10);

    // opening the file (path chosen previously with switch statement) for read
    FILE * fpointer = fopen(path, "r");

    // fgets stores the next line in a file. the loop will iterate a randomly generated amount of times (n), thus fetching
    // the word at line n in the file
    for (int i = 0; i < n; i++){
      fgets(line, 10, fpointer);
    }
    // closing the file
    fclose(fpointer);

    // copying the string fetched from the file to a locally declared string so that we can free the memory before returning to main
    strcpy(word, line);
    // freeing the memory on the heap
    free(line);
    return word;
}

int main()
{
    int x, n, choice;
    char cleaned[9];
    char pw[50] = "";
    int size;
    char word[9] = "";
    // Use current time as seed for random generator
    srand(time(0));

    x = inpt();
    printf("\nGenerating password \n");
    sleep(1);

    // loop that will iterate x number of times where 2 < x < 5
    for (int i = 0; i < x; i++)
    {
      // randomly picking a dictionary
      choice = randNumGen(4, 7);
      // generating tls
      //he line at which the word must be fetched in the dictionary
      n = randNumGen(1, 500);
      // storing the returned word to a variable in the scope of the main fuction
      strcpy(word,fileHandle(n, choice, word));
      // finding out how many characters are in the word
      size = strlen(word);
      strcpy(cleaned, word);
      // fgets returns the line with an added new line character. cleaned is a copy of the returned word where that new line character
      // is removed
      cleaned[size-1] = '\0';
      strcat(pw, cleaned);

      // formatting the output
      if (i != (x-1))
      {
        strcat(pw, "-");
      }
      sleep(1.5);
      printf("%d %s",(i+1), word);
      printf("\a");
    }
    sleep(2);
    printf("\nYour e-t-r password is: ");
    printf("%s\n", pw);
    return 0;
}
