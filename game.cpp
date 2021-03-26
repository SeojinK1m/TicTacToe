#include "game.h"

Game::Game() {
    //set border
    board[0][1].print_value = '1';
    board[0][2].print_value = '2';
    board[0][3].print_value = '3';
    board[1][0].print_value = '1';
    board[2][0].print_value = '2';
    board[3][0].print_value = '3';

    //initialzie piece position
    row = 999;
    col = 999;

    //initialize turn
    TURN = true;
}

std::ostream & operator <<(std::ostream& out, const Game& game) {
    //print board
    for(int i=4; i>=0; i--) {
        for(int j=0; j<5; j++) {
            out<<game.board[i][j].print_value<<" ";  
        }
        out<<std::endl;
    }
    out<<" "<<std::endl;

    return out;
}

bool Game::done() {
    //check for win condition
    return checkDiagonals() || checkHorizontal() || checkVertical();
}

bool Game::draw() {
    //if game has winner return false
    if(done()) {
        return false;
    }
    int n = 0;
    for(int i=1; i<4; i++) {
        for(int j=1; j<4; j++) {
            if(board[i][j].print_value=='O' || board[i][j].print_value=='X') {
                n++;
            }
        }
    }

    //if all 9 squares are filled and there are no winners return draw is true
    return n<9 ? false : true;
}

int Game::prompt(unsigned int & a, unsigned int & b) {
    std::string in;
    while(true) {
        std::cout<<"CHOOSE SQUARE OR TYPE 'QUIT'"<<std::endl;
        getline(std::cin, in);
        std::cout << std::endl;

        //remove all whitespace
        std::istringstream iss(in);
        std::string no_white;
        while (iss) {
            std::string temp;
            iss >> temp;
            no_white += temp;
        }

        //check if user wants to quit
        if(no_white== "QUIT" || no_white == "quit") {
            return Result::QUIT;
        }

        //replace comma with whitespace
        std::replace(no_white.begin(), no_white.end(), ',', ' ');

        //wrap string with iss
        std::istringstream iss2(no_white);
        unsigned int a2;
        unsigned int b2;
        
        iss2>>a2;
        iss2>>b2;

        if(a2<4 && a2>0 && b2<4 && b2>0) {
            a = a2;
            b = b2;
            break;
        }
    }
    return 0;
}

int Game::turn() {
    //set temp turn variable
    bool turn = TURN;

    //set turn to other player
    TURN = !TURN;

    std::cout << "Player " << (turn ? 'X' : 'O') << "'s turn" << std::endl;
    while(true) {
        if(prompt(row, col)==Result::QUIT) {
            return Result::QUIT;
        }

        if(board[row][col].print_value==' ') {
            char piece_val = turn ? 'X' : 'O';
            Piece piece;
            piece.print_value = piece_val;
            board[row][col] = piece;
            break;
        } else {
            std::cout << "Square has already been played" << std::endl;
        }
    }

    if(turn) {
        std::string thisMove;
        thisMove = "("+std::to_string(row)+","+std::to_string(col)+") ";
        p1 += thisMove;
        std::cout<<p1;
    } else {
        std::string thisMove;
        thisMove = "("+std::to_string(row)+","+std::to_string(col)+") ";
        p2 += thisMove;
        std::cout<<p2;
    }

    return Result::SUCCESS;

}

int Game::play() {

    while(true) {
        for(int i=4; i>=0; i--) {
            for(int j=0; j<5; j++) {
                std::cout<<board[i][j].print_value<<" ";  
            }
            std::cout<<std::endl;
        }
        std::cout<<" "<<std::endl;
        if (this->turn() == 1) {;
            std::cout << "Player has decided to quit"<< std::endl;
            return Result::QUIT;
        }
        if (this->done()) {
            for(int i=4; i>=0; i--) {
                for(int j=0; j<5; j++) {
                    std::cout<<board[i][j].print_value<<" ";  
                }
                std::cout<<std::endl;
            }
            if (TURN) {
                std::cout << "Player O has won!" << std::endl;
                return Result::SUCCESS;
            } else {
                std::cout << "Player X has won!" << std::endl;
                return Result::SUCCESS;
            }
        }
        if (this->draw()) {
            std::cout<<"no winner"<<std::endl;
            return Result::DRAW;
        }
    }
}

bool Game::checkHorizontal() {
    for(int i=1; i<4; i++) {
        int x = 0;
        int o = 0;
        for(int j=1; j<4; j++) {
            if(board[i][j].print_value=='X') {
                x++;
            }
            if(board[i][j].print_value=='O') {
                o++;
            }
        }
        if(x==3 || o==3) {
            return true;
        }
    }
    return false;
}

bool Game::checkVertical() {
    for(int i=1; i<4; i++) {
        int x = 0;
        int o = 0;
        for(int j=1; j<4; j++) {
            if(board[j][i].print_value=='X') {
                x++;
            }
            if(board[j][i].print_value=='O') {
                o++;
            }
        }
        if(x==3 || o==3) {
            return true;
        }
    }
    return false;
}

bool Game::checkDiagonals() {

    if(board[1][1].print_value=='X' && board[2][2].print_value=='X' && board[3][3].print_value=='X') {
        return true;
    }
    if(board[1][1].print_value=='O' && board[2][2].print_value=='O' && board[3][3].print_value=='O') {
        return true;
    }
    if(board[1][3].print_value=='X' && board[2][2].print_value=='X' && board[3][1].print_value=='X') {
        return true;
    }
    if(board[1][3].print_value=='O' && board[2][2].print_value=='O' && board[3][1].print_value=='O') {
        return true;
    }

    return false;
}

int Game::minimax(Piece board[5][5], int depth, bool turn) {
    int score = 0;
    
    if(turn && this->done()) {
        score = -10;
    } else if(!turn && this->done()) {
        score = 10;
    }

    if (score == 10 || score == -10) {
        return score;
    }

    if (this->draw()) {
        return 0;
    }

    if (turn)
    {
        int best = -1000;
 
        for (int i = 1; i<4; i++) {
            for (int j = 1; j<4; j++) {
                if (board[i][j].print_value==' ') {
                    board[i][j].print_value = 'X';
                    best = std::max(best, minimax(board, depth+1, !turn));
                    board[i][j].print_value = ' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 1; i<4; i++) {
            for (int j = 1; j<4; j++) {

                if (board[i][j].print_value==' ') {
                    board[i][j].print_value = 'O';
                    best = std::min(best,minimax(board, depth+1, !turn));
                    board[i][j].print_value = ' ';
                }
            }
        }
        return best;
    }
}

int * Game::findBestMove(Piece board[5][5]) {
    int bestVal = -1000;
    int bestMove[2];
 
    for (int i = 1; i<4; i++) {
        for (int j = 1; j<4; j++) {
            if (board[i][j].print_value==' ') {
                board[i][j].print_value = 'X';
                int moveVal = minimax(board, 0, false);
                board[i][j].print_value = ' ';
 
                if (moveVal > bestVal) {
                    bestMove[0] = i;
                    bestMove[1] = j;
                    bestVal = moveVal;
                }
            }
        }
    }
 
    return bestMove;
}

int Game::playAI() {
    while(true) {
        for(int i=4; i>=0; i--) {
            for(int j=0; j<5; j++) {
                std::cout<<board[i][j].print_value<<" ";  
            }
            std::cout<<std::endl;
        }
        std::cout<<" "<<std::endl;

        if(prompt(row, col)==Result::QUIT) {
            return Result::QUIT;
        }

        if(board[row][col].print_value==' ') {
            char piece_val = 'O';
            Piece piece;
            piece.print_value = piece_val;
            board[row][col] = piece;
        } else {
            std::cout << "Square has already been played" << std::endl;
        }

        if(this->done()) {
            std::cout << "You win!" << std::endl;
            return Result::SUCCESS;
        }
        if(this->draw()) {
            for(int i=4; i>=0; i--) {
                for(int j=0; j<5; j++) {
                    std::cout<<board[i][j].print_value<<" ";  
                }
                std::cout<<std::endl;
            }
            std::cout<<" "<<std::endl;
            std::cout << "Draw!"<< std::endl;
            return Result::DRAW;
        }

        for(int i=4; i>=0; i--) {
            for(int j=0; j<5; j++) {
                std::cout<<board[i][j].print_value<<" ";  
            }
            std::cout<<std::endl;
        }
        std::cout<<" "<<std::endl;

        int * aiMove = findBestMove(board);
        board[aiMove[0]][aiMove[1]].print_value = 'X';

        if(this->done()) {
            for(int i=4; i>=0; i--) {
                for(int j=0; j<5; j++) {
                    std::cout<<board[i][j].print_value<<" ";  
                }
                std::cout<<std::endl;
            }
            std::cout<<" "<<std::endl;
            std::cout << "AI Wins!" << std::endl;
            return Result::SUCCESS;
        }
        if(this->draw()) {
            for(int i=4; i>=0; i--) {
                for(int j=0; j<5; j++) {
                    std::cout<<board[i][j].print_value<<" ";  
                }
                std::cout<<std::endl;
            }
            std::cout<<" "<<std::endl;
            std::cout << "Draw!"<< std::endl;
            return Result::DRAW;
        }
    }
    return 0;
}