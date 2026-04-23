# Take Home Programming Test 2: Personality Type Analyzer

Implement the scoring logic for a simplified Myers-Briggs style personality
test.

## What to implement

Write these functions in `personality.c`:

1. `getDimensionIndex`
2. `countAnswers`
3. `computePercentageB`
4. `determinePersonalityLetter`
5. `analyzeAnswers`

Do not modify `main.c` or `personality.h`.

## Rules

Each person answers 70 questions using `A`, `a`, `B`, `b`, or `-`.

The question pattern repeats every 7 questions:

1. `E / I`
2. `S / N`
3. `S / N`
4. `T / F`
5. `T / F`
6. `J / P`
7. `J / P`

`A` means the left side: `E`, `S`, `T`, `J`

`B` means the right side: `I`, `N`, `F`, `P`

`-` means no answer and must be ignored.

For each dimension:

- compute the percentage of `B` answers
- round to the nearest integer
- if there are no non-dash answers, store `-1`

The starter file already provides `roundNearest`, so you do not need
`math.h` or `round()`.

Convert percentages to letters like this:

- `-1` -> `-`
- `< 50` -> left-side letter
- `50` -> `X`
- `> 50` -> right-side letter

Examples:

- `90 15 10 10` -> `ISTJ`
- `80 50 45 25` -> `IXTJ`
- `-1 -1 -1 0` -> `---J`

## Input

Run the program like this:

```bash
./personality inputs/input_1.txt
```

Each input file is:

```text
<number of records>
<name 1>
<70 answers for person 1>
<name 2>
<70 answers for person 2>
...
```

You may assume:

- the file format is valid
- each answer line has exactly 70 characters
- answer characters are only `A`, `a`, `B`, `b`, or `-`

## Output

Each person prints on one line, for example:

```text
                    Betty Boop:         90         15         10         10 = ISTJ
```

If a dimension has no answers, the output uses `NO ANSWERS` for that field:

```text
                No Answer Dude: NO ANSWERS NO ANSWERS NO ANSWERS NO ANSWERS = ----
```

`main.c` already handles the output format. Your job is to return the correct
percentages and personality type.

## Files

- `main.c` - test harness
- `personality.h` - type definitions and prototypes
- `personality.c` - your work
- `inputs/` - sample inputs
- `expected/` - expected outputs
- `Makefile` - build and test commands

Gradescope may use additional hidden tests.

## Build and test

```bash
make
./personality inputs/input_1.txt
make test
```

## Submission

Submit only `personality.c`.

## Grading

- File submission: 10%
- Compilation: 10%
- Output correctness: 80%
