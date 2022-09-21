//Strategy������ģʽ-������Ϊ�ͣ�
//����Policy
//����һϵ�е��㷨��������һ������װ����������ʹ���ǿ����໥�滻��
//ʹ���㷨�ɶ�����ʹ�����Ŀͻ����仯��
#include <iostream>
#include <string>
#include <memory>

//���Խӿ�
class AbstractStrategy
{
public:
	virtual ~AbstractStrategy() = default;
	virtual std::string doAlgorithm(const std::string& data) const = 0;
};

//�����ĳ��в���ʵ������
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

//�������A
class ConcreteStrategyA : public AbstractStrategy
{
public:
	std::string doAlgorithm(const std::string& data) const override {
		std::cout << "ConcreteStrategyA doAlgorithm: " << data << std::endl;
		return "ConcreteStrategyA";
	}
};

//�������B
class ConcreteStrategyB : public AbstractStrategy
{
	std::string doAlgorithm(const std::string& data) const override {
		std::cout << "ConcreteStrategyB doAlgorithm: " << data << std::endl;
		return "ConcreteStrategyB";
	}
};

//����
static void testStrategyPattern()
{
	std::cout << "context set stategy ConcreteStrategyA" << std::endl;
	Context context(std::make_unique<ConcreteStrategyA>());
	context.doSome();
	std::cout << "context set stategy ConcreteStrategyB" << std::endl;
	context.setStrategy(std::make_unique<ConcreteStrategyB>());
	context.doSome();
}