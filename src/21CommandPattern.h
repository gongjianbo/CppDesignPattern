//Command（命令模式-对象行为型）
//别名动作（Action）、事务（Transaction）
//将一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数化；
//对请求排队或记录请求日志，以及支持可撤销的操作。
#include <iostream>
#include <string>
#include <vector>

//命令接口
class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
};

//具体命令
class ConcreteCommand1 : public Command
{
public:
	explicit ConcreteCommand1(const std::string& arg) : argument(arg) {}
	void execute() override {
		std::cout << "Command 1 execute: " << argument << std::endl;
	}
private:
	std::string argument;
};

class ConcreteCommand2 : public Command
{
public:
	explicit ConcreteCommand2(const std::string& arg) : argument(arg) {}
	void execute() override {
		std::cout << "Command 2 execute: " << argument << std::endl;
	}
private:
	std::string argument;
};

//宏命令，多个命令组合
class MacroCommand : public Command
{
public:
	void addCommand(Command* cmd) {
		commands.push_back(cmd);
	}
	void execute() override {
		for (auto& cmd : commands)
		{
			cmd->execute();
		}
	}
private:
	std::vector<Command*> commands;
};

//测试
void testCommandPattern()
{
	ConcreteCommand1 cmd1("hello");
	ConcreteCommand2 cmd2("world");

	MacroCommand macro;
	macro.addCommand(&cmd1);
	macro.addCommand(&cmd2);

	macro.execute();
}
