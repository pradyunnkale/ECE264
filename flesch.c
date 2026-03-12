// flesch.c - Student Implementation File
// Implement the Flesch Reading Ease algorithm
//
// DO NOT modify the function signatures

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "flesch.h"

int countSentences(const char* text) {
    if (text[0] == '\0')
    {
        return 0;
    }

    int i, sentences;
    i = 0;
    sentences = 0;
    while (text[i] != '\0')
    {
        if (text[i] == '.' || text[i] == ':' || text[i] == ';' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
        i++;
    }

    if (sentences == 0)
    {
        sentences = 1;
    }

    return sentences;
}

int countWords(const char* text) {
    if (text[0] == '\0')
    {
        return 0;
    }

    int i, words;
    words = 0;
    i = 0;
    while (text[i] != '\0')
    {
        if (!(text[i] == ' ' || text[i] == '.' || text[i] == ':' || text[i] == ';' || text[i] == '?' || text[i] == '!')
            && (i == 0 || (text[i-1] == ' ' || text[i-1] == '.' || text[i-1] == ':' || text[i-1] == ';' || text[i-1] == '?' || text[i-1] == '!')))
        {
            words++;
        }
        i++;
    }

    return words;
}

int countSyllables(const char* text) {
    if (text[0] == '\0')
    {
        return 0;
    }

    int prev_vowel;
    int i, syllables;
    i = 0;
    syllables = 0;
    prev_vowel = 0;
    while (text[i] != '\0')
    {
        if (text[i] == 'a' || text[i] == 'e' || text[i] == 'i' || text[i] == 'o' || text[i] == 'u' ||
            text[i] == 'A' || text[i] == 'E' || text[i] == 'I' || text[i] == 'O' || text[i] == 'U') 
        {
            prev_vowel = 1;
        } 
        else if (prev_vowel)
        {
            syllables++;
            prev_vowel = 0;
        }
        i++;
    }
    return syllables;
}

double calculateFleschScore(TextStats stats) {
    double fleschScore;
    fleschScore = 206.835 - (1.015 * ((float) stats.words / (float) stats.sentences)) - (84.6 * (float) stats.syllables / (float) stats.words);
    return fleschScore;
}

TextStats analyzeText(const char* text) {
    TextStats stats;
    stats.sentences = countSentences(text);
    stats.words = countWords(text);
    stats.syllables = countSyllables(text);
    return stats;
}
