#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include <time.h>
#include <sstream>
#include <vector>
using namespace std;



const int nSquares = 9;


bool coinToss(){
    bool validChoice = false;
    bool coin; //zero for head one for tails to simplify? use enums in the future.
    string read;
    int readings = 0;


    cout << "You must first decide who goes first, a coin will be tossed, choose heads or tails: ";

    while(!validChoice){

        if(readings > 0){
            cout << "Try again, you must choose between heads or tails: ";
        }


        getline(cin,read);
        char choice[6];
        readings++;


        if(read.length() == 5){
            strncpy(choice,read.c_str(),5);
            choice[5] = '\0';

            for(unsigned int i=0;i<5;i++){
                choice[i] = tolower(choice[i]);
            }

            if(!strcmp(choice,"heads")){
                cout << "-You have chosen heads, good luck!" << endl;
                coin = false;
                validChoice = true;
            }else if(!strcmp(choice,"tails")){
                cout << "-You have chosen tails, good luck!" << endl;
                coin = true;
                validChoice = true;
            }else{
                validChoice = false;
            }

            cout << endl;
        }
    


    }


    return coin;
}


void showIntro(){
    cout << "TIC TAC TOE CODE" << endl;
    cout << "________________" << endl;
    cout << "Play tic tac toe against the machine, give it a try!" << endl << endl;
    
}




bool randomToss(){
    int random = rand() % 2 ;
    cout << "The randomizer has tossed: ";
    if(random == 0){
        cout << "heads" << endl;
    }else{
        cout << "tails" << endl;
    }
    return random;
}

bool checkTurn(bool coin,bool random){
    bool turn;

    if(coin == random){
        cout << "-Congrats!!! You have won the coin toss, let's start playing!" << endl;
        turn = true;
    }else{
        cout << "-Oh! The machine has taken the first turn, good luck!" << endl;
        turn = false;
    }

    cout << endl;
    return turn;
}


bool requestPlay(){
    bool yea;
    char c;
    cout << "Wish to play again? (y/Y to continue): ";
    cin.get(c);
    cin.ignore();
    
    if(tolower(c) == 'y'){
        yea = true;
    }else{
        yea = false;
    }

    cout << endl;

    return yea;
}


bool checkGame(const char game[],int turns, bool xturn, bool &myWin){
    bool win = false;
    char winChar;

    if(turns <5){
        win = false;
    }else{
        if(game[0]!=' ' && (game[0] == game[4]) && (game[4] == game[8])){
            win = true;
            winChar = game[4];
           
        }else if(game[2]!=' ' && (game[2] == game[4]) && (game[4] == game[6])){
            win = true;
            winChar = game[4];
            
        }
        for(int i = 0; i < 3 && !win; i++){
            if(game[i*3]!=' ' && (game[i*3] ==  game[1+i*3]) &&  (game[1+i*3]  == game[2+i*3])){
                win =true;
                winChar = game[i*3];
                
            }else if(game[i]!=' ' &&  (game[i] == game[i+3]) && (game[i+3] == game[i+6])){
                win = true;
                winChar = game[i];
               
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



void drawBoard(const char game[]){ //char input[]
   
    for( int i = 0; i < 3;i++) {
        cout << '\t'  << '\t' << " " << game[i*3] << " | " <<  game[1+i*3] << " | " << game[2+i*3] << endl;
        if( i < 2){
            cout << '\t' << '\t'  << "——— ——— ———" << endl;
        }
    }
    cout << endl;

}

void play(bool xturn, bool myTurn, char game[]){
    int square;
    char myPlay,robot;
    bool valid = false;
    vector <int> possible;


    cout << "-The remaining squares are: ";
    for(int i = 0; i < 10; i++){
        if(isdigit(game[i])){
            cout << "(" << i << ")";
            possible.push_back(i);
        }
    }
    cout << endl;
    
    if(xturn){
        myPlay = 'X';
        robot = 'O';
    }else{
        myPlay = 'O';
        robot = 'X';
    }
    if(myTurn){
       do{  
           cout << "-Please introduce a valid square to play: ";
           cin >> square;
           cin.ignore();
   
           for(unsigned int i = 0; i < possible.size() && !valid; i++){
               if(possible[i] == square){
                   valid = true;
                   game[square] = myPlay;
               }
           }
       }while(!valid);

    }else{

        do{      
            square = rand() % 9;
            for(unsigned int i = 0; i < possible.size() && !valid; i++){
                if(possible[i]== square){
                    valid = true;
                    game[square] = robot;
                }
            }
        }while(!valid);
        cout << "-The robot has chosen the square: " << square << endl;
        //machine makes its play
    }


}

void congrats(bool myWin){
    if(myWin){
        cout << "Congratulations!!! You have defeated the machine!" << endl;
    }else{
        cout << "Better luck next time, the machine has defeated you." << endl;
    }

}

void draw(){
    cout << "The match has concluded in a draw, feel free to try again!" << endl;
}

int main(){
    bool coin,win,random,xturn,myturn,myWin,goon=true;
    
    int plays = 0;
    srand(time(NULL));


    showIntro();

    while(goon){
        char game[9] = {'1','2','3','4','5','6','7','8','9'};
        //zero for head one for tails to simplify? use enums in the future.
        coin = coinToss();
        random = randomToss();
        xturn = checkTurn(coin,random);
        myturn = xturn;
        win = false;
        myWin = false;
        plays = 0;
    
        
        while(!win && plays < 9){
            play(xturn,myturn,game);
            plays++;
            drawBoard(game);
            win = checkGame(game,plays,xturn,myWin);
            myturn = !myturn;
        }
        if(plays == 9 && !win){
            draw();
        }else{
            congrats(myWin);
        }

        goon = requestPlay();
    }
    return 0;
}
