#include <vector>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

struct statStruct {
	int bestScore = 0,
		resultSucc = 0,
		totalNumberNodes = 1,
		totalExpandedNodes = 0,
		highestDepth = 0,
		newValue = 0,
		wins = 0,
		losses = 0,
		recurse = 0,
		bestScoreDepth = 0,
		value = 0;
	bool firstTerminalNode = false;
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

	clock_t start, end;
	vector<int> currentState{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	statStruct* metrics = new statStruct;

	statStruct* bestValue = new statStruct;

	cout << endl << "************** MAX(EV1) VS MIN(EV2) **************" << endl << endl;

	ofstream fileOUT;
	fileOUT.open("generatedNodes.txt"); // open file to write
	fileOUT << "************** MAX(EV1) VS MIN(EV2) **************" << endl << endl;
	fileOUT << "#### MAX(EV1) ####" << endl << endl;
	fileOUT.close();

	start = clock(); // Start Timer
	bestValue = minimaxAB(currentState, 1, 1, 1000, -1000, 1, metrics);
	end = clock(); // End Timer

	// Printing Metric:
	// Total length of the game path
	// Total # of nodes generated
	// Total # of nodes expanded
	// Execution Time
	// Memory Utilized
	// Winning/losing statistics
	cout << "Metrics for evaluation function Max EV1:" << endl;
	cout << "Total Length of the Game Path: " << bestValue->highestDepth << endl;
	cout << "Total # of nodes: " << bestValue->totalNumberNodes << endl;
	cout << "Total Expanded nodes: " << bestValue->totalExpandedNodes << endl;
	cout << "Execution Time: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(5) << " sec " << endl;
	cout << "Winning boards encountered: " << bestValue->wins << endl;
	cout << "Losing boards encountered: " << bestValue->losses << endl << endl << "VS" << endl << endl;

	metrics = new statStruct;
	bestValue = new statStruct;

	fileOUT.open("generatedNodes.txt", ios::app);
	fileOUT << "#### MIN(EV2) ####" << endl << endl;


	start = clock();
	bestValue = minimaxAB(currentState, 1, -1, 1000, -1000, 2, metrics);
	end = clock();

	cout << "Metrics for evaluation function Min EV2:" << endl;
	cout << "Total Length of the Game Path: " << bestValue->highestDepth << endl;
	cout << "Total # of nodes: " << bestValue->totalNumberNodes << endl;
	cout << "Total Expanded nodes: " << bestValue->totalExpandedNodes << endl;
	cout << "Execution Time: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(5) << " sec " << endl;
	cout << "Winning boards encountered: " << bestValue->wins << endl;
	cout << "Losing boards encountered: " << bestValue->losses << endl;

	cout << endl << "************** MAX(EV1) VS MIN(EV3) **************" << endl << endl;

	fileOUT << "************** MAX(EV1) VS MIN(EV3) **************" << endl << endl;

	fileOUT << "#### MAX(EV1) ####" << endl << endl;

	metrics = new statStruct;
	bestValue = new statStruct;

	start = clock();
	bestValue = minimaxAB(currentState, 1, 1, 1000, -1000, 1, metrics);
	end = clock();

	cout << "Metrics for evaluation function Max EV1:" << endl;
	cout << "Total Length of the Game Path: " << bestValue->highestDepth << endl;
	cout << "Total # of nodes: " << bestValue->totalNumberNodes << endl;
	cout << "Total Expanded nodes: " << bestValue->totalExpandedNodes << endl;
	cout << "Execution Time: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(5) << " sec " << endl;
	cout << "Winning boards encountered: " << bestValue->wins << endl;
	cout << "Losing boards encountered: " << bestValue->losses << endl << endl << "VS" << endl << endl;

	metrics = new statStruct;
	bestValue = new statStruct;

	fileOUT << "#### MIN(EV3) ####" << endl << endl;

	start = clock();
	bestValue = minimaxAB(currentState, 1, -1, 1000, -1000, 3, metrics);
	end = clock();

	cout << "Metrics for evaluation function Min EV3:" << endl;
	cout << "Total Length of the Game Path: " << bestValue->highestDepth << endl;
	cout << "Total # of nodes: " << bestValue->totalNumberNodes << endl;
	cout << "Total Expanded nodes: " << bestValue->totalExpandedNodes << endl;
	cout << "Execution Time: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(5) << " sec " << endl;
	cout << "Winning boards encountered: " << bestValue->wins << endl;
	cout << "Losing boards encountered: " << bestValue->losses << endl;

	cout << endl << "************** MAX(EV1) VS MIN(EV4) **************" << endl << endl;

	fileOUT << "************** MAX(EV1) VS MIN(EV4) **************" << endl << endl;

	fileOUT << "#### MAX(EV1) ####" << endl << endl;

	metrics = new statStruct;
	bestValue = new statStruct;

	start = clock();
	bestValue = minimaxAB(currentState, 1, 1, 1000, -1000, 1, metrics);
	end = clock();

	cout << "Metrics for evaluation function Max EV1:" << endl;
	cout << "Total Length of the Game Path: " << bestValue->highestDepth << endl;
	cout << "Total # of nodes: " << bestValue->totalNumberNodes << endl;
	cout << "Total Expanded nodes: " << bestValue->totalExpandedNodes << endl;
	cout << "Execution Time: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(5) << " sec " << endl;
	cout << "Winning boards encountered: " << bestValue->wins << endl;
	cout << "Losing boards encountered: " << bestValue->losses << endl << endl << "VS" << endl << endl;

	metrics = new statStruct;
	bestValue = new statStruct;

	fileOUT << "#### MIN(EV4) ####" << endl << endl;

	start = clock();
	bestValue = minimaxAB(currentState, 1, -1, 1000, -1000, 4, metrics);
	end = clock();

	cout << "Metrics for evaluation function Min EV4:" << endl;
	cout << "Total Length of the Game Path: " << bestValue->highestDepth << endl;
	cout << "Total # of nodes: " << bestValue->totalNumberNodes << endl;
	cout << "Total Expanded nodes: " << bestValue->totalExpandedNodes << endl;
	cout << "Execution Time: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(5) << " sec " << endl;
	cout << "Winning boards encountered: " << bestValue->wins << endl;
	cout << "Losing boards encountered: " << bestValue->losses << endl;

	cout << endl << "************** MAX(EV2) VS MIN(EV3) **************" << endl << endl;

	fileOUT << "************** MAX(EV2) VS MIN(EV3) **************" << endl << endl;

	fileOUT << "#### MAX(EV2) ####" << endl << endl;

	metrics = new statStruct;
	bestValue = new statStruct;

	start = clock();
	bestValue = minimaxAB(currentState, 1, 1, 1000, -1000, 2, metrics);
	end = clock();

	cout << "Metrics for evaluation function Max EV2:" << endl;
	cout << "Total Length of the Game Path: " << bestValue->highestDepth << endl;
	cout << "Total # of nodes: " << bestValue->totalNumberNodes << endl;
	cout << "Total Expanded nodes: " << bestValue->totalExpandedNodes << endl;
	cout << "Execution Time: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(5) << " sec " << endl;
	cout << "Winning boards encountered: " << bestValue->wins << endl;
	cout << "Losing boards encountered: " << bestValue->losses << endl << endl << "VS" << endl << endl;

	metrics = new statStruct;
	bestValue = new statStruct;

	fileOUT << "#### MIN(EV3) ####" << endl << endl;

	start = clock();
	bestValue = minimaxAB(currentState, 1, -1, 1000, -1000, 3, metrics);
	end = clock();

	cout << "Metrics for evaluation function Min EV3:" << endl;
	cout << "Total Length of the Game Path: " << bestValue->highestDepth << endl;
	cout << "Total # of nodes: " << bestValue->totalNumberNodes << endl;
	cout << "Total Expanded nodes: " << bestValue->totalExpandedNodes << endl;
	cout << "Execution Time: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(5) << " sec " << endl;
	cout << "Winning boards encountered: " << bestValue->wins << endl;
	cout << "Losing boards encountered: " << bestValue->losses << endl;

	cout << endl << "************** MAX(EV2) VS MIN(EV4) **************" << endl << endl;

	fileOUT << "************** MAX(EV2) VS MIN(EV4) **************" << endl << endl;

	fileOUT << "#### MAX(EV2) ####" << endl << endl;

	metrics = new statStruct;
	bestValue = new statStruct;

	start = clock();
	bestValue = minimaxAB(currentState, 1, 1, 1000, -1000, 2, metrics);
	end = clock();

	cout << "Metrics for evaluation function Max EV2:" << endl;
	cout << "Total Length of the Game Path: " << bestValue->highestDepth << endl;
	cout << "Total # of nodes: " << bestValue->totalNumberNodes << endl;
	cout << "Total Expanded nodes: " << bestValue->totalExpandedNodes << endl;
	cout << "Execution Time: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(5) << " sec " << endl;
	cout << "Winning boards encountered: " << bestValue->wins << endl;
	cout << "Losing boards encountered: " << bestValue->losses << endl << endl << "VS" << endl << endl;


	metrics = new statStruct;
	bestValue = new statStruct;

	fileOUT << "#### MIN(EV4) ####" << endl << endl;

	start = clock();
	bestValue = minimaxAB(currentState, 1, -1, 1000, -1000, 4, metrics);
	end = clock();

	cout << "Metrics for evaluation function Min EV4:" << endl;
	cout << "Total Length of the Game Path: " << bestValue->highestDepth << endl;
	cout << "Total # of nodes: " << bestValue->totalNumberNodes << endl;
	cout << "Total Expanded nodes: " << bestValue->totalExpandedNodes << endl;
	cout << "Execution Time: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(5) << " sec " << endl;
	cout << "Winning boards encountered: " << bestValue->wins << endl;
	cout << "Losing boards encountered: " << bestValue->losses << endl;

	cout << endl << "************** MAX(EV3) VS MIN(EV4) **************" << endl << endl;

	fileOUT << "************** MAX(EV3) VS MIN(EV4) **************" << endl << endl;

	fileOUT << "#### MAX(EV3) ####" << endl << endl;

	metrics = new statStruct;
	bestValue = new statStruct;

	start = clock();
	bestValue = minimaxAB(currentState, 1, 1, 1000, -1000, 3, metrics);
	end = clock();

	cout << "Metrics for evaluation function Max EV3:" << endl;
	cout << "Total Length of the Game Path: " << bestValue->highestDepth << endl;
	cout << "Total # of nodes: " << bestValue->totalNumberNodes << endl;
	cout << "Total Expanded nodes: " << bestValue->totalExpandedNodes << endl;
	cout << "Execution Time: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(5) << " sec " << endl;
	cout << "Winning boards encountered: " << bestValue->wins << endl;
	cout << "Losing boards encountered: " << bestValue->losses << endl << endl << "VS" << endl << endl;

	metrics = new statStruct;
	bestValue = new statStruct;

	fileOUT << "#### MIN(EV4) ####" << endl << endl;

	start = clock();
	bestValue = minimaxAB(currentState, 1, -1, 1000, -1000, 4, metrics);
	end = clock();

	cout << "Metrics for evaluation function Min EV4:" << endl;
	cout << "Total Length of the Game Path: " << bestValue->highestDepth << endl;
	cout << "Total # of nodes: " << bestValue->totalNumberNodes << endl;
	cout << "Total Expanded nodes: " << bestValue->totalExpandedNodes << endl;
	cout << "Execution Time: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(5) << " sec " << endl;
	cout << "Winning boards encountered: " << bestValue->wins << endl;
	cout << "Losing boards encountered: " << bestValue->losses << endl;

	fileOUT.close();// close the file

	delete metrics;

	return 0;
}

// only generate the nodes that would have atleast one winning line with a changed position
// return length of the game path
// return total number of nodes generated
// return total number of nodes expanded
// useThresh = alpha
// passThresh = beta
statStruct* minimaxAB(vector<int> currentState, int depth, int currentPlayer, int useThresh, int passThresh, int evalNum, statStruct* metrics) {
	ofstream fileOUT("generatedNodes.txt", ios::app); // open file to append
	fileOUT << "Current State & depth " << depth << endl << endl;

	for (int index = 0; index < 9; index += 3) {
		fileOUT << currentState[index] << " | " << currentState[index + 1] << " | " << currentState[index + 2] << endl;
	}

	fileOUT << endl;
	fileOUT.close();// close the file

	metrics->recurse += 1;


	vector<int> newState;
	vector<vector<int> > listStates;

	// Checks for depth requirement
	if (depth > 9) {
		metrics->value = getBestScores(currentState, currentPlayer, evalNum, metrics, depth);
		return metrics;
	}

	/// Generates a list of states and evalutes the values of those states
	listStates = createNewState(currentState, currentPlayer);
	if (listStates.size() == 0) {
		metrics->value = getBestScores(currentState, currentPlayer, evalNum, metrics, depth);
		return metrics;
	}

	/// Checks if the current state is a win for current player
	if (checkWin(currentState) == 1) {
		metrics->wins += 1;
		metrics->value = getBestScores(currentState, currentPlayer, evalNum, metrics, depth);
		return metrics;
	}
	/// Checks if the current state is a win for the opposing player
	else if (checkWin(currentState) == -1) {
		metrics->losses += 1;
		metrics->value = getBestScores(currentState, currentPlayer, evalNum, metrics, depth);
		return metrics;
	}


	metrics->totalExpandedNodes += 1;

	metrics->totalNumberNodes += listStates.size();

	for (int i = 0; i < listStates.size(); i++) {

		newState = listStates.at(i);

		metrics = minimaxAB(newState, depth + 1, opposite(currentPlayer), -passThresh, -useThresh, evalNum, metrics);

		//b
		metrics->newValue = -metrics->value;

		//c
		if (metrics->newValue > passThresh) {
			//i
			passThresh = metrics->newValue;
			//ii
			//set bestpath to result of attching succ to front of path(result succ)
			metrics->bestScore = passThresh;
			metrics->bestScoreDepth = depth + 1;
		}

		//d
		if (passThresh >= useThresh) {
			return metrics;
		}
	}

	return metrics;
}

// Switches the current player
int opposite(int player) {
	return -player;
}

// Calculates the best score
int getBestScores(vector<int> currentState, int currentPlayer, int evalNum, statStruct *metrics, int depth) {

	int value = 0;

	if (evalNum == 1)
		value = firstMinusOpp(currentState, currentPlayer);
	if (evalNum == 2)
		value = cornAndMid(currentState, currentPlayer);
	if (evalNum == 3)
		value = proximityEval(currentState, currentPlayer);
	if (evalNum == 4)
		value = evalTie(currentState, currentPlayer);

	if (metrics->firstTerminalNode == false) {
		metrics->firstTerminalNode = true;
		metrics->bestScore = value;
		metrics->bestScoreDepth = depth;
	}

	return value;
}

// Checks if the current state is a win
int checkWin(vector<int> currentState) {
	// Check if the current state is a win by rows
	for (int index = 0; index < 9; index += 3) {
		if (currentState[index] == 1 && currentState[index + 1] == 1 && currentState[index + 2] == 1)
			return 1;
		if (currentState[index] == -1 && currentState[index + 1] == -1 && currentState[index + 2] == -1)
			return -1;
	}

	// Check if the current state is a win by columns
	for (int index = 0; index < 3; index++) {
		if (currentState[index] == 1 && currentState[index + 3] == 1 && currentState[index + 6] == 1)
			return 1;
		if (currentState[index] == -1 && currentState[index + 3] == -1 && currentState[index + 6] == -1)
			return -1;
	}

	// Check if the current state is a win by diagnols
	for (int index = 0; index < 4; index += 2) {
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
