#pragma once
#include <vector>
#include <iostream>

class PathFindingProblem
{
	std::vector<std::vector<int>> map;
	int start_x; int start_y;
	int exit_x; int exit_y;

	int pos_x; int pos_y;
	int direction = 1; // 0 - up, 1 - right, 2 - down, 3 - left

	void forwardPos(int &x, int &y);
protected:
	void start();
	void turnLeft();
	void turnRight();
	bool isWallForward();
	void moveForward();
	bool isExit();
	float distanceToExit();
public:
	void loadMapFromFile(std::string fileName);
	void saveMaptoStream(std::ostream &file);
};

class PathFindingProgrammingProblem : public PathFindingProblem
{
	// machine code
	//0x - goto relative -(x) instructions   // 0 - nop
	//1x - goto relative +(x) instructions   // 10- nop
	//2x - move forward
	//3x - turn left
	//4x - turn right
	//5x - if wall exists forward, skip next instruction
protected:
	const int time_limit = 1000;
	const int max_instruction_code = 59;
	void execute(std::vector<int> machine_code, std::ostream *log);
	void logExecution(std::vector<int> machine_code, std::string log_file);
	float objective(std::vector<int> machine_code);
public:
	void runTestCase(std::string log_filename);
};
