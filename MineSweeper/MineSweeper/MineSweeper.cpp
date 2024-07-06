#include <conio.h>
#include <iostream>
#include "board.h"
using namespace std;

int main()
{

   int dif = 0;

   while (dif != 1 && dif != 2)
   {
   cout << "1. 16 X 16\n2. 25 X 25\n";
   cin >> dif;
   }
   Board board(dif);
   system("cls");
   board.displayBoard();
   board.firstLocation();
   system("cls");
   board.displayBoard();
   int move = board.getCoro();

   while (move != 99)
   {
      board.updateBoard(move);
      system("cls");
      board.displayBoard();
      move = board.getCoro();
   }
   system("cls");
   cout << "You Lost\n";
   board.displayBoard();
}

