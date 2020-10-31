int proximityEval(vector<int> currentState, int player){
    int scorePlayer = 0;
    int scoreOtherPlayer = 0;
    
    // Checking proximity of values above each player
    for(int index = 3; index < 9; index++){
        if (currentstate[index - 3] == player && currentstate[index - 3] == (-player))
            scorePlayer += 2;
    }
    
    // Checking proximity of values above each other player
    for(int index = 3; index < 9; index++){
        if (currentstate[index - 3] == (-player) && currentstate[index - 3] == player)
            scoreOtherPlayer += 2;
    }
    
    return(scorePlayer - scoreOtherPlayer);
    
}
 // -1 = O
 // 1 = X

 0 1 2
 3 4 5
 6 7 8
