#include "shop.h"


//�޲ι���
Shop::Shop() {
	//this->shop_foods->size = 0;
	//vector<food>(this->shop_foods).swap(this->shop_foods);
}

//�˵�
void Shop::openMenu(){
	cout << "��ӭ�̼ң�" << this->shopName << "��¼��" << endl;
	cout << "\t\t -------------------------------------\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           1.��ѯ�͹���Ϣ           |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           2.�޸Ĳ͹���Ϣ           |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           3.����Ԥ��               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           4.��ѯ����Ԥ��           |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           5.��ѯ�û�Ԥ��           |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           6.ע���˺�               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           0.�˳���½               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t ------------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl; 
}

//��ѯ�͹���Ϣ
void Shop::showInfo() {
	cout << "�̼����� " << this->shoptype<< endl;
	cout << "�͹�ID" << this->S_Id << endl;
	cout << "�͹��� " << this->shopName << endl;
	cout << "��¼���� " << this->shoppwd << endl;
	cout << "�͹�ƽ����" << this->avgScore << endl;
	cout << "�͹�ƽ������ " << this->avePrice << endl;
	cout << "�ι۵�ַ " << this->address<< endl;
	cout << "�͹ݵ绰" << this->Tel<< endl;

	//չʾʳ��
	cout << "���ڲ˵� " <<  endl;

	for (auto f:this->shop_foods)
	{
		cout << "��Ʒ��ţ�"<< f.food_id << "\t��Ʒ����" << f.food_name<<  "\t��Ʒ�۸�"<< f.food_price<< endl;
	}

	//չʾ����
	cout << "�˿����� " << endl;
	for (size_t i = 0; i < this->shop_comments.size(); i++)
	{
		cout << "�˿�" << i << "˵�� " << this->shop_comments[i] << endl;
			 
	}
}

//ɾ����Ϣ
Shop Shop::delInfo() {
	return *this;
}

//�޸Ĳ͹���Ϣ
Shop Shop::updateInfo(Shop &shop) {
	char choice;
	cout << "���Ƿ�Ҫ�޸Ĳ͹����� y/n	" << endl;
	cin >> choice;
	if (choice == 'y'|| choice == 'Y')
	{
		cout << "���������޸ĺ�Ĳ͹�����  ";
		cin >> shop.shoptype;
	}
	cout << "���Ƿ�Ҫ�޸ĸ������� y/n	" << endl;
	cin >> choice;
	if (choice == 'y' || choice == 'Y')
	{
		cout << "���������޸ĺ�ĸ�������  ";
		cin >> shop.shoppwd;
	}
	cout << "���Ƿ�Ҫ�޸Ĳ͹ݵ�ַ y/n	" << endl;
	cin >> choice;
	if (choice == 'y' || choice == 'Y')
	{
		cout << "���������޸ĺ�Ĳ͹ݵ�ַ  ";
		cin >> shop.address;
	}

	return *this;
}

//��ѯ�͹�����Ԥ��
void Shop::queryAll() {
	cout << "�û��ʺ�\t\tԤ��ʱ��" << endl;
	int orders = this->shop_order.size();
	if (orders == 0)
		cout << "�������¶���������" << endl;
	else
	{
		for (size_t i = 0; i <orders; i++)
		{
			cout << this->shop_order.at(i).U_Id<<"\t\t" << this->shop_order.at(i).reverse << endl;
		}
	}
}

//��ѯĳ�û�Ԥ��
void Shop::queryUser() {
	cout << "��������Ҫ��ѯ���û��ʺ� ��";
	string U_id;
	cin >> U_id;


	int orders = this->shop_order.size();
	if (orders == 0)
		cout << "���û����û���µ�������" << endl;
	else
	{
		cout << "�û��ʺ�\t\tԤ��ʱ��" << endl;
		for (size_t i = 0; i < orders; i++)
		{
			if(this->shop_order[i].U_Id == U_id)
			cout << this->shop_order.at(i).U_Id << "\tԤ��ʱ��" << this->shop_order.at(i).U_Id << endl;
		}
	}
}

//����Ԥ��
void Shop::dealReserve() {

	int orders = this->shop_order.size();
	if (orders == 0)
		cout << "���Ķ����Ѿ���������!" << endl;
	else
	{
		cout << "��Ҫ����Ķ���" << endl;

		cout << "�˿��˺�\t\tԤ��ʱ��" << endl;

		for (size_t i = 0; i < orders; i++)
		{
			cout << this->shop_order[i].U_Id << "\t\t" << this->shop_order[i].reverse << endl;
		}
	}

	cout << "��������Ҫ���������������ʱ��˳��:" << endl;
	int t;
	cin >> t;
	if (t==0)
	{
		cout << "�޲���" << endl;
	}
	else if(t <= this->shop_order.size()){
		int j = 0;
		for (auto i = shop_order.begin(); i != shop_order.end(); i++)
		{
			if (j== t)
				break;
			j++;
			shop_order.pop_back();
		}
	}
	else {
		cout << "����������ݴ���ʵ���е�˳�򣬽�Ĭ��Ϊ������ȫ������" << endl;
		shop_order.clear();
	}
}

//��ù�ϣ��
int Shop::getGBKindex() {

	return ((unsigned char)shopName[0] - 129) * 190 + ((unsigned char)shopName[3] - 129) +
		((unsigned char)shopName[2] - 64) - (unsigned char)shopName[1] / 128;

}

//�����ڴ�
void Shop:: clear() {
	//vector<food>(this->shop_foods).swap(this->shop_foods);
	this->shop_comments.clear();
}

