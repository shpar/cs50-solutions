#include <stdio.h>
#include <cs50.h>

void printSpace(int x);
void printHash(int y);

int main(void)
{
    
  int a;
  do
  {
    printf("The height of the pyramid:");
    a = GetInt();
  }
  while ((a > 23) || (a < 0));

  for (int i = 1; i <= a; i++)
  {
    printSpace(a-i);
    printHash(i);
    printf("  ");
    printHash(i);
    printf("\n");
  }

  return 0;

}

void printSpace(int x)
{

  for (int i = 0; i < x; i++)
    printf(" ");

}

void printHash(int y)
{

  for (int i = 0; i < y; i++)
    printf("#");
   
}