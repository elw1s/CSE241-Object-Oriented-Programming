#ifndef HEXARRAY1D
#define HEXARRAY1D

#include <iostream>
#include "AbstractHex.h"
#include <vector>
using namespace HexGame; //Namespace
using std::string;

/* Header file for HexArray1D */

class HexArray1D : public AbstractHex{
    public:
        HexArray1D(int size){
            setBoardSize(size);
            setSize();
        };
        ~HexArray1D(); //Destructor
        HexArray1D(){/* INTENTIONALLY EMPTY */}; //Constructor
        HexArray1D(const HexArray1D& obj); //Copy Constructor
        void print() const override; 
        void readFromFile(string& file_path) override;
        void writeToFile(string& file_path)const override;
        void reset() override;
        void setSize() override;
        void play() override;
        void play(const AbstractHex::Cell& move) override; 
        char operator()(int rw, int col)const override;
        bool operator==(const AbstractHex& other) const override;
        bool checkMove(char col, int rw)const override;
        bool checkWin(int curr_row,int curr_col) override;
        int getIndex(int rw , int col) const;
        void moveBot() override;
    private:
       Cell * board; 
};

#endif