#include "game.h"

int main(int argc, char * argv[]) {

    if(argc!=StartCondition::correctSize ) {
        std::cout << "Correct usage is ./<programname>.exe TicTacToe" << std::endl;
        return Error::wrongUsage;
    }

    if(argv[StartCondition::argIndex]==std::string("TicTacToe")) {
        Game game;
        game.play();
        return Result::SUCCESS;
    }

    if(argv[StartCondition::argIndex]==std::string("TicTacToeAI")) {
        Game game;
        game.playAI();
        return Result::SUCCESS;
    }

    std::cout << "Correct usage is ./<programname> TicTacToe" << std::endl;
    return Error::wrongUsage;
    
}
