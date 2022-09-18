//Observer���۲���ģʽ-������Ϊ�ͣ�
//����������Dependents��������-���ģ�Publish-Subscribe��
//���������һ��һ�Զ��������ϵ����һ�������״̬�����ı�ʱ��
//�������������Ķ��󶼵õ�֪ͨ�����Զ����¡�
//��ģ�ͣ�Ŀ����۲��߷��͹��ڸı����ϸ��Ϣ��������������Ҫ���
//��ģ�ͣ�Ŀ�����С֪ͨ��ʲôҲ���ͳ������ڴ�֮���ɹ۲�����ʽ����Ŀ���ѯϸ�ڡ�
#include <iostream>
#include <string>
#include <list>

//�۲���
class AbstractObserver
{
public:
	virtual ~AbstractObserver() {}
	//����֪ͨ��ִ����Ӧ����
	virtual void update(const std::string& message) = 0;
};

//Ŀ��
class AbstractSubject
{
public:
	virtual ~AbstractSubject() {}
	//ע��
	void attach(AbstractObserver* observer) {
		observerList.push_back(observer);
	}
	//ȡ������
	void detach(AbstractObserver* observer) {
		auto it = std::find(observerList.begin(), observerList.end(), observer);
		if (it != observerList.end()) {
			observerList.erase(it);
		}
	}
	//֪ͨ
	void notify(const std::string& message) {
		for (auto observer : observerList)
			observer->update(message);
	}

private:
	std::list<AbstractObserver*> observerList;
};

//����Ĺ۲���������
class ConcreteObserver : public AbstractObserver
{
public:
	//��дupdateִ�о���Ķ���
	void update(const std::string& message) override {
		std::cout << "observer update:" << message << std::endl;
	}
};

//�����Ŀ��������
class ConcreteSubject : public AbstractSubject
{
public:
	//����notify֪ͨ�۲���
	void doSome() {
		std::cout << "subject notify: do some begin" << std::endl;
		notify("do some begin.");
		// ... ...
		std::cout << "subject notify: do some finished" << std::endl;
		notify("do some finished.");
	}
};

//����
static void testObserverPattern()
{
	ConcreteSubject subject;
	ConcreteObserver ab1;
	ConcreteObserver ab2;
	subject.attach(&ab1);
	subject.attach(&ab2);
	subject.doSome();
}
