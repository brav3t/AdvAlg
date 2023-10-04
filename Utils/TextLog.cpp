#include "stdafx.h"
#include "TextLog.h"

using namespace std;

void Textlog::clearScreen() {
	log_file << "Clear" << endl;
	log_file.flush();
}

void Textlog::putInfo(string info) {
	log_file << "Info" << "\t" << info << endl;
	log_file.flush();
}
