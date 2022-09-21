#include "helpers.h"
#include <math.h>
#include <stdio.h>



// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // each row 1 by 1
    for (int i = 0; i < height; i++)
    {
        //in that row each pixel 1 by 1
        for (int j = 0; j < width; j++)
        {
            //take each value (rgb) and store them in a variable, they have to be floats so that u can round them correctly
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;
            //take an avarage of those variables
            int avg = round((red + green + blue) / 3);

            //make the rgb avg color which will end up giving a shade of gray
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}



// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_image[height][width];
    //for loops are same explanation as the first one
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_image[i][j] = image[i][j];

        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp_image[i][width - j - 1];
        }
    }

    return;
}



// Blur image
// create a file in which i will transfer the files and back just like in reflect
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_image[height][width];

    //copy the image to the temp_image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float total_red = 0;
            float total_green = 0;
            float total_blue = 0;

            int avgred = 0;
            int avggreen = 0;
            int avgblue = 0;

            float red = 0;
            float green = 0;
            float blue = 0;
            float totalpix = 0;

            for (int x = -1; x <= 1; x++)
            {
                if (i + x >= height || i + x < 0)
                {
                }
                else
                {
                    for (int o = - 1; o <= 1; o++)
                    {
                        if (j + o >= width || j + o < 0)
                        {
                        }
                        else
                        {
                            red = temp_image[i + x][j + o].rgbtRed;
                            green = temp_image[i + x][j + o].rgbtGreen;
                            blue = temp_image[i + x][j + o].rgbtBlue;

                            total_red += red;
                            total_green += green;
                            total_blue += blue;
                            totalpix++;
                        }
                    }
                }
            }

            avgred = round(total_red / totalpix);
            avggreen = round(total_green / totalpix);
            avgblue = round(total_blue / totalpix);

            image[i][j].rgbtRed = avgred;
            image[i][j].rgbtGreen = avggreen;
            image[i][j].rgbtBlue = avgblue;

        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //defines
    int GXRed = 0, GXGreen = 0, GXBlue = 0;
    int GYRed = 0, GYGreen = 0, GYBlue = 0;
    // multiplies defines
    int GXm[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int GYm[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE tempcolor[height][width];

    //copying the colors into a temp
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempcolor[i][j].rgbtRed = image[i][j].rgbtRed;
            tempcolor[i][j].rgbtGreen = image[i][j].rgbtGreen;
            tempcolor[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //for loop for height of image
    for (int i = 0; i < height; i++)
    {
        //for loop for width of image
        for (int j = 0; j < width; j++)
        {
            //for loop for the height part of the square
            for (int y = -1; y < 2; y++)
            {
                //for loop for the width part of the square
                for (int x = -1; x < 2; x++)
                {
                    //checking if its within boundaries, if it isnt then values are set as 0 on default so they will stay that way
                    if (i + y < height && i + y >= 0 && j + x < width && j + x >= 0)
                    {
                        //store each value of every color and both gx/gy after performed the calculations
                        //we need the +1 because the y and x will be -1 and -1 on the first go and that cant happen so we add a 1 to acces the 1st number of the array which is -1
                        GXRed += (tempcolor[i + y][j + x].rgbtRed * GXm[y + 1 ][x + 1]);
                        GXGreen += (tempcolor[i + y][j + x].rgbtGreen * GXm[y + 1][x + 1]);
                        GXBlue += (tempcolor[i + y][j + x].rgbtBlue * GXm[y + 1][x + 1]);

                        GYRed += (tempcolor[i + y][j + x].rgbtRed * GYm[y + 1][x + 1]);
                        GYGreen += (tempcolor[i + y][j + x].rgbtGreen * GYm[y + 1][x + 1]);
                        GYBlue += (tempcolor[i + y][j + x].rgbtBlue * GYm[y + 1][x + 1]);
                    }
                }
            }
            //final formula for calculating the pixel
            int checkred = (int) round(sqrt((int) pow(GXRed, 2) + (int) pow(GYRed, 2)));
            int checkgreen = (int) round(sqrt((int) pow(GXGreen, 2) + (int) pow(GYGreen, 2)));
            int checkblue = (int) round(sqrt((int) pow(GXBlue, 2) + (int) pow(GYBlue, 2)));

            // if the value is higher than 255 then make it 255
            if (checkred > 255)
            {
                checkred = 255;
            }

            if (checkgreen > 255)
            {
                checkgreen = 255;
            }

            if (checkblue > 255)
            {
                checkblue = 255;
            }

            image[i][j].rgbtRed = checkred;
            image[i][j].rgbtGreen = checkgreen;
            image[i][j].rgbtBlue = checkblue;

            //reset all the values for the next go
            GXRed = 0;
            GXGreen = 0;
            GXBlue = 0;
            GYRed = 0;
            GYGreen = 0;
            GYBlue = 0;
        }
    }
    return;
}


