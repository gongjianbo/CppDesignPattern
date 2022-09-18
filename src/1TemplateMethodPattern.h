//Template Method��ģ�巽��-����Ϊ�ͣ�
//����һ�������е��㷨�ĹǼܣ�����һЩ�����ӳٵ������С�
//Template Method ʹ��������Բ��ı�һ���㷨�Ľṹ�����ض�����㷨��ĳЩ�ض����衣
#include <iostream>

//��or���Ԥ����һЩ���̼���ؽӿ�
class CoreApp
{
public:
	virtual ~CoreApp() {}

	//������ִ��
	void run() {
		std::cout << "start run" << std::endl;
		step1();
		if (step2()) {
			step3();
		}
	}

protected:
	//����һϵ�е����̲���
	void step1() {
		std::cout << "CoreApp::step1" << std::endl;
	}
	virtual bool step2() { return false; }
	virtual void step3() {}
	//... ...
};

//��or���ʹ��������ʵ�ֲ���ϸ��
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

//����
static void testTemplateMethodPattern()
{
	CoreApp* app = new MyApp;
	app->run();
	delete app;
}