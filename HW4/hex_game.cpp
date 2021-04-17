#include "hex_game.h" 

int Hex::playerMove = 0; //static variable for counting marked cells in all active games.

/* HEX CONSTRUCTORS */
Hex::Hex(){
	setBoardSize(-1);
	setGameplayType(-1);
	setTurn(0);
	win = false;
	setScoreP1(0);
	setScoreP2(0);
	createMoves();
	terminalOutput(false);
}
Hex::Hex(int boardSizeInput){
	setGameplayType(-1);
	if(boardSizeInput >= 5) setBoardSize(boardSizeInput);
	else{
		cerr << " Object is not created. Invalid Board Size. It should be between 5 and infinity." << endl;
		exit(0);
	} 
	setTurn(0);
	win = false;
	setScoreP1(0);
	setScoreP2(0);
	createMoves();
	terminalOutput(false);
}
Hex::Hex(int boardSizeInput,int gameplayTypeInput){
	if(boardSizeInput >= 5 && (gameplayTypeInput == 1 || gameplayTypeInput == 2)){
		setBoardSize(boardSizeInput);
		setGameplayType(gameplayTypeInput);
	}
	else{
		cerr << "Object is not created. Please attention to appropriate choices." << endl;
		exit(0);
	}
	setTurn(0); 
	win = false;
	setScoreP1(0);
	setScoreP2(0);
	createMoves();
	terminalOutput(false);
}


/* CELL CONSTRUCTORS */

Hex::Cell::Cell(int rw, char col, char poi){
	Hex::Cell::row = rw;
	Hex::Cell::column = col;
	Hex::Cell::point = poi;
}
Hex::Cell::Cell(int rw, int col, char poi){
	Hex::Cell::row = rw;
	Hex::Cell::column = (char) 'A' + col;
	Hex::Cell::point = poi;
}
Hex::Cell::Cell(){ /* Intentionally Empty */ }

/* THE BIG THREE */

Hex::Hex(const Hex& obj){

setTurn(obj.getTurn());
delete[] moves;
moves = new Cell[getTurn()+1];

for(int i=0; i < getBoardSize(); i++) delete[] hexCells[i];
	delete[] hexCells;

	setBoardSize(obj.getBoardSize());
	hexCells = new Cell*[getBoardSize()];
		for(int i=0; i < getBoardSize(); i++) hexCells[i] = new Cell[getBoardSize()];

		if(moves == nullptr || hexCells == nullptr) {
			cerr << "Insufficient memory!" << endl;
			exit(1);
		}

	for(int i = 0; i < getTurn(); i++) moves[i] = obj.moves[i];
	for(int i = 0; i < getBoardSize(); i++) hexCells[i] = obj.hexCells[i];


setGameplayType(obj.getGameplayType());
win = obj.win;
setScoreP1(obj.getScoreP1());
setScoreP2(obj.getScoreP2());
play_on_terminal = obj.play_on_terminal;
user_move_x = obj.user_move_x;
user_move_y = obj.user_move_y;
index_of_column = obj.index_of_column;
}
Hex& Hex::operator =(const Hex& rvalue){

setTurn(rvalue.getTurn());

	if(this != &rvalue){
		delete []moves;
		moves = new Cell[getTurn()+1];

		for(int i=0; i < getBoardSize(); i++) delete[] hexCells[i];
		
		delete[] hexCells;

		setBoardSize(rvalue.getBoardSize());
		hexCells = new Cell*[getBoardSize()];
			for(int i=0; i < getBoardSize(); i++) hexCells[i] = new Cell[getBoardSize()];

			if(moves == nullptr || hexCells == nullptr) {
				cerr << "Insufficient memory!" << endl;
				exit(1);
			}
	}
		for(int i = 0; i < getTurn(); i++) moves[i] = rvalue.moves[i];
		for(int i = 0; i < getBoardSize(); i++) hexCells[i] = rvalue.hexCells[i];


setGameplayType(rvalue.getGameplayType());
win = rvalue.win;
setScoreP1(rvalue.getScoreP1());
setScoreP2(rvalue.getScoreP2());
play_on_terminal = rvalue.play_on_terminal;
user_move_x = rvalue.user_move_x;
user_move_y = rvalue.user_move_y;
index_of_column = rvalue.index_of_column;

return *this;
}
Hex::~Hex(){  
	 delete[] moves; 
}

/* INLINE FUNCTIONS */

inline int Hex::getGameplayType() const{
	return gameplay_type;
}
inline void Hex::cleanConsole() const{
	cout << "\033c" << endl;
}
inline int Hex::getTurn() const{
	return player_turn;
}
inline void Hex::nextPlayerTurn(){
	player_turn ++;
}

/* setter for player_turn */
void Hex::setTurn(int turn){
	player_turn = turn;
}

/* SCORE FUNCTIONS (P1 = user1 , P2 = user2) */

int Hex::getScoreP1() const{
	return score_p1;
}
int Hex::getScoreP2() const{
	return score_p2;
}
void Hex::setScoreP1(int exp){
	score_p1 = exp;

}
void Hex::setScoreP2(int exp){
	score_p2 = exp;
}
/* This function calculates score each round */
void Hex::Score(){

bool found;
	if(getSign() == char(user1)){
		setScoreP1(0);
		for(int i = 0; i < getBoardSize(); i++){
			found = false;
			for(int k = 0; k < getBoardSize(); k++){
				if(hexCells[k][i].getPoint() == char(user1) && found) setScoreP1(getScoreP1() + 1);
				if(neighbourCell(hexCells[k][i]) && found) setScoreP1(getScoreP1() + 4);			
				if(hexCells[k][i].getPoint() == char(user1) && !found){
					if(i < getBoardSize() / 2) setScoreP1(getScoreP1() + (2 * (getBoardSize() - i - 1)));
					else if( i >= getBoardSize() / 2) setScoreP1(getScoreP1() + (2 * i));
					found = true;
				}
			}
		}
	}
	else{
		setScoreP2(0);
		for(int i = 0; i < getBoardSize(); i++){
			found = false;
			for(int k = 0; k < getBoardSize(); k++){
				if(hexCells[i][k].getPoint() == char(user2) && found) setScoreP2(getScoreP2() + 1);
				if(neighbourCell(hexCells[i][k]) && found) setScoreP2(getScoreP2() + 4);
				if(hexCells[i][k].getPoint() == char(user2) && !found){
					if(i < getBoardSize() / 2) setScoreP2(getScoreP2() + (2 * (getBoardSize() - i - 1)));
					else if( i >= getBoardSize() / 2) setScoreP2(getScoreP2() + (2 * i));
					found = true;
				}
			}
		}
	}
}
/* Returns true if appropriate point finds by program */
bool Hex::neighbourCell(const Cell& cell){
	if(getSign() == char(user1)){
		if(cell.getRow() - 1 >= 0 && (cell.getColumn() - 'A') + 1 < getBoardSize() && getSign() == hexCells[cell.getRow() - 1][(cell.getColumn() - 'A') + 1].getPoint())
			return true;
		else if((cell.getColumn() - 'A') + 1  && getSign() == hexCells[cell.getRow()][(cell.getColumn() - 'A') + 1].getPoint())
			return true;	
	}
	else if(getSign() == char(user2)){
		if(cell.getRow() + 1 < getBoardSize() && (cell.getColumn() - 'A') - 1 >= 0 && getSign() == hexCells[cell.getRow() + 1][(cell.getColumn() - 'A') - 1].getPoint())
			return true;
		else if(cell.getRow() + 1 < getBoardSize()  && getSign() == hexCells[cell.getRow() + 1][(cell.getColumn() - 'A')].getPoint())
			return true;
	}
return false;
}


/* MARKED CELLS */

bool Hex::compareMarkedCells(const Hex& other) const{
	return getTurn() >= other.getTurn();
}
bool Hex::operator ==(const Hex& other) const{
	return getTurn() >= other.getTurn();
}
int Hex::numberOfMarkedCells(){
	return playerMove;
}

/* BOARD SIZE */

int Hex::getBoardSize() const{
	return board_size;
}
void Hex::setBoardSize(int size){
	board_size = size;
}
/* Gets input from user for board_size */
int Hex::inputBoardSize(){
int size;	
	while(true){
		cout << "Please enter a board size (min 5x5)" << endl;
		cin >> size;
		if(size >= 5){
			setBoardSize(size);
			return size;
		} 
		else{
		cleanConsole();
	    cerr  << "Invalid Board Size!" << endl;
		}
	}
}

/* GAMEPLAY TYPE */

/* Gets input from user for gameplay_type */
int Hex::inputGameplayType(){
	int type;
	while(true){
	cout << "Gameplay Type:" << endl;
	cout  << "1. Player vs Player" << endl;
	cout << "2. Player vs Computer" << endl;
	cin >> type;
		if(type == 1 || type == 2){
			setGameplayType(type);
			return type;
		} 
		else{
			cleanConsole();
			cerr  << "Invalid Gameplay Type!" << endl;
		} 
	}
}
void Hex::setGameplayType(int type){
	gameplay_type = type;
}

/* PRINTING ON TERMINAL*/

/* terminalOutput function determines that output will be on terminal or not. */
void Hex::terminalOutput(bool input){
	play_on_terminal = input;
}
bool Hex::playOnTerminal() const{
	return play_on_terminal;
}
/* This functions prints board with scores , columns and rows. */
void Hex::printBoard() const{
	if(getGameplayType() == 1){
        cout << "Player1's Score: " << getScoreP1() << " points" << "  |  Player2's Score: " << getScoreP2() << " points";
    }
    else{
        cout << "Player's Score: " << getScoreP1() << " points";
    }

    cout << "\n\n ";
    for(int i=0; i<getBoardSize(); i++){
        cout << " " <<hexCells[0][i].getColumn();
    }
    cout << endl;
    cout << (*this);
}

/* SAVE & LOAD */

void Hex::loadGame(const string& file_path){
ifstream myfile;
 myfile.open(file_path);
	myfile >> (*this);
 myfile.close();

 if(getGameplayType() == 1 && playOnTerminal()) playerVsPlayer();
 else if(getGameplayType() == 2 && playOnTerminal()) playerVsBot();
 
}
void Hex::saveGame(const string& file_path){
ofstream myfile;
 myfile.open(file_path);

	myfile << getGameplayType() << endl;
    myfile << getBoardSize() << endl;
    myfile << getTurn() << endl;
	myfile << getScoreP1() << endl;
	myfile << getScoreP2() << endl;

	for(int i=0; i < getTurn(); i++){
		myfile << moves[i].getRow();
		myfile << " " << moves[i].getColumn() << endl;
	}

    myfile << (*this);

	cout << "Game has been saved!" << endl;
	myfile.close();
}

/* UNDO */

/* This function adds element to the last of moves array */
void Hex::pushElementMoves(const Cell& element){

Cell * temp = new Cell[getTurn() + 1];

	for(int i=0; i < getTurn(); i++){
		temp[i] = moves[i];
	}
	temp[getTurn()] = element;
	resizeMoves();
	for(int i=0;  i <= getTurn(); i++){
		moves[i] = temp[i];
	}

}
/* This function resize moves array */
void Hex::resizeMoves(){
	delete []moves;
	
	createMoves();

}
/* This function creates a new moves array without deleting anything */
void Hex::createMoves(){
	moves = new Cell[getTurn() + 1];
	if(moves == nullptr){
		cerr << "Insufficient memory!" << endl;
		exit(1);
	}
}
/* UNARY OVERLOADED OPERATORS FOR UNDO */
void Hex::operator --(){ //prefix
 if(getTurn() == 0) {
	cerr << "You must make a move to undo!" << endl;
	return;
 }
	if(getGameplayType() == 2){
		for(int i=0; i<2; i++) undoLastPoint();
		setUserMove(moves[getTurn()-1].getRow() , moves[getTurn()-1].getColumn());
	}
	else undoLastPoint();
}
void Hex::operator --(int ignoreMe){ //postfix
if(getTurn() == 0) {
	cerr << "You must make a move to undo!" << endl;
	return;
}
	if(getGameplayType() == 2){
		for(int i=0; i<2; i++) undoLastPoint();
		setUserMove(moves[getTurn()-1].getRow() , moves[getTurn()-1].getColumn());
	}
	else undoLastPoint();
}
/* This function removes last point of moves array */
void Hex::undoLastPoint(){
int rw = moves[getTurn() - 1].getRow();
int col = moves[getTurn() - 1].getColumn() - 'A';
hexCells[rw][col].setPoint(char(empty));

setTurn(getTurn() - 1);
}

/* INSERTION - EXTRACTION OPERATOR OVERLOADING */

/* This operator prints board without score and columns.  */
ostream& operator <<(ostream& outputStream, const Hex& obj){ //used for both file output and console output.
	for(int i=0; i<obj.getBoardSize(); i++){
        outputStream << i + 1;
        if(i+1 < 10) outputStream << " "; 
        if(i >= 1){
            for(int j=0; j<i; j++) outputStream << " ";
        }
        for(int k=0; k<obj.getBoardSize(); k++){
              outputStream << " " << obj.hexCells[i][k].getPoint();  
        }
            outputStream << endl;
    }

return outputStream;
}
/* This operator reads ifstream typed stream and loads saved game. */
ifstream& operator >>( ifstream& fileInput, Hex& obj){
int type , size, turn , sco1 , sco2;

 string str;
 stringstream ss;
 
 for(int line=1; line < 6; line++){
 	getline(fileInput,str);
 	ss.str(str);
 		if(line == 1) ss >> type;
 		else if(line == 2) ss >> size;
 		else if(line == 3)  ss >> turn;
		else if(line == 4) ss >> sco1;
		else if(line == 5) ss >> sco2;
 	ss.clear();
 }

 obj.setGameplayType(type);
 obj.deleteBoard();
 obj.setBoardSize(size);
 obj.resizeBoard();
 obj.setTurn(turn);
 obj.setScoreP1(sco1);
 obj.setScoreP2(sco2);

 if(obj.getTurn() == 0) obj.createMoves();
 else obj.resizeMoves();

 for(int i = 0; i < obj.getTurn(); i++){
	getline(fileInput,str);
	if(str[1] == ' '){
		obj.moves[i].setRow(str[0] - '0');
		obj.moves[i].setColumn(str[2]);
	}
	else if(str[1] != ' '){
		obj.moves[i].setRow(((str[0] - '0') * 10 + (str[1] - '0')));
		obj.moves[i].setColumn(str[3]);
	}
 }

int index = 0;
 while(getline(fileInput,str)){
    if(str[1] == ' '){
        for(int i=((str[0] - '0') + 2) , j = 0; j < obj.getBoardSize() && index < obj.getBoardSize(); i+=2 , j++){
            obj.hexCells[index][j].setPoint(str[i]);
        }
    }
    else if(str[1] != ' '){
        for(int j(0) , i=((str[0] - '0') * 10) + (str[1] - '0') + 2; j < obj.getBoardSize() && index < obj.getBoardSize(); i+=2 , j++){
            obj.hexCells[index][j].setPoint(str[i]);
        }
    }
 	index ++;
 }
 return fileInput;
} 

/* INPUT ERROR HANDLING */

bool Hex::checkMove(int row, int column) const{
	if(hexCells[row][column].getPoint() == char(empty)) return true;
	return false;
}
bool Hex::checkInput(int row, int column) const{
	if((column < 0 || column >= getBoardSize()) || (row < 0 || row >= getBoardSize())) return false;
	else if(column == 0 || row == 0) return true;
	else return true;
}

/* MAIN GAME FUNCTIONS */

/* This function is the main function of the Player Vs Bot games. */
void Hex::playerVsBot(){
	while(!IsGameEnded()){
		cleanConsole();
		printBoard();
		if(getTurn() % 2 == 0){
			cout << "Your Turn (" << char(user1) << "): ";
			getMove();
		}
		else if(getTurn() % 2 != 0){
			botTurn();
		}
		if(isBoardFull()) break;
	}
	cleanConsole();
	printBoard();
	if((getTurn()-1) % 2 == 0 && IsGameEnded()){
		cout << endl << "You Won!" << endl;
	}
	else if((getTurn()-1) % 2 != 0 && IsGameEnded()){
		cout << endl << "Bot Won!" << endl;
	}
	else{
		cout << endl << "DRAW!" << endl;
	}
}
/* This function is the main function of the Player Vs Player games. */
void Hex::playerVsPlayer(){
		while(!IsGameEnded()){
			cleanConsole();
			printBoard();
			if(getTurn() % 2 == 0){
				cout << "Player1's Turn (" << char(user1) << "): ";
				getMove();
			}
			else if(getTurn() % 2 != 0){
				cout << "Player2's Turn (" << char(user2) << "): ";
				getMove(); 
			}
			playerMove++;
			if(isBoardFull()) break;
		}
		cleanConsole();
		printBoard();
		if((getTurn()-1) % 2 == 0 && IsGameEnded()){
			cout << endl << "Player1 Won!" << endl;
		}
		else if((getTurn()-1) % 2 != 0 && IsGameEnded()){
			cout << endl << "Player2 Won!" << endl;
		}
		else{
			cout << endl << "DRAW!" << endl;
		}
}
/* This function is the main function for all games. The whole game starts with this function. */
void Hex::playGame(){
	//cleanConsole();
	if(getBoardSize() == -1 && getGameplayType() == -1){
		inputBoardSize();
	//	cleanConsole();
		inputGameplayType();
	}
	else if(getBoardSize() != -1 && getGameplayType() == -1){
		inputGameplayType();
	}
	deleteBoard();
	resizeBoard();
	initializeBoard();

	if(playOnTerminal()){
		if(getGameplayType() == 1) playerVsPlayer();
		else if(getGameplayType() == 2) playerVsBot();
    }
}

/* GETTING MOVES FROM USER */

/* This function gets move from user on terminal */
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
			break;
		}
		else if(str1 == "SAVE"){
			cin >> str2;
			saveGame(str2);
			break;
		}
		else if(str1 == "UNDO"){
			(*this)--;
			Score();
			break;
		}
		else{
			ss.clear();
			ss.str(str1);
			ss >> c >> r;
			r--;
			column = charToInt(c);
			if(checkInput(r,column) && checkMove(r,column)){
					setUserMove(r,c);
					movePlayer(); 
					break;
			}
			else cerr << "Invalid Move!" << endl;
		}
			
	}
}
/* This function plays for bot and returns that cell's position*/
Hex::Cell Hex::play(){

 if(getGameplayType() != 2){
	cerr << "Cannot use play() function while not playing with bot." << endl;
	exit(0);
 }
 else if(getTurn() % 2 == 0){
	 cerr << "Player's turn. Bot can not play!" << endl;
	 exit(0);
 } 

	Cell temp = botTurn();
	return temp;
}
/* This function plays for player. */
void Hex::play(Cell& new_point){

 int column = charToInt(new_point.getColumn());
 new_point.setRow(new_point.getRow() - 1); 
	if(checkInput(new_point.getRow(),column) && checkMove(new_point.getRow(),column)){
		setUserMove(new_point.getRow() , new_point.getColumn());
		movePlayer();
	}
	else cerr << "Invalid Move!" << endl;
}

/* MOVE PLAYER & BOT */

/* This function is the main function of BOT. */
Hex::Cell Hex::botTurn(){
 vector<vector<int> > visited;
 initializeVisitedVector(visited);
    Cell temp = moveBot();
	pushElementMoves(temp);
	if(getSign() == char(bot)){
		for(int i=0; i<getBoardSize(); i++){
			if(hexCells[getBoardSize()-1][i].getPoint() == getSign()){
				if(checkWin(getBoardSize()-1,i,visited)){
					break;
				}
			}
		}
	}
	playerMove++;
	nextPlayerTurn();

	return temp;
}
/* This function moves bot. */
Hex::Cell Hex::moveBot(){

	for(int i=0; i<getBoardSize(); i++){
		if(((user_move_x-1 >= 0) && hexCells[user_move_x][i].getPoint() == char(empty)) && hexCells[user_move_x-1][i].getPoint() == char(bot)){
			hexCells[user_move_x][i].setPoint(char(bot));
			return Cell(user_move_x , i , char(bot));
		}
	}
	for(int i = index_of_column; i<getBoardSize(); i++){
		if(hexCells[user_move_x][i].getPoint() == char(empty)){
			hexCells[user_move_x][i].setPoint(char(bot));
			return Cell(user_move_x , i , char(bot));
		}
	}
	for(int i = 0; i<index_of_column; i++){
		if(hexCells[user_move_x][i].getPoint() == char(empty)){
			hexCells[user_move_x][i].setPoint(char(bot));
			return Cell(user_move_x , i , char(bot));
		}
	}
	for(int i=0; i<getBoardSize(); i++){
		if(((user_move_x+1 < getBoardSize()) && hexCells[user_move_x][i].getPoint() == char(empty)) && hexCells[user_move_x+1][i].getPoint() == char(bot)){
			hexCells[user_move_x][i].setPoint(char(bot));
			return Cell(user_move_x , i , char(bot));
		}
	}
	Cell tmp;
	return tmp;
}
/* This function moves player and is the main function of PLAYER */
void Hex::movePlayer(){
 vector<vector<int> > visited;
 initializeVisitedVector(visited);

	hexCells[user_move_x][index_of_column].setPoint(getSign());
	pushElementMoves(Cell(user_move_x,index_of_column,getSign()));
	Score();
	if(getSign() == char(user1)){
		for(int i=0; i<getBoardSize(); i++){
			if(hexCells[i][0].getPoint() == getSign()){
				if(checkWin(i,0,visited)){
					 setScoreP1(getScoreP1() + getBoardSize() * (getTurn() / 2)); 
					break;
				}
			}
		}
	}
	else if(getSign() == char(user2)){
		for(int i=0; i<getBoardSize(); i++){
			if(hexCells[getBoardSize()-1][i].getPoint() == getSign()){
				if(checkWin(getBoardSize()-1,i,visited)){
					 setScoreP2(getScoreP2() + getBoardSize() * 4 ); 
					break;
				}
			}
		}
	}	
	playerMove++;
	nextPlayerTurn();
}

/* BOARD */

/* Deletes hexCells array */
void Hex::deleteBoard(){
	if(getTurn() != 0){
		for(int i=0; i < getBoardSize(); i++) delete[] hexCells[i];
		delete[] hexCells;
	}
}
/* Returns true when board is full */
bool Hex::isBoardFull() const{
	for(int i=0; i<getBoardSize(); i++){
		for(int k=0; k<getBoardSize(); k++){
			if(hexCells[i][k].getPoint() != char(empty) || getTurn() == 0) return false;
		}
	}
	return true;

}
/* This function resizes hexCell array without deleting anything.  */
void Hex::resizeBoard(){
	hexCells = new Cell*[getBoardSize()];
	if(hexCells == nullptr){
		cerr << "Insufficient memory!" << endl;
		exit(1);
	}
	for(int i=0; i < getBoardSize(); i++){
		hexCells[i] = new Cell[getBoardSize()];
		for(int k=0; k<getBoardSize(); k++){
			hexCells[i][k].setRow(i);
			hexCells[i][k].setColumn(65+k);
		}
	}
}
/* This function sets all positions to empty. */
void Hex::initializeBoard(){
	for(int i=0; i<getBoardSize(); i++){
		for(int k=0; k<getBoardSize(); k++){
			hexCells[i][k].setPoint(char(empty));
		}
	}
}

/* CHECK BOARD */

/* Returns true when game is ended */
bool Hex::IsGameEnded() const{
	return win;
}
/* Returns true when game is finished by player or bot. */
bool Hex::checkWin(int current_row,int current_column,vector<vector<int> >& visited){
 
	if(getSign() == char(user1)){
		if(current_column == getBoardSize()-1){
			hexCells[current_row][current_column].setPoint(char(user1 - 32));
			return true;
		}
	}
	else if(getSign() == char(user2)){
		if(current_row == 0) {
			hexCells[current_row][current_column].setPoint(char(user2 - 32));
			return true;
		}
	}
		if(current_row-1 >= 0 && current_column+1 < getBoardSize() && (hexCells[current_row-1][current_column+1].getPoint() == getSign() && IsGameEnded() != true) && visited[current_row-1][current_column+1] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(current_row-1,current_column+1,visited);
		}
		if(current_column+1 < getBoardSize() && (hexCells[current_row][current_column+1].getPoint() == getSign() && IsGameEnded() != true) && visited[current_row][current_column+1] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(current_row,current_column+1,visited);
		}
		if(current_row-1 >= 0 && (hexCells[current_row-1][current_column].getPoint() == getSign() && IsGameEnded() != true) && visited[current_row-1][current_column] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(current_row-1,current_column,visited);
		}
		if(current_row+1 < getBoardSize() && (hexCells[current_row+1][current_column].getPoint() == getSign() && IsGameEnded() != true) && visited[current_row+1][current_column] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(current_row+1,current_column,visited);
		}
		if(current_column-1 >= 0 && (hexCells[current_row][current_column-1].getPoint() == getSign() && IsGameEnded() != true) && visited[current_row][current_column-1] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(current_row,current_column-1,visited);
		}
		if(current_column-1 >= 0 && current_row+1 < getBoardSize() && (hexCells[current_row+1][current_column-1].getPoint() == getSign() && IsGameEnded() != true) && visited[current_row+1][current_column-1] != 1){
			visited[current_row][current_column] = 1;
			win = checkWin(current_row+1,current_column-1,visited);	
		}
		if(IsGameEnded()){
			if(getSign() == char(user1)) hexCells[current_row][current_column].setPoint((char(user1) - 32));
			if(getSign() == char(user2)) hexCells[current_row][current_column].setPoint((char(user2) - 32));
			return true;
		}
		else{
			return false;
		}
}

/* Returns sign */
char Hex::getSign() const{
	if( getTurn() % 2 == 0) return char(user1);
	else if( getTurn() % 2 != 0) return char(user2);
	else return char(empty);
}
/* Sets index_of_column depending on user's last move's column */
void Hex::setIndexOfColumn(){
	index_of_column = charToInt(user_move_y);
}
/* Returns index of parameter */
int Hex::charToInt(char column) const{
 int index = 0;
	for(char i=0; i< getBoardSize(); i++){
		if(column == char(65+i)) return index;
		index ++;
	}
	return -1;
}
/* Inıtıalizes visited vector */
void Hex::initializeVisitedVector(vector<vector<int> >& visited){
	visited.resize(getBoardSize());
	for(int i=0; i<getBoardSize(); i++){
		visited[i].resize(getBoardSize());
		for(int j=0; j<getBoardSize(); j++){
			visited[i][j] = 0;
		}
	}
}
/* Sets user move's variables */
void Hex::setUserMove(int x , char y){
	user_move_x = x;
	user_move_y = y;
	setIndexOfColumn();
}
