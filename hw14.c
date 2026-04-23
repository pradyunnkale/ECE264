#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

/* count the occurrences in a file */

long *countLetters(FILE *fp)
{
   long *asciiCount = (long *)malloc(sizeof(long)*ASCII_SIZE);
   if (asciiCount == NULL) {
      return NULL;
   }
   int ch;
   for (ch = 0; ch < ASCII_SIZE; ch++) {
      asciiCount[ch] = 0;
   }
   fseek(fp, 0, SEEK_SET);
   while ((ch = fgetc(fp)) != EOF) {
      asciiCount[ch] += 1;
   }
   return asciiCount;
}

// You main function takes exactly four inputs
// argv[1]: input file name - for example, testcases/gophers
// argv[2]: output file 1 name - to store the sorted characters, for example, gophers_sorted
// argv[3]: output file 2 name - to store the huffman code of each characters, for example, gophers_huffman
// argv[4]: output file 3 name - to store the header information, for example, gophers_header
int main(int argc, char **argv)
{
   if (argc != 5) {
    printf("Not enough arguments");
    return EXIT_FAILURE;
   }
   FILE * inFile = fopen(argv[1], "r");
   if (inFile == NULL) {
      fprintf(stderr, "can't open the input file.  Quit.\n");
      return EXIT_FAILURE;
   }

   /* read and count the occurrences of characters */
   long *asciiCount = countLetters(inFile);
   fclose(inFile);

   if (asciiCount == NULL) {
      fprintf(stderr, "cannot allocate memory to count the characters in input file.  Quit.\n");
      return EXIT_FAILURE;
   }

   // Your code should go here
   ListNode *list = NULL;
   for (int c = 0; c < ASCII_SIZE; c++)
   {
      if (asciiCount[c] > 0)
      {
         TreeNode *leaf = buildTreeNode(c, NULL, NULL);
         if (leaf == NULL)
         {
            freeList(list);
            return EXIT_FAILURE;
         }
         leaf->count = asciiCount[c];
         if (addListNode(&list, leaf, treeNodeCompare) == NULL)
         {
            free(leaf);
            return EXIT_FAILURE;
         }
      }
   }

   free(asciiCount);

   FILE *fpSorted = fopen(argv[2], "w");
   if (fpSorted == NULL)
   {
      freeList(list);
      return EXIT_FAILURE;
   }
   printList(list, fpSorted);
   fclose(fpSorted);
   
   TreeNode *root = buildHuffmanTree(list);
   FILE *fpHuff = fopen(argv[3], "w");
   if (fpHuff == NULL)
   {
      freeHuffmanTree(root);
      return EXIT_FAILURE;
   }
   huffmanPrint(root, fpHuff);
   fclose(fpHuff); 

   FILE *fpHeader = fopen(argv[4], "wb");
   if (fpHeader == NULL)
   {
      freeHuffmanTree(root);
      return EXIT_FAILURE;
   }
   fclose(fpHeader);

   freeHuffmanTree(root);
   return EXIT_SUCCESS;
}
