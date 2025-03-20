#ifndef __MAKE_ANAGRAM_LIST_H
#define __MAKE_ANAGRAM_LIST_H

typedef struct word_node{
    char *word;  // original word
    struct word_node *next; //next word with the same key
} word_node;

typedef struct key_node{
    char *sorted_key; //sorted key
    int count; //no of variants
    struct key_node *next; //next sorted key
    struct word_node *word_list; //list of words with matching key
} key_node;

int compare(const void *a, const void *b);
char *sorting_key(char *word);
key_node *make_anagram_list(char **words, int n);
void free_anagram_list(key_node *list);

#endif