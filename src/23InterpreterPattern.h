//Interpreter（解析器模式-类行为型）
//给定一个语言，定义它的文法的一种表示，并定义一个解释器，这个解释器使用该表示来解释语言中的句子。
//适用于业务规则频繁变化,且类似的结构不断重复出现，并且容易抽象为语法规则的问题。
#include<iostream>
#include<map>
#include<string>
#include<stack>
#include <memory>

int counter = 0;

class Expression
{
public:
	virtual ~Expression() {}
	virtual int interpreter(std::map<char, int>) = 0;
};

class VarExpression : public Expression
{
public:
	VarExpression(const char& k) : key(k) {}
	int interpreter(std::map<char, int> var) override {
		return var[key];
	}
private:
	char key;
};

class SymbolExpression : public Expression
{
public:
	SymbolExpression(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
		: left(l), right(r) {}
protected:
	std::shared_ptr<Expression> left;
	std::shared_ptr<Expression>  right;
};

class AddExpression : public SymbolExpression
{
public:
	AddExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
		: SymbolExpression(left, right) {}
	int interpreter(std::map<char, int> var) override {
		return left->interpreter(var) + right->interpreter(var);
	}
};

class SubExpression : public SymbolExpression
{
public:
	SubExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
		: SymbolExpression(left, right) {}
	int interpreter(std::map<char, int> var) override {
		return left->interpreter(var) - right->interpreter(var);
	}
};

//计算表达式
std::shared_ptr<Expression> analyse(std::string expStr)
{
	std::stack<std::shared_ptr<Expression>> expStack;
	std::shared_ptr<Expression> left = nullptr;
	std::shared_ptr<Expression> right = nullptr;
	for (int i = 0; i < expStr.size(); ++i)
	{
		switch (expStr[i])
		{
		case '+':
			//加法运算
			left = expStack.top();
			right = std::shared_ptr<Expression>(new VarExpression(expStr[++i]));
			expStack.push(std::shared_ptr<Expression>(new AddExpression(left, right)));
			break;
		case '-':
			//减法运算
			left = expStack.top();
			right = std::shared_ptr<Expression>(new VarExpression(expStr[++i]));
			expStack.push(std::shared_ptr<Expression>(new SubExpression(left, right)));
			break;
		default:
			// 变量表达式
			expStack.push(std::shared_ptr<Expression>(new VarExpression(expStr[i])));
		}
	}
	std::shared_ptr<Expression> expression = expStack.top();
	return expression;
}

//测试
void testInterpreterPattern()
{
	std::string expStr = "a+b-c+d";
	std::map<char, int> var;
	var.insert(std::make_pair('a', 5));
	var.insert(std::make_pair('b', 2));
	var.insert(std::make_pair('c', 1));
	var.insert(std::make_pair('d', 6));

	std::cout << "expression: 5 + 2 - 1 + 6" << std::endl;
	auto expression = analyse(expStr);
	int result = expression->interpreter(var);
	std::cout << "result: " << result << std::endl;
}
