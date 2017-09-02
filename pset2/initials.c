#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void printChar(char c, bool b);

int main(void)
{
  string name = GetString();
  int length = strlen(name);
  
  //prints first initial
  printChar(name[0],isupper(name[0]));
  
  //checks for spaces and prints characters after spaces
  for (int i = 0; i < length; i++)
  {
    if (name[i] == ' ')
    printChar(name[i+1],isupper(name[i+1]));
  }
  printf("\n");
  return 0;
}

void printChar(char c, bool b)
{
  //prints all characters upper case
  if (b)
    printf("%c", c);
  else
    printf("%c", (char) ((int) c - (int) 'a' + (int) 'A'));
}