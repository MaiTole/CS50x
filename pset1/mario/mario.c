#include <cs50.h>
#include <stdio.h>

int main(void)
{
  int n;
    do
    {
      n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
       for (int j = 1; j < n+1; j++)
       {
          for (int i = 0; i < n-j; i++)
                {
                  printf(" ");
                }
           for (int k = 0; k < j; k++)
                {
                  printf("#");
                }
            printf("\n");
        }
}