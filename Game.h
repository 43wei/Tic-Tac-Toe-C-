#include <vector>
#include <iostream>

using namespace std;

class Game{
    friend ostream& operator<<(ostream &os, const Game &g);
    public:
        Game(bool xturn);
        void drawBoard() const ;
        bool checkGame(bool xturn, bool &myWin); // if xturn is true the first turn, the first x is placed is was the players'
        void playable();
        void makePlay(bool myTurn);
        void addPlay(){ plays++;};
        int getPlays(){ return plays;};
        void resetPossible();
    private:
        char board[9];
        vector <int> possible;
        char myPlay;
        char robot;
        int plays;
        bool win; // someone has won, check who has won win myWin variable
};