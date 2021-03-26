#include <sstream>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

enum Result {SUCCESS, QUIT, DRAW};
enum StartCondition {argIndex=1, correctSize = 2};
enum Error {wrongUsage=1};

struct Piece {
    char print_value = ' ';
};

class Game {
    private:
    //2d array representing game board
    Piece board[5][5];

    //uints representing where the piece is placed
    unsigned int row;
    unsigned int col;

    //boolean representing whose turn it is. true means X, false means O
    bool TURN;

    //string representing all the moves played by each player thus far
    std::string p1;
    std::string p2;

    public:
    //Constructor
    Game();

    //overlaoding operator
    friend std::ostream & operator <<(std::ostream& out, const Game& game);

    //check if game is finished with winenr
    bool done();

    //check if game is draw
	bool draw();

    //prompt user for position to place piece
	int prompt(unsigned int & a, unsigned int & b);

    //switch turns
	int turn();

    //play the game
	int play();

    //check win conditions
    bool checkHorizontal();
    bool checkVertical();
    bool checkDiagonals();

    //unbeatable AI (minimax algorithm)
    int minimax(Piece board[5][5], int depth, bool max);

    //find best move using minimax
    int * findBestMove(Piece board[5][5]);

    //pay against AI
    int playAI();
};