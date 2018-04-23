#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

FBullCowGame BCGame;

void PrintIntro() {
	std::cout << "Welcome to Bulls and Cows Word Game\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter word I'm thinking of? (No repeating characters)\n";
	std::cout << "Cows represent letters that exist in the word, but in the wrong position." << std::endl;
	std::cout << "Bulls represent letters that exist in the word AND in the correct position." << std::endl;
	std::cout << std::endl;
	return;
}

std::string GetGuess() {
	int CurrentTry = BCGame.GetCurrentTry();

	std::cout << "Try " << CurrentTry << ". ";
	std::cout << "Enter your guess: ";
	std::string Guess = "";
	getline(std::cin, Guess);
	return Guess;
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "YOU WON! \n";
	}
	else {
		std::cout << "Better luck next time!\n";
	}
}

FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << " Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letter.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

int main() {
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;
}