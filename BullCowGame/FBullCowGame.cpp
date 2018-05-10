#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 16}, {7,20} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}


void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; // must be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	if (!IsIsogram(guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	
	if (!IsLowercase(guess))
	{
		return EGuessStatus::Not_Lowercase;
	}

	if (guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}

	return EGuessStatus::OK;
}


// receives valid guess, increment turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
	MyCurrentTry++;
	FBullCowCount bullCowCount;

	const auto length = GetHiddenWordLength();
	for (int32 myWordChar = 0; myWordChar < length; myWordChar++)
	{
		for (int32 guessChar = 0; guessChar < length; guessChar++)
		{
			if (guess[guessChar] == MyHiddenWord[myWordChar])
			{
				if (myWordChar == guessChar)
				{
					bullCowCount.Bulls++;
				}
				else
				{
					bullCowCount.Cows++;
				}
			}
		}
	}

	bGameIsWon = bullCowCount.Bulls == length;

	return bullCowCount;
}

bool FBullCowGame::IsIsogram(FString word) const
{
	if (word.length() <= 1) { return true; }

	TMap<char, bool> letterSeen;
	for (auto letter : word)
	{
		letter = tolower(letter);
		if (letterSeen[letter])
		{
			return false;
		}

		letterSeen[letter] = true;
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString word) const
{
	for (auto letter : word)
	{
		return islower(letter);
	}

	return false;
}
