#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ROWS 12
#define MAX_COLS 12
#define MAX_WORD_LENGTH 100
#define MAX_TRIES 1000

typedef enum {
    HORIZONTAL,
    VERTICAL
} Direction;

typedef struct {
    int row;
    int col;
    Direction direction;
    char word[MAX_WORD_LENGTH];
} Word;

typedef struct {
    char puzzle[MAX_ROWS][MAX_COLS];
} Crossword;

void initializePuzzle(Crossword *puzzle) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            puzzle->puzzle[i][j] = ' ';
        }
    }
}

int checkIntersection(Crossword *puzzle, Word word) {
    int row = word.row;
    int col = word.col;

    if (word.direction == HORIZONTAL && (col < 0 || col + strlen(word.word) > MAX_COLS))
        return 0; // Cuvântul depășește limitele pe orizontală
    if (word.direction == VERTICAL && (row < 0 || row + strlen(word.word) > MAX_ROWS))
        return 0; // Cuvântul depășește limitele pe verticală

    for (int i = 0; i < strlen(word.word); i++) {
        if (puzzle->puzzle[row][col] != ' ' && puzzle->puzzle[row][col] != word.word[i])
            return 0; // Conflict de litere
        if (word.direction == HORIZONTAL)
            col++;
        else
            row++;
    }
    return 1; // Nu există conflict 
}

void placeWord(Crossword *puzzle, Word word) {
    int row = word.row;
    int col = word.col;
    for (int i = 0; i < strlen(word.word); i++) {
        if (puzzle->puzzle[row][col] == ' ') // Verificăm dacă poziția este liberă
            puzzle->puzzle[row][col] = word.word[i];
        if (word.direction == HORIZONTAL)
            col++;
        else
            row++;
    }
}

int main() {
    srand(time(NULL)); // generatorul de numere aleatoare
    Crossword puzzle;
    initializePuzzle(&puzzle);

    Word words[] = {
        {1, 2, HORIZONTAL, "security"},
        {4, 1, HORIZONTAL, "natural"},
        {2, 1, VERTICAL, "future"},
        {8, 10, VERTICAL, "biodiversity"},
        {2, 8, VERTICAL, "three"},
        {1, 4, VERTICAL, "farming"}
    };

    int numWords = sizeof(words) / sizeof(Word);
    for (int i = 0; i < numWords; i++) {
        Word currentWord = words[i];
        int tries = 0;
        while (!checkIntersection(&puzzle, currentWord) && tries < MAX_TRIES) {
            currentWord.row = rand() % MAX_ROWS;
            currentWord.col = rand() % MAX_COLS;
            currentWord.direction = rand() % 2 == 0 ? HORIZONTAL : VERTICAL; // Schimbă direcția aleatoriu
            tries++;
        }
        if (tries < MAX_TRIES) {
            placeWord(&puzzle, currentWord);
        } else {
            printf("Nu se poate plasa cuvântul \"%s\".\n", currentWord.word);
        }
    }

    // Afișare 
    printf("Rebus Puzzle:\n");
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("%c ", puzzle.puzzle[i][j]);
        }
        printf("\n");
    }

    return 0;
}
