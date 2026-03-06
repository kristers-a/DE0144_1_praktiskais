#pragma once
#include <cstdint>

using namespace std;

class GameState {
protected:
	uint32_t Symbols;	//0=O, 1=X
	int ScoreX;
	int ScoreO;
	bool Turn;			// true = O turn, false = X turn
public:
	GameState() : Symbols(), ScoreX(0), ScoreO(0), Turn(true) {}
	GameState(uint32_t Symbols);
	GameState(int length);

	//returns the uint32 as a number
	uint32_t getSymbols() { return Symbols; }
	int getScoreX() { return ScoreX; }
	int getScoreO() { return ScoreO; }
	bool getTurn() { return Turn; }

	void setSymbols(uint32_t Symbols) { this->Symbols = Symbols; }
	void setScoreX(int ScoreX) { this->ScoreX = ScoreX; }
	void setScoreO(int ScoreO) { this->ScoreO = ScoreO; }
	void setTurn(bool Turn) { this->Turn = Turn; }
};