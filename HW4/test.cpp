#include "hex_game.h"

using namespace std;


/* Test Program for hex_game library*/

int main(){
Hex game1,game2(6),game3(7,1),game4(8,1),game5(20,2);
Hex::Cell move1(1,'A','x') , move2(4,'C','o') , move3(2,'B','x') , move4(7,'D','o') , move5(7,'E','x'),
		  move6(3,'B','x') , move7(5,'F','o') , move8(4,'B','x') , move9(5,'D','x') , move10(1,'H','x'),
		  move11(15,'G','x');

	/* GAME 1 */
	game1.terminalOutput(true);
	game1.playGame();

	/* GAME 2 */
	cout << "\n GAME 2  [NOTE: SELECT PLAYER VS COMPUTER. IT IS AN EXAMPLE OF HOW TO PLAY GAME WITHOUT TERMINAL]\n\n";
	int x;
	char y;
	game2.playGame();
	game2.cleanConsole();
	game2.printBoard();
	while(!game2.IsGameEnded()){
		cout << "Player's turn: ";
		cin >> y >> x;
		Hex::Cell move(x , y , 'x');
		game2.play(move);
		if(!game2.IsGameEnded()) game2.play();
		game2.cleanConsole();
		game2.printBoard();
	} 
	game2.cleanConsole();
	cout << "-------------------------------GAME 1-------------------------------" << endl;
	game1.printBoard();
	cout << "-------------------------------GAME 2-------------------------------" << endl;
	game2.printBoard();

	cout << "-------------------------------GAME 3-------------------------------" << endl;
	/* GAME 3 */
	game3.playGame();
	game3.play(move1); 
	game3.play(move2); 
	game3.play(move6);
	game3.play(move7);
	game3.play(move8);
	game3.play(move9);
	game3.printBoard();

	cout << "-------------------------------GAME 4-------------------------------" << endl;
	
	/* GAME 4 */
	game4.playGame();
	game4.play(move3); 
	game4.play(move4);
	game4.play(move2);
	game4.play(move5);
	game4.saveGame("save1.txt");
	cout << "\n";
	game4.printBoard(); 

	cout << "-------------------------------GAME 5-------------------------------" << endl;
	/* GAME 5 */
	game5.playGame();
	game5.play(move10);
	game5.play();
	game5.play(move11);
	game5.play();
	game5.printBoard();
	game5.loadGame("save1.txt"); 

	cout << "-------------------------------GAME 5 (after loading save1.txt)-------------------------------" << endl;
	game5.printBoard();

	cout << "-------------------------------MARKED CELLS-------------------------------" << endl;
	cout << endl << "Compare game2 and game4 (In terms of marked cells): " << game2.compareMarkedCells(game4) << endl;

	cout <<  "Total marked cells of game1: " << game1.getTurn() << endl;
	cout <<  "Total marked cells of game2: " << game2.getTurn() << endl;
	cout <<  "Total marked cells of game3: " << game3.getTurn() << endl;
	cout <<  "Total marked cells of game4: " << game4.getTurn() << endl;
	cout <<  "Total marked cells of game5: " << game5.getTurn() << endl;
	cout <<  "Total marked cells in all active games: " << game1.numberOfMarkedCells() << endl;

	cout << "\n-------------------------------STREAM INSERTION OPERATOR OVERLOADING ( cout << game5 )-------------------------------\n";
	cout << game5;
	cout << "\n-------------------------------UNARY MINUS OPERATOR OVERLOADING ~ POSTFIX ( game3--; )-------------------------------\n"; 
	game3--;
	cout << game3;
	cout << "\n-------------------------------UNARY MINUS OPERATOR OVERLOADING ~ PREFIX ( --game3; )-------------------------------\n";
	--game3;
	cout << game3;
	cout << "\n-------------------------------== OPERATOR OVERLOADING (game1 == game2)-------------------------------\n";
	cout << "game1 == game2 -> " << (game1 == game2) << endl;
	cout << "\n-------------------------------SCORE-------------------------------\n";
	cout << "Scores for game3: \n";
	cout << "Player1's score: " << game3.getScoreP1() << " | Player2's score: " << game3.getScoreP2() << endl;


	return 0;
}
