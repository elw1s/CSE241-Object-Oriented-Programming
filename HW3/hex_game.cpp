#include "hex_game.h" 

int Hex::playerMove = 0; //static variable for counting marked cells in all active games.

/* Default constructor. board_size sets -1 because program will no longer waits for user's input. */
Hex::Hex(){
	board_size = -1;
	gameplay_type = -1;
}
/* Constructor with size of board */
Hex::Hex(int boardSizeInput){
	gameplay_type = -1;
	if(boardSizeInput >= 5) board_size = boardSizeInput;
	else{
		cerr << " Object is not created. Invalid Board Size. It should be between 5 and infinity." << endl;
		exit(0);
	} 
}
/* Constructor with size of board and type of gameplay. */
Hex::Hex(int boardSizeInput,int gameplayTypeInput){
	if(boardSizeInput >= 5 && (gameplayTypeInput == 1 || gameplayTypeInput == 2)){
		board_size = boardSizeInput;
		gameplay_type = gameplayTypeInput;
	}
	else{
		cerr << "Object is not created. Please attention to appropriate choices." << endl;
		exit(0);
	} 
}
/* Returns size of board */
inline int Hex::getboard_size(){
	return board_size;
}
/* Returns type of gameplay */
inline int Hex::getgameplay_type(){
	return gameplay_type;
}
/* increase player_turn by 1 when program placed a character on game board */
inline void Hex::increasePlayerTurn(){
	player_turn ++;
}
/* cleans console / terminal */
inline void Hex::cleanConsole(){
	cout << "\033c" << endl;
}
/* returns total played moves in this object */
int Hex::numOfPlayerMoves() const{
	return player_turn;
}
/* return true when marked cell's number is more than second object */
bool Hex::compareMarkedCells(Hex other) const{
	return player_turn >= other.numOfPlayerMoves();
}
/* return total marked cells in all active games. */
int Hex::numberOfMarkedCells(){
	return playerMove;
}
/* return size of board */
int Hex::BoardSize() const{
	return board_size;
}
/* sets play_on_terminal value by parameter. */
void Hex::playOnTerminal(bool input){
	play_on_terminal = input;
}
/* returns win variable (it is true when game is ended) */
bool Hex::IsGameEnded() const{
	return win;
}
/* returns sign */
char Hex::getSign(){
	if( player_turn % 2 == 0) return char(user1);
	else if( player_turn % 2 != 0) return char(user2);
	else return char(empty);
}
/* set index_of_column by calling charToInt function */
void Hex::setIndex_Of_Column(){
	index_of_column = charToInt(user_move_y);
}
/* checks the availability of place */
bool Hex::checkMove(int row, int column){
	if(hexCells[row][column].point == char(empty)) return true;
	return false;
}
/* checks the input is correct or not. */
bool Hex::checkInput(int row, int column){
	if((column < 0 || column >= board_size) || (row < 0 || row >= board_size)) return false;
	else if(column == 0 || row == 0) return true;
	else return true;
}
/* checks that game is ended or not. If someone is won then it will return true */
bool Hex::checkWin(int current_row,int current_column,vector<vector<int> >& visited){
 
	char sign = getSign();
	if(sign == char(user1)){
		if(current_column == board_size-1){
			hexCells[current_row][current_column].point = char(user1 - 32);
			return true;
		}
	}
	else if(sign == char(user2)){
		if(current_row == 0) {
			hexCells[current_row][current_column].point = char(user2 - 32);
			return true;
		}
	}
		if(current_row-1 >= 0 && current_column+1 < board_size && (hexCells[current_row-1][current_column+1].point == sign && win != true) && visited[current_row-1][current_column+1] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(current_row-1,current_column+1,visited);
		}
		if(current_column+1 < board_size && (hexCells[current_row][current_column+1].point == sign && win != true) && visited[current_row][current_column+1] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(current_row,current_column+1,visited);
		}
		if(current_row-1 >= 0 && (hexCells[current_row-1][current_column].point == sign && win != true) && visited[current_row-1][current_column] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(current_row-1,current_column,visited);
		}
		if(current_row+1 < board_size && (hexCells[current_row+1][current_column].point == sign && win != true) && visited[current_row+1][current_column] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(current_row+1,current_column,visited);
		}
		if(current_column-1 >= 0 && (hexCells[current_row][current_column-1].point == sign && win != true) && visited[current_row][current_column-1] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(current_row,current_column-1,visited);
		}
		if(current_column-1 >= 0 && current_row+1 < board_size && (hexCells[current_row+1][current_column-1].point == sign && win != true) && visited[current_row+1][current_column-1] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(current_row+1,current_column-1,visited);	
		}
		if(win){
			if(sign == char(user1)) hexCells[current_row][current_column].point = (char(user1) - 32);
			if(sign == char(user2)) hexCells[current_row][current_column].point = (char(user2) - 32);
			return true;
		}
		else{
			return false;
		}
}
/* converts char to int (it returns index (int) of column (char) ) */
int Hex::charToInt(char column){
 int index = 0;
	for(char i=0; i< board_size; i++){
		if(column == char(65+i)) return index;
		index ++;
	}
	return -1;
}
/* resize visited vector and initialize it by 0 */
void Hex::initializeVisitedVector(vector<vector<int> >& visited){
	visited.resize(board_size);
	for(int i=0; i<board_size; i++){
		visited[i].resize(board_size);
		for(int j=0; j<board_size; j++){
			visited[i][j] = 0;
		}
	}
}
/* play() functions makes move for bot. */
void Hex::play(){
 if(gameplay_type != 2){
	cerr << "Cannot use play() function while not playing with bot." << endl;
	exit(0);
 }
 else if(player_turn % 2 == 0) return;
	botTurn();
}
/* play(char,int) function makes move for player */
void Hex::play(char c, int r){

 int column = charToInt(c);
 r --;
	if(checkInput(r,column) && checkMove(r,column)){
		user_move_y = c;
 		user_move_x = r;
 		setIndex_Of_Column();
		movePlayer();
	}
	else cerr << "Invalid Move!" << endl;
}
/* This function loads game from given parameter */
void Hex::loadGame(const string& file_path){
 
 int index = 0;

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
 resizeBoardSize();
 while(getline(myfile,str)){
 	for(int i=0; i<board_size; i++){
 		hexCells[index][i].point = str[i];
 	}
 	index ++;
 }
 myfile.close();

 if(gameplay_type == 1 && play_on_terminal) playerVsPlayer();
 else if(gameplay_type == 2 && play_on_terminal) playerVsBot();
 
}
/* This function saves game to given parameter */
void Hex::saveGame(const string& file_path){

 ofstream myfile;
 myfile.open(file_path);

	myfile << gameplay_type << endl;
	myfile << board_size << endl;
	myfile << player_turn << endl;

	for(int i=0; i<board_size; i++){
		for(int k=0; k<board_size; k++){
			myfile << hexCells[i][k].point;  
		}
		myfile << endl;
	}
	cout << "Game has been saved!" << endl;
	myfile.close();
}
/* This function gets input from user. */
void Hex::getMove(){

 string str1,str2;
 stringstream ss;
 int r,column;
 char c;

	while(true){
		cin >> str1;
		if(str1 == "LOAD"){
			cin >> str2;
			loadGame(str2);
		}
		else if(str1 == "SAVE"){
			cin >> str2;
			saveGame(str2);
		}
		else{
			ss.clear();
			ss.str(str1);
			ss >> c >> r;
			r--;
			column = charToInt(c);
			if(checkInput(r,column) && checkMove(r,column)){
					user_move_y = c;
					user_move_x = r;
					setIndex_Of_Column();
					movePlayer(); 
					break;
			}
			else cerr << "Invalid Move!" << endl;
		}
			
	}
}
/* This function checks that is bot won or not. */
void Hex::botTurn(){
 vector<vector<int> > visited;
 initializeVisitedVector(visited);
 char sign = getSign();
    moveBot();
	if(sign == char(bot)){
		for(int i=0; i<board_size; i++){
			if(hexCells[board_size-1][i].point == sign){
				if(checkWin(board_size-1,i,visited)){
					break;
				}
			}
		}
	}
	playerMove++;
	player_turn++;
}
/* In this function bot makes a move into appropriate cell */
void Hex::moveBot(){
	for(int i=0; i<board_size; i++){
		if(((user_move_x-1 >= 0) && hexCells[user_move_x][i].point == char(empty)) && hexCells[user_move_x-1][i].point == char(bot)){
			hexCells[user_move_x][i].point = char(bot);
			return;
		}
	}
	for(int i = index_of_column; i<board_size; i++){
		if(hexCells[user_move_x][i].point == char(empty)){
			hexCells[user_move_x][i].point = char(bot);
			return;
		}
	}
	for(int i = 0; i<index_of_column; i++){
		if(hexCells[user_move_x][i].point == char(empty)){
			hexCells[user_move_x][i].point = char(bot);
			return;
		}
	}
	for(int i=0; i<board_size; i++){
		if(((user_move_x+1 < board_size) && hexCells[user_move_x][i].point == char(empty)) && hexCells[user_move_x+1][i].point == char(bot)){
			hexCells[user_move_x][i].point = char(bot);
			return;
		}
	}
}
/* This function place move into cell and checks that player is won or not. */
void Hex::movePlayer(){
 vector<vector<int> > visited;
 initializeVisitedVector(visited);
 char sign = getSign();
	
	hexCells[user_move_x][index_of_column].point = sign;
	if(sign == char(user1)){
		for(int i=0; i<board_size; i++){
			if(hexCells[i][0].point == sign){
				if(checkWin(i,0,visited)){
					break;
				}
			}
		}
	}
	else if(sign == char(user2)){
		for(int i=0; i<board_size; i++){
			if(hexCells[board_size-1][i].point == sign){
				if(checkWin(board_size-1,i,visited)){
					break;
				}
			}
		}
	}	
	playerMove++;
	player_turn++;
}
/* This function only called when player wants to play on terminal. Function continues until win is true. */
void Hex::playerVsBot(){
	while(!win){
		cleanConsole();
		printBoard();
		if(player_turn % 2 == 0){
			cout << "Your Turn (" << char(user1) << "): ";
			getMove();
		}
		else if(player_turn % 2 != 0){
			botTurn();
		}
		if(isBoardFull()) break;
	}
	cleanConsole();
	printBoard();
	if((player_turn-1) % 2 == 0 && win){
		cout << endl << "You Won!" << endl;
	}
	else if((player_turn-1) % 2 != 0 && win){
		cout << endl << "Bot Won!" << endl;
	}
	else{
		cout << endl << "DRAW!" << endl;
	}
}
/* This function only called when player wants to play on terminal. Function continues until win is true. */
void Hex::playerVsPlayer(){
		while(!win){
			cleanConsole();
			printBoard();
			if(player_turn % 2 == 0){
				cout << "Player1's Turn (" << char(user1) << "): ";
				getMove();
			}
			else if(player_turn % 2 != 0){
				cout << "Player2's Turn (" << char(user2) << "): ";
				getMove(); 
			}
			playerMove++;
			if(isBoardFull()) break;
		}
		cleanConsole();
		printBoard();
		if((player_turn-1) % 2 == 0 && win){
			cout << endl << "Player1 Won!" << endl;
		}
		else if((player_turn-1) % 2 != 0 && win){
			cout << endl << "Player2 Won!" << endl;
		}
		else{
			cout << endl << "DRAW!" << endl;
		}
}
/* returns false when there's a empty cell on board. */
bool Hex::isBoardFull(){
	for(int i=0; i<board_size; i++){
		for(int k=0; k<board_size; k++){
			if(hexCells[i][k].point != char(empty)) return false;
		}
	}
	return true;

}
/* This function calls appropriate functions to get input from user. User has to be called this function to set the board for the game.
If user does not call this function before the move then he/she will get "Segmentation Error"
 */
void Hex::playGame(){
	if(board_size == -1 && gameplay_type == -1){
		getBoardSize();
		cleanConsole();
		getGameplayType();
	}
	else if(board_size != -1 && gameplay_type == -1){
		getGameplayType();
	}
	resizeBoardSize();
	setBoardSize();

	if(play_on_terminal){
		if(gameplay_type == 1) playerVsPlayer();
		else if(gameplay_type == 2) playerVsBot();
    }
}
/* gets board size from user and returns it. */
int Hex::getBoardSize(){
	while(true){
		cout << "Please enter a board size (min 5x5)" << endl;
		cin >> board_size;
		if(board_size >= 5) return board_size;
		else{
		cleanConsole();
	    cerr  << "Invalid Board Size!" << endl;
		}
	}
}
/* gets type of gameplay from user and returns it. */
int Hex::getGameplayType(){
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
/* Resize hexcells vector  */
void Hex::resizeBoardSize(){
	hexCells.resize(board_size);
	for(int i=0; i<board_size; i++){
		hexCells[i].resize(board_size);
	}
}
/* sets the appropriate values into hexCells vector  */
void Hex::setBoardSize(){
	for(int i=0; i<board_size; i++){
		for(int k=0; k<board_size; k++){
			hexCells[i][k].row = i;
			hexCells[i][k].column = 65+k;
			hexCells[i][k].point = char(empty);
		}
	}
}
/* prints game board */
void Hex::printBoard(){
	cout << " ";
	for(int i=0; i<board_size; i++){
		cout << " " <<hexCells[0][i].column;
	}
	cout << endl;
	for(int i=0; i<board_size; i++){
		cout << i + 1;
		if(i+1 < 10) cout << " "; 
		if(i >= 1){
			for(int j=0; j<i; j++) cout << " ";
		}
		for(int k=0; k<board_size; k++){
			cout << " " << hexCells[i][k].point;
		}
		cout << endl;
	}
}
