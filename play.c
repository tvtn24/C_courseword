// helper file for patience and pstatistics
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "shuffle.h"
#include "play.h"

Pair add_to_11(int *visible, int num_vis) {


    Pair pair;
    pair.i = -1;  // Initialise to -1 to indicate "no pair found"
    pair.j = -1;

    // Loop through the piles for pair that add to 11
    for (int i = 0; i < num_vis - 1; i++) {
        for (int j = i + 1; j < num_vis; j++) {
            if (visible[i] + visible[j] == 11) {
                // Set the value of pair to corresponding index of cards that add to 11
                pair.i = i;
                pair.j = j;
                return pair; // Return when a pair is found
            }
        }
    }

    return pair;
}

Royal jqk(int *visible, int num_vis) {

    Royal royal;
    royal.j = -1; // Initialise to -1 to indicate "no royal found"
    royal.q = -1;
    royal.k = -1;

    // Loop through the piles to find royals
    for (int i = 0; i < num_vis; i++)
    {   
        // If found assign the value corresponding piles to royal
        if (visible[i] == 11)
            royal.j = i;
        else if (visible[i] == 12)
            royal.q = i;
        else if (visible[i] == 13)
            royal.k = i;
    }

    return royal;
   
}

int play(int *deck, int verbose){
    // Initalise array of visible card, fill with 0
    int visible[9] = {0};
    int num_visible = 0;

    int deck_size = 52;
    int next_card = 0;

    // Start with first two cards from deck
    visible[num_visible++] = deck[next_card++];
    visible[num_visible++] = deck[next_card++];
    deck_size -= 2; 

    if (verbose) {
        // Print initial state
        for (int i = 0; i < num_visible; i++) {
            printf("%d ", visible[i]);
        }
        printf("\n");
    }

    // Game loop
    while (deck_size > 0 && num_visible <= 9)
    {
        // Check for pairs that sum to 11
        Pair pair = add_to_11(visible, num_visible);

        //Check for J,Q,K
        Royal royal = jqk(visible, num_visible);

        // If there a pair that sums to 11
        if(pair.i != -1 && pair.j != -1 && deck_size >=2){
            visible[pair.i] = deck[next_card++];
            visible[pair.j] = deck[next_card++];
            deck_size -= 2; 

            if (verbose) {
                for (int i = 0; i < num_visible; i++) {
                    printf("%d ", visible[i]);
                }
                printf("\n");
            }
        } 

        // If there are Jack, Queen and King
        else if(royal.j != -1 && royal.q != -1 && royal.k != -1 && deck_size >=3){
            visible[royal.j] = deck[next_card++];
            visible[royal.q] = deck[next_card++];
            visible[royal.k] = deck[next_card++];
            deck_size -= 3;

            if (verbose) {
                for (int i = 0; i < num_visible; i++) {
                    printf("%d ", visible[i]);
                }
                printf("\n");
            }
        } 
        
        // If no match
        else{
            if (num_visible < 9){
                visible[num_visible++] = deck[next_card++];
                deck_size--;
                
                if (verbose) {
                    for (int i = 0; i < num_visible; i++) {
                        printf("%d ", visible[i]);
                    }
                    printf("\n");
                }
            } else {
                break; //Have more than 9 piles then game over
            }
        }
    }
    return deck_size;
}