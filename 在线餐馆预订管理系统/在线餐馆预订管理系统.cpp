#include "globalFile.h"
#include "manager.h"
#include<cstdlib>

using namespace std;

int getGBK(string s) {

	return ((unsigned char)s[0] - 129) * 190 + ((unsigned char)s[3] - 129) +
		((unsigned char)s[2] - 64) - (unsigned char)s[1] / 128;
}


//进入用户主界面
void UserMenu(User& user,Manager &m)
{
	while (true)
	{

		//调用用户子菜单
		user.openMenu();

		int select = 0;
		cin >> select; //接受用户选择

		if (select == 1) //查看个人信息
		{
			user.showMyInfo();
		}
		else if (select == 2) //修改个人信息
		{
			user = user.updateMyInfo(user);
			m.updateUser(UPDATE, user);
		}
		else if (select == 3) //餐馆查询
		{
			m.queryRes(user.queryRes());
		}
		else if (select == 4) //查看预约
		{
			user.queryAllReserve();
		}
		else if (select == 5) //添加预订
		{		
			order o =user.addReserve();
			m.updateOrder(ADD,o );
		}
		else if (select == 6) //餐馆推荐
		{
			m.accommadation1();
		}
		else if(select == 7)//注销账号
		{
			
			m.updateUser(DELETION, user.deleteMyInfo());
			cout << "注销成功,用户系统将强制退出" << endl;
			break;
		}
		else if(select == 0){
			cout << "退出账户" << endl;
			break;
		}
		else {
			cout << "您的输入有误" << endl;
		}

		system("pause");
		system("cls");
	}
	system("pause");
	system("cls");
}


//进入商家子菜单界面
void ShopMenu(Shop &shop , Manager &m)
{
	while (true)
	{
		//调用子菜单界面
		shop.openMenu();

		int select = 0; 
		cin >> select;

		if (select == 1) //查询餐馆信息
		{
			shop.showInfo();
		}
		else if (select == 2) //修改餐馆信息
		{
			m.updateShop(UPDATE, shop.updateInfo(shop));
		}
		else if (select == 3) //处理预订
		{
			shop.dealReserve();
		}
		else if (select == 4) //查询所有预订
		{
			shop.queryAll();			
		}
		else if (select == 5) //查询用户预订
		{
			shop.queryUser();
		}
		else if(select == 6)
		{
			m.updateShop(DELETION, shop.delInfo());
			cout << "注销成功,用户系统将强制退出" << endl;
			break;
		}
		else if (select == 0)
		{
			cout <<"退出账户" << endl;
			break;
		}
		else {
			cout << "您的输入有误" << endl;
		}
		system("pause");
		system("cls");
	}
	system("pause");
	system("cls");
}


void Login(string fileName, int type, Manager& m) {

	string pwd;

	//用户类型
	if (type == 1) {
		string id;
		cout << "请输入用户名：" << endl;
		cin >> id;

		cout << "请输入密码：" << endl;
		cin >> pwd;

		for (User u:m.users)
		{
			if (id == u.U_Id && pwd == u.U_pwd) {
				cout << "用户验证登录成功！" << endl;
				system("pause");
				system("cls");
				
				for ( order o: m.orders)
				{
					if (o.U_Id == id) {
						u.user_order.push_back(o);
					}
				}				
				//进入学生身份的子菜单
				UserMenu(u,m);

				return ;
			}
			
		}		
	}//商家类型
	/*
	else {
		string shop_name;
		cout << "请输入商家名：" << endl;
		cin >> shop_name;
		cout << "请输入密码：" << endl;
		cin >> pwd;

		for (auto s:m.shops)
		{
			if (s.shopName == shop_name && s.shoppwd == pwd) {
				cout << "商家验证登录成功！" << endl;

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
		cout << "请输入商家名：" << endl;
		cin >> shop_name;

		auto temp = m.ht.find(getGBK(shop_name));
		
		if (temp != NULL) {
			Shop s = temp->_kv.second;

			cout << "请输入密码：" << endl;
			cin >> pwd;

			if (pwd == s.shoppwd)
			{
				cout << "商家验证登录成功！" << endl;

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
			cout << "您输入的商家名不存在！" << endl;
		}			
	}	
	cout << "验证登录失败！" << endl;
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
		cout << "======================  欢迎使用zzuli在线餐馆预订管理系统  =====================" << endl;

		cout << endl << "请选择您的身份" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.用    户           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.商    家           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.退    出           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "\t\t help:没有账号？您可以按0注册一个用户帐号\n\n";

		int select = 0;
		cin >> select;
		switch (select)
		{
		case 1://用户
			Login(USER_FILE, 1,m);
			break;
		case 2:  //商家
			Login(SHOP_FILE, 2,m);
			break;
		case 3:  //退出系统
			cout << "欢迎下一次使用" << endl;
			system("pause");
			return 0;
			break;
		case 0:
			m.RegistUser();
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}

