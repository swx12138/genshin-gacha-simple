#pragma once

#include <Windows.h>

class console
{
public:
	static BOOL SetTextWhite()
	{
		return SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	static BOOL SetTextRed()
	{
		return SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_RED);
	}
	static BOOL SetTextGreen()
	{
		return SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	}
	static BOOL SetTextBlue()
	{
		return SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	}
	static BOOL SetTextPink()
	{
		return SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	}
	static BOOL SetTextGreenBlue()
	{
		return SetConsoleTextAttribute(hStdOut, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	static BOOL SetTextGolden()
	{
		return SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN);
	}
private:
	static HANDLE hStdOut;
};

HANDLE console::hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);