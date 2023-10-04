#include "stdafx.h"
#include "Random.h"
#include <random>

using namespace std;

random_device rd;
mt19937 gen(rd());

// random float between [min, max[
float randomUniform(float min, float max) {
	uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}

// random integer between [min, max]
int randomUniform(int min, int max) {
	uniform_real_distribution<float> dis((float)min, (float)max + 1);
	return (int)dis(gen);
}

// random unsigned integer between [min, max]
unsigned int randomUniform(unsigned int min, unsigned int max) {
	return (unsigned int)randomUniform((int)min, (int)max);
}

// random float between [0, 1[
float randomUniform() {
	uniform_real_distribution<float> dis(0, 1);
	return dis(gen);
}

// ranom gaussian number
float randomNormal(float mean, float stddev) {
	normal_distribution<float> dis(mean, stddev);
	return dis(gen);
}