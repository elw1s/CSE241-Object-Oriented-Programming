#include <iostream>
#include <sstream>
#include <fstream>
#include "hex_game.h" // Library of Hex Game

using namespace std;

/*    HOMEWORK 2 FEATURES    */

/*

**************
*HEX_GAME.CPP*
**************

auto: LINE 328
decltype: LINE 329
Parameter by reference: getBoardSize() and getGameplayType functions
Constant Parameter by reference: setBoardSize(), saveGame() and loadGame() functions
Save & Load: saveGame() and loadGame() functions
Cerr: LINES 246,387,401

**************
* HEX_GAME.H *
**************

Default Arguments: playerVsBot() and playerVsPlayer() (player_turn = 0 as a default parameter) / playerTurn() (sign = player1 as a default parameter)
Enum: LINE 13 

*/

int user_move_x, user_move_y; //Variables for user's last move's x (row) and y (column)

/*Returns true when an user is winner. Otherwise it returns false.*/
bool checkWin(char board[FIXED_SIZE][FIXED_SIZE],int current_row,int current_column,int board_size,int visited[FIXED_SIZE][FIXED_SIZE],char sign)
 {

	bool win = false;
	if(sign == static_cast<char>(player1)){
		if(current_column == board_size-1){
			board[current_row][current_column] = static_cast<char>(player1U);
			return true;
		}
	}
	else if(sign == static_cast<char>(player2)){
		if(current_row == 0) {
			board[current_row][current_column] = static_cast<char>(player2U);
			return true;
		}
	}
		if((board[current_row-1][current_column+1] == sign && win != true) && visited[current_row-1][current_column+1] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(board,current_row-1,current_column+1,board_size,visited,sign);
		}
		if((board[current_row][current_column+1] == sign && win != true) && visited[current_row][current_column+1] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(board,current_row,current_column+1,board_size,visited,sign);
		}
		if((board[current_row-1][current_column] == sign && win != true) && visited[current_row-1][current_column] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(board,current_row-1,current_column,board_size,visited,sign);
		}
		if((board[current_row+1][current_column] == sign && win != true) && visited[current_row+1][current_column] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(board,current_row+1,current_column,board_size,visited,sign);
		}
		if((board[current_row][current_column-1] == sign && win != true) && visited[current_row][current_column-1] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(board,current_row,current_column-1,board_size,visited,sign);
		}
		if((board[current_row+1][current_column-1] == sign && win != true) && visited[current_row+1][current_column-1] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(board,current_row+1,current_column-1,board_size,visited,sign);	
		}
		if(win){
			if(sign == static_cast<char>(player1)) board[current_row][current_column] = static_cast<char>(player1U);
			if(sign == static_cast<char>(player2)) board[current_row][current_column] = static_cast<char>(player2U);
			return true;
		}
		else return false;
}

/*Converts column (char) to int index and returns that index. Otherwise it returns '-1' */
int charToInt(char column){

 int index = 0;
	for(char i='A'; i<='L'; i++){
		if(column == i) return index;
		index ++;
	}
	return -1;
}
/*Returns true when board[row][column] is empty. Otherwise it returns false*/
bool checkMove(char board[FIXED_SIZE][FIXED_SIZE],int column,int row){
	if(board[row][column] == static_cast<char>(empty)) return true;
	return false;
}

/*Prints board*/
void printBoard(char board[FIXED_SIZE][FIXED_SIZE],const int board_size){
	cleanConsole();
	cout << " ";
	for(int i=0; i<board_size; i++){
		cout << " " <<char('a'+i);
	}
	cout << endl;
	for(int row=0; row<board_size; row++){
		cout << row + 1;
		if(row+1 < 10) cout << " "; 
		if(row >= 1){
			for(int j=0; j<row; j++) cout << " ";
		}
		for(int column=0; column<board_size; column++){
			cout << " " << board[row][column];
		}
		cout << endl;
	}
}

/*Makes a move for bot.*/
void botTurn(char board[FIXED_SIZE][FIXED_SIZE],const int board_size){

	for(int i=0; i<board_size; i++){
		if(((user_move_x-1 >= 0) && checkMove(board,i,user_move_x)) && board[user_move_x-1][i] == static_cast<char>(player2)){
			board[user_move_x][i] = static_cast<char>(player2);
			return;
		}
	}
	for(int i = user_move_y; i<board_size; i++){
		if(checkMove(board,i,user_move_x)){
			board[user_move_x][i] = static_cast<char>(player2);
			return;
		}
	}
	for(int i = 0; i<user_move_y; i++){
		if(checkMove(board,i,user_move_x)){
			board[user_move_x][i] = static_cast<char>(player2);
			return;
		}
	}
	for(int i=0; i<board_size; i++){
		if(((user_move_x+1 < board_size) && checkMove(board,i,user_move_x)) && board[user_move_x+1][i] == static_cast<char>(player2)){
			board[user_move_x][i] = static_cast<char>(player2);
			return;
		}
	}
}

/*Checks Input of user. Returns true when input is appropriate.Otherwise it returns false*/
bool checkInput(int column, int row,const int board_size){
	if((column < 0 || column >= board_size) || (row < 0 || row >= board_size)) return false;
	else if(column == 0 || row == 0) return true;
	else return true;
}

/* Loads saved game from file_path*/
void loadGame(const string& file_path){
 
 int board_size, gameplay_type,player_turn,index = 0;
 char board[FIXED_SIZE][FIXED_SIZE];
 string str;
 stringstream ss;

 ifstream myfile;
 myfile.open(file_path);

 for(int line=1; line < 4; line++){
 	getline(myfile,str);
 	ss.str(str);
 		if(line == 1) ss >> gameplay_type;
 		else if(line == 2) ss >> board_size;
 		else if(line == 3)  ss >> player_turn;
 	ss.clear();
 }

 while(getline(myfile,str)){
 	for(int i=0; i<board_size; i++){
 		board[index][i] = str[i];
 	}
 	index ++;
 }
 myfile.close();
 
 if(gameplay_type == 1) playerVsPlayer(board,board_size,player_turn);
 else if(gameplay_type == 2) playerVsBot(board,board_size,player_turn);
 
}

/*Saves game to file_path file.*/
void saveGame(const char board[FIXED_SIZE][FIXED_SIZE], const int& board_size, const string& file_path,const int& gameplay_type,
	const int& player_turn){

 ofstream myfile;
 myfile.open(file_path);

	myfile << gameplay_type << endl;
	myfile << board_size << endl;
	myfile << player_turn << endl;

	for(int i=0; i<board_size; i++){
		for(int k=0; k<board_size; k++){
			myfile << board[i][k];  
		}
		myfile << endl;
	}
	cout << "Game has been saved!" << endl;
	myfile.close();
}

/*Makes a move for player depending player's sign. Returns true when game is finished. Otherwise it returns false. */
bool playerTurn(char board[FIXED_SIZE][FIXED_SIZE],const int board_size,int gameplay_type, char sign){
char column_c;
int row ,
column_int, 
visited[FIXED_SIZE][FIXED_SIZE];
bool win = false;
initializeVisitedArray(board_size,visited);
string str1,str2;
stringstream ss;

	while(true){
		column_int = -10;
		cin >> str1;
		if(str1 == "LOAD"){
			cin >> str2;
			loadGame(str2);
		}
		else if(str1 == "SAVE"){
			cin >> str2;
			if(sign == static_cast<char>(player1)) saveGame(board,board_size,str2,gameplay_type,0);
			else if(sign == static_cast<char>(player2)) saveGame(board,board_size,str2,gameplay_type,1);
		}
		else{
			ss.clear();
			ss.str(str1);
			ss >> column_c >> row;
			column_int = charToInt(column_c);
		}
			if(checkMove(board,column_int,row-1) && checkInput(column_int,row-1,board_size)){
					user_move_x = row-1;
					user_move_y = column_int;
					board[user_move_x][user_move_y] = sign;
					break;
			}
			else if(column_int != -10){
					cerr << "Invalid Move!" << endl;
			}
	}

	if(sign == static_cast<char>(player1)){
		for(int i=0; i<board_size; i++){
			if(board[i][0] == sign){
				if(checkWin(board,i,0,board_size,visited,sign)){
					win = true;
					break;
				}
			}
		}
	}
	else if(sign == static_cast<char>(player2)){
		for(int i=0; i<board_size; i++){
			if(board[board_size-1][i] == sign){
				if(checkWin(board,board_size-1,i,board_size,visited,sign)){
					win = true;
					break;
				}
			}
		}
	}	
	return win;
}

/*Returns true when board is full. Otherwise it returns false*/
bool isBoardFull(char board[FIXED_SIZE][FIXED_SIZE],const int board_size){

	for(int i=0; i<board_size; i++){
		for(int k=0; k<board_size; k++){
			if(board[i][k] != static_cast<char>(empty)) return false;
		}
	}
	return true;
}

/*Function for player vs player gameplay. This function will be continue until board is full and an user is winner. */
void playerVsPlayer(char board[FIXED_SIZE][FIXED_SIZE],const int board_size,int player_turn){
bool win = false;
printBoard(board,board_size);
	while(!win){
		if(player_turn % 2 == 0){
			cout << "Player1's Turn (" << static_cast<char>(player1) << "): ";
			win = playerTurn(board,board_size,1);	
		}
		else if(player_turn % 2 != 0){
			cout << "Player2's Turn (" << static_cast<char>(player2) << "): ";
			win = playerTurn(board,board_size,1,static_cast<char>(player2));
		}
		
		cleanConsole();
		printBoard(board,board_size);
		player_turn ++;
		if(isBoardFull(board,board_size)) break;
	}
	if((player_turn-1) % 2 == 0 && win){
		cout << endl << "Player1 Won!" << endl;
	}
	else if((player_turn-1) % 2 != 0 && win){
		cout << endl << "Player2 Won!" << endl;
	}
	else{
		cout << endl << "DRAW!" << endl;
	}

	restartGame();

}

/*Fill visited array with 0's.*/
void initializeVisitedArray(const int board_size,int visited[FIXED_SIZE][FIXED_SIZE]){
	for(int i=0; i<board_size; i++){
		for(int j=0; j<board_size; j++){
			visited[i][j] = 0;
		}
	}
}

/*Function for player vs bot gameplay. */
void playerVsBot(char board[FIXED_SIZE][FIXED_SIZE],const int board_size,int player_turn){
auto win = false;
decltype(player_turn) visited[12][12];
printBoard(board,board_size);
	while(!win){
		initializeVisitedArray(board_size,visited);
		if(player_turn % 2 == 0){
			cout << "Your Turn (" << static_cast<char>(player1) << "): ";
			win = playerTurn(board,board_size,2);
		}
		else if(player_turn % 2 != 0){
			botTurn(board,board_size);
			for(int i=0; i<board_size; i++){
				if(board[board_size-1][i] == static_cast<char>(player2)){
					if(checkWin(board,board_size-1,i,board_size,visited,static_cast<char>(player2))){
						win = true;
						break;
					}
				}
			}		
		}
		cleanConsole();
		printBoard(board,board_size);
		player_turn ++;
		if(isBoardFull(board,board_size)) break;
	}
	if((player_turn-1) % 2 == 0 && win){
		cout << endl << "You Won!" << endl;
	}
	else if((player_turn-1) % 2 != 0 && win){
		cout << endl << "Bot Won!" << endl;
	}
	else{
		cout << endl << "DRAW!" << endl;
	}

	restartGame();
}

/*Fills board with '.'*/
void setBoardSize(char board[FIXED_SIZE][FIXED_SIZE],const int& board_size){
	for(int row=0; row<board_size; row++){
		for(int column=0; column<board_size; column++){
			board[row][column] = static_cast<char>(empty);
		}
	}
}
/*Cleans terminal / console.*/
void cleanConsole(){
	cout << "\033c" << endl;
}
/*Gets input(Board size) from user. Returns that input*/
int getBoardSize(int& board_size){

	while(true){
	cout << "Please enter a board size (min 6x6 - max 12x12)" << endl;
	cin >> board_size;
		if(board_size <= 12 && board_size >= 6) return board_size;
		else{
		cleanConsole();
	    cerr  << "Invalid Board Size!" << endl;
		}
	}
}
/*Gets input(Gameplay Type) from user. Returns that input*/
int getGameplayType(int& gameplay_type){
	while(true){
	cout << "Gameplay Type:" << endl;
	cout  << "1. Player vs Player" << endl;
	cout << "2. Player vs Computer" << endl;
	cin >> gameplay_type;
		if(gameplay_type == 1 || gameplay_type == 2) return gameplay_type;
		else{
			cleanConsole();
			cerr  << "Invalid Gameplay Type!" << endl;
		} 
	}
}
/*Starting function for game.*/
void startGame(){
	char board[FIXED_SIZE][FIXED_SIZE];
	int board_size,gameplay_type; 
	cleanConsole();
	getBoardSize(board_size);
	cleanConsole();
	getGameplayType(gameplay_type);
	setBoardSize(board,board_size);
	printBoard(board,board_size);
	if(gameplay_type == 1) playerVsPlayer(board,board_size);
	else if(gameplay_type == 2) playerVsBot(board,board_size);
}
/*Restarts game if user selects 1. Otherwise it will exit.*/
void restartGame(){
 int choice;
	cout << endl<< "1. Restart Game" << endl << "2. Exit" << endl;
	cin >> choice;
	switch(choice){
		case 1:	
			startGame();
			break;
		case 2:
			exit(0);
	}
}




