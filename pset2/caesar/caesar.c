#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{

string Msg;

  if (argc > 2 || argc < 2)
     {
        printf("Usage: ./caesar key\n");
        return 1;
     }
  else if (argc == 2)
    {
       for (int k = 0, q = strlen(argv[1]); k < q; k++)
            { 
                if (!isdigit(argv[1][k]))
                    {
                       printf("Usage: ./caesar key\n");
                       return 1;
                    }
            }

        for (int i = 0, n = strlen(argv[1]); i < n; i++)
                {
                    Msg = get_string("Plaintext: \n");
                    int key = atoi(argv[1]);

                    for (int x = 0, p = strlen(Msg); x < p; x++)
                      {
                          if isupper(Msg[x])
                          {
                              Msg[x] = ((Msg[x] + key - 65) % 26) + 65;
                          }
                          else if islower(Msg[x])
                          {
                              Msg[x] = ((Msg[x] + key - 97) % 26) + 97;
                          }
                      }
                          printf("ciphertext: %s\n", Msg);
                          break;
                }
    }
}