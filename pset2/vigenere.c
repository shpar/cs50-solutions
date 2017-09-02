#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define ENGALPH (int) 'Z' - (int) 'A' 

bool checkInput(string input);
void rotate(char letter, char key);

int main(int argc, string argv[])
{
  //checks correctness of argument
  if (argc == 2 && checkInput(argv[1]))
  {
    int keylength = strlen(argv[1]);
    string text = GetString();
    int textlength = strlen(text);
    //scans input one letter at a time
    for (int i = 0, j = 0; i < textlength; i++)
    {
      rotate(text[i], argv[1][j % keylength]);
      if (isalpha(text[i]))
        j++;
    }
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
    if (!isalpha(input[i]))
      return 0;
  }
  return 1;
}

void rotate(char letter, char key)
{ 
  //rotation amount for upper/lowercase key letters
  int pw = (isupper((int) key)) ? ((int) key) - (int) 'A' : ((int) key) - (int) 'a'; 
  //rotate upper/lowercase/non-alpha text
  if (isupper((int) letter))
    printf("%c", (char) (((int) letter) + pw - (int) 'A') % (ENGALPH + 1) + (int) 'A');
  else if (islower((int) letter))
    printf("%c", (char) (((int) letter) + pw - (int) 'a') % (ENGALPH + 1) + (int) 'a');
  else
    printf("%c", letter); 
}