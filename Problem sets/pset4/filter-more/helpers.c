#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE gray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0);
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int widthLoop;
    if (width % 2 !=  0)
    {
       widthLoop = width - 1;
    }
    else
    {
        widthLoop = width;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < widthLoop/2; j++)
        {
            RGBTRIPLE temp[height][width];
            temp[i][j] = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp[i][j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float count = 0;
            float red = 0;
            float green = 0;
            float blue = 0;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (i + x < 0 || i + x > (height-1))
                    {
                        continue;
                    }

                    if (j + y < 0 || j + y > (width-1))
                    {
                        continue;
                    }

                    count++;
                    red = red + image[i+x][j+y].rgbtRed;
                    green = green + image[i+x][j+y].rgbtGreen;
                    blue = blue + image[i+x][j+y].rgbtBlue;

                }
            }
            temp[i][j].rgbtRed = round(red / count);
            temp[i][j].rgbtGreen = round(green / count);
            temp[i][j].rgbtBlue = round(blue / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redX = 0;
            int redY = 0;
            int blueX = 0;
            int blueY = 0;
            int greenX = 0;
            int greenY = 0;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (i + x < 0 || i + x > (height-1))
                    {
                        continue;
                    }

                    if (j + y < 0 || j + y > (width-1))
                    {
                        continue;
                    }

                    redX = redX + image[i+x][j+y].rgbtRed * gx[x+1][y+1];
                    redY = redY + image[i+x][j+y].rgbtRed * gy[x+1][y+1];

                    blueX = blueX + image[i+x][j+y].rgbtBlue * gx[x+1][y+1];
                    blueY = blueY + image[i+x][j+y].rgbtBlue * gy[x+1][y+1];

                    greenX = greenX + image[i+x][j+y].rgbtGreen * gx[x+1][y+1];
                    greenY = greenY + image[i+x][j+y].rgbtGreen * gy[x+1][y+1];

                }
            }

            temp[i][j].rgbtRed = fmin(round(sqrt((redX * redX) + (redY * redY))), 255);
            temp[i][j].rgbtBlue = fmin(round(sqrt((blueX * blueX) + (blueY * blueY))), 255);
            temp[i][j].rgbtGreen = fmin(round(sqrt((greenX * greenX) + (greenY * greenY))), 255);

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }

    return;
}
