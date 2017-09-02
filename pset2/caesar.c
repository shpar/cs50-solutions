#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ENGALPH (int) 'Z' - (int) 'A'

bool checkInput(string input);
void rotate(char letter, int key);

int main(int argc, string argv[])
{
  //checks correctness of argument
  if (argc == 2 && checkInput(argv[1]) && atoi(argv[1]) >= 0)
    {
      int k = atoi(argv[1]);
      string text = GetString();
      int textlength = strlen(text);
      //scans input one letter at a time
      for (int i = 0; i < textlength; i++)
        //checks if letter is upper/lower/non-alphabetic and rotates accordingly using key k
        rotate(text[i], k);
      
      printf("\n");  
      return 0;    
    }
  else
  {
    printf("PFFFF\n");
    return 1;
  }
}

bool checkInput(string input)
{
  int keylength = strlen(input);
  for (int i = 0; i < keylength; i++)
    {
      if (!isdigit((int) input[i]))
        return 0;
    }
  return 1;
}

void rotate(char letter, int key)
{
  if (isupper((int) letter))
    printf("%c", (char) (((int) letter) + key - (int) 'A') % (ENGALPH + 1) + (int) 'A');
  else if (islower((int) letter))
    printf("%c", (char) (((int) letter) + key - (int) 'a') % (ENGALPH + 1) + (int) 'a');
  else
    printf("%c", letter); 
}