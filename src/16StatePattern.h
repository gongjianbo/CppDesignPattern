//State（状态模式-对象行为型）
//允许一个对象在其内部状态改变时改变他的行为。
//对象看起来似乎修改了他的类。
//别名状态对象（Objects for States）
#include <iostream>

//状态基类
class NetworkState
{
public:
	virtual ~NetworkState() {}
	//针对不同操作接口，每个状态都有各自的逻辑
	virtual void doA() = 0;
	virtual void doB() = 0;

	NetworkState* getNext() {
		return next;
	}
	void setNext(NetworkState* ptr) {
		next = ptr;
	}

private:
	NetworkState* next{ this };
};

//具体的状态
//如同策略模式一样，if-else拆成独立的类便于扩展
class OpenState : public NetworkState
{
public:
	static NetworkState* getInstance() {
		static OpenState instance;
		return &instance;
	}
	void doA() override;
	void doB() override;
};

class CloseState : public NetworkState
{
public:
	static NetworkState* getInstance() {
		static CloseState instance;
		return &instance;
	}
	void doA() override;
	void doB() override;
};

//互相依赖了，实现放后面
void OpenState::doA() {
	std::cout << "OpenState doA. next CloseState" << std::endl;
	setNext(CloseState::getInstance());
}
void OpenState::doB() {
	std::cout << "OpenState doB. next OpenState" << std::endl;
	setNext(OpenState::getInstance());
}
void CloseState::doA() {
	std::cout << "CloseState doA. next OpenState" << std::endl;
	setNext(OpenState::getInstance());
}
void CloseState::doB() {
	std::cout << "CloseState doB. next CloseState" << std::endl;
	setNext(CloseState::getInstance());
}

//context类
class NetworkManager
{
public:
	NetworkManager() : state{ CloseState::getInstance() } {}

	void doA() {
		std::cout << "Manager doA" << std::endl;
		state->doA();
		state = state->getNext();
	}
	void doB() {
		std::cout << "Manager doB" << std::endl;
		state->doB();
		state = state->getNext();
	}

private:
	NetworkState* state;
};

//测试
void testStatePattern()
{
	NetworkManager manager;
	manager.doA();
	manager.doB();
	manager.doA();
	manager.doB();
}
