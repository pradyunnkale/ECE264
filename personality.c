// personality.c - Student implementation file
// Implement the personality scoring logic described in the README.

#include <ctype.h>
#include "personality.h"

static int roundNearest(double value) {
  return (int) (value + 0.5);
}

int getDimensionIndex(int questionIndex) {
  // TODO: Implement this function
  if (questionIndex % 7 == 0)
  {
    return 0;    
  } 
  else if (questionIndex % 7 == 1 || questionIndex % 7 == 2)
  {
    return 1;
  }
  else if (questionIndex % 7 == 3 || questionIndex % 7 == 4)
  {
    return 2;
  }
  else 
  {
    return 3;
  }
}

void countAnswers(const char * answers, int aCounts[NUM_DIMENSIONS], int bCounts[NUM_DIMENSIONS]) {
  // TODO: Implement this function
  int i = 0;
  while (answers[i] != '\0')
  {
    if (answers[i] == 'a' || answers[i] == 'A')
    {
      aCounts[getDimensionIndex(i)] += 1;
    }
    else if (answers[i] == 'b' || answers[i] == 'B')
    {
      bCounts[getDimensionIndex(i)] += 1;
    }
    i++;
  }
}

int computePercentageB(int aCount, int bCount) {
  if (aCount + bCount == 0)
  {
    return -1;
  } 
  else 
  {
    double percent = 100.0 * ((double)bCount / (double)(aCount + bCount)); 
    return roundNearest(percent);
  }
}

char determinePersonalityLetter(int dimension, int percentageB) {
  char leftLetters[NUM_DIMENSIONS] = {'E', 'S', 'T', 'J'};
  char rightLetters[NUM_DIMENSIONS] = {'I', 'N', 'F', 'P'};

  if (percentageB == -1)
  {
    return '-';
  }
  if (percentageB == 50)
  {
    return 'X';
  }

  return (percentageB < 50) ? leftLetters[dimension] : rightLetters[dimension];
}

PersonalityResult analyzeAnswers(const char * answers) {
  PersonalityResult result;

  // TODO: Implement this function
  int aCount[NUM_DIMENSIONS] = {0};
  int bCount[NUM_DIMENSIONS] = {0};
  countAnswers(answers, aCount, bCount);
  for (int i = 0; i < NUM_DIMENSIONS; i++) {
    result.percentages[i] = computePercentageB(aCount[i], bCount[i]);
    result.personalityType[i] = determinePersonalityLetter(i, result.percentages[i]);
  }

  return result;
}
