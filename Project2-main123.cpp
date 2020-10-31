#include <iostream>
#include <vector>
using namespace std;

int main() {

	vector<int> currentState = { 0, 2, 1, 1, 0, 0, 1, 2, 0 };

	return 0;
}

// only generate the nodes that would have atleast one winning line with a changed position
// return best score
int minimaxAB(vector<int> currentState, int depth, int player, int useThresh, int passThresh) {
	int bestScore;
	int resultSucc;
	vector<int> newState;
	if (depth > 3)
		return evalOne(currentState, depth);

	for (int i = 0; i < 3; i++) {
		newState = createNewState(currentState);
		if (newState) {
			resultSucc = minimaxAB(newState, depth + 1, pos, opposite(player), -useThresh, -passThresh)
				// finish b, c, and d
		}
	}

	return bestScore;
}

int opposite(int player) {
	if (player)
		return 0;
	else
		return 1;
}

// create the next state in a game from a previous state
vector<int> createNewState(vector<int> currentState) {
	vector<int> newState;

	return newState;
}


// currentState will have 9 values that make up the tic-tac-toe table starting from left to right, 
// and then we move to the next row for every 3 positions
// return evalution score with heuristic function one
int evalOne(vector<int> currentState, int depth) {
	int evalScore;



	return int;
}

