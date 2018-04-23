#pragma once

#include "FBullCowGame.h"
#include <map>

#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

bool FBullCowGame::IsGameWon() const { return bIsGameWon; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "light";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{
		{3,4}, {4,7}, {5, 10}, {6, 16}, {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	for (int32 i = 0; i < WordLength; i++) {
		for (int32 x = 0; x < WordLength; x++) {
			if (Guess[x] == MyHiddenWord[i]) {
				if (x == i) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bIsGameWon = true;
	}
	else {
		bIsGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	if (Word.length() <= 1) {
		return true;
	}

	TMap<char, bool> LetterSeen;

	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
