#pragma once
#include <string>
#include <vector>
class IOManager
{

public:
	static bool LoadFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	IOManager();
	~IOManager();
};

