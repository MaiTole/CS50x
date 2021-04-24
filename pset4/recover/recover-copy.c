#include <stdio.h>
#include <stdlib.h>

int sizeOf = 1000000000;
int main(int argc, char *argv[])
{
   if (argc != 2) {
       printf("./recover image\n");
       return 1;
   }

   // returns a pointer to opened file, imageCheck
   FILE *imageCheck = fopen(argv[1], "r");
   if (!imageCheck) {
      return 1;
   }

   //to keep code running until certain condition is met
   while (sizeOf >= 512) {
   // allocates memory for data from imageCheck to be read into; is the first arg of fread
   unsigned char myReader[512];
   char myPhoto[512];
   // reads data from imageCheck into myReader to test condition
   fread(&myReader, 1, 512, imageCheck);
   sizeOf = fread(&myReader, 1, 512, imageCheck);

      if (myReader[0] == 0xff && myReader[1] == 0xd8 && myReader[2] == 0xff && (myReader[3] & 0xf0) == 0xe0) {
        for (int i = 0; i < ((sizeof("card.raw")/512)+1); i++) {
         sprintf(myPhoto, "%03i.jpg", i);
        }
         FILE *img = fopen(myPhoto, "w");
         fwrite(&myReader, 512, 1, img);
      }
   }
}
