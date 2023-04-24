#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int mean = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = mean;
            image[i][j].rgbtRed = mean;
            image[i][j].rgbtGreen = mean;
        }
    }
    return;
}

int min(int x, int y)
{
    if (x < y)
    {
        return x;
    }
    return y;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepia_rgbtRed = min(round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue), 255);
            int sepia_rgbtGreen = min(round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue), 255);
            int sepia_rgbtBlue = min(round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue), 255);
            image[i][j].rgbtRed = sepia_rgbtRed;
            image[i][j].rgbtGreen = sepia_rgbtGreen;
            image[i][j].rgbtBlue = sepia_rgbtBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE output[height][width];
    for (int i = 0; i < height; i++)
    {
        int k = 0;
        for (int j = width - 1; j >= 0; j--)
        {
            output[i][k] = image[i][j];
            k++;
        }

        for (int l = 0; l < width; l++)
        {
            image[i][l] = output[i][l];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE output[height][width];
    int count;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_rgbtRed = 0;
            int sum_rgbtGreen = 0;
            int sum_rgbtBlue = 0;
            count = 0;
            for (int ii = i - 1; ii <= i + 1; ii++)
            {
                for (int jj = j - 1; jj <= j + 1; jj++)
                {
                    if (jj >= 0 && jj < width && ii >= 0 && ii < height)
                    {
                        sum_rgbtRed += image[ii][jj].rgbtRed;
                        sum_rgbtGreen += image[ii][jj].rgbtGreen;
                        sum_rgbtBlue += image[ii][jj].rgbtBlue;
                        count += 1;
                    }
                }
            }
            int avg_rgbtRed = round((float) sum_rgbtRed / count);
            int avg_rgbtGreen = round((float) sum_rgbtGreen / count);
            int avg_rgbtBlue = round((float) sum_rgbtBlue / count);

            output[i][j].rgbtRed = avg_rgbtRed;
            output[i][j].rgbtGreen = avg_rgbtGreen;
            output[i][j].rgbtBlue = avg_rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = output[i][j];
        }
    }

    return;
}

