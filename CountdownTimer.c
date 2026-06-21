#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

#define MAX_QUESTION_LEN 200
#define MAX_OPTION_LEN 50
#define NUM_QUESTIONS 5
#define COUNTDOWN_SECONDS 10

// Function prototypes
void display_countdown(void);
void initialize_quiz_data(char questions[][MAX_QUESTION_LEN], 
                         char options[][4][MAX_OPTION_LEN], 
                         char answers[]);
void shuffle_questions(int *order, int n);
void play_quiz(void);
char get_valid_answer(void);
void display_question(const char *question, char options[][MAX_OPTION_LEN]);
void display_results(int score, int total);

void display_countdown(void) {
    printf("\nYou have %d seconds to think...\n", COUNTDOWN_SECONDS);
    
    for (int i = COUNTDOWN_SECONDS; i > 0; i--) {
        printf("\r⏱️  Time left: %2d seconds ", i);
        fflush(stdout);
        sleep(1);
    }
    printf("\r⏱️  Time's up!    \n\n");
}

void initialize_quiz_data(char questions[][MAX_QUESTION_LEN], 
                         char options[][4][MAX_OPTION_LEN], 
                         char answers[]) {
    // Question 1
    strcpy(questions[0], "What is the output of: printf(\"%d\", 5 + 3 * 2);");
    strcpy(options[0][0], "A) 11");
    strcpy(options[0][1], "B) 16");
    strcpy(options[0][2], "C) 10");
    strcpy(options[0][3], "D) 13");
    answers[0] = 'A';
    
    // Question 2
    strcpy(questions[1], "What does the '++' operator do in C?");
    strcpy(options[1][0], "A) Adds 2");
    strcpy(options[1][1], "B) Increments by 1");
    strcpy(options[1][2], "C) Multiplies by 2");
    strcpy(options[1][3], "D) Squares the value");
    answers[1] = 'B';
    
    // Question 3
    strcpy(questions[2], "Which of these is used to make decisions in C?");
    strcpy(options[2][0], "A) if statement");
    strcpy(options[2][1], "B) switch statement");
    strcpy(options[2][2], "C) while loop");
    strcpy(options[2][3], "D) Both A and B");
    answers[2] = 'D';
    
    // Question 4
    strcpy(questions[3], "Which function is used to compare two strings in C?");
    strcpy(options[3][0], "A) strcomp()");
    strcpy(options[3][1], "B) strcmp()");
    strcpy(options[3][2], "C) compare()");
    strcpy(options[3][3], "D) stringcomp()");
    answers[3] = 'B';
    
    // Question 5
    strcpy(questions[4], "Which function is used to read a string from standard input?");
    strcpy(options[4][0], "A) scanf");
    strcpy(options[4][1], "B) gets");
    strcpy(options[4][2], "C) fgets");
    strcpy(options[4][3], "D) All of these");
    answers[4] = 'D';
}

void shuffle_questions(int *order, int n) {
    srand((unsigned int)time(NULL));
    
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = order[i];
        order[i] = order[j];
        order[j] = temp;
    }
}

void display_question(const char *question, char options[][MAX_OPTION_LEN]) {
    printf("\n%s\n", question);
    for (int i = 0; i < 4; i++) {
        printf("  %s\n", options[i]);
    }
    printf("\nYour answer: ");
}

char get_valid_answer(void) {
    char answer;
    int valid = 0;
    
    while (!valid) {
        scanf(" %c", &answer);
        answer = toupper(answer);
        
        if (answer >= 'A' && answer <= 'D') {
            valid = 1;
        } else {
            printf("Invalid input. Please enter A, B, C, or D: ");
            // Clear input buffer
            while (getchar() != '\n');
        }
    }
    return answer;
}

void display_results(int score, int total) {
    printf("\n╔═══════════════════════════════════╗\n");
    printf("║         QUIZ RESULTS              ║\n");
    printf("╠═══════════════════════════════════╣\n");
    printf("║  Your Score: %2d / %2d                ║\n", score, total);
    
    float percentage = (score * 100.0f) / total;
    printf("║  Percentage: %.1f%%                ║\n", percentage);
    
    // Feedback based on performance
    printf("╠═══════════════════════════════════╣\n");
    printf("║  ");
    if (percentage >= 80) {
        printf("Excellent! You're a C pro!    ║\n");
    } else if (percentage >= 60) {
        printf("Good job! Keep practicing!     ║\n");
    } else if (percentage >= 40) {
        printf("Review the basics and try again!║\n");
    } else {
        printf("Don't give up! Practice more!   ║\n");
    }
    printf("╚═══════════════════════════════════╝\n");
}

void play_quiz(void) {
    printf("\n═══════════════════════════════════════\n");
    printf("    WELCOME TO C PROGRAMMING QUIZ    \n");
    printf("═══════════════════════════════════════\n");
    printf("You will be asked %d multiple-choice questions.\n", NUM_QUESTIONS);
    printf("Choose the best answer for each.\n\n");
    
    char questions[NUM_QUESTIONS][MAX_QUESTION_LEN];
    char options[NUM_QUESTIONS][4][MAX_OPTION_LEN];
    char answers[NUM_QUESTIONS];
    int question_order[NUM_QUESTIONS];
    
    // Initialize question order
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        question_order[i] = i;
    }
    
    // Initialize quiz data
    initialize_quiz_data(questions, options, answers);
    
    // Shuffle questions
    shuffle_questions(question_order, NUM_QUESTIONS);
    
    // Display countdown
    display_countdown();
    
    // Start quiz
    int score = 0;
    char user_answer;
    
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        int q_index = question_order[i];
        
        display_question(questions[q_index], options[q_index]);
        user_answer = get_valid_answer();
        
        if (user_answer == answers[q_index]) {
            printf("✅ Correct!\n");
            score++;
        } else {
            printf("❌ Incorrect. The correct answer was %c.\n", answers[q_index]);
        }
    }
    
    // Display final results
    display_results(score, NUM_QUESTIONS);
}

int main(void) {
    play_quiz();
    return 0;
}
