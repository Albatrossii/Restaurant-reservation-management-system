#pragma once
#include "globalFile.h"
#include "order.h"
#include "shop.h"
#include "user.h"
#include "hash.h"
#include <list>
#include <algorithm>
#include <fstream>

using namespace std;

class Manager {
public:
	//无参构造
	Manager();
	
	//程序结束时 对已知文件的保存
	~Manager();

	//注册页面
	void RegistUser();

	//字符串分割函数
	void split(string str, const const char split, list<string>& s);

	//通过二分查找返回一个二分函数
	vector<User>::iterator search_User(vector<User>& v, string val);

	//修改用户
	void updateUser(int type,User user);

	//修改订单
	void updateOrder(int type, order& order);

	//修改商家
	void updateShop(int type, Shop shop);

	//餐厅推荐
	void accommadation();

	void accommadation1();

	//查询餐馆是否存在
	void queryRes(int S_name);
	void dijkstra();

	vector<User> users;
	vector<Shop> shops;
	vector<order> orders;

	
	string user_title;
	string order_title;

	//哈希表	
	HashTable<int, Shop> ht;
};
