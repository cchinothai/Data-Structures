//Author: Cody Chinothai
//San Diego State university
// CS210/496: Data Structures
//
// Twisty Passages: Construction of a random maze utilizing the int pair coordinate approach.
// stack and set data structures are used to actively create pathways within the maze.

#include <iostream>
#include <stack>
#include <set>
#include <random>
#include <vector>
#include <chrono>
using namespace std;
std::set<pair<int,int>> visited;
std::stack<pair<int,int>> toDo;

//identifies the adjacent neighbors of the current node and checks if they've been visited
//and are within the bounds of the maze before being pushed into the stack
vector<pair<int,int>> loadUnvisitedNeighbors(pair<int,int> curNode, int length){
    vector<pair<int,int>> neighbors;
    //up
    pair<int,int> up;
    up.first = curNode.first-1;
    up.second = curNode.second;
    if(!visited.count(up) && up.first >=0)
        neighbors.push_back(up);
    //down
    pair<int,int> down;
    down.first = curNode.first+1;
    down.second = curNode.second;
    if(!visited.count(down) && down.first < length)
        neighbors.push_back(down);
    //left
    pair<int,int> left;
    left.first = curNode.first;
    left.second = curNode.second-1;
    if(!visited.count(left) && left.second >=0)
        neighbors.push_back(left);
    //right
    pair<int,int> right;
    right.first = curNode.first;
    right.second = curNode.second+1;
    if(!visited.count(right) && right.second < length)
        neighbors.push_back(right);

    return neighbors;
}

//prints the maze by printing the active row/column contents and the borders separately
void showSpace(vector<string> col, vector<vector<string>> row){
    //top border
    for(int c = 0; c < col.size()+2; c++){
        std::cout << "X";
    }
    cout << endl;

    for(int r = 0; r < row.size(); r++){
        cout << "X";
        for(int c = 0; c < col.size(); c++){
            std::cout << row[r][c];
        }
        cout << "X";
        std::cout << endl;
    }

    //bottom border

    for(int c = 0; c < col.size()+2; c++){
        std::cout << "X";
    }

}

//uses seeded uniform int distribution to generate random numbers for random neighbor selection
int getRandomIndex(int range){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0, range);
    distribution.reset();
    return distribution(generator);
}

int main() {

    int arg = 40; // default value
    cin >> arg;

    // STEP ONE: REPRESENT SQUARE SPACE
    //default argument: generate space with 40x40 rooms
    int width = arg * 2 - 1;
    vector<string> col;
    for (int i = 0; i < arg * 2 - 1; i++) {
        if (i % 2 == 0)
            col.push_back(".");
        else
            //with borders removed, walls will always be at odd square/column indexes
            col.push_back("X");
    }
    vector<vector<string>> square;
    for (int i = 0; i < arg * 2 - 1; i++) {
        square.push_back(col);
    }

    //square modulus separation
    for (int r = 0; r < square.size(); r++) {
        for (int c = 0; c < col.size(); c++) {
            if (r % 2 == 1)
                square[r][c] = "X";
        }
    }

    // STEP TWO: ALGORITHM (Depth First Search) --> Turn square space into a maze
    //---------------------------------------------------------
    //std::set<pair<int,int>> visited;
    //std::stack<pair<int,int>> toDo;
    //---------------------------------------------------------
    //defined startNode is the upper left corner of maze
    pair<int, int> startNode = {0, 0};
    toDo.push(startNode);

    while (!toDo.empty()) {
        pair<int, int> currentNode = toDo.top();
        toDo.pop();
        if (!visited.count(currentNode)) {
            //for border checking
            int mazeLength = arg * 2 - 1;
            vector<pair<int, int>> neighbors = loadUnvisitedNeighbors(currentNode, mazeLength);
            //push unvisited neighbors into stack of work to do
            for (pair<int, int> &n: neighbors) {
                toDo.push(n);
            }

            //pick random neighbor
            if (neighbors.size() != 0) {
                int randIndex = getRandomIndex(neighbors.size() - 1);
                pair<int, int> randNeighbor = neighbors[randIndex];

                //break wall
                int neighborRow = randNeighbor.first;
                int neighborCol = randNeighbor.second;
                square[neighborRow][neighborCol] = ".";


                //mark current node as visited then push selected neighbor to the top of stack
                toDo.push(randNeighbor);
            }
        }
        visited.insert(currentNode);


    }
        //print maze after depth first search algorithm is performed.
        showSpace(col, square);

        return 0;

}