
#include<iostream>
#include<stdlib.h>
#include<bits/stdc++.h>

using namespace std;

# define NUMBER_OF_LADDER 5
# define NUMBER_OF_SNAKES 5
# define SIZE 10

int random(int upper_limit = SIZE-1)   // upper_limit argument defines the max value this function can return,
{
  return rand() % upper_limit + 1;    // +1 done because dice roll is from 1 to 6 and not 0 to 5.
}

int dice_roll ()
{
  return random(6);   // 6 is the max value that can come.
}

class Snakes
{
  public:
    Snakes(int board[][SIZE])
    {
      insertSnakes(board);
    }

    void insertSnakes(int board[][SIZE])
    {
    }

    void printSnakes ()
    {
    }
};

class Ladders
{
  public:
    Ladders(int board[][SIZE])
    {
      insertLadder(board);
    }

    void insertLadder(int board[][SIZE])
    {
    }

    void printLadders ()
    {
    }
};

class Player
{
  pair<int,int> *current_location;    // It contains the row and column number, like an (x,y) co-ordinate.
  string name;                        // Name of the player

  public:
    Player(string naam) : name {naam}
    {
      // name = naam;
      current_location = new pair<int,int>(0,0);
      cout <<"[*] Player '" <<name<<"' ready "<<endl; 
    }

    // This function takes accound the value that arrived on dice throw and increments
    void update_location(int dice_output)
    {
      int current_loc_numeric = current_location->first * SIZE + current_location->second + 1;
      int new_loc_numeric = current_loc_numeric + dice_output;

      cout<< "[*] Player "<<name<<" moved to : "<< numeric_loc<<endl;
    }

    // Player wons if it's current location exceeds the board i.e exceeds 100.
    bool won()
    {
      return SIZE*SIZE <= ( (current_location->first+1)*10 + current_location->second+1) ? true:false;
    }

    string getName()
    {
      return name;
    }
};

class Board
{
  int board_matrix[SIZE][SIZE];
  Snakes *snak;
  Ladders *lad;

  public:
    
    Board()
    {
      // Game has begun
      snak = new Snakes(board_matrix);
      lad  = new Ladders(board_matrix);

      // The board matrix now has both snakes and ladders.
      cout <<"[*] The playing board is ready"<<endl;
    }

    void printBoard()
    {
      for (int row = 0; row < SIZE; row++)
      {
        for (int column = 0 ; column< SIZE ; column++)
        {
          cout << board_matrix[row][column]<<" ";
        }
        cout<<endl;
      }
    }
};

int main( int argc,  char *argv[])
{

  bool turn = true;     // if true then player1 will execute else player2
  string p_name;

  cout <<"[*] Enter name of player1 : ";
  cin>>p_name;
  Player player1(p_name);

  cout <<"[*] Enter name of player2 : ";
  cin>>p_name;
  Player player2(p_name);

  while ( !player1.won() || !player2.won())
  {
    if (turn)
      player1.update_location(dice_roll());   // Player1 does the dice roll and it's location is updated.
    else
      player2.update_location(dice_roll());   // Player2 does the dice roll and it's location is updated.

    turn = !turn;   // toggle turn for alternate dice roll turns
  }

  if (player1.won())
    cout << "[*] "<<player1.getName()<<" wond the game"<<endl;
  else
    cout << "[*] "<<player2.getName()<<" wond the game"<<endl;
}

