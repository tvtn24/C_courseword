#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "shuffle.h"
#include "play.h"

int main(int argc, char *argv[]) {
    // Create and initialize the deck
    int deck[52];
    for (int i = 0; i < 52; i++) {
        deck[i] = (i % 13) + 1;  // Fill the deck with cards
    }

    // Shuffle the deck
    int seed = atoi(argv[1]);
    shuffle(deck, 52, seed);
    
    // Play a game with output
    int cards_left = play(deck, true);
    printf("Game ended with %d cards left in the deck.\n", cards_left);
    if (cards_left == 0) {
        printf("Player wins!\n");
    } else {
        printf("Player loses.\n");
    }
    
    return 0;
}


