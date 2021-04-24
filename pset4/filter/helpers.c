#include <cs50.h>
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float gray;
    double grayscale;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

        gray = ((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
        grayscale = round(gray);
        image[i][j].rgbtBlue = grayscale;
        image[i][j].rgbtRed = grayscale;
        image[i][j].rgbtGreen = grayscale;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
     for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

        float sepiaRed = (0.393*image[i][j].rgbtRed + 0.769*image[i][j].rgbtGreen + 0.189*image[i][j].rgbtBlue);
        float sepiaGreen = (0.349*image[i][j].rgbtRed + 0.686*image[i][j].rgbtGreen + 0.168*image[i][j].rgbtBlue);
        float sepiaBlue = (0.272*image[i][j].rgbtRed + 0.534*image[i][j].rgbtGreen + 0.131*image[i][j].rgbtBlue);
        double sepiaRedNew = round(sepiaRed);
        double sepiaGreenNew = round(sepiaGreen);
        double sepiaBlueNew = round(sepiaBlue);
        if (sepiaRedNew > 255) { sepiaRedNew = 255; }
        if (sepiaBlueNew > 255) { sepiaBlueNew = 255; }
        if (sepiaGreenNew > 255) {sepiaGreenNew = 255; }
        image[i][j].rgbtBlue = sepiaBlueNew;
        image[i][j].rgbtRed = sepiaRedNew;
        image[i][j].rgbtGreen = sepiaGreenNew;
        }
     }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //int newArray[height][width];
    for (int i = 0; i < height; i++) {
             //newArray[i] = image[i];
        //for (int j = 0; j < width; j++) {
          for (int j = 0; j < width/2; j++) { // width by 2 method
             RGBTRIPLE k = image[i][j]; // width by 2 method
             image[i][j] = image[i][width-1-j]; // width by 2 method
             image[i][width-1-j] = k; // width by 2 method
        //     image[i][j] = image[i][width-1-i];
        //  image[i][j] = newArray[i][width-1-j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newArray[height][width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            //calculate for top-left corner
            if (i == 0 && j == 0) {
                double newBlue = round((image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +image[i+1][j].rgbtBlue +image[i+1][j+1].rgbtBlue)/4.0);
                double newRed = round((image[i][j].rgbtRed + image[i][j+1].rgbtRed +image[i+1][j].rgbtRed +image[i+1][j+1].rgbtRed)/4.0);
                double newGreen = round((image[i][j].rgbtGreen + image[i][j+1].rgbtGreen +image[i+1][j].rgbtGreen +image[i+1][j+1].rgbtGreen)/4.0);

                newArray[i][j].rgbtBlue = newBlue;
                newArray[i][j].rgbtGreen = newGreen;
                newArray[i][j].rgbtRed = newRed;
            }
            //calculate for top-right corner
            else if (i == 0 && j == width-1) {
                double newBlue = round((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue +image[i+1][j].rgbtBlue +image[i+1][j-1].rgbtBlue)/4.0);
                double newRed = round((image[i][j].rgbtRed + image[i][j-1].rgbtRed +image[i+1][j].rgbtRed +image[i+1][j-1].rgbtRed)/4.0);
                double newGreen = round((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen +image[i+1][j].rgbtGreen +image[i+1][j-1].rgbtGreen)/4.0);

                newArray[i][j].rgbtBlue = newBlue;
                newArray[i][j].rgbtGreen = newGreen;
                newArray[i][j].rgbtRed = newRed;
            }
            //calculate for bottom-left corner
            else if (i == height-1 && j == 0) {
                double newBlue = round((image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +image[i-1][j].rgbtBlue +image[i-1][j+1].rgbtBlue)/4.0);
                double newRed = round((image[i][j].rgbtRed + image[i][j+1].rgbtRed +image[i-1][j].rgbtRed +image[i-1][j+1].rgbtRed)/4.0);
                double newGreen = round((image[i][j].rgbtGreen + image[i][j+1].rgbtGreen +image[i-1][j].rgbtGreen +image[i-1][j+1].rgbtGreen)/4.0);

                newArray[i][j].rgbtBlue = newBlue;
                newArray[i][j].rgbtGreen = newGreen;
                newArray[i][j].rgbtRed = newRed;
            }
           //calculate for bottom-right corner
           else if (i == height-1 && j == width-1) {
                double newBlue = round((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue +image[i-1][j].rgbtBlue +image[i-1][j-1].rgbtBlue)/4.0);
                double newRed = round((image[i][j].rgbtRed + image[i][j-1].rgbtRed +image[i-1][j].rgbtRed +image[i-1][j-1].rgbtRed)/4.0);
                double newGreen = round((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen +image[i-1][j].rgbtGreen +image[i-1][j-1].rgbtGreen)/4.0);

                newArray[i][j].rgbtBlue = newBlue;
                newArray[i][j].rgbtGreen = newGreen;
                newArray[i][j].rgbtRed = newRed;
            }
            //calculate for top row, non-corner
           else if (i == 0 && 0 < j < width-1) {
                double newBlue = round((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue)/6.0);
                double newRed = round((image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed)/6.0);
                double newGreen = round((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen)/6.0);

                newArray[i][j].rgbtBlue = newBlue;
                newArray[i][j].rgbtGreen = newGreen;
                newArray[i][j].rgbtRed = newRed;
            }
            //calculate for bottom row, non-corner
           else if ((i == height-1) && (0 < j < width-1)) {
                double newBlue = round((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j+1].rgbtBlue +image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue)/6.0);
                double newRed = round((image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i][j+1].rgbtRed +image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed)/6.0);
                double newGreen = round((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j+1].rgbtGreen +image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen)/6.0);

                newArray[i][j].rgbtBlue = newBlue;
                newArray[i][j].rgbtGreen = newGreen;
                newArray[i][j].rgbtRed = newRed;
            }
            //calculate for left-most column, non-corner
           else if ((0 < i < height-1) && j == 0) {
                double newBlue = round((image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i+1][j].rgbtBlue +image[i-1][j+1].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue)/6.0);
                double newRed = round((image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i+1][j].rgbtRed +image[i-1][j+1].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j+1].rgbtRed)/6.0);
                double newGreen = round((image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i+1][j].rgbtGreen +image[i-1][j+1].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen)/6.0);

               newArray[i][j].rgbtBlue = newBlue;
               newArray[i][j].rgbtGreen = newGreen;
               newArray[i][j].rgbtRed = newRed;
            }
            //calculate for right-most column, non-corner
           else if ((0 < i < height-1) && (j == width-1)) {
                double newBlue = round((image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i+1][j].rgbtBlue +image[i-1][j-1].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue)/6.0);
                double newRed = round((image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i+1][j].rgbtRed +image[i-1][j-1].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed)/6.0);
                double newGreen = round((image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i+1][j].rgbtGreen +image[i-1][j-1].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen)/6.0);

                newArray[i][j].rgbtBlue = newBlue;
                newArray[i][j].rgbtGreen = newGreen;
                newArray[i][j].rgbtRed = newRed;
            }
            else if ((0 < i < height-1) && (0 < j < width-1)) {

               double newBlue = round(((image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue) / 9.0));
               double newRed = round(((image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed) / 9.0));
               double newGreen = round(((image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen) / 9.0));

               newArray[i][j].rgbtBlue = newBlue;
               newArray[i][j].rgbtGreen = newGreen;
               newArray[i][j].rgbtRed = newRed;

            }
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
         image[i][j].rgbtBlue = newArray[i][j].rgbtBlue;
         image[i][j].rgbtRed = newArray[i][j].rgbtRed;
         image[i][j].rgbtGreen = newArray[i][j].rgbtGreen;
        }
    }
    return;
}