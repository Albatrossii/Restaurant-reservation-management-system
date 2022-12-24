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
		cout << "Ϊ���ҵ� " << temp->_kv.second.shopName << " ������ʾ�ò͹���Ϣ " << endl;
		temp->_kv.second.showInfo();
	}
	else {
		cout << "�޷���ѯ���̼���Ϣ" << endl;
	}

}

void Manager::split(string str, const const char split,list<string> &s) {
	istringstream iss(str);	// ������
	string token;
	int i = 0;
	// ���ջ�����
	while (getline(iss, token, split))	// ��splitΪ�ָ���
	{
		s.push_back(token);
	}
}

//��ʼ����Ϣ ��ȡ������Ϣ
Manager::Manager() {
	ifstream ifs;

	//�ȶ�ȡ��Ϣ����װ��������
	//�������û���Ϣ
	
	ifs.open(USER_FILE, ios::in);

	if (!ifs.is_open()) {
		cout << "�ļ�������" << endl;
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
	

	//������Ϣ
	ifs.open(ORDER_FILE, ios::in);

	if (!ifs.is_open()) {
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	getline(ifs, order_title);

	order order;
	while (ifs >> order.U_Id && ifs >> order.R_Name && ifs >> order.reverse)
	{
		orders.push_back(order);
	}
	//cout << "����ȡ��" << orders.size() << endl;

	ifs.close();

	//������̼���Ϣ
	ifs.open(SHOP_FILE, ios::in);

	if (!ifs.is_open()) {
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	Shop s;
	string readline;

	//int cnt = 0;

	while (getline(ifs,readline))
	{			
		//ʳ��		
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
		//�̼ҵ���
		else if (readline[4] == 'N') {
			s.shopName = readline.substr(10);			
		}
		//�̼�����
		else if (readline[4] == 'P') {
			s.shoppwd = readline.substr(14);
		}
		//ƽ������
		else if (readline[2] == 'g') {
			
			s.avgScore = stof(readline.substr(9));
			
		}
		//ƽ���۸�
		else if (readline[4] == 'r') {
			s.avePrice = stof(readline.substr(10));
			
		}
		//��ַ
		else if (readline[1] == 'd') {
			s.address = readline.substr(9);
			
		}
		//�绰
		else if (readline[3] == 'n') {
			s.Tel = readline.substr(7);
			
		}
		
		else if (readline[4] == 'I') {
			s.S_Id = stoi(readline.substr(8));
		}
		//�̼�ID
		else if (readline[4] == 't')
		{
			s.shoptype = readline.substr(10);

		}
		//����
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

	cout << "��Ϣ�������" << endl;
	cout << "Ϊ����תҳ��..." << endl;

	system("pause");
	system("cls");
}

//��������
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
	
	cout << "�ļ�����ɹ�";
	
}

//ע��ҳ��
void Manager::RegistUser() {
	string id;
	string pwd;
	LL tel;

	cout << "��������Ҫע����˺ţ���֧��6λ���֣�";
	cin >> id;
	
	for (auto user:this->users)
	{
		if (id == user.U_Id) {
			cout << "��������˺�ϵͳ�Ѵ��ڣ�";
			RegistUser();
			return;
		}
	}
	
	cout << "�������������루����6λ���֣�";
	cin >> pwd;
	cout << "������������ϵ��ʽ";
	cin >> tel;

	User u(id, pwd, tel);
	//�˺��б�ԭ����Ϊ�����б��ʿ�ͨ���۰���ң�ȷ���µ�ע���߲����λ��
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

//�޸��û�
void Manager::updateUser(int type,User user) {
	//ɾ������
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

//�޸Ķ���
void Manager::updateOrder(int type,order &order) {
	//���Ӳ���
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

//�޸��̼�
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

//�͹��Ƽ�
void Manager::accommadation() {
	cout << "��������صĹؼ��ʣ�ϵͳ��Ϊ���Ƽ���Ӧ�Ĳ���  " << endl;
	string rtype;
	string cuisine;
	cout << "�͹������ص�(���������ط��ˣ�����......�� " << endl;
	cin >> rtype;
	cout << "��ɫ�ˣ�����������ԵĲ�����" << endl;
	cin >> cuisine;

	int cnt = 0, i=0;
	vector<Shop> temp;
		
	for (; i < this->shops.size(); i++)
	{
		
		int j = 0, k = 0;
		int succeed = -1; 
	
		//cnt++;
		
		//����ƥ�� ��ɫ
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
		
		//ƥ����ɫ��
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
	
	
	cout << "���������϶࣬ϵͳ��Ϊ����������Ϊ��չ��ʱչʾǰ������" << endl;
	i = 0;
	if (temp.size() == 0) {
		cout << "�ܱ�Ǹ ��δ��������ز˹�" << endl;
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
			cout << "���Ƿ�������²鿴�� y/n " << endl;
			cin >> choice;
			if (choice == 'n' || choice == 'N') {
				break;
			}
		}
	}
}


//�͹��Ƽ�
void Manager::accommadation1() {
	cout << "��������صĹؼ��ʣ�ϵͳ��Ϊ���Ƽ���Ӧ�Ĳ���  " << endl;
	string rtype;
	string cuisine;
	cout << "�͹������ص�(���������ط��ˣ�����......�� " << endl;
	cin >> rtype;
	cout << "��ɫ�ˣ�����������ԵĲ�����" << endl;
	cin >> cuisine;

	int cnt = 0;
	list<Shop> temp;

	for (auto t: this->shops)
	{
		int succeed = -1;
		
		//����ƥ�� ��ɫ		
		if (t.shoptype.find(rtype) != rtype.npos || t.shopName.find(rtype) != rtype.npos)
			succeed++;

		if (t.shoptype.find(cuisine) != cuisine.npos || t.shopName.find(cuisine) != cuisine.npos)
			succeed++;
		//ƥ����ɫ��
			
		if (succeed == 1)
			temp.push_back(t),cnt++;
	}
	cout << "�������� "<< cnt << "������" << endl;

	//sort(temp.begin(), temp.end(), cmp);
	int i = 0;

	if (cnt == 0) {
		cout << "�ܱ�Ǹ ��δ��������ز˹�" << endl;
	}
	else {
		cout << "�����������϶�ʱ����Ϊ��չʾ����ǰ������" << endl;
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
			cout << "�Ƿ������ֲ鿴�����Ƽ��̼ң� y/n " << endl;
			cin >> choice;
			if (choice == 'n' || choice == 'N') {
				break;
			}
		}
	}
}

/*
int head[maxn], cnt = 1, n, m, s, vis[maxn], dis[maxn];

void add(string u, string v, float w) //��ʽǰ���Ǽӱ�
{
	e[cnt].to = v;
	e[cnt].w = w;
	e[cnt].next = head[getGBKindex(u)]; //�洢�õ����һ����
	head[getGBKindex(u)] = cnt++;       //����Ŀǰ�õ�����һ��
}

void Manager::dijkstra() {
	memset(dis, 0x3f3f3f, sizeof dis);

	dis[getGBKindex("֣���Ṥҵ��ѧ")] = 0; //��ʼ��
	q.push(node{ 0, 0 });

	while (!q.empty()) //�����ջΪ�գ���ô���е㶼�Ѿ�����
	{
		node x = q.top();
		q.pop();
		int u = x.now; //��¼�Ѷ������䵯��
		if (vis[u])
			continue;
		vis[u] = 1;
		for (string i = this->ht.find(u)->_kv.second.shopName; i != NULL; i = e[i].next) //�����Ѷ����е�����
		{
			int v = e[i].to;
			if (dis[v] > dis[u] + e[i].w)
			{
				dis[v] = dis[u] + e[i].w;  //�ɳڲ���
				q.push({ dis[v], v }); //���±����ĵ��ĵ�������
			}
		}
	}
}
*/

