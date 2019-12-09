// GammaTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GlfwRenderWindow.h"

int main()
{
	CGlfwRenderWindow* pRenderWindow = new CGlfwRenderWindow(800, 600);
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));
	// Main message loop:
	while (!glfwWindowShouldClose(pRenderWindow->GetMainWindow()))
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		pRenderWindow->Render();
		Sleep(0);
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
