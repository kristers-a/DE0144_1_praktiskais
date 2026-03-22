#pragma once

namespace CppCLRWinFormsProject {

    using namespace System;
    using namespace System::Drawing;
    using namespace System::Windows::Forms;

    public ref class Form1 : public Form {
    private:
        GameState* gameState;
        int selectedIndex;
        int aiMoveIndex;

        cli::array<Button^>^ symbolButtons;

        RadioButton^ rbO;
        RadioButton^ rbX;
        RadioButton^ rbMinimax;
        RadioButton^ rbAlphaBeta;

        Panel^ sequencePanel;

        Label^ playerScoreLabel;
        Label^ computerScoreLabel;
        Label^ statusLabel;

        Button^ newGameButton;
        NumericUpDown^ lengthSelector;

        Timer^ computerTurnTimer;
        System::ComponentModel::Container^ components;

    public:
        Form1() {
            gameState = nullptr;
            selectedIndex = -1;
            aiMoveIndex = -1;
            symbolButtons = nullptr;
            components = nullptr;

            InitializeComponent();

            computerTurnTimer = gcnew Timer();
            computerTurnTimer->Interval = 800;
            computerTurnTimer->Tick += gcnew EventHandler(this, &Form1::HandleComputerTurn);
        }

    protected:
        ~Form1() {
            if (components) {
                delete components;
            }

            if (gameState) {
                delete gameState;
            }
        }

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

        void InitializeComponent() {
            this->Text = L"X-O Game";
            this->Height = 290;
            this->Width = 900;

            lengthSelector = gcnew NumericUpDown();
            lengthSelector->Minimum = 15;
            lengthSelector->Maximum = 25;
            lengthSelector->Value = 20;
            lengthSelector->Width = 50;
            lengthSelector->Location = Point(125, 11);

            newGameButton = gcnew Button();
            newGameButton->Text = L"New Game";
            newGameButton->Width = 100;
            newGameButton->Location = Point(185, 10);
            newGameButton->Click += gcnew EventHandler(this, &Form1::StartNewGame);

            rbO = gcnew RadioButton();
            rbO->Text = L"Play as O";
            rbO->Checked = true;
            rbO->AutoSize = true;
            rbO->Location = Point(300, 12);

            rbX = gcnew RadioButton();
            rbX->Text = L"Play as X";
            rbX->AutoSize = true;
            rbX->Location = Point(390, 12);

            // Разделитель
            Label^ lblAlgorithm = CreateLabel(L"Algorithm:", 10, 42);

            rbMinimax = gcnew RadioButton();
            rbMinimax->Text = L"Minimax";
            rbMinimax->Checked = true;
            rbMinimax->AutoSize = true;
            rbMinimax->Location = Point(125, 40);

            rbAlphaBeta = gcnew RadioButton();
            rbAlphaBeta->Text = L"Alpha-Beta";
            rbAlphaBeta->AutoSize = true;
            rbAlphaBeta->Location = Point(220, 40);

            sequencePanel = gcnew Panel();
            sequencePanel->Location = Point(5, 75);
            sequencePanel->Size = Drawing::Size(900, 66);

            playerScoreLabel = CreateLabel(L"Player (O): 0", 10, 185);
            computerScoreLabel = CreateLabel(L"Computer (X): 0", 10, 205);
            statusLabel = CreateLabel(L"Press New Game", 300, 185);

            this->Controls->Add(CreateLabel(L"Length (15-25):", 10, 14));
            this->Controls->Add(lengthSelector);
            this->Controls->Add(newGameButton);
            this->Controls->Add(rbO);
            this->Controls->Add(rbX);
            this->Controls->Add(lblAlgorithm);
            this->Controls->Add(rbMinimax);
            this->Controls->Add(rbAlphaBeta);
            this->Controls->Add(sequencePanel);
            this->Controls->Add(playerScoreLabel);
            this->Controls->Add(computerScoreLabel);
            this->Controls->Add(statusLabel);
        }

        void StartNewGame(Object^ sender, EventArgs^ e) {
            if (gameState) {
                delete gameState;
            }

            gameState = new GameState((int8_t)lengthSelector->Value);
            selectedIndex = -1;

            rbO->Visible = false;
            rbX->Visible = false;
            rbMinimax->Visible = false;
            rbAlphaBeta->Visible = false;

            this->Width = gameState->getLength() * 50 + 80;

            RefreshSequence();
            UpdateScoreLabels();

            if (rbX->Checked) {
                gameState->setTurn(false);
                statusLabel->Text = L"Computer is thinking...";
                newGameButton->Enabled = false;
                computerTurnTimer->Start();
            }
            else {
                statusLabel->Text = L"Your turn";
            }
        }

        void RefreshSequence() {
            sequencePanel->Controls->Clear();

            int length = gameState->getLength();
            sequencePanel->Width = length * 50 + 10;
            symbolButtons = gcnew cli::array<Button^>(length);

            for (int i = 0; i < length; i++) {
                Label^ lbl = gcnew Label();
                lbl->Width = 46;
                lbl->Height = 46;
                lbl->Left = 5 + i * 50;
                lbl->Top = 5;  // just below the 46px button + 5px top padding
                lbl->Text = ((gameState->getSymbols() >> i) & 1) ? L"X" : L"O";
                lbl->TextAlign = ContentAlignment::MiddleCenter;
                lbl->Font = gcnew Drawing::Font(this->Font->FontFamily, 8, FontStyle::Regular);

                // Make pretty 
                lbl->BorderStyle = BorderStyle::FixedSingle; // gives it a box outline
                lbl->BackColor = Color::White;  // labels ignore Transparent, needs explicit color
                lbl->ForeColor = Color::Black;
                lbl->Enabled = false;  // disables hit detection and lets it pass to the buttons
                sequencePanel->Controls->Add(lbl);
            }


            for (int i = 0; i < length-1; i++) {
                // Tile them and make them work
                Button^ button = gcnew Button();
                button->Width = 46;
                button->Height = 46;
                button->Left = (button->Width/2)+5 + i * 50;
                button->Top = 5;
                //button->Font = gcnew Drawing::Font(this->Font->FontFamily, 15, FontStyle::Bold);
                button->Tag = i;
                //button->Text = ((gameState->getSymbols() >> i) & 1) ? L"X" : L"O";
                button->Text = "";
                button->Click += gcnew EventHandler(this, &Form1::HandleSymbolClick);

                // Make it look nice
                button->FlatStyle = FlatStyle::Flat;
                button->FlatAppearance->BorderColor = Color::Red;
                button->FlatAppearance->BorderSize = 0;
                button->BackColor = Color::Transparent;
                button->FlatAppearance->MouseOverBackColor = Color::Transparent;
                button->ForeColor = Color::Black; // or whatever text color you want
                
                //button->BackColor = Color::Blue;
                //button->ForeColor = Color::Transparent;          // hide text too
                button->MouseEnter += gcnew EventHandler(this, &Form1::SymbolButton_OnHover);
                button->MouseLeave += gcnew EventHandler(this, &Form1::SymbolButton_OffHover);

                // Add
                sequencePanel->Controls->Add(button);
                symbolButtons[i] = button;
            }




        }

        void HandleSymbolClick(Object^ sender, EventArgs^ e) {
            if (!gameState) {
                return;
            }

            if (rbO->Checked && gameState->getTurn()) {
                return;
            }

            if (rbX->Checked && !gameState->getTurn()) {
                return;
            }

            int clickedIndex = safe_cast<int>(safe_cast<Button^>(sender)->Tag);

            if (selectedIndex == -1) {
                selectedIndex = clickedIndex;
                symbolButtons[clickedIndex]->BackColor = Color::Yellow;
                return;
            }

            if (clickedIndex == selectedIndex) {
                symbolButtons[clickedIndex]->ResetBackColor();
                selectedIndex = -1;
                return;
            }

            int leftIndex = Math::Min(clickedIndex, selectedIndex);

            if (Math::Abs(clickedIndex - selectedIndex) != 1 || !gameState->validCheck(*gameState, leftIndex)) {
                symbolButtons[selectedIndex]->BackColor = Color::Red;
                symbolButtons[clickedIndex]->BackColor = Color::Red;
                selectedIndex = -1;
                RefreshSequence();
                return;
            }

            *gameState = MakeMove(*gameState, leftIndex);
            selectedIndex = -1;

            RefreshSequence();
            UpdateScoreLabels();

            if (!IsGameOver()) {
                statusLabel->Text = L"Computer is thinking...";
                newGameButton->Enabled = false;
                computerTurnTimer->Start();
            }
        }

        void HandleComputerTurn(Object^ sender, EventArgs^ e) {
            computerTurnTimer->Stop();

            if (rbMinimax->Checked) {
                // minimax
            }
            else {
                // TODO: alphabeta
            }
            aiMoveIndex = -1;

            if (aiMoveIndex == -1) {
                FinishGame();
                return;
            }

            *gameState = MakeMove(*gameState, aiMoveIndex);

            RefreshSequence();
            UpdateScoreLabels();

            newGameButton->Enabled = true;

            if (!IsGameOver()) {
                statusLabel->Text = L"Your turn";
            }
        }

        bool IsGameOver() {
            if (gameState->getLength() <= 1) {
                FinishGame();
                return true;
            }

            for (int i = 0; i < gameState->getLength() - 1; i++) {
                if (gameState->validCheck(*gameState, i)) {
                    return false;
                }
            }

            FinishGame();
            return true;
        }

        void FinishGame() {
            int playerOScore = (int)gameState->getScoreO();
            int playerXScore = (int)gameState->getScoreX();

            statusLabel->Text = L"Game over";
            rbO->Visible = true;
            rbX->Visible = true;
            rbMinimax->Visible = true;
            rbAlphaBeta->Visible = true;
            newGameButton->Enabled = true;

            RefreshSequence();

            MessageBox::Show(
                (playerOScore > playerXScore ? L"Player (O) wins!" : playerXScore > playerOScore ? L"Player (X) wins!" : L"Draw!") +
                L"\n\nO: " + playerOScore.ToString() + L"  X: " + playerXScore.ToString(),
                L"Game Over",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information
            );
        }

        void UpdateScoreLabels() {
            playerScoreLabel->Text = L"Player (O): " + ((int)gameState->getScoreO()).ToString();
            computerScoreLabel->Text = L"Computer (X): " + ((int)gameState->getScoreX()).ToString();
        }

        void SymbolButton_OnHover(Object^ sender, EventArgs^ e) {
            Button^ btn = safe_cast<Button^>(sender);
            btn->FlatAppearance->BorderSize = 2;
            btn->ForeColor = Color::Black;

            // Grow: 2x width, +5 height
            int newW = btn->Width * 2 + 10;    // 46 -> 92
            int newH = btn->Height + 10;   // 46 -> 51

            // Shift left to keep it centered over the original position
            int origCenter = btn->Left + 46 / 2;  // center of original size
            btn->Left = origCenter - newW / 2 + 10/4;
            btn->Top = btn->Top - 10 / 2;       // center vertically too
            btn->Width = newW;
            btn->Height = newH;
            //btn->BringToFront();
        }

        void SymbolButton_OffHover(Object^ sender, EventArgs^ e) {
            Button^ btn = safe_cast<Button^>(sender);
            btn->FlatAppearance->BorderSize = 0;
            btn->ForeColor = Color::Transparent;

            // Restore original size and position
            int i = safe_cast<int>(btn->Tag);
            btn->Width = 46;
            btn->Height = 46;
            btn->Left = (46/2)+5 + i * 50;  // recalculate from index
            btn->Top = 5;
            //btn->SendToBack();
        }
    };
}
