#ifndef ABSTRACTHEX
#define ABSTRACTHEX
#include <iostream>
#include <vector>

/* Header file for AbstractHex */

namespace HexGame{ //Namespace

    enum HexBoard{empty = '.', user1 = 'x', user2 = 'o', bot = 'o'};

    class AbstractHex{

        public:
            class Cell{
                public:
                    explicit Cell(){};
                    explicit Cell(int rw,int col) : row(rw-1) , column(col){} //INTENTIONALLY EMPTY
                    explicit Cell(int rw,int col, char p) : row(rw-1) , column(col) , point(p){} //INTENTIONALLY EMPTY
                    int getRow()const {return row;};
                    int getColumn()const {return column;};
                    void setRow(int index) {row = index;};
                    void setColumn(int index) {column = index;};
                    char getPoint()const {return point;};
                    void setPoint(char param) {point = param;};    
                private:
                    int row;
                    int column;
                    char point;
            };
            /* Virtual functions */
            virtual void moveBot() = 0;
            virtual void print() const = 0;
            virtual void readFromFile(std::string& file_path) = 0;
            virtual void writeToFile(std::string& file_path) const = 0;
            virtual void reset() = 0;
            virtual void setSize() = 0;
            virtual void play() = 0;
            virtual void play(const Cell& move) = 0;
            virtual char operator()(int rw, int col) const = 0;
            virtual bool checkWin(int curr_row,int curr_col) = 0;
            virtual bool checkMove(char c , int rw) const = 0;
            virtual bool operator==(const AbstractHex& other)const = 0;
            /* Functions that are common for 3 classes */
            bool isEnd();
            int numberOfMoves();
            void determineTurn() const;
            void getMove();
            Cell lastMove() const;
            void startGame();
            void inputBoardSize();
            void inputGameplayType();
            void winningStatements() const;
            void userLastMove(int row, int col) {last_moveR=row; last_moveC=col;};
            bool checkInput(int rw, int col) const;
            int convertCharToInt(char column) const;
            void cleanConsole() const;
            int getBoardSize()const {return board_size;};
            void setBoardSize(int param){board_size = param;};
            int getGameplayType()const {return gameplay_type;};
            void setGameplayType(int param){gameplay_type = param;};
            int getPlayerTurn()const {return player_turn;};
            void setPlayerTurn(int turn){player_turn = turn;};
            void nextPlayer();
            bool getWin()const {return win;};
            void setWin(int param){win = param;};
            char getSign()const{return sign;};
            void initializeVisitedVector();
            int getLastRow()const{return last_moveR;};
            void setLastRow(int rw){last_moveR = rw;};
            void setLastColumn(int col){last_moveC = col;};
            int getLastColumn()const{return last_moveC;};
            void visitedLocation(int , int);
            int getVisitedLocation(int , int)const;
        private:
            int board_size , gameplay_type;
            bool win = false;
            int player_turn = 0;
            int last_moveR=-1 , last_moveC=-1;
            char sign = user1;
            std::vector<std::vector<int> > visited;
    };

}

#endif