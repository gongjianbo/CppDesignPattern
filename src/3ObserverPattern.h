//Observer（观察者模式-对象行为型）
//别名依赖（Dependents）、发布-订阅（Publish-Subscribe）
//定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，
//所有依赖于它的对象都得到通知并被自动更新。
//推模型，目标像观察者发送关于改变地详细信息，而不管他们需要与否。
//拉模型，目标除最小通知外什么也不送出，而在此之后由观察者显式地向目标查询细节。
#include <iostream>
#include <string>
#include <list>

//观察者
class AbstractObserver
{
public:
	virtual ~AbstractObserver() {}
	//接收通知，执行相应动作
	virtual void update(const std::string& message) = 0;
};

//目标
class AbstractSubject
{
public:
	virtual ~AbstractSubject() {}
	//注册
	void attach(AbstractObserver* observer) {
		observerList.push_back(observer);
	}
	//取消关联
	void detach(AbstractObserver* observer) {
		auto it = std::find(observerList.begin(), observerList.end(), observer);
		if (it != observerList.end()) {
			observerList.erase(it);
		}
	}
	//通知
	void notify(const std::string& message) {
		for (auto observer : observerList)
			observer->update(message);
	}

private:
	std::list<AbstractObserver*> observerList;
};

//具体的观察者派生类
class ConcreteObserver : public AbstractObserver
{
public:
	//重写update执行具体的动作
	void update(const std::string& message) override {
		std::cout << "observer update:" << message << std::endl;
	}
};

//具体的目标派生类
class ConcreteSubject : public AbstractSubject
{
public:
	//调用notify通知观察者
	void doSome() {
		std::cout << "subject notify: do some begin" << std::endl;
		notify("do some begin.");
		// ... ...
		std::cout << "subject notify: do some finished" << std::endl;
		notify("do some finished.");
	}
};

//测试
static void testObserverPattern()
{
	ConcreteSubject subject;
	ConcreteObserver ab1;
	ConcreteObserver ab2;
	subject.attach(&ab1);
	subject.attach(&ab2);
	subject.doSome();
}
