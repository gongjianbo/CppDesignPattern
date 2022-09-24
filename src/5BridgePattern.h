//Bridge（桥接模式-对象结构型）
//别名Handle/Body
//将抽象部分与它的实现部分分离，使它们都可以独立的变化。
//PIMPL，即“pointer to implementation”（指向实现的指针），桥模式的特例。
#include <iostream>

//操作基类
//Implementation不必和Abstraction保持接口一致
class Implementation
{
public:
	virtual ~Implementation() {}
	virtual void doing() const = 0;
};

//每个具体的Implementation对应特定平台platform
class ConcreteImplementationA : public Implementation
{
public:
	void doing() const override {}
};

class ConcreteImplementationB : public Implementation
{
public:
	void doing() const override {}
};

//接口基类
class Abstraction
{
public:
	Abstraction(Implementation* implementation) : impl(implementation) {
	}
	virtual ~Abstraction() {}

	virtual void doSome() const {
		impl->doing();
	}

protected:
	Implementation* impl;
};

class ExtendedAbstraction : public Abstraction
{
public:
	ExtendedAbstraction(Implementation* implementation) : Abstraction(implementation) {
	}

	void doSome() const override {
		std::cout << "ExtendedAbstraction doSome" << std::endl;
		impl->doing();
	}
};

//测试
void testBridgePattern()
{
	//这个demo只是演示抽象逻辑
	//比较经典的例子还是组件和平台实现的IMPL demo
	//如Window（用于外部访问的接口）+WindowImpl（底层各平台的具体实现）
	//具体Window类（如ProWindow、LiteWindow）调用具体impl实现的接口（如PCWindowImpl、MobileWindowImpl）
	std::cout << "construct ImplA" << std::endl;
	Implementation* implementation = new ConcreteImplementationA;
	std::cout << "set ImplA to Abstraction" << std::endl;
	Abstraction* abstraction = new ExtendedAbstraction(implementation);
	std::cout << "Abstraction doing,internal call ImplA doing" << std::endl;
	abstraction->doSome();
	delete implementation;
	delete abstraction;

	std::cout << "construct ImplB" << std::endl;
	implementation = new ConcreteImplementationB;
	std::cout << "set ImplB to Abstraction" << std::endl;
	abstraction = new ExtendedAbstraction(implementation);
	std::cout << "Abstraction doing,internal call ImplB doing" << std::endl;
	abstraction->doSome();
	delete implementation;
	delete abstraction;
}
