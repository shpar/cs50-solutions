#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void printChar(char c, bool b);

int main(void)
{
  string name = GetString();
  int length = strlen(name);
  
  //prints first initial after potential spaces
  int i = 0;
  while (name[i] == ' ')
    i++;
  printChar(name[i],isupper(name[i]));
  i++;
  //checks for spaces and prints characters after spaces
  while (i < length)
  {
    if (name[i-1] == ' ' && name[i] != ' ')
      printChar(name[i],isupper(name[i]));
    i++;
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