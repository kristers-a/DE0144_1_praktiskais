#include "pch.h"
#include "Form1.h"
#include <chrono>

namespace CppCLRWinFormsProject {
    void Form1::HandleComputerTurn(Object^ sender, EventArgs^ e) {
        computerTurnTimer->Stop();
        if (!gameState || IsGameOver()) return;

        auto startTime = std::chrono::high_resolution_clock::now();

        int nodesVisited = 0;
        int depth = 6; // lower if the AI takes too long on its turn
        bool useAlphaBeta = rbAlphaBeta->Checked;

        //Generate the game tree for the current position
        GameNode* root = new GameNode(*gameState);
        generateGameTree(root, depth);

        // Count generated nodes in the tree
        int generatedNodes = 0;
		if (testingMode) generatedNodes = CountNodes(root);

        //Get the index of the move the AI wants to make
        aiMoveIndex = GetAIMove(root, depth, useAlphaBeta, nodesVisited);

        //Clean up memory, by deleting the tree
        delete root;

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedSeconds = endTime - startTime;

        //Save stats
        if (testingMode) {
			this->aiMoveCount++;
            if (useAlphaBeta) {
                this->generatedNodesAlpha += generatedNodes;
                this->visitedNodesAlpha += nodesVisited;
                this->totalTimeAlpha += elapsedSeconds.count();
            } else {
                this->generatedNodesMinimax += generatedNodes;
                this->visitedNodesMinimax += nodesVisited;
                this->totalTimeMinimax += elapsedSeconds.count();
            }
        }

        if (aiMoveIndex == -1) {
            FinishGame();
            return;
        }

        HighlightCpuMove(aiMoveIndex);
    }

    void Form1::ResetStats() {
		this->aiMoveCount = 0;

        this->generatedNodesMinimax = 0;
        this->visitedNodesMinimax = 0;
        this->totalTimeMinimax = 0.0;

        this->generatedNodesAlpha = 0;
        this->visitedNodesAlpha = 0;
        this->totalTimeAlpha = 0.0;
    }

    void Form1::FinishGame() {
        int playerOScore = (int)gameState->getScoreO();
        int playerXScore = (int)gameState->getScoreX();

        statusLabel->Text = L"Game over";
        groupSelectPlayer->Visible = true;
        groupSelectAlgorithm->Visible = true;
        newGameButton->Enabled = true;

        RefreshSequence();

        String^ resultText;
        if (playerOScore > playerXScore) resultText = L"Player (O) wins!";
        else if (playerXScore > playerOScore) resultText = L"Player (X) wins!";
        else resultText = L"Draw!";

        String^ message = resultText + L"\n\nO: " + System::Convert::ToString(playerOScore) + L"  X: " + System::Convert::ToString(playerXScore);

        if (testingMode) {
            if (currentGameUseAlphaBeta) {
                String^ alphaStats = L"\n\nAlpha-Beta Stats:\nGenerated nodes: " + System::Convert::ToString(this->generatedNodesAlpha)
                    + L"\nVisited nodes: " + System::Convert::ToString(this->visitedNodesAlpha) + L"\nAvg time (s): ";

                if (this->aiMoveCount > 0) {
                    double avgAlpha = this->totalTimeAlpha / this->aiMoveCount;
                    alphaStats += System::Convert::ToString(avgAlpha);
                } else {
                    alphaStats += L"0";
                }

                message += alphaStats;

            } else {
                String^ minimaxStats = L"\n\nMinimax Stats:\nGenerated nodes: " + System::Convert::ToString(this->generatedNodesMinimax)
                    + L"\nVisited nodes: " + System::Convert::ToString(this->visitedNodesMinimax) + L"\nAvg time (s): ";

                if (this->aiMoveCount > 0) {
                    double avgMinimax = this->totalTimeMinimax / this->aiMoveCount;
                    minimaxStats += System::Convert::ToString(avgMinimax);
                } else {
                    minimaxStats += L"0";
                }

                message += minimaxStats;
            }
        }

        MessageBox::Show(message, L"Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
}