#include "pch.h"
#include <iostream>

using namespace System;

// int main(array<System::String ^> ^args)
// {
//    return 0;
// }

#include "Form1.h"

using namespace System::Windows::Forms;

[STAThread]
int main()
{
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);

  CppCLRWinFormsProject::Form1^ form = gcnew CppCLRWinFormsProject::Form1();
  form->textBox1->AppendText("Hello World");

  Application::Run(form);

  return 0;
}

struct Node {
    std::string string; // Current string of X and O
    int scoreO;         // O score
    int scoreX;         // X score
    bool turn;          // true - O turn, false - X turn
};