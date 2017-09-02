#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
  long long a;
  do
  {
    printf("Credit card number:");
    a = GetLongLong();
  }
  while (a <= 0);
    
  int number[16];
  int digits = 0;
  int sum = 0;
    
  while (a > 0) 
  {
    number[digits] = a % 10;
    a = a / 10;
    digits++;
  }
   
  digits--; 
    
  for (int i = 1; i <= digits; i = i + 2)
  {
    if (2*number[i] > 9)
      sum = sum + ((2 * number[i]) / 10) + ((2 * number[i]) % 10);
    else 
      sum = sum + (2 * number[i]); 
  } 
    
  for (int i = 0; i <= digits; i = i + 2)
    sum = sum + number[i];

  if (sum % 10 == 0)
  {
    if ((number[digits] == 3) && (number[digits-1] == 4) && digits == 14) 
      printf("AMEX\n");
    else if ((number[digits] == 3) && (number[digits-1] == 7) && digits == 14) 
      printf("AMEX\n");
    else if ((number[digits] == 5) && ((number[digits-1] < 6) || (number[digits-1] > 0))) 
      printf("MASTERCARD\n");
    else if (number[digits] == 4 && digits == 12) 
      printf("VISA\n");
    else if (number[digits] == 4 && digits == 15) 
      printf("VISA\n");
    else 
      printf("INVALID\n");
  }
    
  else 
    printf("INVALID\n");

  return 0;

}