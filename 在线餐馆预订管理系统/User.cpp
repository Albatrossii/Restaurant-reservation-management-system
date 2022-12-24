#include "user.h"
#include "hash.h"

//无参构造
User::User() {

}

//有参构造
User::User(string id, string pwd, LL tel) {
	this->U_Id = id;
	this->U_pwd = pwd;
	this->U_Tel = tel;
}

//菜单
void User::openMenu() {
	cout << "欢迎用户：" << this->U_Id << "登录！" << endl;
	cout << "\t\t -------------------------------------\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           1.查看个人信息           |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           2.修改个人信息           |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           3.餐馆查询               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           4.查看预约               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           5.添加预订               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           6.餐馆推荐               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           7.注销账号               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           0.退出登陆               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t ------------------------------------\n";
	cout << "请选择您的操作： " << endl; 
}

//展示个人信息
void User::showMyInfo() {
	cout << "账户名 " << this->U_Id << endl;
	cout << "密  码" << this->U_pwd << endl;
	cout << "电  话 " << this->U_Tel << endl;
}

//更新个人信息
User User::updateMyInfo(User user) {
	
	cout << "请输入您修改的密码" << endl;
	cin >> user.U_pwd;

	cout << "请输入您修改的电话号码" << endl;
	cin >> user.U_Tel;

	return user;
}

//删除个人信息
User User::deleteMyInfo() {
	return *this;
}

//餐馆查询
int User::queryRes() {
	cout << "请输入您要查询的餐馆名称 ： " << endl;
	string s;
	cin >> s;

	return ((unsigned char)s[0] - 129) * 190 + ((unsigned char)s[3] - 129) +
			((unsigned char)s[2] - 64) - (unsigned char)s[1] / 128;

}

//查询用户的所有预定
void User::queryAllReserve() {
	
	int orders = this->user_order.size();
	if (orders == 0)
		cout << "您未下单呦亲亲" << endl;
	else
	{
		cout << "餐馆名称\t\t预定时间" << endl;

		for (size_t i = 0; i < orders; i++)
		{
			cout << this->user_order.at(i).R_Name << "\t" << this->user_order.at(i).reverse << endl;
		}
	}
}

//查询某餐馆的预订
void User::queryResReserve() {
	cout << "请输入您要查询的餐馆名称" << endl;
	string name;
	cin >> name;
	int orders = this->user_order.size();
	int cnt = 0;
	if (orders == 0)
		cout << "您未下单呦亲亲" << endl;
	else
	{
		for (size_t i = 0; i < orders; i++)
		{
			if (cnt == 0 && name == this->user_order[i].R_Name) {
				cout << "预定时间" << endl;
				cout << this->user_order[i].reverse<< endl;
				cnt++;
			}
			else if (name == this->user_order[i].R_Name) {

				cout << this->user_order[i].reverse << endl;
			}
			
		}
	}

}
//添加预订
order User::addReserve() {
	string name;
	string time;
	cout << "请输入您要预订的商家名称  " << endl;
	cin >> name;
	cout << "请输入要预订的时间(某月某日上午/下午)  " << endl;
	cin >> time;
	order o(this->U_Id, name, time);
	this->user_order.push_back(o);
	return o;

}


