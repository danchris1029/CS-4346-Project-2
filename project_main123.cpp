#include <vector>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <fstream>

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
struct statStruct {
    int bestScore = 0,
   	resultSucc = 0,
   	lengthGamePath = 0,
   	totalNumberNodes = 1,
   	totalExpandedNodes = 0,
  	newValue = 0,
    wins = 0,
    losses = 0,
    recurse = 0;
};

statStruct* minimaxAB(vector<int> currentState, int depth, int currentPlayer, int useThresh, int passThresh, int evalNum, statStruct* metrics);
vector<vector<int> > createNewState(vector<int> currentState, int player);
int opposite(int player);
int firstMinusOpp(vector<int> currentState, int player);
int cornAndMid(vector<int> currentState, int player);
int proximityEval(vector<int> currentState, int player);
int evalTie(vector<int> currentState, int player);
int getBestScores(vector<int> currentState, int currentPlayer, int evalNum);
int checkWin(vector<int> currentState);

// X = 1
// O = -1
int main() {

    /* Time function returns the time since the
        Epoch(jan 1 1970). Returned time is in seconds. */
    clock_t start, end;

		vector<int> currentState{ 1, 0, 1, -1, 1, 0, 0, -1, -1 };

	/*

1 | 0 | 1
-1 | 1  | 0
0 | -1 | -1

	*/

    statStruct* metrics = new statStruct;

    statStruct* bestValue = new statStruct;

    // Start Timer
    start = clock();

    bestValue = minimaxAB(currentState, 1, 1, 1000, -1000, 1, metrics);

    // End Timer
    end = clock();

    // Printing Metric:
    // Total length of the game path
    // Total # of nodes generated
    // Total # of nodes expanded
    // Execution Time
    // Memory Utilized
    // Winning/losing statistics
    cout << "Metrics for evaluation function E1:" << endl;
    cout << "Total Length of the Game Path: " << bestValue->lengthGamePath << endl;
    cout << "Total # of nodes: " << bestValue->totalNumberNodes << endl;
    cout << "Total Expanded nodes: " << bestValue->totalExpandedNodes << endl;
    cout << "Execution Time: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(5) << " sec " << endl;
    cout << "Winning boards encountered: " << bestValue->wins << endl;
    cout << "Losing boards encountered: " << bestValue->losses << endl;
    //cout << "Memory Utilized " << (sizeof(bestValue) + ((20 + 24  + 92 + 72 + 48) * bestValue->recurse)) * 100 << " kilobytes" << endl;

    /*

    Size of metrics struct (constant)
    Size of values passed every call to minimax (5 - integers and one vector<int>)
    Size of all other values
    (sizeof(bestValue) + 20 + 24 ) + 92 + 72 + 48

    */



/*    metrics = new statStruct;

    bestValue = minimaxAB(currentState, 1, 1, 1000, -1000, 2, metrics);
    cout << "Metrics Value E2 " << metrics->bestScore << " Best Value E2 " << bestValue->bestScore << " Total # of nodes " << metrics->totalNumberNodes << " Total Expanded nodes " << metrics->totalExpandedNodes  << endl;
    metrics = new statStruct;

    bestValue = minimaxAB(currentState, 1, 1, 1000, -1000, 3, metrics);
    cout << "Metrics Value E3 " << metrics->bestScore << " Best Value E3 " << bestValue->bestScore << " Total # of nodes " << metrics->totalNumberNodes << " Total Expanded nodes " << metrics->totalExpandedNodes  << endl;
    metrics = new statStruct;

    bestValue = minimaxAB(currentState, 1, 1, 1000, -1000, 4, metrics);
    cout << "Metrics Value E4 " << metrics->bestScore << " Best Value E4 " << bestValue->bestScore << " Total # of nodes " << metrics->totalNumberNodes << " Total Expanded nodes " << metrics->totalExpandedNodes  << endl;
*/
    delete metrics;
    //delete bestValue;

	return 0;
}

// only generate the nodes that would have atleast one winning line with a changed position
// return length of the game path
// return total number of nodes generated
// return total number of nodes expanded
// useThresh = alpha
// passThresh = beta
statStruct* minimaxAB(vector<int> currentState, int depth, int currentPlayer, int useThresh, int passThresh, int evalNum, statStruct* metrics) {
	ofstream fileOUT("filename.txt", ios::app); // open file to append
	fileOUT << "Current State & depth " << depth << endl << endl;

	for(int index = 0; index < 9; index+=3){
	    fileOUT << currentState[index] << " | " << currentState[index + 1] << " | " << currentState[index + 2] << endl;
	}

	fileOUT << endl;
	fileOUT.close();// close the file

    metrics->recurse += 1;

	vector<int> newState;
	vector<vector<int> > listStates;

    // Checks for depth requirement
	if (depth > 9) {
		metrics->bestScore = getBestScores(currentState, currentPlayer, evalNum);
		return metrics;
	}

    /// Generates a list of states and evalutes the values of those states
	listStates = createNewState(currentState, currentPlayer);
	if (listStates.size() == 0) {
        metrics->bestScore = getBestScores(currentState, currentPlayer, evalNum);
		return metrics;
	}

	/// Checks if the current state is a win for current player
	if(checkWin(currentState) == 1){
	    metrics->wins += 1;
        metrics->bestScore = getBestScores(currentState, currentPlayer, evalNum);
		return metrics;
    }
    /// Checks if the current state is a win for the opposing player
	else if(checkWin(currentState) == -1){
	    metrics->losses += 1;
        metrics->bestScore = getBestScores(currentState, currentPlayer, evalNum);
		return metrics;
    }


	metrics->totalExpandedNodes += 1;

	metrics->totalNumberNodes += listStates.size();

	for (int i = 0; i < listStates.size(); i++) {

		newState = listStates.at(i);

		metrics = minimaxAB(newState, depth + 1, opposite(currentPlayer), -passThresh, -useThresh, evalNum, metrics);

		//b
		metrics->newValue = -metrics->bestScore;

		//c
		if (metrics->newValue > passThresh) {
			//i
			passThresh = metrics->newValue;
			//ii
			//set bestpath to result of attching succ to front of path(result succ)
			metrics->bestScore = passThresh;
		}

		//d
		if (passThresh >= useThresh){
			return metrics;
		}
		metrics->lengthGamePath += 1;
	}

	return metrics;
}

// Switches the current player
int opposite(int player) {
	return -player;
}

// Calculates the best score
int getBestScores(vector<int> currentState, int currentPlayer, int evalNum){
    if (evalNum == 1)
		return firstMinusOpp(currentState, currentPlayer);
	if (evalNum == 2)
		return cornAndMid(currentState, currentPlayer);
	if (evalNum == 3)
		return proximityEval(currentState, currentPlayer);
	if (evalNum == 4)
		return evalTie(currentState, currentPlayer);
    else
        return 0;
}

// Checks if the current state is a win
int checkWin(vector<int> currentState){
    // Check if the current state is a win by rows
    for (int index = 0; index < 9; index += 3){
        if (currentState[index] == 1 && currentState[index + 1] == 1 && currentState[index + 2] == 1)
            return 1;
        if (currentState[index] == -1 && currentState[index + 1] == -1 && currentState[index + 2] == -1)
            return -1;
    }

    // Check if the current state is a win by columns
    for (int index = 0; index < 3; index++){
        if (currentState[index] == 1 && currentState[index + 3] == 1 && currentState[index + 6] == 1)
            return 1;
        if (currentState[index] == -1 && currentState[index + 3] == -1 && currentState[index + 6] == -1)
            return -1;
    }

	// Check if the current state is a win by diagnols
    for (int index = 0; index < 4; index += 2){
        if (index == 0 && currentState[index] == 1 && currentState[index + 4] == 1 && currentState[index + 8] == 1)
            return 1;
        if (index == 0 && currentState[index] == -1 && currentState[index + 4] == -1 && currentState[index + 8] == -1)
            return -1;
        if (index == 2 && currentState[index] == 1 && currentState[index + 2] == 1 && currentState[index + 4] == 1)
            return 1;
        if (index == 2 && currentState[index] == -1 && currentState[index + 2] == -1 && currentState[index + 4] == -1)
            return -1;

    }

    return 0;

}

// G(currentState, player) --> listStates
// Return a list of states that can be taken by current player
vector<vector<int> > createNewState(vector<int> currentState, int player) {
	vector<vector<int> > listStates;
	vector<int> emptyPos;
	vector<int> moveState;

	for (int i = 0; i < currentState.size(); i++) {
		if (currentState[i] == 0)
			emptyPos.push_back(i);
	}

	for (int i = 0; i < emptyPos.size(); i++) {
		moveState = currentState;
		moveState[emptyPos[i]] = opposite(player);
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
		if (currentState.at(i) == player) {
			score++;
		}
	}


	return score;
}

// Determines the objects positioned above each player.
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
