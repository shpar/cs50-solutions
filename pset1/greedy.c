#include <stdio.h>
#include <cs50.h>
#include <math.h>

float getPositiveFloat(void);
int change(int cents);

int main(void)
{

  //gets non-negative float
  float dollars = getPositiveFloat();
  //rounds the sum to cents and casts them as an integer
  int cash = (int) roundf(dollars*100);
  
  //calculates number of coins
  int coins = change(cash);
  
  printf("%i\n", coins);
  
  return 0;

}

float getPositiveFloat(void)
{
  
  float f;
  do
  {
    printf("Total sum:");
    f = GetFloat();
  }
  while (f < 0);
  
  return f;
  
}

int change(int cents)
{
  
  //calculates the number of quarters and adds them to the coin sum
  int coins = cents / 25;
  //calculates the number of dimes and adds them to the coin sum
  coins += cents % 25 / 10;
  //calculates the number of nickles and adds them to the coin sum
  coins += cents % 25 % 10 / 5;
  //calculates the number of cents and adds them to the coin sum
  coins += cents % 25 % 10 % 5;
  
  return coins;
  
}