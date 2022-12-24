#pragma once
#include <iostream>
using namespace std;

//身份抽象基类
class Identity
{
public:

	//操作菜单   纯虚函数
	virtual void operMenu() = 0;

};