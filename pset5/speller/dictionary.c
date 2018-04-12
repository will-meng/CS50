// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

#define HASH_TABLE_SIZE 40000

// SLL node
typedef struct _node
{
    char* key;
    struct _node* next;
} node;

// number of words in dictionary
int words = 0;

// create hash table array with elements/buckets pointing to linked lists
node* hash_table[HASH_TABLE_SIZE] = { NULL };

// insert a key into a linked list
node* insert(node* head, char* key);

// find a key in a linked list
bool find(node* head, const char* key);

// string hashing function djb2
unsigned long hash(char *str);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // make lowercase copy of word
    int n = strlen(word), i = 0;
    char* copy = malloc(n + 1);
    for (; i < n; i++)
        copy[i] = tolower(word[i]);
    copy[i] = '\0';
    
    // hash word to find which linked-list bucket it should be in
    unsigned long bucket = hash(copy) % HASH_TABLE_SIZE;

    // search linked-list for word
    bool found = find(hash_table[bucket], copy);
    
    // free copy
    free(copy);
    
    return found;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // try to open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
        return false;
        
    // prepare to read words
    int index = 0;
    char* word = malloc(LENGTH + 1);
    
    // read each word in dictionary
    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        // Allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word
            word[index] = c;
            index++;
        }

        // We must have found a whole word
        else if (index > 0)
        {
            // Terminate current word
            word[index] = '\0';
            
            // hash word to find which linked-list bucket it should be added to
            unsigned long bucket = hash(word) % HASH_TABLE_SIZE;
            
            // insert word into bucket
            hash_table[bucket] = insert(hash_table[bucket], word);

            // Update counter
            words++;

            // Prepare for next word
            index = 0;
            word = malloc(LENGTH + 1);
        }
    }
    
    // Check whether there was an error
    if (ferror(file))
    {
        fclose(file);
        printf("Error reading %s.\n", dictionary);
        unload();
        return 1;
    }

    // Close text
    fclose(file);
    
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node* cur, *next;
    
    // iterate through all buckets/linked-lists of hash_table and free nodes
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        if (hash_table[i])
        {
            next = hash_table[i];
            
            do
            {
                cur = next;
                next = cur->next;
                free(cur);
            } 
            while(next);
        }
    }
    
    return true;
}

// hash function djb2 by Dan Bernstein, code taken from http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

node* insert(node* head, char* key)
{
  // create new node
  node* new_node = malloc(sizeof(node));
  
  // point node's key to already existing pointer to word
  new_node->key = key;
  
  // set next pointer
  if (head == NULL)
  {
    // this is the only node in the LL
    new_node->next = NULL;
  }
  else
  {
    // this is the new head and points to the previous head
    new_node->next = head;
  }
  
  // return pointer to new head
  return new_node;
}

bool find(node* head, const char* key)
{
    node* trav = head;
    
    while (trav)
    {
        if (strcmp(trav->key, key) == 0)
            return true;
            
        trav = trav->next;
    }
    
    return false;
}