#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

class Animlog {
	std::ofstream log_file;
public:
	Animlog(std::string filename) : log_file(filename) {
	}

	~Animlog() {
		log_file.close();
	}

	void clearScreen();
	void putInfo(std::string info);
	void putIteration(int iteration);
	void putFitness(float fitness);
	void putPoint(float x, float y, std::string color);
	void putLine(float x1, float y1, float x2, float y2, std::string color);
	void putArrow(float x1, float y1, float x2, float y2, std::string color);
};
