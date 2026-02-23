#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void printDeck(CardDeck deck);
void divide(CardDeck origDeck, CardDeck * leftDeck, CardDeck * rightDeck);
void interleave(CardDeck leftDeck, CardDeck rightDeck, CardDeck * resultArray, int * resultCount);
void helper(CardDeck leftDeck, CardDeck rightDeck, int pos, CardDeck outputDeck, CardDeck * resultArray, int* resultCount);

void shuffle(CardDeck origDeck, int round)
{
  if (round == 0)
  {
    return;
  }

  int numPairs = origDeck.size - 1;
  CardDeck * leftDeck = (CardDeck *) malloc(sizeof(CardDeck) * numPairs);
  if (leftDeck == NULL) return;
  CardDeck * rightDeck = (CardDeck *) malloc(sizeof(CardDeck) * numPairs);
  if (rightDeck == NULL) 
  {
    free(leftDeck);
    return;
  }

  divide(origDeck, leftDeck, rightDeck);

  int i;
  for (i = 0; i < numPairs; i++)
  {
    CardDeck * resultArray = (CardDeck *) malloc(sizeof(CardDeck) * 1000000);
    if (resultArray == NULL) {
      free(leftDeck);
      free(rightDeck);
      return;
    }
    int resultCount = 0;
    interleave(leftDeck[i], rightDeck[i], resultArray, &resultCount);
    int j;
    for (j = 0; j < resultCount; j++)
    {
      if (round == 1)
      {
        printDeck(resultArray[j]);
      }
      else
      {
      shuffle(resultArray[j], round - 1);
      }
    }
    free(resultArray);
  }
  free(leftDeck);
  free(rightDeck);
}

static void printDeck(CardDeck deck)
{
  int ind;
  for (ind = 0; ind < deck.size; ind ++)
  {
    printf("%c ", deck.cards[ind]);
  }
  printf("\n");
}

void divide(CardDeck origDeck, CardDeck * leftDeck, CardDeck * rightDeck)
{
  int i;
  for (i = 1; i < origDeck.size; i++)
  {
    leftDeck[i-1].size = i;
    memcpy(leftDeck[i-1].cards, origDeck.cards, leftDeck[i-1].size);

    rightDeck[i-1].size = origDeck.size - i;
    memcpy(rightDeck[i-1].cards, origDeck.cards + i, rightDeck[i-1].size);
  }
}


void interleave(CardDeck leftDeck, CardDeck rightDeck, CardDeck * resultArray, int * resultCount)
{
  int totalSize = leftDeck.size + rightDeck.size;
  int pos = 0;
  CardDeck outputDeck = {
    .size = totalSize
  };
  helper(leftDeck, rightDeck, pos, outputDeck, resultArray, resultCount);
}

void helper(CardDeck leftDeck, CardDeck rightDeck, int pos, CardDeck outputDeck, CardDeck * resultArray, int* resultCount)
{
  if (leftDeck.size == 0)
  {
    // Append the outputDeck with whatever is in the rightDeck
    memcpy(outputDeck.cards + pos, rightDeck.cards, rightDeck.size);
    // Store in an array
    resultArray[*resultCount] = outputDeck;
    (*resultCount)++;

    return;
  }

  if (rightDeck.size == 0)
  {
    // Append the outputDeck with whatever is in the rightDeck
    memcpy(outputDeck.cards + pos, leftDeck.cards, leftDeck.size);
    // Store in an array
    resultArray[*resultCount] = outputDeck;
    (*resultCount)++;

    return;
  }

  outputDeck.cards[pos] = leftDeck.cards[0];
  CardDeck newLeftDeck = {
    .size = leftDeck.size - 1
  };
  memcpy(newLeftDeck.cards, leftDeck.cards + 1, newLeftDeck.size);
  helper(newLeftDeck, rightDeck, pos + 1, outputDeck, resultArray, resultCount);

  outputDeck.cards[pos] = rightDeck.cards[0];
  CardDeck newRightDeck = {
    .size = rightDeck.size - 1
  };
  memcpy(newRightDeck.cards, rightDeck.cards + 1, newRightDeck.size);
  helper(leftDeck, newRightDeck, pos + 1, outputDeck, resultArray, resultCount);
}