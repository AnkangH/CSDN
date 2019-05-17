#ifndef ___001H___
#define ___001H___
#include<string>
class stock 
{
	std::string company;//公司名称
	double price;//股票价格
	static int num_size;//当前股票数目
public:
	stock();//构造函数
	stock(std::string, double);//构造函数
	~stock();//析构函数
	void show(void);//显示公司股票
	void update(std::string, double);//更新股票价格
	const stock& topval(const stock&)const;//比较股票价格
//  const1				const2		 const3
	//const1 因为返回了const常量的引用 所以返回值必须为const
	//const2 不可修改参数的值，否则报错
	//const3 不可修改调用topval的对象的值，否则报错
	stock operator+(stock s);//重载'+',  this+s
	stock operator*(double p);//重载'*'  this*p
	friend stock operator*(double, const stock& s);//重载'*'    double*s
	friend stock operator+(double, const stock& s);//重载'+'	double+s
	friend stock operator+(const stock& s, double);//重载'+'	s+double
};
class person : public stock
//公有继承 派生类可以访问基类的公有成员
//但是只能通过基类的公有成员访问基类的私有成员
{
	std::string name;//人名
public:
	person(std::string,std::string,double);
	person(std::string, const stock&);
	~person();
};
#endif
