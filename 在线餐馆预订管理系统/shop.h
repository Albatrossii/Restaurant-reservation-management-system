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
	//�޲ι���
	Shop();

	//�����˵�
	void openMenu() ;

	//��ѯ�͹���Ϣ
	void showInfo();

	//�޸Ĳ͹���Ϣ
	Shop updateInfo(Shop &shop);

	//ע���͹���Ϣ
	//string delInfo();

	//��ѯ�͹�����Ԥ��
	void queryAll();

	//��ѯĳ�û�Ԥ��
	void queryUser();

	//����Ԥ��
	void dealReserve();

	//��ù�ϣ��
	int getGBKindex();

	//����ڴ�
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
