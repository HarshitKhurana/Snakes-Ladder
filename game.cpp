
#include<iostream>
#include<stdlib.h>
#include<unistd.h>

using namespace std;

# define NUMBER_OF_LADDER 5
# define NUMBER_OF_SNAKES 5
# define SIZE 10

// upper_limit argument defines the max value this function can return,
int random(int upper_limit)  
{
  return rand() % upper_limit + 1;    // +1 done because dice roll is from 1 to 6 and not 0 to 5.
}

// Returns a random number from 1 to 6
int diceRoll ()
{
  return  random(6);   // 6 is the max value that can come.
}

class Snakes
{
  public:
    
    // This is the constructor which calls the actual function.
    Snakes(pair<int,int> board[][SIZE])
    {
      insertSnakes(board);
    }

    // This function simply inserts snake in the board randomly
    void insertSnakes(pair<int,int> board[][SIZE])
    {
      for (int counter = 0 ; counter < NUMBER_OF_SNAKES ; counter ++)
      {
        int x  = 0 ,y = 0;
        while ( !(x>1) )  { x = random(SIZE-1); }
        while ( !(y>1) )  { y = random(SIZE-1); }
        pair<int,int> &temp_ref = board[x][y];

        if (temp_ref.first == x && temp_ref.second == y)  // this box currently points to iself only i.e no ladder or snake is attached to it
        {
          temp_ref.first  = x-1;
          temp_ref.second = y-1;
          cout << "[*] Added snake to ("<<x<<","<<y<<") it now points to ("<<temp_ref.first<<","<<temp_ref.second<<")"<<endl;
        }
        else
          counter --;   // This is because if this board[x][y] already contains a snake or a ladder then don't modify this, and thus will have to retry with new co-ordinates.
      }
    }
};

class Ladders
{
  public:
    // This is the constructor which calls the actual function.
    Ladders(pair<int,int> board[][SIZE])
    {
      insertLadder(board);
    }

    // This function simply inserts ladders in the board randomly
    void insertLadder(pair<int,int> board[][SIZE])
    {
      for (int counter = 0 ; counter < NUMBER_OF_LADDER ; counter ++)
      {
        int x  = SIZE-1,y = SIZE-1;
        while ( !(x<SIZE-1) )  { x = random(SIZE-1); }
        while ( !(y<SIZE-1) )  { y = random(SIZE-1); }

        pair<int,int> &temp_ref = board[x][y];

        if (temp_ref.first == x && temp_ref.second == y)    // this box currently points to iself only i.e no ladder or snake is attached to it
        {
          temp_ref.first  = x+1;
          temp_ref.second = y+1;
          cout << "[*] Added Ladder to ("<<x<<","<<y<<") it now points to ("<<temp_ref.first<<","<<temp_ref.second<<")"<<endl;
        }
        else
          counter --;   // This is because if this board[x][y] already contains a snake or a ladder then don't modify this, and thus will have to retry with new co-ordinates.
      }
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
    void update_location(int row , int column, int dice_value)
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
      cout<< "[*] Player "<<name<<" got "<<dice_value<<" and moved from (" << x_prev << "," << y_prev<<") -> ("<<current_location->first<<","<< current_location->second<<")"<<endl;

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
      // Initialising all boxes with their own values as initially there are no snakes or ladder inserted in the board.
      for (int row = 0 ; row < SIZE ; row ++)
      {
        for (int col = 0 ; col < SIZE ; col++)
        {
          board_matrix[row][col] = pair<int,int>(row,col);    
        }
      }

      // The board matrix now has both snakes and ladders and the 2d array contains the location to which it points.
      // For Ex : If a box say at (3,4)  has snake which take you to (2,3), then the board_matrix[3][4] will contain (2,3) to show that incase you arrive at this box then go to board[2][3]
      // Similarly for ladder but it insted of decreasing, it increments the location towards the destination.

      snak = new Snakes(board_matrix);
      lad  = new Ladders(board_matrix);
      
      cout <<"[*] The playing board is ready"<<endl;
    }

    ~Board()
    {
      delete snak;
      delete lad;
      cout <<"[*] GAME OVER"<<endl;
    }

    void printBoard()
    {
      cout <<endl<<"[*] The following is the Playingg board"<<endl;
      cout << "[*] '*' indicates the presence of snake or a ladder at that box"<<endl;
      for (int row = 0; row < SIZE; row++)
      {
        for (int column = 0 ; column< SIZE ; column++)
        {
          pair<int,int> &temp_ref = board_matrix[row][column];
          string s = temp_ref.first != row || temp_ref.second != column?"*":" ";
          cout << s<<"("<<temp_ref.first <<","<<temp_ref.second<<")  ";
        }
        cout<<endl;
      }
      cout<<endl;
    }

    // This is the actual function which starts and runs the game untill 1 of the player wins the game.
    Player& playGame(Player &player1 , Player &player2)
    {
      bool turn = true;     // if true then player1 will execute else player2

      // Untill one of the players win the game keep on playing the game and continue to roll the dice.
      while (true)
      {
        if (player1.won() || player2.won())
          break;
        int dice_value = diceRoll();
        int x_cord , y_cord;      // For new location
        
        // if true then player1 will execute else player2
        if (turn)
        {
          pair<int,int> location = player1.getLocation(); // got current location of this player.
          int new_numeric_loc = location.first*SIZE + location.second+1 + dice_value;

          x_cord = new_numeric_loc / SIZE;          // Row
          y_cord = new_numeric_loc % SIZE - 1;      // Column

          // When the column reaches -1 that means that we want the last element from the previous row.
          if (y_cord == -1)
          {
            x_cord -=1;
            y_cord = SIZE - 1;
          }

          // reason for jumping to board_matrix[x_cord][y_cord].first and board_matrix[x_cord][y_cord].second instead of board_matrix[x_cord][y_cord] is because if there is a snake or ladder there then we will have to follow that path.
          pair<int,int> new_location = pair<int,int> (board_matrix[x_cord][y_cord].first , board_matrix[x_cord][y_cord].second);
          player1.update_location( new_location.first , new_location.second , dice_value);   // Player1 does the dice roll and it's location is updated.
        }

        else
        {
          pair<int,int> location = player2.getLocation(); // got current location of this player.
          int new_numeric_loc = location.first*SIZE + location.second+1 + dice_value;

          x_cord = new_numeric_loc / SIZE;       // Row
          y_cord = new_numeric_loc % SIZE - 1;   // Column

          // When the column reaches -1 that means that we want the last element from the previous row.
          if (y_cord == -1)
          {
            x_cord -=1;
            y_cord = SIZE - 1;
          }

          // reason for jumping to board_matrix[x_cord][y_cord].first and board_matrix[x_cord][y_cord].second instead of board_matrix[x_cord][y_cord] is because if there is a snake or ladder there then we will have to follow that path.
          pair<int,int> new_location = pair<int,int> (board_matrix[x_cord][y_cord].first , board_matrix[x_cord][y_cord].second);
          player2.update_location( new_location.first , new_location.second , dice_value);   // Player2 does the dice roll and it's location is updated.
        }

        turn = !turn;   // toggle turn for alternate dice roll turns
      }

      return player1.won()?player1:player2;   // return winner of the game.
    }
};

int main( int argc,  char *argv[])
{

  string p_name;

  cout <<"[*] Enter name of player1 : ";
  cin>>p_name;
  Player player1(p_name);

  cout <<"[*] Enter name of player2 : ";
  cin>>p_name;
  Player player2(p_name);

  Board playing_board;
  playing_board.printBoard();

  // Adding delay so that the board is printed first and visible for sufficient time. (Not required , just added for visibility while running code)
  cout <<"[*] Starting game in 3 second"<<endl;
  sleep(3);
  Player &winner  = playing_board.playGame( player1, player2 );
  cout << "[*] "<< winner.getName()<<" won the game"<<endl;
}

