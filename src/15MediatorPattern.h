//Mediator（中介者模式-对象行为型）
//用一个中介对象来封装一系列的对象交互。
//中介者使各对象不需要显式地相互引用，从而使其耦合松散，
//而且可以独立地改变它们之间的交互。
#include <iostream>

//不知道为什么书上用Colleague（同事）一词来表示协作类
class Colleague;

//中介者接口
class Mediator
{
public:
	virtual ~Mediator() {}
	virtual void notify(Colleague* sender, int type) = 0;
};

//"同事"类接口
class Colleague
{
public:
	virtual ~Colleague() {}
	void setMediator(Mediator* ptr) {
		mediator = ptr;
	}
	void notify(int type) {
		std::cout << "Colleague notify:" << type << std::endl;
		if (!mediator) {
			return;
		}
		mediator->notify(this, type);
	}
private:
	Mediator* mediator{ nullptr };
};

//具体的同事类1
class ConcreteColleague1 : public Colleague
{
public:
	void update() {
		std::cout << "ConcreteColleague1 update" << std::endl;
	}
};

//具体的同事类2
class ConcreteColleague2 : public Colleague
{
public:
	void update() {
		std::cout << "ConcreteColleague2 update" << std::endl;
	}
};

//具体的中介者类
class ConcreteMediator : public Mediator
{
public:
	ConcreteMediator(ConcreteColleague1* c1, ConcreteColleague2* c2)
		: colleague1(c1), colleague2(c2) {
		c1->setMediator(this);
		c2->setMediator(this);
	}
	~ConcreteMediator() {}
	//具体的交互逻辑
	void notify(Colleague* sender, int type) override {
		std::cout << "ConcreteMediator notify:" << type << std::endl;
		if (type == 1 && sender == colleague1) {
			colleague2->update();
		}
		else {
			colleague1->update();
			colleague2->update();
		}
	}
private:
	ConcreteColleague1* colleague1;
	ConcreteColleague2* colleague2;
};

//测试
void testMediatorPattern()
{
	ConcreteColleague1 c1;
	ConcreteColleague2 c2;
	ConcreteMediator mediator(&c1, &c2);
	//通过中介者去处理关联逻辑
	std::cout << "c1 notify" << std::endl;
	c1.notify(1);
	std::cout << "c2 notify" << std::endl;
	c2.notify(1);
}
