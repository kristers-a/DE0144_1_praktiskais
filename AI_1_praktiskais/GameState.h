#pragma once
#include <cstdint>

using namespace std;

class GameState {
protected:
	uint32_t Symbols;	//0=O, 1=X
	int8_t ScoreX;
	int8_t ScoreO;
	bool Turn;			// false = O turn, true = X turn
public:
	GameState() : Symbols(), ScoreX(0), ScoreO(0), Turn(false) {}
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

	bool validCheck(const GameState& state, int pos) {
		uint32_t symbols = state.getSymbols();
		bool bit1 = (symbols >> pos) & 1;
		bool bit2 = (symbols >> (pos + 1)) & 1;

		if (state.getTurn()) {
			if (!bit2) { return true; }
			else { return false; }
		}
		else {
			if (bit2) { return true; }
			else { return false; }
		}
	}
};