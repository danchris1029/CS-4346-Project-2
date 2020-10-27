#include <iostream>
#include <vector>
using namespace std;

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
			resultSucc = minimaxAB(newState, depth+1, pos, opposite(player), -useThresh, -passThresh)
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

// return evalution score with heuristic function one
int evalOne(vector<int> currentState, int depth) {
	int evalScore;



	return int;
}
