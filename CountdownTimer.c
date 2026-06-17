#include <stdio.h> 
#include <stdlib.h> // for rand()
#include <string.h> // for strcpy()
#include <unistd.h> // for sleep()
#include <time.h> // for time()

#define MAX_QUESTION_LEN 200
#define MAX_OPTION_LEN 50
#define NUM_QUESTIONS 5

void countdown_timer() {
    printf("\nYou have 10 seconds to think...\n");

    // Start a countdown loop from 10 down to 1
    for(int i = 10 ; i > 0 ; i--) {

        printf("\rTime left: %d seconds ", i);

        // Flush the output buffer to ensure immediate display
        fflush(stdout);

        // Pause execution for 1 second
        sleep(1);
    }
    printf("\nTime's up!\n");
}

void initialize_and_shuffle(char questions[][MAX_QUESTION_LEN], char options[][4][MAX_OPTION_LEN], char answers[], int *order, int n) {
    strcpy(questions[0], "What is the output of: printf(\"%d\", 5 + 3 * 2);");
    strcpy(options[0][0], "A) 11");
    strcpy(options[0][1], "B) 16");
    strcpy(options[0][2], "C) 10");
    strcpy(options[0][3], "D) 13");
    answers[0] = 'A'; 

    strcpy(questions[1], "What does the '++' operator do in C?");
    strcpy(options[1][0], "A) Adds 2");
    strcpy(options[1][1], "B) Increments by 1");
    strcpy(options[1][2], "C) Multiplies by 2");
    strcpy(options[1][3], "D) Squares the value");
    answers[1] = 'B'; 

    strcpy(questions[2], "Which of these is used to make decisions in C?");
    strcpy(options[2][0], "A) if statement");
    strcpy(options[2][1], "B) switch statement");
    strcpy(options[2][2], "C) while loop");
    strcpy(options[2][3], "D) Both A and B");
    answers[2] = 'D'; 

    strcpy(questions[3], "Which function is used to compare two strings in C?");
    strcpy(options[3][0], "A) strcomp()");
    strcpy(options[3][1], "B) strcmp()");
    strcpy(options[3][2], "C) compare()");
    strcpy(options[3][3], "D) stringcomp()");
    answers[3] = 'B'; 

    strcpy(questions[4], "Which function is used to read a string from standard input?");
    strcpy(options[4][0], "A) scanf");
    strcpy(options[4][1], "B) gets");
    strcpy(options[4][2], "C) fgets");
    strcpy(options[4][3], "D) All of these");
    answers[4] = 'D';

    srand(time(NULL));
    
    for (int i = 0; i < n - 1; i++) {
        int j = i + rand() % (n - i);
        int temp = order[j];
        order[j] = order[i];
        order[i] = temp;
    }
}

void play_quiz() {
    printf("Welcome to C Programming Quiz!\n");

    char questions[NUM_QUESTIONS][MAX_QUESTION_LEN];

    char options[NUM_QUESTIONS][4][MAX_OPTION_LEN];

    char answers[NUM_QUESTIONS];
    
    int question_order[5] = {0, 1, 2, 3, 4};

    initialize_and_shuffle(questions, options, answers, question_order, 5);

    // Countdown timer of 10 seconds
    countdown_timer();
}

int main() {
    play_quiz();
    return 0;
}
