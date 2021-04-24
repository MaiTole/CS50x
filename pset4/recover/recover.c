#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//int sizeOf = 10000;
int i = 0;
FILE* img = NULL;
int jpeg_alrdy_open = 0;

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

   // allocates memory for data from imageCheck to be read into; is the first arg of fread
   unsigned char myReader[512];
   char myPhoto[8];

   // reads data from imageCheck into myReader to test condition
//  int sizeOf = fread(myReader, 1, 512, imageCheck);

   //to keep code running until certain condition is met
   while (fread(myReader, 1, 512, imageCheck) >= 512) {
      if (myReader[0] == 0xff && myReader[1] == 0xd8 && myReader[2] == 0xff && (myReader[3] & 0xf0) == 0xe0) {
          if (img == NULL) {
              sprintf(myPhoto, "%03i.jpg", i);
              i++;
              img = fopen(myPhoto, "w");
              fwrite(myReader, 512, 1, img);
              jpeg_alrdy_open = 1;
           }
           else if (jpeg_alrdy_open == 1) {
              fclose(img);
              sprintf(myPhoto, "%03i.jpg", i);
              i++;
              img = fopen(myPhoto, "w");
              rm -f *.jpgfwrite(myReader, 512, 1, img);
           }
      }
      else if (jpeg_alrdy_open == 1) {
                 fwrite(myReader, 512, 1, img);
      }

   }
   fclose(imageCheck);
   fclose(img);
   return 0;
}