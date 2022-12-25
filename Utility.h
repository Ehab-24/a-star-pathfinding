#pragma once

#include<Windows.h>

void setColor(int tcl, int bcl = 0) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}