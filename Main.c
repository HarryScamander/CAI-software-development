#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_QUESTIONS 50
#define PASS_SCORE 95
#define FILENAME "high_scores.txt"

#define GREEN "\x1B[32m"
#define RED "\x1B[31m"
#define YELLOW "\x1B[33m"
#define RESET "\x1B[0m"

void PlayGame();
void SaveHighScore(char name[], int score);
void DisplayHighScores();
void DisplayGameRules();
int GenerateQuestion();
int GetRandomNumber(int level);

int main() {
    int choice;
    srand(time(0));

    while (1) {
        printf("\n-------------------------------------\n");
        printf("        " YELLOW "Arithmetic Game CAI" RESET " \n");
        printf("-------------------------------------\n");
        printf("1. Start Game\n");
        printf("2. View High Scores\n");
        printf("3. View the Game Rules\n");
        printf("0. Exit\n");
        printf("-------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            PlayGame();
        } else if (choice == 2) {
            DisplayHighScores();
        } else if (choice == 3) {
            DisplayGameRules();
        } else if (choice == 0) {
            printf(GREEN "Goodbye!\n" RESET);
            break;
        } else {
            printf(RED "Invalid choice! Try again.\n" RESET);
        }
    }
    return 0;
}

void PlayGame() {
    char name[20];
    int score = 0, questionCount = 0, correct;

    printf("Enter your name: ");
    scanf("%s", name);

    while (questionCount < MAX_QUESTIONS) {
        correct = GenerateQuestion(questionCount +1);

        if (correct) {
            score += 2;
        }
        questionCount++;

        if (score >= PASS_SCORE) {
            printf(GREEN "\n Congratulations! You reached Level 2 (Two-Digit Numbers). \n" RESET);
            break;
        }
    }

    printf(YELLOW "\n Game Over! Final Score: %d \n" RESET, score);
    SaveHighScore(name, score);
}

int GenerateQuestion(int questionNumber) {
    int num1 = GetRandomNumber(1), num2 = GetRandomNumber(1);
    int operation = rand() % 4;
    int correctAnswer, userAnswer, attempts = 0;

    printf("\n" YELLOW "Q%d: " RESET, questionNumber);

    switch (operation) {
        case 0:
            correctAnswer = num1 + num2;
            printf("\nQ: %d + %d = ?\n", num1, num2);
            break;

        case 1:
            if (num1 < num2) {
                int temp = num1;
                num1 = num2;
                num2 = temp;
            }
            correctAnswer = num1 - num2;
            printf("\nQ: %d - %d = ?\n", num1, num2);
            break;

        case 2:
            correctAnswer = num1 * num2;
            printf("\nQ: %d * %d = ?\n", num1, num2);
            break;

        case 3:
            while (num2 == 0 || num1 % num2 != 0) {
                num1 = GetRandomNumber(1);
                num2 = GetRandomNumber(1);
            }
            correctAnswer = num1 / num2;
            printf("\nQ: %d / %d = ?\n", num1, num2);
            break;
    }

    while (attempts < 5) {
        printf("Your Answer: ");
        if (scanf("%d", &userAnswer) != 1) {
            printf(RED "Invalid input! Skipping question.\n" RESET);
            while (getchar() != '\n'); 
            return 0;
        }

        if (userAnswer == correctAnswer) {
            printf(GREEN "Correct!\n" RESET);
            return 1;
        } else {
            printf(RED "Incorrect. (%d attempts left)\n" RESET, 4 - attempts);
        }
        attempts++;
    }

    printf(RED "Out of attempts! Moving to next question.\n" RESET);
    return 0;
}

int GetRandomNumber(int level) {
    return (level == 1) ? (rand() % 9 + 1) : (rand() % 90 + 10);
}

void DisplayGameRules() {
    printf("\n" YELLOW "=== Game Rules ===\n" RESET);
    printf("1. You have 5 chances to answer each question.\n");
    printf("2. If you answer incorrectly 5 times, the question will be skipped.\n");
    printf("3. Score 95 points or above to advance to two-digit numbers.\n");
    printf("4. You can play up to 50 questions.\n");
    printf("5. Division questions only appear if the division is exact.\n\n");
}

void SaveHighScore(char name[], int score) {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf(RED "Error saving score!\n" RESET);
        return;
    }

    fprintf(file, "%s %d\n", name, score);
    fclose(file);
    printf(GREEN "High Score saved!\n" RESET);
}

void DisplayHighScores() {
    FILE *file = fopen(FILENAME, "r");
    char name[20];
    int score;

    if (file == NULL) {
        printf(RED "No high scores found.\n" RESET);
        return;
    }

    printf("\n=== " YELLOW "High Scores" RESET " ===\n");
    while (fscanf(file, "%s %d", name, &score) != EOF) {
        printf(GREEN "%s - %d points\n" RESET, name, score);
    }
    fclose(file);
}
