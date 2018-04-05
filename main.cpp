/*
This is the cosole executable, that makes use of the BullCow class
This acts as the view in the MVC pattern, and is responsible for all user interation. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game

// entry point of our application
int main()
{
	std::cout << BCGame.GetCurrentTry();

	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0; //exit the application
}


// introduce the game
void PrintIntro() 
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game!\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}


// Plays the game
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while( ! BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)	{
		FText Guess = GetValidGuess(); // TODO make loop checking valid guess

		// sumbit valid guess to the game and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// check and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a valid Isogram word.\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter using lower case only.\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}


bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the smae hidden word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!!!\n";
	}
	else
	{
		std::cout << "Better luck next time!!!\n";
	}
}


