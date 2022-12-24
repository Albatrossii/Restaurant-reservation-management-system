#include "manager.h"
#include <sstream>
#include <cstdlib>
#include <list>
#include <iostream>
#include <queue>
#include "Edge.h"

using namespace std;

void Manager::queryRes(int S_name) {

	auto temp = this->ht.find(S_name);

	if (temp != NULL)
	{
		cout << "为您找到 " << temp->_kv.second.shopName << " 正在显示该餐馆信息 " << endl;
		temp->_kv.second.showInfo();
	}
	else {
		cout << "无法查询到商家信息" << endl;
	}

}

void Manager::split(string str, const const char split,list<string> &s) {
	istringstream iss(str);	// 输入流
	string token;
	int i = 0;
	// 接收缓冲区
	while (getline(iss, token, split))	// 以split为分隔符
	{
		s.push_back(token);
	}
}

//初始化信息 读取所有信息
Manager::Manager() {
	ifstream ifs;

	//先读取信息并封装在容器中
	//首先是用户信息
	
	ifs.open(USER_FILE, ios::in);

	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	getline(ifs, user_title);
	
	User user;
	while (ifs >> user.U_Id && ifs >> user.U_pwd && ifs >> user.U_Tel)
	{		
		users.push_back(user);	
	}
	ifs.close();
	

	//订单信息
	ifs.open(ORDER_FILE, ios::in);

	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	getline(ifs, order_title);

	order order;
	while (ifs >> order.U_Id && ifs >> order.R_Name && ifs >> order.reverse)
	{
		orders.push_back(order);
	}
	//cout << "共读取到" << orders.size() << endl;

	ifs.close();

	//其次是商家信息
	ifs.open(SHOP_FILE, ios::in);

	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	Shop s;
	string readline;

	//int cnt = 0;

	while (getline(ifs,readline))
	{			
		//食物		
		if (readline.substr(0,4)=="food") {
			food f;
			int i = readline.find(',');
			f.food_id = readline.substr(9, i-9);
			i = readline.find('e') + 3;
			int j = readline.rfind(',');
			f.food_name = readline.substr(i, j-i);
			f.food_price = stof(readline.substr(readline.rfind(' ')));				
			s.shop_foods.push_back(f);
			
		}		
		//商家店名
		else if (readline[4] == 'N') {
			s.shopName = readline.substr(10);			
		}
		//商家密码
		else if (readline[4] == 'P') {
			s.shoppwd = readline.substr(14);
		}
		//平均评分
		else if (readline[2] == 'g') {
			
			s.avgScore = stof(readline.substr(9));
			
		}
		//平均价格
		else if (readline[4] == 'r') {
			s.avePrice = stof(readline.substr(10));
			
		}
		//地址
		else if (readline[1] == 'd') {
			s.address = readline.substr(9);
			
		}
		//电话
		else if (readline[3] == 'n') {
			s.Tel = readline.substr(7);
			
		}
		
		else if (readline[4] == 'I') {
			s.S_Id = stoi(readline.substr(8));
		}
		//商家ID
		else if (readline[4] == 't')
		{
			s.shoptype = readline.substr(10);

		}
		//评论
		else if (readline.substr(0,2) =="Co") {
			string com = readline.substr(10);
			s.shop_comments.push_back(com);

			if (readline.at(7) == '9') {
				shops.push_back(s);
				this->ht.insert(make_pair(s.getGBKindex(), s));
				s.shop_comments.clear();
				s.shop_foods.clear();
			}
		}		
	}

	ifs.close();

	cout << "信息加载完成" << endl;
	cout << "为您跳转页面..." << endl;

	system("pause");
	system("cls");
}

//结束操作
Manager ::~Manager() {

	ofstream ofs;
	ofs.open(USER_FILE, ios::out);
	ofs << user_title << endl;
	for (size_t i = 0; i < users.size(); i++)
	{
		ofs << users[i].U_Id << " " << users[i].U_pwd << " " << users[i].U_Tel << endl;
	}
	ofs.close();

	ofs.open(ORDER_FILE, ios::out);
	ofs << order_title << endl;
	for (size_t i = 0; i < orders.size(); i++)
	{
		ofs << orders[i].U_Id << " " << orders[i].R_Name << "\t\t\t" << orders[i].reverse << endl;
	}
	ofs.close();

	
	ofs.open(SHOP_FILE, ios::out);
	for (size_t i = 0; i < shops.size(); i++)
	{
		ofs <<  "shoptype: " << shops[i].shoptype << endl;
		ofs << "shopId: " << shops[i].S_Id << endl;
		ofs << "shopName: " << shops[i].shopName<< endl;
		ofs << "shopPassword: " << shops[i].shoppwd << endl;
		ofs << "avgScore: " << shops[i].avgScore<< endl;
		ofs << "avePrice: " << shops[i].avePrice << endl;
		ofs << "address: " << shops[i].address << endl;
		ofs << "phone: " << shops[i].Tel << endl;
		
		for (auto i : shops[i].shop_foods)
		{
			ofs << "food_id: " << i.food_id << ", food_name: " << i.food_name << ", food_price: " << i.food_price << endl;
		}
		int j = 0;
		for (auto t:shops[i].shop_comments)
		{
			ofs << "Comment" << j << ": " << t << endl;
			j++;
		}

	}
	ofs.close();
	
	cout << "文件保存成功";
	
}

//注册页面
void Manager::RegistUser() {
	string id;
	string pwd;
	LL tel;

	cout << "请输入您要注册的账号（仅支持6位数字）";
	cin >> id;
	
	for (auto user:this->users)
	{
		if (id == user.U_Id) {
			cout << "您输入的账号系统已存在！";
			RegistUser();
			return;
		}
	}
	
	cout << "请输入您的密码（建议6位数字）";
	cin >> pwd;
	cout << "请输入您的联系方式";
	cin >> tel;

	User u(id, pwd, tel);
	//账号列表原本就为有序列表，故可通过折半查找，确定新的注册者插入的位置
	this->users.insert(search_User(this->users, id),u);

}

vector<User>::iterator Manager::search_User(vector<User>& v, string val) {
	
	auto begin = v.begin();
	auto end = v.end();
	while (begin != end) {
		auto mid = begin + (end - begin) / 2;
		if ((mid->U_Id == val))
			return mid;
		else if (stof(mid->U_Id) > stof(val))
			end = mid;
		else
			begin = mid + 1;
	}

	return end;
}

//修改用户
void Manager::updateUser(int type,User user) {
	//删除操作
	if (type == DELETION) {
	
		for (auto i = this->users.begin(); i != this->users.end(); i++)
		{
			if (i->U_Id == user.U_Id) {
				users.erase(i);
				break;
			}
		}
	}
	else if (type == UPDATE)
	{
		for (auto i = this->users.begin(); i != this->users.end(); i++)
		{
			if (i->U_Id == user.U_Id) {
				i->U_Tel = user.U_Tel;
				i->U_pwd = user.U_pwd;
				break;
			}
		}
	}
}

//修改订单
void Manager::updateOrder(int type,order &order) {
	//增加操作
	if (type == ADD) {
		this->orders.push_back(order);
	}
	else if (type == DELETION) {
		for (auto i = this->orders.begin(); i != this->orders.end(); i++)
		{
			if (i->U_Id == order.U_Id && i->R_Name == order.R_Name) {
				orders.erase(i);
				break;
			}
	}
}
}

//修改商家
void Manager::updateShop(int type, Shop shop) {
	if (type == DELETION) {
		ht.erase(shop.getGBKindex());

		for (auto i = shops.begin();i!=shops.end() ; i++)
		{
			if (i->shopName == shop.shopName) {
				this->shops.erase(i);
				break;
			}
		}	
	}	
}

bool cmp(Shop a, Shop b) {
	return a.avgScore > b.avgScore;
}

//餐馆推荐
void Manager::accommadation() {
	cout << "请输入相关的关键词，系统会为您推荐对应的餐厅  " << endl;
	string rtype;
	string cuisine;
	cout << "餐馆类别或特点(比如火锅，地方菜，烤鱼......） " << endl;
	cin >> rtype;
	cout << "特色菜（您可输入想吃的菜名）" << endl;
	cin >> cuisine;

	int cnt = 0, i=0;
	vector<Shop> temp;
		
	for (; i < this->shops.size(); i++)
	{
		
		int j = 0, k = 0;
		int succeed = -1; 
	
		//cnt++;
		
		//首先匹配 特色
		while (k<rtype.size() && j < this->shops[i].shoptype.size())
		{
			if (rtype[k] == this->shops[i].shoptype[j]) {
				k++; j++;
			}
			else {
				k = k - j + 1;
				k= 0;
			}
		}
		if (j >= rtype.size()) succeed++;
		
		//匹配特色菜
		j = 0, k = 0;
		if (!this->shops[i].shopName.find(cuisine[0])== cuisine.npos)
		while (k < cuisine.size() && j < this->shops[i].shopName.size())
		{
			if (cuisine[k] == this->shops[i].shopName[j]) {
				k++; j++;
			}
			else {
				k = k - j + 1;
				k = 0;
			}
		}

		if (j >= cuisine.size()) succeed++;

		if (succeed == 1)
			temp.push_back(this->shops[i]);

		if (succeed == 1)
			cnt++;
	}
	cout << cnt << endl;
	char choice;
	//sort(temp.begin(), temp.end(), cmp);
	
	
	cout << "若数据量较多，系统将为您按照评分为您展暂时展示前五条：" << endl;
	i = 0;
	if (temp.size() == 0) {
		cout << "很抱歉 ，未搜索到相关菜馆" << endl;
	}
	else {
		while (true)
		{
			for (i; i < temp.size(); i++)
			{
				temp[i].showInfo();
				if (i % 5 == 4) break;
			}
			if (i < 5) break;
			cout << "您是否继续往下查看？ y/n " << endl;
			cin >> choice;
			if (choice == 'n' || choice == 'N') {
				break;
			}
		}
	}
}


//餐馆推荐
void Manager::accommadation1() {
	cout << "请输入相关的关键词，系统会为您推荐对应的餐厅  " << endl;
	string rtype;
	string cuisine;
	cout << "餐馆类别或特点(比如火锅，地方菜，烤鱼......） " << endl;
	cin >> rtype;
	cout << "特色菜（您可输入想吃的菜名）" << endl;
	cin >> cuisine;

	int cnt = 0;
	list<Shop> temp;

	for (auto t: this->shops)
	{
		int succeed = -1;
		
		//首先匹配 特色		
		if (t.shoptype.find(rtype) != rtype.npos || t.shopName.find(rtype) != rtype.npos)
			succeed++;

		if (t.shoptype.find(cuisine) != cuisine.npos || t.shopName.find(cuisine) != cuisine.npos)
			succeed++;
		//匹配特色菜
			
		if (succeed == 1)
			temp.push_back(t),cnt++;
	}
	cout << "共搜索到 "<< cnt << "条数据" << endl;

	//sort(temp.begin(), temp.end(), cmp);
	int i = 0;

	if (cnt == 0) {
		cout << "很抱歉 ，未搜索到相关菜馆" << endl;
	}
	else {
		cout << "由于数据量较多时，将为您展示评分前五条：" << endl;
		temp.sort(cmp);
		list<Shop>::iterator t = temp.begin();
		while (true)
		{			
			for ( ;t != temp.end(); t++,i++)
			{
				t->showInfo();
				if (i % 5 == 4 || t == temp.end()) break;
				cout << "----------------------------------------------------" << endl;
			}
			if (cnt < 5 || i == cnt) break;
			char choice;
			cout << "是否按照评分查看其他推荐商家？ y/n " << endl;
			cin >> choice;
			if (choice == 'n' || choice == 'N') {
				break;
			}
		}
	}
}

/*
int head[maxn], cnt = 1, n, m, s, vis[maxn], dis[maxn];

void add(string u, string v, float w) //链式前向星加边
{
	e[cnt].to = v;
	e[cnt].w = w;
	e[cnt].next = head[getGBKindex(u)]; //存储该点的下一条边
	head[getGBKindex(u)] = cnt++;       //更新目前该点的最后一边
}

void Manager::dijkstra() {
	memset(dis, 0x3f3f3f, sizeof dis);

	dis[getGBKindex("郑州轻工业大学")] = 0; //初始化
	q.push(node{ 0, 0 });

	while (!q.empty()) //如果堆栈为空，那么所有点都已经更新
	{
		node x = q.top();
		q.pop();
		int u = x.now; //记录堆顶并将其弹出
		if (vis[u])
			continue;
		vis[u] = 1;
		for (string i = this->ht.find(u)->_kv.second.shopName; i != NULL; i = e[i].next) //搜索堆顶所有的连边
		{
			int v = e[i].to;
			if (dis[v] > dis[u] + e[i].w)
			{
				dis[v] = dis[u] + e[i].w;  //松弛操作
				q.push({ dis[v], v }); //把新遍历的到的点加入堆中
			}
		}
	}
}
*/

