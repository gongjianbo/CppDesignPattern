//Chain of Responsibility（职责链模式-对象行为型）
//使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。
//将这些对象连成一条链，并沿着这条链传递该请求，直到有一个对象处理它为止。
#include <iostream>
#include <string>

//请求类型
enum class RequestType
{
	Req1,
	Req2
};

//请求
struct Request
{
	RequestType type;
	std::string info;
};

//节点
class ChainHandler
{
public:
	void setNextHandler(ChainHandler* handle) {
		nextHandler = handle;
	}
	virtual ~ChainHandler() {};
	void process(const Request& req) {
		if (canProcess(req)) {
			doProcess(req);
		}
		else if (nextHandler) {
			nextHandler->process(req);
		}
	}

protected:
	virtual bool canProcess(const Request& req) const { return false; }
	virtual void doProcess(const Request& req) {};

private:
	ChainHandler* nextHandler{ nullptr };
};

class ConcreteHandler1 : public ChainHandler
{
protected:
	bool canProcess(const Request& req) const {
		return req.type == RequestType::Req1;
	}
	void doProcess(const Request& req) {
		std::cout << "Handler-1 process: " << req.info << std::endl;
	};
};

class ConcreteHandler2 : public ChainHandler
{
protected:
	bool canProcess(const Request& req) const {
		return req.type == RequestType::Req2;
	}
	void doProcess(const Request& req) {
		std::cout << "Handler-2 process: " << req.info << std::endl;
	};
};


//测试
void testChainOfResponsibilityPattern()
{
	ConcreteHandler1 h1;
	ConcreteHandler2 h2;
	h1.setNextHandler(&h2);
	Request req1{ RequestType::Req1, "hello" };
	h1.process(req1);
	Request req2{ RequestType::Req2, "world" };
	h1.process(req2);
}
