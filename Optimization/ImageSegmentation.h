#pragma once
#include<vector>

class ImageSegmentation
{
	char file_header[54];
protected:
	unsigned int width, height;

	unsigned char* raw_color;
	unsigned char* raw_grayscale;

	char gs_histogram[256];

	int pixg(int x, int y);
	void setPixCluster(int x, int y, unsigned int cluster);

	std::vector<unsigned int> pix_cluster;

public:
	virtual void loadImageFromFile(std::string filename);
	void savePixClusterToFile(std::string filename);
	
	ImageSegmentation() = default;
	~ImageSegmentation();
};
