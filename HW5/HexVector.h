#ifndef HEXVECTOR
#define HEXVECTOR

#include <iostream>
#include "AbstractHex.h"
#include <vector>
using namespace HexGame; //Namespace
using std::vector;
using std::string;

/* Header file for HexVector */


class HexVector : public AbstractHex{
    public:
        HexVector(int size){
            setBoardSize(size);
            setSize();
        };
        HexVector(){};
        void print() const override;
        void readFromFile(string& file_path) override;
        void writeToFile(string& file_path) const override;
        void reset() override;
        void setSize() override;
        void play() override;
        void play(const AbstractHex::Cell& move) override; 
        char operator()(int rw, int col) const override;
        bool checkMove(char c , int rw) const override;
        bool checkWin(int curr_row,int curr_col) override;
        void moveBot() override;
        bool operator==(const AbstractHex& other)const override;
    private:
        vector<vector<AbstractHex::Cell> > board;

};

#endif