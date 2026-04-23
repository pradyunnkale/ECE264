#ifndef PERSONALITY_H
#define PERSONALITY_H

#define NUM_DIMENSIONS 4
#define NUM_QUESTIONS 70

typedef struct {
    int percentages[NUM_DIMENSIONS];
    char personalityType[NUM_DIMENSIONS + 1];
} PersonalityResult;

/**
 * Return which personality dimension a question belongs to.
 *
 * The questionIndex is zero-based:
 * - 0 -> dimension 0 (E/I)
 * - 1 -> dimension 1 (S/N)
 * - 2 -> dimension 1 (S/N)
 * - 3 -> dimension 2 (T/F)
 * - 4 -> dimension 2 (T/F)
 * - 5 -> dimension 3 (J/P)
 * - 6 -> dimension 3 (J/P)
 * and then the pattern repeats every 7 questions.
 */
int getDimensionIndex(int questionIndex);

/**
 * Count A and B answers for each dimension.
 *
 * Ignore '-' answers. Treat uppercase and lowercase letters the same.
 * Arrays aCounts and bCounts each have length NUM_DIMENSIONS.
 */
void countAnswers(const char * answers,
                  int aCounts[NUM_DIMENSIONS],
                  int bCounts[NUM_DIMENSIONS]);

/**
 * Compute the rounded percentage of B answers for one dimension.
 *
 * Return -1 if there are no non-dash answers in the dimension.
 */
int computePercentageB(int aCount, int bCount);

/**
 * Determine the personality letter for one dimension.
 *
 * dimension values:
 * 0 -> E/I
 * 1 -> S/N
 * 2 -> T/F
 * 3 -> J/P
 *
 * percentageB rules:
 * - -1 => '-'
 * - < 50 => left-side letter
 * - = 50 => 'X'
 * - > 50 => right-side letter
 */
char determinePersonalityLetter(int dimension, int percentageB);

/**
 * Analyze one 70-character answer string and return all results.
 */
PersonalityResult analyzeAnswers(const char * answers);

#endif
