// DO NOT MODIFY THIS FILE
// Test harness for Take Home Programming Test 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personality.h"

#define MAX_LINE_LEN 512

static void stripNewline(char * line) {
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }
}

static void printPercentageField(int percentage) {
    if (percentage < 0) {
        printf("%11s", "NO ANSWERS");
    }
    else {
        printf("%11d", percentage);
    }
}

static void printResult(const char * name, PersonalityResult result) {
    printf("%30s:", name);
    for (int i = 0; i < NUM_DIMENSIONS; i++) {
        printPercentageField(result.percentages[i]);
    }
    printf(" = %s\n", result.personalityType);
}

int main(int argc, char * argv[]) {
    char line[MAX_LINE_LEN];
    char name[MAX_LINE_LEN];
    char answers[MAX_LINE_LEN];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s input_file\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE * inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (fgets(line, sizeof(line), inputFile) == NULL) {
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    int recordCount = atoi(line);

    for (int i = 0; i < recordCount; i++) {
        if (fgets(name, sizeof(name), inputFile) == NULL) {
            fclose(inputFile);
            return EXIT_FAILURE;
        }
        if (fgets(answers, sizeof(answers), inputFile) == NULL) {
            fclose(inputFile);
            return EXIT_FAILURE;
        }

        stripNewline(name);
        stripNewline(answers);

        PersonalityResult result = analyzeAnswers(answers);
        printResult(name, result);
    }

    fclose(inputFile);
    return EXIT_SUCCESS;
}
