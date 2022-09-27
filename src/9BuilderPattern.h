//Builder（生成器模式-对象创建型）
//也叫建造者模式、构建器模式
//将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示。
#include<iostream>

//产品基类
class House
{
public:
	virtual ~House() {}
	virtual void show() = 0;
};

//生成器基类
class HouseBuilder
{
public:
	virtual ~HouseBuilder() {}
	virtual void reset() = 0;
	House* getResult() {
		return pHouse;
	}

	virtual void buildPart1() = 0;
	virtual void buildPart2() = 0;
	virtual void buildPart3() = 0;

protected:
	House* pHouse;
};

class StoneHouse : public House
{
public:
	void show() override {
		std::cout << "StoneHouse::show" << std::endl;
	}
};

class StoneHouseBuilder : public HouseBuilder
{
public:
	void reset() override {
		pHouse = new StoneHouse();
	}
	void buildPart1() override {
		std::cout << "build Part 1" << std::endl;
	}
	void buildPart2() override {
		std::cout << "build Part 2" << std::endl;
	}
	void buildPart3() override {
		std::cout << "build Part 3" << std::endl;
	}
};

//定义调用构造步骤的顺序
class HouseDirector
{
public:
	HouseDirector(HouseBuilder* pHouseBuilder)
		: pBudiler(pHouseBuilder) { }
	House* construct() {
		pBudiler->reset();
		pBudiler->buildPart1();
		pBudiler->buildPart2();
		pBudiler->buildPart3();
		return pBudiler->getResult();
	}
private:
	HouseBuilder* pBudiler;
};

//测试
void testBuilderPattern()
{
	std::cout << "construct StoneHouseBuilder" << std::endl;
	HouseBuilder* builder = new StoneHouseBuilder();
	std::cout << "construct HouseDirector" << std::endl;
	HouseDirector* director = new HouseDirector(builder);
	std::cout << "HouseDirector build House" << std::endl;
	auto* house = director->construct();
	house->show();
	delete house;
	delete director;
	delete builder;
}
