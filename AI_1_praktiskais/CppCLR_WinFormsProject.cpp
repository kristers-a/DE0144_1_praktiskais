#include "pch.h"
#include <iostream>
#include <ctime>
#include "GameNode.h"

using namespace System;

#include "Form1.h"

using namespace System::Windows::Forms;

[STAThread]
int main()
{
  srand(time(0));
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);

  CppCLRWinFormsProject::Form1^ form = gcnew CppCLRWinFormsProject::Form1();

  Application::Run(form);

  return 0;
}
