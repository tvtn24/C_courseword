#ifndef __PLAY_H
#define __PLAY_H

typedef struct Pair{
    int i;
    int j;
} Pair;

typedef struct Royal{
    int j;
    int q;
    int k; 
} Royal;

Pair add_to_11(int *visible, int num_vis);
Royal jqk(int *visible, int num_vis);
int play(int *deck, int verbose);

#endif