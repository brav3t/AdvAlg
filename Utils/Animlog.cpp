#include "stdafx.h"
#include "Animlog.h"

using namespace std;

void Animlog::clearScreen() {
	log_file << "Clear" << endl;
}

void Animlog::putInfo(string info) {
	log_file << "Info" << "\t" << info << endl;
}

void Animlog::putIteration(int iteration) {
	log_file << "Iteration" << "\t" << iteration << endl;
}

void Animlog::putFitness(float fitness) {
	log_file << "Fitness" << "\t" << fitness << endl;
}

void  Animlog::putPoint(float x, float y, string color) {
	log_file << "Point" << "\t" << x << "\t" << y << "\t" << color << endl;
}

void  Animlog::putLine(float x1, float y1, float x2, float y2, string color) {
	log_file << "Line" << "\t" << x1 << "\t" << y1 << "\t" << x2 << "\t" << y2 << "\t" << color << endl;
}

void  Animlog::putArrow(float x1, float y1, float x2, float y2, string color) {
	log_file << "Arrow" << "\t" << x1 << "\t" << y1 << "\t" << x2 << "\t" << y2 << "\t" << color << endl;
}
