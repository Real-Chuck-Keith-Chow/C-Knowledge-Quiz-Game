#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

#define MAX_Q 200
#define MAX_O 50
#define NUM_Q 5
#define COUNTDOWN 10

void countdown(void);
void load_questions(char q[][MAX_Q], char o[][4][MAX_O], char ans[]);
void shuffle(int *order, int n);
void run_quiz(void);
char get_answer(void);
void show_q(const char *q, char o[][MAX_O]);
void show_score(int score, int total);

void countdown(void)
{
printf("\nYou get %d seconds to prepare...\n", COUNTDOWN);

for (int i = COUNTDOWN; i > 0; i--) {
printf("\r⏱️  %2d seconds remaining ", i);
fflush(stdout);
sleep(1);
}
printf("\r⏱️  Time's up!    \n\n");
}

void load_questions(char q[][MAX_Q], char o[][4][MAX_O], char ans[])
{
strcpy(q[0], "What is the output of: printf(\"%d\", 5 + 3 * 2);");
strcpy(o[0][0], "A) 11");
strcpy(o[0][1], "B) 16");
strcpy(o[0][2], "C) 10");
strcpy(o[0][3], "D) 13");
ans[0] = 'A';

strcpy(q[1], "What does the '++' operator do in C?");
strcpy(o[1][0], "A) Adds 2");
strcpy(o[1][1], "B) Increments by 1");
strcpy(o[1][2], "C) Multiplies by 2");
strcpy(o[1][3], "D) Squares the value");
ans[1] = 'B';

strcpy(q[2], "Which of these is used for decisions in C?");
strcpy(o[2][0], "A) if statement");
strcpy(o[2][1], "B) switch statement");
strcpy(o[2][2], "C) while loop");
strcpy(o[2][3], "D) Both A and B");
ans[2] = 'D';

strcpy(q[3], "Which function compares two strings in C?");
strcpy(o[3][0], "A) strcomp()");
strcpy(o[3][1], "B) strcmp()");
strcpy(o[3][2], "C) compare()");
strcpy(o[3][3], "D) stringcomp()");
ans[3] = 'B';

strcpy(q[4], "Which function reads a string from standard input?");
strcpy(o[4][0], "A) scanf");
strcpy(o[4][1], "B) gets");
strcpy(o[4][2], "C) fgets");
strcpy(o[4][3], "D) All of these");
ans[4] = 'D';
}

void shuffle(int *order, int n)
{
srand(time(NULL));

for (int i = n - 1; i > 0; i--) {
int j = rand() % (i + 1);
int tmp = order[i];
order[i] = order[j];
order[j] = tmp;
}
}

void show_q(const char *q, char o[][MAX_O])
{
printf("\n%s\n", q);
for (int i = 0; i < 4; i++) {
printf("  %s\n", o[i]);
}
printf("\nYour choice: ");
}

char get_answer(void)
{
char c;

while (1) {
scanf(" %c", &c);
c = toupper(c);

if (c >= 'A' && c <= 'D') {
return c;
}

printf("Please enter A, B, C, or D: ");
while (getchar() != '\n');
}
}

void show_score(int score, int total)
{
printf("\n╔═══════════════════════════════════╗\n");
printf("║         QUIZ RESULTS              ║\n");
printf("╠═══════════════════════════════════╣\n");
printf("║  Score: %2d / %2d                    ║\n", score, total);

float pct = (score * 100.0f) / total;
printf("║  Percentage: %.1f%%                ║\n", pct);

printf("╠═══════════════════════════════════╣\n");
printf("║  ");
if (pct >= 80) {
printf("Great work! You know your C!     ║\n");
} else if (pct >= 60) {
printf("Not bad! Keep studying!          ║\n");
} else if (pct >= 40) {
printf("Review the material and try again.║\n");
} else {
printf("Don't worry, practice makes perfect!║\n");
}
printf("╚═══════════════════════════════════╝\n");
}

void run_quiz(void)
{
printf("\n═══════════════════════════════════════\n");
printf("       C PROGRAMMING QUIZ             \n");
printf("═══════════════════════════════════════\n");
printf("There are %d multiple choice questions.\n", NUM_Q);
printf("Pick the best answer for each one.\n\n");

char qs[NUM_Q][MAX_Q];
char opts[NUM_Q][4][MAX_O];
char answers[NUM_Q];
int order[NUM_Q];

for (int i = 0; i < NUM_Q; i++) {
order[i] = i;
}

load_questions(qs, opts, answers);
shuffle(order, NUM_Q);
countdown();

int score = 0;

for (int i = 0; i < NUM_Q; i++) {
int idx = order[i];

show_q(qs[idx], opts[idx]);
char user = get_answer();

if (user == answers[idx]) {
printf("✅ Correct!\n");
score++;
} else {
printf("❌ Nope. The answer was %c.\n", answers[idx]);
}
}

show_score(score, NUM_Q);
}

int main(void)
{
run_quiz();
return 0;
}
