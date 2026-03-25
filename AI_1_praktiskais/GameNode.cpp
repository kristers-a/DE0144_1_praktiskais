#include "pch.h"
#include "GameNode.h"
#include <cstdint>
#include <fstream>

void generateGameTree(GameNode* root, int8_t depth) {
	//Stop if the game is over
	if (depth <= 0 || root->getState().getLength() <= 1) return;

	GameState& currentState = root->getState();
	int currentLength = currentState.getLength();

	for (int i = 0; i < currentLength; i++) {
		if (currentState.validCheck(currentState, i)) {
			GameState nextState = MakeMove(currentState, i);
			GameNode* childNode = new GameNode(nextState, i);
			root->addChild(childNode);
			generateGameTree(childNode, depth - 1);
		}
	}
}

// Count nodes in the tree (including root)
int CountNodes(GameNode* root) {
	if (!root) return 0;
	int count = 1;
	for (GameNode* child : root->getChildren()) {
		count += CountNodes(child);
	}
	return count;
}

//Only for debugging purposes
void exportToDot(GameNode* node, std::ostream& out) {
    if (!node) return;

    out << 
		"  node" <<
		node <<		//memory address of the node
		" [label=\"Pos: " <<
		node->GetMovePosition()	<<	//the position of the move that led to this state 
		"\\nScoreX: " << 
		(int)node->getState().getScoreX() <<
		"\\nScoreO: " << 
		(int)node->getState().getScoreO() << 
		"\"];" << 
		std::endl;

	//links for child nodes
    for (GameNode* child : node->getChildren()) {
        if (child) {
            out << 
				"  node" << 
				node <<		//memory address of the parent node
				" -> node" <<	//link between the parent and child nodes
				child <<	//memory address of the child node
				";" << 
				std::endl;

            exportToDot(child, out);
        }
    }
}

void getDotFile(GameNode* root) {

	std::ofstream outFile("game_tree.dot");
	if (outFile.is_open()) {
		outFile <<	//start of the DOT file
			"digraph G {" << 
			std::endl;
		exportToDot(root, outFile);
		outFile <<	//end of the DOT file
			"}" << 
			std::endl;
		outFile.close();
	}
}

#include <algorithm>

int MiniMax(GameNode* node, int depth, bool isMaximizingPlayer, int& nodesVisited) {
    nodesVisited++;

    if (depth == 0 || node->getChildren().empty()) {
        return node->getState().evaluate();
    }

    if (isMaximizingPlayer) {
        int bestValue = -1000000;

        for (GameNode* child : node->getChildren()) {
            int value = MiniMax(child, depth - 1, false, nodesVisited);
            bestValue = std::max(bestValue, value); 
        }
        return bestValue;
    } 
    else {
        int bestValue = 1000000;

        for (GameNode* child : node->getChildren()) {
            int value = MiniMax(child, depth - 1, true, nodesVisited);
            bestValue = std::min(bestValue, value);
        }
        return bestValue;
    }
}

int AlphaBeta(GameNode* node, int depth, int alpha, int beta, bool isMaximizingPlayer, int& nodesVisited) {
    nodesVisited++;

    if (depth == 0 || node->getChildren().empty()) {
        return node->getState().evaluate();
    }

    if (isMaximizingPlayer) {
        int bestValue = -1000000;

        for (GameNode* child : node->getChildren()) {
            int value = AlphaBeta(child, depth - 1, alpha, beta, false, nodesVisited);
            bestValue = std::max(bestValue, value);

            alpha = std::max(alpha, bestValue);
            if (beta <= alpha) {
                break;
            }
        }
        return bestValue;
    }
    else {
        int bestValue = 1000000;

        for (GameNode* child : node->getChildren()) {
            int value = AlphaBeta(child, depth - 1, alpha, beta, true, nodesVisited);
            bestValue = std::min(bestValue, value);

            beta = std::min(beta, bestValue);
            if (beta <= alpha) {
                break;
            }
        }
        return bestValue;
    }
}

int GetAIMove(GameNode* node, int depth, bool useAlphaBeta, int& nodesVisited) {
    int bestMove = -1;
    int bestValue = -1000000;
    nodesVisited = 0;

    //Check if there are moves
    if (node->getChildren().empty()) return -1;

    for (GameNode* child : node->getChildren()) {
        int value = 0;
        if (useAlphaBeta) {
            value = AlphaBeta(child, depth - 1, -1000000, 1000000, false, nodesVisited);
        } else {
            value = MiniMax(child, depth - 1, false, nodesVisited);
        }

        if (value > bestValue) {
            bestValue = value;
            bestMove = child->GetMovePosition();
        }
    }
    return bestMove;
}