#include <iostream>
#include "AbstractHex.h"
#include "HexVector.h"
#include "HexArray1D.h"
#include "HexAdapter.h"
#include "HexAdapter.cpp" //For templates
#include <vector>
#include <deque>
using std::cout;
using std::cin;
using std::endl;
using namespace HexGame;

bool validSequence(AbstractHex * other[],int size){
AbstractHex * obj = other[0];

    for(int i = 1; i < size; i++){
        if(other[i]->getBoardSize() != obj->getBoardSize()) {return false;}
        for(int k = 1; k <= obj->getBoardSize(); k++){
            for(int j=0; j < obj->getBoardSize(); j++){
                    AbstractHex::Cell cell(k,j,other[i]->operator()(k-1,j));
                    if(obj->operator()(k-1,j) != '.' && other[i]->operator()(k-1,j) != '.' && obj->operator()(k-1,j) != other[i]->operator()(k-1,j)){
                        return false;
                    }
                    else if(obj->operator()(k-1,j) == '.') obj->play(cell);
            }
        }
    }

int number_of_user1 = 0 , number_of_user2 = 0;
    for(int k = 0; k < obj->getBoardSize(); k++){
        for(int j=0; j < obj->getBoardSize(); j++){
             if(obj->operator()(k,j) == 'x') number_of_user1++;
            else if(obj->operator()(k,j) == 'o') number_of_user2++;
            if(number_of_user1 - number_of_user2 > 1 || number_of_user2 - number_of_user1 > 1){
                return false;} 
        }
    }
    return true;
}


/* MENU TO TEST THE CLASSES */
int main(){
int select1,select2,select3;
std::string str;

try{ //TRY BLOCK
menu:
cout << "\033c" << endl;
cout << "\t%%% WELCOME TO THE HEX GAME %%%\n\t     Created by Arda Kılıç\n\n\n";
cout << "Menu:\n\n";
cout << "1- Play Game\n";
cout << "2- Instructions\n";
cout << "3- Exit\n";
cout << "\n>";
cin >> select1;

    switch(select1){
        case 1:
            cout << "\033c" << endl;
            cout << "Please Select A Class\n\n";
            cout << "1- HexVector ~ Board is a vector\n";
            cout << "2- HexArray1D ~ Board is a 1D C array\n";
            cout << "3- HexAdapter ~ Board is vector OR deque\n";
            cout << "\n>";
            cin >> select2;
                switch(select2){
                    case 1:
                        cout << "\033c" << endl;
                        {
                        HexVector game;
                        game.startGame();
                        game.print();
                            while(!game.isEnd()){
                                game.getMove();
                                game.print();
    
                            }    
                        }
                        break;
                    case 2:
                        cout << "\033c" << endl;
                        {
                        HexArray1D game;
                        game.startGame();
                        game.print();
                            while(!game.isEnd()){
                                game.getMove();
                                game.print();
                            }    
                        }     
                        break;
                    case 3:
                        cout << "\033c" << endl;
                        cout << "Select a container for template class\n\n";
                        cout << "1- Vector\n";
                        cout << "2- Deque\n";
                            cout << "\n>";
                            cin >> select3;
                                switch(select3){
                                    case 1:
                                        cout << "\033c" << endl;
                                        {
                                        HexAdapter<std::vector> game;
                                        game.startGame();
                                        game.print();
                                            while(!game.isEnd()){
                                            game.getMove();
                                            game.print();
                                              }    
                                        }      
                                        break;
                                    case 2:
                                        cout << "\033c" << endl;
                                        {
                                        HexAdapter<std::deque> game;
                                        game.startGame();
                                        game.print();
                                            while(!game.isEnd()){
                                            game.getMove();
                                            game.print();
                                              }       
                                        }
                                    break;
                                    default:
                                        throw "Input is not correct! You must enter a number between 1 and 2\n";
                                }
                        break;
                        default:
                            throw "Input is not correct! You must enter a number between 1 and 3\n";
                }
        break;
        case 2:
            cout << "\033c" << endl;
            cout << "\t %%% INSTRUCTIONS %%% \n\n";
            cout << "Save game: SAVE filename.txt\n";
            cout << "Load game: LOAD filename.txt\n";
            cout << "Get Number of Moves: MOVES\n";
            cout << "Use operator(): OPERATOR() index1 index2 [Ex: ""OPERATOR() 0 1"" (For B1)]\n";
            cout << "Get the last move: LAST\n";
            cout << "Reset the board: RESET\n";
            cout << "Exit: exit\n";
            cout << "Back To Menu: back\n";
            cout << "\n>";
            cin >> str;
            if(str == "back") goto menu;
        break;
        case 3:
            cout << "Have a nice day!\n";
            exit(0);
        default:
            throw "Input is not correct! You must enter a number between 1 and 3\n";
    }
}
catch(const char* error){ //Catches exceptions that sent from functions in classes
    cerr << error; //Prints the error and terminates the program.
    exit(1);
}

    /* TESTING GLOBAL FUNCTION */
AbstractHex::Cell m1(2,3,'x'),m2(2,3,'o'),m3(1,2,'x'),m4(1,3,'o'),m5(1,3,'x'),m6(4,5,'o'),m7(4,5,'x');
/* Inıtıalization of Boards (HexVector) */
HexVector gameV1(5),gameV2(6);
gameV1.play(m5);gameV1.play(m3);
gameV2.play(m3);gameV2.play(m6);
/* Inıtıalization of Boards (HexArray1D) */
HexArray1D gameAr1(6),gameAr2(6);
gameAr1.play(m2);gameAr1.play(m7); 
gameAr2.play(m1);gameAr2.play(m4);
/* Inıtıalization of Boards (HexAdapter using vector) */
HexAdapter<std::vector> gameAdV1(5);
gameAdV1.play(m3);gameAdV1.play(m6);
/* Inıtıalization of Boards (HexAdapter using deque) */
HexAdapter<std::deque> gameAdD1(5);
gameAdD1.play(m7);gameAdD1.play(m4);
/* Setting the arrays */
AbstractHex * sequence1[3] = {&gameV1,&gameAr1,&gameAdV1};
AbstractHex * sequence2[2] = {&gameV2,&gameAr2};
AbstractHex * sequence3[2] = {&gameV1,&gameAdD1};
AbstractHex * sequence4[4] = {&gameV1,&gameAr1,&gameAdV1,&gameAr2};
AbstractHex * sequence5[3] = {&gameV1,&gameAr2,&gameAdV1};

                      /* TESTING SEQUENCES */
    cout << "\n1- Is this sequence valid = " << std::boolalpha << validSequence(sequence1,3) << endl;
    cout << "2- Is this sequence valid = " << std::boolalpha << validSequence(sequence2,2) << endl;
    cout << "3- Is this sequence valid = " << std::boolalpha << validSequence(sequence3,2) << endl;
    cout << "4- Is this sequence valid = " << std::boolalpha << validSequence(sequence4,4) << endl;
    cout << "5- Is this sequence valid = " << std::boolalpha << validSequence(sequence5,3) << endl;

                    /* TESTING operator== */
    cout << "\nAre this 2 game equal (gameV1 and gameV2)? = " << std::boolalpha << (gameV1==gameV2) << endl;



    return 0;
}