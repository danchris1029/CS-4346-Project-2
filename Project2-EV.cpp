#include <iostream>
#include <vector>
using namespace std;

// only generate the nodes that would have atleast one winning line with a changed position
// return game tree
ListNode generateGameTree(vector<int> currentState, int depth) {
	vector<int, int> rows = { {currentState[0], currentState[1], currentState[2]},
							{currentState[3], currentState[4], currentState[5]},
							{currentState[6], currentState[7], currentState[8]} };

	vector<int, int> cols = { {currentState[0], currentState[3], currentState[6]},
								{currentState[1], currentState[4], currentState[7]},
								{currentState[2], currentState[5], currentState[8]} };

	vector<int, int> diags = { {currentState[0], currentState[4], currentState[8]},
								{currentState[2], currentState[4], currentState[6]} };

	

	ListNode head;

	return head;
}


// return evalution score
vector<int> evalOne(vector<int> currentState, int depth) {
	vector<int> gameTree;



	return gameTree;
}
