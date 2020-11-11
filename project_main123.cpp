#include <iostream>
#include <vector>
using namespace std;

/*
A. If deepenough(1.)
	return value
B. Generate ply (2.)
C. Check if the ply is empty
	if empty (3.):
		evaluate currentState
		end
	if not empty (4.):
		transverse through list of created nodes --> currentNode
			resultSucc = minmaxab(currentNode, depth+1, opposite(player), -passThresh, -useThresh, int *lastNodeNumber) (a.)
			newValue = -resultSucc (b.)
			if (NEW-VALUE> Pass-Thresh) (c.)
				Set Pass-Thresh to NEW-VALUE.
				set best-path
			if (pass-thresh>=use-thresh)(d.)
				return the structure
					VALUE= Pass-Thresh;
					PATH= BEST-PATH;

D.	Return the structure (5.)
		VALUE = Pass-Thresh
		PATH = BEST-PATH
*/

int minimaxAB(vector<int> currentState, int depth, int currentPlayer, int useThresh, int passThresh, int evalNum);
vector<vector<int>, int> createNewState(vector<int> currentState, int player);
int opposite(int player);
int firstMinusOpp(vector<int> currentState, int player);
int cornAndMid(vector<int> currentState, int player);
int proximityEval(vector<int> currentState, int player);
int evalTie(vector<int> currentState, int player);

// only generate the nodes that would have atleast one winning line with a changed position
// return length of the game path
// return total number of nodes generated
// return total number of nodes expanded
int minimaxAB(vector<int> currentState, int depth, int currentPlayer, int useThresh, int passThresh, int evalNum) {
	int bestScore,
		resultSucc,
		lengthGamePath,
		totalNumberNodes,
		totalExpandedNodes,
		newValue;
	vector<int> newState;
	int table[4];
	vector<vector<int>, int> listStates;

	if (depth > 9) {
		if (evalNum == 1)
			return firstMinusOpp(currentState, depth);
		if (evalNum == 2)
			return cornAndMid(currentState, depth);
		if (evalNum == 3)
			return proximityEval(currentState, depth);
		if (evalNum == 4)
			return evalTie(currentState, depth);
	}


	listStates = createNewState(currentState, currentPlayer);
	if (listStates.size() == 0)
		return bestScore;
	for (int i = 0; i < listStates.size(); i++) {
		for (int x = 0; x < listStates[i].size(); x++)
			newState.push_back(listStates[i][x]);
		resultSucc = minimaxAB(newState, depth + 1, opposite(currentPlayer), -passThresh, -useThresh, evalNum);

		//b (set newState to -resultSucc)
		newValue = -resultSucc;

		//c
		if (newValue > passThresh) {
			//i
			passThresh = newValue;
			//ii
			//set bestpath to result of attching succ to front of path(result succ)
			bestScore = passThresh;
		}

		//d
		if (passThresh >= useThresh)
			return bestScore;
	}

	return bestScore;
}

int opposite(int player) {
	return -player;
}

// G(currentState, player) --> listStates
// Return a list of states that can be taken by current player
vector<vector<int>, int> createNewState(vector<int> currentState, int player) {
	vector<vector<int>, int> listStates;
	vector<int> emptyPos;
	vector<int> moveState;

	for (int i = 0; i < currentState.size(); i++) {
		if (currentState[i] == 0)
			emptyPos.push_back(i);
	}

	for (int i = 0; i < emptyPos.size(); i++) {
		moveState = currentState;
		moveState[emptyPos[i]] = player;
		listStates.push_back(moveState);
	}

	return listStates;
}

// first players winning path - opposing players winning paths
int firstMinusOpp(vector<int> currentState, int player) {
	int score = 0;
	int player1 = 0;
	int player2 = 0;


	// Check rows and colomns
	for (int i = 0; i < 3; i++) {
		//rows
		if (currentState[i * 3] != (-player) && currentState[(i * 3) + 1] != (-player) &&
			currentState[(i * 3) + 2] != (-player))
			player1++;
		//colomns
		if (currentState[i] != (-player) && currentState[i + 3] != (-player) &&
			currentState[i + 6] != (-player))
			player1++;
	}

	// Check diagonals
	for (int i = 0; i < 2; i++) {
		//rows
		if (currentState[0 + (i * 2)] != (-player) && currentState[4] != (-player) &&
			currentState[8 - (i * 2)] != (-player))
			player1++;
	}

	// Check rows and colomns
	for (int i = 0; i < 3; i++) {
		//rows 
		if (currentState[i * 3] != (player) && currentState[(i * 3) + 1] != (player) &&
			currentState[(i * 3) + 2] != (player))
			player2++;
		//colomns
		if (currentState[i] != (player) && currentState[i + 3] != (player) &&
			currentState[i + 6] != (player))
			player2++;
	}

	// Check diagonals
	for (int i = 0; i < 2; i++) {
		//rows
		if (currentState[0 + (i * 2)] != (player) && currentState[4] != (player) &&
			currentState[8 - (i * 2)] != (player))
			player2++;
	}

	return player1 - player2;
}


// Add a point for every player's piece in any of the corners or mid position.
int cornAndMid(vector<int> currentState, int player) {
	int score = 0;

	// Check rows and colomns	
	for (int i = 0; i <= 8; i = i + 2) {
		if (currentState[i] == player) {
			score++;
		}
	}

	return score;
}

// Determines the objects positined above each player.
int proximityEval(vector<int> currentState, int player) {
	int scorePlayer = 0;
	int scoreOtherPlayer = 0;

	// Checking proximity of values above each player
	for (int index = 3; index < 9; index++) {
		if (currentState[index] == player && currentState[index - 3] == player)
			scorePlayer += 2;
		else if (currentState[index] == player && currentState[index - 3] == -player)
			scorePlayer -= 1;
	}

	// Checking proximity of values above each other player
	for (int index = 3; index < 9; index++) {
		if (currentState[index] == -player && currentState[index - 3] == -player)
			scoreOtherPlayer += 2;
		else if (currentState[index] == -player && currentState[index - 3] == player)
			scoreOtherPlayer -= 1;
	}

	return(scorePlayer - scoreOtherPlayer);

}

int evalTie(vector<int> currentState, int player) {
	int score = 0;

	for (int i = 0; i < 3; i++) {
		if (currentState[i * 3] == player && currentState[(i * 3) + 1] == player && currentState[(i * 3) + 2] == (-player))
			score++;
		else if (currentState[i * 3] == (-player) && currentState[(i * 3) + 1] == player && currentState[(i * 3) + 2] == player)
			score++;
		else if (currentState[i * 3] == player && currentState[(i * 3) + 1] == (-player) && currentState[(i * 3) + 2] == player)
			score++;

		if (currentState[i] == player && currentState[i + 1] == player && currentState[i + 2] == (-player))
			score++;
		else if (currentState[i] == (-player) && currentState[i + 1] == player && currentState[i + 2] == player)
			score++;
		else if (currentState[i] == player && currentState[i + 1] == (-player) && currentState[i + 2] == player)
			score++;
	}
	return score;
}
// -1 = O
// 1 = X

// X = 1
// O = -1
int main() {
	vector<int> currentState = { 0, -1, 1, -1, 0, 0, 1, -1, 0 };

	return 0;
}
