/* Some Fun   */
/* Martin v. M. very old code ...  */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 

int  score;   /* Globals */
char in[20];

const char VALUE_LIST_PATH[] = "./current_value_states.csv";

// Learning
const bool LEARNING_MODE = true;
const double REWARD_DISCOUNT = 0.1;

int user(void)
{
	int i = 0;
	while (i != 1 && i != 2) {
		printf("We are at %-2d, add 1 or 2 ? ", score);
		fgets(in, 10, stdin);
		i = atoi(in);
	};
	return(i);
}


int computer(void)
{
	int i;
	if (score % 3 == 1)  i = 1;
	else if (score % 3 == 0)  i = 2;
	else  i = rand() % 2 + 1;
	printf("We are at %-2d Computer adds %d \n", score, i);
	return(i);
}


int computer2(void)
{
	if (score % 3 == 1) return(1);
	if (score % 3 == 0)return(2);
	else return(rand() % 2 + 1);
}

// returns 1 or 2 - greedy policy
int valueIterationComputer(float values[21], int current_state) {
	// Invalid state
	if (current_state < 0 | current_state >= 20) {
		printf("Program crashed: Invalid input state during computer's turn.");
		exit(1);
	}
	// 1 and 2 are valid moves
	if (current_state + 2 <= 20) {
		return (values[current_state + 1] > values[current_state + 2]) ? 1 : 2;
	}
	// Only 1 is a valid move
	else if (current_state + 1 <= 20) {
		return 1;
	}
	else {
		printf("Game crashed: Invalid state reached: State %d", current_state);
		exit(1);
	}
}

void runValueIteration(float values[21]) {
	// V(s) = max_a(Rss'a + GAMMA*V(s'))
}


int main(void)
{
	FILE* values_file;
	float values[21]; // init to zeroes
	fopen_s(values_file, VALUE_LIST_PATH, 'r');

	if (LEARNING_MODE) {
		// TODO
		runValueIteration(values_file);
		return 0;
	}
	srand(time(NULL));
	int i;
	printf(" Who says first 20 \n \n");
	score = 0;
	i = 0;
	while (i != 1 && i != 2) {
		printf("Who goes first: you=1 computer=2 ? ");
		fgets(in, 10, stdin);
		i = atoi(in);
	};
	if (i == 2)score = computer();
	while (score <= 20) {
		score = score + user();
		if (score >= 20) { printf(" YOU WIN !!\n "); break; };
		score = score + computer();
		if (score >= 20) { printf(" I WIN !! \n "); break; };
	};
	close(values_file);
	return 0;
};

