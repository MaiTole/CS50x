#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
 float n;

    do 
   {
    n = get_float("How much change is required?: ");
   }
    while (n < 0);
   
   int y = round(n*100);
   
  int coins25 = (y / 25);
   
  int cashleft = y - (coins25*25);
   // printf("%i\n", cashleft);
   // printf("%i\n", coins25);
    
  int coins10 = (cashleft / 10);
   
  int cashleft2 = cashleft - (coins10*10);
   // printf("%f\n", cashleft2);
   // printf("%i\n", coins10);
    
  int coins5 = (cashleft2 / 5);
   
  int cashleft3 = cashleft2 - (coins5*5);
   // printf("%f\n", cashleft3);
   // printf("%i\n", coins5);
    
  int coins1 = (cashleft3 / 1);
   // printf("%i\n", coins1);
  
   int coinstotal = coins25 + coins10 + coins5 + coins1;

   printf("%i\n", coinstotal);
}