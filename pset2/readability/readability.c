#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(void)
{

 float letters;
 float words;
 float space = 0;
 float upper = 0;

string Text = get_string("Text:\n");

int x = strlen(Text);
    for (int i = 0, n = strlen(Text); i < n; i++)
    {

        if isalpha(Text[i])
        {
            letters = letters + 1;
        }

        if isblank(Text[i])
        {
            space = space + 1;
        }
        if (Text[i]=='.' || Text[i]=='!' || Text[i]=='?')
        {
            upper = upper + 1;
        }
    }

words = space + 1;

//printf("%f letter(s)\n", letters);
//printf("%f word(s)\n", words);
//printf("%f sentence(s)\n", upper);

float L = 100*letters/words;
float S = 100*upper/words;

float index = 0.0588 * L - 0.296 * S - 15.8;
int grade = rint(index);

   if (index < 1)
      {
         printf("Before Grade 1\n");
      }
   if (index >= 16)
      {
         printf("Grade 16+\n");
      }
   if (index >= 1 && index < 16)
      {
         printf("Grade %i\n", grade);
      }
}