#include <stdio.h>
#include <stdlib.h>
#include "play.h"
#include "shuffle.h"
#include "histogram.h"

int *many_plays(int N) {
    // Initialise an array to store card left after every game
    int *remaining = (int *)malloc(53 * sizeof(int));
    if (remaining == NULL) {
        printf("Malloc failed\n");
        exit(0);
    }

    // fill array with 0
    for(int i = 0; i < 53; i++){
        remaining[i] = 0;
    }

    if (remaining == NULL) {
        printf("Malloc failed\n");
        exit(0);
    }
    
    // Set the first seed to -1 and 0 for the remaining game
    int seed = -1;
    for (int i = 0; i < N; i++) {
        int deck[52];
        for (int j = 0; j < 52; j++) {
            deck[j] = (j % 13) + 1;
        }
        shuffle(deck, 52, seed);
        seed = 0;
        
        int game_result = play(deck, 0);
        remaining[game_result]++;
    }

    return remaining;
}

int main() {
    int N = 10000; 
    printf("Playing %d games of patience...\n", N);
    
    int *results = many_plays(N);
    
    // Calculate percentage of winning games
    double win_probability = (double)results[0] / N * 100.0;
    printf("Probability of winning: %.2f%%\n", win_probability);
    
    // Create data for histogram
    int x[53];
    double y[53];
    
    for (int i = 0; i < 53; i++) {
        x[i] = i;
        y[i] = (double)results[i] / N * 100.0;
    }
    
    // Print histogram
    printf("\nHistogram of cards remaining at end of game:\n");
    printf("Cards  Distribution (%%)\n");
    histogram(x, y, 53, 50);
    
    free(results);
}