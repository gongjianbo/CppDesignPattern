//Memento（备忘录模式-对象行为型）
//别名 Token
//在不破坏封装性的前提下，捕获一个对象的内部状态，
//并在该对象之外保存这个状态，这样以后就可以将该对象恢复到原先保存的状态。
//对外隐藏信息，保持封装性，同时又需要将状态保持到外界，相关内容-对象序列化。
#include <iostream>
#include <memory>
#include <stack>

//备忘录
class Memento
{
public:
	virtual ~Memento() {}
	virtual int state() const = 0;
};

class ConcreteMemento : public Memento
{
public:
	explicit ConcreteMemento(int state) : mState(state) {}
	int state() const { return mState; }

private:
	int mState = 0;
};

//原发器
class Originator
{
public:
	//获取状态
	std::shared_ptr<Memento> save() {
		std::cout << "save memento " << mState << std::endl;
		return std::make_shared<ConcreteMemento>(mState);
	}

	//恢复状态
	void restore(std::shared_ptr<Memento> memento) {
		mState = memento->state();
		std::cout << "restore memento " << mState << std::endl;
	}

	//操作之后内部状态改变
	void doSome(int num) {
		mState = num;
		std::cout << "do some, current state " << mState << std::endl;
	}

private:
	int mState = 0;
};


//测试
void testMementoPattern()
{
	//外部保存状态，可以是封装在某个对象内部，在执行恢复时pop上一次存的状态
	std::stack<std::shared_ptr<Memento>> mementos;

	Originator origin;
	origin.doSome(10);
	mementos.push(origin.save());
	origin.doSome(20);
	origin.restore(mementos.top());
	mementos.pop();
}
