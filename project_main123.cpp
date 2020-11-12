#include <vector>
#include <iostream>
#include <cstdlib> 

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
  	newValue = 0;
};
statStruct* minimaxAB(vector<int> currentState, int depth, int currentPlayer, int useThresh, int passThresh, int evalNum, statStruct* metrics);
vector<vector<int> > createNewState(vector<int> currentState, int player);
int opposite(int player);
int firstMinusOpp(vector<int> currentState, int player);
int cornAndMid(vector<int> currentState, int player);
int proximityEval(vector<int> currentState, int player);
int evalTie(vector<int> currentState, int player);


// X = 1
// O = -1
int main() {

	vector<int> currentState{ 0, -1, 1, -1, 0, 0, 1, -1, 0 };

    statStruct* metrics = new statStruct;

    statStruct* bestValue = minimaxAB(currentState, 1, 1, 1000, -1000, 1, metrics);
    cout << "Best Value E1 " << bestValue->bestScore << " Total # of nodes " << bestValue->totalNumberNodes << " Total Expanded nodes " << bestValue->totalExpandedNodes << endl;
    metrics = new statStruct;
    
    bestValue = minimaxAB(currentState, 1, 1, 1000, -1000, 2, metrics);
    cout << "Best Value E2 " << bestValue->bestScore << " Total # of nodes " << metrics->totalNumberNodes << " Total Expanded nodes " << metrics->totalExpandedNodes  << endl;
    metrics = new statStruct;
    
    bestValue = minimaxAB(currentState, 1, 1, 1000, -1000, 3, metrics);
    cout << "Best Value E3 " << bestValue->bestScore << " Total # of nodes " << metrics->totalNumberNodes << " Total Expanded nodes " << metrics->totalExpandedNodes  << endl;
    metrics = new statStruct;
    
    bestValue = minimaxAB(currentState, 1, 1, 1000, -1000, 4, metrics);
    cout << "Best Value E4 " << bestValue->bestScore << " Total # of nodes " << metrics->totalNumberNodes << " Total Expanded nodes " << metrics->totalExpandedNodes  << endl;

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
	/*int bestScore = 0,
		resultSucc = 0,
		lengthGamePath = 0,
		totalNumberNodes = 0,
		totalExpandedNodes = 0,
		newValue = 0;*/
	
	vector<int> newState;
	int table[4];
	vector<vector<int> > listStates;

	if (depth > 9) {
		if (evalNum == 1){
		    metrics->bestScore = firstMinusOpp(currentState, currentPlayer);
			return metrics;
			}
		if (evalNum == 2){
		    metrics->bestScore = cornAndMid(currentState, currentPlayer);
			return metrics;
			}
		if (evalNum == 3){
		    metrics->bestScore = proximityEval(currentState, currentPlayer);
			return metrics;
			}
		if (evalNum == 4){
		    metrics->bestScore = evalTie(currentState, currentPlayer);
			return metrics;
			}
	}

    //cout << "Best Score Out " << metrics.bestScore << endl;

	listStates = createNewState(currentState, currentPlayer);
	if (listStates.size() == 0) {
		if (evalNum == 1){
		    metrics->bestScore = firstMinusOpp(currentState, currentPlayer);
		    cout << "Best Score E1 " << metrics->bestScore << endl;
			return metrics;
			}
		if (evalNum == 2){
		    metrics->bestScore = cornAndMid(currentState, currentPlayer);
		    cout << "Best Score E2 " << metrics->bestScore << endl;
			return metrics;
			}
		if (evalNum == 3){
		    metrics->bestScore = proximityEval(currentState, currentPlayer);
		    cout << "Best Score E3 " << metrics->bestScore << endl;
			return metrics;
			}
		if (evalNum == 4){
		    metrics->bestScore = evalTie(currentState, currentPlayer);
		    cout << "Best Score E4 " << metrics->bestScore << endl;
			return metrics;
			}
	}
	
	//cout << "1) PT " << passThresh << " UT " << useThresh << endl;
	
	metrics->totalExpandedNodes += 1;
	
	metrics->totalNumberNodes += listStates.size();
	
	//cout << "Loop " << evalNum << endl;
	
	for (int i = 0; i < listStates.size(); i++) {
		newState = listStates.at(i);
		
        
		metrics = minimaxAB(newState, depth + 1, opposite(currentPlayer), -passThresh, -useThresh, evalNum, metrics);
        
        //cout << "Result Succ " << metrics.resultSucc << endl;
        
		//b (set newState to -resultSucc)
		metrics->newValue = -metrics->resultSucc;

		//c
		if (metrics->newValue > passThresh) {
			//i
			passThresh = metrics->newValue;
			//ii
			//set bestpath to result of attching succ to front of path(result succ)
			metrics->bestScore = passThresh;
		}

        //cout << "2) PT " << passThresh << " UT " << useThresh << endl;

		//d
		if (passThresh >= useThresh)
			return metrics;
	}

	return metrics;
}

int opposite(int player) {
	return -player;
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

    //cout << "E1 = " << player1 - player2 << endl;

	return player1 - player2;
}


// Add a point for every player's piece in any of the corners or mid position.
int cornAndMid(vector<int> currentState, int player) {
	int score = 0;

	// Check rows and colomns
	for (int i = 0; i <= 8; i = i + 2) {
	    //cout << "current state " << currentState[i] << " Player " << player << endl;
		if (currentState.at(i) == player) {
			score++;
		}
	}

    //cout << "E2 = " << score << endl;

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

    //cout << "E3 = " << scorePlayer - scoreOtherPlayer << endl;
     
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
	
	//cout << "E4 = " << score << endl;
	
	return score;
}
// -1 = O
// 1 = X

