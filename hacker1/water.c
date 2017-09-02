#include <stdio.h>
#include <cs50.h>

int main(void)
{

  int a;
  do
  {
    printf("Showering minutes:");
    a = GetInt();
  }
  while (a <= 0);

  printf("Number of bottles:%i\n", a * 12);

  return 0;

}