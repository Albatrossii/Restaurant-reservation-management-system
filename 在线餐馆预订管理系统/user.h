#pragma once
#include <vector>
#include "order.h"
#include "globalFile.h"

class User 
{
public:
	//无参构造
	User();

	//有参构造
	User(string id, string pwd, LL tel);

	//显示菜单
	void openMenu();

	//展示个人信息
	void showMyInfo();

	//修改个人信息
	User updateMyInfo(User user);

	//删除个人信息
	User deleteMyInfo();

	//查询餐馆
	int queryRes();

	//查看预订
	void queryAllReserve();

	//参看餐馆预订
	void queryResReserve();

	//添加预订
	order addReserve();

	string U_Id;
	string U_pwd;
	LL U_Tel;
	vector<order> user_order;
};

