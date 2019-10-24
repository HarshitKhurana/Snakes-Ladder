
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

int diceRoll ()
{
  return  random(6);   // 6 is the max value that can come.
}

class Snakes
{
  public:
    Snakes(pair<int,int> board[][SIZE])
    {
      insertSnakes(board);
    }

    void insertSnakes(pair<int,int> board[][SIZE])
    {


    }

    void printSnakes ()
    {
    }
};

class Ladders
{
  public:
    Ladders(pair<int,int> board[][SIZE])
    {
      insertLadder(board);
    }

    void insertLadder(pair<int,int> board[][SIZE])
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

    ~Player() 
    {
      delete current_location;
    }

    // This function takes accound the value that arrived on dice throw and increments
    void update_location(int row , int column)
    {

      int x_prev = current_location->first;
      int y_prev = current_location->second;

      // Update current location
      if (row < SIZE && column < SIZE)
      {
        current_location->first  = row;
        current_location->second = column;
      }
      else
      {  // Set to max accessible indexes
        current_location->first  = SIZE - 1;   
        current_location->second = SIZE - 1;
      }
      cout<< "[*] Player "<<name<<" moved from (" << x_prev << "," << y_prev<<") -> ("<<current_location->first<<","<< current_location->second<<")"<<endl;

    }

    // Player wons if it's current location exceeds the board i.e exceeds 100.
    bool won()
    {
      return SIZE*SIZE <= ( current_location->first*10 + current_location->second+1) ? true:false;
    }

    // Returns current location of the player
    pair<int,int> getLocation()
    {
      return *current_location;
    }

    string getName()
    {
      return name;
    }
};

class Board
{
  pair<int,int> board_matrix[SIZE][SIZE];   // It stores where exactly this box will take to (helpful for keeping track of snack and/or ladder)
  Snakes *snak;
  Ladders *lad;

  public:
    
    // Game has begun
    Board()
    {
      // Initialising all boxes with their own values
      for (int row = 0 ; row < SIZE ; row ++)
      {
        for (int col = 0 ; col < SIZE ; col++)
        {
          board_matrix[row][col] = pair<int,int>(row,col);
        }
      }

      // The board matrix now has both snakes and ladders and the 2d array contains the location to which it points.
      // For Ex : If a box say at (3,4)  has snake which take you to (2,3), then the board_matrix[3][4] will contain (2,3) to show that incase you arrive at this box then go back to this box.
      // Similarly for ladder but it insted of decreasing, it increments the location towards the destination.

      snak = new Snakes(board_matrix);
      lad  = new Ladders(board_matrix);
      
      cout <<"[*] The playing board is ready"<<endl;
    }

    ~Board()
    {
      delete snak;
      delete lad;
      cout <<"[*] The playing board is destroyed"<<endl;
    }

    void printBoard()
    {
      cout <<endl<<"[*] The following is the Playingg board"<<endl;
      for (int row = 0; row < SIZE; row++)
      {
        for (int column = 0 ; column< SIZE ; column++)
        {
          cout << "("<<board_matrix[row][column].first <<","<<board_matrix[row][column].second<<")  ";
        }
        cout<<endl;
      }
      cout<<endl;
    }

    Player& playGame(Player &player1 , Player &player2)
    {
      bool turn = true;     // if true then player1 will execute else player2
      while (true)
      {
        if (player1.won() || player2.won())
          break;
        int dice_value = diceRoll();
        int x_cord , y_cord;      // For new location
        if (turn)
        {
          pair<int,int> location = player1.getLocation(); // got current location of this player.
          int new_numeric_loc = location.first*SIZE + location.second+1 + dice_value;

          x_cord = new_numeric_loc / SIZE;
          y_cord = new_numeric_loc % SIZE - 1;

          if (y_cord == -1)
          {
            x_cord -=1;
            y_cord = SIZE - 1;
          }

          pair<int,int> new_location = pair<int,int> (board_matrix[x_cord][y_cord].first , board_matrix[x_cord][y_cord].second);

//          cout << "New numeric locatoin : "<< new_numeric_loc<<endl;
//          cout << "x_cord : "<<x_cord<<", y_cord : "<<y_cord <<endl;
//          cout << "value at board_matrix : " << board_matrix[x_cord][y_cord].first << " , "<<board_matrix[x_cord][y_cord].second<<endl;
//
          player1.update_location( new_location.first , new_location.second);   // Player1 does the dice roll and it's location is updated.
        }
        else
        {
          pair<int,int> location = player2.getLocation(); // got current location of this player.
          int new_numeric_loc = location.first*SIZE + location.second+1 + dice_value;

          x_cord = new_numeric_loc / SIZE;
          y_cord = new_numeric_loc % SIZE - 1;

          if (y_cord == -1)
          {
            x_cord -=1;
            y_cord = SIZE - 1;
          }

          pair<int,int> new_location = pair<int,int> (board_matrix[x_cord][y_cord].first , board_matrix[x_cord][y_cord].second);
//          cout << "New numeric locatoin : "<< new_numeric_loc<<endl;
//          cout << "x_cord : "<<x_cord<<", y_cord : "<<y_cord <<endl;
//          cout << "value at board_matrix : " << board_matrix[x_cord][y_cord].first << " , "<<board_matrix[x_cord][y_cord].second<<endl;

          player2.update_location( new_location.first , new_location.second);   // Player2 does the dice roll and it's location is updated.
        }

        turn = !turn;   // toggle turn for alternate dice roll turns
      }

      if (player1.won())
        return player1;
      else
        return player2;
    }
};

int main( int argc,  char *argv[])
{

  Board playing_board;
  string p_name;

  cout <<"[*] Enter name of player1 : ";
  cin>>p_name;
  Player player1(p_name);

  cout <<"[*] Enter name of player2 : ";
  cin>>p_name;
  Player player2(p_name);


  playing_board.printBoard();
  Player winner  = playing_board.playGame( player1, player2 );
  cout << "[*] "<< winner.getName()<<" won the game"<<endl;
}

