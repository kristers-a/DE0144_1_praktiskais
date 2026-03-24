#include "pch.h"
#include <iostream>
#include "GameState.h"
#include <cstdlib>

using namespace std;

GameState::GameState(uint32_t Symbols) {
	this->Symbols = Symbols;
	this->ScoreX = 0;
	this->ScoreO = 0;
	this->Turn = false;
}

GameState::GameState(int8_t length) {
	this->Symbols = 0;
	this->ScoreX = 0;
	this->ScoreO = 0;
	this->Turn = false;
	this->symbolLength = length;

	if (length > 25) length = 25;
	else if (length < 15) length = 15;

	for (int i = 0; i < length; i++) {
		// placing each bit in its position
		this->Symbols |= ((std::rand() % 2) << i);
	}
}

GameState MakeMove(GameState state, int pos) {
	//Invalid state/move check
	if (pos < 0 || pos >= state.getLength() - 1) {
		GameState invalidState;
		invalidState.setLength(0); //doesnt go on any further in the game tree
		return invalidState;
	}

	GameState next = state;
	uint32_t symbols = next.getSymbols();
	bool bit1 = (symbols >> pos) & 1; // get the bit at position pos
	bool bit2 = (symbols >> (pos+1)) & 1; // get the bit at position next to pos
	uint32_t res = 0;

	if (next.getTurn()) { // X's turn
		if (!bit1) {
			if (!bit2) { // OO
				next.setScoreX(next.getScoreX() + 2);
			}
			else { // OX
				next.setScoreO(next.getScoreO() - 1); 
			} 
		}
		else { // XX or XO
			next.setLength(0);
			return next;
		}
		res = 1;
	}
	else { // O's turn
		if (bit1) {
			if (bit2) { // XX
				next.setScoreO(next.getScoreO() + 2);
			}
			else { // XO
				next.setScoreX(next.getScoreX() - 1);
			}
		}
		else { // OO or OX
			next.setLength(0);
			return next;
		}
		res = 0;
	}

	uint32_t rightMask = (1U << pos) - 1;  // mask for bits to the right of pos
	uint32_t right = symbols & rightMask;  // right part of result string
	uint32_t left = (symbols >> (pos + 2)) << (pos + 1);  // left part of result string
	symbols = left | (res << pos) | right;  // result string
	// state changing
	next.setSymbols(symbols);
	next.setTurn(!next.getTurn());
	next.setLength(next.getLength() - 1);

	return next;
}