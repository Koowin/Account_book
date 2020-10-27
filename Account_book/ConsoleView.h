#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <stdlib.h>

class ConsoleView{

private:

	char input = '0';
	int page = 0;


public:
	void showUI();
	int userUI0();
	int userUI1();
	
	
	void console_clear();
	void line_clear();
	void inputs();
}