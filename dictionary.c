// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

node *n;

// Number of buckets in hash table
const unsigned int N = 6000;

// Hash table
node *table[N];
int count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int index = hash(word); // TODO
    node *cursor = table[index];
    while ((cursor) != NULL) {
        if (strcasecmp(word, cursor->word) == 0) {
            return true;
        }
    cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int multiple = 0;
    int char0 = word[0];
    if (64 < char0 && char0 < 91) {
        char0 = char0 + 32;
    }

    if (isalpha(word[1]) == 0) {
        multiple = (char0 * char0);
    }
    else {
        int char1 = word[1];
            if (64 < char1 && char1 < 91) {
                char1 = char1 + 32;
            }
        multiple = (char0 * char1);
    }
    return (multiple - 9408); // TODO
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r"); // TODO
    char buffer[LENGTH+1];
    if (dict == NULL) {
        unload();
        return false;
    }
    while (fscanf(dict, "%s", buffer) != EOF) {
      count++;
      int wordIndex = hash(buffer);
            node *x = malloc(sizeof(node));
                  if (x == NULL) {
                      return false;
                    }
        strcpy(x->word, buffer);
        x->next = table[wordIndex];
        table[wordIndex] = x;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (!*load) { // TODO
    return 1;
    }
    else {
        return count;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for (int i = 0; i < N+1; i++) { // TODO
        node *cursor = table[i];
        while (cursor != NULL) {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        free(cursor);
    }
    return true;
}
