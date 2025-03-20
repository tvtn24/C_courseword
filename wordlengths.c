#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "histogram.h"

// Function prototypes
void histogram(int *x, double *y, int n, int width);
int *histogram_lengths(char **strings, int n);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Could not open file %s\n", argv[1]);
        return 1;
    }

    // Initialise array for strings
    char **strings = NULL;
    int count = 0;
    int capacity = 10;
    char *line = NULL;

    // Allocate initial capacity for strings
    strings = (char **)malloc(capacity * sizeof(char *));
    if (strings == NULL) {
        printf("Malloc failed\n");
        fclose(file);
        return 1;
    }

    // Read the file line by line
    while (fscanf(file, "%s", line) == -1) {
        // Remove the newline character at the end of each line
        line[strcspn(line, "\n")] = '\0';

        // Resize the array
        if (count >= capacity) {
            capacity *= 2;
            char **new_strings = (char **)realloc(strings, capacity * sizeof(char *));

            if (new_strings == NULL) {
                printf("Malloc failed\n");
                fclose(file);
                
                // Free already allocated memory
                for (int i = 0; i < count; i++) {
                    free(strings[i]);
                }
                free(strings);

                return 1;
            }
            strings = new_strings;
        } 

        strings[count] = strdup(line);  // Duplicate the line into the array
        count++;
    }

    fclose(file);

    // Compute word length frequencies
    int *H = histogram_lengths(strings, count);
    if (H == NULL) {
        return 1;
    }

    // Find max length to determine how many bins to show
    int max_len = 0;
    for (int i = 1; i <= count; i++) {
        if (H[i] > 0) {
            max_len = i;
        }
    }

    // Prepare data for histogram
    int *x = (int *)malloc(max_len * sizeof(int));
    double *y = (double *)malloc(max_len * sizeof(double));

    if (x == NULL || y == NULL) {
        printf("Malloc failed\n");
        free(H);
        return 1;
    }

    for (int i = 1; i <= max_len; i++) {
        x[i - 1] = i;  // Word length
        y[i - 1] = (H[i] / (double)count) * 100.0;  // Percentage
    }

    // Print histogram
    histogram(x, y, max_len, 30);

    // Print the date and time of execution
    time_t t = time(NULL);
    printf("\nProgram run at: %s", ctime(&t));

    // Free allocated memory
    free(H);
    free(x);
    free(y);
    for (int i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}
