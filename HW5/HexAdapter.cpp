#include "HexAdapter.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;
using std::stringstream;
using std::ofstream;
using std::ifstream;

/* Prints board to the cout */
template<template<typename ...> class T>
void HexAdapter<T>::print() const{
cout <<"\n\n\n";
cout << " ";
for(int i=0; i<getBoardSize(); i++){
        cout << " " << char('A' + i);
    }
    cout << endl;
for(int i=0; i<getBoardSize(); i++){
        cout << i + 1;
        if(i+1 < 10) cout << " "; 
        if(i >= 1){
            for(int j=0; j<i; j++) cout << " ";
        }
        for(int k=0; k<getBoardSize(); k++){
		
              cout << " " << board.at(i).at(k).getPoint();  
        }
            cout << endl;
    }
determineTurn();
}

/* Saving Game || Saves the game to the file_path */
template<template<typename ...> class T>
void HexAdapter<T>::writeToFile(string& file_path)const{
 ofstream myfile;
 myfile.open(file_path);
 if(myfile.fail()) throw "File is not opened\n";

	myfile << getGameplayType() << endl;
	myfile << getBoardSize() << endl;
	myfile << getPlayerTurn() << endl;

	for(int i=0; i < getBoardSize(); i++){
		for(int k=0; k < getBoardSize(); k++){
			myfile << board.at(i).at(k).getPoint();  
		}
		myfile << endl;
	}
	cout << "Game has been saved!" << endl;
	myfile.close();
}

/* Loading game || Loads game from file_path */
template<template<typename ...> class T>
void HexAdapter<T>::readFromFile(string& file_path){
int index = 0;
string str;
stringstream ss;
ifstream myfile;
myfile.open(file_path);
if(myfile.fail()) throw "File is not opened\n";
int temp;
 for(int line=1; line < 4; line++){
 	getline(myfile,str);
 	ss.str(str);
 		if(line == 1){
		  ss >> temp;
		  setGameplayType(temp);
		}
 		else if(line == 2){
		  ss >> temp;
		  setBoardSize(temp);
		 } 
 		else if(line == 3){
          ss >> temp;
		  setPlayerTurn(temp);
		 }  
 	ss.clear();
 }
 setSize();
 while(getline(myfile,str)){
 	for(int i=0; i<getBoardSize(); i++){
 		board.at(index).at(i).setPoint(str[i]);
 	}
 	index ++;
 }
 myfile.close();
}

/* Reset the board */
template<template<typename ...> class T>
void HexAdapter<T>::reset(){
	for(int i=0; i<getBoardSize(); i++){
			for(int k=0; k<getBoardSize(); k++){
				board.at(i).at(k).setPoint(char(empty));
		}
	}	
}

/* Sets size of the board. Initialize the Cell */
template<template<typename ...> class T>
void HexAdapter<T>::setSize(){
board.resize(getBoardSize());
	for(int i=0; i<getBoardSize(); i++){
		board.at(i).resize(getBoardSize());
			for(int k=0; k<getBoardSize(); k++){
				board.at(i).at(k).setRow(i);
				board.at(i).at(k).setColumn(k);
				board.at(i).at(k).setPoint(char(empty));
		}
	}
}

/* play() function for bot. This function checks the move of bot*/
template<template<typename ...> class T>
void HexAdapter<T>::play(){
if(getGameplayType() != 2) throw "Cannot use play() function while not playing with bot.\n";
else if(getPlayerTurn() % 2 == 0 || isEnd()) return;

    moveBot();
	if(getSign() == char(bot)){
		for(int i=0; i<getBoardSize(); i++){
			if(board[getBoardSize()-1][i].getPoint() == getSign()){
				if(checkWin(getBoardSize()-1,i)){
					break;
				}
			}
		}
	}
	nextPlayer();
}

/* This function finds an appropriate place for the move of the bot */
template<template<typename ...> class T>
void HexAdapter<T>::moveBot(){
	for(int i=0; i<getBoardSize(); i++){
		if(((getLastRow()-1 >= 0) && board[getLastRow()][i].getPoint() == char(empty)) && board[getLastRow()-1][i].getPoint() == char(bot)){
			board[getLastRow()][i].setPoint(char(bot));
			return;
		}
	}
	for(int i = getLastColumn(); i<getBoardSize(); i++){
		if(board[getLastRow()][i].getPoint() == char(empty)){
			board[getLastRow()][i].setPoint(char(bot));
			return;
		}
	}
	for(int i = 0; i<getLastColumn(); i++){
		if(board[getLastRow()][i].getPoint() == char(empty)){
			board[getLastRow()][i].setPoint(char(bot));
			return;
		}
	}
	for(int i=0; i<getBoardSize(); i++){
		if(((getLastRow()+1 < getBoardSize()) && board[getLastRow()][i].getPoint() == char(empty)) && board[getLastRow()+1][i].getPoint() == char(bot)){
			board[getLastRow()][i].setPoint(char(bot));
			return;
		}
	}
}

/* Checks move is legal or illegal. If it is legal then function will return true. Otherwise it will return false. */
template<template<typename ...> class T>
bool HexAdapter<T>::checkMove(char c , int rw)const{
	int col = convertCharToInt(c);
	if(board.at(rw).at(col).getPoint() == char(empty) && checkInput(rw,col)) return true;
	else return false;
}

/* This function takes a Cell object and makes a move for the player. */
template<template<typename ...> class T>
void HexAdapter<T>::play(const Cell& move){
 initializeVisitedVector();
	board[move.getRow()][move.getColumn()].setPoint(move.getPoint());
	if(getSign() == char(user1)){
		for(int i=0; i<getBoardSize(); i++){
			if(board[i][0].getPoint() == getSign()){
				if(checkWin(i,0)){
					break;
				}
			}
		}
	}
	else if(getSign() == char(user2)){
		for(int i=0; i<getBoardSize(); i++){
			if(board[getBoardSize()-1][i].getPoint() == getSign()){
				if(checkWin(getBoardSize()-1,i)){ 
					break;
				}
			}
		}
	}	
	//playerMove++;
	setLastRow(move.getRow());
	setLastColumn(move.getColumn());
	nextPlayer();
}

/* This function is a recursive and it will look places and if game is ended then it will return true.*/
template<template<typename ...> class T>
bool HexAdapter<T>::checkWin(int curr_row,int curr_col){
	if(getSign() == char(user1)){
		if(curr_col == getBoardSize()-1){
			board[curr_row][curr_col].setPoint(char(user1 - 32));
			return true;
		}
	}
	else if(getSign() == char(user2)){
		if(curr_row == 0) {
			board[curr_row][curr_col].setPoint(char(user2 - 32));
			return true;
		}
	}
		if(curr_row-1 >= 0 && curr_col+1 < getBoardSize() && (board[curr_row-1][curr_col+1].getPoint() == getSign() && getWin() != true) && getVisitedLocation(curr_row-1,curr_col+1) != 1){
			visitedLocation(curr_row,curr_col);
			setWin(checkWin(curr_row-1,curr_col+1));
		}
		if(curr_col+1 < getBoardSize() && (board[curr_row][curr_col+1].getPoint() == getSign() && getWin() != true) && getVisitedLocation(curr_row,curr_col+1) != 1){
			visitedLocation(curr_row,curr_col);
			setWin(checkWin(curr_row,curr_col+1));
		}
		if(curr_row-1 >= 0 && (board[curr_row-1][curr_col].getPoint() == getSign() && getWin() != true) && getVisitedLocation(curr_row-1,curr_col) != 1){
			visitedLocation(curr_row,curr_col);
			setWin(checkWin(curr_row-1,curr_col));
		}
		if(curr_row+1 < getBoardSize() && (board[curr_row+1][curr_col].getPoint() == getSign() && getWin() != true) && getVisitedLocation(curr_row+1,curr_col) != 1){
			visitedLocation(curr_row,curr_col);
			setWin(checkWin(curr_row+1,curr_col));
		}
		if(curr_col-1 >= 0 && (board[curr_row][curr_col-1].getPoint() == getSign() && getWin() != true) && getVisitedLocation(curr_row,curr_col-1) != 1){
			visitedLocation(curr_row,curr_col);
			setWin(checkWin(curr_row,curr_col-1));
		}
		if(curr_col-1 >= 0 && curr_row+1 < getBoardSize() && (board[curr_row+1][curr_col-1].getPoint() == getSign() && getWin() != true) && getVisitedLocation(curr_row+1,curr_col-1) != 1){
			visitedLocation(curr_row,curr_col);
			setWin(checkWin(curr_row+1,curr_col-1));	
		}
		if(getWin()){
			if(getSign() == char(user1)) board[curr_row][curr_col].setPoint((char(user1) - 32));
			if(getSign() == char(user2)) board[curr_row][curr_col].setPoint((char(user2) - 32));
			return true;
		}
		else{
			return false;
		}
}
/* If the boards are the same then return true. */
template<template<typename ...> class T>
bool HexAdapter<T>::operator==(const AbstractHex& other) const{
	if(other.getBoardSize() != getBoardSize()) return false;

	for(int i=0; i<getBoardSize(); i++){
		for(int k=0; k<getBoardSize(); k++){
			if(board[i][k].getPoint() != other(i,k)){
				return false;
			}
		}	
	}
	return true;
}

/* Gets row and column (indexes) and returns the content of the appropriate cell.*/
template<template<typename ...> class T>
char HexAdapter<T>::operator()(int rw, int col)const{
	if(!checkInput(rw,col)) throw "Indexes are out of the range\n";
	return board[rw][col].getPoint();
}