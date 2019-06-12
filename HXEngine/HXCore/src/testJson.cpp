//#include "stdafx.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using json = nlohmann::json;
using namespace std;

int main()
{
	std::ifstream t("test.meta");
	std::stringstream buffer;
	buffer << t.rdbuf();
	std::string contents(buffer.str());
	//cout << contents << endl;
	auto j = json::parse(contents);
	cout << j["object"] << endl;
	
	system("pause");
    return 0;
}

