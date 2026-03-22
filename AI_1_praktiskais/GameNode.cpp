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

int minimax(GameNode* node, int depth, bool isMaximizingPlayer, int& nodesVisited) {
    nodesVisited++;

    if (depth == 0 || node->getChildren().empty()) {
        return node->getState().getScoreX() - node->getState().getScoreO();
    }

    if (isMaximizingPlayer) {
        int bestValue = -1000000;

        for (GameNode* child : node->getChildren()) {
            int value = minimax(child, depth - 1, false, nodesVisited);
            bestValue = std::max(bestValue, value); 
        }
        return bestValue;
    } 
    else {
        int bestValue = 1000000;

        for (GameNode* child : node->getChildren()) {
            int value = minimax(child, depth - 1, true, nodesVisited);
            bestValue = std::min(bestValue, value);
        }
        return bestValue;
    }
}
}
