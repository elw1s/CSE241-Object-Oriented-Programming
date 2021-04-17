[HOW TO START A GAME]

** There are 3 choices to start a new game object. ** 

Hex new_game; // 1- board_size and gameplay_type is not defined.
Hex new_game(6); //2- board_size sets to 6 , gameplay_type is not defined.
Hex new_game(6,2); //3- board_size sets to 6 , gameplay_type sets to 2 (player vs bot)

~~After Hex game object is created then you should use outputTerminal(bool) function to decision
on board's output.

new_game.outputTerminal("true"); //Your board will be printed on terminal.

*Note: If you don't set outputTerminal(bool) function to true then your program will not be printed
on terminal. Default version is this.

~~You created an object and decide your output. Now you can start your game using playGame() function.

new_game.playGame(); //This function is mandatory for games. It will set appropriate values to start game.

[HOW TO MAKE MOVE]

** If you are playing on terminal then you don't need to worry about making moves. Program will handle it 
for you. But if you are not playing on terminal then you have to use play() functions.

-> Cell play(); //plays for the bot. 
-> void play(Cell&); //plays for the user.

*NOTE: If you use play() function while playing player vs player game then you will get an error and 
program will be aborted.
*NOTE: If you use play functions then you should use printBoard() afterwards. Otherwise you will not see output.
*NOTE: If you play an invalid move then program will be aborted.

[END OF THE GAME]

** If you are not playing on terminal then you can need a function to see that game is ended or not.
There is one function handles this.

new_game.IsGameEnded(); //returns true when game is ended.


[SAVING & LOADING]

**There are 2 public member functions to handle saving and loading. These are:

-> void saveGame(const string& file_path);
-> void loadGame(const string& file_path);

[OVERLOADED OPERATORS]

**Overloaded operators are:

->bool operator ==(const Hex& other) const; //returns true when two game's marked cells are equal
->void operator --(); //prefix operator for undo operations
->void operator --(int ignoreMe); //postfix operator for undo operations
->ostream& operator <<( ostream& outputStream,const Hex& obj); //prints board without column and score
->ifstream& operator >>( ifstream& fileInput,  Hex& obj); //loads game from a file.
->Hex& operator =(const Hex& rvalue); //Assignment operator

*NOTE: Stream insertion operator does not print whole board.

Example of insertion operator:

cout << new_game;

OUTPUT:
(without score and columns)

1  . . . . . . . .
2   . x . . . . . .
3    . . x . . . . .
4     . . . . . . . .
5      . . . . . . . .
6       . . . . . . . .
7        . . . o o . . .
8         . . . . . . . .


[MARKED CELLS]

** You can see marked cells of an active game like that:

new_game.getTurn(); //this will returns number of marked cells of new_game

** You can see marked cells of all active games like that:

new_game.numberOfMarkedCells();

[SCORE]

**You can see score of an active game like that:

new_game.getScoreP1(); //This returns user1's score. (If you are playing player vs bot then this will be your main score)
new_game.getScoreP2(); //This returns user2's score. (Only when playing player vs player)

