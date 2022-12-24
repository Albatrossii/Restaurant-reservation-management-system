#pragma once
#include <vector>
#include "order.h"
#include "globalFile.h"

class User 
{
public:
	//�޲ι���
	User();

	//�вι���
	User(string id, string pwd, LL tel);

	//��ʾ�˵�
	void openMenu();

	//չʾ������Ϣ
	void showMyInfo();

	//�޸ĸ�����Ϣ
	User updateMyInfo(User user);

	//ɾ��������Ϣ
	User deleteMyInfo();

	//��ѯ�͹�
	int queryRes();

	//�鿴Ԥ��
	void queryAllReserve();

	//�ο��͹�Ԥ��
	void queryResReserve();

	//���Ԥ��
	order addReserve();

	string U_Id;
	string U_pwd;
	LL U_Tel;
	vector<order> user_order;
};

