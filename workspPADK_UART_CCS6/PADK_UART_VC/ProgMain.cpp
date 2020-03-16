#include "stdafx.h"
#include "MyForm.h"


using namespace System;
using namespace System::Windows::Forms;
using namespace PADK_UART_VC;

// Definicja zmiennych globalnych
int x = 0;


[STAThread]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	MyForm form;
	Application::Run(%form);


}

