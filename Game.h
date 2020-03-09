//This is my own work.

#ifndef GAME_H
#define GAME_H

#include <cmath>
#include <utility>
#include <ctime>
#include <iostream>
#include "Guess.h"

using namespace std;

class Game {

private:
	Guess currentGuess;
	Guess secretCode;
	int blackPegs, whitePegs, numGuesses;

public:
	Game();
	void playGame();
	void generateFeedback();
	void getUserGuess();
	bool isWinner();
	bool isLoser();
};

Game::Game() {
	blackPegs = 0;
	whitePegs = 0;
	numGuesses = 10;
	secretCode.setMaster();
}

void Game::getUserGuess() {
	cout << "Enter 4 digits between 1 and 6." << endl;
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	currentGuess.setGuess(a, b, c, d);
}

bool Game::isWinner() {
	return blackPegs == 4;
}  //Makes it so you need all 4 black pegs to win.

bool Game::isLoser() {
	return numGuesses == 0;
}  //Returns the number of guesses and makes you lose at 10.

void Game::generateFeedback() {
	blackPegs = whitePegs = 0;
	for (int i = 0; i < 4; i++)
	//When you guess right you get a black peg.
	{
		if (currentGuess[i] == secretCode[i])
			blackPegs++;
	}
	cout << "Black Pegs = " << blackPegs << endl;
	//Creates 2 arrays to keep track of pegs earned by guesses.
	int guessColor[6];
	int codeColor[6];
	for (int i = 0; i < 6; i++)
	{
		guessColor[i] = codeColor[i] = 0;
	}
	for (int i = 0; i < 4; i++)
	{
		guessColor[currentGuess[i] - 1]++;
		codeColor[secretCode[i] - 1]++;
	}
	int inc = 0;
	//Counts the white pegs based off of the arrays.
	for (int i = 0; i < 6; i++)
	{
		int inc = fmin(guessColor[i], codeColor[i]);
		if (inc > 0)
		{
			whitePegs += inc;
		}

	}
	whitePegs = whitePegs - blackPegs;
	cout << "White Pegs = " << whitePegs << endl;
	cout << endl;
}

void Game::playGame() {
	do
	{
		getUserGuess();
		generateFeedback();
		numGuesses--;
		if (isWinner() == true)
			cout << "YOU WIN" << endl;
		else if (isLoser() == true)
			cout << "YOU LOSE" << endl;
	} while (!isWinner() && !isLoser());
}

#endif
