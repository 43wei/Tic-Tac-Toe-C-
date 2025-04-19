#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include <time.h>
#include <sstream>
#include "Game.h"
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


void congrats(bool myWin,int &wins,int &matches){
    if(myWin){
        cout << "Congratulations!!! You have defeated the machine!" << endl;
        wins++;
    }else{
        cout << "Better luck next time, the machine has defeated you." << endl;
    }
    matches++;
    cout <<"Current score: " << wins << "-" << matches-wins << endl;
    
}

void draw(){
    cout << "The match has concluded in a draw nobody gets points, feel free to try again!" << endl;
}



int main(){
    bool coin,win,random,xturn,myturn,myWin,goon=true;
    srand(time(NULL));
    int matches = 0, wins = 0;
    

    showIntro();

    while(goon){
        //zero for head one for tails to simplify? use enums in the future.
        coin = coinToss();
        random = randomToss();
        xturn = checkTurn(coin,random);
        myturn = xturn;
        win = false;
        myWin = false;
        
        Game g(xturn);
    
        
        while(!win && g.getPlays() < 9){
            g.makePlay(myturn);
            g.addPlay();
            g.drawBoard();
            win = g.checkGame(xturn,myWin);
            myturn = !myturn;
        }
        if(g.getPlays() == 9 && !win){
            draw();
        }else{
            congrats(myWin,wins,matches);
        }
        goon = requestPlay();
    }
    return 0;
}