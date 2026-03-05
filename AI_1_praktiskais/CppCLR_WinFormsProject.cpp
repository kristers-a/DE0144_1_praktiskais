#include "pch.h"
#include <iostream>
#include <ctime>

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

  Application::Run(form);

  return 0;
}