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
            this->generatedNodes += generatedNodes;
            this->visitedNodes += nodesVisited;
            this->totalTime += elapsedSeconds.count();
        }

        if (aiMoveIndex == -1) {
            FinishGame();
            return;
        }

        HighlightCpuMove(aiMoveIndex);
    }

    void Form1::ResetStats() {
		this->aiMoveCount = 0;

        this->generatedNodes = 0;
        this->visitedNodes = 0;
        this->totalTime = 0.0;
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
            String^ Stats = L"\n\nGameStats:\nGenerated nodes: " + System::Convert::ToString(this->generatedNodes)
                + L"\nVisited nodes: " + System::Convert::ToString(this->visitedNodes) + L"\nAvg time (s): ";

            if (this->aiMoveCount > 0) {
                double avgTime = this->totalTime / this->aiMoveCount;
                Stats += System::Convert::ToString(avgTime);
            } else {
                Stats += L"0";
            }

            message += Stats;
        }

        MessageBox::Show(message, L"Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
}