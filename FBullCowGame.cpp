#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
		MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	
	return;
}

bool FBullCowGame::IsGameWone() const
{
	return false;
}

bool FBullCowGame::CheckGuessValidity(FString)
{
	return false;
}
// recieves a valid guess increments turn, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	// increment the turn number
	MyCurrentTry++;

	// TODO setup a return variable
	FBullCowCount BullCowCount;

	// loop through all letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) {
		// compare letters agaisnt the hidden word
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++) {
			//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				//if they're in the same place
				if (MHWChar == GChar) {
					BullCowCount.Bulls++; //incriment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}

			}
		}
	}
	return BullCowCount;
}
