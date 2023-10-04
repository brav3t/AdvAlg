#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

class Textlog
{
	std::ofstream log_file;
public:
	Textlog(std::string filename) : log_file(filename) {
	}

	~Textlog() {
		log_file.close();
	}

	void clearScreen();
	void putInfo(std::string info);
};

