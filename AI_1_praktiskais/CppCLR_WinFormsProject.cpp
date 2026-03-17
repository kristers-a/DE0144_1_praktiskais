#include "pch.h"
#include <iostream>
#include <ctime>
#include "GameNode.h"

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
  srand(time(0));
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);

  CppCLRWinFormsProject::Form1^ form = gcnew CppCLRWinFormsProject::Form1();
  form->textBox1->AppendText("Hello World");

  // For debugging purposes
  GameState startState(uint32_t(55666));
  startState.setLength(18);
  GameNode* root = new GameNode(startState);
  generateGameTree(root, 5); // be careful with the depth
  getDotFile(root); //saves the DOT file in the project folder

  Application::Run(form);

  return 0;
}