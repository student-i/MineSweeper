#include "board.h"

void SetColor(int text, int background) {
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hConsole, text + background * 16);
}

using namespace std;

Board::Board(int difficulty)
{

   if (difficulty == 1)
      size = 16;
   else
      size = 25;
   for (int i = 0; i < size*size; i++)
   {
      Location newLocation;

      board.push_back(newLocation);
   }
}

void Board::reset(int firstCoro)
{
   int numBombs = 0;
   if (size == 9)
      numBombs = 10;
   if (size == 16)
      numBombs = 40;
   else
      numBombs = 80;
   srand(time(NULL));
   // Find the loaction of the bombs
   for (int b = 0; b < numBombs; b++)
   {
      bool added = false;
      while (!added)
      {
         added = true;
         int r = rand() % 257;

         // Make sure it is not the first corodenate
         if (r == firstCoro)
            added = false;

         // Make sure it isn't already a bomb
         else if(board[r].value == 9)
            added = false;
         else
         {
            added = true;
            board[r].value = 9;
         }
      }
   }
   for (int i = 0; i < board.size(); i++)
   {
      int row = i / size;
      int col = i % size;

      // Update value so that each location reflects the number of bombs touching it.
      // Making sure that it only effects the ones that each location is displayed with.
      // Making sure that it doesn't leave the bounds of the vector. 
      if (board[i].value != 9)
      {
         if (col != 0)
         {
            if (i - 1 >= 0 && board[i - 1].value == 9)
               board[i].value += 1;
            if (row != 0)
            {
               if (i - (size+1) >= 0 && board[i - (size + 1)].value == 9)
                  board[i].value += 1;
            }
            if (row != size-1)
            {

               if (i + (size-1) < size*size && board[i + (size - 1)].value == 9)
                  board[i].value += 1;
            }
         }

         if (col != size-1)
         {
            if (i + 1 < size*size && board[i + 1].value == 9)
               board[i].value += 1;
            if (row != 0)
            {
               if (i + (size + 1) < size*size && board[i + (size + 1)].value == 9)
                  board[i].value += 1;
            }
            if (row != (size - 1))
            {
               if (i - (size - 1) >= 0 && board[i - (size - 1)].value == 9)
                  board[i].value += 1;
            }
         }
         if (row != 0)
         {
            if (i - size >= 0 && board[i - size].value == 9)
               board[i].value += 1;
         }
         if (row != (size - 1))
         {
            if (i + size < size*size && board[i + size].value == 9)
               board[i].value += 1;
         }
      }
   }
}


void Board::updateBoard(int coro)
{
   int row = coro / size;
   int col = coro % size;

   // Update what is revealed recursively
   // Makeing sure that we remain in the bounds of the vector
   // and it only effectsthose that are displyed together.
   if (board[coro].value == 0)
   {
      if (col != 0)
      {
         if (coro - 1 >= 0 && board[coro - 1].revealed == false) {
            board[coro - 1].revealed = true;
            updateBoard(coro - 1);
         }
         if (row != 0)
         {

            if (coro - (size + 1) >= 0 && board[coro - (size + 1)].revealed == false)
            {
               board[coro - (size + 1)].revealed = true;
               updateBoard(coro - (size + 1));
            }
         }
         if (row != (size - 1))
         {

            if (coro + (size - 1) < size*size && board[coro + (size - 1)].revealed == false)
            {
               board[coro + (size - 1)].revealed = true;
               updateBoard(coro + (size - 1));
            }
         }
      }
      if (col != (size - 1))
      {

         if (coro + 1 < size*size && board[coro + 1].revealed == false)
         {
            board[coro + 1].revealed = true;
            updateBoard(coro + 1);
         }
         if (row != 0)
         {
            if (coro + (size + 1) < size*size && board[coro + (size + 1)].revealed == false)
            {
               board[coro + (size + 1)].revealed = true;
               updateBoard(coro + (size + 1));
            }
         }
         if (row != (size - 1))
         {

            if (coro - (size - 1) >= 0 && board[coro - (size - 1)].revealed == false)
            {
               board[coro - (size - 1)].revealed = true;
               updateBoard(coro - (size - 1));
            }
         }
      }
      if (row != 0)
      {

         if (coro - size >= 0 && board[coro - size].revealed == false)
         {
            board[coro - size].revealed = true;
            updateBoard(coro - size);
         }
      }

      if (row != (size - 1))
      {

         if (coro + size < size*size && board[coro + size].revealed == false)
         {
            board[coro + size].revealed = true;
            updateBoard(coro + size);
         }
      }



   }
}

void Board::displayBoard()
{
   int index = 0;
   cout << "   1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16" << endl;       
   for (int l = 0; l < size; l++)
   {
      SetColor(7, 0);
      cout << l+1 << " ";
      if (l <= 8)
         cout << " ";

      for (int i = index; i < size + index; i++)
      {
         if (board[i].revealed)
         {

            if (board[i].value == 9)
            {
               SetColor(7, 0);
               cout << "* " << " ";
            }
            else 
            {
               SetColor(9, 0);
               cout << board[i].value << "  ";
            }
         }
         else
         {
            SetColor(4, 0);
            cout << "X " << " ";
         }
      }
      cout << endl;
      index += size;
   }
   SetColor(7,0);
}

int Board::getCoro()
{
   int rowInput = -1;
   int columnInput = -1;

   while (!(rowInput < size+1 && rowInput > 0 && columnInput < size+1 && columnInput > 0))
   {

      cout << "What is the row of your next guess? ";
      cin >> rowInput;

      cout << "What is the column of you next guess? ";
      cin >> columnInput;
   }

   int corodinate = (rowInput - 1) * size + (columnInput - 1);
   board[corodinate].revealed = true;

   if (board[corodinate].value == 9)
      return 99;
   return corodinate;
}
