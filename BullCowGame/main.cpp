/*
 * Console executable that makes use of the BullCowClass
 * Acting as the View (MVC), and is responsible for all
 * user interaction.
 */

#include <iostream>
#include <string>
#include <cctype>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame{};

int main()
{
	bool bPlayGain;
	do
	{
		PrintIntro();
		PlayGame();
		// TODO: Add a game summary
		bPlayGain = AskToPlayAgain();
	} while (bPlayGain);

	return 0;
}

void PrintIntro()
{
	std::cout << "\n\n";
	std::cout << "Welcome to Bulls and Cows, an amazeballs word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
}



void PlayGame()
{
	BCGame.Reset();
	const auto maxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= maxTries)
	{
		const auto guess = GetValidGuess();

		const auto bullCowCount = BCGame.SubmitValidGuess(guess);

		std::cout << "Bulls = " << bullCowCount.Bulls;
		std::cout << ". Cows = " << bullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();

	return;
}

// loop until get valid guess
FText GetValidGuess() // TODO: change to GetValidGuess
{
	EGuessStatus status = EGuessStatus::Invalid_Status;
	FText guess;
	do
	{
		const auto currentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << currentTry << " of " << BCGame.GetMaxTries() << " -- Enter your guess : ";
		getline(std::cin, guess);

		status = BCGame.CheckGuessValidity(guess);
		switch (status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		case EGuessStatus::OK: break;
		default: break;
		}
	} while (status != EGuessStatus::OK);
	return guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? ";
	FText response;
	getline(std::cin, response);
	return (std::tolower(response[0]) == 'y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!!\n";
	}
	else
	{
		std::cout << "Wah, wah...Better luck next time!\n";
	}
}
