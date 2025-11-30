/* Some Fun   */
/* Martin v. M. very old code ...  */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> 

int  score;   /* Globals */
char in[20];

const char VALUE_LIST_PATH[] = "./current_value_states.csv";
const bool LEARNING_MODE = true;

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

int valueIterationComputer(float values[21]) {

	// TODO

}

int runValueIteration() {
	// TODO
}



int main(void)
{
	FILE* values_file;
	float values[21]; // init to zeroes
	fopen_s(values_file, VALUE_LIST_PATH, 'r');

	if (LEARNING_MODE) {
		// TODO
		runValueIteration();
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
	return(0);
};

