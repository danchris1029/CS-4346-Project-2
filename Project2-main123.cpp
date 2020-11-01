#include <iostream>
#include <vector>
using namespace std;

// X = 1
// O = -1
int main() {
	vector<int> currentState = { 0, -1, 1, -1, 0, 0, 1, -1, 0 };

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

int evalOne(vector<int> currentState, int player){
	int score = 0;
	int player1 = 0;
	int player2 = 0;
	
	
	// Check rows and colomns
	for(int i = 0; i < 3; i++){
		//rows
		if(currentState[i*3] != (-player) && currentState[(i*3)+1] != (-player)
			currentState[(i*3)+2] != (-player))
			player1++;
		//colomns
		if(currentState[i] != (-player) && currentState[i+3] != (-player)
			currentState[i+6] != (-player))
			player1++;
	}
	
	// Check diagonals
	for(int i = 0; i < 2; i++){
		//rows
		if(currentState[0+(i*2)] != (-player) && currentState[4] != (-player)
			currentState[8-(i*2)] != (-player))
			player1++;
	}
	
	// Check rows and colomns
	for(int i = 0; i < 3; i++){
		//rows 
		if(currentState[i*3] != (player) && currentState[(i*3)+1] != (player)
			currentState[(i*3)+2] != (player))
			player2++;
		//colomns
		if(currentState[i] != (player) && currentState[i+3] != (player)
			currentState[i+6] != (player))
			player2++;
	}
	
	// Check diagonals
	for(int i = 0; i < 2; i++){
		//rows
		if(currentState[0+(i*2)] != (player) && currentState[4] != (player)
			currentState[8-(i*2)] != (player))
			player2++;
	}
	
	return player1 - player2;
}


// currentState will have 9 values that make up the tic-tac-toe table starting from left to right, 
// and then we move to the next row for every 3 positions
// return evalution score with heuristic function one
int cornAndMid(vector<int> currentState, int player){
	int score = 0;

	// Check rows and colomns	
	for(int i = 0; i <= 8; i = i + 2){
		if(currentState[i] == player){
			score++;
		}
	}

	return score;
}
