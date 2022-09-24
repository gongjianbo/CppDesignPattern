//Factory Method（工厂方法-对象创建型）
//别名Virtual Constructor（虚构造器）
//定义一个用于创建目标对象的接口，让子类决定实例化哪一个目标类。
//Factory Method 使一个类的实例化延迟到其子类。
#include <iostream>

class IProduct
{
public:
	virtual ~IProduct() {}
};
class AProduct : public IProduct {};
class BProduct : public IProduct {};

//方式1：Creator/Factory缺省实现+参数化工厂方法
//（简单工厂）
class SimpleFactory
{
public:
	virtual IProduct* create(int type) {
		switch (type)
		{
		case 0: return new AProduct();
		case 1: return new BProduct();
		default: break;
		}
		return nullptr;
	}
};

//方式2：子类化
class IFactory
{
public:
	virtual ~IFactory() {}
	virtual IProduct* create() = 0;
};
class AFactory : public IFactory
{
public:
	IProduct* create() override {
		return new AProduct();
	}
};
class BFactory : public IFactory
{
public:
	IProduct* create() override {
		return new BProduct();
	}
};

//测试
void testFactoryMethodPattern()
{
	//简单工厂，根据参数来创建对应对象
	std::cout << "eg.1" << std::endl;
	std::cout << "construct SimpleFactory" << std::endl;
	SimpleFactory* f = new SimpleFactory();
	std::cout << "SimpleFactory create AProduct through flag" << std::endl;
	IProduct* p1 = f->create(0);
	std::cout << "AProduct Construction completed" << std::endl;
	delete f;
	delete p1;

	//factory可作为参数传递给类实例，用户再调用factory的create函数
	//如我们提供一个带factory参数的接口，后面使用的时候再根据需求创建具体的factory
	std::cout << "eg.2" << std::endl;
	std::cout << "construct AFactory" << std::endl;
	IFactory* factory = new AFactory();
	std::cout << "AFactory create AProduct" << std::endl;
	IProduct* p2 = factory->create();
	std::cout << "AProduct Construction completed" << std::endl;
	delete factory;
	delete p2;
	//
	std::cout << "construct BFactory" << std::endl;
	factory = new BFactory();
	std::cout << "BFactory create BProduct" << std::endl;
	p2 = factory->create();
	std::cout << "BProduct Construction completed" << std::endl;
	delete factory;
	delete p2;
}
