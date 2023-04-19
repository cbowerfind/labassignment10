#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

struct Trie {
    int count;
    bool isEndOfWord;
    struct Trie* children[ALPHABET_SIZE];
};

// Function to create a new trie node
struct Trie* createNode(void) {
    struct Trie* pNode = (struct Trie*)malloc(sizeof(struct Trie));
    pNode->isEndOfWord = false;
    pNode->count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
    return pNode;
}

// Function to insert a word into the trie
void insert(struct Trie** ppTrie, char* word) {
    if (*ppTrie == NULL)
        *ppTrie = createNode();
    struct Trie* pNode = *ppTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (pNode->children[index] == NULL)
            pNode->children[index] = createNode();
        pNode = pNode->children[index];
    }
    pNode->isEndOfWord = true;
    pNode->count++;
}

// Function to search for a word in the trie
int numberOfOccurances(struct Trie* pTrie, char* word) {
    if (pTrie == NULL)
        return 0;
    struct Trie* pNode = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (pNode->children[index] == NULL)
            return 0;
        pNode = pNode->children[index];
    }
    if (pNode->isEndOfWord)
        return pNode->count;
    else
        return 0;
}

// Function to deallocate the trie
struct Trie* deallocateTrie(struct Trie* pTrie) {
    if (pTrie == NULL)
        return NULL;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    free(pTrie);
    return NULL;
}

int main(void)
{
    // Initialize the trie
    struct Trie* trie = NULL;

    // Insert words into the trie
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        insert(&trie, pWords[i]);
    }

    // Check the number of occurrences of each word
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    // Deallocate the trie
    trie = deallocateTrie(trie);

    // Check if the trie has been deallocated successfully
    if(trie != NULL)
        printf("There is an error in this program\n");
     return 0;
 }

