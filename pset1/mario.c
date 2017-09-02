#include <stdio.h>
#include <cs50.h>
#define MAX_PYRAMID 23

int getPyramidHeight(void);
void printSpace(int x);
void printHash(int y);

int main(void)
{
  
  //gets pyramid height between zero and MAX_PYRAMID
  int a = getPyramidHeight();  
  
  //prints one pyramid line every iteration 
  for (int i = 1; i <= a; i++)
  {
    //prints space a-i times
    printSpace(a - i);
    
    //prints hash i+1 times
    printHash(i + 1);
    
    //goes into new line
    printf("\n");
  }

  return 0;

}

int getPyramidHeight(void)
{
  
  int h;
  do
  {
    printf("The height of the pyramid:");
    h = GetInt();
  }
  while ((h > MAX_PYRAMID) || (h < 0));
  
  return h;
  
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