#include "HexArray1D.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
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
void HexArray1D::print() const{
cout <<"\n\n\n";
int index = 0;
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
        for(index; index<getBoardSize()+(i*getBoardSize()); index++){
              cout << " " << board[index].getPoint(); 
        }
            cout << endl;
    }
determineTurn();
}
/* Saving Game || Saves the game to the file_path */
void HexArray1D::writeToFile(string& file_path) const{
 ofstream myfile;
 myfile.open(file_path);
 if(myfile.fail()) throw "File is not opened\n";
	myfile << getGameplayType() << endl;
	myfile << getBoardSize() << endl;
	myfile << getPlayerTurn() << endl;

	for(int i=0; i < getBoardSize(); i++){
		for(int k=0; k < getBoardSize(); k++){
			myfile << board[getIndex(i,k)].getPoint();  
		}
		myfile << endl;
	}
	cout << "Game has been saved!" << endl;
	myfile.close();
}
/* Loading game || Loads game from file_path */
void HexArray1D::readFromFile(string& file_path){
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
 setSize(); //reallocate
 while(getline(myfile,str)){
 	for(int i=0; i<getBoardSize(); i++){
 		board[getIndex(index,i)].setPoint(str[i]);
 	}
 	index ++;
 }
 myfile.close();
}
/* Reset the board */
void HexArray1D::reset(){
int index = 0;
	for(int i=0; i<getBoardSize(); i++){
		for(index; index < getBoardSize()+(i*getBoardSize()); index++){
            board[index].setPoint(char(empty)); 
        }
	}	
}
/* Sets size of the board. Initialize the Cell */
void HexArray1D::setSize(){
int index = 0;
board = (Cell*)calloc(getBoardSize()*getBoardSize(), sizeof(Cell));
	for(int i=0; i<getBoardSize(); i++){
		for(index; index < getBoardSize()+(i*getBoardSize()); index++){
            board[index].setRow(i);
            board[index].setColumn(index);
            board[index].setPoint(char(empty)); 
        }
	}
}
/* play() function for bot. This function checks the move of bot*/
void HexArray1D::play(){
if(getGameplayType() != 2) throw "Cannot use play() function while not playing with bot.\n";
else if(getPlayerTurn() % 2 == 0) return;
    moveBot();
	if(getSign() == char(bot)){
			for(int i=0; i<getBoardSize(); i++){
					if(board[getIndex(getBoardSize()-1,i)].getPoint() == getSign()){
							if(checkWin(getBoardSize()-1,i)){
					break;
				}
			}
		}
	}
	nextPlayer();
}
/* This function finds an appropriate place for the move of the bot */
void HexArray1D::moveBot(){
	for(int i=0; i<getBoardSize(); i++){
		if(((getLastRow()-1 >= 0) && board[getIndex(getLastRow(),i)].getPoint() == char(empty)) && board[getIndex(getLastRow()-1,i)].getPoint() == char(bot)){
					board[getIndex(getLastRow(),i)].setPoint(char(bot));
			return;
		}
	}
	for(int i = getLastColumn(); i<getBoardSize(); i++){
			if(board[getIndex(getLastRow(),i)].getPoint() == char(empty)){
			board[getIndex(getLastRow(),i)].setPoint(char(bot));
			return;
		}
	}
	for(int i = 0; i<getLastColumn(); i++){
			if(board[getIndex(getLastRow(),i)].getPoint() == char(empty)){
					board[getIndex(getLastRow(),i)].setPoint(char(bot));
			return;
		}
	}
	for(int i=0; i<getBoardSize(); i++){
		if(((getLastRow()+1 < getBoardSize()) && board[getIndex(getLastRow(),i)].getPoint() == char(empty)) && board[getIndex(getLastRow()+1,i)].getPoint() == char(bot)){
			board[getIndex(getLastRow(),i)].setPoint(char(bot));
			return;
		}
	}
}
/* This function gets row and column indexes (like 2D array or vector) and returns an index for 1D array */
int HexArray1D::getIndex(int rw , int col) const{
    return (rw*getBoardSize()) + col;
}
/* Checks move is legal or illegal. If it is legal then function will return true. Otherwise it will return false. */
bool HexArray1D::checkMove(char c , int rw) const{
	int col = convertCharToInt(c);
	if(board[getIndex(rw,col)].getPoint() == char(empty) && checkInput(rw,col)) return true;
	else return false;
}
/* This function takes a Cell object and makes a move for the player. */
void HexArray1D::play(const Cell& move){
 initializeVisitedVector();
    board[getIndex(move.getRow(),move.getColumn())].setPoint(move.getPoint());
	//board[move.getRow()][move.getColumn()].setPoint(getSign());
	if(getSign() == char(user1)){
		for(int i=0; i<getBoardSize(); i++){
			if(board[getIndex(i,0)].getPoint() == getSign()){
				if(checkWin(i,0)){
					break;
				}
			}
		}
	}
	else if(getSign() == char(user2)){
		for(int i=0; i<getBoardSize(); i++){
			if(board[getIndex(getBoardSize() - 1,i)].getPoint() == getSign()){
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
bool HexArray1D::checkWin(int curr_row,int curr_col){
	if(getSign() == char(user1)){
		if(curr_col == getBoardSize()-1){
			board[getIndex(curr_row,curr_col)].setPoint(char(user1 - 32));
			return true;
		}
	}
	else if(getSign() == char(user2)){
		if(curr_row == 0) {
			board[getIndex(curr_row,curr_col)].setPoint(char(user2 - 32));
			return true;
		}
	}
		if(curr_row-1 >= 0 && curr_col+1 < getBoardSize() && (board[getIndex(curr_row-1,curr_col+1)].getPoint() == getSign() && getWin() != true) && getVisitedLocation(curr_row-1,curr_col+1) != 1){
			visitedLocation(curr_row,curr_col);
			setWin(checkWin(curr_row-1,curr_col+1));
		}
		if(curr_col+1 < getBoardSize() && (board[getIndex(curr_row,curr_col+1)].getPoint() == getSign() && getWin() != true) && getVisitedLocation(curr_row,curr_col+1) != 1){
			visitedLocation(curr_row,curr_col);
			setWin(checkWin(curr_row,curr_col+1));
		}
		if(curr_row-1 >= 0 && (board[getIndex(curr_row-1,curr_col)].getPoint() == getSign() && getWin() != true) && getVisitedLocation(curr_row-1,curr_col) != 1){
			visitedLocation(curr_row,curr_col);
			setWin(checkWin(curr_row-1,curr_col));
		}
		if(curr_row+1 < getBoardSize() && (board[getIndex(curr_row+1,curr_col)].getPoint() == getSign() && getWin() != true) && getVisitedLocation(curr_row+1,curr_col) != 1){
			visitedLocation(curr_row,curr_col);
			setWin(checkWin(curr_row+1,curr_col));
		}
		if(curr_col-1 >= 0 && (board[getIndex(curr_row,curr_col-1)].getPoint() == getSign() && getWin() != true) && getVisitedLocation(curr_row,curr_col-1) != 1){
			visitedLocation(curr_row,curr_col);
			setWin(checkWin(curr_row,curr_col-1));
		}
		if(curr_col-1 >= 0 && curr_row+1 < getBoardSize() && (board[getIndex(curr_row+1,curr_col-1)].getPoint() == getSign() && getWin() != true) && getVisitedLocation(curr_row+1,curr_col-1) != 1){
			visitedLocation(curr_row,curr_col);
			setWin(checkWin(curr_row+1,curr_col-1));	
		}
		if(getWin()){
			if(getSign() == char(user1)) board[getIndex(curr_row,curr_col)].setPoint((char(user1) - 32));
			if(getSign() == char(user2)) board[getIndex(curr_row,curr_col)].setPoint((char(user2) - 32));
			return true;
		}
		else{
			return false;
		}
}
/* If the boards are the same then return true. */
char HexArray1D::operator()(int rw, int col) const{
	if(!checkInput(rw,col)) throw "Indexes are out of the range\n";
	return board[getIndex(rw,col)].getPoint();
}
/* Gets row and column (indexes) and returns the content of the appropriate cell.*/
bool HexArray1D::operator==(const AbstractHex& other) const{
	if(other.getBoardSize() != getBoardSize()) return false;

	for(int i=0; i<getBoardSize(); i++){
		for(int k=0; k < getBoardSize(); k++){
			if(board[getIndex(i,k)].getPoint() != other(i,k));
		}
	}
	return true;
}
/* Destructor */
HexArray1D::~HexArray1D(){
	free(board);
}
/* Copy Constructor */
HexArray1D::HexArray1D(const HexArray1D& obj){
int index = 0;
Cell * temp_board = (Cell*)calloc(obj.getBoardSize()*obj.getBoardSize(), sizeof(Cell));
	for(int i=0; i<obj.getBoardSize(); i++){
		for(index; index < obj.getBoardSize()+(i*obj.getBoardSize()); index++){
            temp_board[index].setRow(i);
            temp_board[index].setColumn(index);
            temp_board[index].setPoint(obj.board[index].getPoint()); 
        }
	}
	free(board);
setPlayerTurn(obj.getPlayerTurn());
setGameplayType(obj.getGameplayType());
setBoardSize(obj.getBoardSize());
board = temp_board;
}
