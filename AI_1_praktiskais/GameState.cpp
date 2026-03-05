#include "pch.h"
#include <iostream>
#include "GameState.h"
#include <cstdlib>

using namespace std;

GameState::GameState(uint32_t Symbols) {
	this->Symbols = Symbols;
	this->ScoreX = 0;
	this->ScoreO = 0;
	this->Turn = true;
}

GameState::GameState(int length) {
	this->Symbols = 0;
	this->ScoreX = 0;
	this->ScoreO = 0;
	this->Turn = true;

	if (length > 25) length = 25;

	for (int i = 0; i < length; i++) {
		// placing each bit in its position
		this->Symbols |= ((std::rand() % 2) << i);
	}
}