/* Some Fun   */
/* Martin v. M. very old code ...  */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

char in[20];

// Learning
const double TERMINATION_REWARD = 1;
const double GAMMA = 0.1;
const double TOLERANCE = 1e-9;

int user(int score)
{
	int i = 0;
	while (i != 1 && i != 2) {
		printf("We are at %-2d, add 1 or 2 ? ", score);
		fgets(in, 10, stdin);
		i = atoi(in);
	};
	return(i);
}


int computer(int score)
{
	int i;
	if (score % 3 == 1)  i = 1;
	else if (score % 3 == 0)  i = 2;
	else  i = rand() % 2 + 1;
	printf("We are at %-2d Computer adds %d \n", score, i);
	return(i);
}


int computer2(int score)
{
	if (score % 3 == 1) return(1);
	if (score % 3 == 0)return(2);
	else return(rand() % 2 + 1);
}

// returns 1 or 2 - greedy policy
int valueIterationComputer(float values[42], int state) {
	// Invalid state
	bool agent_turn = state % 2 == 0;
	int score = state / 2;
	if (score < 0 | score >= 20 | !agent_turn) {
		printf("Game crashed: Invalid input state during value iteration computer's turn. State: %d\n", state);
		exit(1);
	}
	// 1 and 2 are valid moves
	if (score + 2 <= 20) {
		return (values[state + 1] > values[state + 3]) ? 1 : 2;
	}
	// Only 1 is a valid move
	else if (score + 1 <= 20) {
		return 1;
	}
	else {
		printf("Game crashed: Invalid state reached: State %d\n", state);
		exit(1);
	}
}

// Mutates array with updated values
void runValueIteration(float values[42]) {
	float old_values[42];
	float improvement = 0;

	do {
		// Store old values
		memcpy(old_values, values, 42 * sizeof(float));

		improvement = 0;
		for (int i = 0; i < 40; i++) { // Iterate over NON terminal states
			// V(s) = max_a(Rss'a + GAMMA*V(s'))
			bool agent_turn = i % 2 == 0;
			int score = i / 2;
			
			// Calculate next state
			int s_prime;
			if (agent_turn) {
				s_prime = i + ((valueIterationComputer(old_values, i) == 2) ? 3 : 1);
			}
			else {
				s_prime = i + ((computer2(score) == 2) ? 3 : 1);
			}
			// Termination states
			float rSSA = 0;
			if (s_prime == 40) {
				rSSA = +TERMINATION_REWARD;
			}
			else if (s_prime == 41) {
				rSSA = -TERMINATION_REWARD;
			}
			values[i] = rSSA + GAMMA * old_values[s_prime];

			// Evaluate
			improvement = max(abs(old_values[i] - values[i]), improvement);
		}
	} while (improvement > TOLERANCE);

}


int main(void)
{
	// states are encoded as:
	// i % 2 == 0 -> agent turn
	// i // 2 -> score

	float values[42]; // implicit init to zeroes
	runValueIteration(values); // learns values on each run
	for (int i = 0; i < 42; i++) {
		printf("% .4f ", values[i]);
	}
	printf('\n');

	srand(time(NULL));
	int i;
	printf(" Who says first 20 \n \n");
	int score = 0;
	i = 0;
	while (i != 1 && i != 2) {
		printf("Who goes first: you=1 computer=2 ? ");
		fgets(in, 10, stdin);
		i = atoi(in);
	};
	if (i == 2)score = valueIterationComputer(values, score);
	while (score <= 20) {
		score = score + user(score);
		if (score >= 20) { printf(" YOU WIN !!\n "); break; };
		score = score + valueIterationComputer(values, score);
		if (score >= 20) { printf(" I WIN !! \n "); break; };
	};
	return 0;
};

