#include <stdio.h>
#include <cs50.h>

int getPositiveInt(void);

int main(void)
{
  
  //asks for a positive integer
  int a = getPositiveInt();
  //returns number of bottles
  printf("Number of bottles:%i\n", a*12);

  return 0;

}

int getPositiveInt(void)
{
  
  int x;
  do
  {
    //keeps prompting the user until it receives a non-negative integer
    printf("Showering minutes:");
    x = GetInt();
  }
  while (x <= 0); 
  
  return x;

}