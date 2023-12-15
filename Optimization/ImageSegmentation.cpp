#include "stdafx.h"
#include "ImageSegmentation.h"
#include <fstream>
#include <iostream>

using namespace std;

int ImageSegmentation::pixg(int x, int y)
{
	return raw_grayscale[y * width + x];
}

void ImageSegmentation::setPixCluster(int x, int y, unsigned int cluster)
{
	pix_cluster[y * width + x] = cluster;
}

void ImageSegmentation::loadImageFromFile(std::string filename)
{
	// load from file
	ifstream is(filename, ios::binary);
	is.seekg(18);
	
	is.read((char*)&width, 4);
	is.read((char*)&height, 4);

	raw_color = new unsigned char[width * height * 3];

	is.seekg(54);
	is.read((char*)raw_color, width * height * 3);

	raw_grayscale = new unsigned char[width * height];
	int i = 0;
	for (unsigned int i = 0; i < width * height; i++) {
		raw_grayscale[i] = (unsigned char)(((float)(raw_color[i * 3]) + (float)(raw_color[i * 3 + 1]) + (float)(raw_color[i * 3 + 2])) / 3);
	}

	is.seekg(0);
	is.read(file_header, 54);

	is.close();

	// create histogram
	for (unsigned int i = 0; i < 255; i++)
		gs_histogram[i] = 0;
	for (unsigned int i = 0; i < width * height; i++)
		gs_histogram[raw_grayscale[i]]++;

	// cluster data
	for(unsigned int i = 0; i < width * height; i++)
		pix_cluster.push_back(0);
}

void ImageSegmentation::savePixClusterToFile(std::string filename)
{
	ofstream os(filename, ios::binary);
	os.write(file_header, 54);
	for (unsigned int i = 0; i < width * height; i++) {
		unsigned char data[3];
		switch (pix_cluster[i]) {
		case 0:
			data[0] = 255;
			data[1] = 100;
			data[2] = 100;
			break;
		case 1:
			data[0] = 100;
			data[1] = 255;
			data[2] = 100;
			break;
		case 2:
			data[0] = 100;
			data[1] = 100;
			data[2] = 255;
			break;
		case 3:
			data[0] = 100;
			data[1] = 255;
			data[2] = 255;
			break;
		case 4:
			data[0] = 255;
			data[1] = 100;
			data[2] = 255;
			break;
		} 
		os.write((char*)data, 3);
	}
	os.close();
}

ImageSegmentation::~ImageSegmentation()
{
	delete[] raw_grayscale;
	delete[] raw_color;
}
