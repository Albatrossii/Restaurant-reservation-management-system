#include "order.h"

//�޲ι���
order::order() {

}

//�вι���
order::order(string id, string name, string rev) {
	this->U_Id = id;
	this->R_Name = name;
	this->reverse = rev;
}