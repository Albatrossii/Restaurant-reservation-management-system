#include "order.h"

//无参构造
order::order() {

}

//有参构造
order::order(string id, string name, string rev) {
	this->U_Id = id;
	this->R_Name = name;
	this->reverse = rev;
}