### [\*] Snakes & Ladders

* Emulation of simple Snakes and Ladder game in C++.
* Following is the description of classes


|S.No | Class        | Utility       |
|:----|:-------------|:-------------:|
|1.   | Snake  Class | This class is responsible for adding snakes on the board |
|2.   | Ladder Class | This class is responsible for adding Ladder on the board |
|3.   | Board  Class | This class is responsible for creating the board itself |
|4.   | Player Class | This class is responsible for creating the players which will be playing on the board|


* To run , compile and run as :

```bash
$ g++ -std=c++11 game.cpp -o game
$ ./game
```

* Currently for inserting snakes or ladders a point is select randomly from the entire grid and it points to exactly (1,1) level below or above it depending upon whether a ladder was added or a snake.

* The flow is as :
	* The board is the main class.
	* Board class uses association for snake and ladder class.
	* Board class has the functionality to start running the game, for that it needs 2 players to begin with.
	* These 2 players are just function arguments and in no way related to the Board class (no inheritance or association)

* The matrix printed is a 10\*10 grid (configurable MACRO in code), which tells that to which point that particular point is redirects to.
	* Example 1 : If a box say at board[3][4] has a snake which take you to boad[2][3], then the board[3][4] will contain (2,3) to show that incase you arrive at this box then you will be redirected to board[2][3].
	* Example 2 : Lets say the board[2][3] contains [4][5] it means that there is a ladder connected to board[2][3] which directly takes you to board[4][5].



* Running Example : 

```bash
[*] Enter name of player1 : user1
[*] Player 'user1' ready 
[*] Enter name of player2 : user2
[*] Player 'user2' ready 
[*] Added snake to (2,8) it now points to (1,7)
[*] Added snake to (8,6) it now points to (7,5)
[*] Added snake to (8,2) it now points to (7,1)
[*] Added snake to (4,7) it now points to (3,6)
[*] Added snake to (2,6) it now points to (1,5)
[*] Added Ladder to (5,6) it now points to (6,7)
[*] Added Ladder to (5,7) it now points to (6,8)
[*] Added Ladder to (1,8) it now points to (2,9)
[*] Added Ladder to (2,7) it now points to (3,8)
[*] Added Ladder to (7,5) it now points to (8,6)
[*] The playing board is ready

[*] The following is the Playingg board
[*] '*' indicates the presence of snake or a ladder at that box
 (0,0)   (0,1)   (0,2)   (0,3)   (0,4)   (0,5)   (0,6)   (0,7)   (0,8)   (0,9)  
 (1,0)   (1,1)   (1,2)   (1,3)   (1,4)   (1,5)   (1,6)   (1,7)  *(2,9)   (1,9)  
 (2,0)   (2,1)   (2,2)   (2,3)   (2,4)   (2,5)  *(1,5)  *(3,8)  *(1,7)   (2,9)  
 (3,0)   (3,1)   (3,2)   (3,3)   (3,4)   (3,5)   (3,6)   (3,7)   (3,8)   (3,9)  
 (4,0)   (4,1)   (4,2)   (4,3)   (4,4)   (4,5)   (4,6)  *(3,6)   (4,8)   (4,9)  
 (5,0)   (5,1)   (5,2)   (5,3)   (5,4)   (5,5)  *(6,7)  *(6,8)   (5,8)   (5,9)  
 (6,0)   (6,1)   (6,2)   (6,3)   (6,4)   (6,5)   (6,6)   (6,7)   (6,8)   (6,9)  
 (7,0)   (7,1)   (7,2)   (7,3)   (7,4)  *(8,6)   (7,6)   (7,7)   (7,8)   (7,9)  
 (8,0)   (8,1)  *(7,1)   (8,3)   (8,4)   (8,5)  *(7,5)   (8,7)   (8,8)   (8,9)  
 (9,0)   (9,1)   (9,2)   (9,3)   (9,4)   (9,5)   (9,6)   (9,7)   (9,8)   (9,9)  

[*] Starting game in 3 second
[*] Player user1 got 2 and moved from (0,0) -> (0,2)
[*] Player user2 got 2 and moved from (0,0) -> (0,2)
[*] Player user1 got 6 and moved from (0,2) -> (0,8)
[*] Player user2 got 1 and moved from (0,2) -> (0,3)
[*] Player user1 got 1 and moved from (0,8) -> (0,9)
[*] Player user2 got 1 and moved from (0,3) -> (0,4)
[*] Player user1 got 6 and moved from (0,9) -> (1,5)
[*] Player user2 got 4 and moved from (0,4) -> (0,8)
[*] Player user1 got 2 and moved from (1,5) -> (1,7)
[*] Player user2 got 5 and moved from (0,8) -> (1,3)
[*] Player user1 got 2 and moved from (1,7) -> (1,9)
[*] Player user2 got 5 and moved from (1,3) -> (2,9)
[*] Player user1 got 4 and moved from (1,9) -> (2,3)
[*] Player user2 got 4 and moved from (2,9) -> (3,3)
[*] Player user1 got 4 and moved from (2,3) -> (3,8)
[*] Player user2 got 6 and moved from (3,3) -> (3,9)
[*] Player user1 got 3 and moved from (3,8) -> (4,1)
[*] Player user2 got 2 and moved from (3,9) -> (4,1)
[*] Player user1 got 3 and moved from (4,1) -> (4,4)
[*] Player user2 got 3 and moved from (4,1) -> (4,4)
[*] Player user1 got 6 and moved from (4,4) -> (5,0)
[*] Player user2 got 1 and moved from (4,4) -> (4,5)
[*] Player user1 got 6 and moved from (5,0) -> (6,7)
[*] Player user2 got 5 and moved from (4,5) -> (5,0)
[*] Player user1 got 2 and moved from (6,7) -> (6,9)
[*] Player user2 got 3 and moved from (5,0) -> (5,3)
[*] Player user1 got 3 and moved from (6,9) -> (7,2)
[*] Player user2 got 4 and moved from (5,3) -> (6,8)
[*] Player user1 got 3 and moved from (7,2) -> (8,6)
[*] Player user2 got 3 and moved from (6,8) -> (7,1)
[*] Player user1 got 5 and moved from (8,6) -> (9,1)
[*] Player user2 got 2 and moved from (7,1) -> (7,3)
[*] Player user1 got 4 and moved from (9,1) -> (9,5)
[*] Player user2 got 4 and moved from (7,3) -> (7,7)
[*] Player user1 got 3 and moved from (9,5) -> (9,8)
[*] Player user2 got 4 and moved from (7,7) -> (8,1)
[*] Player user1 got 3 and moved from (9,8) -> (9,9)
[*] user1 won the game
[*] GAME OVER
```
