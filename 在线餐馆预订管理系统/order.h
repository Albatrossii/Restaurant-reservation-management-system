#pragma once
#include "globalFile.h"

using namespace std;

class order {
public:

	//无参构造
	order();

	//有参构造
	order(string id, string name, string rev);

	string U_Id;
	string R_Name;
	string reverse;
};

