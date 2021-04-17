#include <iostream>
#include "hex_game.h" // Library of Hex Game

using namespace std;

#define FIXED_SIZE 12 //Fixed size for board.

int user_move_x, user_move_y; //Variables for user's last move's x (row) and y (column)


/*Returns true when an user is winner. Otherwise it returns false.*/

bool checkWin(char board[FIXED_SIZE][FIXED_SIZE],int current_row,int current_column,int board_size,int visited[FIXED_SIZE][FIXED_SIZE],char sign)
{

	bool win = false;
	if(sign == 'x'){
		if(current_column == board_size-1){
			board[current_row][current_column] = 'X';
			return true;
		}
	}
	else if(sign == 'o'){
		if(current_row == 0) {
			board[current_row][current_column] = 'O';
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
			if(sign == 'x') board[current_row][current_column] = 'X';
			if(sign == 'o') board[current_row][current_column] = 'O';
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
	if(board[row][column] == '.') return true;
	return false;
}

/*Prints board*/
void printBoard(char board[FIXED_SIZE][FIXED_SIZE], int board_size){
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
void botTurn(char board[FIXED_SIZE][FIXED_SIZE], int board_size){

	for(int i=0; i<board_size; i++){
		if(((user_move_x-1 >= 0) && checkMove(board,i,user_move_x)) && board[user_move_x-1][i] == 'o'){
			board[user_move_x][i] = 'o';
			return;
		}
	}
	for(int i = user_move_y; i<board_size; i++){
		if(checkMove(board,i,user_move_x)){
			board[user_move_x][i] = 'o';
			return;
		}
	}
	for(int i = 0; i<user_move_y; i++){
		if(checkMove(board,i,user_move_x)){
			board[user_move_x][i] = 'o';
			return;
		}
	}
	for(int i=0; i<board_size; i++){
		if(((user_move_x+1 < board_size) && checkMove(board,i,user_move_x)) && board[user_move_x+1][i] == 'o'){
			board[user_move_x][i] = 'o';
			return;
		}
	}
}

/*Checks Input of user. Returns true when input is appropriate.Otherwise it returns false*/
bool checkInput(int column, int row,int board_size){
	if((column < 0 || column >= board_size) || (row < 0 || row >= board_size)) return false;
	else if(column == 0 || row == 0) return true;
	else return true;
}
/*Makes a move for player depending player's sign. Returns true when game is finished. Otherwise it returns false. */
bool playerTurn(char sign,char board[FIXED_SIZE][FIXED_SIZE], int board_size){
char column_c;
int row ,
column_int, 
visited[FIXED_SIZE][FIXED_SIZE];
bool win;
initializeVisitedArray(board_size,visited);

	while(true){
				cin >> column_c >> row;
				column_int = charToInt(column_c);
				if(checkMove(board,column_int,row-1) && checkInput(column_int,row-1,board_size)){
					user_move_x = row-1;
					user_move_y = column_int;
					board[user_move_x][user_move_y] = sign;
					break;
				}
				else{
					cerr << "Invalid Move!" << endl;
				}
			}
	if(sign == 'x'){
		for(int i=0; i<board_size; i++){
			if(board[i][0] == sign){
				if(checkWin(board,i,0,board_size,visited,sign)){
					win = true;
					break;
				}
			}
		}
	}
	else if(sign == 'o'){
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
bool isBoardFull(char board[FIXED_SIZE][FIXED_SIZE],int board_size){

	for(int i=0; i<board_size; i++){
		for(int k=0; k<board_size; k++){
			if(board[i][k] != '.') return false;
		}
	}
	return true;
}

/*Function for player vs player gameplay. This function will be continue until board is full and an user is winner. */
void playerVsPlayer(char board[FIXED_SIZE][FIXED_SIZE], int board_size){
int player_turn = 0;
bool win = false;

	while(!win){
		if(player_turn % 2 == 0){
			cout << "Player1's Turn (x): ";
			win = playerTurn('x',board,board_size);	
		}
		else if(player_turn % 2 != 0){
			cout << "Player2's Turn (o): ";
			win = playerTurn('o',board,board_size);
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
void initializeVisitedArray(int board_size,int visited[FIXED_SIZE][FIXED_SIZE]){
	for(int i=0; i<board_size; i++){
		for(int j=0; j<board_size; j++){
			visited[i][j] = 0;
		}
	}
}

/*Function for player vs bot gameplay. */
void playerVsBot(char board[FIXED_SIZE][FIXED_SIZE], int board_size){
bool win = false;
int player_turn = 0,
visited[12][12];

	while(!win){
		initializeVisitedArray(board_size,visited);

		if(player_turn % 2 == 0){
			cout << "Your Turn (x): ";
			win = playerTurn('x',board,board_size);
		}
		else if(player_turn % 2 != 0){
			botTurn(board,board_size);
			for(int i=0; i<board_size; i++){
				if(board[board_size-1][i] == 'o'){
					if(checkWin(board,board_size-1,i,board_size,visited,'o')){
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
void setBoardSize(char board[FIXED_SIZE][FIXED_SIZE], int board_size){
	for(int row=0; row<board_size; row++){
		for(int column=0; column<board_size; column++){
			board[row][column] = '.';
		}
	}
}
/*Cleans terminal / console.*/
void cleanConsole(){
	cout << "\033c" << endl;
}
/*Gets input(Board size) from user. Returns that input*/
int getBoardSize(){
	int board_size;
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
int getGameplayType(){
	int gameplay_type;
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
board_size = getBoardSize();
cleanConsole();
gameplay_type = getGameplayType();
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




