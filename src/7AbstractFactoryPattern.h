//Abstract Factory（抽象工厂-对象创建型）
//别名Kit
//提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。
#include <iostream>

//Product1-按钮
class AbstractButton
{
public:
	virtual ~AbstractButton() {}
};
//具体Product
class DarkButton : public AbstractButton {};
class LightButton : public AbstractButton {};

//Product2-输入框
class AbstractInput
{
public:
	virtual ~AbstractInput() {}
};
//具体Product
class DarkInput : public AbstractInput {};
class LightInput : public AbstractInput {};

//工厂
class AbstractFactory
{
public:
	virtual ~AbstractFactory() {}
	virtual AbstractButton* createButton() = 0;
	virtual AbstractInput* createInput() = 0;
};
//创建Dark系列Product的工厂
class DarkFactory : public AbstractFactory
{
public:
	AbstractButton* createButton() override {
		return new DarkButton;
	}
	AbstractInput* createInput()override {
		return new DarkInput;
	}
};
//创建Light系列Product的工厂
//class LightFactory : public AbstractFactory {};

//测试
void testAbstractFactoryPattern()
{
	std::cout << "construct DarkFactory" << std::endl;
	DarkFactory factory;
	std::cout << "DarkFactory create DarkButton" << std::endl;
	AbstractButton* btn = factory.createButton();
	std::cout << "DarkFactory create DarkInput" << std::endl;
	AbstractInput* input = factory.createInput();
	delete btn;
	delete input;
}
