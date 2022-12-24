#pragma once
#include <vector>
#include <list>
#include "order.h"
#include "globalFile.h"

typedef long long LL;

class food {
public:
	string food_id;
	string food_name;
	float food_price;
};

class Shop {
public:
	//无参构造
	Shop();

	//操作菜单
	void openMenu() ;

	//查询餐馆信息
	void showInfo();

	//修改餐馆信息
	Shop updateInfo(Shop &shop);

	//注销餐馆信息
	//string delInfo();

	//查询餐馆所有预订
	void queryAll();

	//查询某用户预订
	void queryUser();

	//处理预订
	void dealReserve();

	//获得哈希码
	int getGBKindex();

	//清除内存
	void clear();

	Shop delInfo();

	string shoptype;
	string shopName;
	string shoppwd;
	int S_Id;
	float avgScore;
	float avePrice;
	string address;
	string Tel;
	vector<order> shop_order;
	list<food> shop_foods;
	vector<string> shop_comments;
};
