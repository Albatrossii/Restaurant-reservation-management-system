#include "shop.h"


//无参构造
Shop::Shop() {
	//this->shop_foods->size = 0;
	//vector<food>(this->shop_foods).swap(this->shop_foods);
}

//菜单
void Shop::openMenu(){
	cout << "欢迎商家：" << this->shopName << "登录！" << endl;
	cout << "\t\t -------------------------------------\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           1.查询餐馆信息           |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           2.修改餐馆信息           |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           3.处理预订               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           4.查询所有预订           |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           5.查询用户预订           |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           6.注销账号               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t|           0.退出登陆               |\n";
	cout << "\t\t|                                    |\n";
	cout << "\t\t ------------------------------------\n";
	cout << "请选择您的操作： " << endl; 
}

//查询餐馆信息
void Shop::showInfo() {
	cout << "商家类型 " << this->shoptype<< endl;
	cout << "餐馆ID" << this->S_Id << endl;
	cout << "餐馆名 " << this->shopName << endl;
	cout << "登录密码 " << this->shoppwd << endl;
	cout << "餐馆平均分" << this->avgScore << endl;
	cout << "餐馆平均消费 " << this->avePrice << endl;
	cout << "参观地址 " << this->address<< endl;
	cout << "餐馆电话" << this->Tel<< endl;

	//展示食物
	cout << "店内菜单 " <<  endl;

	for (auto f:this->shop_foods)
	{
		cout << "菜品编号："<< f.food_id << "\t菜品名：" << f.food_name<<  "\t菜品价格："<< f.food_price<< endl;
	}

	//展示评价
	cout << "顾客评价 " << endl;
	for (size_t i = 0; i < this->shop_comments.size(); i++)
	{
		cout << "顾客" << i << "说： " << this->shop_comments[i] << endl;
			 
	}
}

//删除信息
Shop Shop::delInfo() {
	return *this;
}

//修改餐馆信息
Shop Shop::updateInfo(Shop &shop) {
	char choice;
	cout << "您是否要修改餐馆类型 y/n	" << endl;
	cin >> choice;
	if (choice == 'y'|| choice == 'Y')
	{
		cout << "请输入您修改后的餐馆类型  ";
		cin >> shop.shoptype;
	}
	cout << "您是否要修改个人密码 y/n	" << endl;
	cin >> choice;
	if (choice == 'y' || choice == 'Y')
	{
		cout << "请输入您修改后的个人密码  ";
		cin >> shop.shoppwd;
	}
	cout << "您是否要修改餐馆地址 y/n	" << endl;
	cin >> choice;
	if (choice == 'y' || choice == 'Y')
	{
		cout << "请输入您修改后的餐馆地址  ";
		cin >> shop.address;
	}

	return *this;
}

//查询餐馆所有预订
void Shop::queryAll() {
	cout << "用户帐号\t\t预定时间" << endl;
	int orders = this->shop_order.size();
	if (orders == 0)
		cout << "暂无最新订单呦亲亲" << endl;
	else
	{
		for (size_t i = 0; i <orders; i++)
		{
			cout << this->shop_order.at(i).U_Id<<"\t\t" << this->shop_order.at(i).reverse << endl;
		}
	}
}

//查询某用户预订
void Shop::queryUser() {
	cout << "请输入您要查询的用户帐号 ：";
	string U_id;
	cin >> U_id;


	int orders = this->shop_order.size();
	if (orders == 0)
		cout << "该用户最近没有下单呦亲亲" << endl;
	else
	{
		cout << "用户帐号\t\t预定时间" << endl;
		for (size_t i = 0; i < orders; i++)
		{
			if(this->shop_order[i].U_Id == U_id)
			cout << this->shop_order.at(i).U_Id << "\t预定时间" << this->shop_order.at(i).U_Id << endl;
		}
	}
}

//处理预订
void Shop::dealReserve() {

	int orders = this->shop_order.size();
	if (orders == 0)
		cout << "您的订单已经处理完啦!" << endl;
	else
	{
		cout << "需要处理的订单" << endl;

		cout << "顾客账号\t\t预定时间" << endl;

		for (size_t i = 0; i < orders; i++)
		{
			cout << this->shop_order[i].U_Id << "\t\t" << this->shop_order[i].reverse << endl;
		}
	}

	cout << "请输入您要处理的条数（按照时间顺序）:" << endl;
	int t;
	cin >> t;
	if (t==0)
	{
		cout << "无操作" << endl;
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
		cout << "您输入的数据大于实际有的顺序，将默认为您处理全部订单" << endl;
		shop_order.clear();
	}
}

//获得哈希码
int Shop::getGBKindex() {

	return ((unsigned char)shopName[0] - 129) * 190 + ((unsigned char)shopName[3] - 129) +
		((unsigned char)shopName[2] - 64) - (unsigned char)shopName[1] / 128;

}

//清理内存
void Shop:: clear() {
	//vector<food>(this->shop_foods).swap(this->shop_foods);
	this->shop_comments.clear();
}

