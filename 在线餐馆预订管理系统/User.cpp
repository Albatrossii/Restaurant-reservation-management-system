#include "user.h"
#include "hash.h"

//�޲ι���
User::User() {

}

//�вι���
User::User(string id, string pwd, LL tel) {
	this->U_Id = id;
	this->U_pwd = pwd;
	this->U_Tel = tel;
}

//�˵�
void User::openMenu() {
	cout << "��ӭ�û���" << this->U_Id << "��¼��" << endl;
	cout << "\t\t -------------------------------------\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           1.�鿴������Ϣ           |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           2.�޸ĸ�����Ϣ           |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           3.�͹ݲ�ѯ               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           4.�鿴ԤԼ               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           5.���Ԥ��               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           6.�͹��Ƽ�               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           7.ע���˺�               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           0.�˳���½               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t ------------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl; 
}

//չʾ������Ϣ
void User::showMyInfo() {
	cout << "�˻��� " << this->U_Id << endl;
	cout << "��  ��" << this->U_pwd << endl;
	cout << "��  �� " << this->U_Tel << endl;
}

//���¸�����Ϣ
User User::updateMyInfo(User user) {
	
	cout << "���������޸ĵ�����" << endl;
	cin >> user.U_pwd;

	cout << "���������޸ĵĵ绰����" << endl;
	cin >> user.U_Tel;

	return user;
}

//ɾ��������Ϣ
User User::deleteMyInfo() {
	return *this;
}

//�͹ݲ�ѯ
int User::queryRes() {
	cout << "��������Ҫ��ѯ�Ĳ͹����� �� " << endl;
	string s;
	cin >> s;

	return ((unsigned char)s[0] - 129) * 190 + ((unsigned char)s[3] - 129) +
			((unsigned char)s[2] - 64) - (unsigned char)s[1] / 128;

}

//��ѯ�û�������Ԥ��
void User::queryAllReserve() {
	
	int orders = this->user_order.size();
	if (orders == 0)
		cout << "��δ�µ�������" << endl;
	else
	{
		cout << "�͹�����\t\tԤ��ʱ��" << endl;

		for (size_t i = 0; i < orders; i++)
		{
			cout << this->user_order.at(i).R_Name << "\t" << this->user_order.at(i).reverse << endl;
		}
	}
}

//��ѯĳ�͹ݵ�Ԥ��
void User::queryResReserve() {
	cout << "��������Ҫ��ѯ�Ĳ͹�����" << endl;
	string name;
	cin >> name;
	int orders = this->user_order.size();
	int cnt = 0;
	if (orders == 0)
		cout << "��δ�µ�������" << endl;
	else
	{
		for (size_t i = 0; i < orders; i++)
		{
			if (cnt == 0 && name == this->user_order[i].R_Name) {
				cout << "Ԥ��ʱ��" << endl;
				cout << this->user_order[i].reverse<< endl;
				cnt++;
			}
			else if (name == this->user_order[i].R_Name) {

				cout << this->user_order[i].reverse << endl;
			}
			
		}
	}

}
//���Ԥ��
order User::addReserve() {
	string name;
	string time;
	cout << "��������ҪԤ�����̼�����  " << endl;
	cin >> name;
	cout << "������ҪԤ����ʱ��(ĳ��ĳ������/����)  " << endl;
	cin >> time;
	order o(this->U_Id, name, time);
	this->user_order.push_back(o);
	return o;

}


