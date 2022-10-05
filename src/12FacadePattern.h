//Facade（外观模式-对象结构型）
//为子系统中的一组接口提供一个一致的界面，Facade模式定义了一个高层接口
//这个接口使得这一子系统更加容易使用。
#include <iostream>

//各子系统
class SubSystem1
{
public:
	void working() {
		std::cout << "SubSystem1 working" << std::endl;
	}
};
class SubSystem2
{
public:
	void working() {
		std::cout << "SubSystem2 working" << std::endl;
	}
};

//对外接口
//Facade将客户请求代理给适当的子系统对象
class Facade
{
public:
	void working() {
		std::cout << "Facade working" << std::endl;
		//各子系统之间可能是互相依赖的
		s1.working();
		s2.working();
	}

private:
	SubSystem1 s1;
	SubSystem2 s2;
};

//测试
void testFacadePattern()
{
	Facade facade;
	facade.working();
}
