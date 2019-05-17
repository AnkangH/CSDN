#include<iostream>
#include"001.h"
int stock::num_size = 0;//静态变量初始化
void stock::show(void)
{
	std::cout << company << " " << price << std::endl;
	std::cout << "Now has " << num_size << " stocks." << std::endl;
}
void stock::update(std::string s, double p)//形参要与类的私有成员异名
{
	company = s;
	price = p;
}
stock::stock(std::string s, double p)
{
	company = s;
	price = p;
	num_size++;
	std::cout << "Class stock construct." << std::endl;
}
stock::stock()
{
	company = "Non";
	price = 0;
	num_size++;
}
stock::~stock()
{
	std::cout << "Class stock dis-construct." << std::endl;
	num_size--;
}
const stock& stock::topval(const stock& s) const
{
	if (s.price >= this->price)//s为参数对象
		return s;
	else
		return *this;//this为调用函数的对象
}
stock stock::operator+(stock s)
{
	stock temp;
	temp.company = s.company + " " + this->company;//string拼接
	temp.price = s.price + this->price;//价格相加
	return temp;
}
stock stock::operator*(double p)
{
	stock temp=*this;
	temp.price = this->price*p;
	return temp;
}
stock operator*(double p, const stock& s)
{
	stock temp = s;
	temp.price = p*temp.price;
	return temp;
}
stock operator+(double p, const stock& s)
{
	stock temp = s;
	temp.price += p;
	return temp;
}
stock operator+(const stock& s, double p)
{
	stock temp = s;
	temp.price += p;
	return temp;
}
person::person(std::string s1, std::string s2, double p)
	:stock(s2, p)//必须先创建基类对象 再创建派生类对象
				//如果不显示创建基类对象 将使用默认基类构造函数
{
	name = s1;
	std::cout << "Class person construct." << std::endl;
}
person::person(std::string s1, const stock& s)
	:stock(s),name(s1)//这里未定义参数为stock的构造函数
					//但是c++会自动生成复制构造函数 所以也可行
{
	std::cout << "Class person construct." << std::endl;
}
person::~person()
{
	std::cout << "Class person dis-construct." << std::endl;
}
