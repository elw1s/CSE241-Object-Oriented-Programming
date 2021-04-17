#ifndef hex_game
#define hex_game

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

enum HexBoard{empty = '.', user1 = 'x', user2 = 'o', bot = 'o'};

class Hex{
public:
 	class Cell{
		public:
			int getRow() const{return row;};
			char getColumn() const {return column;};
			char getPoint() const { return point;};
			void setRow(int rw) { row = rw; };
			void setColumn(char col) { column = col;};
			void setPoint(char poi) {point = poi;};
			explicit Cell(int , char , char);
			explicit Cell(int , int , char);
			explicit Cell();
		private:
			int row;
			char column;
			char point; 
	};

 	/* CONSTRUCTORS */
	explicit Hex(int board_size);
	explicit Hex();
	explicit Hex(int board_size, int gameplay_type);
	~Hex();
	Hex(const Hex& obj);

	/* PLAY FUNCTIONS */
	void play(Cell&);
	Cell play();

	/* MARKED CELLS COMPARING */
	static int numberOfMarkedCells();
	bool compareMarkedCells(const Hex& other) const;

	/* Play Game On Terminal */
	void playGame();
	void printBoard() const;
	void cleanConsole() const;
	void terminalOutput(bool input);
	bool playOnTerminal() const;
	bool IsGameEnded() const;

	/* SAVE & LOAD */
	void saveGame(const string& file_path);
	void loadGame(const string& file_path);

	/* OVERLOADED OPERATORS */
  	bool operator ==(const Hex& other) const;
	void operator --();
	void operator --(int ignoreMe);
	friend ostream& operator <<( ostream& outputStream,const Hex& obj);
	friend ifstream& operator >>( ifstream& fileInput,  Hex& obj);
	Hex& operator =(const Hex& rvalue);

	/* Others */
	int getTurn() const;
	int getScoreP1() const;
	int getScoreP2() const;
 private:

	/* private variables of Hex class */
	Cell ** hexCells; /* DELETE YAP UNUTMA */
	int board_size, gameplay_type; //holds size of board and type of gameplay
	bool win; //when win is true then game will be ended.
	static int playerMove; //static variable for counting moves of all active games.
	int user_move_x; //holds user's move of row.
	char user_move_y;  //holds user's move of column.
	int index_of_column;  //holds index of column
	int player_turn; //if player_turn % 2 == 0 then it is the turn of user1. Same as playerMove but this variable holds only it's own object's number of moves.
	bool play_on_terminal; //If user wants to play on terminal then this variable will be true.
	int score_p1, score_p2;
	Cell * moves;
	/* private member functions of Hex class */
	void playerVsPlayer();
	void playerVsBot();
	void movePlayer();
	Cell botTurn();
	 bool checkMove(int row, int column) const;
	 bool checkInput(int row, int column) const;
	char getSign() const;
	void setIndexOfColumn();
	bool checkWin(int current_row, int current_column, vector<vector<int> >& visited);
	bool isBoardFull() const;
	void initializeVisitedVector(vector<vector<int> >& visited);
	int charToInt(char column) const;
	void getMove();
	Cell moveBot();
	void undoLastPoint();
	void resizeMoves();
	void pushElementMoves(const Cell& element);
	void createMoves();
	
	/* LAST MOVES */
	void setUserMove(int , char);

	/* TURN */
	void nextPlayerTurn();
	void setTurn(int);

	/* Board Size */
	void setBoardSize(int);
	void resizeBoard();
	int inputBoardSize();
	void initializeBoard();
	void deleteBoard();
	int getBoardSize() const;
	
	/* Gameplay Type */
	int inputGameplayType();
	int getGameplayType() const;
	void setGameplayType(int);
	
	/*  SCORE  */
	void Score();
	void setScoreP1(int exp);
	void setScoreP2(int exp);
	bool neighbourCell(const Cell& cell);

};



#endif