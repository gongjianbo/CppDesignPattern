//Flyweight（享元模式-对象结构型）
//运用共享技术有效地支持大量细粒度的对象
#include <iostream>
#include <string>
#include <map>

//抽象的享元类
class Flyweight
{
public:
	virtual ~Flyweight() {}
	virtual void operate(int type) = 0;
};

//共享的子类
class ConcreteFlyweight : public Flyweight
{
public:
	void operate(int type) override {
		std::cout << "ConcreteFlyweight operate: " << type << std::endl;
	}
};

//非共享的子类
class UnshareConcreteFlyweight : public Flyweight
{
public:
	void operate(int type) override {
		std::cout << "UnshareConcreteFlyweight operate: " << type << std::endl;
	}
};

//享元工厂
//创建并管理flyweight对象
class FlyweightFactory
{
public:
	Flyweight* getFlyweight(std::string key) {
		//检测是否已存在
		if (flyweights.find(key) != flyweights.end())
		{
			std::cout << "getFlyweight: " << key << " already exists" << std::endl;
			return flyweights[key];
		}
		std::cout << "getFlyweight: " << key << " new instance" << std::endl;
		//不存在创建一个并放到池子里
		auto instance = new ConcreteFlyweight();
		flyweights[key] = instance;
		return instance;
	}
	//释放
	void free() {
		std::cout << "FlyweightFactory free" << std::endl;
		for (auto iter = flyweights.begin(); iter != flyweights.end();)
		{
			std::cout << "delte " << iter->first << std::endl;
			delete iter->second;
			iter->second = nullptr;
			iter = flyweights.erase(iter);
		}
	}

private:
	//享元对象池
	std::map<std::string, Flyweight*> flyweights;
};

//测试
void testFlayweightPattern()
{
	std::cout << "create FlyweightFactory" << std::endl;
	FlyweightFactory factory;
	auto f1 = factory.getFlyweight("gong");
	auto f2 = factory.getFlyweight("gong");
	auto f3 = factory.getFlyweight("1992");
	factory.free();
}
