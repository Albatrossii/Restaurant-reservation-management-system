#include "globalFile.h"
#include "manager.h"
#include<cstdlib>

using namespace std;

int getGBK(string s) {

	return ((unsigned char)s[0] - 129) * 190 + ((unsigned char)s[3] - 129) +
		((unsigned char)s[2] - 64) - (unsigned char)s[1] / 128;
}


//�����û�������
void UserMenu(User& user,Manager &m)
{
	while (true)
	{

		//�����û��Ӳ˵�
		user.openMenu();

		int select = 0;
		cin >> select; //�����û�ѡ��

		if (select == 1) //�鿴������Ϣ
		{
			user.showMyInfo();
		}
		else if (select == 2) //�޸ĸ�����Ϣ
		{
			user = user.updateMyInfo(user);
			m.updateUser(UPDATE, user);
		}
		else if (select == 3) //�͹ݲ�ѯ
		{
			m.queryRes(user.queryRes());
		}
		else if (select == 4) //�鿴ԤԼ
		{
			user.queryAllReserve();
		}
		else if (select == 5) //���Ԥ��
		{		
			order o =user.addReserve();
			m.updateOrder(ADD,o );
		}
		else if (select == 6) //�͹��Ƽ�
		{
			m.accommadation1();
		}
		else if(select == 7)//ע���˺�
		{
			
			m.updateUser(DELETION, user.deleteMyInfo());
			cout << "ע���ɹ�,�û�ϵͳ��ǿ���˳�" << endl;
			break;
		}
		else if(select == 0){
			cout << "�˳��˻�" << endl;
			break;
		}
		else {
			cout << "������������" << endl;
		}

		system("pause");
		system("cls");
	}
	system("pause");
	system("cls");
}


//�����̼��Ӳ˵�����
void ShopMenu(Shop &shop , Manager &m)
{
	while (true)
	{
		//�����Ӳ˵�����
		shop.openMenu();

		int select = 0; 
		cin >> select;

		if (select == 1) //��ѯ�͹���Ϣ
		{
			shop.showInfo();
		}
		else if (select == 2) //�޸Ĳ͹���Ϣ
		{
			m.updateShop(UPDATE, shop.updateInfo(shop));
		}
		else if (select == 3) //����Ԥ��
		{
			shop.dealReserve();
		}
		else if (select == 4) //��ѯ����Ԥ��
		{
			shop.queryAll();			
		}
		else if (select == 5) //��ѯ�û�Ԥ��
		{
			shop.queryUser();
		}
		else if(select == 6)
		{
			m.updateShop(DELETION, shop.delInfo());
			cout << "ע���ɹ�,�û�ϵͳ��ǿ���˳�" << endl;
			break;
		}
		else if (select == 0)
		{
			cout <<"�˳��˻�" << endl;
			break;
		}
		else {
			cout << "������������" << endl;
		}
		system("pause");
		system("cls");
	}
	system("pause");
	system("cls");
}


void Login(string fileName, int type, Manager& m) {

	string pwd;

	//�û�����
	if (type == 1) {
		string id;
		cout << "�������û�����" << endl;
		cin >> id;

		cout << "���������룺" << endl;
		cin >> pwd;

		for (User u:m.users)
		{
			if (id == u.U_Id && pwd == u.U_pwd) {
				cout << "�û���֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				
				for ( order o: m.orders)
				{
					if (o.U_Id == id) {
						u.user_order.push_back(o);
					}
				}				
				//����ѧ����ݵ��Ӳ˵�
				UserMenu(u,m);

				return ;
			}
			
		}		
	}//�̼�����
	/*
	else {
		string shop_name;
		cout << "�������̼�����" << endl;
		cin >> shop_name;
		cout << "���������룺" << endl;
		cin >> pwd;

		for (auto s:m.shops)
		{
			if (s.shopName == shop_name && s.shoppwd == pwd) {
				cout << "�̼���֤��¼�ɹ���" << endl;

				for (order o : m.orders)
				{
					if (o.R_Name == shop_name) {
						s.shop_order.push_back(o);
					}
				}
				system("pause");
				system("cls");

				ShopMenu(s, m);
				
				return;

			}
			else {
				break;
			}
		}
	}*/
	else {
		string shop_name;
		cout << "�������̼�����" << endl;
		cin >> shop_name;

		auto temp = m.ht.find(getGBK(shop_name));
		
		if (temp != NULL) {
			Shop s = temp->_kv.second;

			cout << "���������룺" << endl;
			cin >> pwd;

			if (pwd == s.shoppwd)
			{
				cout << "�̼���֤��¼�ɹ���" << endl;

				for (order o : m.orders)
				{
					if (o.R_Name == shop_name) {
						s.shop_order.push_back(o);
					}
				}
				system("pause");
				system("cls");
				ShopMenu(s, m);

				return;
			}
		}
		else {
			cout << "��������̼��������ڣ�" << endl;
		}			
	}	
	cout << "��֤��¼ʧ�ܣ�" << endl;
	system("pause");
	system("cls");

	return ;

}

int main() {
	
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	system("color 0B");
	int select = 0;
	Manager m;

	while (true)
	{
		cout << "======================  ��ӭʹ��zzuli���߲͹�Ԥ������ϵͳ  =====================" << endl;

		cout << endl << "��ѡ���������" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.��    ��           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.��    ��           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.��    ��           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "\t\t help:û���˺ţ������԰�0ע��һ���û��ʺ�\n\n";

		int select = 0;
		cin >> select;
		switch (select)
		{
		case 1://�û�
			Login(USER_FILE, 1,m);
			break;
		case 2:  //�̼�
			Login(SHOP_FILE, 2,m);
			break;
		case 3:  //�˳�ϵͳ
			cout << "��ӭ��һ��ʹ��" << endl;
			system("pause");
			return 0;
			break;
		case 0:
			m.RegistUser();
			break;
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}

