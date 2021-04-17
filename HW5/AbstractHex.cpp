#include "AbstractHex.h"
#include <string>
#include <sstream>
using namespace HexGame;
using namespace std;

//Returns true when row and column in the range of the board
bool AbstractHex::checkInput(int rw, int col)const
{ 
    if((col < 0 || col >= getBoardSize()) || (rw < 0 || rw >= getBoardSize()))
        return false;
	else
		return true;
}

//Returns the index according to the CHAR column
int AbstractHex::convertCharToInt(char column) const{
    int index = 0;
	for(char i=0; i < getBoardSize(); i++){
		if(column == char(65+i)) return index;
		index ++;
	}
	return -1;
}
//Starts the game by calling the required functions. This function has to be called for each game.
void AbstractHex::startGame(){
inputBoardSize();
cleanConsole();
inputGameplayType();
cleanConsole();
setSize();
}

//Gets the board size from user. If it is not correct then throws an exception.
void AbstractHex::inputBoardSize(){
int size;	
	while(true){
			cout << "Please enter a board size (min 5x5)" << endl;
			cout << "\n>";
			cin >> size;
			if(size >= 5){
				setBoardSize(size);
				break;
			}
			else throw "Invalid Board Size!\n"; 
	}
}

//Gets the gameplay type from user. If it is not correct then throws an exception
void AbstractHex::inputGameplayType(){
int type;
	while(true){
			cout << "Gameplay Type:" << endl;
			cout  << "1. Player vs Player" << endl;
			cout << "2. Player vs Computer" << endl;
			cout << "\n>";
			cin >> type;
			if(type == 1 || type == 2){
			setGameplayType(type);
			break;
			} 
			else throw "Invalid Gameplay Type!\n";
	}
}

//Determines the turn depending to the number of moves.
void AbstractHex::determineTurn() const{
	if(getPlayerTurn() % 2 == 0){
		cout << "Player1's Turn (" << char(user1) << "): "; 
	}
	else if(getPlayerTurn() % 2 != 0){
		cout << "Player2's Turn (" << char(user2) << "): ";
	}
}

//Gets an input from user to make a move. Other inputs are handled in this function.
void AbstractHex::getMove(){
 string str1,str2;
 stringstream ss;
 int r,column;
 char c;
		if(getGameplayType() == 2 && getPlayerTurn() % 2 != 0){
			play();
			return;
		}
		cout << "\n>";
		cin >> str1;
		if(str1 == "LOAD"){
			cin >> str2;
			readFromFile(str2);
		}
		else if(str1 == "SAVE"){
			cin >> str2;
			writeToFile(str2);
		}
		else if(str1 == "MOVES"){
			cout << "Number of moves in current game: " << numberOfMoves() << endl;
		}
		else if(str1 == "exit"){
			cout << "Have a nice day!\n";
			exit(0);
		}
		else if(str1 == "RESET"){
			cout << "Board is reseted!\n";
			reset();
		}
		else if(str1== "LAST"){
			Cell obj = lastMove();
			cout <<"LAST MOVE: "<< obj.getPoint() << " is placed at " << obj.getRow()+1 << "(row) - " << obj.getColumn()+1 << "(column) coordinates." << endl;
		}
		else if(str1 == "OPERATOR()"){
			int rw,col;
			cin >> rw >> col;
			cout << "\nCharacter at point (" << rw << "," << col << ") is " <<"'"<<(*this)(rw,col)<< "'\n";
		}
		else if(str1 == "back"){
			throw "You cannot go back in a game\n";
		}
		else{
			ss.clear();
			ss.str(str1);
			ss >> c >> r;
            r--;
			column = convertCharToInt(c);
			if(!checkInput(r,column)) throw "Invalid entry.\n";
				if(checkMove(c,r)){
					userLastMove(r,column);
					Cell cell(r+1,column,getSign());
					play(cell);
				}
				else throw "That place is not empty!\n";
		}
}

//Returns true if the game is end. If game is ended then it will print the statements that says "X is won". 
bool AbstractHex::isEnd(){
	if(getWin()) winningStatements();
	return getWin();
}

//Returns number of moves in that game.
int AbstractHex::numberOfMoves(){
	return getPlayerTurn();
}

//Cleans the console
inline void AbstractHex::cleanConsole() const{
	cout << "\033c" << endl;
}

//Sentences that will be printed after the game is ended
void AbstractHex::winningStatements() const{
	if((getPlayerTurn()-1) % 2 == 0){
		cout << endl << "Player1 Won!" << endl;
	}
	else if(getGameplayType() == 1 && (getPlayerTurn()-1) % 2 != 0){
		cout << endl << "Player2 Won!" << endl;
	}
	else if(getGameplayType() == 2 && (getPlayerTurn()-1) % 2 != 0){
		cout << getPlayerTurn() << "-1 = " << getPlayerTurn()-1 << "||| %2 = " << getPlayerTurn()-1 % 2 << endl;
		cout << endl << "Bot Won!" << endl;
	}
}

//Returns the last move as a Cell object. Otherwise it will return an exception.
AbstractHex::Cell AbstractHex::lastMove() const{
	if(getLastRow() == -1 || getLastColumn() == -1) throw "There is not any last move!\n";
	return AbstractHex::Cell(last_moveR,last_moveC,getSign());
}

//Increases the player_turn so the turn will be the next player. Sets the sign according to that player.
void AbstractHex::nextPlayer(){
	player_turn++;
	if(getPlayerTurn() % 2 == 0) sign = char(user1);
	else if(getPlayerTurn() % 2 == 1) sign = char(user2);
}

//Initialize the visited vector with 0
void AbstractHex::initializeVisitedVector(){
	visited.resize(getBoardSize());
	for(int i=0; i<getBoardSize(); i++){
		visited[i].resize(getBoardSize());
		for(int j=0; j<getBoardSize(); j++){
			visited[i][j] = 0;
		}
	}
}

//Sets the visited vector location to 1. 
void AbstractHex::visitedLocation(int rw, int col){
	visited[rw][col] = 1;
}

//Returns the point that held in visited vector.
int AbstractHex::getVisitedLocation(int rw, int col)const{
	return visited[rw][col];
}