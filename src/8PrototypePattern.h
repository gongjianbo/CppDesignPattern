//Prototype（原型模式-对象创建型）
//也叫Clone克隆模式
//用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。
#include <iostream>
#include <memory>

//每个具体的原型对象可能会有一系列复杂的创建过程
class Prototype
{
public:
	virtual ~Prototype() {}
	virtual std::shared_ptr<Prototype> clone() = 0;
};

//具体的原型重写clone接口
class ConcretePrototypeA : public Prototype
{
public:
	std::shared_ptr<Prototype> clone() override {
		Prototype* instance = new ConcretePrototypeA;
		//这里可能会有复杂的创建逻辑
		return std::shared_ptr<Prototype>{ instance };
	}
};

//class ConcretePrototypeB : public Prototype{};

//测试
void testPrototypePattern() {
	std::cout << "new prototype" << std::endl;
	std::shared_ptr<Prototype> prototype{ new ConcretePrototypeA };
	std::cout << "prototype clone instance 1" << std::endl;
	auto instance1 = prototype->clone();
	std::cout << "prototype clone instance 2" << std::endl;
	auto instance2 = prototype->clone();
}
