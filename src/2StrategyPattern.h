//Strategy（策略模式-对象行为型）
//别名Policy
//定义一系列的算法，把它们一个个封装起来，并且使它们可以相互替换。
//使得算法可独立于使用它的客户而变化。
#include <iostream>
#include <string>
#include <memory>

//策略接口
class AbstractStrategy
{
public:
	virtual ~AbstractStrategy() = default;
	virtual std::string doAlgorithm(const std::string& data) const = 0;
};

//上下文持有策略实例引用
class Context
{
public:
	explicit Context(std::unique_ptr<AbstractStrategy>&& strategy = {})
		: currentStrategy(std::move(strategy)) {
	}

	void setStrategy(std::unique_ptr<AbstractStrategy>&& strategy) {
		currentStrategy = std::move(strategy);
	}

	void doSome() const {
		if (currentStrategy) {
			std::cout << "doSome begin" << std::endl;
			std::string result = currentStrategy->doAlgorithm("arg data");
			std::cout << "doSome result: " << result << std::endl;
		}
	}

private:
	std::unique_ptr<AbstractStrategy> currentStrategy;
};

//具体策略A
class ConcreteStrategyA : public AbstractStrategy
{
public:
	std::string doAlgorithm(const std::string& data) const override {
		std::cout << "ConcreteStrategyA doAlgorithm: " << data << std::endl;
		return "ConcreteStrategyA";
	}
};

//具体策略B
class ConcreteStrategyB : public AbstractStrategy
{
	std::string doAlgorithm(const std::string& data) const override {
		std::cout << "ConcreteStrategyB doAlgorithm: " << data << std::endl;
		return "ConcreteStrategyB";
	}
};

//测试
static void testStrategyPattern()
{
	std::cout << "context set stategy ConcreteStrategyA" << std::endl;
	Context context(std::make_unique<ConcreteStrategyA>());
	context.doSome();
	std::cout << "context set stategy ConcreteStrategyB" << std::endl;
	context.setStrategy(std::make_unique<ConcreteStrategyB>());
	context.doSome();
}