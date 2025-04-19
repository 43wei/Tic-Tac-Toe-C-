#include "Game.h"

using namespace std;



Game::Game(bool xturn){
    plays = 0;
    win = false;
    for(unsigned i = 0; i < 9; i++){
        board[i] = ' ';
    }
    if(xturn){
        myPlay = 'X';
        robot = 'O';
    }else{
        myPlay = 'O';
        robot = 'X';
    }


}


void Game::drawBoard() const {
    
    for( int i = 0; i < 3;i++) {
        cout << '\t'  << '\t' << " " << board[i*3] << " | " <<  board[1+i*3] << " | " << board[2+i*3] << endl;
        if( i < 2){
            cout << '\t' << '\t'  << "——— ——— ———" << endl;
        }
    }
    cout << endl;

}


bool Game::checkGame(bool xturn, bool &myWin){
    bool win = false;
    char winChar;

    if(plays <5){
        win = false;
    }else{
        if(board[0]!=' ' && (board[0] == board[4]) && (board[4] == board[8])){
            win = true;
            winChar = board[4];
           
        }else if(board[2]!=' ' && (board[2] == board[4]) && (board[4] == board[6])){
            win = true;
            winChar = board[4];
            
        }
        for(int i = 0; i < 3 && !win; i++){
            if(board[i*3]!=' ' && (board[i*3] ==  board[1+i*3]) &&  (board[1+i*3]  == board[2+i*3])){
                win =true;
                winChar = board[i*3];
                
            }else if(board[i]!=' ' &&  (board[i] == board[i+3]) && (board[i+3] == board[i+6])){
                win = true;
                winChar = board[i];
               
            }
        }
    }
    // diagonals, rows, colums 
    if(win && xturn && winChar == 'X'){
        myWin = true;
    }else if(win && !xturn && winChar == 'O'){
        myWin =true;
    }else{
        myWin = false;
    }
    
    return win;
}

void Game::resetPossible(){
    vector <int> aux;
    possible = aux;
}

void Game::playable(){
    cout << "-The remaining squares are: ";
    for(int i = 0; i < 9; i++){
        if(board[i] == ' '){
            cout << "(" << i+1 << ")";
            possible.push_back(i+1);
        }
    }
    cout << endl;
}

void Game::makePlay(bool myTurn){
    bool valid = false;
    int square;
    this->resetPossible();
    this->playable();
    
   

    if(myTurn){
       do{  
           cout << "-Please introduce a valid square to play: ";
           cin >> square;
           cin.ignore();
   
           for(unsigned int i = 0; i < possible.size() && !valid; i++){
               if(possible[i]== square){
                   valid = true;
                   board[square-1] = myPlay;
               }
           }
       }while(!valid);

    }else{

        do{      
            square = 1 + rand() % 9;
            for(unsigned int i = 0; i < possible.size() && !valid; i++){
                if(possible[i]== square){
                    valid = true;
                    board[square-1] = robot;
                }
            }
        }while(!valid);
        cout << "-The robot has chosen the square: " << square << endl;
        //machine makes its play
    }


}
