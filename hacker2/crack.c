#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
  if (argc == 2)
    {
      char salt[3];
      char *res = crypt("Berkeley","HA");
      for (int i = 0; i < 2; i++)
        salt[i] = argv[1][i];
      salt[2]='\0';

      FILE* words = fopen("/usr/share/dict/words", "r");
      char s[50];
      string test2;

    
      do
      {
        test2 = fgets(s, 50, words);
        int len = strlen(test2);
        if (test2[len-1] == '\n')
          test2[len-1] = 0;

      }
      while(fgets(s, 50, words) != NULL && strcmp(crypt(test2,salt),argv[1]) != 0);
      printf("password: %s\n", test2);

      fclose(words);
      return 0;    
    }
  else
  {
      printf("PFFFF\n");
      return 1;
  }
}

