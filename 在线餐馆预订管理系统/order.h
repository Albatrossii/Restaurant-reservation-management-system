#pragma once
#include "globalFile.h"

using namespace std;

class order {
public:

	//�޲ι���
	order();

	//�вι���
	order(string id, string name, string rev);

	string U_Id;
	string R_Name;
	string reverse;
};

