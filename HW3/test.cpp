#include "hex_game.h"

using namespace std;


/* Test Program for hex_game library*/

int main(){

	Hex game1,game2(6),game3(7,1),game4(8,1),game5(20,2);

    /* game1 will be played on terminal. */
	game1.playOnTerminal(true);
	game1.playGame();

	/* game2 will be played by public member functions (adding points one by one)*/
	int x;
	char y;

	game2.playGame();

	game2.cleanConsole();
	game2.printBoard();
	while(!game2.IsGameEnded()){
		cin >> y >> x;
		game2.play(y,x);
		game2.play();
		game2.printBoard();
	}

	/* game3 is a player vs player game and board size of game3 is 7 */

	game3.playGame();
	game3.play('A',2); // Placed 'x' to position A2.
	game3.play('C',4); // Placed 'o' to position C4.
	cout << endl << "game3: " << endl;
	game3.printBoard();

	/* game4 is a player vs player game and board size of game4 is 8 */

	game4.playGame();
	game4.play('F',5); // Placed 'x' to position F5.
	game4.saveGame("save.txt");
	cout << endl << "game4: " << endl;
	game4.printBoard(); 

	/* game5 is a player vs bot game and board size of game5 is 20 */

	game5.playGame();
	game5.play('G',17);
	game5.play();
	game5.play('D',10);
	game5.play();
	cout << endl << "game5: " << endl;
	game5.printBoard();
	game5.loadGame("save.txt"); // game5 will be same as game4.
	cout << endl << "game5 (loaded from save.txt) [Same as game4]: " << endl;
	game5.printBoard();

	/* Other functions */
	/* compareMarkedCells function will return 1 (true) when calling object has more marked cells than the parameter object */
	cout << endl << "Compare game2 and game4 (In terms of marked cells): " << game2.compareMarkedCells(game4) << endl;
	cout << endl << "Compare game1 and game5 (In terms of marked cells): " << game1.compareMarkedCells(game5) << endl;
	cout << endl << "Compare game3 and game1 (In terms of marked cells): " << game3.compareMarkedCells(game1) << endl;

	return 0;
}
