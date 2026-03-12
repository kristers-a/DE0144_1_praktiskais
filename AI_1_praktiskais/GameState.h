#pragma once
#include <cstdint>

using namespace std;

class GameState {
protected:
	uint32_t Symbols;	//0=O, 1=X
	int8_t ScoreX;
	int8_t ScoreO;
	bool Turn;			// false = O turn, true = X turn
	int8_t symbolLength;
public:
	GameState() : Symbols(), ScoreX(0), ScoreO(0), Turn(false), symbolLength() {}
	GameState(uint32_t Symbols);
	GameState(int8_t length);

	//returns the uint32 as a number
	uint32_t getSymbols() { return Symbols; }
	int8_t getScoreX() { return ScoreX; }
	int8_t getScoreO() { return ScoreO; }
	bool getTurn() { return Turn; }

	void setSymbols(uint32_t Symbols) { this->Symbols = Symbols; }
	void setScoreX(int8_t ScoreX) { this->ScoreX = ScoreX; }
	void setScoreO(int8_t ScoreO) { this->ScoreO = ScoreO; }
	void setTurn(bool Turn) { this->Turn = Turn; }
	void setLength(int8_t length) { this->symbolLength = length; }

	bool validCheck(const GameState& state, int pos) {
		if (pos < 0 || pos >= state.symbolLength - 1) {
			return false; // Invalid position
		}

		uint32_t symbols = state.getSymbols();
		bool bit1 = (symbols >> pos) & 1;
		bool bit2 = (symbols >> (pos + 1)) & 1;

		if (state.getTurn()) { // X's turn
			if (!bit2) { return true; } // OO or OX
			else { return false; }
		}
		else { // O's turn
			if (bit2) { return true; } // XX or XO
			else { return false; }
		}
	}
};