#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "histogram.h"

void histogram(int *x, double *y, int n, int width)
{
    double max_y = find_max(y, n); // find the biggest value in array

    for (int i = 0; i < n; i++)
    {
        // compute the stars for each element in array y
        int stars = (int)round(width * (y[i] / max_y));
        printf("%d ", x[i]);

        // second loop to print stars
        for (int j = 0; j < width; j++)
        {
            if (j < stars)
            {
                printf("*");
            }
            else
            {
                printf(" "); // print padding for align visual
            }
        }
        printf("   %.1f\n", y[i]);
    }
}

int find_max(double *y, int n)
{
    double max = y[0]; // set max value to first element

    for (int i = 0; i < n; i++)
    {
        if (y[i] > max) // compare and replace max value if current element is higher
            max = y[i];
    }

    return max;
}

int *histogram_lengths(char **strings, int n)
{
    // find longest words
    int max_len = max_length(strings, n);

    // initiate H array with max_len size
    int *H = (int *)malloc((max_len + 1) * sizeof(int));
    for (int i = 0; i < max_len + 1; i++)
    {
        H[i] = 0;
    }

    if (H == NULL)
    {
        printf("Malloc failed\n");
        exit(1);
    }

    // count words length and increase the corresponding index in H
    for (int i = 0; i < n; i++)
    {
        int len = strlen(strings[i]);
        H[len]++;
    }

    // Print elements of H
    for (int i = 1; i <= max_len; i++)
        printf("Length %d: %d words\n", i, H[i]);

    return H;
}

// find the words with longest length in array
int max_length(char **strings, int n)
{
    int max_length = 0;

    for (int i = 0; i < n; i++)
    {
        int len = strlen(strings[i]);
        // compare and replace max value if current word is longer
        if (len > max_length)
            max_length = len;
    }

    return max_length;
}
