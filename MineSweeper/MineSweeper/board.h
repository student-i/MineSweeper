#pragma once

#include <vector>
#include <iostream>
#include <stdlib.h> 
#include <time.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

class Location
{
public:
   Location() 
   {
      revealed = false;
      value = 0;
   }
   bool revealed;
   int value;
};

class Board
{
public:

   Board(int difficulty);

   vector<Location> getBoard() { return board; }

   void displayBoard();
   void reset(int firstCoro);
   void updateBoard(int coro);
   void firstLocation() 
   {
      int c = getCoro();
      board[c].revealed = true;
      reset(c); 
      updateBoard(c);
   }
   int getCoro();

private:
   vector<Location> board;
   int size;
};

