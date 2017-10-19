#pragma once
#include <string>
#include <vector>

struct AnimInfo 
{
	std::string strAnimName;
	std::string strFileName;
};

class hxtest
{
public:
	hxtest();
	~hxtest();

	bool LoadFile(std::string strFileName);
	std::vector<AnimInfo> vctAnimsInfo;
};

