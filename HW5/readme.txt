ERROR HANDLING:

-If user enters invalid things such as range , board size , gameplay type etc. then program will throw an exception
and catch it in main. After catching it , program will print that error and terminate.

[HOW TO USE ALL FUNCTIONS IN GAME]

-There is an instructions page that tells the user how to use this functions in-game. Here's the list of
all commands that can be usable in game.

Save game: SAVE filename.txt
Load game: LOAD filename.txt
Get Number of Moves: MOVES
Use operator(): OPERATOR() index1 index2 [Ex: "OPERATOR() 0 1" (For B1)]
Get the last move: LAST
Reset the board: RESET
Exit: exit
Back To Menu: back

[OTHER FUNCTIONS THAT ARE NOT IMPLEMENTED TO USE IN GAME BUT CAN BE USABLE IN OUTSIDE]

-The operator== and global function are not implemented in-game commands. This function and operator are
calling after the ending of the game. If someone wins (or program gets out from menu) then these functions 
will be appear.

[WHAT GLOBAL FUNCTION DO?]

-Global function gets an array of AbstactHex pointers and size of this array. AbstractHex pointer (named obj)
will be created in function. This is the main board of this function. For every element of AbstractHex pointer array
this function will be used. Every AbstractHex pointer array element's (which is a game) will insert it's pointers
to the obj (AbstactHex pointer). At the end of the function if the obj (AbstactHex pointer) is valid then true will be return by function.

In summary obj is a reflection of all games.

