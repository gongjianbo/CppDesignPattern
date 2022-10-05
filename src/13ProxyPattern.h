//Proxy（代理模式-对象结构型）
//别名Surrogate
//为其他对象提供一种代理以控制对这个对象的访问。
//适配器模式能为被封装对象提供不同的接口， 代理模式能为对象提供相同的接口， 
//装饰模式则能为对象提供加强的接口。
#include <iostream>

//抽象接口
class ISubject
{
public:
	virtual ~ISubject() {}
	virtual void request() const = 0;
};

//实体类，完成具体的操作
class RealSubject : public ISubject
{
public:
	void request() const override {
		std::cout << "RealSubject request" << std::endl;
	}
};

//代理持有实体的引用
class Proxy : public ISubject
{
public:
	Proxy() {}
	~Proxy() { 
		if (subject) delete subject; 
	}

	//通过代理简介访问
	void request() const override {
		std::cout << "Proxy request. call RealSubject request" << std::endl;
		getSubject()->request();
	}

protected:
	//延迟加载
	RealSubject* getSubject() const {
		if (!subject) {
			subject = new RealSubject;
		}
		return subject;
	}

private:
	mutable RealSubject* subject{ nullptr };
};

//测试
void testProxyPattern()
{
	Proxy proxy;
	proxy.request();
}
