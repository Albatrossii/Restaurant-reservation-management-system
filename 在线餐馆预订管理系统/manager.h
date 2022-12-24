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
	//�޲ι���
	Manager();
	
	//�������ʱ ����֪�ļ��ı���
	~Manager();

	//ע��ҳ��
	void RegistUser();

	//�ַ����ָ��
	void split(string str, const const char split, list<string>& s);

	//ͨ�����ֲ��ҷ���һ�����ֺ���
	vector<User>::iterator search_User(vector<User>& v, string val);

	//�޸��û�
	void updateUser(int type,User user);

	//�޸Ķ���
	void updateOrder(int type, order& order);

	//�޸��̼�
	void updateShop(int type, Shop shop);

	//�����Ƽ�
	void accommadation();

	void accommadation1();

	//��ѯ�͹��Ƿ����
	void queryRes(int S_name);
	void dijkstra();

	vector<User> users;
	vector<Shop> shops;
	vector<order> orders;

	
	string user_title;
	string order_title;

	//��ϣ��	
	HashTable<int, Shop> ht;
};
