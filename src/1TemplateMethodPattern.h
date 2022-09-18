//Template Method（模板方法-类行为型）
//定义一个操作中的算法的骨架，而将一些步骤延迟到子类中。
//Template Method 使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。
#include <iostream>

//库or框架预定义一些流程及相关接口
class CoreApp
{
public:
	virtual ~CoreApp() {}

	//按流程执行
	void run() {
		std::cout << "start run" << std::endl;
		step1();
		if (step2()) {
			step3();
		}
	}

protected:
	//抽象一系列的流程步骤
	void step1() {
		std::cout << "CoreApp::step1" << std::endl;
	}
	virtual bool step2() { return false; }
	virtual void step3() {}
	//... ...
};

//库or框架使用者重新实现部分细节
class MyApp : public CoreApp
{
protected:
	bool step2() override {
		std::cout << "MyApp::step2" << std::endl;
		//... ...
		return true;
	}
	void step3() override {
		std::cout << "MyApp::step3" << std::endl;
	}
};

//测试
static void testTemplateMethodPattern()
{
	CoreApp* app = new MyApp;
	app->run();
	delete app;
}