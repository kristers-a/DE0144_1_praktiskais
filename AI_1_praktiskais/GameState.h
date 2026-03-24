#pragma once
#include <cstdint>


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
	int8_t getLength() { return symbolLength; }

	void setSymbols(uint32_t Symbols) { this->Symbols = Symbols; }
	void setScoreX(int8_t ScoreX) { this->ScoreX = ScoreX; }
	void setScoreO(int8_t ScoreO) { this->ScoreO = ScoreO; }
	void setTurn(bool Turn) { this->Turn = Turn; }
	void setLength(int8_t length) { this->symbolLength = length; }

	bool validCheck(const GameState& state, int pos) {
		if (pos < 0 || pos >= state.symbolLength - 1) {
			return false; // Invalid position
		}

		uint32_t symbols = state.Symbols;
		bool bit1 = (symbols >> pos) & 1;
		bool bit2 = (symbols >> (pos + 1)) & 1;

		if (state.Turn) { // X's turn
			return !bit1; //OO or OX
		}
		else { // O's turn
			return bit1; //XX or XO
		}
	}

	int evaluate() {
		// Skaita starpība
		int score = this->getScoreX() - this->getScoreO();

		// Potenciālo gājienu novērtējums
		uint32_t symbols = this->getSymbols();
		int length = this->getLength();

		int potentialX = 0;
		int potentialO = 0;

		for (int i = 0; i < length - 1; i++) {
			bool bit1 = (symbols >> i) & 1;
			bool bit2 = (symbols >> (i + 1)) & 1;

			if (this->getTurn()) { // X's turn requires !bit1 (left is O)
				if (!bit1 && !bit2) potentialX += 2; // OO
				if (!bit1 && bit2)  potentialX += 1; // OX (Wait, maybe potentialX changes, but let's just make the condition match !bit1)
			}
			else { // O's turn requires bit1 (left is X)
				if (bit1 && bit2)   potentialO += 2; // XX
				if (bit1 && !bit2)  potentialO += 1; // XO
			}
		}

		// Kopējais heiristiskais novērtējums
		return score + potentialX - potentialO;
	}
};

GameState MakeMove(GameState state, int pos);
