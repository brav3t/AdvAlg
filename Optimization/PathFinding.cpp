#include "stdafx.h"
#include "PathFinding.h"
#include <fstream>
#include <string>

using namespace std;

//
// PathFindingProgrammingProblem
//
void PathFindingProblem::forwardPos(int &x, int &y) {
	x = pos_x + ((direction == 1 || direction == 3) ? -(direction - 2) : 0);
	y = pos_y + ((direction == 0 || direction == 2) ? (direction - 1) : 0);
}

void PathFindingProblem::start() {
	pos_x = start_x;
	pos_y = start_y;
	direction = 1;
}

void PathFindingProblem::turnLeft() {
	direction = (direction - 1 + 4) % 4;
}

void PathFindingProblem::turnRight() {
	direction = (direction + 1) % 4;
}

bool PathFindingProblem::isWallForward() {
	int next_x, next_y;
	forwardPos(next_x, next_y);
	return map[next_y][next_x] == 1;
}

void PathFindingProblem::moveForward() {
	if (!isWallForward())
		forwardPos(pos_x, pos_y);
}

bool PathFindingProblem::isExit() {
	return pos_x == exit_x && pos_y == exit_y;
}

float PathFindingProblem::distanceToExit() {
	if (isExit())
		return 0;
	return (float)sqrt(pow(pos_x - exit_x, 2) + pow(pos_y - exit_y, 2));
}

void PathFindingProblem::loadMapFromFile(std::string fileName)
{
	map.clear();
	vector<int> map_line;

	ifstream fmap(fileName);
	fmap.unsetf(ios_base::skipws);
	int x = 0; int y = 0;

	while (!fmap.eof()) {
		char chr;
		fmap >> chr;
		if (chr == 13 || chr == 10) {
			if (map_line.size() != 0) {
				map.push_back(map_line);
				map_line.clear();
				y++;
				x = 0;
			}
		}
		else {
			if (chr == '*')
				map_line.push_back(1);
			else
			{
				map_line.push_back(0);
				if (chr == 'S') {
					start_x = x;
					start_y = y;
				}
				else if (chr == 'E') {
					exit_x = x;
					exit_y = y;
				}
			}
			x++;
		}
	}
	fmap.close();
}

void PathFindingProblem::saveMaptoStream(ostream &file)
{
	for (int y = 0; y <= 9; y++) {
		for (int x = 0; x <= 9; x++) {
			unsigned char chr = ' ';
			if (x == pos_x && y == pos_y)
				switch (direction) {
				case 0: chr = 193; break;
				case 1: chr = 195; break;
				case 2: chr = 194; break;
				case 3: chr = 180; break;
				}
			else
				if (map[y][x] == 1)
					chr = '*';
				else if (x == start_x && y == start_y)
					chr = 'S';
				else
					if (x == exit_x && y == exit_y)
						chr = 'E';
			file << chr;
		}
		file << endl;
	}
}

//
// PathFindingProgrammingProblem
//
void PathFindingProgrammingProblem::execute(std::vector<int> machine_code, ostream *log) {
	start();
	if (log != nullptr) saveMaptoStream(*log);
	int t = 0;
	unsigned int ip = 0;
	while (!isExit() && t < time_limit && ip < machine_code.size()) {
		int cmd = machine_code[ip];
		switch (cmd / 10) {
		case 0:
			ip -= (cmd % 10 + 1);
			break;
		case 1:
			ip += (cmd % 10 - 1);
			break;
		case 2:
			moveForward();
			break;
		case 3:
			turnLeft();
			break;
		case 4:
			turnRight();
			break;
		case 5:
			if (isWallForward())
				ip++;
		}
		ip++;

		if (log != nullptr) {
			*log << "Time:" << t << endl;
			saveMaptoStream(*log);
		}
		t++;
	}
}

float PathFindingProgrammingProblem::objective(std::vector<int> machine_code) {
	execute(machine_code, nullptr);
	return distanceToExit();
}

void PathFindingProgrammingProblem::logExecution(std::vector<int> machine_code, string log_file) {
	ofstream *log = new ofstream(log_file);
	*log << "Program code:" << endl;
	for (unsigned int ip = 0; ip < machine_code.size(); ip++)
	{
		int cmd = machine_code[ip];
		switch (cmd / 10) {
		case 0:
			*log << "GOTO -" << to_string(cmd % 10) << endl;
			break;
		case 1:
			*log << "GOTO +" << to_string(cmd % 10) << endl;
			break;
		case 2:
			*log << "MOVE" << endl;
			break;
		case 3:
			*log << "LEFT" << endl;
			break;
		case 4:
			*log << "RIGHT" << endl;
			break;
		case 5:
			*log << "IF_WALL_SKIP_NEXT" << endl;
		}
	}
	*log << endl << "Execution log:" << endl;
	execute(machine_code, log);
	log->close();
}

void PathFindingProgrammingProblem::runTestCase(string log_filename) {
	std::vector<int> sample_code{
		40,	// 0 - LEFT
		40, // 1 - LEFT
		30, // 2 - RIGHT
		50, // 3 - IF_WALL_SKIP_NEXT
		12, // 4 - GOTO +2
		03, // 5 - GOTO -3
		20, // 6 - MOVE
		07  // 7 - GOTO -7
	};

	logExecution(sample_code, log_filename);
}
