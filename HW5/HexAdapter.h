#ifndef HEXADAPTER
#define HEXADAPTER

#include <iostream>
#include "AbstractHex.h"
using namespace HexGame; //namespace
using std::string;

/* Header file for HexAdapter */

template<template<typename ...> class T>
    class HexAdapter : public AbstractHex{
        public:
            HexAdapter(int size){
            setBoardSize(size);
            setSize();
            };
            HexAdapter(){};
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
            void moveBot() override;
        private:
             T<T<Cell> > board; 
    };

#endif