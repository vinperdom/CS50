#include "helpers.h"
#include <math.h>
#include <stdio.h>

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


int min(int x, int y)
{
    if (x < y)
    {
        return x;
    }
    return y;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE output[height][width];
    RGBTRIPLE tmp;
    RGBTRIPLE grid[3][3];

    // G
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    // 1: red, 2: green, 3: blue.
    int Gxgrid[3][3][3];
    int Gygrid[3][3][3];
    int Gxsum[3];
    int Gysum[3];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // populate grid
            int row_counter = 0;
            for (int ii = i - 1; ii <= i + 1; ii++)
            {
                int col_counter = 0;
                for (int jj = j - 1; jj <= j + 1; jj++)
                {
                    if (jj >= 0 && jj < width && ii >= 0 && ii < height)
                    {
                        tmp.rgbtRed = image[ii][jj].rgbtRed;
                        tmp.rgbtGreen = image[ii][jj].rgbtGreen;
                        tmp.rgbtBlue = image[ii][jj].rgbtBlue;
                    }
                    else
                    {
                        tmp.rgbtRed = 0x00;
                        tmp.rgbtGreen = 0x00;
                        tmp.rgbtBlue = 0x00;
                    }
                    grid[row_counter][col_counter].rgbtRed = tmp.rgbtRed;
                    grid[row_counter][col_counter].rgbtGreen = tmp.rgbtGreen;
                    grid[row_counter][col_counter].rgbtBlue = tmp.rgbtBlue;
                    col_counter++;
                }
                row_counter++;
            }


            // apply Gx to grid and save to Gx
            Gxsum[0] = 0;
            Gysum[0] = 0;
            Gxsum[1] = 0;
            Gysum[1] = 0;
            Gxsum[2] = 0;
            Gysum[2] = 0;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    Gxgrid[k][l][0] = round((float) grid[k][l].rgbtRed * Gx[k][l]);
                    Gygrid[k][l][0] = round((float) grid[k][l].rgbtRed * Gy[k][l]);
                    Gxgrid[k][l][1] = round((float) grid[k][l].rgbtGreen * Gx[k][l]);
                    Gygrid[k][l][1] = round((float) grid[k][l].rgbtGreen * Gy[k][l]);
                    Gxgrid[k][l][2] = round((float) grid[k][l].rgbtBlue * Gx[k][l]);
                    Gygrid[k][l][2] = round((float) grid[k][l].rgbtBlue * Gy[k][l]);
                    Gxsum[0] += Gxgrid[k][l][0];
                    Gysum[0] += Gygrid[k][l][0];
                    Gxsum[1] += Gxgrid[k][l][1];
                    Gysum[1] += Gygrid[k][l][1];
                    Gxsum[2] += Gxgrid[k][l][2];
                    Gysum[2] += Gygrid[k][l][2];
                }
            }

            output[i][j].rgbtRed = min(round(sqrt(Gxsum[0] * Gxsum[0] + Gysum[0] * Gysum[0])), 255);
            output[i][j].rgbtGreen = min(round(sqrt(Gxsum[1] * Gxsum[1] + Gysum[1] * Gysum[1])), 255);
            output[i][j].rgbtBlue = min(round(sqrt(Gxsum[2] * Gxsum[2] + Gysum[2] * Gysum[2])), 255);

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

