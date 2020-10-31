#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
	vector<int> currentState;
	ListNode* next;
};

// only generate the nodes that would have atleast one winning line with a changed position
// return game tree
ListNode generateGameTree(vector<int> currentState, int depth, int pos, int player, int maxDepth) {
	if (pos > 8)
		return null;
	vector<int, int> rows = { {currentState[0], currentState[1], currentState[2]},
							{currentState[3], currentState[4], currentState[5]},
							{currentState[6], currentState[7], currentState[8]} };

	vector<int, int> cols = { {currentState[0], currentState[3], currentState[6]},
								{currentState[1], currentState[4], currentState[7]},
								{currentState[2], currentState[5], currentState[8]} };

	vector<int, int> diags = { {currentState[0], currentState[4], currentState[8]},
								{currentState[2], currentState[4], currentState[6]} };

	ListNode currentNode*;

	if (depth = 0)
		currentNode->currentState = currentState;
	else {
		if (currentState[pos] == 0)
			currentState[pos] == player;
		else {
			if (currentState[pos] != player)
				currentState[pos] == player;
		}
		if (player == 1) 
			player == 2;
		else
			player == 1
	}
	if (depth != maxDepth) {
		for
		ListNode next* = generateGameTree(currentState, depth + 1, pos + 1, player, maxDepth);
		if(currentState != next->currentState)
			currentNode->next = 
	}

	return currentNode;
}


// return evalution score
vector<int> evalOne(vector<int> currentState, int depth) {
	vector<int> gameTree;



	return gameTree;
}
