#pragma once
#include "GameState.h"
#include <vector>
#include <cstdint>
#include <ostream>

class GameNode {
	private:
		GameState state;
		int movePosition; // the position of the move that led to this state
		std::vector<GameNode*> children; // child nodes representing possible next states

	public:
		GameNode(GameState s, int position = -1) : state(s), movePosition(position) {}

		GameState& getState() { return state; }
		int GetMovePosition() { return movePosition; }
		const std::vector<GameNode*>& getChildren() const { return children; }

		void addChild(GameNode* child) {
			children.push_back(child);
		}

		// Delete child nodes to free up memory
		~GameNode() {
			for (GameNode* child : children) {
				delete child;
			}
		}
};

void generateGameTree(GameNode* root, int8_t depth);
void exportToDot(GameNode* node, std::ostream& out);
void getDotFile(GameNode* root);
int MiniMax(GameNode* node, int depth, bool isMaximizingPlayer, int& nodesVisited);
int AlphaBeta(GameNode* node, int depth, int alpha, int beta, bool isMaximizingPlayer, int& nodesVisited);
int GetAIMove(GameNode* node, int depth, bool useAlphaBeta, int& nodesVisited);